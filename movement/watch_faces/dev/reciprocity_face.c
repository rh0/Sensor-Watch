#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "reciprocity_face.h"
#include "watch_utility.h"

/*
 * setup function is called on first boot and when waking from sleep mode.
 *
 * settings: pointer to the global movement settings
 * watch_face_index: 0-indexed position of the watch face in the faces list
 * context_ptr: keep track of state (context) for the face, first run will be null
 */
void reciprocity_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    if (*context_ptr == NULL) *context_ptr = malloc(sizeof(reciprocity_state_t));
}

/*
 * activate function is called just before the face enters the foreground
 */
void reciprocity_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
}

/*
 * loop function is called repetedly when the face is on screen.
 * (much like arduino)
 */
bool reciprocity_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
    //reciprocity_state_t *reciprocity_state = (reciprocity_state_t *)context;

    switch (event.event_type) {
        case EVENT_TICK:
            watch_display_string("f4", 0);
            watch_display_string("REC", 4);

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
    (void) context;
}
