#include <gkit_window.h>
#include <gkit_widget_canvas.h>
#include <stk_button.h>
#include <stk_text.h>
#include <stk_progress_bar.h>
#include <stk_menu.h>






void listen(void *arg)
{
    gkit_widget *c = (gkit_widget*)arg;
    char coords[10] = {0};
    sprintf(coords, "%dx%d", c->ev->xbutton.x, c->ev->xbutton.y);
    printf("%dx%d\n", c->ev->xbutton.x, c->ev->xbutton.y);
    gkit_widget_canvas_draw_string(c, c->ev->xbutton.x, c->ev->xbutton.y, coords);
}



void draw(void *arg)
{
    int i = 0;
    gkit_widget *c = (gkit_widget*)arg;
    gkit_widget_canvas_draw_arc(c, 80, 70, 300, 100, 100, 360*64);
    gkit_widget_canvas_draw_line(c, 10, 10, 100, 100);
    gkit_widget_canvas_draw_string(c, 70, 70, "draw.gkit_widget_canvas_draw_string");

    for(i = 350; i > 200; i--)
        gkit_widget_canvas_draw_point(c, 100+i, i-150);        
}


int main()
{
    gkit_widget *myCanvas, *myWin;


    stk_init();
    
    myWin = gkit_window_new(500, 500, 800, 600, "test-canvas.c");

    myCanvas  = gkit_widget_canvas_new(myWin, 10, 10, 780, 580);
    
    gkit_widget_event_listen_add(myCanvas, GKIT_EVENT_MOVE, listen, (void*)myCanvas);
    gkit_widget_event_listen_add(myCanvas, GKIT_EVENT_PRESS, listen, (void*)myCanvas);

    gkit_widget_canvas_draw_arc(myCanvas, 50, 70, 150, 150, 10, 360*64);
	

	draw(myCanvas);
    printf("GKIT_PLATFORM: %s\n", GKIT_PLATFORM);
	printf("GKIT_VERSION: %s\n", GKIT_VERSION);


    gkit_window_show(myWin);

    stk_run();
    
    return 0;
}
