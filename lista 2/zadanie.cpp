#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

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
        
        int mid = high - 1;
        
        if(arr[mid] > arr[high])
            swap(arr[mid], arr[high]);
        
        int pivot1 = arr[mid];
        int pivot2 = arr[high];
        
        int i = low;
        int j = low;
    
        for (int n = low; n < high - 1; n++) {
            if (arr[n] <= pivot1) {
                swap(arr[i], arr[j]);
                if(n != j)
                    swap(arr[i], arr[n]);
                i++;
                j++;
            } else if(arr[n] <= pivot2) {
                swap(arr[j], arr[n]);
                j++;
            }
        }
        
        if(j != mid)
            swap(arr[i], arr[j]);
        j++;
        swap(arr[i], arr[mid]);
        swap(arr[j], arr[high]);

        quickSort3(arr, low, i - 1);
        quickSort3(arr, i + 1, j - 1);
        quickSort3(arr, j + 1, high);
    }
}

void radixsort(int arr[], int n, int d)
{
    int m = abs(arr[0]);
    for (int i = 1; i < n; i++)
        if (abs(arr[i]) > m)
            m = abs(arr[i]);


    for (int ex = 1; m / ex > 0; ex *= d) {
        int output[n];
        int *count = new int[(2 * d) - 1] { 0 };

        for (int i = 0; i < n; i++)
            count[((arr[i] / ex) % d) + d - 1]++;
    
        for (int i = 1; i < 2 * d - 1; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            output[count[((arr[i] / ex) % d) + d - 1] - 1] = arr[i];
            count[((arr[i] / ex) % d) + d - 1]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }
}


int main()
{
	int size = 1000;
    srand(time(NULL));
    int arr[size];
    for(int n = 0; n < size; n++)
        arr[n] = (rand() % (size * 10)) - (size * 5);
        
    
  	//quickSort(arr, 0, size-1);
  	//quickSort3(arr, 0, size-1);
  	//radixsort(arr, size, 10);

    for(int n = 1; n < size; n++)
          cout << arr[n] << "\t" << (arr[n-1]<=arr[n]) << endl;
 
  	return 0;
}