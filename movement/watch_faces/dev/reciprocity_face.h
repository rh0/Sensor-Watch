/*
 * reciprocity_face.h
 *
 * Header file for the reciprocity failure timer/calculator face.
 */

#ifndef RECIPROCITY_FACE_H_
#define RECIPROCITY_FACE_H_

#include "movement.h"

typedef struct {
    bool counting;
} reciprocity_state_t;

void reciprocity_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr);
void reciprocity_face_activate(movement_settings_t *settings, void *context);
bool reciprocity_face_loop(movement_event_t event, movement_settings_t *settings, void *context);
void reciprocity_face_resign(movement_settings_t *settings, void *context);

#define reciprocity_face ((const watch_face_t){ \
    reciprocity_face_setup, \
    reciprocity_face_activate, \
    reciprocity_face_loop, \
    reciprocity_face_resign, \
    NULL, \
})

#endif // MOON_PHASE_FACE_H_

