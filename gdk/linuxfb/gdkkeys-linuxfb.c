/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2000 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
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

#include "gdkprivate-linuxfb.h"
#include "gdkinternals.h"
#include "gdkdisplay-linuxfb.h"
#include "gdkkeysprivate.h"
#include "gdkkeysyms.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <limits.h>
#include <errno.h>

typedef struct _GdkLinuxFbKeymap   GdkLinuxFbKeymap;
typedef struct _GdkKeymapClass GdkLinuxFbKeymapClass;

#define GDK_TYPE_LINUXFB_KEYMAP          (gdk_linuxfb_keymap_get_type ())
#define GDK_LINUXFB_KEYMAP(object)       (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_LINUXFB_KEYMAP, GdkLinuxFbKeymap))
#define GDK_IS_LINUXFB_KEYMAP(object)    (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_LINUXFB_KEYMAP))

static GType gdk_linuxfb_keymap_get_type (void);

typedef struct _DirectionCacheEntry DirectionCacheEntry;

struct _GdkLinuxFbKeymap
{
  GdkKeymap     parent_instance;
};

struct _GdkLinuxFbKeymapClass
{
  GdkKeymapClass keymap_class;
};

G_DEFINE_TYPE (GdkLinuxFbKeymap, gdk_linuxfb_keymap, GDK_TYPE_KEYMAP)

  static void  gdk_linuxfb_keymap_finalize   (GObject           *object);

static void
gdk_linuxfb_keymap_init (GdkLinuxFbKeymap *keymap)
{
}

static void
gdk_linuxfb_keymap_finalize (GObject *object)
{
  G_OBJECT_CLASS (gdk_linuxfb_keymap_parent_class)->finalize (object);
}

GdkKeymap*
_gdk_linuxfb_display_get_keymap (GdkDisplay *display)
{
  GdkLinuxFbDisplay *linuxfb_display;

  g_return_val_if_fail (GDK_IS_DISPLAY (display), NULL);
  linuxfb_display = GDK_LINUXFB_DISPLAY (display);

  if (!linuxfb_display->keymap)
    linuxfb_display->keymap = g_object_new (gdk_linuxfb_keymap_get_type (), NULL);

  linuxfb_display->keymap->display = display;

  return linuxfb_display->keymap;
}

static PangoDirection
gdk_linuxfb_keymap_get_direction (GdkKeymap *keymap)
{
  return PANGO_DIRECTION_NEUTRAL;
}

static gboolean
gdk_linuxfb_keymap_have_bidi_layouts (GdkKeymap *keymap)
{
  return FALSE;
}

static gboolean
gdk_linuxfb_keymap_get_caps_lock_state (GdkKeymap *keymap)
{
  return FALSE;
}

static gboolean
gdk_linuxfb_keymap_get_num_lock_state (GdkKeymap *keymap)
{
  return FALSE;
}

static gboolean
gdk_linuxfb_keymap_get_scroll_lock_state (GdkKeymap *keymap)
{
  return FALSE;
}

static gboolean
gdk_linuxfb_keymap_get_entries_for_keyval (GdkKeymap     *keymap,
					    guint          keyval,
					    GdkKeymapKey **keys,
					    gint          *n_keys)
{
  if (n_keys)
    *n_keys = 1;
  if (keys)
    {
      *keys = g_new0 (GdkKeymapKey, 1);
      (*keys)->keycode = keyval;
    }

  return TRUE;
}

static gboolean
gdk_linuxfb_keymap_get_entries_for_keycode (GdkKeymap     *keymap,
					     guint          hardware_keycode,
					     GdkKeymapKey **keys,
					     guint        **keyvals,
					     gint          *n_entries)
{
  if (n_entries)
    *n_entries = 1;
  if (keys)
    {
      *keys = g_new0 (GdkKeymapKey, 1);
      (*keys)->keycode = hardware_keycode;
    }
  if (keyvals)
    {
      *keyvals = g_new0 (guint, 1);
      (*keyvals)[0] = hardware_keycode;
    }
  return TRUE;
}

static guint
gdk_linuxfb_keymap_lookup_key (GdkKeymap          *keymap,
				const GdkKeymapKey *key)
{
  return key->keycode;
}


static gboolean
gdk_linuxfb_keymap_translate_keyboard_state (GdkKeymap       *keymap,
					      guint            hardware_keycode,
					      GdkModifierType  state,
					      gint             group,
					      guint           *keyval,
					      gint            *effective_group,
					      gint            *level,
					      GdkModifierType *consumed_modifiers)
{
  if (keyval)
    *keyval = hardware_keycode;
  if (effective_group)
    *effective_group = 0;
  if (level)
    *level = 0;
  return TRUE;
}

static void
gdk_linuxfb_keymap_add_virtual_modifiers (GdkKeymap       *keymap,
					   GdkModifierType *state)
{
}

static gboolean
gdk_linuxfb_keymap_map_virtual_modifiers (GdkKeymap       *keymap,
					   GdkModifierType *state)
{
  return TRUE;
}

static void
gdk_linuxfb_keymap_class_init (GdkLinuxFbKeymapClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GdkKeymapClass *keymap_class = GDK_KEYMAP_CLASS (klass);

  object_class->finalize = gdk_linuxfb_keymap_finalize;

  keymap_class->get_direction = gdk_linuxfb_keymap_get_direction;
  keymap_class->have_bidi_layouts = gdk_linuxfb_keymap_have_bidi_layouts;
  keymap_class->get_caps_lock_state = gdk_linuxfb_keymap_get_caps_lock_state;
  keymap_class->get_num_lock_state = gdk_linuxfb_keymap_get_num_lock_state;
  keymap_class->get_scroll_lock_state = gdk_linuxfb_keymap_get_scroll_lock_state;
  keymap_class->get_entries_for_keyval = gdk_linuxfb_keymap_get_entries_for_keyval;
  keymap_class->get_entries_for_keycode = gdk_linuxfb_keymap_get_entries_for_keycode;
  keymap_class->lookup_key = gdk_linuxfb_keymap_lookup_key;
  keymap_class->translate_keyboard_state = gdk_linuxfb_keymap_translate_keyboard_state;
  keymap_class->add_virtual_modifiers = gdk_linuxfb_keymap_add_virtual_modifiers;
  keymap_class->map_virtual_modifiers = gdk_linuxfb_keymap_map_virtual_modifiers;
}

