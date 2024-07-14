#ifndef __LINUXFB_H__
#define __LINUXFB_H__

#include <glib.h>
#include <gio/gio.h>
#include "linuxfb-protocol.h"
#include "linuxfb-buffer.h"

typedef struct LinuxFbOutput LinuxFbOutput;

typedef enum {
  LINUXFB_WS_CONTINUATION = 0,
  LINUXFB_WS_TEXT = 1,
  LINUXFB_WS_BINARY = 2,
  LINUXFB_WS_CNX_CLOSE = 8,
  LINUXFB_WS_CNX_PING = 9,
  LINUXFB_WS_CNX_PONG = 0xa
} LinuxFbWSOpCode;

LinuxFbOutput *linuxfb_output_new             (GOutputStream  *out,
					       guint32         serial);
void            linuxfb_output_free            (LinuxFbOutput *output);
int             linuxfb_output_flush           (LinuxFbOutput *output);
int             linuxfb_output_has_error       (LinuxFbOutput *output);
void            linuxfb_output_set_next_serial (LinuxFbOutput *output,
						 guint32         serial);
guint32         linuxfb_output_get_next_serial (LinuxFbOutput *output);
void            linuxfb_output_new_surface     (LinuxFbOutput *output,
						 int             id,
						 int             x,
						 int             y,
						 int             w,
						 int             h,
						 gboolean        is_temp);
void            linuxfb_output_disconnected    (LinuxFbOutput *output);
void            linuxfb_output_show_surface    (LinuxFbOutput *output,
						 int             id);
void            linuxfb_output_hide_surface    (LinuxFbOutput *output,
						int             id);
void            linuxfb_output_raise_surface   (LinuxFbOutput *output,
						int             id);
void            linuxfb_output_lower_surface   (LinuxFbOutput *output,
						int             id);
void            linuxfb_output_destroy_surface (LinuxFbOutput *output,
						int             id);
void            linuxfb_output_move_resize_surface (LinuxFbOutput *output,
						    int             id,
						     gboolean        has_pos,
						     int             x,
						     int             y,
						     gboolean        has_size,
						     int             w,
						     int             h);
void            linuxfb_output_set_transient_for (LinuxFbOutput *output,
						  int             id,
						   int             parent_id);
void            linuxfb_output_put_buffer      (LinuxFbOutput *output,
						int             id,
                                                 LinuxFbBuffer *prev_buffer,
                                                 LinuxFbBuffer *buffer);
void            linuxfb_output_grab_pointer    (LinuxFbOutput *output,
						int id,
						 gboolean owner_event);
guint32         linuxfb_output_ungrab_pointer  (LinuxFbOutput *output);
void            linuxfb_output_pong            (LinuxFbOutput *output);
void            linuxfb_output_set_show_keyboard (LinuxFbOutput *output,
						  gboolean show);

#endif /* __LINUXFB_H__ */
