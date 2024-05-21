#include "camera.h"

#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 90.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

int update_camera(Camera* camera, double time, Scene* scene)
{
    double angle;
    double side_angle;
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
	for(int i=0;i<scene->block_counter;i++){
		if(fabs(camera->position.y-scene->blocks[i].position.y)<scene->block_size && fabs(camera->position.z-scene->blocks[i].position.z)<scene->block_size){
			if(scene->blocks[i].is_active!=1){
				continue;
			}
			if(scene->blocks[i].id==2){
				printf("\n\n\n");
				printf("----------------------------------------\n");
				printf("              GAME OVER                 \n");
				printf("----------------------------------------\n");
				printf("\n\n\n");
				return -1;
			}
			if(scene->blocks[i].id==3){
				printf("\n\n\n");
				printf("----------------------------------------\n");
				printf("         Gratulation, you WON           \n");
				printf("----------------------------------------\n");
				printf("\n\n\n");
				return -1;
			}
			camera->position.x -= cos(angle) * camera->speed.y * time;
			camera->position.y -= sin(angle) * camera->speed.y * time;
			camera->position.x -= cos(side_angle) * camera->speed.x * time;
			camera->position.y -= sin(side_angle) * camera->speed.x * time;
			break;
		}
	}
	scene->player_velocity+=scene->gravity*time;
	camera->position.z-=scene->player_velocity;
	for(int i=0;i<scene->block_counter;i++){
		if(fabs(camera->position.y-scene->blocks[i].position.y)<scene->block_size && fabs(camera->position.z-scene->blocks[i].position.z)<scene->block_size){
			if(scene->blocks[i].is_active!=1){
				continue;
			}
			if(scene->blocks[i].id==2){
				scene->blocks[i].is_active=0;
			}
			camera->position.z +=scene->player_velocity;
			scene->player_velocity=0;
			break;
		}
	}
	
	if(camera->position.z<-5.0){
		camera->position.z=-5.0;
		scene->player_velocity=0.0;
	}
	
	if(camera->position.x>0.5){
		camera->position.x=0.5;
	}else if(camera->position.x<-0.5){
		camera->position.x=-0.5;
	}
	if(camera->position.y<-0.5){
		camera->position.y=-0.5;
	}
	return 0;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }
	
	if (camera->rotation.x < -90.0) {
        camera->rotation.x = -90.0;
    }

    if (camera->rotation.x > 90.0) {
        camera->rotation.x =90.0;
    }
	

}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}



void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}