//Constructor
template<typename T>
string_map<T>::string_map() {

    raiz = NULL;
    _size = 0;

}


//Constructor por copia
template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar)
        : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.



//Operador de asignacion
template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d) {

    borraraux(raiz);                        // Primero destruir el trie actual, y "resetearlo"
    raiz = NULL;
    _size = 0;

    auto iter = d.palabras.begin();         // Y luego, recorrer las palabras definidas en el trie parametro, y agregarlas al actual
    while (iter != d.palabras.end()) {
        (*this)[*iter] = d.at(*iter);
        ++iter;
    }

}


//Destructor
template<typename T>
string_map<T>::~string_map() {

    borraraux(raiz);     // Usar la funcion auxiliar recursiva sobre la raiz del trie
    raiz = NULL;
    _size = 0;

}


template<typename T>
void string_map<T>::borraraux(Nodo *a) {   // Funcion recursiva, que elimina un nodo y el camino formado a partir de el

    if (a != NULL) {
        int i = 0;

        while (i < 255) {
            if (a->siguientes[i] != NULL) {
                borraraux(a->siguientes[i]);
            } else {
                // Si la posicion del arreglo no apunta a NULL, no hacer nada
            }
            i++;
        }

        delete a;

    } else {
        // No hacer nada  si el nodo es NULL
    }
}


//Operador para acceder o definir una clave
template<typename T>
T &string_map<T>::operator[](const string &clave) {

    if (empty()) {      // Caso en que el trie esta vacio
        Nodo *nuevo = new Nodo();
        raiz = nuevo;
    }

    int i = 0;
    Nodo *it = raiz;

    if (count(clave) == 1) {   // Caso en el que la clave ya esta definida

        while (i < clave.size()) {       // Buscarla, y devolver su significado
            it = it->siguientes[int(clave[i])];
            i++;
        }

        return *(it->definicion);

    } else {                   // Caso en el que la palabra no estaba definida, i.e. count(clave)==0

        _size++;

        while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {         // Primero buscar donde deberia ir
            it = it->siguientes[int(clave[i])];
            i++;
        }

        while (i < clave.size()) {      // Y luego, agregarla a la lista de palabras, y al trie propiamente dicho
            Nodo *nuevo2 = new Nodo();
            it->siguientes[int(clave[i])] = nuevo2;
            it->cantHijos++;
            it = it->siguientes[int(clave[i])];
            i++;
        }
        it->it = palabras.insert(palabras.end(), clave);
        if (it->definicion == NULL) {    // Si no tiene significado, agregarlo
            it->definicion = new T();
        } else {
            // Caso contrario, devolver el que tenga
        }

        return *(it->definicion);
    }
}


//Definido?
template<typename T>
int string_map<T>::count(const string &clave) const {

    if (empty()) {  // Caso 1: el trie esta vacio
        return 0;

    } else {   // Caso 2: el trie no esta vacio

        int res = 0;
        Nodo *it = raiz;
        int i = 0;

        while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
            it = it->siguientes[int(clave[i])];
            i++;
        }

        if (!(i < clave.size())) {
            if (it->definicion != NULL) {   // Si la palabra esta, y tiene significado, count=1
                res = 1;
            }

        } else {
            // Nada, pues la palabra no esta,i.e. count sigue en cero

        }
        return res;
    }

}


//Acceder al significado de una clave. Version no modificable
template<typename T>
const T &string_map<T>::at(const string &clave) const {

    Nodo *it = raiz;
    int i = 0;

    while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
        it = it->siguientes[int(clave[i])];
        i++;
    }

    T &res = *it->definicion;

    return res;
}


//Acceder al significado de una clave. Version modificable
template<typename T>
T &string_map<T>::at(const string &clave) {

    Nodo *it = raiz;
    int i = 0;

    while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
        it = it->siguientes[int(clave[i])];
        i++;
    }

    T &res = *it->definicion;

    return res;
}


//Borrar una clave
template<typename T>
void string_map<T>::erase(const string &clave) {

    stack<Nodo *> camino;

    if (_size == 1) { // Caso 1: el trie tiene tamano 1

        Nodo *it = raiz;
        int i = 0;

        while (i < clave.size() && it->siguientes[int(clave[i])] != NULL) {
            camino.emplace(it);                     // Guardar el camino para llegar a la clave
            it = it->siguientes[int(clave[i])];     // Moverse en el trie hacia el final de la clave
            i++;
        }

        Nodo *aBorrar = it;         // Una vez hayado el nodo de la clave, borrarlo
        delete aBorrar;
        it = camino.top();
        it->cantHijos--;

        int j = clave.size() - 1;
        while (it->cantHijos == 0 && it->definicion == NULL && j > 0) {  // Y borrar el camino hacia el
            Nodo *borrar = it;
            borrar->siguientes[int(clave[j])] = NULL;
            camino.pop();
            delete borrar;
            it = camino.top();
            it->cantHijos--;
            j--;
        }

        it->siguientes[int(clave[j])] = NULL;
        delete raiz;        // Por ultimo, borrar la raiz, pues el trie no tiene mas elementos
        raiz = NULL;

    } else {  // Caso 2: el trie tiene mas de una clave

        Nodo *it = raiz;
        int i = 0;
        while (i < clave.size() &&
               it->siguientes[int(clave[i])] != NULL) {     // Buscar la clave y guardar el camino a ella
            camino.emplace(it);
            it = it->siguientes[int(clave[i])];
            i++;
        }

        if (it->cantHijos > 0) {    // Si tiene significado, borrarlo

            delete it->definicion;
            it->definicion = NULL;
            this->palabras.erase(it->it);

        } else {

            Nodo *aBorrar = it;     // Borrar el nodo de la clave
            delete aBorrar;
            it = camino.top();
            it->cantHijos--;

            int j = clave.size() - 1;
            while (it->cantHijos == 0 && it->definicion == NULL && j > 0) {         // Borrar el camino hacia el
                Nodo *borrar = it;
                borrar->siguientes[int(clave[j])] = NULL;
                camino.pop();
                delete borrar;
                it = camino.top();
                it->cantHijos--;
                j--;
            }

            it->siguientes[int(clave[j])] = NULL;

        }
    }

    _size--;                            // En ambos casos, el tamano disminuye en 1

}


//Cantidad de claves definidas
template<typename T>
int string_map<T>::size() const {

    return _size;
}


//Indica si el trie esta vacio
template<typename T>
bool string_map<T>::empty() const {

    return raiz == NULL;
}


//Devuelve las claves definidas en el diccionario
template<typename T>
const list<string> &string_map<T>::claves() const {

    return palabras;
}
