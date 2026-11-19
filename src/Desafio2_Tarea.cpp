#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

struct Tarea {
    string nombre;
    string descripcion;
    int diasVencimiento;
    string estado;
};

// Prototipos de funciones
bool existeTarea(const vector<Tarea>& listaTareas, const string& nombre);
bool agregarTarea(vector<Tarea>& listaTareas, string nombre, string descripcion,
                  int dias, float promedio, char respuesta);
bool actualizarTarea(vector<Tarea>& listaTareas, string nombreBuscar, string nuevoEstado, int nuevosDias);
void mostrarTareas(const vector<Tarea>& listaTareas);

// Funcion auxiliar para validar que no haya nombres duplicados
bool existeTarea(const vector<Tarea>& listaTareas, const string& nombre) {
    for (size_t i = 0; i < listaTareas.size(); i++) {
        if (listaTareas[i].nombre == nombre) {
            return true;
        }
    }
    return false;
}

// Funcion modular para agregar una tarea
bool agregarTarea(vector<Tarea>& listaTareas, string nombre, string descripcion,
                  int dias, float promedio, char respuesta) {
    // Validaciones de datos basicos
    if (nombre.empty()) {
        printf("Error: el nombre de la tarea no puede estar vacio.\n");
        return false;
    }
    if (existeTarea(listaTareas, nombre)) {
        printf("Error: ya existe una tarea con el nombre '%s'.\n", nombre.c_str());
        return false;
    }
    if (dias <= 0) {
        printf("Error: la cantidad de dias para el vencimiento debe ser mayor a 0.\n");
        return false;
    }

    // Requisitos de la beca
    if (promedio < 9.5) {
        printf("No cumple los requisitos: el promedio debe ser 9.5 o mas.\n");
        return false;
    }
    if (respuesta == 'N' || respuesta == 'n') {
        printf("No cumple los requisitos: debe ser ciudadano argentino y residir en zona sur.\n");
        return false;
    }

    // Si pasa todas las validaciones, se crea y guarda
    Tarea nueva;
    nueva.nombre = nombre;
    nueva.descripcion = descripcion;
    nueva.diasVencimiento = dias;
    nueva.estado = "Preseleccionada";

    listaTareas.push_back(nueva);
    return true;
}

// Funcion modular para actualizar una tarea existente
bool actualizarTarea(vector<Tarea>& listaTareas, string nombreBuscar, string nuevoEstado, int nuevosDias) {
    if (nuevosDias <= 0) {
        printf("Error: los dias de vencimiento deben ser mayores a 0.\n");
        return false;
    }

    for (size_t i = 0; i < listaTareas.size(); i++) {
        if (listaTareas[i].nombre == nombreBuscar) {
            listaTareas[i].estado = nuevoEstado;
            listaTareas[i].diasVencimiento = nuevosDias;
            return true; // Actualizada con exito
        }
    }

    printf("Error: no se encontro ninguna tarea con el nombre '%s'.\n", nombreBuscar.c_str());
    return false;
}

// Funcion modular para mostrar todas las tareas
void mostrarTareas(const vector<Tarea>& listaTareas) {
    if (listaTareas.empty()) {
        printf("\nNo hay tareas registradas.\n");
        return;
    }

    printf("\n=== LISTA DE TAREAS ===\n");
    for (size_t i = 0; i < listaTareas.size(); i++) {
        printf("Tarea #%d\n", (int)(i + 1));
        printf("Nombre: %s\n", listaTareas[i].nombre.c_str());
        printf("Descripcion: %s\n", listaTareas[i].descripcion.c_str());
        printf("Dias para el vencimiento: %d\n", listaTareas[i].diasVencimiento);
        printf("Estado: %s\n", listaTareas[i].estado.c_str());
        printf("-----------------------------\n");
    }
}

int main() {
    vector<Tarea> listaTareas;
    int opcion = 0;

    do {
        printf("\n--- SISTEMA DE GESTION DE TAREAS ---\n");
        printf("1. Agregar tarea\n");
        printf("2. Actualizar tarea\n");
        printf("3. Mostrar tareas\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("Error: ingrese un numero valido.\n");
            continue;
        }
        while (getchar() != '\n'); // Limpiar buffer

        if (opcion == 1) {
            // ---------- NOMBRE ----------
            string nombre;
            printf("Ingrese el nombre: ");
            getline(cin, nombre);
            while (nombre.empty() || existeTarea(listaTareas, nombre)) {
                if (nombre.empty()) {
                    printf("Error: el nombre no puede estar vacio.\n");
                } else {
                    printf("Error: ya existe una tarea con ese nombre.\n");
                }
                printf("Ingrese el nombre: ");
                getline(cin, nombre);
            }

            // ---------- DESCRIPCION ----------
            string descripcion;
            printf("Ingresa la descripcion de la tarea (opcional): ");
            getline(cin, descripcion);

            // ---------- DIAS ----------
            int dias, leidos;
            printf("Ingresa en cuantos dias vence la tarea: ");
            leidos = scanf("%d", &dias);
            while (getchar() != '\n');

            while (leidos != 1 || dias <= 0) {
                if (leidos != 1) printf("Error: ingrese un numero entero.\n");
                else printf("Error: los dias deben ser mayores a 0.\n");

                printf("Ingresa en cuantos dias vence la tarea: ");
                leidos = scanf("%d", &dias);
                while (getchar() != '\n');
            }

            // ---------- PROMEDIO ----------
            float promedio;
            int leidoPromedio;
            printf("Ingresa el promedio (0 a 10): ");
            leidoPromedio = scanf("%f", &promedio);
            while (getchar() != '\n');

            while (leidoPromedio != 1 || promedio < 0 || promedio > 10) {
                if (leidoPromedio != 1) printf("Error: ingrese un numero (no letras).\n");
                else printf("Error: el promedio debe estar entre 0 y 10.\n");

                printf("Ingresa el promedio (0 a 10): ");
                leidoPromedio = scanf("%f", &promedio);
                while (getchar() != '\n');
            }

            // Requisito 1: promedio de 9.5 o mas (se evalua apenas se sabe)
            if (promedio < 9.5) {
                printf("No cumple los requisitos: el promedio debe ser 9.5 o mas.\n");
                continue;   // vuelve al menu
            }

            // ---------- CIUDADANIA Y ZONA SUR ----------
            char respuesta;
            printf("Es ciudadano argentino y reside en zona sur? (S/N): ");
            scanf(" %c", &respuesta);
            while (getchar() != '\n');

            while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n') {
                printf("Error: responda S o N.\n");
                printf("Es ciudadano argentino y reside en zona sur? (S/N): ");
                scanf(" %c", &respuesta);
                while (getchar() != '\n');
            }

            // Llamada a la funcion modular
            if (agregarTarea(listaTareas, nombre, descripcion, dias, promedio, respuesta)) {
                printf("Solicitud registrada con exito.\n");
            }

        } else if (opcion == 2) {
            if (listaTareas.empty()) {
                printf("No hay tareas para actualizar.\n");
                continue;
            }

            string nombreBuscar, nuevoEstado;
            int nuevosDias, leidos;

            printf("Ingrese el nombre exacto de la tarea a actualizar: ");
            getline(cin, nombreBuscar);

            printf("Ingrese el nuevo estado (Preseleccionada, Aprobada o Rechazada): ");
            getline(cin, nuevoEstado);

            printf("Ingrese los nuevos dias para el vencimiento: ");
            leidos = scanf("%d", &nuevosDias);
            while (getchar() != '\n');

            while (leidos != 1 || nuevosDias <= 0) {
                printf("Error: ingrese un numero mayor a 0: ");
                leidos = scanf("%d", &nuevosDias);
                while (getchar() != '\n');
            }

            if (actualizarTarea(listaTareas, nombreBuscar, nuevoEstado, nuevosDias)) {
                printf("Tarea actualizada correctamente.\n");
            }

        } else if (opcion == 3) {
            mostrarTareas(listaTareas);
        } else if (opcion != 4) {
            printf("Opcion invalida.\n");
        }

    } while (opcion != 4);

    printf("Saliendo del programa...\n");
    return 0;
}
