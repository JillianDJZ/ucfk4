/** @file   display_messages.c
    @author Faraz Hussain fhu31, Dongjin Zhou dzh80
    @date   20th October 2021
    @brief  Displaying game info and scores to the player. 
*/

#include <stdint.h>
#include <stdbool.h>

#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "pacer.h"
#include "uint8toa.h"

#include "display_messages.h"
#include "player.h"
#include "whack.h"


/** display text */
static bool display_text (char* text)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text(text);
    pacer_init (PACER_RATE);
    bool pressed = false; // Used to check when navswitch pressed down

    do {

        pacer_wait();
        tinygl_update();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            pressed = true;
        }

    } while (pressed == false); // End loop when navswitch pushed down

    tinygl_clear(); // Clearing display for pushbutton pressed

    return pressed;
}

/** Display welcome message */
static bool display_welcome (void)
{
    bool pressed = false;
    pressed = display_text("Whack-A-Mole!");
    return pressed;
}


/** Display final score to user */
static bool display_time_out(uint8_t score)
{
    bool pressed = false;
    char string[] = "    ";
    uint8toa (score, string, 0);
    pressed = display_text(string);

    return pressed;
}

/** Updating the message on the LED depending on the current state */ 
void messages_task (state_t *current_state, player_t *player)
{
    bool change_state = false;

    switch (*current_state) {

        case STATE_READY:

            // Display Welcome Message "Whack-a-mole"
            change_state = display_welcome ();

            // If navswitch pressed, change the current state of the game
            if (change_state == true) {
                *current_state = STATE_PLAYING;
                tinygl_clear (); // Clear the display to start the game
            }

            break;

        case STATE_OVER:

            // Display final score and wait for navswitch press down to restart
            change_state = display_time_out (player->score);

            // If navswitch pressed down, change the state to ready to reset game            
            if (change_state == true) {
                *current_state = STATE_READY;
            }

            break;
        
        default:
            break;
    }
}

/** Modulating the moles and player cursor to not be too bright, and for the 
    player cursor to flash */
void pwm_task (uint16_t *pwm_tick, uint16_t *cursor_flash_ticker, player_t *player)
{
    /* Pulse width modulate for mole pixels to control luminance.  */
    for (uint8_t x = 0; x < TINYGL_WIDTH; x++) {
        for (uint8_t y = 0; y < TINYGL_HEIGHT; y++) {
            tinygl_draw_point (tinygl_point (x, y), mole_up[x][y] > *pwm_tick);
        }
    }

    // Flash player cursor depending on the cursor_flash_ticker
    tinygl_draw_point (player->pos, 1 > *cursor_flash_ticker);
}
