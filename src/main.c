#include <stdio.h>
#include "funciones.h"

int main(void) {
    // inicializamos la estrucutura productos
    Producto p[max_producto] = {
        {1, "Refresco", 1.50, 6},
        {2, "Chocolatina", 0.80, 10},
        {3, "Snack", 1.60, 8},
        {4, "Agua", 1.20, 15},
        {5, "Sandwich", 2.30, 7}
    };
    int op;
    do {
        // llamo a una función que se encarga de contar los productos existentes.
        int contador = contar_productos(p, max_producto);
        printf("Numero de productos: %d\n", contador);

        printf("===MENU===\n");
        printf("1. Listar\n");
        printf("2. Anadir\n");
        printf("3. Modificar\n");
        printf("4. Guardar fichero texto\n");
        printf("5. Leer fichero texto\n");
        printf("6. Guardar fichero binario\n");
        printf("7. Leer fichero binario\n");
        printf("8. Salir\n");

        if (!leer_entero("Opcion: ", &op)) return 0;
        // comprobamos el valor de op que hemos seleccionado y se ejecutará lo que hallamos elegido
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
            case 4: printf("Guardar fichero texto\n\n");
                if (!guardar_texto("datos.txt",p, contador)) return 0;
                printf("Fichero guardado exitosamente\n\n");
                break;
            case 5: printf("Leer fichero texto\n");
                // inicializamos la estructura para que no se solapen los productos
                for (int i = 0; i < contador; i++) {
                    p[i].id = 0;
                    p[i].nombre[0] = '\0';
                    p[i].precio = 0;
                    p[i].stock = 0;
                }
                if (!cargar_texto("datos.txt",p,max_producto)) return 0;
                break;
            case 6: printf("Guardar fichero binario\n");
                if (!guardar_bin("datos.bin", p, contador)) return 0;
                printf("Fichero guardado exitosamente\n\n");
                break;
            case 7: printf("Leer fichero binario\n");
                // inicializamos la estructura para que no se solapen los productos
                for (int i = 0; i < contador; i++) {
                    p[i].id = 0;
                    p[i].nombre[0] = '\0';
                    p[i].precio = 0;
                    p[i].stock = 0;
                }
                if (!cargar_bin("datos.bin",p,max_producto)) return 0;
                break;
            case 8: printf("Salir\n"); break;
            default: printf("Accion no valida\n"); break;
        }
    } while (op != 8);
    // se repetirá el proceso de selección de opcion de menu hasta que elijas
    // salir (8) que entonces saldrá de la función y finalizará el programa.
}