#include <iostream>
#include <string>
#include <limits>
using namespace std; 

#define TAM 3

struct Contacto { //Se realiza un contacto con los datos solicitados en el proyecto
    string nombre;
    string telefono;
    string correo;
};

// Variables globales
Contacto* arreglo;
int capacidad = TAM;
int cantidad = 0;

// Función para crecer el arreglo
void CrecerArreglo() {
    int nuevaCapacidad = capacidad * 2;
    Contacto* nuevo = new Contacto[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevo[i] = arreglo[i];   // Copiamos datos
    }

    delete[] arreglo;           // Borramos el anterior
    arreglo = nuevo;            // Apuntamos al nuevo
    capacidad = nuevaCapacidad;
}

// Función para mostrar
void MostrarContactos() {
    cout << "\n----CONTACTOS REGISTRADOS----\n";
    for (int i = 0; i < cantidad; i++) {
        cout << arreglo[i].nombre << endl;
        cout << arreglo[i].telefono << endl;
        cout << arreglo[i].correo << endl;
        cout << "---------------------------\n";
    }
}

void OrdenarPorNombre() { // Función para ordenar los nombres de manera alfabetica 

    if (cantidad < 2) { cout << "\nNo hay suficientes contactos para ordenar...\n"; return; }
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (arreglo[j + 1].nombre < arreglo[j].nombre) {
                Contacto tmp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = tmp;
            }
        }
    }
    cout << "\nSe ordenaron los contactos alfabeticamente...\n";
}

int BusquedaSecuencialNombre(string nombre) {  // Función para buscar de manera secuencial
    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i].nombre == nombre) return i;
    }
    return -1;
}

int BusquedaBinariaNombre(string nombre) { // Función para buscar de manera binaria, pero debe estar ordenados los nombres
    int ini = 0, fin = cantidad - 1;
    while (ini <= fin) {
        int mid = (ini + fin) / 2;
        if (arreglo[mid].nombre == nombre) return mid;
        else if (nombre < arreglo[mid].nombre) fin = mid - 1;
        else ini = mid + 1;
    }
    return -1;
}

struct NodoPila {
    string accion;
    NodoPila* siguiente;
};

NodoPila* pila = NULL;

void Push(string accion) {
    NodoPila* nuevo = new NodoPila();
    nuevo->accion = accion;
    nuevo->siguiente = pila;
    pila = nuevo;
}

void MostrarHistorial() { // Se encarga de mostrar el historial
    NodoPila* actual = pila;
    cout << "\n---- HISTORIAL DE OPERACIONES ----\n";
    while (actual != NULL) {
        cout << actual->accion << endl;
        cout << "---------------------------\n";
        actual = actual->siguiente;
    }
}

struct Nodo {
    Contacto dato;
    Nodo* siguiente;
};

Nodo* lista = NULL; // lista enlazada global

void InsertarEnLista(Contacto c) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = c;
    nuevo->siguiente = lista;
    lista = nuevo;
}

void MostrarLista() { 
    Nodo* actual = lista;
    cout << "\n---- LISTA ENLAZADA ----\n";
    while (actual != NULL) {
        cout << actual->dato.nombre << endl;
        cout << actual->dato.telefono << endl;
        cout << actual->dato.correo << endl;
        cout << "---------------------------\n";
        actual = actual->siguiente;
    }
}

void EliminarNodo(string nombre) {
    if (lista == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    Nodo* auxiliar = lista;
    Nodo* anterior = NULL;

    while (auxiliar != NULL && auxiliar->dato.nombre != nombre) {
        anterior = auxiliar;
        auxiliar = auxiliar->siguiente;
    }

    if (auxiliar == NULL) {
        cout << "No se encontro el contacto en la lista...\n";
        return;
    }

    if (anterior == NULL) {
        lista = auxiliar->siguiente;
    }
    else {
        anterior->siguiente = auxiliar->siguiente;
    }

    cout << "\nSe ha eliminado el contacto de manera correcta con lista enlazada...\n";
    Push("\nSe elimino el contacto: " + auxiliar->dato.nombre);
    delete auxiliar;
}

// Función para agregar contactos al sistema
void AgregarContacto() {
    if (cantidad == capacidad) {
        CrecerArreglo();   // Si se llena, crece
    }

    cout << "Digite un nombre: ";
    cin >> arreglo[cantidad].nombre;
    cout << "Digite un numero de telefono: ";
    cin >> arreglo[cantidad].telefono;
    cout << "Digite un correo electronico: ";
    cin >> arreglo[cantidad].correo;

    InsertarEnLista(arreglo[cantidad]);

    cantidad++;
    cout << "\nSe ingresaron los datos de manera correcta...\n";

    Push("\nSe agrego el contacto: " + arreglo[cantidad - 1].nombre);
}

int main() {
    arreglo = new Contacto[capacidad];  // Creamos el arreglo dinámico
    int op;
    int secu;
    int bina;
    string nombre;
    do {
        cout << "\n================ MENU ====================\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Mostrar contactos\n";
        cout << "3. Ordenar por nombre\n";
        cout << "4. Buscar por nombre de manera secuencial\n";
        cout << "5. Buscar por nombre de manera binaria\n";
        cout << "6. Eliminar contacto con lista enlazada\n";
        cout << "7. Mostrar lista enlazada\n";
        cout << "8. Mostrar historial de operaciones\n";
        cout << "9. Salir\n";
        cout << "------------------------------------------\n";
        cout << "Por favor, seleccione una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            AgregarContacto();
            break;
        case 2:
            MostrarContactos();
            break;
        case 3:
            OrdenarPorNombre();
            break;
        case 4:
            cout << "Digite el nombre a buscar: ";
            cin >> nombre;
            secu = BusquedaSecuencialNombre(nombre);
            if (secu != -1) {
                cout << "El nombre del contacto encontrado es: " << arreglo[secu].nombre << ", su numero de telefono es: " << arreglo[secu].telefono << " y el correo es: " << arreglo[secu].correo << endl;
            }
            else {
                cout << "\nNo se encontro el contacto...\n";
            }
            break;
        case 5:
            OrdenarPorNombre();
            cout << "Digite el nombre a buscar: ";
            cin >> nombre;
            bina = BusquedaBinariaNombre(nombre);
            if (bina != -1) {
                cout << "El nombre del contacto encontrado es: " << arreglo[bina].nombre << ", su numero de telefono es: " << arreglo[bina].telefono << " y el correo es: " << arreglo[bina].correo << endl;
            }
            else {
                cout << "\nNo se encontro el contacto...\n";
            }
            break;
        case 6:
            cout << "Digite el nombre a eliminar: ";
            cin >> nombre;
            EliminarNodo(nombre);
            break;
        case 7:
            MostrarLista();
            break;
        case 8:
            MostrarHistorial();
            break;
        case 9:
            cout << "\nUsted esta saliendo del programa...\n";
            break;
        }

    } while (op != 9);

    delete[] arreglo; // Liberamos memoria al final
    return 0;
}
