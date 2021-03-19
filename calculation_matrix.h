/* % Copyright (C) 2021, GenieView（海沁）
   % The algorithm is made for Joint Autonomous Vehicle Project
   % supported by both HawkEye (Nanjing) and RobSense (Shenzhen)
   % The key team members are Tong Xu（徐童），Moran Huang（黄佳敏），
   % Siqing Ma（马思清），Steed Huang（黄骏）and Hongbin Qian（钱鸿斌）。
   % Version 0.2.8，Mar.08, 2021.
*/
#ifndef UNTITLED_CALCULATION_H
#define UNTITLED_CALCULATION_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <complex>
#include <string>
#include <cstdio>
#include <windows.h>

// Mantis middle eye and left right eyes

#pragma pack(push)  // push current alignment to stack
#pragma pack(1)     // set alignment to 1 byte boundary

typedef struct
{
    unsigned short int Type; // File type
    unsigned int Size; // File size in bytes
    unsigned short int Reserved1; // Reserved; must be 0
    unsigned short int Reserved2; // Reserved; must be 0
    unsigned int Offset; // Species the offset in bytes from the header to the bitmap bits (in B)
} HEADER; // 14 Bytes

typedef struct
{
    unsigned int Size; // Header size in bytes
    int Width; // Width of image
    int Height; // Height of image
    unsigned short int Planes; // Number of colour planes, must be 1
    unsigned short int Bits; // Bits per pixel
    unsigned int Compression; // Compression type
    unsigned int ImageSize; // Image size in bytes
    int xResolution; // Number of pixels per meter in x axis
    int yResolution; // Number of pixels per meter in y axis
    unsigned int Colors; // Number of colors
    unsigned int ImportantColors; // Important colors
} INFO; // 40 Bytes

#pragma pack(pop)   // restore original alignment from stack

#define W 560
#define H 420
#define R 0.2989
#define G 0.5870
#define B 0.1140
#define mome 1.5
#define border 140

using namespace std;

int calculation_cMatrix(vector<vector<double> > matrix);

#endif


/*
 * //opencv solution
#include <opencv2/opencv.hpp>
typedef struct {
    BITMAPFILEHEADER bmpHeader;
    BITMAPINFOHEADER bmpInfo;
    RGBQUAD bmpRgb[256];
    unsigned char *bmpData;
} BMP;
 */
