#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

void InsertSort(vector<int>&, int);

void Merge(vector<int>&, int, int, int);

void MergeSort(vector<int>&, int, int);

int Split(vector<int>&, int, int);

void QuickSort(vector<int>&, int, int);

int MaxValue(vector<int>, int);

void RadixSort(vector<int>&, int);

int getRandomInt(int, int);

long getElapsedTime(chrono::time_point<chrono::high_resolution_clock>,
                    chrono::time_point<chrono::high_resolution_clock>);

int main(int argc, char *argv[]){
    string ifile_name = argv[1];
    char alg = *argv[2];

    int begining = ifile_name.find('_');
    int end = ifile_name.find('.');

    int size = stoi(ifile_name.substr(begining + 1, end - begining - 1));

    ifstream input_file("../../datos/"+ifile_name);
    ofstream output_file("../../datos/"+ifile_name+".sorted");

    string line;
    vector<int> A;
    int n = 0;
    while(getline(input_file, line)) {
        int rut = stoi(line);
        A.push_back(rut);
        n++;
    }

    auto t1 = chrono::high_resolution_clock::now();

    if(alg == 'I') InsertSort(A, size), cout << "InsertSort" << endl;
    else if(alg == 'M') MergeSort(A, 0, size - 1), cout << "MergeSort" << endl;
    else if(alg == 'Q') QuickSort(A, 0, size - 1), cout << "QuickSort" << endl;
    else if(alg == 'R') RadixSort(A, size), cout << "RadixSort" << endl;

    auto t2 = chrono::high_resolution_clock::now();
    cout << "Elapsed: " << getElapsedTime(t1, t2) << endl;

    for(int k: A) output_file << k << endl;
    
    input_file.close();
    output_file.close();
}

void InsertSort(vector<int>& A, int size){
    for (int i = 1; i < size; i++) {
        int elem = A[i];
        int j = i-1;
        while (j >= 0 && elem < A[j]) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = elem;
    }
}

void Merge(vector<int>& A, int i, int j, int k) {
    vector<int> Aux(j-i+1);
    int q = 0;
    int p1 = i;
    int p2 = k + 1;

    while (p1 <= k && p2 <= j) {
        if (A[p1] <= A[p2]) {
            Aux[q] = A[p1];
            p1++;
        } else {
            Aux[q] = A[p2];
            p2++;
        }
        q++;
    }
    while (p1 <= k) {
        Aux[q] = A[p1];
        p1++;
        q++;
    }
    while (p2 <= j) {
        Aux[q] = A[p2];
        p2++;
        q++;
    }
    int r = 0;
    for (int s = i; s <= j; s++) {
        A[s] = Aux[r];
        r++;
    }
}

void MergeSort(vector<int>& A,int i,int j) {
    int k = (i + j)/2;

    if (i < j) {
        MergeSort(A, i, k);
        MergeSort(A, k+1, j);
        Merge(A, i, j, k);
    }
}

int Split(vector<int>& A, int i, int j) {

    int p = getRandomInt(i, j);

    while (i < j) {
        while (i < p and A[i] <= A[p]) {
            i++;
        }
        while (j > p and A[j] >= A[p]) {
            j--;
        }
        int aux = A[i];
        A[i] = A[j];
        A[j] = aux;
        if (i == p) {
            p = j;
        } else {
            if (j == p) {
                p = i;
            }
        }
    }
    return p;
}

void QuickSort(vector<int>& A, int i, int j) {
    if (i < j) {
        int k = Split(A, i, j);
        QuickSort(A, i, k-1);
        QuickSort(A, k+1, j);
    }
}

int MaxValue(vector<int> A, int size){
    int Max = 0;
    for (int i = 0; i < size; i++){
        if (A[i] > Max) Max = A[i];
    }
    return Max;
}

void RadixSort(vector<int>& A, int size) {
    int M = MaxValue(A, size);
    for(int i  = 1; i <= M; i *= 10){
        int k = 0;
        vector<int> Aux(size);
        vector<vector<int>> B(10);
        for(int j = 0; j < size; j++){
            int d = (A[j]/i) % 10;
            B[d].push_back(j);
        }
        for(int m = 0; m < 10; m++){
            if(B[m].size() > 0){
                for(int j : B[m]){
                    Aux[k] = A[j];
                    k++;
                }
            }
        }
        for(int n = 0; n < size; n++){
            A[n] = Aux[n];
        }
    }
}

int getRandomInt(int min, int max){
    srand(time(nullptr));
    float a = rand() / static_cast<float>(RAND_MAX);
    return static_cast<int>(a * (max - min) + min + 0.5);
}

long getElapsedTime(chrono::time_point<chrono::high_resolution_clock> t1,
                    chrono::time_point<chrono::high_resolution_clock> t2) {
    auto int_ms = chrono::duration_cast<chrono::milliseconds> (t2 - t1);
    return static_cast<long> (int_ms.count());
}