gdk_linuxfb_sources = files(
  'gdkcursor-linuxfb.c',
  'gdkdevice-linuxfb.c',
  'gdkdevicemanager-linuxfb.c',
  'gdkdisplay-linuxfb.c',
  'gdkdnd-linuxfb.c',
  'gdkeventsource.c',
  'gdkglobals-linuxfb.c',
  'gdkkeys-linuxfb.c',
  'gdkmonitor-linuxfb.c',
  'gdkproperty-linuxfb.c',
  'gdkscreen-linuxfb.c',
  'gdkselection-linuxfb.c',
  'gdktestutils-linuxfb.c',
  'gdkvisual-linuxfb.c',
  'gdkwindow-linuxfb.c',
  'gdklinuxfb-server.c',
)

gdk_linuxfb_public_headers = files(
  'gdklinuxfbdisplay.h',
  'gdklinuxfbwindow.h',
  'gdklinuxfbcursor.h',
  'gdklinuxfbmonitor.h',
  'gdklinuxfbvisual.h',
)

install_headers(gdk_linuxfb_public_headers, subdir: 'gtk-3.0/gdk/linuxfb/')
install_headers('gdklinuxfb.h', subdir: 'gtk-3.0/gdk/')

gdk_linuxfb_deps = [shmlib]

libgdk_linuxfb = static_library('gdk-linuxfb',
  gdk_linuxfb_sources, gdkconfig, gdkenum_h,
  include_directories: [confinc, gdkinc],
  c_args: [
    '-DGDK_COMPILATION',
    '-DG_LOG_DOMAIN="Gdk"',
  ] + common_cflags,
  link_args: common_ldflags,
  dependencies: [gdk_deps, gdk_linuxfb_deps])
