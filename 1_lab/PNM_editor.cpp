#include <iostream>
#include <fstream>
#include <string>
#include <vector>
typedef unsigned char uchar;

using namespace std;

struct RGB {
    uchar R;
    uchar G;
    uchar B;
};

class PNM {
private:
    short type_of_pnm = -1;
    int width = -1, height = -1, colors = -1;

    vector<uchar> matrix_P5;
    vector<RGB> matrix_P6;

    void color_P5() {
        for (int i = 0; i < width * height; i++) {
            matrix_P5[i] = colors - matrix_P5[i];
        }
    }
    void color_P6() {
        for (int i = 0; i < width * height; i++) {
            matrix_P6[i].R = colors - matrix_P6[i].R;
            matrix_P6[i].G = colors - matrix_P6[i].G;
            matrix_P6[i].B = colors - matrix_P6[i].B;
        }
    }

    void mirror_H_P5() {
        for (int j = 0; j < width; j++) {
            for (int i = 0; i < height / 2; i++) {
                swap(matrix_P5[i * width + j], matrix_P5[(height - 1) * width - i * width + j]);
            }
        }
    }
    void mirror_H_P6() {
        for (int j = 0; j < width; j++) {
            for (int i = 0; i < height / 2; i++) {
                swap(matrix_P6[i * width + j], matrix_P6[(height - 1) * width - i * width + j]);
            }
        }
    }

    void mirror_V_P5() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width / 2; j++) {
                swap(matrix_P5[i * width + j], matrix_P5[i * width + width - j - 1]);
            }
        }
    }
    void mirror_V_P6() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width / 2; j++) {
                swap(matrix_P6[i * width + j], matrix_P6[i * width + width - j - 1]);
            }
        }
    }

    void turn_right_P5() {
        vector<uchar> turnedDataP5(width * height);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                turnedDataP5[(height - i - 1) + j * height] = matrix_P5[i * width + j];
            }
        }

        matrix_P5.clear();
        matrix_P5 = turnedDataP5;
    }
    void turn_right_P6() {
        vector<RGB> turnedDataP6(width * height);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                turnedDataP6[(height - i - 1) + j * height] = matrix_P6[i * width + j];
            }
        }

        matrix_P6.clear();
        matrix_P6 = turnedDataP6;
    }

    void turn_left_P5() {
        vector<uchar> turnedDataP5(width * height);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                turnedDataP5[height * (width - j - 1) + i] = matrix_P5[i * width + j];
            }
        }

        matrix_P5.clear();
        matrix_P5 = turnedDataP5;
    }
    void turn_left_P6() {
        vector<RGB> turnedDataP6(width * height);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                turnedDataP6[height * (width - j - 1) + i] = matrix_P6[i * width + j];
            }
        }

        matrix_P6.clear();
        matrix_P6 = turnedDataP6;
    }

public:
    void read(const string& fileName) {
        ifstream inputFile(fileName, ios::binary);

        if (!inputFile.is_open()) {
            cout << "Input file wasn't open\n";
            exit(-1);
        }
        char P;
        inputFile >> P >> type_of_pnm >> width >> height >> colors;

        if (P != 'P') {
            cout << "Error format\n";
            exit(-1);
        }
        if (type_of_pnm != 5 && type_of_pnm != 6) {
            cout << "Error format\n";
            exit(-1);
        }
        if (colors != 255) {
            cout << "Error format of color";
            exit(-1);
        }

        inputFile.get();
        if (type_of_pnm == 5) {
            matrix_P5.clear();
            matrix_P5.resize(width * height);
            inputFile.read((char *) &matrix_P5[0], width * height);
        }
        else
        if (type_of_pnm == 6) {
            matrix_P6.clear();
            matrix_P6.resize(width * height);

            auto* buffer = new uchar[width * height * 3];
            inputFile.read((char*) buffer, width * height * 3);

            for (int i = 0; i < width * height; i++) {
                matrix_P6[i].R = buffer[i * 3 + 0];
                matrix_P6[i].G = buffer[i * 3 + 1];
                matrix_P6[i].B = buffer[i * 3 + 2];
            }

            delete[] buffer;
        }

        inputFile.close();
    }

    void write(const string& fileName) {
        ofstream outputFile(fileName, ios::binary);
        if (!outputFile.is_open()) {
            cout << "Output file wasn't open\n";
            exit(-1);
        }

        outputFile << "P" << type_of_pnm << '\n';
        outputFile << width << ' ' << height << '\n';
        outputFile << colors << '\n';

        if (type_of_pnm == 5)
            outputFile.write((char*) &matrix_P5[0], width * height);
        else
        if (type_of_pnm == 6) {
            uchar* buffer = new uchar[width * height * 3];
            for (int i = 0; i < width * height; i++) {
                buffer[i * 3 + 0] = matrix_P6[i].R;
                buffer[i * 3 + 1] = matrix_P6[i].G;
                buffer[i * 3 + 2] = matrix_P6[i].B;
            }
            outputFile.write((char*) buffer, width * height * 3);
            delete[] buffer;
        }
        outputFile.close();
    }

    void execute(short cmd) {
        switch(cmd) {
            case 0:
                if (type_of_pnm == 5)
                    color_P5();
                else
                    color_P6();

                break;
            case 1:
                if (type_of_pnm == 5)
                    mirror_H_P5();
                else
                    mirror_H_P6();

                break;
            case 2:
                if (type_of_pnm == 5)
                    mirror_V_P5();
                else
                    mirror_V_P6();

                break;
            case 3:
                if (type_of_pnm == 5)
                    turn_right_P5();
                else
                    turn_right_P6();
                swap(width, height);

                break;
            case 4:
                if (type_of_pnm == 5)
                    turn_left_P5();
                else
                    turn_left_P6();
                swap(width, height);

                break;
            default:
                exit(-1);
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Incorrect count of arguments\n";
        return 0;
    }
    string in_name = argv[1], out_name = argv[2];

    short command;
    command = (short) stoi(argv[3], nullptr);

    if (command > 4 || command < 0) {
        cout << "Wrong command";
        return -1;
    }

    PNM pic;

    pic.read(in_name);
    pic.execute(command);
    pic.write(out_name);

    return 0;
}
