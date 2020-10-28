/* % Copyright (C) 2020, GenieView（海沁）
   % The algorithm is made for Joint Autonomous Vehicle Project
   % supported by both HawkEye and RobSense
   % The key team members are Tong Xu（徐童），Moran Huang（黄佳敏），
   % Siqing Ma（马思清），Steed Huang（黄骏）and Hongbin Qian（钱鸿斌）。
   % Version 0.2.3，Oct.25, 2020.
*/

#include "calculation_matrix.h"

using namespace std;

int calculation_matrix(vector<vector<int> > matrix) {

    double rowAvg[a];
    double colAvg[b];
    double sum = 0;
    int i, j;

// Find row average or column average

    for (i = 0; i < a; i++) {
        for (j = 0; j < b; j++)
            sum += matrix[i][j];
        rowAvg[i] = sum / b;
        sum = 0;
    }

    for (j = 0; j < b; j++) {
        for (i = 0; i < a; i++)
            sum += matrix[i][j];
        colAvg[j] = sum / a;
        sum = 0;
    }

// Find row and column average

    double allElemAvg;
    sum = 0;
    for (i = 0; i < a; i++)
        sum = sum + rowAvg[i];
    allElemAvg = sum / a;

// Find row momenergy or column momenergy

    complex<double> diffRowValues[a];
    complex<double> diffColValues[b];
    for (i = 0; i < a; i++) {
        if (rowAvg[i] < allElemAvg)
            diffRowValues[i] = {0,pow(allElemAvg - rowAvg[i],mome)};
        else
            diffRowValues[i] = {pow(rowAvg[i] - allElemAvg,mome),0};
    }

    for (j = 0; j < b; j++) {
        if (colAvg[j] < allElemAvg)
            diffColValues[j] = {0,pow(allElemAvg - colAvg[j],mome)};
        else
            diffColValues[j] = {pow(colAvg[j] - allElemAvg,mome),0};
    }

// Find all momenergies report card score

    double dRowPowRealValues[a], dRowPowImagValues[a], dColPowRealValues[b], dColPowImagValues[b];
    for (i = 0; i < a; i++) {
        dRowPowRealValues[i] = (diffRowValues[i].real());
        dRowPowImagValues[i] = (diffRowValues[i].imag());
    }
    for (j = 0; j < b; j++) {
        dColPowRealValues[j] = (diffColValues[j].real());
        dColPowImagValues[j] = (diffColValues[j].imag());
    }

    double rowPowRealAvg, rowPowImagAvg, colPowRealAvg, colPowImagAvg;
    double sumReal = 0, sumImag = 0;
    for (i = 0; i < a; i++) {
        sumReal = sumReal + dRowPowRealValues[i];
        sumImag = sumImag + dRowPowImagValues[i];
    }
    rowPowRealAvg = sumReal / a;
    rowPowImagAvg = sumImag / a;

    sumReal = 0;
    sumImag = 0;
    for (j = 0; j < b; j++) {
        sumReal = sumReal + dColPowRealValues[j];
        sumImag = sumImag + dColPowImagValues[j];
    }
    colPowRealAvg = sumReal / b;
    colPowImagAvg = sumImag / b;

// Compare against the pre-trained score markers 

    int t;
    int p;
    vector<int> standValue {396, 598, 148, 109, 495, 65};
    vector<int> diffStandValue {1, 2, 3, 4, 5, 6};
    t = rowPowRealAvg + rowPowImagAvg + colPowRealAvg + colPowImagAvg;

// Round off to the neareast object

    for (i = 0; i < 6; i++)
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
            cout << "SUV" << endl;
            break;
        case 6:
            cout << "Curb" << endl;
            break;
        default:
            cout << "Fail" << endl;
    }

    return 0;
}