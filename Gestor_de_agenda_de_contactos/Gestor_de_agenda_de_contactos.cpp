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
void crecerArreglo() {
    int nuevaCapacidad = capacidad * 2;
    Contacto* nuevo = new Contacto[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevo[i] = arreglo[i];   // Copiamos datos
    }

    delete[] arreglo;           // Borramos el anterior
    arreglo = nuevo;            // Apuntamos al nuevo
    capacidad = nuevaCapacidad;
}

// Función para agregar
void agregarContacto() {
    if (cantidad == capacidad) {
        crecerArreglo();   // Si se llena, crece
    }

    cout << "Digite un nombre: ";
    cin >> arreglo[cantidad].nombre;
    cout << "Digite un numero de telefono: ";
    cin >> arreglo[cantidad].telefono;
    cout << "Digite un correo electronico: ";
    cin >> arreglo[cantidad].correo;
    cantidad++;
    cout << "\nSe ingresaron los datos de manera correcta...\n";
}

// Función para mostrar
void mostrarContactos() {
    cout << "\n----CONTACTOS REGISTRADOS----\n";
    for (int i = 0; i < cantidad; i++) {
        cout << arreglo[i].nombre << endl;
        cout << arreglo[i].telefono << endl;
        cout << arreglo[i].correo << endl;
        cout << "---------------------------\n";
    }
}

void ordenarPorNombre() { // Función para ordenar los nombres de manera alfabetica 

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

int main() {
    arreglo = new Contacto[capacidad];  // Creamos el arreglo dinámico

    int op;
    do {
        cout << "\n------MENU-----\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Mostrar contactos\n";
        cout << "3. Ordenar por nombre\n";
        cout << "4. Salir\n";
        cout << "Por favor, seleccione una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            agregarContacto();
            break;
        case 2:
            mostrarContactos();
            break;
        case 3:
            ordenarPorNombre();
            break;
        case 4:
            cout << "\nUsted esta saliendo del programa...\n";
            break;
        }

    } while (op != 4);

    delete[] arreglo; // Liberamos memoria al final
    return 0;
}
