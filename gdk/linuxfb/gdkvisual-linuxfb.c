/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
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

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#include "config.h"

#include "gdkvisualprivate.h"

#include "gdkprivate-linuxfb.h"
#include "gdkscreen-linuxfb.h"
#include "gdkinternals.h"

struct _GdkLinuxFbVisual
{
  GdkVisual visual;
};

struct _GdkLinuxFbVisualClass
{
  GObjectClass parent_class;
};

G_DEFINE_TYPE (GdkLinuxFbVisual, gdk_linuxfb_visual, GDK_TYPE_VISUAL)

     static void
     gdk_linuxfb_visual_finalize (GObject *object)
{
  G_OBJECT_CLASS (gdk_linuxfb_visual_parent_class)->finalize (object);
}

static void
gdk_linuxfb_visual_class_init (GdkLinuxFbVisualClass *visual_class)
{
  GObjectClass *object_class = G_OBJECT_CLASS (visual_class);

  object_class->finalize = gdk_linuxfb_visual_finalize;
}

static void
gdk_linuxfb_visual_init (GdkLinuxFbVisual *visual)
{
}

void
_gdk_linuxfb_screen_init_visuals (GdkScreen *screen)
{
  GdkLinuxFbScreen *linuxfb_screen;
  GdkVisual **visuals;
  int nvisuals;

  g_return_if_fail (GDK_IS_SCREEN (screen));
  linuxfb_screen = GDK_LINUXFB_SCREEN (screen);

  nvisuals = 2;
  visuals = g_new (GdkVisual *, nvisuals);

  visuals[0] = g_object_new (GDK_TYPE_LINUXFB_VISUAL, NULL);
  visuals[0]->screen = screen;
  visuals[0]->type = GDK_VISUAL_TRUE_COLOR;
  visuals[0]->depth = 32;
  visuals[0]->byte_order = (G_BYTE_ORDER == G_LITTLE_ENDIAN) ? GDK_LSB_FIRST : GDK_MSB_FIRST;
  visuals[0]->red_mask = 0xff0000;
  visuals[0]->green_mask = 0xff00;
  visuals[0]->blue_mask = 0xff;
  visuals[0]->colormap_size = 256;
  visuals[0]->bits_per_rgb = 8;

  visuals[1] = g_object_new (GDK_TYPE_LINUXFB_VISUAL, NULL);
  visuals[1]->screen = screen;
  visuals[1]->type = GDK_VISUAL_TRUE_COLOR;
  visuals[1]->depth = 24;
  visuals[1]->byte_order = (G_BYTE_ORDER == G_LITTLE_ENDIAN) ? GDK_LSB_FIRST : GDK_MSB_FIRST;
  visuals[1]->red_mask = 0xff0000;
  visuals[1]->green_mask = 0xff00;
  visuals[1]->blue_mask = 0xff;
  visuals[1]->colormap_size = 256;
  visuals[1]->bits_per_rgb = 8;

  linuxfb_screen->system_visual = visuals[1];
  linuxfb_screen->rgba_visual = visuals[0];

  linuxfb_screen->navailable_depths = 2;
  linuxfb_screen->available_depths[0] = 32;
  linuxfb_screen->available_depths[1] = 24;

  linuxfb_screen->navailable_types = 1;
  linuxfb_screen->available_types[0] = GDK_VISUAL_TRUE_COLOR;

  linuxfb_screen->visuals = visuals;
  linuxfb_screen->nvisuals = nvisuals;
}

gint
_gdk_linuxfb_screen_visual_get_best_depth (GdkScreen * screen)
{
  return GDK_LINUXFB_SCREEN (screen)->available_depths[0];
}

GdkVisualType
_gdk_linuxfb_screen_visual_get_best_type (GdkScreen * screen)
{
  return GDK_LINUXFB_SCREEN (screen)->available_types[0];
}

GdkVisual *
_gdk_linuxfb_screen_get_system_visual (GdkScreen * screen)
{
  g_return_val_if_fail (GDK_IS_SCREEN (screen), NULL);

  return ((GdkVisual *) GDK_LINUXFB_SCREEN (screen)->system_visual);
}

GdkVisual*
_gdk_linuxfb_screen_visual_get_best (GdkScreen * screen)
{
  GdkLinuxFbScreen *linuxfb_screen = GDK_LINUXFB_SCREEN (screen);

  return (GdkVisual *)linuxfb_screen->visuals[0];
}

GdkVisual*
_gdk_linuxfb_screen_visual_get_best_with_depth (GdkScreen * screen,
						 gint depth)
{
  GdkLinuxFbScreen *linuxfb_screen = GDK_LINUXFB_SCREEN (screen);
  GdkVisual *return_val;
  int i;

  return_val = NULL;
  for (i = 0; i < linuxfb_screen->nvisuals; i++)
    if (depth == linuxfb_screen->visuals[i]->depth)
      {
	return_val = (GdkVisual *) linuxfb_screen->visuals[i];
	break;
      }

  return return_val;
}

GdkVisual*
_gdk_linuxfb_screen_visual_get_best_with_type (GdkScreen * screen,
						GdkVisualType visual_type)
{
  GdkLinuxFbScreen *linuxfb_screen = GDK_LINUXFB_SCREEN (screen);
  GdkVisual *return_val;
  int i;

  return_val = NULL;
  for (i = 0; i < linuxfb_screen->nvisuals; i++)
    if (visual_type == linuxfb_screen->visuals[i]->type)
      {
	return_val = (GdkVisual *) linuxfb_screen->visuals[i];
	break;
      }

  return return_val;
}

GdkVisual*
_gdk_linuxfb_screen_visual_get_best_with_both (GdkScreen * screen,
						gint          depth,
						GdkVisualType visual_type)
{
  GdkLinuxFbScreen *linuxfb_screen = GDK_LINUXFB_SCREEN (screen);
  GdkVisual *return_val;
  int i;

  return_val = NULL;
  for (i = 0; i < linuxfb_screen->nvisuals; i++)
    if ((depth == linuxfb_screen->visuals[i]->depth) &&
	(visual_type == linuxfb_screen->visuals[i]->type))
      {
	return_val = (GdkVisual *) linuxfb_screen->visuals[i];
	break;
      }

  return return_val;
}

void
_gdk_linuxfb_screen_query_depths  (GdkScreen * screen,
				   gint **depths,
				    gint  *count)
{
  GdkLinuxFbScreen *linuxfb_screen = GDK_LINUXFB_SCREEN (screen);

  *count = linuxfb_screen->navailable_depths;
  *depths = linuxfb_screen->available_depths;
}

void
_gdk_linuxfb_screen_query_visual_types (GdkScreen * screen,
					GdkVisualType **visual_types,
					 gint           *count)
{
  GdkLinuxFbScreen *linuxfb_screen = GDK_LINUXFB_SCREEN (screen);

  *count = linuxfb_screen->navailable_types;
  *visual_types = linuxfb_screen->available_types;
}

GList *
_gdk_linuxfb_screen_list_visuals (GdkScreen *screen)
{
  GList *list;
  GdkLinuxFbScreen *linuxfb_screen;
  guint i;

  g_return_val_if_fail (GDK_IS_SCREEN (screen), NULL);
  linuxfb_screen = GDK_LINUXFB_SCREEN (screen);

  list = NULL;

  for (i = 0; i < linuxfb_screen->nvisuals; ++i)
    list = g_list_append (list, linuxfb_screen->visuals[i]);

  return list;
}
