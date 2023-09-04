#include "sort.hpp"

using namespace std;

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

    return 0;
}