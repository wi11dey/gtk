add_languages('vala')

gdk_linuxfb_sources = files(
  'gdkdisplay-linuxfb.vala',
  'gdkeventsource.vala'
)

gdk_linuxfb_public_headers = files()

libgdk_linuxfb = static_library('gdk-linuxfb',
                                gdk_linuxfb_sources, gdkconfig, gdkenum_h,
                                include_directories: [confinc, gdkinc],
                                c_args: [
                                  '-DGDK_COMPILATION',
                                  '-DG_LOG_DOMAIN="Gdk"',
                                ] + common_cflags,
                                link_args: common_ldflags,
                                dependencies: [gdk_vapi]
                               )
