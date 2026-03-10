#include <stdio.h>
#include "funciones.h"

int main(void) {
    Producto p[max_producto] = {
        {1, "Refresco", 1.50, 6},
        {2, "Chocolatina", 0.80, 10},
        {3, "Snack", 1.60, 8},
        {4, "Agua", 1.20, 15},
        {5, "Sandwich", 2.30, 7}
    };
    int op;
    do {
        int contador = contar_productos(p, max_producto);
        printf("Numero de productos: %d\n", contador);

        printf("===MENU===\n");
        printf("1. Listar\n");
        printf("2. Anadir\n");
        printf("3. Modificar\n");
        printf("4. Salir\n");

        if (!leer_entero("Opcion: ", &op)) return 0;
        switch (op) {
            case 1: printf("Listar\n");
                imprimir(p, contador);
                break;
            case 2: printf("Anadir\n");
                anadir(p, contador);
                break;
            case 3: printf("Modificar\n");
                modificar(p);
                break;
            case 4: printf("Salir\n"); break;
            default: printf("Acción no válida\n"); break;
        }
    } while (op != 4);
}