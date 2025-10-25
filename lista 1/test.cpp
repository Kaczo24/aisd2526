#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <tuple>
#include <vector>

using namespace std;

long assCount = 0, comCount = 0;


void insertionSort(int arr[], int _, int e) {
    for (int n = 1; n < e; n++) {
        int x = arr[n];
        int m = n - 1;
        assCount++;
        comCount += 2;
        while (m >= 0 && arr[m] > x) {
            arr[m + 1] = arr[m];
            m--;
            assCount++;
            comCount += 2;
        }
        arr[m + 1] = x;
        assCount++;
    }
}

void insertionSort2(int arr[], int _, int e) {
    for (int n = 2; n < e; n += 2) {
        int x = arr[n] > arr[n - 1] ? arr[n - 1] : arr[n];
        int y = arr[n] > arr[n - 1] ? arr[n] : arr[n - 1];

        int m = n - 2;
        assCount += 2;
        comCount++;
        while (m >= 0 && arr[m] > y) {
            arr[m + 2] = arr[m];
            m--;
            assCount++;
            comCount += 2;
        }
        arr[m + 2] = y;
        arr[m + 1] = arr[m];
        assCount += 2;
        while (m >= 0 && arr[m] > x) {
            arr[m + 1] = arr[m];
            m--;
            assCount++;
            comCount += 2;
        }
        arr[m + 1] = x;
        assCount++;
        if (n == e - 2)n--;
    }
}

void merge(int arr[], int b, int m, int e) {
    int n1 = m - b + 1;
    int n2 = e - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[b + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];


    int i = 0, j = 0;
    int k = b;

    assCount += e - b;

    comCount += 2;
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
        assCount++;
        comCount += 3;
    }

    comCount++;
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        assCount++;
        comCount++;
    }

    comCount++;
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        assCount++;
        comCount++;
    }
}

void mergeSort(int arr[], int b, int e) {
    e--;
    if (b < e) {
        int m = (b + e) / 2;
        mergeSort(arr, b, m + 1);
        mergeSort(arr, m + 1, e + 1);
        merge(arr, b, m, e);
    }
}

void merge3(int arr[], int b, int m1, int m2, int e) {
    int n1 = m1 - b + 2;
    int n2 = m2 - m1 + 1;
    int n3 = e - m2 + 1;

    int* L = new int[n1];
    int* M = new int[n2];
    int* R = new int[n3];

    for (int i = 0; i < n1 - 1; i++)
        L[i] = arr[b + i];
    for (int j = 0; j < n2 - 1; j++)
        M[j] = arr[m1 + 1 + j];
    for (int k = 0; k < n3 - 1; k++)
        R[k] = arr[m2 + 1 + k];

    L[n1 - 1] = INT_MAX;
    M[n2 - 1] = INT_MAX;
    R[n3 - 1] = INT_MAX;

    int i = 0, j = 0, k = 0;

    assCount += 3 + e - b;
    comCount++;

    for (int index = b; index <= e; index++) {
        if (L[i] < M[j]) {
            if (L[i] < R[k]) {
                arr[index] = L[i++];
            }
            else {
                arr[index] = R[k++];
            }
        }
        else {
            if (M[j] < R[k]) {
                arr[index] = M[j++];
            }
            else {
                arr[index] = R[k++];
            }
        }
        assCount++;
        comCount += 3;
    }
}

void mergeSort3(int arr[], int b, int e) {
    e--;
    if (b < e) {
        int m1 = b + (e - b) / 3;
        int m2 = b + (e - b) * 2 / 3;
        mergeSort3(arr, b, m1 + 1);
        mergeSort3(arr, m1 + 1, m2 + 1);
        mergeSort3(arr, m2 + 1, e + 1);
        merge3(arr, b, m1, m2, e);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    comCount += 2;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        assCount += 3;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int _, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        assCount += 3;
        heapify(arr, i, 0);
    }
}

void heapify3(int arr[], int n, int i) {
    int largest = i;
    int l = 3 * i + 1;
    int m = 3 * i + 2;
    int r = 3 * i + 3;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (m < n && arr[m] > arr[largest])
        largest = m;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    comCount += 3;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        assCount += 3;
        heapify3(arr, n, largest);
    }
}

void heapSort3(int arr[], int _, int n) {
    for (int i = n / 3; i >= 0; i--)
        heapify3(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        assCount += 3;
        heapify3(arr, i, 0);
    }
}

vector<tuple<long, long>> Test(int sizes[], int sizeCount, int testNumber, void (*sort)(int[], int, int)) {
    vector<tuple<long, long>> output;

    for (int s = 0; s < sizeCount; s++)
    {
        int arraySize = sizes[s];

        int* arr = new int[arraySize];
        long avgAssCount = 0, avgComCount = 0;

        for (int m = 0; m < testNumber; m++) {
            for (int n = 0; n < arraySize; n++)
                arr[n] = rand() % (arraySize * 10);

            assCount = 0; comCount = 0;
            sort(arr, 0, arraySize);
            avgAssCount += assCount, avgComCount += comCount;

            /*bool isWorking = true;
            for (int n = 1; n < arraySize; n++) {
                if (arr[n] < arr[n - 1]) {
                    isWorking = false;
                    break;
                }
            }
            cout << isWorking ? "1" : "0";
        }
        cout << endl;*/ }

        avgAssCount /= testNumber; avgComCount /= testNumber;
        output.push_back({ avgAssCount, avgComCount });
    }
    return output;
}

int main()
{
    srand(time(NULL));


    int sizes[] = { 10, 100, 1000, 5000, 10000, 50000}, sizeCount = 6;
    
    auto sortingMethods = { insertionSort, insertionSort2, mergeSort, mergeSort3, heapSort, heapSort3 };
    string sortingNames[] = { "insertionSort", "insertionSort2", "mergeSort", "mergeSort3", "heapSort", "heapSort3" };
    int index = 0;
    for (auto sort : sortingMethods) {

        long a, b;
        auto tup = tie(a, b);
        auto out = Test(sizes, sizeCount, 10, sort);
        
        cout << sortingNames[index++] << endl << "Array Size: \t\t";
        for (int m = 0; m < sizeCount; m++)
            cout << sizes[m] << "\t\t";
        cout << endl << "Assignment Count: \t";
        for (int m = 0; m < sizeCount; m++) {
            tup = out[m];
            cout << a << (a < 10000000 ? "\t\t" : "\t");
        }
        cout << endl << "Comparison Count: \t";
        for (int m = 0; m < sizeCount; m++) {
            tup = out[m];
            cout << b << (b < 10000000 ? "\t\t" : "\t");
        }
        cout << endl << endl << endl;
    }
    getchar();
    return 0;
}