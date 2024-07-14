#ifndef __LINUXFB_BUFFER__
#define __LINUXFB_BUFFER__

#include "linuxfb-protocol.h"
#include <glib-object.h>

typedef struct _LinuxFbBuffer LinuxFbBuffer;

LinuxFbBuffer *linuxfb_buffer_create     (int             width,
					  int             height,
                                            guint8         *data,
                                            int             stride);
void            linuxfb_buffer_destroy    (LinuxFbBuffer *buffer);
void            linuxfb_buffer_encode     (LinuxFbBuffer *buffer,
					   LinuxFbBuffer *prev,
                                            GString        *dest);
int             linuxfb_buffer_get_width  (LinuxFbBuffer *buffer);
int             linuxfb_buffer_get_height (LinuxFbBuffer *buffer);

#endif /* __LINUXFB_BUFFER__ */
