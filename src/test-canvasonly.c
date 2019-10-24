#include "stk_window.h"
#include "stk_canvas.h"

typedef struct 
{
    void *d1;
    int c, x, y;
} ptr;



void listen2(void *c)
{
    stk_widget *p = (stk_widget*)c;
    char coords[10] = {0};
    sprintf(coords, "%dx%d", p->ev->xbutton.x, p->ev->xbutton.y);
    printf("%dx%d\n", p->ev->xbutton.x, p->ev->xbutton.y);
    stk_canvas_draw_string(p, p->ev->xbutton.x, p->ev->xbutton.y, coords);
}




int main()
{
    stk_widget *cv, *win;

    stk_init();
    
    win = stk_window_new(500, 500, 800, 600, "STK Demo");
    cv  = stk_canvas_new(win, 80, 230, 700, 350);
    
    stk_widget_event_listen_add(cv, STK_WIDGET_MOVE, listen2, (void*)cv);
    stk_widget_event_listen_add(cv, STK_WIDGET_PRESS, listen2, (void*)cv);

    stk_canvas_draw_arc(cv, 50, 70, 150, 150, 10, 360*64);
    

    stk_window_show(win);

    stk_run();
    
    return 0;
}
