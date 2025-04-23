#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cassert>
using namespace std;

//General Vector
template<typename T,int N>
class Vec{
private:
    T values[N];

public:
    //default
    Vec(){
        for (int i = 0; i < N; i++)
        {
            values[i]=T();
        }
        
    }
    //array
    Vec(const T (&array)[N]){
        for (int i = 0; i < N; i++)
        {
            values[i]=array[i];
        }
    }

    //copy
    Vec(const Vec<T,N>& other){
        for (int i = 0; i < N; i++)
            values[i]=other.values[i];
    }

    int size(){
        return N;
    }

    T& operator[](int index){
        static T iErr=T();

        if(index>=0 && index<N)
            return values[index];
        else{
            clog << "Array bounds violation." << endl;
        return iErr;
        }
     }

    const T& operator[](int index) const {
        return values[index];
    }
    
    Vec<T, N> operator+(const Vec<T, N>& other) const {
        Vec<T, N> result;
        for (int i = 0; i < N; ++i)
            result.values[i] = values[i] + other.values[i];
        return result;
    }

    
};
template <typename T, int N>
std::ostream& operator<<(std::ostream& os, const Vec<T, N>& v) {
    os << "(";
    for (int i = 0; i < N; ++i) {
        os << v[i];
        if (i != N - 1)
            os << ", ";
    }
    os << ")";
    return os;
}


// Vector of size 2
template<typename T>
class Vec<T,2>{
public:
    union 
    {
        T values[2];
        struct 
        {
            T x,y;
        };
        
    };
    
public: 
    Vec(){
        for (int i = 0; i < 2; i++)
        {
            values[i]=T();
        }
    }
     //array
     Vec(const T (&array)[2]){
        for (int i = 0; i < 2; i++)
        {
            values[i]=array[i];
        }
    }

    //copy
    Vec(const Vec<T,2>& other){
        for (int i = 0; i < 2; i++)
            values[i]=other.values[i];
    }

    int size(){
        return 2;
    }

    T& operator[](int index){
        static T iErr=T();

        if(index>=0 && index<2)
            return values[index];
        else{
            clog << "Array bounds violation." << endl;
        return iErr;
        }
     }

    const T& operator[](int index) const {
        return values[index];
    }
    
    Vec<T, 2> operator+(const Vec<T, 2>& other) const {
        Vec<T, 2> result;
        for (int i = 0; i < 2; ++i)
            result.values[i] = values[i] + other.values[i];
        return result;
    }

};

template <typename T, int>
std::ostream& operator<<(std::ostream& os, const Vec<T, 2>& v) {
    os << "(";
    for (int i = 0; i < 2; ++i) {
        os << v[i];
        if (i != 2 - 1)
            os << ", ";
    }
    os << ")";
    return os;
}

// Vector of size 3
template<typename T>
class Vec<T,3>{
public:
    union 
    {
        T values[3];
        struct 
        {
            T x,y,z;
        };
        
    };
    
public: 
    Vec(){
        for (int i = 0; i < 3; i++)
        {
            values[i]=T();
        }
    }
     //array
     Vec(const T (&array)[3]){
        for (int i = 0; i < 3; i++)
        {
            values[i]=array[i];
        }
    }

    //copy
    Vec(const Vec<T,3>& other){
        for (int i = 0; i < 3; i++)
            values[i]=other.values[i];
    }

    int size(){
        return 3;
    }

    T& operator[](int index){
        static T iErr=T();

        if(index>=0 && index<3)
            return values[index];
        else{
            clog << "Array bounds violation." << endl;
        return iErr;
        }
     }

    const T& operator[](int index) const {
        return values[index];
    }
    
    Vec<T, 3> operator+(const Vec<T, 3>& other) const {
        Vec<T, 3> result;
        for (int i = 0; i < 3; ++i)
            result.values[i] = values[i] + other.values[i];
        return result;
    }

};

template <typename T, int>
std::ostream& operator<<(std::ostream& os, const Vec<T, 3>& v) {
    os << "(";
    for (int i = 0; i < 3; ++i) {
        os << v[i];
        if (i != 3 - 1)
            os << ", ";
    }
    os << ")";
    return os;
}

