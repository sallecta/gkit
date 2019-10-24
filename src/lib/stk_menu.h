#ifndef STK_MENU_H
#define STK_MENU_H

#include <gkit_widget.h>

gkit_widget *stk_menu_new(gkit_widget *, int, int, uint, uint, char*);
void        stk_menu_show(gkit_widget *);
void        stk_menu_handle(GKITEvent *, void *);
void        stk_menu_set_size(gkit_widget *);
void        stk_menu_set_pos(gkit_widget *, uint, uint);
void        stk_menu_set_color(gkit_widget *, int color);

#endif /* STK_MENU_H */
