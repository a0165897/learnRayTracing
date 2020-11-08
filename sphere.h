#pragma once

#include "hitable.h"

class sphere :public hitable {
public:
	sphere():center(vec3(0,0,-1)),radius(1.0f){}
	sphere(vec3 center,double r,material* mat = new lambertian(vec3(0.5,0.5,0.5))):center(center),radius(r),mat(mat){}
	virtual bool hit(const ray& r, const double& t_min, const double& t_max, hit_record& rec) const;
private:
	vec3 center;
	double radius;
	material *mat;
};

bool sphere::hit(const ray& r, const double& t_min, const double& t_max, hit_record& rec)const {
	vec3 oc = r.o() - this->center;
	double A = r.d().dot(r.d());
	double B = oc.dot(r.d());
	double C = oc.dot(oc) - this->radius * this->radius;
	double delta = B * B -  A * C;
	if (delta > 0) {
		double root = (-B - sqrt(delta)) / (A);//root即t，在值域内，root越小，离眼睛越近
		if (t_min < root && root < t_max) {
			rec.t = root;
			rec.p = r.point(rec.t);
			rec.normal = (rec.p - this->center) / vec3(this->radius);
			rec.mat_ptr = mat;
			return true;
		}
		root = (-B + sqrt(delta)) / (A);
		if (t_min < root && root < t_max) {
			rec.t = root;
			rec.p = r.point(rec.t);
			rec.normal = (rec.p - this->center) / vec3(this->radius);
			rec.mat_ptr = mat;
			return true;
		}
	}
	return false;
}