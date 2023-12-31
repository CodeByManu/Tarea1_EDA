#include "sort.hpp"

void InsertSort(std::vector<int>& A, int size){
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

void Merge(std::vector<int>& A, int i, int j, int k) {
    std::vector<int> Aux(j-i+1);
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

void MergeSort(std::vector<int>& A,int i,int j) {
    int k = (i + j)/2;

    if (i < j) {
        MergeSort(A, i, k);
        MergeSort(A, k+1, j);
        Merge(A, i, j, k);
    }
}

int Split(std::vector<int>& A, int i, int j) {

    // int p = getRandomInt(i, j);
    int p = (i + j)/2;

    while (i < j) {
        while (i < p and A[i] <= A[p]) {
            i++;
        }
        while (j > p and A[j] >= A[p]) {
            j--;
        }
        // int aux = A[i];
        // A[i] = A[j];
        // A[j] = aux;
        std::swap(A[i], A[j]);
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

void QuickSort(std::vector<int>& A, int i, int j) {
    if (i < j) {
        int k = Split(A, i, j);
        QuickSort(A, i, k-1);
        QuickSort(A, k+1, j);
    }
}

int MaxValue(std::vector<int>& A, int size){
    int Max = 0;
    for (int i = 0; i < size; i++){
        if (A[i] > Max) Max = A[i];
    }
    return Max;
}

void RadixSort(std::vector<int>& A, int size) {
    int M = MaxValue(A, size);
    for(int i  = 1; i <= M; i *= 10){
        int k = 0;
        std::vector<int> Aux(size);
        std::vector<std::vector<int>> B(10);
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

long getElapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock> t1,
                    std::chrono::time_point<std::chrono::high_resolution_clock> t2) {
    auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds> (t2 - t1);
    return static_cast<long> (int_ms.count());
}