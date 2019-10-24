#include <stk_window.h>
#include <stk_button.h>
#include <stk_text.h>
#include <stk_progress_bar.h>
#include <stk_canvas.h>
#include <stk_menu.h>

typedef struct 
{
    void *d1;
    int c, x, y;
} ptr;


void draw(void *c)
{
    int i = 0;
    
    stk_widget *p = (stk_widget*)c;
    stk_canvas_draw_arc(p, 80, 70, 300, 100, 100, 360*64);
    stk_canvas_draw_line(p, 10, 10, 100, 100);
    stk_canvas_draw_string(p, 50, 50, "50x50");

    for(i = 350; i > 200; i--)
        stk_canvas_draw_point(p, 100+i, i-150);        
}

void listen(void *c)
{
    stk_widget *p = (stk_widget*)c;
    char coords[10] = {0};
    printf("listen: %dx%d\n", p->ev->xbutton.x, p->ev->xbutton.y);
    stk_canvas_draw_string(p, p->ev->xbutton.x, p->ev->xbutton.y, coords);
}




int main()
{
    stk_widget *myCanvas,
			   *win;


    stk_init();
    
    win = stk_window_new(500, 500, 800, 600, "test-canvas.c");

    myCanvas  = stk_canvas_new(win, 10, 10, 780, 580);
    
    stk_widget_event_listen_add(myCanvas, STK_WIDGET_MOVE, listen, (void*)myCanvas);
    stk_widget_event_listen_add(myCanvas, STK_WIDGET_PRESS, listen, (void*)myCanvas);

    stk_canvas_draw_arc(myCanvas, 50, 70, 150, 150, 10, 360*64);
    


    stk_window_show(win);

    stk_run();
    
    return 0;
}
