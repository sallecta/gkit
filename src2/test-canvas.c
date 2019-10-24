#include <gkit_window.h>
#include <gkit_widget_canvas.h>
#include <stk_button.h>
#include <stk_text.h>
#include <stk_progress_bar.h>
#include <stk_menu.h>

typedef struct 
{
    void *d1;
    int c, x, y;
} ptr;




void listen(void *argCanvas)
{
    gkit_widget *p = (gkit_widget*)argCanvas;
    char coords[10] = {0};
    printf("listen: %dx%d\n", p->ev->xbutton.x, p->ev->xbutton.y);
    gkit_widget_canvas_draw_string(p, p->ev->xbutton.x, p->ev->xbutton.y, coords);
}



void draw(gkit_widget *argCanvas)
{
    int i = 0;
    
    gkit_widget_canvas_draw_arc(argCanvas, 80, 70, 300, 100, 100, 360*64);
    gkit_widget_canvas_draw_line(argCanvas, 10, 10, 100, 100);
    gkit_widget_canvas_draw_string(argCanvas, 70, 70, "draw.gkit_widget_canvas_draw_string");

    for(i = 350; i > 200; i--)
        gkit_widget_canvas_draw_point(argCanvas, 100+i, i-150);        
}


int main()
{
    gkit_widget *myCanvas, *myWin;


    stk_init();
    
    myWin = gkit_window_new(500, 500, 800, 600, "test-canvas.c");

    myCanvas  = gkit_widget_canvas_new(myWin, 10, 10, 780, 580);
    
    gkit_widget_event_listen_add(myCanvas, STK_WIDGET_MOVE, listen, (void*)myCanvas);
    gkit_widget_event_listen_add(myCanvas, STK_WIDGET_PRESS, listen, (void*)myCanvas);

    gkit_widget_canvas_draw_arc(myCanvas, 50, 70, 150, 150, 10, 360*64);
	

	draw(myCanvas);
    


    gkit_window_show(myWin);

    stk_run();
    
    return 0;
}
