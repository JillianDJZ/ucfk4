/**
    @file   game.h
    @author Faraz Hussain fhu31 84204881, Dongjin Zhou dzh80 55179275
    @date   20th October 2021
    @brief  Main whack-a-mole header game file.

Group Number: 301

Defining the different polling rates for the pacer.
*/

#ifndef GAME_H
#define GAME_H

// ------------------------------ Constants ------------------------------

// Different Polling Rates
#define PACER_RATE 500 // Rate for pacer to go through the while loop
#define DISPLAY_TASK_RATE 250 // Display rate
#define PLAYER_MOVE_RATE 100 // Rate at which player movement function called
#define PWM_RATE 500 // PWM rate of mole LEDs
#define PLAYER_CURSOR_PWM_RATE 125 // PWM rate for flashing of player cursor


#endif // GAME_H
