/** @file   sub_game.h
    @authors Raven Townsend, Ben Remacha
    @date   12 Oct 2020
*/


#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


/**
 * Runs one sub_game of the alphabet game and returns the winner (1 if
 * this player wins, 0 if the other player wins).
 *
 * @param turn 1 it is this player's turn when the game starts, 0 otherwise.
 * @return 1 if this player won, 0 otherwise.
 */
uint8_t sub_game_run (uint8_t turn);
