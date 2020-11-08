#pragma once
#include "vec3.h"
class ray {
public:
	ray():origin(vec3(0,0,0)),direction_max(vec3(0,0,-1)){}
	ray(const vec3& o, const vec3& d) :origin(o), direction_max(d) {}
	ray(const vec3 &d):origin(vec3(0, 0, 0)),direction_max(d){}
	vec3 o() const { return this->origin; }
	vec3 d() const { return this->direction_max; }
	vec3 point(const double& t) const { return origin + vec3(t) * direction_max; }
private:
	vec3 origin;
	vec3 direction_max;
};