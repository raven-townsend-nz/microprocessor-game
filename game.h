/** @file   game.h
    @authors Raven Townsend, Ben Remacha
    @date   5 Oct 2020
*/


#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pre_game.h"
#include "sub_game.h"


/**
 * Initializes the modules required for the game.
 */
void game_init (void);


/**
 * Displays the current game score.
 */
static void game_score (void);


/**
 * Displays message of who won and lost the game, decided by who
 * gets to 3 points first.
 */
void display_winner (void);


/**
 * Loops through a single round of the game until one player reaches a
 * score of 3.
 *
 * @return zero if the program ran correctly.
 */
int main (void);
