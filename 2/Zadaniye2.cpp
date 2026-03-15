#include <iostream>
#include <ctime>   
#include <cstdlib> 
using std::cout;
//Вариант № 4
// Даны натуральное числоN и последовательность A1, A2, .. ,A N.
// Определить наименьшее положительное среди A1, A2, .. ,A N.
struct Span{
    int* data;
    int size;
};
class Zadaniye2{
public:
//иполнение задания, аргумент это размер массива в задании
    void run(int sizeofArray);
private:
//находит, что дано в задании
    int findMinElement(const Span &arr);
    //создает массив из случаных чисел
    Span* createArray(int sizeofArray);
    //выводит массив в консоль
    void displayArray(const Span& arr);
    //генерирует случайное число в заданном диапазоне
    int generateRandomInt(int min, int max);
};

void Zadaniye2::run(int sizeofArray) {
    std::srand(std::time(0));
    Span* arr = createArray(sizeofArray);
    displayArray(*arr);
    int minElement = findMinElement(*arr);
     if (minElement != -1)
     {
        cout << "min Element = " << minElement << '\n';
     }
     else
     {
        cout << "Не было найдено подходящего элемента" << '\n';
     }
    
    delete[] arr->data;
}

int Zadaniye2::findMinElement(const Span &arr) {
    int minElement = INT_MAX;
    bool isNotDefault = false;
    for(int i = 0; i < arr.size; i++){
        if(arr.data[i] >= 0
           && arr.data[i] < minElement){
            minElement = arr.data[i];
            isNotDefault = true;
        }
    }
    if(!isNotDefault){
        //если не было найдено подходящего элемента, то возвращаем -1
        minElement = -1;
    }
    return minElement;
}
Span* Zadaniye2::createArray(int sizeofArray){
    Span* arr = new Span();

    arr->size = sizeofArray;
    arr->data = new int(arr->size);
    for(int i = 0; i < arr->size; i++){
        arr->data[i] = generateRandomInt(-100, 100);
    }
    return arr;
}
void Zadaniye2::displayArray(const Span& arr){
    for(int i = 0; i < arr.size; i++){
        cout << arr.data[i] << " ";
    }
    cout << '\n';
}
int Zadaniye2::generateRandomInt(int min, int max){
    int randInt = std::rand() % (max - min + 1) + min;
    return randInt;
}