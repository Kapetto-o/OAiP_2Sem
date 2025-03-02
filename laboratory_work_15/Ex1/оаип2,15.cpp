#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
void merge(vector <int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //create temporary arrays
    vector <int> L(n1), R(n2);

    // copy data in temporary arrays

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    //sort temporary arrays
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
void main()
{
    setlocale(LC_CTYPE, "Rus");
    srand(static_cast<unsigned>(time(nullptr)));
    vector<int> A;
    int nah;
    cout << "Введите количество элементов массива: ";
    cin >> nah;
    cout << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < nah; i++) {

        A.push_back(rand());
    }
    cout << "Массив А: " << endl;
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << ' ';
    }
    cout << endl;
    vector<int>B;
    vector<int>B1;
    for (int i = 0; i < A.size(); i++) {
        if (i % 2 == 0 && i != 0) {
            B.push_back(A[i]);
            B1.push_back(A[i]);
        }
    }

    // bubble sort
    auto start_bubble = chrono::high_resolution_clock::now();
    for (int i = 0; i < B.size(); i++) {
        for (int j = i; j < B.size() - 1; j++) {
            if (B[i] > B[j]) {
                int temp = B[i];
                B[i] = B[j];
                B[j] = temp;
            }
        }
    }
    auto end_bubble = chrono::high_resolution_clock::now();
    auto duration_bubble = chrono::duration_cast<chrono::microseconds>(end_bubble - start_bubble); // calculat time taken by bubble sort
    //end

    cout << endl;
    cout << "Отсортированный массив (пузырьковая сортировка):" << endl;//print a sorted version
    for (int i = 0; i < B.size(); i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    //sort B1 array with a merge sort
    auto start_merge = chrono::high_resolution_clock::now();
    mergeSort(B1, 0, B1.size() - 1);
    auto end_merge = chrono::high_resolution_clock::now();
    auto duration_merge = chrono::duration_cast<chrono::microseconds>(end_merge - start_merge);//calculete time taked by merge sort
    cout << endl;
    cout << "Отсортированный массив (сортировка слиянием):" << endl;
    for (int i = 0; i < B1.size(); i++) {
        cout << B1[i] << ' ';
    }
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
    cout << "Время выполнения пузырьковой сортировки:\t" << duration_bubble.count() << " микросекунд" << endl;
    cout << "Время выполнения сортировки слиянием:\t\t" << duration_merge.count() << " микросекунд" << endl;
}