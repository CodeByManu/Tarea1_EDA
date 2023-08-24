#include <iostream>
#include <fstream>
#include <random>

#define N 10

using namespace std;

void InsertSort(int *);

void Merge(int *, int, int, int);

void MergeSort(int *, int, int);

int Split(int *, int, int);

void QuickSort(int *, int, int);

void BucketSort(int *, int);

void RadixSort();

int main(int argc, char *argv[]){
    string ifile_name = argv[1];
    char alg = *argv[2];
    int A[10];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 10);
    
    for (int i = 0; i < 10; i++) A[i] = dis(gen);
    for (int i = 0; i < 10; i++) cout << A[i] << ", ";
    cout << endl;
    InsertSort(A);
    for (int i = 0; i < 10; i++) cout << A[i] << ", ";
    
    // ifstream ifile(ifile_name);
    // ofstream ofile(ifile_name+".sorted");
}

void InsertSort(int *A){
    for (int i = 1; i <= N; i++) {
        int elem = A[i];
        int j = i-1;
        while (j >= 0 && elem < A[j]) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = elem;
    }
}

void Merge(int *A, int i, int j, int k) {
    int Aux[j-i+1] = {};
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
    for (int s = i; i <= j; s++) {
        A[s] = Aux[r];
        r++;
    }
}

void MergeSort(int *A, int i, int j) {
    int k = (i + j)/2;

    if (i < j) {
        MergeSort(A, i, k);
        MergeSort(A, k+1, j);
        Merge(A, i, j, k);
    }
}

int Split(int *A, int i, int j) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(i, j);
    int p = dis(gen);

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

void QuickSort(int *A, int i, int j) {
    if (i < j) {
        int k = Split(A, i, j);
        QuickSort(A, i, k-1);
        QuickSort(A, k+1, j);
    }
}

void BucketSort(int *A, int B) {

}

void RadixSort() {
    
}