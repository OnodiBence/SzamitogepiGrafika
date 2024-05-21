#ifndef SCENE_H
#define SCENE_H

#include "utils.h"
#include <obj/model.h>
#include "texture.h"
#include <stdlib.h>



typedef struct blocks{
	vec3 position;
	int id;
	int is_active;
	double move;
}Blocks;

typedef struct Scene
{
	Blocks* blocks;
	Model* model;
	GLuint* texture;
	GLuint helpmenu;
	Material material;
	int block_counter;
	float light;
	double block_size;
	double player_speed;
	double gravity;
	double player_velocity;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(Scene* scene);


/**
 * Read the map layout from map.txt.
 */
void read_map(Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);
/**
 * Update the scene.
 */
void update_scene(Scene* scene,double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(Scene* scene);

#endif /* SCENE_H */
