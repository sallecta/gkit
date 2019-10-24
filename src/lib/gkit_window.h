#ifndef gkit_window_H
#define gkit_window_H

#include "gkit_widget.h"

gkit_widget *gkit_window_new(int, int, uint, uint, const char *);
void        gkit_window_show(gkit_widget *);
void        gkit_window_set_title(gkit_widget *, const char *);
void        gkit_window_handle(GKITEvent *, void *);
void        gkit_window_set_size(gkit_widget *);
void        gkit_window_set_pos(gkit_widget *, uint, uint);
void        gkit_window_set_color(gkit_widget *, int color);

#endif /* gkit_window_H */
