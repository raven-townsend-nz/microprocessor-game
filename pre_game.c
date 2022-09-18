/** @file   pre_game.c
    @authors Raven Townsend, Ben Remacha
    @date   10 Oct 2020
*/

#include "button.h"
#include "tinygl.h"
#include "pacer.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define PLAYER_READY 1


/**
 * Displays a start message until both player press button 1 to
 * indicate they are ready.
 *
 * @return 1 if this funkit was the first to be ready, 0 otherwise.
 */
uint8_t pre_game_run (void)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text ("PRESS BUTTON1");
    button_init ();
    pacer_init (PACER_RATE);

    uint8_t this_player_ready = 0;
    uint8_t other_player_ready = 0;

    uint8_t my_turn;

    while (!other_player_ready || !this_player_ready) {

        pacer_wait ();
        tinygl_update ();
        button_update ();


        if (button_push_event_p (BUTTON1) && !other_player_ready) {
            this_player_ready = PLAYER_READY;
            tinygl_text ("READY");
            ir_uart_putc (PLAYER_READY);
            my_turn = 1;
        }

        if (ir_uart_read_ready_p () && (ir_uart_getc () == PLAYER_READY)) {
            other_player_ready = PLAYER_READY;
        }

        if (button_push_event_p (BUTTON1) && other_player_ready) {
            this_player_ready = PLAYER_READY;
            ir_uart_putc (PLAYER_READY);
            my_turn = 0;
        }
    }

    return my_turn;
}
