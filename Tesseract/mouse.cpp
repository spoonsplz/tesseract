#include <vector>

#include "aerobox.h"

#define PI 3.14159265358979323846

namespace aerobox {

	void calc_ray(int, int, int, int);

	int mouse_x, mouse_y;

	std::vector<bool> bd(3, 0), lbd(3, 0);

	glm::vec3 ray_origin(0, 0, 0);
	glm::vec3 ray_dir(0, 0, 0);

	void mouse_func(int key, int state, int x, int y) {
		bd[key] = 1 - state;
	}

	void mouse_update(){
		lbd = bd;
	}

	bool button_down(int b){
		return bd[b];
	}

	bool button_pressed(int b){
		return bd[b] && (!lbd[b]);
	}

	bool button_released(int b){
		return (!bd[b]) && lbd[b];
	}

	void motion_func(int x, int y){
		mouse_x = x;
		mouse_y = y;
	}

	void passive_motion_func(int x, int y){
		mouse_x = x;
		mouse_y = y;
	}

	void calc_ray(){
		glm::vec3 view = viewport_lookat - viewport_position;
		view = glm::normalize(view);
		glm::vec3 h = glm::cross(view, viewport_up);
		h = glm::normalize(h);
		glm::vec3 v = glm::cross(h, view);
		v = glm::normalize(v);

		float rad = fov * PI / 180;
		float vl = tan(rad / 2) * viewport_near;
		float hl = vl * (float)viewport_width / viewport_height;
		h *= hl;
		v *= vl;
		float fx = mouse_x, fy = -mouse_y;
		fx -= viewport_width / 2;
		fy += viewport_height / 2;
		fx /= viewport_width / 2;
		fy /= viewport_height / 2;

		ray_origin = viewport_position;
		ray_origin += view * viewport_near;
		h *= fx;
		ray_origin += h;
		v *= fy;
		ray_origin += v;

		ray_dir = ray_origin - viewport_position;
	}
}
