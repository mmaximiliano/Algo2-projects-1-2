#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <stack>
#include <list>
#include <vector>

using namespace std;

template<typename T>
class string_map {  // Este es el diccionario montado sobre un trie hecho en el Taller 4 de la materia

public:

    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();


    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T> &aCopiar);


    /**
    OPERADOR ASIGNACION
     */
    string_map &operator=(const string_map &d);


    /**
    DESTRUCTOR
    **/
    ~string_map();


    /**
    operator[]
    * Acceso o definición de pares clave/valor
    **/
    T &operator[](const string &clave);


    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/
    int count(const string &clave) const;


    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T &at(const string &clave) const;

    T &at(const string &clave);


    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string &clave);


    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;


    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;

    /**
     CLAVES
     * devuelve el conjunto (sobre vector de string) de claves definidas en el diccionario */
    const list<string> &claves() const;


private:

    struct Nodo {

        Nodo() {                   // Constructor para los nodos del trie

            siguientes = new Nodo *[256];

            int i = 0;
            while (i < 255) {               // Crea el arreglo 'siguientes' con todas sus posiciones en NULL
                siguientes[i] = NULL;
                i++;
                cantHijos = 0;              // Los nodos se inicializan sin hijos

            }
            definicion = NULL;              // Inicializa la definicion en NULL
        }

        int cantHijos;                      // Cantidad de hijos del nodo
        Nodo **siguientes;                  // Arreglo de punteros a nodos
        T *definicion;                      // Significado de la clave
        list<string>::iterator it;

        ~Nodo() {                   // Destructor para los nodos

            delete[] siguientes;
            if (definicion != NULL) {
                delete definicion;
            }

        }

    };

    list<string> palabras;           // Lista enlazada con todas las palabras definidas en el diccionario.

    // stack<Nodo *> camino;            // Pila de padres que llevan al nodo

    Nodo *raiz;

    int _size;                       // Cantidad de claves definidas en el trie

    void borraraux(Nodo *a);         // Funcion auxiliar recursiva para el destructor del trie

};

#include "string_map.hpp"

#endif // STRING_MAP_H_
