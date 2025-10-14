#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

using namespace std;

int assCount = 0, comCount = 0;
int size = 50;


void INSERTION_SORT(int arr[]) {
    for(int n = 1; n < size; n++){
        int x = arr[n];
        int m = n - 1; 
        assCount++; 
        comCount+=2;
        while(m >= 0 && arr[m] > x) {
            arr[m+1] = arr[m];
            m--;
            assCount++;
            comCount+=2;
        }
        arr[m+1] = x;
        assCount++;
    }
}

/*void INSERTION_SORT2(int arr[]) {
    for(int n = 2; n < size; n+=2){
        int x = arr[n] > arr[n-1] ? arr[n-1] : arr[n];
        int y = arr[n] > arr[n-1] ? arr[n] : arr[n-1];
        
        int m = n - 1; 
        assCount+=2; 
        comCount+=2;
        while(m >= 0 && arr[m] > x) {
            arr[m+1] = arr[m];
            m--;
            assCount+=2;
            comCount+=2;
        }
        arr[m+1] = x;
        assCount++;
    }
}*/

void merge(int arr[], int b, int m, int e) {
    int n1 = m - b + 1;
    int n2 = e - m;

    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[b + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    
    int i = 0, j = 0;
    int k = b;
    
    assCount += e - b;

    comCount+=2;
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
        comCount+=3;
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
    if(b < e) {
        int m = (b+e) / 2;
        mergeSort(arr, b, m);
        mergeSort(arr, m+1, e);
        merge(arr, b, m, e);
    }
}

void merge3(int arr[], int b, int m1, int m2, int e) {
    int n1 = m1 - b + 2;
    int n2 = m2 - m1 + 1;
    int n3 = e - m2 + 1;

    int L[n1], M[n2], R[n3];
    
    for (int i = 0; i < n1-1; i++)
        L[i] = arr[b + i];
    for (int j = 0; j < n2-1; j++)
        M[j] = arr[m1 + 1 + j];
    for (int k = 0; k < n3-1; k++)
        R[k] = arr[m2 + 1 + k];
    
    L[n1-1] = INT_MAX;
    M[n2-1] = INT_MAX;
    R[n3-1] = INT_MAX;
    
    int i = 0, j = 0, k = 0;
    
    assCount += 3 + e - b;
    comCount++;

    for(int index = b; index <= e; index++) {
        if(L[i] < M[j]) {
            if(L[i] < R[k]) {
                arr[index] = L[i++];
            } else {
                arr[index] = R[k++];
            }
        } else {
           if(M[j] < R[k]) {
                arr[index] = M[j++];
            } else {
                arr[index] = R[k++];
            } 
        }
        assCount++;
        comCount+=3;
    }
}

void mergeSort3(int arr[], int b, int e) {
    if(b < e) {
        int m1 = b + (e-b) / 3;
        int m2 = b + (e-b) * 2 / 3;
        mergeSort3(arr, b, m1);
        mergeSort3(arr, m1+1, m2);
        mergeSort3(arr, m2+1, e);
        merge3(arr, b, m1, m2, e);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;
        
    comCount+=2;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        assCount+=3;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        assCount+=3;
        heapify(arr, i, 0);
    }
}

int main()
{
    srand(time(NULL));
    int arr[size];
    for(int n = 0; n < size; n++)
        arr[n] = size + 100 - n;
        //arr[n] = rand() % (size * 10);
    
    //INSERTION_SORT(arr);
    //mergeSort(arr, 0, size - 1);
    mergeSort3(arr, 0, size - 1);
    //heapSort(arr, size);
    
    for(int n = 0; n < size; n++)
        cout << arr[n] << endl;
    
    cout << "Assing " << assCount << " comp " << comCount;
    
    return 0;
}