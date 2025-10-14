#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    int arr[10000];
    for(int n = 0; n < 10000; n++)
        arr[n] = rand() % 100000;
    
    
    
    return 0;
}