#include <iostream>
#include <memory>             // Para smart pointers
#include <initializer_list>   // Para list-initialization
#include <vector>
#include <algorithm>          // Para for_each
#include <stdexcept>          // Para out_of_range
#include <utility>            // Para move, swap
#include <string>
#include <windows.h>

using namespace std;
// -----------------------------------------------------------------------------
// 1. Alias para punteros a función
// Este alias define "Function<R, Ts...>" como un puntero a función que devuelve R
// y recibe parámetros de tipos Ts.... Esto permite crear punteros a funciones
// con cualquier cantidad de parámetros y tipos específicos.


// -----------------------------------------------------------------------------
// 2. Definición de la clase node (nodo de la lista)
// Cada nodo almacena el dato y punteros inteligentes a los nodos adyacentes.
template<typename T>
struct node {
    T data;
    shared_ptr<node<T>> next;      // Puntero al siguiente nodo.
    weak_ptr<node<T>> previous;    // Puntero al nodo anterior (weak para evitar ciclos de referencia).

    // Constructor: inicializa el dato y deja los punteros vacíos.
    explicit node(const T& value)
        : data(value), next(nullptr), previous() { }
};

// -----------------------------------------------------------------------------
// 3. Definición de la clase linked_list (lista doblemente enlazada)
template<typename T>
class linked_list {
public:

    template<typename R, typename... Ts>
    using Function = R(*)(const T&, Ts...);
    
    using node_type = node<T>;
    using node_ptr  = shared_ptr<node_type>;

private:
    node_ptr head;       // Puntero al primer nodo.
    node_ptr tail;       // Puntero al último nodo.
    size_t size_;   // Número de elementos en la lista.

public:
    // --- CONSTRUCTORES Y OPERADORES DE ASIGNACIÓN ---

    // 3.1 Constructor por defecto.
    linked_list()
        : head(nullptr), tail(nullptr), size_(0) {
        cout << "[Default Constructor] Lista vacía creada.\n";
    }

    // 3.2 Constructor con list-initialization (similar a C#).
    linked_list(initializer_list<T> ilist)
        : linked_list() {
        for (const auto & val : ilist) {
            Add_Last(val);
        }
        cout << "[Initializer List Constructor] Lista inicializada con { }.\n";
    }

    // 3.3 Constructor que recibe un vector<T>.
    linked_list(const vector<T>& vec)
        : linked_list() {
        for (const auto & val : vec) {
            Add_Last(val);
        }
        cout << "[Vector Constructor] Lista inicializada a partir de vector.\n";
    }

    // 3.4 Constructor de copia (copia profunda).
    linked_list(const linked_list &other)
        : linked_list() {
        cout << "[Copy Constructor] Copia de lista.\n";
        for (node_ptr curr = other.head; curr != nullptr; curr = curr->next) {
            Add_Last(curr->data);
        }
    }

    // 3.5 Constructor de movimiento (move constructor).
    linked_list(linked_list &&other) noexcept
        : head(move(other.head)), tail(move(other.tail)), size_(other.size_) {
        cout << "[Move Constructor] Moviendo lista.\n";
        other.size_ = 0;
    }

    // 3.6 Operador de asignación por copia (copy assignment).
    linked_list& operator=(const linked_list &other) {
        cout << "[Copy Assignment] Asignación por copia.\n";
        if(this != &other) {
            linked_list temp(other);  // Constructor de copia.
            swap(temp);               // Copy-and-swap.
        }
        return *this;
    }

    // 3.7 Operador de asignación por movimiento (move assignment).
    linked_list& operator=(linked_list &&other) noexcept {
        cout << "[Move Assignment] Asignación por movimiento.\n";
        if(this != &other) {
            clear();
            head = move(other.head);
            tail = move(other.tail);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    // --- DESTRUCTOR ---
    ~linked_list() {
        cout << "[Destructor] Liberando lista con " << size_ << " elemento(s).\n";
        clear();
    }

    // -------------------------------------------------------------------------
    // Funciones Auxiliares

    // swap: intercambia el contenido de dos listas (útil para copy-and-swap).
    void swap(linked_list &other) noexcept {
        swap(head, other.head);
        swap(tail, other.tail);
        swap(size_, other.size_);
    }

    // clear: vacía la lista; al asignar nullptr, los smart pointers liberan la memoria.
    void clear() noexcept {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    // length: retorna el número de elementos en la lista.
    size_t length() const noexcept {
        return size_;
    }

    // Add_Last: añade un nuevo elemento al final de la lista.
    void Add_Last(const T &value) {
        auto new_node = make_shared<node_type>(value);
        if (!head) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->previous = tail;
            tail = new_node;
        }
        ++size_;
    }

    // Remove_Last: elimina el último elemento de la lista.
    bool Remove_Last() {
        if (!tail)
            return false;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            auto prev = tail->previous.lock();
            if (prev) {
                prev->next = nullptr;
                tail = prev;
            }
        }
        --size_;
        return true;
    }

    // At: retorna una referencia al elemento en la posición "index".
    // Lanza out_of_range si el índice es inválido.
    T& At(size_t index) {
        if(index >= size_) {
            throw out_of_range("Index out of range");
        }
        auto curr = head;
        for(size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }
    // Versión const de At.
    const T& At(size_t index) const {
        if(index >= size_) {
            throw out_of_range("Index out of range");
        }
        auto curr = head;
        for(size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    // Remove_At: elimina el elemento en la posición "index".
    bool Remove_At(size_t index) {
        if(index >= size_)
            return false;
        if(index == 0) {
            head = head->next;
            if(head)
                head->previous.reset();
            else
                tail = nullptr;
            --size_;
            return true;
        }
        auto curr = head;
        for(size_t i = 0; i < index; ++i) {
            curr = curr->next;
        }
        auto prev = curr->previous.lock();
        auto nxt = curr->next;
        if(prev)
            prev->next = nxt;
        if(nxt)
            nxt->previous = prev;
        if(curr == tail)
            tail = prev;
        --size_;
        return true;
    }

    // -------------------------------------------------------------------------------
    // 4. Función Map: transforma la lista de T a una lista de R.
    // Recibe como parámetro un puntero a función
    // que transforma un elemento del tipo "const T&" en un elemento de tipo R.

    template <typename R, typename... Ts>
    linked_list<R> Map(Function<R, Ts...> transform, Ts... args) const {
        linked_list<R> newList;
        for (auto curr = head; curr != nullptr; curr = curr->next) {
            newList.Add_Last(transform(curr->data, args...));
        }
        return newList;
    }

    // -------------------------------------------------------------------------
    // 5. Función print: utiliza for_each y una lambda para imprimir la lista.
    void print() const {
        vector<T> values;
        for(auto curr = head; curr != nullptr; curr = curr->next) {
            values.push_back(curr->data);
        }
        cout << "Lista: ";
        for_each(values.begin(), values.end(), [](const T &val) {
            cout << val << " <-> ";
        });
    }
};

// -----------------------------------------------------------------------------
// 6. Funciones de Ejemplo para ser usadas con Map

// Función que multiplica un entero.
int multiplyBy(const int &x, int factor) {
    return x * factor;   
}

// Función que calcula la longitud de un string.
int stringLength(const string &s) {
    return static_cast<int>(s.length());
}

template <typename... Args>
void printParameterCount(Args... args) {
    ((std::cout << args << " "), ...); // Fold expression
    std::cout << "\n";
}

int main() {
    SetConsoleOutputCP(65001);  // Configurar consola para caracteres especiales
    SetConsoleCP(65001);

    cout << "=== DEMOSTRACIÓN DE LISTA DOBLEMENTE ENLAZADA EN C++ ===\n\n";

    // ---------------------------------------------------------------
    cout << "\n1. CONSTRUCTORES ESPECIALES\n";
    cout << "----------------------------\n";
    
    // Constructor por defecto
    cout << ">> Creando lista vacía (constructor por defecto):\n";
    linked_list<int> lista_vacia;
    cout << " - Longitud: " << lista_vacia.length() << "\n\n";

    // Constructor con initializer_list
    cout << ">> Creando lista con inicialización uniforme {1,2,3,4,5}:\n";
    linked_list<int> lista1 = {1, 2, 3, 4, 5};
    cout << " - Contenido: ";
    lista1.print();

    // Constructor desde vector
    cout << "\n>> Creando lista desde vector<int>{6,7,8,9}:\n";
    vector<int> vec = {6, 7, 8, 9};
    linked_list<int> lista2(vec);
    cout << " - Contenido: ";
    lista2.print();

    // ---------------------------------------------------------------
    cout << "\n\n2. SEMÁNTICA DE COPIA Y MOVIMIENTO\n";
    cout << "----------------------------------\n";
    
    // Copia profunda
    cout << ">> Haciendo copia de lista1 (constructor de copia):\n";
    linked_list<int> lista_copia(lista1);
    cout << " - Copia: ";
    lista_copia.print();
    cout << " - Original sigue intacto: ";
    lista1.print();

    // Movimiento de recursos
    cout << "\n>> Moviendo recursos de lista_copia (constructor de movimiento):\n";
    linked_list<int> lista_movida(move(lista_copia));
    cout << " - Lista movida: ";
    lista_movida.print();
    cout << " - Lista original después del movimiento: ";
    lista_copia.print();
    cout << " - Longitud original: " << lista_copia.length() << endl;

    // ---------------------------------------------------------------
    cout << "\n\n3. OPERACIONES BÁSICAS\n";
    cout << "-----------------------\n";
    
    // Añadir elementos
    cout << ">> Añadiendo elementos al final (Add_Last):\n";
    lista_vacia.Add_Last(10);
    lista_vacia.Add_Last(20);
    lista_vacia.Add_Last(30);
    cout << " - Lista después de añadir: ";
    lista_vacia.print();

    // Eliminar elementos
    cout << "\n>> Eliminando último elemento (Remove_Last):\n";
    lista_vacia.Remove_Last();
    cout << " - Lista después de eliminar: ";
    lista_vacia.print();

    // Acceso seguro con At()
    cout << "\n>> Acceso seguro a elementos (At()):\n";
    try {
        cout << " - Elemento en posición 1: " << lista_vacia.At(1) << endl;
        cout << " - Intentando acceder a posición 10...\n";
        lista_vacia.At(10); // Esto lanzará excepción
    } catch (const out_of_range& e) {
        cout << " !! ERROR: " << e.what() << endl;
    }

    // ---------------------------------------------------------------
    cout << "\n\n4. FUNCIONALIDAD AVANZADA\n";
    cout << "--------------------------\n";
    
    // Función Map con enteros
    cout << ">> Transformando lista (Map) - Multiplicando valores:\n";
    cout << " - Lista original: ";
    linked_list<int> numeros = {1, 2, 3, 4};
    numeros.print();
    auto dobles = numeros.Map<int>(multiplyBy, 3);
    cout << " - Lista transformada: ";
    dobles.print();

    cout << "\n";

    // Función Map con strings
    cout << "\n>> Transformando lista de strings (Map) - Longitudes:\n";
    linked_list<string> lenguajes = {"C++", "Python", "JavaScript"};
    cout << " - Lista original: ";
    lenguajes.print();
    auto longitudes = lenguajes.Map<int>(stringLength);
    cout << " - Longitudes: ";
    longitudes.print();

    // ---------------------------------------------------------------
    cout << "\n\n5. GESTIÓN AUTOMÁTICA DE MEMORIA\n";
    cout << "--------------------------------\n";
    
    cout << ">> Creando lista en bloque local:\n";
    {
        linked_list<int> lista_local = {1, 3, 5, 7};
        cout << " - Dentro del bloque: ";
        lista_local.print();
    } // Destructor automático aquí
    cout << " - Fuera del bloque: Lista ya fue destruida\n";

    // ---------------------------------------------------------------
    cout << "\n\n6. EJEMPLO DE FUNCIÓN VARIÁDICA\n";
    cout << "------------------------------\n";
    
    cout << ">> Llamando función variádica:\n";
    printParameterCount(23, "test", 'a', true);

    // ---------------------------------------------------------------
    cout << "\n\n=== FIN DE LA DEMOSTRACIÓN ===" << endl;
    cout << "\nPresiona ENTER para salir...";
    cin.ignore();
    cin.get();
    return 0;
}