//
// Created by user on 22.02.2026.
//
//#include "CustomIntArr.h"
#pragma once
#include <stdexcept>
#include <fstream>
#include <iostream>


class CustomIntArr{
private:
    int m_size;
    int* m_arr;
    //насколько массив может расшириться
    int m_capacity;
    //метод для расширения
    void changeCapacity();

    void swap(const int index1, const int index2);
public:
    //заполняет массив нулями
    void fillWithNulls();

    CustomIntArr(int size);

    //size = 0
    CustomIntArr();
    ~CustomIntArr();
    int getSize() const;

    //доступ к элементу
    int& operator[](int index);
    //доступ к элементу, const перегрузка т.к. она нужно для передачи по const reference
    const int& operator[](int index) const;

    void sort();

    int sumAll();
    int sumOfPositiveElements();
    int elementsInRangeCount(const int a, const int b);
    int evenNumberCount();
    int negativeNumberCount();
    double average();
    int max();
    int min();
    //Расширяет массив
    void pushBack(const int value);
    //копия массива без утечки памяти
    CustomIntArr& operator=(const CustomIntArr& other);
    void readFromFile(std::string filePath, int numbersToRead);
    void readFromConsole(int numbersToRead);
};
CustomIntArr::~CustomIntArr() {
    delete[] m_arr;
}
void CustomIntArr::changeCapacity() {
    if(m_capacity == 0) {
        m_capacity = 1;
    }
    else {
        m_capacity *= 2;
    }
    int* newArr = new int[m_capacity];
    for(int i = 0; i < m_capacity; i++) {
        newArr[i] = m_arr[i];
    }
    delete[] m_arr;
    m_arr = newArr;
}
CustomIntArr::CustomIntArr(int size)
        : m_size(size), m_arr(new int[size]), m_capacity(size){
    fillWithNulls();
}
CustomIntArr::CustomIntArr()
        : CustomIntArr(0){
}

void CustomIntArr::fillWithNulls() {
    for(int i = 0; i < m_size; i++){
        m_arr[i] = 0;
    }
}


int CustomIntArr::getSize() const{
    return m_size;
}

int& CustomIntArr::operator[](int index){
    if(index < m_size && index >= 0){
        return m_arr[index];
    }
    else{
        throw std::invalid_argument("index is not in range");
    }
}
const int& CustomIntArr::operator[](int index) const{

    return m_arr[index];


}
void CustomIntArr::swap(const int index1, const int index2){

    if(index1 < m_size && index1 >= 0
       && index2 < m_size && index2 >= 0 ){
        int t = m_arr[index1];
        m_arr[index1] = m_arr[index2];
        m_arr[index2] = t;
    }
    else{
        throw std::invalid_argument("index is not in range");
    }
}
void CustomIntArr::sort() {
    for (int step = 0; step < m_size -1; ++step) {


        for (int i = 0; i < m_size - step - 1; ++i) {
            if (m_arr[i] > m_arr[i + 1]) {
                swap(i, i+1);
//                int temp = m_arr[i];
//                m_arr[i] = m_arr[i + 1];
//                m_arr[i + 1] = temp;
            }
        }
    }
}
int CustomIntArr::sumAll(){
    int sum = 0;
    for(int i = 0; i < m_size; i++){
        sum += m_arr[i];
    }
    return sum;
}
int CustomIntArr::sumOfPositiveElements(){
    int sum = 0;
    for(int i = 0; i < m_size; i++){
        if(m_arr[i] > 0){
            sum += m_arr[i];
        }
    }
    return sum;
}


int CustomIntArr::elementsInRangeCount(const int a, const int b){
    int countElements = 0;
    for(int i = 0; i < m_size; i++){
        if(m_arr[i] >= a
        && m_arr[i] <= b){
            countElements++;
        }
    }
    return countElements;
}
int CustomIntArr::evenNumberCount() {
    int count = 0;
    for (int i = 0; i < m_size; i++) {
        if (m_arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}
int CustomIntArr::negativeNumberCount() {
    int count = 0;
    for (int i = 0; i < m_size; i++) {
        if (m_arr[i] < 0) {
            count++;
        }
    }
    return count;
}
double CustomIntArr::average() {
    int sum = 0;
    for (int i = 0; i < m_size; i++) {
        sum += m_arr[i];

    }
    return (double)sum / m_size;
}
void CustomIntArr::pushBack(const int value) {
    if(m_size == m_capacity) {
        changeCapacity();
    }
    m_arr[m_size] = value;
    m_size++;
}
CustomIntArr& CustomIntArr::operator=(const CustomIntArr& other){
    if(this == &other){
        return *this;
    }

    delete[] m_arr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    if(other.m_arr == nullptr){
        m_arr = nullptr;
    }
    else{
        m_arr = new int[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            m_arr[i] = other.m_arr[i];
        }
    }
    return *this;
}
int CustomIntArr::max(){
    if(m_size == 0) {
        return 0;
    }
    int arrMax = m_arr[0];
    for (int i = 0; i < m_size; i++) {
        if (arrMax < m_arr[i]) {
            arrMax = m_arr[i];
        }
    }
    return arrMax;

}
int CustomIntArr::min(){
    if(m_size == 0) {
        return 0;
    }
    int arrMin = m_arr[0];
    for (int i = 0; i < m_size; i++) {
        if (arrMin > m_arr[i]) {
            arrMin = m_arr[i];
        }
    }
    return arrMin;
}

void CustomIntArr::readFromFile(std::string filePath, int numbersToRead){
    std::ifstream file(filePath);

    if (file.is_open()) {
        for(int i = 0; i < numbersToRead; i++){
            file >> m_arr[i];
            if(file.fail()){
                throw std::runtime_error("Couldn't read the file correctly.");
            }
        }
        file.close();
    }
    else {
        throw std::runtime_error("Couldn't open the file.");
    }
}
