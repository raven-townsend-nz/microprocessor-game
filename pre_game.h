/** @file   pre_game.h
    @authors Raven Townsend, Ben Remacha
    @date   10 Oct 2020
*/

#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"


/**
 * Displays a start message until both player press button 1 to
 * indicate they are ready.
 *
 * @return 1 if this funkit was the first to be ready, 0 otherwise.
 */
uint8_t pre_game_run (void);
