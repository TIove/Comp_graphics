#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
typedef unsigned char uchar;

class PNM_dith {
public:
private:
    short type_of_pnm = -1, colors = -1;
    int width = -1, height = -1;
    vector<uchar> data;

    void read(const string& fileName);
    void write(const string& fileName);

};