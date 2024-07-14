/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2009 Carlos Garnacho <carlosg@gnome.org>
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

#ifndef __GDK_DEVICE_MANAGER_LINUXFB_H__
#define __GDK_DEVICE_MANAGER_LINUXFB_H__

#include <gdk/gdkdevicemanagerprivate.h>

G_BEGIN_DECLS

#define GDK_TYPE_LINUXFB_DEVICE_MANAGER         (gdk_linuxfb_device_manager_get_type ())
#define GDK_LINUXFB_DEVICE_MANAGER(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_LINUXFB_DEVICE_MANAGER, GdkLinuxFbDeviceManager))
#define GDK_LINUXFB_DEVICE_MANAGER_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GDK_TYPE_LINUXFB_DEVICE_MANAGER, GdkLinuxFbDeviceManagerClass))
#define GDK_IS_LINUXFB_DEVICE_MANAGER(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_LINUXFB_DEVICE_MANAGER))
#define GDK_IS_LINUXFB_DEVICE_MANAGER_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GDK_TYPE_LINUXFB_DEVICE_MANAGER))
#define GDK_LINUXFB_DEVICE_MANAGER_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDK_TYPE_LINUXFB_DEVICE_MANAGER, GdkLinuxFbDeviceManagerClass))

typedef struct _GdkLinuxFbDeviceManager GdkLinuxFbDeviceManager;
typedef struct _GdkLinuxFbDeviceManagerClass GdkLinuxFbDeviceManagerClass;

struct _GdkLinuxFbDeviceManager
{
  GdkDeviceManager parent_object;
  GdkDevice *core_pointer;
  GdkDevice *core_keyboard;
  GdkDevice *touchscreen;
};

struct _GdkLinuxFbDeviceManagerClass
{
  GdkDeviceManagerClass parent_class;
};

GType gdk_linuxfb_device_manager_get_type (void) G_GNUC_CONST;
GdkDeviceManager *_gdk_linuxfb_device_manager_new (GdkDisplay *display);

G_END_DECLS

#endif /* __GDK_DEVICE_MANAGER_LINUXFB_H__ */
