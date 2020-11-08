#include <iostream>
#include <fstream>
#include <random>
#include "ppm2bmp.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
using namespace std;

default_random_engine e(time(0));
vec3 get_random_unit_vector() {
	//rand(e)
	uniform_real_distribution<double> rand(-1.0,1.0);
	vec3 p;
	do {
		p = vec3(rand(e), rand(e), rand(e));
	} while (p.dot(p) >= 1.0);
	return p;
}

vec3 test_hit(const ray& r, const hitable_list &world,int depth) {
	hit_record rec;
	if (world.hit(r,0.001,INFINITY,rec)) {
		ray scattered;//反射
		vec3 attenuation;
		if (depth<50 &&rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
			return  attenuation* test_hit(scattered, world,depth+1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 normalized_direction = r.d().normalized();
		double ct = 0.5 * (1.0 + normalized_direction.y());
		return vec3(1.0 - ct) * vec3(1.0, 1.0, 1.0) + vec3(ct) * vec3(0.4, 0.6, 1.0);
	}
}


int main(){
	//rand(e)
	uniform_real_distribution<double> rand(-0.5, 0.5);
	double level = 8;
	double width = 90*level;
	double height = 160*level;
	int ssaa = 128;
    char image[]= "OutputImage.ppm";
	ofstream fout(image);
	fout << "P3\n" << width << " " << height << "\n255\n";
	cout << "rendering..." << endl;
	vec3 look_from = vec3(0,1.0,7.0);
	vec3 look_to = vec3(0, 1.5, -1.0);
	double aperture = 1.5;
	camera cam(look_from, look_to, vec3(0, 1, 0), 30, width / height, aperture, (look_from - look_to).length());
	hitable* list[6];
	list[0] = new sphere(vec3(0, -1000.5, -1), 1000, new lambertian(vec3(0.65, 0.65, 0.65)));
	list[1] = new sphere(vec3(0, 1, -1), 0.5, new lambertian(vec3(0.99, 0.99, 0.99)));
	list[2] = new sphere(vec3(0, 0, -1), 0.5, new metal(vec3(0.99, 0.99, 0.99), 0.0));
	list[3] = new sphere(vec3(0, 3, -1), 0.5, new dielectric(1.36));
	list[4] = new sphere(vec3(0, 3, -1), -0.47, new dielectric(1.36));
	list[5] = new sphere(vec3(0, 2, -1), 0.5, new dielectric(1.8));
	hitable_list world = hitable_list(list, 6);
	for (int j = height - 1; j >= 0; j--){
		cout << setiosflags(ios::fixed) << setprecision(3) <<1.0 - j / height << endl;
		for (int i = 0; i < width; i++){
			vec3 hit_result_color = vec3(0,0,0);
			for (int t = 0; t < ssaa; t++) {
				double u = (i +rand(e)) / width;
				double v = (j +rand(e)) / height;
				ray ray = cam.get_ray(u, v);
				hit_result_color += test_hit(ray, world,0);
			}
			hit_result_color /= (double)ssaa;
			int r = int(255.99f * pow(hit_result_color.r(), 1 / 2.2));
            int g = int(255.99f * pow(hit_result_color.g(), 1 / 2.2));
			int b = int(255.99f * pow(hit_result_color.b(), 1 / 2.2));
			fout << r << " " << g << " " << b << "\n";
		}
	}
	cout << "rendered." << endl;
	fout.close();
    ppm2bmp(image);
	cout << "ppm transformed to bmp." << endl;

	return 0;
}