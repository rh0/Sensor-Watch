#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reciprocity_face.h"
#include "watch_utility.h"

const char RECIPROCITY_WELCOME[] = "RECIPROCITy ";

/*
 * setup function is called on first boot and when waking from sleep mode.
 *
 * settings: pointer to the global movement settings
 * watch_face_index: 0-indexed position of the watch face in the faces list
 * context_ptr: keep track of state (context) for the face, first run will be null
 */
void reciprocity_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    (void) watch_face_index;

    // set aside some memory to store our state context
    if (*context_ptr == NULL) {
        *context_ptr = malloc(sizeof(reciprocity_state_t));
    }
}

/*
 * activate function is called just before the face enters the foreground
 */
void reciprocity_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;

    reciprocity_state_t *state = (reciprocity_state_t *)context;

    state->char_index = 0;
    state->animating = true;
}

/*
 * loop function is called repetedly when the face is on screen.
 * (much like arduino)
 */
bool reciprocity_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    (void) settings;
    reciprocity_state_t *state = (reciprocity_state_t *)context;


    switch (event.event_type) {
        case EVENT_ACTIVATE: 
        case EVENT_TICK:

            if (state->animating) {
                size_t msg = sizeof(RECIPROCITY_WELCOME);
                char buf[10];
                char msgSlice[5] = "";

                //sprintf(buf, "%lu", sizeof(RECIPROCITY_WELCOME));
                //watch_display_string(buf, 2);
                //watch_display_string("REC", 4);

                strncpy(msgSlice, RECIPROCITY_WELCOME + state->char_index, state->char_index + 4);
                watch_display_string(msgSlice, 4);
                watch_display_string("  ", 8);


                sprintf(buf, "%d", state->char_index);
                watch_display_string(buf, 3);
                if (state->char_index < sizeof(RECIPROCITY_WELCOME)-5) {
                    state->char_index += 4;
                }
                else {
                    state->char_index = 0;
                }

            }

        default:
            movement_default_loop_handler(event, settings);
    }

    return true;
}

/*
 * resign function is called before the face goes off screen
 * disable any periferals enables in the activate function
 */
void reciprocity_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
}
