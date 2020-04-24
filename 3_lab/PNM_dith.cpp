#include "PNM_dith.h"

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

