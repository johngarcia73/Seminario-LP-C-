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

    //one value
    Vec(int value){
        for (int i = 0; i < N; i++)
        {
            values[i]=value;
        }
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

    // one Value
    Vec(int value){
        for (int i = 0; i < 2; i++)
        {
            values[i]=value;
        }
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

    //one value
    Vec(int value){
        for (int i = 0; i < 3; i++)
        {
            values[i]=value;
        }
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



int main() {
    // -------------------------------
    // Caso general: vec<double, 4>
    // -------------------------------
    std::cout << "Probando Vec<int, 4> (caso general)" << std::endl;
    Vec<double, 4> v4;

    // Inicialización mediante operator[]
    for (int i = 0; i < 4; ++i) {
        v4[i] = i; 
    }
    std::cout << v4;
   
    std::cout << "\n\n";

    // -------------------------------
    // Caso especializado: Vec<int, 2> (2D)
    // -------------------------------
    std::cout << "Probando Vec<int, 2> (especialización 2D)" << std::endl;
    // Inicialización mediante constructor a partir de arreglo
    int arr2[2] = {10, 20};
    Vec<int, 2> v2(arr2);
    std::cout << "v2 (acceso por campos): x = " << v2.x << ", y = " << v2.y << std::endl;

    // Modificar elementos utilizando operator[]
    v2[0] = 30;
    v2[1] = 40;
    std::cout << "v2 (tras modificar con operator[]): x = " << v2.x << ", y = " << v2.y << "\n\n";
    
    // -------------------------------
    // Caso especializado: vec<float, 3> (3D)
    // -------------------------------
    std::cout << "Probando vec<float, 3> (especialización 3D)" << std::endl;
    // Construcción por defecto y asignación a través de miembros
    Vec<float, 3> v3;
    v3.x = 1.0f;
    v3.y = 2.0f;
    v3.z = 3.0f;
    std::cout << "v3 (acceso por miembros): (" << v3.x << ", " << v3.y << ", " << v3.z << ")" << std::endl;

    // Modificar elementos utilizando operator[]
    v3[0] = 4.0f;
    v3[1] = 5.0f;
    v3[2] = 6.0f;
    std::cout << "v3 (tras modificar con operator[]): (" 
              << v3.x << ", " << v3.y << ", " << v3.z << ")" << std::endl;

    
    
    // Aquí para vec<float,3> se espera que sizeof(v3) sea igual a 3 * sizeof(float)
    if(sizeof(v3) == 3 * sizeof(float)){
        std::cout<<"Se verifica que sizeof(v3) sea igual a 3* sizeof(float)";
    }
    
    

    return 0;
}