/*!

*/
#include <gkit_widget.h>

widget_list *list;

/*!
@brief 
Initialize the Display connection to X and the widget list

Must be called before any STK functions
*/
void stk_init()
{
    list = NULL;
    display =  XOpenDisplay(0);
}


/**
@brief Alloc and insert a widget in the widget list.
@param widget The pointer to the widget to be inserted on the list
@return 0 if success or -1 if unsuccessful.
@discussion Every widget must call it to be
registered and have its events
handled
*/
int stk_widget_insert(void *widget)
{
    widget_list *new_widget = (widget_list *)malloc(sizeof(widget_list));
    
    if(new_widget)
    {
        new_widget->this = widget;
        new_widget->prev = NULL;
        new_widget->next = list;

        if(list != NULL)
            list->prev = new_widget;

        list = new_widget;

        return 0;
    }
    return -1;
}


int stk_widget_delete(void *widget)
{
    return 0;
}


/*!
@brief Searchs for a widget in the widget list.
@param widget The widget to be located on the list.
@return Returns a pointer to gkit_widget or NULL
*/
gkit_widget *stk_widget_search(void *widget)
{
    widget_list *node = list;
    gkit_widget *wnode = NULL;


    if(node ==  NULL)
        printf("Empty widget list\n");
    else
    {
        while(node)
        {
            wnode = (gkit_widget*)node->this;
            if(wnode->win == (Window)widget)
                return wnode;
            else
                node = node->next;
        }
    }

    printf("Widget %p not found :(\n", widget);
    return NULL;
}


/*!
@brief Search for a widget in the widget list.
@return Must be called after all STK functions.
It's the event loop that handles the all
the event callings of the widgets.
*/
void stk_run()
{
    GKITEvent event;
    widget_list *node = list;
    gkit_widget *wnode = NULL;

    if(node ==  NULL)
        printf("Empty list\n");
    else
    {       
        while(1)
        {
            XNextEvent(display, &event);
            wnode = stk_widget_search((void*)event.xany.window);

            if(wnode != NULL)
                wnode->handler(&event, wnode);
        }
    }
}



void gkit_widget_event_listen_add(gkit_widget *win, int event_type,
                                 void (*func)(void*), void *args)
{
    switch(event_type)
    {
        case GKIT_EVENT_MOVE:
            win->movefunc = func;
            win->margs = args;
            break;
            
        case GKIT_EVENT_PRESS:
            win->pressfunc = func;
            win->pargs = args;
            break;
            
        case GKIT_EVENT_EXPOSE:
            win->exposefunc = func;
            win->exargs = args;
            break;
            
        case GKIT_EVENT_LEAVE:
            win->leavefunc = func;
            win->largs = args;
            break;
            
        case GKIT_EVENT_ENTER:
            win->enterfunc = func;
            win->eargs = args;
            break;
            
        case GKIT_EVENT_RELEASE:
            win->releasefunc = func;
            win->rargs = args;
            break;
    }
}



void stk_widget_event_listen_remove(gkit_widget *win, int event_type)
{
    switch(event_type)
    {
        case GKIT_EVENT_MOVE:
            win->movefunc = NULL;
            win->margs = NULL;
            break;
            
        case GKIT_EVENT_PRESS:
            win->pressfunc = NULL;
            win->pargs = NULL;
            break;
            
        case GKIT_EVENT_EXPOSE:
            win->exposefunc = NULL;
            win->exargs = NULL;
            break;
            
        case GKIT_EVENT_LEAVE:
            win->leavefunc = NULL;
            win->largs = NULL;
            break;
            
        case GKIT_EVENT_ENTER:
            win->enterfunc = NULL;
            win->eargs = NULL;
            break;
            
        case GKIT_EVENT_RELEASE:
            win->releasefunc = NULL;
            win->rargs = NULL;
            break;
    }
}

void stk_widget_set_size(gkit_widget *win, uint w, uint h)
{
    XResizeWindow(win->dsp, win->win, w, h);
}

/*! 
@brief returns the first widget created
@return The pointer to the first widget added on the list
*/
gkit_widget *stk_widget_root()
{
    widget_list *node = list;
    gkit_widget *wnode = NULL;

    while(node)
    {

        wnode = (gkit_widget*)node->this;
        node = node->next;
    }
    return wnode;
}

/*! 
@brief set widget position on the screen
*/
void stk_widget_set_pos(gkit_widget *win, uint x, uint y)
{
    XMoveWindow(win->dsp, win->win, x, y);   
}

/*! 
@brief set widget color
*/
void stk_widget_set_color(gkit_widget *win, int color)
{
    XSetWindowBackground(win->dsp, win->win, color);
    XClearWindow(win->dsp, win->win);
    XFlush(win->dsp);
}


void stk_widget_set_font_size(gkit_widget *win, char *str_size)
{
    win->font_info = XLoadQueryFont(win->dsp, str_size);

    if(win->fontname != NULL)
        XSetFont(win->dsp, win->gc2, win->font_info->fid);
    else
        perror("XLoadQueryFont");
}


