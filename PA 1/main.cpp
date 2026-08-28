#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <vector>
#include <chrono>

#include "BF_V1"
#include "BF_V2"

using namespace std;

// Runs an algorithm on all 1,000 pairs and writes the results to a CSV file

vector<double> runAlgorithm( 
    const string& filename,
    const vector<pair<int, int>>& numbers,
    int (*algorithm)(int, int)
) {
    ofstream file(filename);

    file << "Number One,Number Two,Their GCD,Time Spent (Milliseconds)\n";

    vector<double> times;

    for (pair<int, int> p : numbers) {

        auto start = chrono::high_resolution_clock::now();

        int gcd = algorithm(p.first, p.second);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;

        times.push_back(elapsed.count());

        file << p.first << "," << p.second << "," << gcd << "," << elapsed.count() << "\n";
    }

    file.close();

    return times;
}

// Writes the statistics for an algorithm to a CSV file

void writeStatistics (string filename, vector<double> times) {
    sort(times.begin(), times.end());

    double minimum = times[0];
    double maximum = times[times.size() -1];

    double total = 0; 
    for (double time : times) { 
        total += time; 
    }

    double average = total / times.size(); 

    double median; 

    if (times.size() % 2 == 0) { 
        median = (times[times.size() / 2 - 1] + times[times.size() / 2]) / 2; 
    } 
    else { 
        median = times[times.size() / 2]; 
    } 

    ofstream file(filename); 

    file << "Statistics,Milliseconds\n"; 
    file << "Maximum Time," << maximum << "\n"; 
    file << "Minimum Time," << minimum << "\n"; 
    file << "Average Time," << average << "\n"; 
    file << "Median Time," << median << "\n";

    file.close();
}

// Calculates the average time saved when using 2 different algorithms
double averageSavedTime(const vector<double>& algorithmA,const vector<double>& algorithmB,int& count) {

    double totalSaved = 0;
    count = 0;

    for (size_t i = 0; i < algorithmA.size(); i++) {

        if (algorithmA[i] < algorithmB[i]) {

            totalSaved += algorithmB[i] - algorithmA[i];
            count++;
        }
    }

    if (count == 0) {
        return 0;
    }

    return totalSaved / count;
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    vector<pair<int, int>> numbers;


    for (int i = 0; i < 1000; i++) {
        int a = dist(gen);
        int b = dist(gen);

        numbers.push_back({a, b});

    }

    // Run BF_v1
    vector<double> bf1Times = runAlgorithm("BF_v1_Results.csv", numbers, BF_v1);
    writeStatistics( "BF_v1_Statistics.csv", bf1Times);

    // Run BF_v2
    vector<double> bf2Times = runAlgorithm("BF_v2_Results.csv", numbers, BF_v2);
    writeStatistics( "BF_v2_Statistics.csv", bf2Times);

    /*
    // Run OE
    vector<double> OETimes = runAlgorithm("OE_Results.csv", numbers, OE);
    writeStatistics( "OE_Statistics.csv", OETimes );

    // Run SE
    vector<double> SETimes = runAlgorithm("SE_Results.csv", numbers, SE);
    writeStatistics( "SE_Statistics.csv", SETimes );

    */
    return 0;
}