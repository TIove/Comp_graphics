#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
typedef unsigned char uchar;

enum Dith_type {
    NONE = 0,
    ORDERED_8x8 = 1,
    RANDOM = 2,
    FLOYD_STEINBERG = 3,
    JARVIS_JUDICE_NINKE = 4,
    SIERRA_3 = 5,
    ATKINSON = 6,
    HALFTONE_4x4 = 7
};

class PNM_dith {
public:
    double gamma = 0;
    void fill_grad();
    void read(const string& fileName);
    void write(const string& fileName);
    void dith_algo(const Dith_type& type, const int& bitRate);

private:
    short type_of_pnm = -1, colors = -1;
    int width = -1, height = -1;

    vector<uchar> data;

    double gamma_set (double value);
    double gamma_remove (double value);

    void none(const Dith_type& type, const int& bitRate, const int& value);
    void ordered(const Dith_type& type, const int& bitRate, const int& value);
    void random(const Dith_type& type, const int& bitRate, const int& value);
    void floyd(const Dith_type& type, const int& bitRate, const int& value);
    void jarvis(const Dith_type& type, const int& bitRate, const int& value);
    void sierra(const Dith_type& type, const int& bitRate, const int& value);
    void atkinson(const Dith_type& type, const int& bitRate, const int& value);
    void halftone(const Dith_type& type, const int& bitRate, const int& value);
};