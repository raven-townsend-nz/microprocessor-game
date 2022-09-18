/** @file   game.c
    @authors Raven Townsend, Ben Remacha
    @date   5 Oct 2020
*/


#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pre_game.h"
#include "sub_game.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define SCORE_RATE 1
#define DEC_TO_CHAR 48


static uint8_t my_score = 0;
static uint8_t their_score = 0;


/**
 * Initializes the modules required for the game.
 */
void game_init (void)
{
    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    navswitch_init ();
    ir_uart_init();
    pacer_init (PACER_RATE);
}


/**
 * Displays the current game score.
 */
static void game_score (void)
{
    uint16_t period = 1500;
    uint16_t counter = 0;

    char score = my_score + DEC_TO_CHAR;
    char buffer[2];
    buffer[0] = score;
    buffer[1] = '\0';
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_text (buffer);

    while (counter < period) {
        pacer_wait ();
        counter++;
        tinygl_update ();
    }

    tinygl_clear ();
    tinygl_update ();
}


/**
 * Displays message of who won and lost the game, decided by who
 * gets to 3 points first.
 */
void display_winner (void)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    if (my_score == 3) {
        tinygl_text("YOU WIN");
    }

    else if (their_score == 3) {
        tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
        tinygl_text("YOU LOSE");
    }

    while (1) {
        pacer_wait();
        tinygl_update();
    }
}


/**
 * Loops through a single round of the game until one player reaches a
 * score of 3.
 *
 * @return zero if the program ran correctly.
 */
int main (void)
{
    game_init ();
    uint8_t my_turn = pre_game_run();
    tinygl_clear();

    while (their_score < 3 && my_score < 3) {

        int8_t result = sub_game_run (my_turn);

        if (result == 1) {
            my_score++;
            my_turn = 0;

        } else if (result == 0) {
            their_score++;
            my_turn = 1;
        }

        game_score ();
    }

    display_winner ();

    return 0;
}
