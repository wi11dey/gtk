using GLib;
using Gdk;

extern List<Event> _gdk_event_queue_append (Display display, Event event);

[Compact (opaque = true)]
class GdkEvdevEventSource : Source  {
	private int fd;
	private void* tag;

	protected GdkEvdevEventSource (int fd) {
		this.fd = fd;
		tag = add_unix_fd (fd, IOCondition.HUP | IOCondition.IN);

		set_can_recurse (true);
	}

	protected override bool dispatch (SourceFunc? _callback) {
		if (IOCondition.HUP in query_unix_fd (tag))
			return Source.REMOVE;

		Linux.Input.Event raw_event = {};
		if (Posix.read (fd, &raw_event, sizeof (Linux.Input.Event)) == 0)
			return Source.CONTINUE;

		Event event;
		switch (raw_event.type) {
		case Linux.Input.EV_REL:
			event = new Event(EventType.MOTION_NOTIFY);
			break;
		default:
			return Source.CONTINUE;
		}
		_gdk_event_queue_append (null, event);

		return Source.CONTINUE;
	}
}

/**
 * Event source checking for new evdev inputs.
 */
[Compact (opaque = true)]
class GdkEventSource : Source  {
	private HashTable<string, Source> devices = new HashTable<string, Source> (str_hash, str_equal);

	protected GdkEventSource () {
		set_can_recurse (false);
	}

	protected override bool check () {
		return true;
	}

	protected override bool dispatch (SourceFunc? callback) {
		callback ();
		return Source.CONTINUE;
	}
}
