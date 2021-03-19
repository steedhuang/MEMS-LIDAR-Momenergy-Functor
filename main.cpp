/* % Copyright (C) 2021, GenieView（海沁）
   % The algorithm is made for Joint Autonomous Vehicle Project
   % supported by both HawkEye (Nanjing) and RobSense (Shenzhen)
   % The key team members are Tong Xu（徐童），Moran Huang（黄佳敏），
   % Siqing Ma（马思清），Steed Huang（黄骏）and Hongbin Qian（钱鸿斌）。
   % Version 0.2.8，Mar.08, 2021.
*/
#include "calculation_matrix.h"

using namespace std;

HEADER bmpHeader;
INFO bmpInfo;

int main() {
    FILE *bmpImg;
    vector<vector<double> > orgMatrix;
//gap_9_10_0185.bmp
    if (bmpImg = fopen("C:\\Users\\steed\\Desktop\\Nanjing\\seainf\\10w\\calculationMatrix\\calculationMatrixV12\\calculationMatrixV12\\test.bmp", "rb")) {
        fread(&bmpHeader, 1, sizeof(HEADER), bmpImg);

        // Check if the file is a bmp file.
        if (bmpHeader.Type == 0x4d42) {
            fread(&bmpInfo,1, sizeof(INFO), bmpImg);

            // Check if it's 24-bit bmp file.()
            if (bmpInfo.Bits == 24) {

                // Read the 54-byte header
                unsigned char info[54];
                fread(info, sizeof(unsigned char), 54, bmpImg);

                // Extract image height and width from header
                int width = bmpInfo.Width;
                int height = bmpInfo.Height;
                //cout << width << endl;
                //cout << height << endl;

                // Move file point to the begging of bitmap data
                fseek(bmpImg, bmpHeader.Offset, SEEK_SET);

                // Allocate 3 bytes per pixel(Only works on 24bit bmp.)
                int row_padded = (width * 3 + 3) & (~3);
                unsigned char *data = new unsigned char[row_padded];

                // Calculate grey value of each pixel and push into a vector.
                for (int i = 0; i < height; i++) {
                    fread(data, sizeof(unsigned char), row_padded, bmpImg);
                    vector<double> img2Data;
                    for (int j = 0; j < row_padded; j += 3) {
                        // RGB to Grey
                        double greyValue = R * data[j + 2] + G * data[j + 1] + B * data[j];
                        img2Data.push_back(greyValue);
                    }
                    orgMatrix.push_back(img2Data);
                }
                // Wrap up
                free(data);
                fclose(bmpImg);
                calculation_cMatrix(orgMatrix);
            }
            else
                cout << "Not a 24bit bmp file!" << endl;
        }
        else cout << "Not a bmp file!" << endl;
    }
    else
        cout << "Loading failed." << endl;
    return 0;
}