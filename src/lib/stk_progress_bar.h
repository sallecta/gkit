#ifndef STK_PROGRESS_BAR_H
#define STK_PROGRESS_BAR_H

#include <gkit_widget.h>

/* STKButton Events */
#define STK_PROGRESS_BAR_EXPOSE   0x10
#define STK_PROGRESS_BAR_PRESS    0x20
#define STK_PROGRESS_BAR_RELEASE  0x30
#define STK_PROGRESS_BAR_ENTER    0x40
#define STK_PROGRESS_BAR_LEAVE    0x50

#define STK_PROGRESS_BAR_LABEL_SIZE (1 << 6)


typedef struct
{
    Colormap cmap;
    XColor color, colorrgb;
    uint pct;
    char label[STK_PROGRESS_BAR_LABEL_SIZE];
} stk_progress_bar;


gkit_widget *stk_progress_bar_new(gkit_widget *, int, int, uint, uint, char *);
void        stk_progress_bar_handle(GKITEvent *, void *);
void        stk_progress_bar_set(gkit_widget *, uint);
void        stk_progress_bar_set_value(gkit_widget *, uint);
void        stk_progress_bar_set_label(gkit_widget *, char *);
uint        stk_progress_bar_get_value(gkit_widget *);

#endif /* STK_PROGRESS_BAR_H */
