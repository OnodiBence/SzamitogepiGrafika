#include "scene.h"
#include <GL/gl.h>
#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <math.h>

void init_scene(Scene* scene)
{
	scene->model=(Model*)malloc(3*sizeof(Model));
	scene->texture=(GLuint*)malloc(3*sizeof(GLuint));
	read_map(scene);
	load_model(&(scene->model[0]), "assets/models/cube.obj");
	scene->texture[0] = load_texture("assets/textures/cube.png");
	load_model(&(scene->model[1]), "assets/models/cube.obj");
	scene->texture[1] = load_texture("assets/textures/shroom.png");
	load_model(&(scene->model[2]), "assets/models/cube.obj");
	scene->texture[2] = load_texture("assets/textures/flag.png");
	scene->helpmenu= load_texture("assets/textures/help.png");
	scene->block_size=1.0f;
	scene->light=0.8f;
	scene->gravity=0.35f;
	scene->player_velocity=0.0f;
	scene->player_speed=6.0f;
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}



void read_map(Scene* scene){
	FILE* fp;
	fp=fopen("assets/map.txt","r");
	int id,x,y,counter=0,i=0;
	size_t bufsize=128;
	char buffer[bufsize];
	char *b=buffer;
	ssize_t read;
	
	while(read=getline(&b,&bufsize,fp)!=-1){
		counter++;
	}
	scene->block_counter=counter;
	fclose(fp);
	fp=fopen("assets/map.txt","r");
	scene->blocks=(Blocks*)malloc(counter*sizeof(Blocks));
	while(fscanf(fp,"%d %d %d",&id,&x,&y)==3){
		scene->blocks[i].id=id;
		scene->blocks[i].position.z=x;
		scene->blocks[i].position.y=y;
		scene->blocks[i].position.x=0.0;
		scene->blocks[i].is_active=1;
		scene->blocks[i].move=0.0;
		if(scene->blocks[i].id==2){
			scene->blocks[i].move=1.0;
		}
		i++;
	}
	fclose(fp);
}



void set_lighting(Scene* scene)
{
    // Ambiens fény beállítása - világos szürke
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    // Diffúz fény beállítása - sárgás szín
    float diffuse_light[] = { 1.0f, 0.8f, 0.2f, 1.0f };

    // Spekuláris fény beállítása - élénk kék
    float specular_light[] = { 1.0f, 0.2f, 0.2f, 1.0f };

    // Fényforrás pozíciója - a nézőpontból felfelé
    float position[] = { 0.0f, 0.0f, 1.0f, 0.0f };

    // Fények beállítása
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}


void update_scene(Scene* scene,double elapsed_time)
{
	for(int i=0;i<scene->block_counter;i++){
		if(scene->blocks[i].id!=2) continue;
		if(scene->blocks[i].is_active==0) continue;
		for(int k=0;k<scene->block_counter;k++){
			if(k!=i){
				if(elapsed_time<0){
					continue;
				}
				scene->blocks[i].position.y -=0.04f*scene->blocks[i].move*elapsed_time;
				if(fabs(scene->blocks[i].position.y-scene->blocks[k].position.y)<scene->block_size&&fabs(scene->blocks[i].position.z-scene->blocks[k].position.z)<scene->block_size){
					scene->blocks[i].position.y+=(0.04f * elapsed_time*scene->blocks[i].move);
					scene->blocks[i].move*=-1;
				}
			}
		}
	}
}

void render_scene(Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
	for(int i=0;i<scene->block_counter;i++){
		if(scene->blocks[i].is_active!=1){
			continue;
		}
		glBindTexture(GL_TEXTURE_2D, scene->texture[scene->blocks[i].id-1]);
		glTranslatef(scene->blocks[i].position.x,scene->blocks[i].position.y,scene->blocks[i].position.z);
		draw_model(&(scene->model[scene->blocks[i].id-1]));
		glTranslatef(-scene->blocks[i].position.x,-scene->blocks[i].position.y,-scene->blocks[i].position.z);
	}
}