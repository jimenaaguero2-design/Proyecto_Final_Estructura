#include <iostream>
#include <string>
#include <limits>
using namespace std; 

#define TAM 3

struct Contacto { //Se realiza un contacto con los datos solicitado en el proyecto
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

int main() {
    arreglo = new Contacto[capacidad];  // Creamos el arreglo dinámico

    int op;
    do {
        cout << "\n------MENU-----\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Mostrar contactos\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            agregarContacto();
            break;
        case 2:
            mostrarContactos();
            break;
        }
    } while (op != 3);
    cout << "Usted esta saliendo del programa...\n";
    delete[] arreglo;   // Liberamos memoria al final
    return 0;
}
