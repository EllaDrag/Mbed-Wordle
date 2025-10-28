#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "globals.h"
 
// TODO: Determine X and Y Ranges


// The bottom of the screen => y=127
// Gut the landscape grow up from the bottom of the screen. It is awkward.
// Thus, we use a macro to reverse the coordinate for convenience.
#define REVERSE_Y(x) (SIZE_Y-(x))

/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_sprite();
void draw_lower_status();

 
#endif // GRAPHICS_H
