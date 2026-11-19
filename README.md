# Sistema de Gestión de Tareas - Evaluación de Becas (Universidad KRL)

Proyecto desarrollado para el **Desafío 02: Diseño modular del sistema de gestión de tareas**. Implementa un algoritmo modular en C++ para registrar, actualizar y consultar solicitudes de becas de acceso universitario, asegurando la integridad de los datos y el cumplimiento de los criterios de elegibilidad.

## Estructura del Proyecto
* `src/Desafio2_Tarea.cpp`: Código fuente en C++ con las funciones modulares (`agregarTarea`, `actualizarTarea`, `mostrarTareas` y `existeTarea`) y el menú interactivo principal.
* `docs/`: Documentación del diseño actualizado (diagramas de flujo, pseudocódigo y justificación de las decisiones de modularización).

## Reglas del Sistema
* **Validaciones de Integridad:** El nombre del postulante no puede estar vacío ni repetirse; los días restantes para el vencimiento deben ser mayores a 0; el promedio debe estar entre 0 y 10.
* **Criterios de Elegibilidad:** Solo se registran en la lista (con estado inicial `"Preseleccionada"`) aquellas solicitudes que cuenten con promedio igual o superior a 9.5, ciudadanía argentina y residencia en zona sur.

## Instrucciones de Uso
1. **Compilación:** Abrir `src/Desafio2_Tarea.cpp` en Dev-C++ (compilar y ejecutar con `F11`) o compilar desde la terminal mediante `g++`:
   ```bash
   g++ src/Desafio2_Tarea.cpp -o gestion_becas