/** @file   whack.h
    @author Faraz Hussain fhu31, Dongjin Zhou dzh80
    @date   20th October 2021
    @brief  Logic for whack-a-mole game

This file includes the logic functions for the Whack-a-mole game. It initializes
the game, keeps track of which LEDs are on that correspond to the moles, creates 
new moles, and checks whether the mole is correctly whacked. 
*/

#ifndef WHACK_H
#define WHACK_H

#include "tinygl.h"
#include "led.h"
#include "player.h"
#include "whack.h"
#include "game.h"

#define STARTING_MOLE_RATE 6 // Rate at which moles are created

typedef enum {STATE_INIT, STATE_PLAYING, STATE_OVER, STATE_READY} state_t; // Different states for the game

// whacky_game_t is used to keep track of the current game
typedef struct {
    uint8_t mole_rate;
} whacky_game_t;

// An array of arrays for each LED position, 0 means mole is down, 1 means mole is up
uint8_t mole_up[TINYGL_WIDTH][TINYGL_HEIGHT];

/** Initializing new game */
whacky_game_t game_init (void);

/** Choosing a random mole changing its position in mole_up to 1 */
void new_mole (void);

/** Checking if the user has pressed the pushbutton above a mole that is up, else does nothing */
void mole_whacked (player_t *player, whacky_game_t *game);

/** Make renew all variables used to keep track of the game */
void new_game (player_t *player, whacky_game_t *game, uint64_t *thirty_second_timer);

#endif // WHACK_H
