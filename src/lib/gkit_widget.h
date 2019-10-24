#ifndef GKIT_WIDGET_H
#define GKIT_WIDGET_H
#include <gkit_config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h> 



/* gkit_widget Events */
#define GKIT_EVENT_EXPOSE     0x10
#define GKIT_EVENT_PRESS      0x20
#define GKIT_EVENT_RELEASE    0x30
#define GKIT_EVENT_ENTER      0x40
#define GKIT_EVENT_LEAVE      0x50
#define GKIT_EVENT_MOVE       0x60
#define GKIT_EVENT_KEYPRESS   0x70
#define GKIT_EVENT_KEYRELEASE 0x80


typedef XEvent GKITEvent;

Display *display;


typedef struct widget_ptr
{
    void *this;
    struct widget_ptr *prev, *next;
} widget_list;


typedef struct
{
    uint w, h;
    int     x, y;
    Window  win;
    Display *dsp;
    void    (*handler)(GKITEvent *, void *);
    int     mask;
    GC gc, gc2;
    XFontStruct *font_info;
    GKITEvent *ev;
    widget_list *child_list;
    char *fontname;
    char *label;
    void *ext_struct; /* if need a place to store a reference to other struct, if it's not a basic widget, etc. */
    void (*movefunc)(void *),     *margs;  /* move event       */
    void (*pressfunc)(void *),    *pargs;  /* press event      */
    void (*enterfunc)(void *),    *eargs;  /* enter event      */
    void (*leavefunc)(void *),    *largs;  /* leave event      */
    void (*exposefunc)(void *),   *exargs; /* expose event     */
    void (*releasefunc)(void *),  *rargs;  /* realse event     */
    void (*kpressfunc)(void *),   *kpxargs;/* keypress event   */
    void (*kreleasefunc)(void *), *krargs; /* keyrelease event */
 } gkit_widget;

/* Font Sizes */
#define STK_FONT_SIZE_6x9   "6x9"
#define STK_FONT_SIZE_7x13  "7x13"
#define STK_FONT_SIZE_9x15  "9x15"

gkit_widget *stk_widget_search(void *);
int         stk_widget_insert(void *);
int         stk_widget_delete(void *);
void        stk_init();
void        stk_run();
void        stk_widget_set_size(gkit_widget *, uint, uint);
void        stk_widget_set_pos(gkit_widget *, uint, uint);
void        stk_widget_set_color(gkit_widget *, int color);
void        stk_widget_set_font_size(gkit_widget *, char *);
gkit_widget *stk_widget_root();
void        gkit_widget_event_listen_add(gkit_widget *, int, 
                                  void (*)(void*),void *);
void        stk_widget_event_listen_remove(gkit_widget *, int);

#endif /* GKIT_WIDGET_H */
