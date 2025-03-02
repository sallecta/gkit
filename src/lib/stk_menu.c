#include <stk_menu.h>
#include <stk_button.h>


gkit_widget *stk_menu_new(gkit_widget *parent_win, int x, int y, uint w, uint h,
                                                                  char *title)
{
    gkit_widget *new_menu  = (gkit_widget*) malloc(sizeof(gkit_widget));
    
    memset(new_menu, 0, sizeof(gkit_widget));
    
    new_menu->dsp = display;

    if(new_menu->dsp)
    {
        new_menu->win = XCreateSimpleWindow(new_menu->dsp, parent_win->win,
                                                x, y, w, h, 1, 0, 0);
        
        new_menu->mask = ExposureMask | ButtonPressMask | ButtonReleaseMask |
                     PointerMotionMask | KeyPressMask | StructureNotifyMask |
                                           EnterWindowMask | LeaveWindowMask;
                
        XSelectInput(new_menu->dsp, new_menu->win, new_menu->mask);
        XSetWindowBackground(new_menu->dsp, new_menu->win, 0xd3d3d3);
        stk_menu_show(new_menu);
        
        new_menu->handler = &stk_menu_handle;
        
        new_menu->x = x;
        new_menu->y = y;
        new_menu->w = w;
        new_menu->h = h;
        
        
        
        new_menu->gc = XCreateGC(display, new_menu->win, 0, 0);
        
        stk_widget_insert((void*)new_menu); 
        
        return new_menu;
    }
    else
      return NULL;
}

/*
void stk_menu_set_pos(gkit_widget *menu, uint x, uint y)
{
  stk_widget_set_pos(win, x, y);
}    

void stk_menu_set_color(gkit_widget *menu, int color)
{
    stk_widget_set_color(win, color);
}
*/

void stk_menu_handle(GKITEvent *event, void *warg)
{
    gkit_widget *wg = (gkit_widget*)warg;

    switch(event->type)
    {
        case Expose:
            break;
      
        case ButtonPress:
            XResizeWindow(wg->dsp, wg->win, wg->w, wg->h+100);
            break;
      
        case ButtonRelease:
            break;

          case EnterNotify:
              break;
        
          case LeaveNotify:
              XResizeWindow(wg->dsp, wg->win, wg->w, 20);
              break;
    }
}

void stk_menu_show(gkit_widget *menu)
{
    XMapWindow(menu->dsp, menu->win);
    XFlush(menu->dsp);
}

