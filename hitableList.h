#pragma once
#include"hitable.h"

class hitable_list :public hitable {
public:
	hitable_list(){}
	hitable_list(hitable ** list,int size):list(list),list_size(size){}
	virtual bool hit(const ray& r, const double& t_min, const double& t_max, hit_record& rec)const;
private:
	hitable** list;
	int list_size;
};

bool hitable_list::hit(const ray& r, const double& t_min, const double& t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	double ray_depth = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, ray_depth, temp_rec)) {
			hit_anything = true;
			ray_depth = temp_rec.t;
			rec = temp_rec;//引用本身的指向初始化后无法重新赋值
		}
	}
	return hit_anything;
}