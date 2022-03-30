// author Ryan Litwin
// version 9-20-20
// Project 3, project3_Litwin_rpl0010.cpp
// compile using g++ project3_Litwin_rpl0010.cpp -o a.out
// run using /.a.out

#include <fstream>
#include <iostream>
using namespace std;
//global variable
const int MAX_SIZE = 100;
//reads the input files
int readFile(int inputArray[], ifstream& instream) {
    int index = 0;

    instream >> inputArray[index];
    while (!instream.eof()) {
        index++;
        instream >> inputArray[index];
    }
    return index;
}

void merge_numbers(int array[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
   
    int* Left = new int[n1];
    int* Right = new int[n2];

    for (i = 0; i < n1; i++) {
        Left[i] = array[left + i];
    }

    for (j = 0; j < n2; j++) {
        Right[j] = array[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            array[k] = Left[i];
            i++;
        }
        else {
            array[k] = Right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        array[k] = Left[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = Right[j];
        j++;
        k++;
    }

    delete[] Left;
    delete[] Right;
}

void merge_sort(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        merge_sort(array, left, middle);
        merge_sort(array, middle + 1, right);
        merge_numbers(array, left, middle, right);
    }
}

int sort(int array1[], int array1_size, int array2[], int array2_size, int output_array[]) {
    int output_array_size = array1_size + array2_size;
    for (int i = 0; i < array1_size; i++) {
        output_array[i] = array1[i];
    }

    for (int i = 0; i < array2_size; i++) {
        output_array[i + array1_size] = array2[i];
    }

    merge_sort(output_array, 0, output_array_size - 1);

    return output_array_size;
}
//writes .txt files
void write_file(int output_array[], int output_array_size) {
    ofstream outstream;
    string output_filename;
    cout << "Enter the output file name: ";
    cin >> output_filename;
    outstream.open((char*)output_filename.c_str());
    for (int i = 0; i < output_array_size; i++) {
        outstream << output_array[i] << "\n";
    }
    outstream.close();
    cout << "*** Please check the new file - " << output_filename << " ***\n";
}
//main function
int main() {
    int array1[MAX_SIZE];
    int array1_size;
    int array2[MAX_SIZE];
    int array2_size;

    cout << endl << "*** Welcome to Ryan's sorting program ***\n";
    ifstream instream;
    string filename_1;
    bool valid_file_1 = false;
    while (!valid_file_1) {
        cout << "Enter the first input file name: ";
        cin >> filename_1;
        instream.open((char*)filename_1.c_str());
        valid_file_1 = instream.good();
        if (!valid_file_1) {
            cout << "Error : The filename is not valid.\n";
            cout << endl;
        }
    }

    array1_size = readFile(array1, instream);
    instream.close();

    cout << "The list of " << array1_size << " numbers in file " << filename_1 << " is:\n";
    for (int i = 0; i < array1_size;i++) {
        cout << array1[i] << "\n";
    }
    cout << endl;

    string filename_2;
    bool valid_file_2 = false;
    while (!valid_file_2) {
        cout << "Enter the second input file name: ";
        cin >> filename_2;
        instream.open((char*)filename_2.c_str());
        valid_file_2 = instream.good();
        if (!valid_file_2) {
            cout << "Error: The filename is not valid.\n";
            cout << endl;
        }
    }

    array2_size = readFile(array2, instream);
    instream.close();
    cout << "The list of " << array2_size << " numbers in file " << filename_2 << " is:\n";
    for (int i = 0; i < array2_size; i++) {
        cout << array2[i] << "\n";
    }
    cout << endl;

    int output_array[MAX_SIZE];
    int output_array_size = sort(array1, array1_size, array2, array2_size, output_array);

    cout << "The sorted list of " << output_array_size <<" numbers is:";
    for (int i = 0; i < output_array_size; i++) {
        cout << " " << output_array[i];
    }
    cout << endl;

    write_file(output_array, output_array_size);
    cout << "*** Goodbye. ***" << endl;
    return 0;
}