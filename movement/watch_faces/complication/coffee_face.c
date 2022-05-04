/*
 * MIT License
 *
 * Copyright (c) 2022 Ryan Oles
 *
 * Based on Phase of Moon App for Tidbyt
 * https://github.com/tidbyt/community/blob/main/apps/phaseofmoon/phase_of_moon.star
 * Copyright (c) 2022 Alan Fleming
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "coffee_face.h"
#include "watch.h"
#include "watch_utility.h"


// Pouring Animation
static void drip_animation(brew_state *state) {
    if(state->vb_on == false) {
        watch_set_pixel(1, 14);
    }
    else {
        watch_clear_pixel(1, 14);
    }
    state->vb_on = !state->vb_on;
}

// Swirling Animation
static void swirl_animation(brew_state *state) {
  state->swirl_step[0] ? watch_set_pixel(1, 12) : watch_clear_pixel(1, 12);
  state->swirl_step[1] ? watch_set_pixel(1, 11) : watch_clear_pixel(1, 11);

  state->swirl_step[0] = !state->swirl_step[0];
  state->swirl_step[1] = !state->swirl_step[1];
}

// Drawing Down (Draining) Animation
static void draw_down_animation(brew_state *state) {
  watch_clear_pixel(0, 11);
  watch_clear_pixel(2, 12);
  watch_clear_pixel(2, 11);

  switch(state->draw_step) {
    case 0:
      watch_set_pixel(0, 11);
      break;
    case 1:
      watch_set_pixel(2, 12);
      break;
    case 2:
      watch_set_pixel(2, 11);
      break;
  }

  if (state->draw_step < 3) {
      state->draw_step++;
  }
  else {
      state->draw_step = 0;
  }
}

void coffee_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    (void) watch_face_index;
}

void coffee_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
    brew_state *state = (brew_state *)context;
    // Setup the initial state.
    state->vb_on = false;
    state->brewing = false;
    state->swirl_step[0] = true;
    state->swirl_step[1] = false;
    state->draw_step = 0;
}

bool coffee_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    (void) settings;
    movement_request_tick_frequency(2);
    brew_state *state = (brew_state *)context;
    char buf[11];

    watch_display_string("    ", 0);
    switch (event.event_type) {
        case EVENT_ACTIVATE:
            // Splash screen.
            sprintf(buf, "  BrEU");
            break;
        case EVENT_TICK:
            if(state->brewing) {
                //drip_animation(state);
                //swirl_animation(state);
                draw_down_animation(state);
            }
            sprintf(buf, "  BrEU");
            break;
        case EVENT_LOW_ENERGY_UPDATE:
            break;
        case EVENT_MODE_BUTTON_UP:
            movement_move_to_next_face();
            break;
        case EVENT_LIGHT_BUTTON_DOWN:
            movement_illuminate_led();
            break;
        case EVENT_ALARM_BUTTON_DOWN:
            // We're brewing!
            //watch_buzzer_play_note(BUZZER_NOTE_A5SHARP_B5FLAT, 100);
            state->brewing = !state->brewing;
            break;
        case EVENT_TIMEOUT:
            break;
        default:
            break;
    }

    watch_display_string(buf, 4);

    // Draw the cup.
    watch_set_pixel(2, 13);
    watch_set_pixel(2, 15);
    watch_set_pixel(2, 14);

    return true;
}

void coffee_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
}
