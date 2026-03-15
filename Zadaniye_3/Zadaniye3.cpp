#include <iostream>
#include <ctime>   
#include <cstdlib>
#include <float.h>
using std::cout;
using std::cout;
//ВАРИАНТ № 5.
//В каждом из массивов X(Nx), Y(Ny) и Z(Nz) вещественных чисел найти среди
//положительных элементов минимальный элемент и его индекс. Массивы
//генерировать при помощи генератора случайных чисел
struct Span{
    double* data;
    int size;
};
struct ElementAndIndex{
    double element;
    int index;
};
class Zadaniye3{
public:
//иполнение задания, аргумент это размер массива в задании
    void run(int sizeofArray);
private:
//находит, что дано в задании
    ElementAndIndex findMinElementAndIndex(const Span &arr);
    //создает массив из случаных чисел
    Span* createArray(int sizeofArray);
    //выводит массив в консоль
    void displayArray(const Span& arr);
    //генерирует случайное число в заданном диапазоне
    double generateRandomDouble(double min, double max);
    //выводит ответ
    void displayAnswer(ElementAndIndex minElement, char arrayName);
};

void Zadaniye3::run(int sizeofArray) {
    std::srand(std::time(0));
    Span* x = createArray(sizeofArray);
    displayArray(*x);
    ElementAndIndex minElementX = findMinElementAndIndex(*x);
    displayAnswer(minElementX, 'X');

    Span* y = createArray(sizeofArray);
    displayArray(*y);
    ElementAndIndex minElementY = findMinElementAndIndex(*y);
    displayAnswer(minElementY, 'Y');

    Span* z = createArray(sizeofArray);
    displayArray(*z);
    ElementAndIndex minElementZ = findMinElementAndIndex(*z);
    displayAnswer(minElementZ, 'Z');

    delete[] x->data;
    delete[] y->data;
    delete[] z->data;
}


ElementAndIndex Zadaniye3::findMinElementAndIndex(const Span &arr) {
    double minElement = DBL_MAX;
    int index = -1;
    bool isNotDefault = false;
    for(int i = 0; i < arr.size; i++){
        if(arr.data[i] < minElement
        && arr.data[i] >= 0){
            minElement = arr.data[i];
            index = i;
            isNotDefault = true;
        }
    }
    if(!isNotDefault){
        //если не было найдено подходящего элемента, то возвращаем -1
        minElement = -1;
    }
    ElementAndIndex elementAndIndex;
    elementAndIndex.index = index;
    elementAndIndex.element = minElement;
    return elementAndIndex;
}
Span* Zadaniye3::createArray(int sizeofArray){
    Span* arr = new Span();
    arr->size = sizeofArray;
    arr->data = new double[arr->size]();
    for(int i = 0; i < arr->size; i++){
        arr->data[i] = generateRandomDouble(-100, 100);
    }
    return arr;
}
void Zadaniye3::displayArray(const Span& arr){
    for(int i = 0; i < arr.size; i++){
        cout << arr.data[i] << " ";
    }
    cout << '\n';
}
double Zadaniye3::generateRandomDouble(double min, double max){
    double rand = std::rand() / (max - min + 1) + min;
    return rand;
}

void Zadaniye3::displayAnswer(ElementAndIndex minElement, char arrayName) {
    if (minElement.element != -1)
    {
        cout << "min Element в массиве " << arrayName << " = " << minElement.element << '\n';
        cout << "index для min element в массиве " << arrayName << " = " << minElement.index << '\n';

    }
    else
    {
        cout << "Не было найдено подходящего элемента в массиве " << arrayName << '\n';
    }
}
