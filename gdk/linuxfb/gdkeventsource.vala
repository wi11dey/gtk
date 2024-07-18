using GLib;

class GdkEventSource : Source  {
	protected override bool dispatch(SourceFunc? _callback)
	{
		return true;
	}
}
