add_languages('vala')

gdk_linuxfb_sources = files(
  'gdklinuxfbdisplay.vala',
  'gdkeventsource.vala'
)

gdk_linuxfb_public_headers = files()

gdk_linuxfb_deps = []

valac = meson.get_compiler('vala')

gdk_linuxfb_vapi_dir = meson.current_source_dir()

libgdk_linuxfb = static_library('gdk-linuxfb',
                                gdk_linuxfb_sources, gdkconfig, gdkenum_h,
                                include_directories: [confinc, gdkinc],
                                vala_args: ['--vapidir', gdk_linuxfb_vapi_dir],
                                c_args: [
                                  '-DGDK_COMPILATION',
                                  '-DG_LOG_DOMAIN="Gdk"',
                                ] + common_cflags,
                                link_args: common_ldflags,
                                dependencies: [
                                  dependency('cairo'),
                                  valac.find_library('gdk-3.0', dirs: gdk_linuxfb_vapi_dir),
                                  dependency('gdk-pixbuf-2.0'),
                                  dependency('gio-2.0'),
                                  dependency('gio-unix-2.0'),
                                  dependency('pango'),
                                  # dependency('linux'),
                                  valac.find_library('linux'),
                                  # dependency('posix'),
                                  valac.find_library('posix'),
                                ])
