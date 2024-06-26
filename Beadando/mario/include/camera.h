#ifndef CAMERA_H
#define CAMERA_H
#include "scene.h"
#include "utils.h"

#include <stdbool.h>

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Camera;

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */
int update_camera(Camera* camera, double time,Scene* scene);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera* camera, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_camera_side_speed(Camera* camera, double speed);

void show_texture_preview();

#endif /* CAMERA_H */
