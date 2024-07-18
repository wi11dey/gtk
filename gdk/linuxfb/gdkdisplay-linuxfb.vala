using GLib;
using Gdk;
using Cairo;

class FileDescriptor : FileDescriptorBased, Object {
	int fd;

	internal FileDescriptor (string file, int flags) throws FileError {
		fd = Posix.open(file, Posix.O_RDONLY);
		if (fd == -1)
			throw (FileError) new Error (FileError.quark (), FileUtils.error_from_errno (Posix.errno), "Failed to open file %s", file);
	}

	public int get_fd () {
		return fd;
	}

	~FileDescriptor () {
		Posix.close (fd);
	}
}

[Compact (opaque = true)]
class SharedMappedFile {
	FileDescriptor fd;
	size_t size;
	internal void* data;

	internal SharedMappedFile (FileDescriptor fd, size_t size) throws IOError {
		this.fd = fd;
		this.size = size;
		data = Posix.mmap (null, size, Posix.PROT_READ | Posix.PROT_WRITE, Posix.MAP_SHARED, fd.get_fd (), 0);
		if (data == Posix.MAP_FAILED) {
			throw new IOError.FAILED ("%s", strerror (errno));
		}
	}

	~SharedMappedFile () {
		Posix.munmap (data, size);
	}
}

public class GdkLinuxFbDisplay : Display {
	ImageSurface surface;
	SharedMappedFile mmapped;

	internal GdkLinuxFbDisplay (string? fb) throws FileError, IOError {
		fb = fb ?? Environment.get_variable ("LINUXFB_DISPLAY");
		FileDescriptor fd = new FileDescriptor(fb, Posix.O_RDWR);

		Linux.Framebuffer.FixScreenInfo fixed_info = {};
		if (Linux.ioctl (fd.get_fd (), Linux.Framebuffer.FBIOGET_FSCREENINFO, &fixed_info) == -1) {
			throw new IOError.FAILED ("Failed to get fixed screen information from framebuffer %s: %s", fb, strerror (errno));
		}

		Linux.Framebuffer.VarScreenInfo variable_info = {};
		if (Linux.ioctl (fd.get_fd (), Linux.Framebuffer.FBIOGET_VSCREENINFO, &variable_info) == -1) {
			throw new IOError.FAILED ("Failed to get variable screen information from framebuffer %s: %s", fb, strerror (errno));
		}

		size_t size = variable_info.xres * variable_info.yres * variable_info.bits_per_pixel / 8;
		try {
			mmapped = new SharedMappedFile ((owned) fd, size);
			surface = new ImageSurface.for_data ((uchar[]) mmapped.data, Format.ARGB32, (int) variable_info.xres, (int) variable_info.yres, (int) fixed_info.line_length); 
		} catch (IOError e) {
			throw (IOError) new Error(e.domain, e.code, "Failed to mmap framebuffer %s: %s", fb, e.message);
		}
	}
}

public Display? _gdk_linuxfb_display_open (string? display_name) {
	try {
		return new GdkLinuxFbDisplay (display_name);
	} catch (Error e) {
		error ("Failed to open Linux Framebuffer display: %s", e.message);
		return null;
	}
}
