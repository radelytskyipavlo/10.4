#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;

void Create(char* filename);
void Print(char* filename);
void CalculateAndWrite(char* filename, char* ofilename);

int main() {
    int choice;
    char filename[101];

    do {
        cout << "--------------------------\n";
        cout << "Menu\n";
        cout << "[1] - Enter and save information\n";
        cout << "[2] - Load and display information\n";
        cout << "[3] - Calculate and write average\n";
        cout << "[0] - Quit\n";
        cout << "--------------------------\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Entering and saving:\n";
            cin.ignore(); 
            cout << "Enter a file name: ";
            cin.getline(filename, sizeof(filename));
            Create(filename);
            break;

        case 2:
            cout << "Output of information:\n";
            cin.ignore();
            cout << "Enter a file name: ";
            cin.getline(filename, sizeof(filename));
            Print(filename);
            break;

        case 3:
            cin.ignore();
            char ofilename[101];
            cout << "Enter a file name: ";
            cin.getline(filename, sizeof(filename));
            cout << "Enter the name of the output file: ";
            cin.getline(ofilename, sizeof(ofilename));
            CalculateAndWrite(filename, ofilename);
            break;

        case 0:
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}

void Create(char* filename) {
    ofstream f(filename);
    if (!f) {
        cerr << "Error opening file '" << filename << "'" << endl;
        return;
    }

    char ch;
    do {
        cout << "Enter numbers and characters (separated by space): ";
        string line;
        getline(cin, line);
        f << line << endl;

        cout << "Continue? (Y/N) ";
        cin >> ch;
        cin.ignore(); 
    } while (ch == 'Y' || ch == 'y');

    f.close();
}

void Print(char* filename) {
    ifstream f(filename);
    if (!f) {
        cerr << "Error opening file '" << filename << "'" << endl;
        return;
    }

    string line;
    while (getline(f, line)) {
        cout << line << endl;
    }

    f.close();
}

void CalculateAndWrite(char* filename, char* ofilename) {
    ifstream infile(filename);
    ofstream outfile(ofilename);
    if (!infile || !outfile) {
        cerr << "Error opening files" << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        double sum = 0;
        double product = 1;
        int count = 0;
        string token;
        vector<double> numbers;

        while (iss >> token) {
            try {
                double num = stod(token);
                sum += num;
                product *= num;
                count++;
                numbers.push_back(num);
            }
            catch (...) {
                continue; 
            }
        }

        if (count > 0) {
            double arithmetic_mean = sum / count;
            double geometric_mean = pow(product, 1.0 / count);
            outfile << "Numbers: ";
            for (double num : numbers) {
                outfile << num << " ";
            }
            outfile << ", Arithmetic Mean: " << arithmetic_mean << ", Geometric Mean: " << geometric_mean << endl;
        }
        else {
            outfile << "No numbers found in the line" << endl;
        }
    }

    infile.close();
    outfile.close();
}
