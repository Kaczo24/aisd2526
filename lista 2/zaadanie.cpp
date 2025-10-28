#include<iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void quickSort(int arr[], int low, int high) {
    if (low < high) {

        int pivot = arr[high];
        int i = (low - 1);
    
        for (int j = low; j <= high - 1; j++) {

            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        
        swap(arr[i + 1], arr[high]);

        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}

void quickSort3(int arr[], int low, int high) {
    if (low < high) {
        int mid = (high + low) / 2;
        
        if(arr[mid] > arr[high])
            swap(arr[mid], arr[high]);
        
        int pivot1 = arr[mid];
        int pivot2 = arr[high];
        
        int i = (low - 1);
        int j = (mid - 1);
    
        for (int n = low; n < high; n++) {
            if (arr[n] <= pivot1) {
                i++;
                swap(arr[i], arr[n]);
            } else if(arr[n] <= pivot2) {
                j++;
                swap(arr[j], arr[n]);
            }
        }
        
        swap(arr[i + 1], arr[mid]);
        swap(arr[j + 1], arr[high]);

        quickSort(arr, low, i);
        quickSort(arr, i+2, j);
        quickSort(arr, j + 2, high);
    }
}

int main()
{
	int size = 500;
    srand(time(NULL));
    int arr[size];
    for(int n = 0; n < size; n++)
        arr[n] = rand() % (size * 10);
 
  	quickSort(arr, 0, size-1);

    for(int n = 1; n < size; n++)
          cout << arr[n] << "\t" << (arr[n-1]<=arr[n]) << endl;
 
  	return 0;
}