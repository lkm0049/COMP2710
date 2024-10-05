//Name: Liam Maher
//Date: 10/1/2019
//Assignment: COMP2710 Project 3
//filename: project3_Maher_lkm0049.cpp
//compile: g++ project3_Maher_lkm0049.cpp -o Project3
//run: ./Project3

#include <fstream>
#include <iostream>
#include <cstdlib> //for exit()
using namespace std;

const int MAX_SIZE = 100;

//readfile from project description did not work, this is what works for my methods
int readfile(int inputArray[], ifstream& inStream) {
    int index = 0;
    while (inStream >> inputArray[index]) { // Reads numbers until end of file
        index++;
    }
    return index;
}

void merge(int array[], int l, int m, int r) { 
    int i, j, k; 

    int x = m - l + 1; 
    int y = r - m; 

    int* left = new int[x];
    int* right = new int[y];
    for (i = 0; i < x; i++) {
        left[i] = array[l + i]; 
    }
    for (j = 0; j < y; j++) {
        right[j] = array[m + 1 + j];
    }
    i = 0;
    j = 0; 
    k = l;
    while (i < x && j < y) { 
        if (left[i] <= right[j]) { 
            array[k] = left[i]; 
            i++; 
        } 
        else { 
            array[k] = right[j]; 
            j++; 
        } 
        k++; 
    }
    while (i < x) { 
        array[k] = left[i]; 
        i++; 
        k++; 
    } 
    while (j < y) { 
        array[k] = right[j]; 
        j++; 
        k++; 
    }
    delete[] left;
    delete[] right;
} 

void mergeSort(int array[], int l, int r) 
{ 
    if (l < r) { 
        int m = l + (r - l) / 2; 
   
        mergeSort(array, l, m); 
        mergeSort(array, m + 1, r); 
  
        merge(array, l, m, r); 
    } 
}

int combine(int iArray1[], int iArray1_size, int iArray2[], int iArray2_size, int output_array[]) {
    int output_array_size = iArray1_size + iArray2_size;

    for (int i = 0; i < iArray1_size; i++) {
        output_array[i] = iArray1[i];
    }
    for (int i = 0; i < iArray2_size; i++) {
        output_array[i+iArray1_size] = iArray2[i];
    }
    mergeSort(output_array, 0, output_array_size-1);

    return output_array_size;
}


void out(int iArray3[], int iArray3_size) {
    ofstream outStream;
    string outputFileName;
    cout << "Enter the output file name: ";
    cin >> outputFileName;
    outStream.open(outputFileName.c_str());
    for (int i = 0; i < iArray3_size; i++) {
        outStream << iArray3[i] << "\n";
    }
    outStream.close();
    cout << "*** Please check the new file - " << outputFileName << " ***\n";
}
//Fuction declaration 
void out(int iArray3[], int iArray3_size);

int main() {
    int iArray1[MAX_SIZE];
    int iArray1_size;
    int iArray2[MAX_SIZE];
    int iArray2_size;

    cout << endl << "*** Welcome to Liam's sorting program ***\n";

    ifstream inStream;
    string fileName1;
    bool validFile1 = false;
    while (!validFile1) {
        cout << "Enter the first input file name: ";
        cin >> fileName1;
        inStream.open((char*)fileName1.c_str());
        validFile1 = inStream.good();
        if (!validFile1) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }
    iArray1_size = readfile(iArray1, inStream);
    inStream.close();
    cout << "The list of " << iArray1_size << " numbers in file " << fileName1 << " is:\n";
    for (int i = 0; i < iArray1_size; i++) {
        cout << iArray1[i] << "\n";
    }
    cout << endl;
    string fileName2;
    bool validFile2 = false;
    while (!validFile2) {
        cout << "Enter the second input file name: ";
        cin >> fileName2;
        inStream.open((char*)fileName2.c_str());
        validFile2 = inStream.good();
        if (!validFile2) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }
    iArray2_size = readfile(iArray2, inStream);
    inStream.close();
    cout << "The list of " << iArray2_size << " numbers in file " << fileName2 << " is:\n";
    for (int i = 0; i < iArray2_size; i++) {
        cout << iArray2[i] << "\n";
    }
    cout << endl;
    int output_array[MAX_SIZE];
    int output_array_size = combine(iArray1, iArray1_size, iArray2, iArray2_size, output_array);
    cout << "The sorted list of " << output_array_size << " numbers is:";
    for (int i = 0; i < output_array_size; i++) {
        cout << " " << output_array[i];
    }
    cout << endl;
    out(output_array, output_array_size);
    cout << "*** Goodbye. ***" << endl;
    return 0;
}









