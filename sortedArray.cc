#include<bits/stdc++.h>
using namespace std;

int binarySearch(int arr[], int low, int high, int key)
{
        if (high < low)
                return -1;
        int mid = (low + high) / 2; /*low + (high - low)/2;*/
        if (key == arr[mid])
                return mid;
        if (key > arr[mid])
                return binarySearch(arr, (mid + 1), high, key);
        return binarySearch(arr, low, (mid - 1), key);
}

// Inserts a key in arr[] of given capacity. n is current
// size of arr[]. This function returns n+1 if insertion
// is successful, else n.

int insertSorted(int arr[], int n, int key, int capacity)
{
        // Cannot insert more elements if n is already
        // more than or equal to capacity
        if (n >= capacity)
                return n;

        int i;
        for (i = n - 1; (i >= 0 && arr[i] > key); i--)
                arr[i + 1] = arr[i];

        arr[i + 1] = key;

        return (n + 1);
}

int main(){

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned long long> dis(1, pow(2,30));


        for(int pow=10;pow <= 30;++pow){
                int num = 1 << pow;
                int *arr = new int[num];
                int size = 0;
                //cout << "array size: 2^" << pow << endl;
                clock_t start,end;
                for(int j=0;j<num;++j){
                        *(arr+j) =  dis(gen);
                        size++;
                }
                start = clock();

                for(int i = 0; i < size; ++i)
                        insertSorted(arr, i, dis(gen), num);

                end = clock();

                double ans1;
                ans1 = ((double) (end - start)) / CLOCKS_PER_SEC;
                //cout << "insert.time= " << ans1 << "sec" << endl;

                start = clock();

                for(int i = 0; i < 100000; ++i){

                        binarySearch(arr, 0, num-1, dis(gen));

                }

                end = clock();

                double ans2;
                ans2 = ((double) (end-start)) / CLOCKS_PER_SEC;
                //cout << "search.time= " << ans2 << "sec" << endl;

                cout << pow << ", " << ans1 << ", " << ans2 << endl;
                delete [] arr;
        }

        return 0;
}
