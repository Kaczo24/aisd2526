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
	int size = 500;
    srand(time(NULL));
    int arr[size];
    List<int> list;
    float farr[size];
    
    for(int n = 0; n < size; n++) {
        farr[n] = ((rand() % (size * 100)) - (size * 50)) / 100.0;
        list.push(rand() % (size * 10));
        arr[n] = (rand() % (size * 10)) - (size * 5);
    }
        
    bucketSort(farr, size);
    list.insertionSort();
  	//quickSort(arr, 0, size-1);
  	//quickSort3(arr, 0, size-1);
  	//radixsort(arr, size, 10);


    List<int>::Iterum val;
        while(list.iterate(val))
            cout << val << "\t" << (val.prev()<=val) << endl;
    
    for(int n = 1; n < size; n++)
        cout << farr[n] << "\t" << (farr[n-1] <= farr[n]) << endl;
        //cout << arr[n] << "\t" << (arr[n-1]<=arr[n]) << endl;
 
  	return 0;
}