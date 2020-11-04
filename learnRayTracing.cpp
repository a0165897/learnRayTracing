#include <iostream>
#include<fstream>
#include "ppm2bmp.h"
using namespace std;
int main()
{
	int width = 200;
	int height = 100;
    char image[]= "OutputImage.ppm";
	ofstream fout(image);
	fout << "P3\n" << width << " " << height << "\n255\n";
	cout << "rendering..." << endl;
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{
			int ir = int(255.99f * i / width);
            int ig = int(255.99f * j / height);
			int ib = int(255.99f * 0.5);

			fout << ir << " " << ig << " " << ib << "\n";
		}
	}
	cout << "rendered." << endl;
	fout.close();
    ppm2bmp(image);
	return 0;
}