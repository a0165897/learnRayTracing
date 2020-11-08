#pragma once
#include"ray.h"
#include <random>

class material;
vec3 get_random_unit_vector();
vec3 reflect(const vec3& in, const vec3& n);
bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted);
double schlick(double cosine, double ref_idx);
struct hit_record {
	double t;//交点在射线上的位置
	vec3 p;//世界坐标
	vec3 normal;//单位法向量
	material* mat_ptr;//材质
};

class hitable {
public:
	virtual bool hit(const ray& r, const double& t_min, const double& t_max, hit_record& rec) const = 0;
};

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attennuation, ray& scattered) const = 0;
};

class lambertian :public material {
public:
	lambertian(const vec3& a):albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 reflect_target = rec.p + rec.normal + get_random_unit_vector();
		scattered = ray(rec.p, reflect_target - rec.p);
		attenuation = albedo;
		return true;
	}
	vec3 albedo;
};

class metal :public material {
public:
	metal(const vec3& a,const double & f=0.0) :albedo(a),fuzz(min(f,1.0f)) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 reflect_direction = reflect(r_in.d().normalized(), rec.normal);
		scattered = ray(rec.p, reflect_direction + vec3(fuzz) * get_random_unit_vector());
		attenuation = albedo;
		return scattered.d().dot(rec.normal) > 0;
	}
	vec3 albedo;
	double fuzz;//粗糙度
};

//玻璃
class dielectric :public material {
public:
	dielectric(const double& ri):ref_idx(ri){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.d(), rec.normal);
		double ni_over_nt; 
		attenuation = vec3(1.00,1.00,1.00);
		vec3 refracted;
		double reflect_prob;
		double cosine;
		if (r_in.d().dot(rec.normal) > 0) {//出
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;          
			cosine = (r_in.d().dot(rec.normal)) / (r_in.d().length());
			cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
		}
		else {//进
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = (-r_in.d().dot(rec.normal)) / (r_in.d().length());
		}
		if (refract(r_in.d(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_idx);
		}
		else {
			reflect_prob = 1.0;
		}
		if (abs(get_random_unit_vector().x()) < reflect_prob) {
			scattered = ray(rec.p, reflected);
		}
		else {
			scattered = ray(rec.p, refracted);
		}
		return true;
	}
	double ref_idx;
};

vec3 reflect(const vec3& in, const vec3& n) {
	return in - vec3(2) * vec3(in.dot(n)) * n;
}

bool refract( const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted) {
	vec3 uv = v.normalized();
	double dt = uv.dot(n);
	double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant>0) {
		refracted = vec3(ni_over_nt) * (uv - n * vec3(dt)) - n * vec3(sqrt(discriminant));
		return true;
	}
	else {
		return false;//全反射
	}
}
double schlick(double cosine, double ref_idx) {
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}