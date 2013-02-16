#include <stk_text.h>


stk_widget *stk_text_new(stk_widget *parent_win, int x, int y, uint w, uint h,
                                                  const char *label, int type)
{
    stk_widget *new_txt  = (stk_widget*) malloc(sizeof(stk_widget));
    stk_text *txt = (stk_text*) malloc(sizeof(stk_text));
    int screen;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    new_txt->dsp = display;
    new_txt->fontname = "7x13";

    screen = DefaultScreen(new_txt->dsp);
    fg = BlackPixel(new_txt->dsp, screen);
    bg = WhitePixel(new_txt->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    new_txt->gc2 = XCreateGC(new_txt->dsp, parent_win->win, GCForeground |
                                                  GCBackground, &gcval);

    setwinattr.backing_store = Always;

    new_txt->font_info = XLoadQueryFont(new_txt->dsp, new_txt->fontname);

    if(new_txt->fontname != NULL)
        XSetFont(display, new_txt->gc2, new_txt->font_info->fid);
    else
      perror("XLoadQueryFont");

    if(new_txt->dsp)
    {
        new_txt->win = XCreateSimpleWindow(new_txt->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);

        new_txt->mask =  ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                         EnterWindowMask | LeaveWindowMask |
                         FocusChangeMask | StructureNotifyMask | PropertyChangeMask | VisibilityChangeMask;

        XChangeWindowAttributes(new_txt->dsp, new_txt->win, CWBackingStore,
                                                              &setwinattr);
        
        XSelectInput(new_txt->dsp, new_txt->win, new_txt->mask);
        XMapWindow(new_txt->dsp, new_txt->win);


        new_txt->x = x;
        new_txt->y = y;
        new_txt->w = w;
        new_txt->h = h;
        new_txt->ext = NULL;
        new_txt->handler = &stk_text_handle;
        new_txt->ext_struct = (void*)txt;

        memset(txt->text, '\0', STK_TEXT_BUFFER_SIZE);

        if(label)
            new_txt->label = label;


        stk_widget_insert((void*)new_txt); 

        return new_txt;
    }
    else
        return NULL;
}


void stk_text_append(stk_widget *txt, char c)
{
    int len = 0;

    stk_text *string = (stk_text*)txt->ext_struct;

    len = strlen(string->text);
    
    if(len == 0)
        string->text[0] = c;
    else
        string->text[len] = c;
}



void stk_text_delete(stk_widget *txt)
{
    int len = 0;
    stk_text *string = (stk_text*)txt->ext_struct;

    len = strlen(string->text);

    if(len == 0)
        return;
    else
        string->text[len - 1] = 0;
}


void stk_text_expose(stk_widget *txt, void *arg)
{
    XClearWindow(txt->dsp, txt->win);
    XFlush(txt->dsp);
}



void stk_text_keys(stk_widget *txt, XKeyEvent *event, KeySym *key)
{
    KeySym keysym = (KeySym)&key;
    char c;

    XLookupString(event, &c, sizeof(char), &keysym, NULL);

    if((keysym == XK_BackSpace) || (keysym == XK_Delete))
    {
        stk_text_delete(txt);
        stk_text_redraw(STK_TEXT_EXPOSE, txt, NULL);
    }

    if((keysym >= XK_Left) && (keysym <= XK_Down))
    {
         printf("Arrow Key:-");
         switch(keysym){
         case XK_Left: printf("Left\n"); break;
         case XK_Up: printf("Up\n"); break;
         case XK_Right: printf("Right\n"); break;
         case XK_Down: printf("Down\n"); break;
         } 
    }
    if((keysym >= XK_space) && (keysym <= XK_asciitilde))
    {
        stk_text_append(txt, c);
    }

}


char *stk_text_get_text(stk_widget *txt)
{
    stk_text *string = (stk_text*)txt->ext_struct;
    return string->text;
}


void stk_text_redraw(int dtype, stk_widget *txt, void *args)
{ 
    
    STKEvent *ev;
    stk_text *string = (stk_text*)txt->ext_struct;

    if(args)
         ev = (STKEvent*)args;

    switch(dtype)
    {
        case STK_TEXT_EXPOSE:
            stk_text_expose(txt, NULL);
            break;

        case STK_TEXT_PRESS:
            XSetInputFocus(txt->dsp, txt->win, RevertToNone, CurrentTime);
            break;

        case STK_TEXT_RELEASE:
            break;

        case STK_TEXT_KEYPRESS:
        {
            KeySym keysym;
            stk_text_expose(txt, NULL);
            stk_text_keys(txt, &ev->xkey, &keysym);
            {     
                int hcenter = (txt->font_info->descent) + (txt->h / 2);
                int sw, begin;

                if(string->text)
                {
                    sw = XTextWidth(txt->font_info, string->text, strlen(string->text));
                    if(sw > txt->w)
                        begin = txt->w - sw;
                    else
                        begin = 2;
                    
                    XDrawString(txt->dsp, txt->win, txt->gc2, begin, hcenter,
                                         string->text, strlen(string->text));
                }
            }
        }
            break;

        case STK_TEXT_KEYRELEASE:
            break;


        case STK_TEXT_ENTER:
        case STK_TEXT_LEAVE:
        default:
            break;
    }
}



void stk_text_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

    switch(event->type)
    {
        case Expose:
            stk_text_redraw(STK_TEXT_EXPOSE, wg, NULL);
            break;
        case LeaveNotify:
            break;

        case ButtonPress:
            stk_text_redraw(STK_TEXT_PRESS, wg, NULL);
            break;

        case ButtonRelease:
            stk_text_redraw(STK_TEXT_RELEASE, wg, NULL);
            break;

        case KeyPress:
            stk_text_redraw(STK_TEXT_KEYPRESS, wg, event);
            break;

        case KeyRelease:
            stk_text_redraw(STK_TEXT_KEYRELEASE, wg, NULL);
            break;
    }
}
