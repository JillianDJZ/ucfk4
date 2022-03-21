/** @file   player.h
    @author Faraz Hussain fhu31, Dongjin Zhou dzh80
    @date   20th October 2021
    @brief  Definitions for player cursor and score. 

This file includes the definition for player cursor functions. It keeps track  
of the players score and their current position.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "tinygl.h"
#include "navswitch.h"
#include "game.h"

/** Player_t object keeps track of the players position and their score throughout the game */
typedef struct {
    tinygl_point_t pos;
    uint8_t score;
} player_t;

/** Making a new player to keep track of a new round */
player_t player_init (void);

/** Player task called depending on the rate to move the player */
void player_task (player_t *player);

#endif // PLAYER_H
