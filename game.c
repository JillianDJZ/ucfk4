/**
    @file   game.c
    @author Faraz Hussain fhu31 84204881, Dongjin Zhou dzh80 55179275
    @date   20th October 2021
    @brief  Main whack-a-mole game file.

Group Number: 301

We are going to implement a game similar to the classic Whack-A-Mole.
*/

// ------------------------------ Header Files ------------------------------

// Standard header files
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Useful Drivers:
#include "system.h" // UCFK system initialisation
#include "button.h" // button support
#include "navswitch.h" // Navswitch support
#include "led.h" // Using the LED on the funkit

// Useful utilities:
#include "pacer.h" // Paced loop support
#include "tinygl.h" // Tiny graphics library.

// Our files:
#include "game.h"
#include "player.h"
#include "whack.h"
#include "display_messages.h"


int main (void) 
{
    // Initializing different systems
    system_init ();
    button_init ();
    navswitch_init ();
    led_init ();
    led_set (LED1, 0);

    pacer_init (PACER_RATE);
    tinygl_init (DISPLAY_TASK_RATE);    
    // srand (timer_get ()); 

    // Creating pacer tickers for different functions
    uint16_t player_move_ticker = 0;
    uint16_t mole_ticker = 0;
    uint16_t pwm_tick = 0;
    uint16_t cursor_flash_ticker = 0;
    uint64_t thirty_second_timer;
  
    // Creating player and game objects to keep track of different variables
    player_t player;
    whacky_game_t game;
    state_t state = STATE_INIT;

    while (1) {

        /* Refresh display and update modules.  */
        for (uint8_t col = 0; col < TINYGL_WIDTH; col++) {
            pacer_wait ();
            tinygl_update ();
        }

        button_update ();
        navswitch_update ();   

        switch (state) {

            case STATE_INIT:

                state = STATE_READY; // If everthing initialized then go to next state

                break;

            case STATE_READY:

                // Initializing game
                new_game (&player, &game, &thirty_second_timer);

                // Display welcome message and update state to start playing when navswitch pressed down
                messages_task (&state, &player);

                break;

            case STATE_PLAYING:

                // Turn LED off 
                led_set (LED1, 0);

                // Make a new mole at game.mole_rate
                mole_ticker++;
                if (mole_ticker > PACER_RATE / game.mole_rate) {
                    mole_ticker = 0;
                    new_mole ();
                }

                // PWM for mole pixels to decrease brigtness, and to flash player cursor
                pwm_task (&pwm_tick, &cursor_flash_ticker, &player);

                pwm_tick++;
                if (pwm_tick > PACER_RATE / PWM_RATE) {
                    pwm_tick = 0;          
                }

                cursor_flash_ticker++;
                if (cursor_flash_ticker > PACER_RATE / PLAYER_CURSOR_PWM_RATE) {
                    cursor_flash_ticker = 0;
                }

                // Rate to check when player moves
                player_move_ticker++;
                if (player_move_ticker > PACER_RATE / PLAYER_MOVE_RATE) {
                    player_task (&player);
                }

                // When push button pressed, check if mole is hit and update score
                if (button_push_event_p (0)) {
                    mole_whacked (&player, &game);
                }

                // Timing down thirty seconds to end game
                thirty_second_timer--;
                if (thirty_second_timer == 0) {
                    state = STATE_OVER;
                }

                break;

            case STATE_OVER:

                // Display final score and check navswitch down press for restart
                messages_task (&state, &player);
                
                break;

        } 

    }

    return 0;
}
