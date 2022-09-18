/** @file   sub_game.c
    @authors Raven Townsend, Ben Remacha
    @date   12 Oct 2020
*/


#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


static char character;
static uint8_t location_counter;
static uint8_t winner;
static uint8_t my_turn;


/**
 * Checks for navswitch inputs and updates the character accordingly.
 */
static void sub_game_update_char (void)
{
    navswitch_update ();

    if (navswitch_push_event_p (NAVSWITCH_NORTH)
            && location_counter < 4 && character < 'Z') {
        location_counter++;
        character++;
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)
            && location_counter > 1 && character > 'A') {
        location_counter--;
        character--;
    }
}


/**
 * Checks for navswitch push and sends character if requested.
 */
static void sub_game_send_char (void)
{
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {

        ir_uart_putc (character);
        my_turn = 0;

        if (character == 'Z') {
            winner = 1;
        }
    }
}


/**
 * Checks for (valid) characters received from the other funkit.
 */
static void sub_game_receive_char (void)
{
    if (ir_uart_read_ready_p ()) {

        char ch = ir_uart_getc ();

        if (ch >= 'A' && ch < 'Z') {
            location_counter = 0;
            character = ch;
            my_turn = 1;
        }

        if (ch == 'Z') {
            winner = 0;
        }
    }
}


/**
 * Displays the given character with tinygl.
 *
 * @param character the character to display.
 */
static void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


/**
 * Runs one sub_game of the alphabet game and returns the winner (1 if
 * this player wins, 0 if the other player wins).
 *
 * @param turn 1 it is this player's turn when the game starts, 0 otherwise.
 * @return 1 if this player won, 0 otherwise.
 */
uint8_t sub_game_run (uint8_t turn)
{
    character = 'A';
    location_counter = 0;
    winner = 2;
    my_turn = turn;

    pacer_init (PACER_RATE);

    while (winner != 0 && winner != 1) {

        tinygl_update ();
        if (my_turn == 1) {
            sub_game_update_char ();
            sub_game_send_char ();
        }
        sub_game_receive_char ();
        display_character (character);
        pacer_wait ();
    }

    tinygl_clear ();
    tinygl_update ();

    return winner;
}
