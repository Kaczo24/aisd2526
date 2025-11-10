#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <cmath>

using namespace std;

void quickSort(float arr[], int low, int high) {
    if (low < high) {

        float pivot = arr[high];
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


void quickSort3(float arr[], int low, int high) {
    if (low < high) {
        
        int mid = high - 1;
        
        if(arr[mid] > arr[high])
            swap(arr[mid], arr[high]);
        
        float pivot1 = arr[mid];
        float pivot2 = arr[high];
        
        int i = low;
        int j = low;
    
        for (int n = low; n < high - 1; n++) {
            if (arr[n] <= pivot1) {
                swap(arr[j], arr[n]);
                swap(arr[i], arr[j]);
                i++;
                j++;
            } else if(arr[n] <= pivot2) {
                swap(arr[j], arr[n]);
                j++;
            }
        }
        
        swap(arr[j], arr[mid]);
        swap(arr[i], arr[j]);
        j++;
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

template <typename T>
class List {
    private:
    struct Node {
        Node *next = nullptr, *prev = nullptr;
        T key;
        Node(T _key) : key(_key) {}
        Node(Node &other) : key(other.key), next(other.next), prev(other.prev) {}
        Node(Node &&other) : key(other.key) {
            next = other.next;
            prev = other.prev;
            other.prev = other.next = nullptr;
        }
        ~Node() {
            delete next;
            delete prev;
        }
        
    };
    Node *start = nullptr, *head = nullptr;
    
    public:
    struct Iterum {
        ~Iterum(){}
        Node *current = nullptr;
        T prev() { if(current != nullptr && current->prev != nullptr) return current->prev->key; return 0;}
        operator T() const {if(current != nullptr) return current->key; return 0; }
    };
    
    int count = 0;
    
    void push(T key) {
        count++;
        if(head == nullptr)
            head = new Node(key);
        else {
            head->next = new Node(key);
            head->next->prev = head;
            head = head->next;
        }
        if(start == nullptr)
            start = head;
    }
    
    T& operator[](int n) {
        if(n > count) return NULL;
        Node* current;
        for(int m = 0; m < n; m++) 
            current = current->head;
        return current->key;
    }
    
    void deleteIndex(int n) {
        if(n > count) return;
        Node* current;
        for(int m = 0; m < n; m++) 
            current = current->head;
        
        if(current->next != nullptr)
            current->next->prev = current->prev;
        else
            head = current->prev;
            
        if(current->prev != nullptr)
            current->prev->next = current->next;
        else
            start = current->next;
            
        delete current;
        count--;
    }
    
    bool iterate(Iterum &value) {
        if(value.current == nullptr) value.current = start;
        else value.current = value.current->next;
        return value.current != nullptr;
    }
    
    void insertionSort() {
        if(count <= 1) return;
        if(count == 2) {
            if(start->key > head->key) swap(start->key, head->key);
            return;
        }
        Node *currentHead = start->next;
        
        for(Node *currentHead = start->next; currentHead != nullptr; ) {
            Node *nextHead = currentHead->next, *sortingHead = currentHead->prev;
            
            if(sortingHead->key > currentHead->key) {
                
                currentHead->prev->next = currentHead->next;
                if(currentHead->next != nullptr)
                    currentHead->next->prev = currentHead->prev;
                else
                    head = currentHead->prev;
                
                while(sortingHead != nullptr && sortingHead->key > currentHead->key)
                    sortingHead = sortingHead->prev;
                    
                if(sortingHead == nullptr) {
                    start->prev = currentHead;
                    currentHead->prev = nullptr;
                    currentHead->next = start;
                    start = currentHead;
                }
                else {
                    currentHead->prev = sortingHead;
                    currentHead->next = sortingHead->next;
                    if(sortingHead->next != nullptr)
                        sortingHead->next->prev = currentHead;
                    else
                        head = currentHead;
                    sortingHead->next = currentHead;
                }
            }
            currentHead = nextHead;
            
        }
    }
};

void bucketSort(float arr[], int n) {
    float max = arr[0], min = arr[0];
    for (int i = 0; i < n; i++) {
        if(arr[i] > max) max = arr[i];
        if(arr[i] < min) min = arr[i];
    }
    
    List<float> b[n];
    for (int i = 0; i < n; i++) 
        b[(int)(n * (arr[i] - min) / (max - min + 1))].push(arr[i]);
    
    for (int i = 0; i < n; i++) 
        b[i].insertionSort();
    
    int index = 0;
    
    for (int i = 0; i < n; i++) {
        List<float>::Iterum val;
        while(b[i].iterate(val))
            arr[index++] = val;
    }
}

int main()
{
    srand(time(NULL));
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    
	int size = 500000, tests = 10;
    int arr[size];
	for(int d = 10; d <= 24; d++) {
	    
    	float totalTime = 0;
    	for(int t = 0; t < tests; t++) {
        
            for(int n = 0; n < size; n++)
                arr[n] = (rand() % (size * 10)) - (size * 5);
            
            auto t1 = high_resolution_clock::now();
            radixsort(arr, size, d);
            auto t2 = high_resolution_clock::now();
            
            totalTime += duration_cast<microseconds>(t2 - t1).count() / 1000.0;
    	}
        cout << d << "\t" << totalTime / tests << endl;
	}
	
	cout << "\n\n------------------\n\n";
	
	int sizes[] = {10, 50, 100, 1000, 10000, 50000, 100000};
	for(int size : sizes) {
	    
	    float quickTime = 0, quick3Time = 0, bucketTime = 0;
    	for(int t = 0; t < tests; t++) {
        
	        float arr1[size], arr2[size], arr3[size];
	        for(int n = 0; n < size; n++)
	            arr1[n] = arr2[n] = arr3[n] = ((rand() % (size * 100)) - (size * 50)) / 100.0;
            
            auto t1 = high_resolution_clock::now();
            quickSort(arr1, 0, size-1);
            auto t2 = high_resolution_clock::now();
            quickSort3(arr2, 0, size-1);
            auto t3 = high_resolution_clock::now();
            bucketSort(arr3, size);
            auto t4 = high_resolution_clock::now();
            
            quickTime += duration_cast<microseconds>(t2 - t1).count() / 1000.0;
            quick3Time += duration_cast<microseconds>(t3 - t2).count() / 1000.0;
            bucketTime += duration_cast<microseconds>(t4 - t3).count() / 1000.0;
    	}
    	cout << size << ":\tquickSort " << quickTime / tests 
    	     << "\tquickSort3 " << quick3Time / tests 
    	     << "\tbucketSort " << bucketTime / tests << endl;
	}
  	return 0;
}