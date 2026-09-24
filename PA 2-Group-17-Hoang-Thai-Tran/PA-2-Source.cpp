#include <iostream>
#include <random> 
#include <vector>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

const int Num_Arrays = 9;

struct BenchmarkResult {
    int n;
    double nlogn;
    double timeSec;
    int roundedX;
    int expY;
};

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<double>& arr, int left, int mid, int right){
                         
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<double> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Begin is for left index and end is right index of the sub-array of arr to be sorted
void mergeSort(vector<double>& arr, int left, int right){
    
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Generates a vector of random doubles of specified size 
vector<double> generateRandomDoubles(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(1.0, 1000000.0); // Random doubles between 1 and 1,000,000

    vector<double> array(size);
    for (int i = 0; i < size; ++i) {
        array[i] = dist(gen);
    }
    return array;
}

// Runs benchmarks for the specified sizes and returns the results
vector<BenchmarkResult> runBenchmarks(const vector<int>& sizes, vector<vector<double>>& originalArrays, vector<vector<double>>& sortedArrays) {
    vector<BenchmarkResult> results;

    // Run benchmarks for each array
    for (size_t i = 0; i < sizes.size(); ++i) {
        int n = sizes[i];
        vector<double> original = generateRandomDoubles(n);
        vector<double> sorted = original; // Copy original array

        // Measure time taken for merge sort
        auto start = chrono::high_resolution_clock::now();
        mergeSort(sorted, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = end - start;
        double timeSec = elapsed.count();

        // Make sure timeSec is not zero or negative
        if (timeSec <= 0.0) timeSec = 1e-9;

        // Calculate performance 
        double nlogn = n * log2(n);
        double ratio = nlogn / timeSec;

        // Calculate Scientific Notation
        double exponent = floor(log10(ratio));
        double sigfig = ratio / pow(10.0, exponent);
        int roundedX = static_cast<int>(round(sigfig));
        int expY = static_cast<int>(exponent);

        if (roundedX == 10) { roundedX = 1; expY += 1; }

        originalArrays.push_back(move(original));
        sortedArrays.push_back(move(sorted));

        results.push_back({n, nlogn, timeSec, roundedX, expY});

        // Output the results to console
        cout << "Array_" << (i + 1) << " (n = " << n << "): " << fixed << setprecision(6) << timeSec << " s | Metric: " << roundedX << "E" << expY << "\n";
    }

    return results;
}

// Exports the benchmark results to a CSV file
void exportToCSV(const vector<BenchmarkResult>& results, const string& filename) {
    ofstream csvFile(filename);

    csvFile << "Array,Input size n for Array_i,Value of n*logn,Time spent (seconds),Value of (n*logn)/time\n";

    for (size_t i = 0; i < results.size(); ++i) {
        const auto& result = results[i];
        csvFile << "Array_" << (i + 1) << "," << result.n << "," << fixed << setprecision(4) << result.nlogn << "," << scientific << setprecision(6) << result.timeSec << "," << result.roundedX << "E" << result.expY << "\n";    }
    csvFile.close();
}

// Runs the user interface for viewing original and sorted arrays
void runInterface(const vector<vector<double>>& originalArrays, const vector<vector<double>>& sortedArrays) {
    int choice = 0;
    while (true) {
        cout << "----------------------------------------\n";
        cout << "Menu:\n";
        for (size_t i = 0; i < originalArrays.size(); ++i) {
            cout << "  [" << (i + 1) << "] View Array_" << (i + 1) 
                 << " (n = " << originalArrays[i].size() << ")\n";
        }
        cout << "  [0] Exit\n";
        cout << "----------------------------------------\n";
        cout << "Select an array index (1-9) or 0 to exit: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a number.\n\n";
            continue;
        }

        if (choice == 0) {
            cout << "\nExiting menu.\n";
            break;
        } else if (choice >= 1 && choice <= static_cast<int>(originalArrays.size())) {
            int idx = choice - 1;
            int n = originalArrays[idx].size();
            cout << "\nOriginal Array_" << choice << " (" << n << " elements): \n";

        for (int j = 0; j < n; ++j) {
            cout << fixed << setprecision(2) << originalArrays[idx][j] << " ";

        if ((j + 1) % 12     == 0)
            cout << "\n";
        }

        cout << "\n\n";
        cout << "\nSorted Array_" << choice << " (" << n << " elements):\n";

        for (int j = 0; j < n; ++j) {
            cout << fixed << setprecision(2) << sortedArrays[idx][j] << " ";

        if ((j + 1) % 12 == 0)
            cout << "\n";
        }       

        cout << "\n\n";
        } else {
            cout << "\nChoice out of range. Pick 1 through 9.\n\n";
        }
    }
}

int main() {

    // Define the sizes of the arrays to be tested
    vector<int> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};

    vector<vector<double>> originalArrays, sortedArrays;
    vector<BenchmarkResult> results = runBenchmarks(sizes, originalArrays, sortedArrays);

    exportToCSV(results, "Mergesort_Time.csv");
    
    runInterface(originalArrays, sortedArrays);

    return 0;
}