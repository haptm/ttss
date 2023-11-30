#include<iostream>
#include<omp.h>
#include<windows.h>
#include<vector>

using namespace std;

void randomVector(vector<double> &v, int n) {
    v.resize(n);
    for(int i = 0; i < n; i++) {
        v[i] = rand();
    }
}

void sumReduction(vector<double> &v, int n) {
    double sum = 0;
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }
    QueryPerformanceCounter(&end);
    double elapsed_time = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Sum: " << sum << endl;
    cout << "Time: " << elapsed_time << " seconds" << endl;
}

void productReduction(vector<double> &v, int n) {
    long long product = 1;
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    #pragma omp parallel for reduction(*:product)
    for(int i = 0; i < n; i++) {
        product *= v[i];
    }
    QueryPerformanceCounter(&end);
    double elapsed_time = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Product: " << product << endl;
    cout << "Time: " << elapsed_time << " seconds" << endl;
}

void sum(vector<double> &v, int n) {
    double sum = 0;
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    for(int i = 0; i < n; i++) {
        sum += v[i];
    }
    QueryPerformanceCounter(&end);
    double elapsed_time = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Sum: " << sum << endl;
    cout << "Time: " << elapsed_time << " seconds" << endl;
}

void product(vector<double> &v, int n) {
    long long product = 1;
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    for(int i = 0; i < n; i++) {
        product *= v[i];
    }
    QueryPerformanceCounter(&end);
    double elapsed_time = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Product: " << product << endl;
    cout << "Time: " << elapsed_time << " seconds" << endl;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    cin.ignore();
    vector<double> v;
    randomVector(v, n);
    sumReduction(v, n);
    sum(v, n);
    productReduction(v, n);
    product(v, n);
}