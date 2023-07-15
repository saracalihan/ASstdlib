#pragma once
#include <type_traits>
#include <vector>

#define ASSTDLIB_DEFAULT_VECTOR_SIZE 100
#define SIZE_T int
#define ITARATOR_T void

template<typename T, int vector_size>
class Vector{
    private:
        std::vector<T> m_data = {};

    public:
    T at(SIZE_T index){
        return m_data.at(index);
    }
    //T friend [int index]{}
    T first(){
        return m_data.front();
    }
    T last(){
        return m_data.end();
    }
    bool is_empty(){
        return m_data.empty();
    }
    SIZE_T size(){
        return m_data.size();
    }
    SIZE_T capacity(){
        return m_data.capacity();
    }
    SIZE_T clear(){
        SIZE_T s = size();
        m_data.clear();
        if (m_data.size() !=0) {
            return -1;
        }
        return s;
    }
    ITARATOR_T insert(T data){
        return m_data.push_back(data);
    }
    ITARATOR_T emplace(SIZE_T to, T data ){
        return m_data.emplace(to, data);
    }
    ITARATOR_T emplace_back(SIZE_T to, T data ){
        return m_data.emplace_back(to, data);
    }
    ITARATOR_T push(T data){
        return m_data.push_back(data)
    }
    ITARATOR_T erase(SIZE_T index){
        return m_data.erase(index);
    }
    ITARATOR_T erase(SIZE_T first, SIZE_T last){
        return m_data.erase(first, last);
    }
    T pop(){
        return m_data.pop_back();
    }
    void resize(SIZE_T size){
        return m_data.resize(size);
    }
    void swap(Vector<T, vector_size> other){
        return m_data.swap(other);
    }
    bool operator ==(const Vector<T, vector_size>&other){}
    bool operator!=(const Vector<T, vector_size>&other){}
    bool operator=(const Vector<T, vector_size>&other){}
    ITARATOR_T operator[](SIZE_T index){}
}
