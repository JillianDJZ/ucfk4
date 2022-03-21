/** @file   display_messages.h
    @author Faraz Hussain fhu31, Dongjin Zhou dzh80
    @date   20th October 2021
    @brief  Displaying game info and scores to the player. 

This file utilises the tinygl.h module to display information to the user about
the game. It includes the welcome message and the final score. */

#ifndef DISPLAY_MESSAGES_H
#define DISPLAY_MESSAGES_H

#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "tinygl.h"
#include "pacer.h"
#include "uint8toa.h"

#include "game.h"
#include "player.h"
#include "whack.h"


#define MESSAGE_RATE 15

/** Updating the message on the LED depending on the current state */ 
void messages_task (state_t *current_state, player_t *player);

/** Modulating the moles and player cursor to not be too bright, and for the 
    player cursor to flash */
void pwm_task (uint16_t *pwm_tick, uint16_t *cursor_flash_ticker, player_t *player);


#endif // DISPLAY_MESSAGES_H
