#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <limits>
#include <fstream>
#include <cmath>

using namespace std;

int fibRecursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return fibRecursive(n -1) + fibRecursive(n-2);
}

void writeFibonacciCSV(const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "\nError creating " << filename << "\n\n";
        return;
    }

    file << "n,F(n),T1: recursive time (ms),T2: DP time (ms),value of (2^n)/n,value of T1 / T2\n";

    vector<int> testN = {1, 2, 5, 10, 12, 15, 23, 25, 30, 36};

    for (int n : testN) {
        auto start1 = chrono::high_resolution_clock::now();
        int fn = fibRecursive(n);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> t1_duration = end1 - start1;
        double t1 = t1_duration.count();

        auto start2 = chrono::high_resolution_clock::now();
        // fibDP(n);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> t2_duration = end2 - start2;
        double t2 = t2_duration.count();

        double exp_val = pow(2.0, n) / static_cast<double>(n);
        double ratio = (t2 > 0) ? (t1 / t2) : 0.0;

        file << n << "," << fn << ",";
        file << fixed << setprecision(2) << t1 << "," << t2 << ",";
        file << scientific << setprecision(2) << exp_val << "," << ratio << "\n";
    }

    file.close();
    cout << "File saved successfully!\n";
}

void runInterface() {
    int choice = 0;
    while (true) {
        cout << "----------------------------------------\n";
        cout << "Menu:\n";
        cout << "  [1] Recursive Fib\n";
        cout << "  [2] DP Fib\n";
        cout << "  [0] Exit\n";
        cout << "----------------------------------------\n";
        cout << "Select either Recursive Fib or DP Fib or 0 to exit: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n\n";
            continue;
        }

        if (choice == 0) {
            cout << "\nExiting menu.\n";
            break;
        }

        if (choice == 1) {
            int n;
            cout << "----------------------------------------\n";
            cout << "Recursive Fib: \n";
            cout << "What is the value of n? N: ";

            if (!(cin >> n) || n < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter a non-negative number.\n\n";
                continue;
            }

            auto start = chrono::high_resolution_clock::now();
            int result = fibRecursive(n);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, milli> elapsed = end - start;

            cout << "F(" << n << ") = " << result << "\n";
            cout << fixed << setprecision(4);
            cout << "Time taken: " << elapsed.count() << " ms\n\n";

        }

        else if (choice == 2) {
            int n;
            cout << "----------------------------------------\n";
            cout << "DP Fib: \n";
            cout << "What is the value of n? N: ";

            if (!(cin >> n) || n < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter a non-negative number.\n\n";
                continue;
            }

            auto start = chrono::high_resolution_clock::now();
            // int result = fibDP(n);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, milli> elapsed = end - start;

            // cout << "F(" << n << ") = " << result << "\n";
            cout << fixed << setprecision(4);
            cout << "Time taken: " << elapsed.count() << " ms\n\n";

        }
        else {
            cout << "\nInvalid selection. Please choose 1, 2, or 0.\n\n";
        }
    }
}

int main () {

    runInterface();

    return 0;
}
