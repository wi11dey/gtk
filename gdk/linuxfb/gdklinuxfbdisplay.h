/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2013 Alexander Larsson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GDK_LINUXFB_DISPLAY_H__
#define __GDK_LINUXFB_DISPLAY_H__

#if !defined (__GDKLINUXFB_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdklinuxfb.h> can be included directly."
#endif

#include <gdk/gdk.h>

G_BEGIN_DECLS

#ifdef GDK_COMPILATION
typedef struct _GdkLinuxFbDisplay GdkLinuxFbDisplay;
#else
typedef GdkDisplay GdkLinuxFbDisplay;
#endif
typedef struct _GdkLinuxFbDisplayClass GdkLinuxFbDisplayClass;

#define GDK_TYPE_LINUXFB_DISPLAY              (gdk_linuxfb_display_get_type())
#define GDK_LINUXFB_DISPLAY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_LINUXFB_DISPLAY, GdkLinuxFbDisplay))
#define GDK_LINUXFB_DISPLAY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_LINUXFB_DISPLAY, GdkLinuxFbDisplayClass))
#define GDK_IS_LINUXFB_DISPLAY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_LINUXFB_DISPLAY))
#define GDK_IS_LINUXFB_DISPLAY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_LINUXFB_DISPLAY))
#define GDK_LINUXFB_DISPLAY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_LINUXFB_DISPLAY, GdkLinuxFbDisplayClass))

GDK_AVAILABLE_IN_ALL
GType                   gdk_linuxfb_display_get_type            (void);

GDK_AVAILABLE_IN_3_12
void                    gdk_linuxfb_display_show_keyboard       (GdkLinuxFbDisplay *display);
GDK_AVAILABLE_IN_3_12
void                    gdk_linuxfb_display_hide_keyboard       (GdkLinuxFbDisplay *display);

G_END_DECLS

#endif /* __GDK_LINUXFB_DISPLAY_H__ */
