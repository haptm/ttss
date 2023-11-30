#include<iostream>
#include<omp.h>
#include<vector>
#include<fstream>
#include<ctime>
#include<chrono>
#include<windows.h>

using namespace std;

void randomMatrix(vector<vector<double>> &matrix, int n) {
    matrix.resize(n, vector<double>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            matrix[i][j] = rand();
        }
    }
}

void printMatrix(vector<vector<double>> matrix, int n) {
    try {
        fstream file_output("result.txt");
        if(file_output.fail()){
            throw "Failed to open this file!";      
        }

        file_output << n << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                 file_output << matrix[i][j] << " ";
            }          
            file_output << endl;
        }
    }
    catch (const char* e) {
        cout << "Exception: " << e << endl;
    }
}

void randomVector(vector<double> &vector, int n) {
    vector.resize(n);
    for(int i = 0; i < n; i++) {
        vector[i] = rand();
    }
}

void printVector(vector<double> vector, int n) {
    try {
        fstream file_output("result.txt");
        if(file_output.fail()){
            throw "Failed to open this file!";      
        }

        file_output << n << endl;
        for (int i = 0; i < n; i++) {
            file_output << vector[i] << " ";         
        }
    }
    catch (const char* e) {
        cout << "Exception: " << e << endl;
    }
}

vector<double> multiplyParallel(vector<vector<double>> matrix, vector<double> vector_1, int n) {
    vector<double> result(n);
    LARGE_INTEGER frequency, start, end;

    // Lấy tần số của performance counter
    QueryPerformanceFrequency(&frequency);

    // Lấy thời điểm bắt đầu
    QueryPerformanceCounter(&start);
    #pragma omp parallel for
    for(int i = 0; i < n; i++) {
        result[i] = 0;
        for(int j = 0; j < n; j++) {
            result[i] += matrix[i][j] * vector_1[j];
            //cout << omp_get_thread_num() << endl;
        }
    }
    printVector(result, n);
    QueryPerformanceCounter(&end);
    double elapsed_time = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Time: " << elapsed_time << " seconds" << endl;
    return result;
}

vector<double> multiply(vector<vector<double>> matrix, vector<double> vector_1, int n) {
    // clock_t start = clock();
    
    //auto start = chrono::high_resolution_clock::now();
    
    LARGE_INTEGER frequency, start, end;

    // Lấy tần số của performance counter
    QueryPerformanceFrequency(&frequency);

    // Lấy thời điểm bắt đầu
    QueryPerformanceCounter(&start);

    vector<double> result(n);
    for(int i = 0; i < n; i++) {
        result[i] = 0;
        for(int j = 0; j < n; j++) {
            result[i] += matrix[i][j] * vector_1[j];
        }
    }
    printVector(result, n);

    QueryPerformanceCounter(&end);
    double elapsed_time = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    cout << "Time: " << elapsed_time << " seconds" << endl;
    //auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double, milli> duration = end - start;
    // cout << "Time: " << duration.count() << " milliseconds" << endl;
    
    // clock_t end = clock();
    // double time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    // cout << "Time: " << time << endl;
    return result;
}

int main() {
    vector<vector<double>> matrix;
    vector<double> vector_1;
    int n;
    cout << "Enter n: ";
    cin >> n;
    cin.ignore();
    randomMatrix(matrix, n);
    randomVector(vector_1, n);
    vector<double> result = multiplyParallel(matrix, vector_1, n);
    return 0;
}