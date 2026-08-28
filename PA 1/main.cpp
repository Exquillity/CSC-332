#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <chrono>

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
    /*
    // Write results to CSV file for OE
    ofstream OEFile("OE_Results.csv");

    OEFile << "Number One,Number Two,Their GCD,Time Spent (Milliseconds)\n";

    vector<double> OETimes;

    for (pair<int, int> p : numbers) {

        auto start = chrono::high_resolution_clock::now();

        int gcd = OE(p.first, p.second);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, std::milli> elapsed = end - start;

        OETimes.push_back(elapsed.count());

        OEFile << p.first << "," << p.second << "," << gcd << "," << elapsed.count() << "\n";
    }

    OEFile.close();

    // Write results to CSV file for SE
    ofstream SEFile("SE_Results.csv");

    SEFile << "Number One,Number Two,Their GCD,Time Spent (Milliseconds)\n";

    vector<double> SETimes;

    for (pair<int, int> p : numbers) {

        auto start = chrono::high_resolution_clock::now();

        int gcd = SE(p.first, p.second);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, std::milli> elapsed = end - start;

        SETimes.push_back(elapsed.count());

        SEFile << p.first << "," << p.second << "," << gcd << "," << elapsed.count() << "\n";
    }

    SEFile.close();

    */
    return 0;
}