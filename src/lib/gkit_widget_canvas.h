#ifndef gkit_widget_canvas_H
#define gkit_widget_canvas_H

#include "gkit_widget.h"

/* STKCanvas Events */
#define gkit_widget_canvas_EXPOSE   0x10
#define gkit_widget_canvas_PRESS    0x20
#define gkit_widget_canvas_RELEASE  0x30
#define gkit_widget_canvas_ENTER    0x40
#define gkit_widget_canvas_LEAVE    0x50
#define gkit_widget_canvas_MOVE     0x60


typedef struct
{
    Pixmap pmap;
} stk_canvas;



gkit_widget *gkit_widget_canvas_new(gkit_widget *, int, int, uint, uint);
void        gkit_widget_canvas_draw_line(gkit_widget *, uint, uint, uint, uint);
void        gkit_widget_canvas_draw_point(gkit_widget *, uint, uint);
void        gkit_widget_canvas_draw_arc(gkit_widget *, uint, uint, uint, uint, uint, uint);
void        gkit_widget_canvas_draw_rectangle(gkit_widget *, int, int);
void        gkit_widget_canvas_draw_string(gkit_widget *pl, uint x, uint y, char *str);
void        gkit_widget_canvas_set_string_font_size(gkit_widget *, char *);
void        gkit_widget_canvas_set_string_font(gkit_widget *, char *);
void        gkit_widget_canvas_handle(GKITEvent *, void *);


/* TODO */
void gkit_widget_canvas_area_rotate(gkit_widget *pl, uint x0, uint y0, uint x1, uint y1, uint angle);
void gkit_widget_canvas_area_move(gkit_widget *pl, uint x0, uint y0, uint x1, uint y1, uint x, uint y);
void gkit_widget_canvas_line_color(gkit_widget *pl, int color);


#endif /* gkit_widget_canvas_H */
