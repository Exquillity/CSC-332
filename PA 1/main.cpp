#include <iostream>
#include <random>
#include <fstream>
#include "BF_V1"
#include "BF_V2"

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    ofstream file("BF_V1_Results.csv");
    file << "Number One,Number Two,Their GCD,Time Spent (Milliseconds)\n";


    for (int i = 0; i < 1000; i++) {
        int a = dist(gen);
        int b = dist(gen);

        file << a << "," << b << "," << BF_v1(a, b) << "\n";

    }
    file.close();

    return 0;
}