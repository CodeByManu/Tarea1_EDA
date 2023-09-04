#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

void InsertSort(std::vector<int>&, int);
void Merge(std::vector<int>&, int, int, int);
void MergeSort(std::vector<int>&, int, int);
int Split(std::vector<int>&, int, int);
void QuickSort(std::vector<int>&, int, int);
int MaxValue(std::vector<int>&, int);
void RadixSort(std::vector<int>&, int);
int getRandomInt(int, int);
long getElapsedTime(std::chrono::time_point<std::chrono::high_resolution_clock>, std::chrono::time_point<std::chrono::high_resolution_clock>);