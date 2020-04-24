#include "PNM_dith.h"

const double Ordered[8][8] = {{0.0 / 64.0,  48.0 / 64.0, 12.0 / 64.0, 60.0 / 64.0, 3.0 / 64.0,  51.0 / 64.0, 15.0 / 64.0, 63.0 / 64.0},
                              {32.0 / 64.0, 16.0 / 64.0, 44.0 / 64.0, 28.0 / 64.0, 35.0 / 64.0, 19.0 / 64.0, 47.0 / 64.0, 31.0 / 64.0},
                              {8.0 / 64.0,  56.0 / 64.0, 4.0 / 64.0,  52.0 / 64.0, 11.0 / 64.0, 59.0 / 64.0, 7.0 / 64.0,  55.0 / 64.0},
                              {40.0 / 64.0, 24.0 / 64.0, 36.0 / 64.0, 20.0 / 64.0, 43.0 / 64.0, 27.0 / 64.0, 39.0 / 64.0, 23.0 / 64.0},
                              {2.0 / 64.0,  50.0 / 64.0, 14.0 / 64.0, 62.0 / 64.0, 1.0 / 64.0,  49.0 / 64.0, 13.0 / 64.0, 61.0 / 64.0},
                              {34.0 / 64.0, 18.0 / 64.0, 46.0 / 64.0, 30.0 / 64.0, 33.0 / 64.0, 17.0 / 64.0, 45.0 / 64.0, 29.0 / 64.0},
                              {10.0 / 64.0, 58.0 / 64.0, 6.0 / 64.0,  54.0 / 64.0, 9.0 / 64.0,  57.0 / 64.0, 5.0 / 64.0,  53.0 / 64.0},
                                {42.0 / 64.0, 26.0 / 64.0, 38.0 / 64.0, 22.0 / 64.0, 41.0 / 64.0, 25.0 / 64.0, 37.0 / 64.0, 21.0 / 64.0},
};
const double JJN[3][5] = {{0, 0, 0, 7, 5},
                          {3, 5, 7, 5, 3},
                          {1, 3, 5, 3, 1}};
const double Sierra3[3][5] = {{0, 0, 0, 5, 3},
                              {2, 4, 5, 4, 2},
                              {0, 2, 3, 2, 0}};
const double Atkinson[3][5] = {{0, 0, 0, 1, 1},
                               {0, 1, 1, 1, 0},
                               {0, 0, 1, 0, 0}};
const double Halftone[4][4] = {{13.0 / 16.0, 11.0 / 16.0, 4.0 / 16.0,  8.0 / 16.0},
                               {6.0 / 16.0,  0,           3.0 / 16.0,  15.0 / 16.0},
                               {14.0 / 16.0, 1.0 / 16.0,  2.0 / 16.0,  7.0 / 16.0},
                               {9.0 / 16.0,  5.0 / 16.0,  10.0 / 16.0, 12.0 / 16.0},
};


void PNM_dith::read(const string &fileName)  {
    ifstream fin(fileName, ios::binary);

    if (!fin.is_open()) {
        cerr << "Input file wasn't open\n";
        exit(1);
    }
    char P;
    fin >> P >> type_of_pnm >> width >> height >> colors;

    if (P != 'P') {
        cerr << "Error format\n";
        exit(1);
    }
    if (type_of_pnm != 5) {
        cerr << "Error format\n";
        exit(1);
    }
    if (colors != 255) {
        cerr << "Error format of brush_color";
        exit(1);
    }

    fin.get();
    data.clear();
    data.resize(width * height);
    fin.read((char *) &data[0], width * height);

    fin.close();
}

void PNM_dith::write(const string &fileName) {
    ofstream fout(fileName, ios::binary);
    if (!fout.is_open()) {
        cerr << "Output file wasn't open\n";
        exit(1);
    }

    fout << "P" << type_of_pnm << '\n';
    fout << width << ' ' << height << '\n';
    fout << colors << '\n';

    fout.write((char*) &data[0], width * height);

    fout.close();
}

void PNM_dith::fill_grad() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i * width + j] = (unsigned char) gamma_set(((double) j / width) * 255.0);
        }
    }
}

double PNM_dith::gamma_set(double value) {
    value = value / 255;
    if (gamma == 0.) {
        if (value < 0.0031308)
            return value * 12.92 * 255;
        else
            return 255. * ((211.0 * pow (value, 0.4166) - 11.0) / 200.0);
    }
    else {
        return 255. * pow(value, gamma);
        }
}
double PNM_dith::gamma_remove(double value){
    value = value / 255;
    if (gamma == 0) {
        if (value < 0.04045)
            return 255 * value * 12.92;
        else
            return 255 * (pow ((200.0 * value + 11.0) / 211.0, 2.4));
    }
    else {
        return 255 * pow (value, 1 / gamma);
        }
}

void PNM_dith::dith_algo(const Dith_type &type, const int &bitRate) {
    int val = pow(2, bitRate);
    switch (type) {
        case NONE:
            none(type, bitRate, val);
            break;
        case ORDERED_8x8:
            ordered(type, bitRate, val);
            break;
        case RANDOM:
            random(type, bitRate, val);
            break;
        case FLOYD_STEINBERG:
            floyd(type, bitRate, val);
            break;
        case JARVIS_JUDICE_NINKE:
            jarvis(type, bitRate, val);
            break;
        case SIERRA_3:
            sierra(type, bitRate, val);
            break;
        case ATKINSON:
            atkinson(type, bitRate, val);
            break;
        case HALFTONE_4x4:
            halftone(type, bitRate, val);
            break;
    }
}

void PNM_dith::none(const Dith_type &type, const int &bitRate, const int& value) {
    for (int i = 0; i < width * height; ++i) {
        double buffer = gamma_remove((double) data[i]) / 255.0;
        buffer *= value - 1;
        buffer = round (buffer);
        data[i] = round ((int) (gamma_set(buffer * (255.0 / (value - 1.0)))));
    }
}

void PNM_dith::ordered(const Dith_type &type, const int &bitRate, const int& value) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double buffer = (gamma_remove(data[i * width + j]) +
                             (255.0 / (bitRate)) * (Ordered[i % 8][j % 8] - 0.5)) / 255.0;
            if (buffer < 0)
                buffer = 0;

            buffer *= value - 1;
            buffer = round (buffer);
            data[i * width + j] = round ((int) (gamma_set (buffer * (255.0 / (value - 1)))));
        }
    }
}

void PNM_dith::random(const Dith_type &type, const int &bitRate, const int &value) {
    uchar maxValue = pow(2, bitRate) - 1;

    srand(time(NULL));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double picColorSRGB = data[width * i + j] / 255.0;
            double picColorLinear = gamma_remove(picColorSRGB);
            double noise =  (double) rand() / RAND_MAX - 0.75;
            double value = picColorLinear + noise / bitRate;

            value = min(max(value, 0.0), 1.0);

            double newPaletteColor = round(value * maxValue);
            data[width * i + j] = gamma_set(newPaletteColor / maxValue * 255);
        }
    }
}

void PNM_dith::floyd(const Dith_type &type, const int &bitRate, const int &value) {
    vector <int> error (height * width, 0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j){

            double buffer = (gamma_remove(data[i * width + j]) + error[i * width + j]) / 255.0;
            buffer *= (value - 1);
            buffer = round (buffer);
            buffer *= 255.0 / (value - 1);
            int CurrentErrorValue = data[i * width + j] + error[i * width + j] - (int) buffer;
            data[i * width + j] = gamma_set(buffer);
            if (j + 1 < width) {
                error[i * width + j + 1] += CurrentErrorValue * (7.0 / 16.0);
            }
            if (i + 1 < height) {
                if (j + 1 < width) {
                    error[(i + 1) * width + j + 1] += CurrentErrorValue * (1.0 / 16.0);
                }
                error[(i + 1) * width + j] += CurrentErrorValue * (5.0 / 16.0);
                if ((i - 1 > 0) && (j - 1 > 0)) {
                    error[(i - 1) * width + j - 1] += CurrentErrorValue * (3.0 / 16.0);
                }
            }
        }
    }
}

void PNM_dith::jarvis(const Dith_type &type, const int &bitRate, const int &value) {
    vector <int> error (height * width, 0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double buffer = (gamma_remove(data[i * width + j]) + error[i * width + j]) / 255.0;
            buffer *= (value - 1);
            buffer = round (buffer);
            buffer *= 255.0 / (value - 1);
            int CurrentErrorValue = data[i * width + j] + error[i * width + j] - (int) buffer;
            data[i * width + j] = gamma_set(buffer);
            for (int k = 0; k <= 2; ++k) {
                for (int l = -2; l <= 2; ++l) {
                    if (i + k < height) {
                        if ((k == 0) && (l > 0)) {
                            if (j + l < width) {
                                error[(i + k) * width + j + l] += CurrentErrorValue * JJN[k][2 + l] / 48.0;
                            }
                        }
                        else {
                            if ((j + l < width) && (j + l > 0)) {
                                error[(i + k) * width + j + l] += CurrentErrorValue * JJN[k][2 + l] / 48.0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void PNM_dith::sierra(const Dith_type &type, const int &bitRate, const int &value) {
    vector <int> error (height * width, 0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {


            double buffer = (gamma_remove(data[i * width + j]) + error[i * width + j]) / 255.0;
            buffer *= (value - 1);
            buffer = round (buffer);
            buffer *= 255.0 / (value - 1);
            int CurrentErrorValue = data[i * width + j] + error[i * width + j] - (int) buffer;
            data[i * width + j] = gamma_set(buffer);
            for (int k = 0; k <= 2; ++k) {
                for (int l = -2; l <= 2; ++l) {
                    if (i + k < height) {
                        if ((k == 0) && (l > 0)) {
                            if (j + l < width)
                                error[(i + k) * width + j + l] += CurrentErrorValue * Sierra3[k][2 + l] / 32.0;
                        } else {
                            if ((j + l < width) && (j + l > 0))
                                error[(i + k) * width + j + l] += CurrentErrorValue * Sierra3[k][2 + l] / 32.0;
                        }
                    }
                }
            }


        }
    }
}

void PNM_dith::atkinson(const Dith_type &type, const int &bitRate, const int &value) {
    vector <int> error (height * width, 0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double buffer = (gamma_remove(data[i * width + j]) + error[i * width + j]) / 255.0;
            buffer *= (value - 1);
            buffer = round (buffer);
            buffer *= 255.0 / (value - 1);
            int CurrentErrorValue = data[i * width + j] + error[i * width + j] - (int) buffer;
            data[i * width + j] = gamma_set(buffer);
            for (int k = 0; k <= 2; ++k) {
                for (int l = -2; l <= 2; ++l) {
                    if (i + k < height) {
                        if ((k == 0) && (l > 0)) {
                            if (j + l < width) {
                                error[(i + k) * width + j + l] += CurrentErrorValue * Atkinson[k][2 + l] / 8.0;
                            }
                        } else {
                            if ((j + l < width) && (j + l > 0)) {
                                error[(i + k) * width + j + l] += CurrentErrorValue * Atkinson[k][2 + l] / 8.0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void PNM_dith::halftone(const Dith_type &type, const int &bitRate, const int &value) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double buffer = (gamma_remove (data[i * width + j]) +
                             (255.0 / bitRate) * (Halftone[i % 4][j % 4] - 0.75)) / 255.0;
            if (buffer < 0)
                buffer = 0;

            buffer *= value;
            buffer = round (buffer);
            data[i * width + j] = (uchar) round( gamma_set(buffer * (255.0 / (value - 1))));
        }
    }
}







