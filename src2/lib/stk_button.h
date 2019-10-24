#ifndef STK_BUTTON_H
#define STK_BUTTON_H

#include <gkit_widget.h>

/* STKButton Events */
#define STK_BUTTON_EXPOSE   0x10
#define STK_BUTTON_PRESS    0x20
#define STK_BUTTON_RELEASE  0x30
#define STK_BUTTON_ENTER    0x40
#define STK_BUTTON_LEAVE    0x50

gkit_widget *stk_button_new(gkit_widget *, int, int, uint, uint, char *, 
                                         void (*)(void*), void *);
void        stk_button_handle(STKEvent *, void *);

#endif /* STK_BUTTON_H */
