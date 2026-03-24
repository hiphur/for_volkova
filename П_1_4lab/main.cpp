#include <iostream>

using namespace std;


int getcount() {
    int c;
    cout << "Введите количество элементов: ";
    cin >> c;
    return c;
}

class clArrSort {
private:
    int Count;
    int* Arr;

    int findMin(int start, int end);
    int findMax(int start, int end);
    void swap(int& a, int& b);

public:
    friend int getcount();

    clArrSort(int c);
    void sort();
    void output();
    ~clArrSort();
};


clArrSort::clArrSort(int c) {
    Count = c;
    Arr = new int[Count];

    for (int i = 0; i < Count; i++) {
        cout << "элемент " << i << ": ";
        cin >> Arr[i];
    }
}

void clArrSort::swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

int clArrSort::findMin(int start, int end) {
    int idx = start;
    for (int i = start; i < end; i++) {
        if (Arr[i] < Arr[idx])
            idx = i;
    }
    return idx;
}

int clArrSort::findMax(int start, int end) {
    int idx = start;
    for (int i = start; i < end; i++) {
        if (Arr[i] > Arr[idx])
            idx = i;
    }
    return idx;
}

void clArrSort::sort() {
    int left = 0;
    int right = Count - 1;
    int mid = Count / 2;


    for (int i = 0; i < mid; i++) {
        int minIndex = findMin(left, right + 1);
        swap(Arr[left], Arr[minIndex]);
        left++;
    }


    for (int i = mid; i < Count; i++) {
        int maxIndex = findMax(left, right + 1);
        swap(Arr[right], Arr[maxIndex]);
        right--;
    }
}

void clArrSort::output() {
    cout << "Массив: ";
    for (int i = 0; i < Count; i++) {
        cout << Arr[i] << " ";
    }
    cout << endl;
}

clArrSort::~clArrSort() {
    delete[] Arr;
}



int main() {
    system("chcp 65001");
    int n = getcount();

    clArrSort arr(n);

    cout << "\nОригинал:\n";
    arr.output();

    arr.sort();

    cout << "\nМодифицированный:\n";
    arr.output();

    return 0;
}