#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10

int main (void)
{
    system_init();

   
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

   
    tinygl_text("123456789");
    
    pacer_init (PACER_RATE);

    uint16_t num = 0;

    while(num <= PACER_RATE * 6)
    {
        pacer_wait();
        
    
        tinygl_update();

        num ++;
        
    }
    return 0;
}