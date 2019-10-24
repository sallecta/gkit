#include <gkit_window.h>

gkit_widget *gkit_window_new(int x, int y, uint w, uint h, const char *title)
{
    gkit_widget *new_win  = (gkit_widget*) malloc(sizeof(gkit_widget));
    Atom del_win;
    
    memset(new_win, 0, sizeof(gkit_widget));
    
    new_win->dsp = display;

    if(new_win->dsp)
    {
        new_win->win = XCreateWindow(new_win->dsp, DefaultRootWindow(new_win->dsp),
                                   x, y, w, h, 0, CopyFromParent, CopyFromParent,
                                                           CopyFromParent, 0, 0);
        
        new_win->mask = ExposureMask | ButtonPressMask | ButtonReleaseMask |
                    PointerMotionMask | KeyPressMask | StructureNotifyMask;
                    
        XSelectInput(new_win->dsp, new_win->win, new_win->mask);
        XSetWindowBackground(new_win->dsp, new_win->win, 0xd3d3d3);
        del_win = XInternAtom(new_win->dsp, "WM_DELETE_WINDOW", 0);
        XSetWMProtocols(new_win->dsp, new_win->win, &del_win, 1);
        
      
      
              
        new_win->x = x;
        new_win->y = y;
        new_win->w = w;
        new_win->h = h;


        new_win->handler = &gkit_window_handle;

        if(title)
            gkit_window_set_title(new_win, title);

        new_win->gc = XCreateGC(display, new_win->win, 0, 0);

        stk_widget_insert((void*)new_win); 

        return new_win;
    }
    else
      return NULL;
}


void gkit_window_set_pos(gkit_widget *win, uint x, uint y)
{
  stk_widget_set_pos(win, x, y);
}    

void gkit_window_set_color(gkit_widget *win, int color)
{
    stk_widget_set_color(win, color);
}

void gkit_window_handle(STKEvent *event, void *warg)
{
  gkit_widget *wg = (gkit_widget*)warg;
  gkit_widget *wroot = stk_widget_root();

  switch(event->type)
  {
      case Expose:
          break;
      
      case ButtonPress:
          XSetInputFocus(wg->dsp, wg->win, RevertToNone, CurrentTime);
          break;
      
      case ButtonRelease:
         /*if(wg->func)
             wg->func(wg->args);*/
          break;

      case ClientMessage:
          if(wg == wroot)
          {
              XDestroyWindow(wg->dsp, wg->win);
              /* close connection to server */
              XCloseDisplay(wg->dsp);
              exit(0);
          }
          else
          {
              XUnmapWindow(wg->dsp, wg->win);
              XFlush(wg->dsp);
          }

          break;
  }
}

void gkit_window_show(gkit_widget *win)
{
    XMapWindow(win->dsp, win->win);
    XFlush(win->dsp);
}


void gkit_window_set_title(gkit_widget *win, const char *title)
{
    /* This variable will store the newly created property. */
    XTextProperty window_title_property;

    /* translate the given string into an X property. */
    XStringListToTextProperty((char**)&title,
                                       1,
                                       &window_title_property);
    XSetWMName(win->dsp, win->win, &window_title_property);
}
