/** @file   display_messages.c
    @author Faraz Hussain fhu31, Dongjin Zhou dzh80
    @date   12th October 2021
    @brief  Logic for whack-a-mole game.
*/

#include <stdint.h>
#include <stdlib.h>

#include "tinygl.h"
#include "led.h"

#include "player.h"
#include "whack.h"


/** Initializing new game */
whacky_game_t game_init (void) 
{
    whacky_game_t game = {.mole_rate = STARTING_MOLE_RATE};
    return game;
}

/** Creating a new random mole and changing its position in mole_up to 1 */
void new_mole (void) 
{
    // Choosing two random numbers inside the mole_up table
    size_t r1 = rand() % TINYGL_WIDTH;
    size_t r2 = rand() % TINYGL_HEIGHT;

    // Turning the position of the new mole to up
    mole_up[r1][r2] = 1;
}

/** Checking if the user has pressed the pushbutton above a mole that is up, else does nothing */
void mole_whacked (player_t *player, whacky_game_t *game)
{
    static uint8_t checkpoint = 0; // Keeping track of current score, used to update game.mole_rate

    if (mole_up[player->pos.x][player->pos.y] == 1) {
        led_set (LED1, 1); // Turn LED on when mole whacked
        player->score++; 
        checkpoint++; 
        mole_up[player->pos.x][player->pos.y] = 0;
    }

    // If checkpoint value of 10 reached, update mole rate by 2 (numbers tested for good gameplay)
    if (checkpoint == 10) {
        checkpoint = 0;
        game->mole_rate += 2;
    }
}

/** Renew player, game and timer to run another game */
void new_game (player_t *player, whacky_game_t *game, uint64_t *thirty_second_timer)
{
    // Reinitialize game, player, and timer
    *game = game_init ();
    *player = player_init ();
    *thirty_second_timer = PACER_RATE * 6;

    // Make sure all moles are down
    for (uint8_t x = 0; x < TINYGL_WIDTH; x++) {
        for (uint8_t y = 0; y < TINYGL_HEIGHT; y++) {
            mole_up[x][y] = 0;
        }
    }     
}
