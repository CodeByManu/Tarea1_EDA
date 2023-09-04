#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

vector<int> InsertSort(vector<int>, int);

vector<int> Merge(vector<int>, int, int, int);

vector<int> MergeSort(vector<int>, int, int);

int Split(vector<int>&, int, int);

vector<int> QuickSort(vector<int>&, int, int);

int MaxValue(vector<int>, int);

vector<int> RadixSort(vector<int>, int);

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

    if(alg == 'I') A = InsertSort(A, size), cout << "InsertSort" << endl;
    else if(alg == 'M') A = MergeSort(A, 0, size - 1), cout << "MergeSort" << endl;
    else if(alg == 'Q') A = QuickSort(A, 0, size - 1), cout << "QuickSort" << endl;
    else if(alg == 'R') A = RadixSort(A, size), cout << "RadixSort" << endl;

    auto t2 = chrono::high_resolution_clock::now();
    cout << "Elapsed: " << getElapsedTime(t1, t2) << endl;

    for(int k: A) output_file << k << endl;
    
    input_file.close();
    output_file.close();
}

vector<int> InsertSort(vector<int> A, int size){
    for (int i = 1; i < size; i++) {
        int elem = A[i];
        int j = i-1;
        while (j >= 0 && elem < A[j]) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = elem;
    }
    return A;
}

vector<int> Merge(vector<int> A, int i, int j, int k) {
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
    return A;
}

vector<int> MergeSort(vector<int> A,int i,int j) {
    int k = (i + j)/2;

    if (i < j) {
        A = MergeSort(A, i, k);
        A = MergeSort(A, k+1, j);
        A = Merge(A, i, j, k);
    }
    return A;
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

vector<int> QuickSort(vector<int>& A, int i, int j) {
    if (i < j) {
        int k = Split(A, i, j);
        A = QuickSort(A, i, k-1);
        A = QuickSort(A, k+1, j);
    }
    return A;
}

int MaxValue(vector<int> A, int size){
    int Max = 0;
    for (int i = 0; i < size; i++){
        if (A[i] > Max) Max = A[i];
    }
    return Max;
}

vector<int> RadixSort(vector<int> A, int size) {
    int M = MaxValue(A, size);
    for(int i  = 1; i <= M; i *= 10){
        int k = 0;
        int Aux[size];
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
    return A;
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