#include "PNM_dith.h"
using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 6) {
        cerr << "Incorrect count of arguments" << endl;
        return 1;
    }
    string fin = argv[1];
    string fout = argv[2];
    
    bool grad;
    if (stoi(argv[3]) == '1')
        grad = true;
    else if (stoi(argv[3]) == '0')
        grad = false;
    else {
        cerr << "Grad must be 1 or 0 and you entered " << stoi(argv[3]) << endl;
        return 1;
    }

    if (0 > stoi(argv[4]) or stoi(argv[4]) > 7) {
        cerr << "Incorrect type of algorithm, it must be between 0 to 7" << endl;
        return 1;
    }
    uchar bitRate = stoi(argv[5]);
    if (bitRate > 8 or bitRate < 1) {
        cerr << "Incorrect bitrate of result, it must be between 1 to 8" << endl;
        return 1;
    }
    //double gamma = stod(argv[6]);
}