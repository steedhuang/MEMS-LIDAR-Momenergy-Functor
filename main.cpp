/* % Copyright (C) 2020, GenieView（海沁）
   % The algorithm is made for Joint Autonomous Vehicle Project
   % supported by both HawkEye and RobSense
   % The key team members are Tong Xu（徐童），Moran Huang（黄佳敏），
   % Siqing Ma（马思清），Steed Huang（黄骏）and Hongbin Qian（钱鸿斌）。
   % Version 0.2.3，Oct.25, 2020.
*/

#include "calculation_matrix.h"

using namespace std;

int main() {
    string str;
    vector<vector<int> > orgMatrix;

    //ifstream in("your file name");
    ifstream in("C:\\Users\\steed\\Desktop\\calculationMatrix\\calculationMatrixV2\\calculationMatrixV2\\car.txt");
    //ifstream in("/Users/Moran/CLionProjects/calculationMatrixV4/curb.txt");

    if (!in.is_open()) {
        cout << "Matrix no loaded." << endl;
        return -1;
    }

    while (getline(in, str)) {
        istringstream input(str);
        vector<int> tmpMatrix;
        int row;
        while (input >> row)
            tmpMatrix.push_back(row);

        orgMatrix.push_back(tmpMatrix);
    }
    in.close();

    calculation_matrix(orgMatrix);
    return 0;
}