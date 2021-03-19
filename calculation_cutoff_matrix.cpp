/* % Copyright (C) 2021, GenieView（海沁）
   % The algorithm is made for Joint Autonomous Vehicle Project
   % supported by both HawkEye (Nanjing) and RobSense (Shenzhen)
   % The key team members are Tong Xu（徐童），Moran Huang（黄佳敏），
   % Siqing Ma（马思清），Steed Huang（黄骏）and Hongbin Qian（钱鸿斌）。
   % Version 0.2.8，Mar.08, 2021.
*/

#include "calculation_matrix.h"

using namespace std;

int calculation_cMatrix(vector<vector<double> > matrix) {

    double rowAvg[border];
    double colAvg[border];
    double sum = 0;
    int leftSum = 0;
    int rightSum = 0;
    vector<vector<double> > cutMatrix;
    int i, j;

    // Peep front with left rob eye
    for (i = 0; i < H; i++)
        for (j = 0; j < W / 2; j++)
            leftSum = leftSum + matrix[i][j];

    // Peep front with right rob eye
    for (i = 0; i < H; i++)
        for (j = W / 2; j < W; j++)
            rightSum = rightSum + matrix[i][j];

    //cout << leftSum << " " << rightSum << endl;

    // Make Mantis eye decision: smaller has bigger object
    if (leftSum <= rightSum) {
        for (i = border; i < border * 2; i++) {
            vector<double> tmpMatrix;
            for (j = border;  j < border * 2; j++)
                tmpMatrix.push_back(matrix[i][j]);
            cutMatrix.push_back(tmpMatrix);
        }
    }
    else {
        for (i = border; i < border * 2; i++) {
            vector<double> tmpMatrix;
            for (j = border * 2; j < border * 3; j++)
                tmpMatrix.push_back(matrix[i][j]);
            cutMatrix.push_back(tmpMatrix);
        }
    }

    // Find row average and column average
    for (i = 0; i < border; i++) {
        for (j = 0; j < border; j++)
            sum += cutMatrix[i][j];
        rowAvg[i] = sum / border;
        sum = 0;
    }

    for (j = 0; j < border; j++) {
        for (i = 0; i < border; i++)
            sum += cutMatrix[i][j];
        colAvg[j] = sum / border;
        sum = 0;
    }
    //printf("%f \n", colAvg[70]);

    // Find row and column average
    double allElemAvg;
    sum = 0;
    for (i = 0; i < border; i++)
        sum = sum + rowAvg[i];
    allElemAvg = sum / border;

    // Find row momenergy and column momenergy
    complex<double> diffRowValues[border];
    complex<double> diffColValues[border];
    for (i = 0; i < border; i++) {
        if (rowAvg[i] < allElemAvg)
            diffRowValues[i] = {0, pow(allElemAvg - rowAvg[i], mome)};
        else
            diffRowValues[i] = {pow(rowAvg[i] - allElemAvg, mome), 0};
    }

    for (j = 0; j < border; j++) {
        if (colAvg[j] < allElemAvg)
            diffColValues[j] = {0, pow(allElemAvg - colAvg[j], mome)};
        else
            diffColValues[j] = {pow(colAvg[j] - allElemAvg, mome), 0};
    }

// Find all momenergies report card score
    double dRowPowRealValues[border], dRowPowImagValues[border], dColPowRealValues[border], dColPowImagValues[border];
    for (i = 0; i < border; i++) {
        dRowPowRealValues[i] = (diffRowValues[i].real());
        dRowPowImagValues[i] = (diffRowValues[i].imag());
    }
    for (j = 0; j < border; j++) {
        dColPowRealValues[j] = (diffColValues[j].real());
        dColPowImagValues[j] = (diffColValues[j].imag());
    }

    double rowPowRealAvg, rowPowImagAvg, colPowRealAvg, colPowImagAvg;
    double sumReal = 0, sumImag = 0;
    for (i = 0; i < border; i++) {
        sumReal = sumReal + dRowPowRealValues[i];
        sumImag = sumImag + dRowPowImagValues[i];
    }
    rowPowRealAvg = sumReal / border;
    rowPowImagAvg = sumImag / border;

    sumReal = 0;
    sumImag = 0;
    for (j = 0; j < border; j++) {
        sumReal = sumReal + dColPowRealValues[j];
        sumImag = sumImag + dColPowImagValues[j];
    }
    colPowRealAvg = sumReal / border;
    colPowImagAvg = sumImag / border;

// Compare against the pre-trained score markers 
    int t;
    int p;
    vector<int> standValue {326, 576, 108, 80, 411, 48, 6};
    // vector<int> standValue{ 396, 598, 148, 109, 495, 65};
    vector<int> diffStandValue {1, 2, 3, 4, 5, 6, 7}; // Make it longer now.
    t = rowPowRealAvg + rowPowImagAvg + colPowRealAvg + colPowImagAvg;

// Round off to the neareast object
    for (i = 0; i < 7; i++)
        diffStandValue[i] = abs(t - standValue[i]);

    auto smallest = min_element(begin(diffStandValue), end(diffStandValue));
    p = int(distance(begin(diffStandValue), smallest)) + 1;

    switch (p) {
        case 1:
            cout << "Car" << endl;
            break;
        case 2:
            cout << "Bus" << endl;
            break;
        case 3:
            cout << "Motor" << endl;
            break;
        case 4:
            cout << "Human" << endl;
            break;
        case 5:
            cout << "Suv" << endl;
            break;
        case 6:
            cout << "Curb" << endl;
            break;
        case 7:
            cout << "Small" << endl;
            break;
        default:
            cout << "Large" << endl;
    }

    return 0;
}
