/*
 * gdkscreen-linuxfb.h
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

#ifndef __GDK_LINUXFB_SCREEN_H__
#define __GDK_LINUXFB_SCREEN_H__

#include <gdk/gdkscreenprivate.h>
#include <gdk/gdkvisual.h>
#include "gdkprivate-linuxfb.h"

G_BEGIN_DECLS

typedef struct _GdkLinuxFbScreen GdkLinuxFbScreen;
typedef struct _GdkLinuxFbScreenClass GdkLinuxFbScreenClass;

#define GDK_TYPE_LINUXFB_SCREEN              (gdk_linuxfb_screen_get_type ())
#define GDK_LINUXFB_SCREEN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_LINUXFB_SCREEN, GdkLinuxFbScreen))
#define GDK_LINUXFB_SCREEN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_LINUXFB_SCREEN, GdkLinuxFbScreenClass))
#define GDK_IS_LINUXFB_SCREEN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_LINUXFB_SCREEN))
#define GDK_IS_LINUXFB_SCREEN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_LINUXFB_SCREEN))
#define GDK_LINUXFB_SCREEN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_LINUXFB_SCREEN, GdkLinuxFbScreenClass))

typedef struct _GdkLinuxFbMonitor GdkLinuxFbMonitor;

struct _GdkLinuxFbScreen
{
  GdkScreen parent_instance;

  GdkDisplay *display;
  GdkWindow *root_window;

  int width;
  int height;

  /* Visual Part */
  GdkVisual **visuals;
  gint nvisuals;
  GdkVisual *system_visual;
  GdkVisual *rgba_visual;
  gint available_depths[7];
  gint navailable_depths;
  GdkVisualType available_types[6];
  gint navailable_types;
};

struct _GdkLinuxFbScreenClass
{
  GdkScreenClass parent_class;

  void (* window_manager_changed) (GdkLinuxFbScreen *screen);
};

GType       gdk_linuxfb_screen_get_type (void);
GdkScreen * _gdk_linuxfb_screen_new      (GdkDisplay *display,
					  gint	  screen_number);
void _gdk_linuxfb_screen_setup           (GdkScreen *screen);

G_END_DECLS

#endif /* __GDK_LINUXFB_SCREEN_H__ */
