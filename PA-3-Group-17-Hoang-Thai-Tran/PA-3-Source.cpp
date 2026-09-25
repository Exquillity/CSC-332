// CSC 332 - Programming Assignment 3
// Group 17
// Hoang, Thai, Tran

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <limits>
#include <fstream>
#include <cmath>

using namespace std;

// Calculates the nth Fibonacci number using recursion
int fibRecursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return fibRecursive(n -1) + fibRecursive(n-2);
}

// Calculates the nth Fibonacci number using dynamic programming
int fibDP(int n) {
    if (n <= 1) {
        return 1;
    }

    // Store Fibonacci numbers in a vector for dynamic programming
    vector<int> fib(n + 1);

    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    // Return the nth Fibonacci number
    return fib[n];
}
// Writes Fibonacci results to a CSV file
void writeFibonacciCSV(const string& filename) {
    ofstream file(filename);

    // Make sure the file is open before writing to it
    if (!file.is_open()) {
        cout << "\nError creating " << filename << "\n\n";
        return;
    }

    // Write the header for the CSV file
    file << "n,F(n),T1: recursive time (ns),T2: DP time (ns),value of (2^n)/n,value of T1 / T2\n";

    // Test values of n for Fibonacci calculations
    vector<int> testN = {1, 2, 5, 10, 12, 15, 23, 25, 30, 36};

    for (int n : testN) {
        // Measure the time taken for the recursive Fibonacci calculation
        auto start1 = chrono::high_resolution_clock::now();
        int fn = fibRecursive(n);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double, nano> t1_duration = end1 - start1;
        double t1 = t1_duration.count();

        // Measure the time taken for the dynamic programming Fibonacci calculation
        auto start2 = chrono::high_resolution_clock::now();
        fibDP(n);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double, nano> t2_duration = end2 - start2;
        double t2 = t2_duration.count();

        // Calculate the expected value of (2^n)/n and the ratio of T1 to T2
        double exp_val = pow(2.0, n) / static_cast<double>(n);
        double ratio = (t2 > 0) ? (t1 / t2) : 0.0;

        file << n << "," << fn << ",";
        // Write T1 and T2 in fixed-point notation with 2 decimal places
        file << fixed << setprecision(2) << t1 << "," << t2 << ",";
        file << defaultfloat;
        // Write the expected value and ratio in scientific notation with 2 decimal places
        file << scientific << setprecision(2) << exp_val << "," << ratio << "\n";
    }

    file.close();
}

// Function to run the user interface for Fibonacci calculations
void runInterface() {
    int choice = 0;
    // Loop until the user chooses to exit
    while (true) {
        cout << "----------------------------------------\n";
        cout << "Menu:\n";
        cout << "  [1] Recursive Fib\n";
        cout << "  [2] DP Fib\n";
        cout << "  [0] Exit\n";
        cout << "----------------------------------------\n";
        cout << "Select either Recursive Fib or DP Fib or 0 to exit: ";

        // Validate user input to ensure it's a number
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n\n";
            continue;
        }

        // Handle user choices
        if (choice == 0) {
            cout << "\nExiting menu.\n";
            break;
        }

        // Handle Recursive Fibonacci calculation
        if (choice == 1) {
            int n;
            cout << "----------------------------------------\n";
            cout << "Recursive Fib: \n";
            cout << "What is the value of n? N: ";

            // Validate user input to ensure it's a non-negative number
            if (!(cin >> n) || n < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter a non-negative number.\n\n";
                continue;
            }

            // Measure the time taken for the recursive Fibonacci calculation
            auto start = chrono::high_resolution_clock::now();
            int result = fibRecursive(n);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, nano> elapsed = end - start;

            // Output the result and time taken for the calculation
            cout << "F(" << n << ") = " << result << "\n";
            cout << fixed << setprecision(4);
            cout << "Time taken: " << elapsed.count() << " ns\n\n";

        }

        // Handle Dynamic Programming Fibonacci calculation
        else if (choice == 2) {
            int n;
            cout << "----------------------------------------\n";
            cout << "DP Fib: \n";
            cout << "What is the value of n? N: ";

            // Validate user input to ensure it's a non-negative number
            if (!(cin >> n) || n < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid input. Please enter a non-negative number.\n\n";
                continue;
            }

            // Measure the time taken for the dynamic programming Fibonacci calculation
            auto start = chrono::high_resolution_clock::now();
            int result = fibDP(n);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, nano> elapsed = end - start;

            // Output the result and time taken for the calculation
            cout << "F(" << n << ") = " << result << "\n";
            cout << fixed << setprecision(4);
            cout << "Time taken: " << elapsed.count() << " ns\n\n";

        }
        // Handle invalid menu selection
        else {
            cout << "\nInvalid selection. Please choose 1, 2, or 0.\n\n";
        }
    }
}

int main () {
    // Write results to CSV file for Fibonacci calculations
    writeFibonacciCSV("Fibonacci_Time.csv");
    // Run the user interface for Fibonacci calculations
    runInterface();

    return 0;
}
