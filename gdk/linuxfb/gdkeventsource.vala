using GLib;
using Gdk;

extern List<Event> _gdk_event_queue_append (Display display, owned Event event);

const string EVDEV_DIRECTORY = "/dev/input";

[Compact (opaque = true)]
class GdkEvdevEventSource : Source  {
	int fd;
	void* tag;

	internal GdkEvdevEventSource (int fd) {
		this.fd = fd;
		tag = add_unix_fd (fd, IOCondition.HUP | IOCondition.IN);

		set_can_recurse (true);
	}

	protected override bool dispatch (SourceFunc? _callback) {
		if (IOCondition.HUP in query_unix_fd (tag))
			return Source.REMOVE;

		Linux.Input.Event raw = {};
		if (Posix.read (fd, &raw, sizeof (Linux.Input.Event)) == 0)
			return Source.CONTINUE;

		Event event = translate (raw);
		if (event != null)
			_gdk_event_queue_append (null, (owned) event);

		return Source.CONTINUE;
	}

	private static Event? translate (Linux.Input.Event raw) {
		switch (raw.type) {
		case Linux.Input.EV_KEY:
			EventKey event = (EventKey) new Event(EventType.KEY_PRESS);
			return event;
		case Linux.Input.EV_REL:
			EventMotion event = (EventMotion) new Event(EventType.MOTION_NOTIFY);

			switch ((int) raw.code) {
			case Linux.Input.REL_X:
				event.x = raw.value;
				break;
			case Linux.Input.REL_Y:
				event.y = raw.value;
				break;
			}

			return event;
		}
		return null;
	}

	~GdkEvdevEventSource () {
		Posix.close (fd);
	}
}

/**
 * Event source checking for new evdev inputs.
 */
[Compact (opaque = true)]
class GdkEventSource : Source  {
	FileMonitor monitor;

	internal GdkEventSource (Display display) {
		try {
			monitor = File.new_for_path (EVDEV_DIRECTORY).monitor_directory (FileMonitorFlags.NONE);
			monitor.changed.connect ((source, _destination, event) => {
					if (!(FileMonitorEvent.CREATED in event))
						return;

					string device = source.get_path();
					try {
						add_child_source (new GdkEvdevEventSource (open (device)));
					} catch (FileError e) {
						error ("%s", e.message);
					}
				});
		} catch (IOError e) {
			warning ("Failed to monitor /dev/input for new devices, falling back to non-hotpluggable devices: %s", e.message);

			try {
				Dir devices = Dir.open (EVDEV_DIRECTORY);
				unowned string device;
				while ((device = devices.read_name ()) != null) {
					if (!device.has_prefix ("event"))
						continue;
					
					try {
						add_child_source (new GdkEvdevEventSource (open (device)));
					} catch (FileError e) {
						error ("%s", e.message);
					}
				}
				if (errno != 0) {
					error ("Failed to iterate /dev/input for fallback: %s", strerror (errno));
				}
			} catch (FileError e) {
				error ("Failed to open /dev/input to iterator for fallback: %s", e.message);
			}
		}

		set_can_recurse (false);
	}

	private static int open (string device) throws FileError {
		int fd = Posix.open(device, Posix.O_RDONLY);
		if (fd == -1)
			throw (FileError) new Error (FileError.quark (), FileUtils.error_from_errno (Posix.errno), "Failed to open device %s", device);
		return fd;
	}

	protected override bool prepare (out int timeout) {
		timeout = 0;
		return true;
	}

	protected override bool check () {
		return false;
	}

	protected override bool dispatch (SourceFunc? callback) {
		return Source.CONTINUE;
	}
}

public Source _gdk_linuxfb_event_source_new (Display display) {
	return new GdkEventSource (display);
}
