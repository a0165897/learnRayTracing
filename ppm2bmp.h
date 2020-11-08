#pragma once
#include<fstream>
#include <iomanip> 
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <vector>

typedef struct RGB {
    int r;
    int g;
    int b;
}RGB;

typedef struct ppm_p3_header {
    char type[2];
    int width, height, maxColor;
}ppm_p3_header;

void ppm2bmp(const char* ppmFileName, const int bpp = 24)
{
    std::ifstream fin(ppmFileName);
    FILE* fp;
    fopen_s(&fp, "test.bmp", "wb");

    ppm_p3_header ppm;
    fin >> ppm.type >> ppm.width >> ppm.height >> ppm.maxColor;

    BITMAPFILEHEADER bmpheader;
    BITMAPINFOHEADER bmpinfo;
    std::vector<std::vector<struct RGB>*>* ppmColor;
    bmpheader.bfType = 0x4d42;
    bmpheader.bfReserved1 = 0;
    bmpheader.bfReserved2 = 0;
    bmpheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) - 2;
    bmpheader.bfSize = bmpheader.bfOffBits + ppm.width * ppm.height * bpp / 8;
    bmpinfo.biSize = sizeof(BITMAPINFOHEADER);
    bmpinfo.biWidth = ppm.width;
    bmpinfo.biHeight = ppm.height;
    bmpinfo.biPlanes = 1;
    bmpinfo.biBitCount = bpp;
    bmpinfo.biCompression = 0;//BI_RGB;
    bmpinfo.biSizeImage = ppm.width * ppm.height * bpp / 8;
    bmpinfo.biXPelsPerMeter = 100;
    bmpinfo.biYPelsPerMeter = 100;
    bmpinfo.biClrUsed = 0;
    bmpinfo.biClrImportant = 0;
    fwrite(&bmpheader.bfType, sizeof(bmpheader.bfType), 1, fp);
    fwrite(&bmpheader.bfSize, sizeof(bmpheader.bfSize), 1, fp);
    fwrite(&bmpheader.bfReserved1, sizeof(bmpheader.bfReserved1), 1, fp);
    fwrite(&bmpheader.bfReserved2, sizeof(bmpheader.bfReserved2), 1, fp);
    fwrite(&bmpheader.bfOffBits, sizeof(bmpheader.bfOffBits), 1, fp);
    fwrite(&bmpinfo.biSize, sizeof(bmpinfo.biSize), 1, fp);
    fwrite(&bmpinfo.biWidth, sizeof(bmpinfo.biWidth), 1, fp);
    fwrite(&bmpinfo.biHeight, sizeof(bmpinfo.biHeight), 1, fp);
    fwrite(&bmpinfo.biPlanes, sizeof(bmpinfo.biPlanes), 1, fp);
    fwrite(&bmpinfo.biBitCount, sizeof(bmpinfo.biBitCount), 1, fp);
    fwrite(&bmpinfo.biCompression, sizeof(bmpinfo.biCompression), 1, fp);
    fwrite(&bmpinfo.biSizeImage, sizeof(bmpinfo.biSizeImage), 1, fp);
    fwrite(&bmpinfo.biXPelsPerMeter, sizeof(bmpinfo.biXPelsPerMeter), 1, fp);
    fwrite(&bmpinfo.biYPelsPerMeter, sizeof(bmpinfo.biYPelsPerMeter), 1, fp);
    fwrite(&bmpinfo.biClrUsed, sizeof(bmpinfo.biClrUsed), 1, fp);
    fwrite(&bmpinfo.biClrImportant, sizeof(bmpinfo.biClrImportant), 1, fp);

    ppmColor = new std::vector<std::vector<struct RGB>*>;
    for (int y = 1; y <= ppm.height; y++) {
        std::vector<struct RGB>* ppmLine = new std::vector<struct RGB>;
        ppmColor->push_back(ppmLine);
        for (int x = 1; x <= ppm.width; x++) {
            struct RGB currentColor;
            fin >> currentColor.r >> currentColor.g >> currentColor.b;
            ppmLine->push_back(currentColor);
        }
    }
    //纵轴存储方向相反 bmp特色
    for (auto i = ppmColor->rbegin(); i < ppmColor->rend(); i++) {
        for (auto j = (*i)->begin(); j < (*i)->end(); j++) {
            fwrite(&(*j).b, 1, 1, fp);
            fwrite(&(*j).g, 1, 1, fp);
            fwrite(&(*j).r, 1, 1, fp);
        }
    }
    for (auto i = ppmColor->begin(); i < ppmColor->end(); i++) {
        delete* i;
        *i = nullptr;
    }
    ppmColor->clear();
    fclose(fp);
    fp = NULL;
    return;
}
