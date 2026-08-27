#include <iostream>
#include <random>
#include <fstream>
#include <vector>

#include "BF_V1"
#include "BF_V2"

using namespace std;

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

    // Write results to CSV file for BF_V1
    ofstream bf1File("BF_v1_Results.csv");

    bf1File << "Number One,Number Two,Their GCD,Time Spent (Milliseconds)\n";

    vector<double> bf1Times;

    for (pair<int, int> p : numbers) {

        auto start = chrono::high_resolution_clock::now();

        int gcd = BF_v1(p.first, p.second);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, std::milli> elapsed = end - start;

        bf1Times.push_back(elapsed.count());

        bf1File << p.first << "," << p.second << "," << gcd << "," << elapsed.count() << "\n";
    }

    bf1File.close();

    // Write results to CSV file for BF_V2
    ofstream bf2File("BF_v2Results.csv");

    bf2File << "Number One,Number Two,Their GCD,Time Spent (Milliseconds)\n";

    vector<double> bf2Times;

    for (pair<int, int> p : numbers) {

        auto start = chrono::high_resolution_clock::now();

        int gcd = BF_v2(p.first, p.second);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, std::milli> elapsed = end - start;

        bf2Times.push_back(elapsed.count());

        bf2File << p.first << "," << p.second << "," << gcd << "," << elapsed.count() << "\n";
    }

    bf2File.close();


    return 0;
}