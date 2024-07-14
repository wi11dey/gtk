/*
 * gdkdisplay-linuxfb.h
 * 
 * Copyright 2001 Sun Microsystems Inc. 
 *
 * Erwann Chenede <erwann.chenede@sun.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GDK_LINUXFB_DISPLAY__
#define __GDK_LINUXFB_DISPLAY__

#include "gdklinuxfbdisplay.h"

#include "gdkdisplayprivate.h"
#include "gdkkeys.h"
#include "gdkwindow.h"
#include "gdkinternals.h"
#include "gdkmain.h"
#include "gdklinuxfb-server.h"
#include "gdkmonitorprivate.h"

G_BEGIN_DECLS

struct _GdkLinuxFbDisplay
{
  GdkDisplay parent_instance;
  GdkScreen *default_screen;
  GdkScreen **screens;

  GHashTable *id_ht;
  GList *toplevels;

  GSource *event_source;

  /* Keyboard related information */
  GdkKeymap *keymap;

  /* drag and drop information */
  GdkDragContext *current_dest_drag;

  /* The offscreen window that has the pointer in it (if any) */
  GdkWindow *active_offscreen_window;

  GdkLinuxFbServer *server;

  gpointer move_resize_data;

  GdkMonitor *monitor;
};

struct _GdkLinuxFbDisplayClass
{
  GdkDisplayClass parent_class;
};

G_END_DECLS

#endif				/* __GDK_LINUXFB_DISPLAY__ */
