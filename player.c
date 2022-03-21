/** @file   player.c
    @author Faraz Hussain fhu31, Dongjin Zhou dzh80
    @date   20th October 2021
    @brief  Definitions for player cursor and score. 
*/

#include <stdint.h>
#include "tinygl.h"
#include "navswitch.h"
#include "player.h"
#include "game.h"

/** Making a new player to keep track of a new round */
player_t player_init (void) 
{
    player_t player;

    // Setting the player to start from the middle of the LED display
    player.pos.x = TINYGL_WIDTH / 2;
    player.pos.y = TINYGL_HEIGHT / 2;
    player.score = 0; // Setting the score to 0

    return player;
}

/** Updating the position of the player */
static void player_move (player_t *player, int dx, int dy) 
{
    // Turning the old position of the player off
    tinygl_draw_point (player->pos, 0);

    // Updating the position of the player
    player->pos.x += dx;
    player->pos.y += dy;

    // Capping the position so it goes around the edges
    if (player->pos.y >= TINYGL_HEIGHT) {player->pos.y = 0;}
    if (player->pos.y < 0) {player->pos.y = TINYGL_HEIGHT - 1;}
    if (player->pos.x >= TINYGL_WIDTH) {player->pos.x = 0;}
    if (player->pos.x < 0) {player->pos.x = TINYGL_WIDTH - 1;}
}

/** Player task called depending on the rate to move the player */
void player_task (player_t *player) 
{
    // Move player up
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        player_move (player, 0, -1);
    } 

    // Move player down
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        player_move (player, 0, 1);
    } 

    // Move player right
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        player_move (player, 1, 0);
    } 

    // Move player left
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        player_move (player, -1, 0);
    } 
}
