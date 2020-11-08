#pragma once
#include"ray.h"
#define PI 3.1415926535897932384626

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = vec3(2.0) * vec3(get_random_unit_vector().x(), get_random_unit_vector().y(), 0.0) - vec3(1, 1, 0);
	} while (p.dot(p) >= 1.0);
	return p;
}
class camera {
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double fov, double aspect, double aperture, double focus_dist) {
		ccd_radius = aperture / 2;
		double theta = fov * PI / 180;
		double half_height = tan(theta / 2) * focus_dist;
		double half_width = aspect * half_height;
		w = (lookfrom - lookat).normalized();
		u = vup.cross(w).normalized();
		v = w.cross(u);
		location_eye = lookfrom;
		u_max = vec3(2.0 * half_width) * u;
		v_max = vec3(2.0 * half_height) * v;
		location_left_down = location_eye - vec3(half_width) * u - vec3(half_height) * v - w * vec3(focus_dist);
	}
	ray get_ray(const double& u, const double& v) {
		vec3 rd = vec3(ccd_radius) * random_in_unit_disk();
		vec3 offset = this->u * rd.x() + this->v * rd.y();
		return ray(location_eye+offset, location_left_down + vec3(u) * u_max + vec3(v) * v_max - (location_eye + offset));
	}
private:
	vec3 location_left_down;
	vec3 location_eye;
	vec3 u_max;
	vec3 v_max;
	vec3 u, v, w;
	double ccd_radius;
};