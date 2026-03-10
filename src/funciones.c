#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"

int leer_entero(const char *prompt, int *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0; // EOF
        errno = 0; // variable global de error en strol
        char *end = NULL;
        long v = strtol(buf, &end, 10);
        // Saltar espacios finales
        while (end && isspace((unsigned char)*end)) end++;

        if (errno == 0 && end && *end == '\0') {
            *out = (int)v;
            return 1;
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}
int leer_float(const char *prompt, float *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        errno = 0; // variable global de error en strof
        char *end = NULL;
        float v = strtof(buf, &end);
        while (end && isspace((unsigned char)*end)) end++;
        if (errno == 0 && end && *end == '\0') {
            *out = v;
            return 1;
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}
int leer_cadena(const char *prompt, char *dst, size_t cap) {
    printf("%s", prompt);
    if (!fgets(dst, cap, stdin)) return 0;
    // quitar \n si existe
    size_t n = strlen(dst);
    if (n > 0 && dst[n - 1] == '\n')
        dst[n - 1] = '\0';
    return 1;
}
int contar_productos(Producto p[], int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].id != 0) {
            contador++;
        }
    }
    return contador;
}
void imprimir(Producto p[], int n) {
    printf("-----PRODUCTOS-----\n"
           "ID   Nombre%9s  Precio  Stock\n", "");

    for (int i = 0; i < n; i++) {
        printf("%-2d | %-15s | %.2f | %d\n",
        p[i].id, p[i].nombre, p[i].precio, p[i].stock
        );
    }
    printf("\n");
}
void anadir(Producto p[], int n) {
    if (n >= max_producto) {
        printf("Limite de productos alcanzado\n");
        return;
    }
    p[n].id = n + 1;
    if (!leer_cadena("Nombre: ", p[n].nombre, 20)) return;
    if (!leer_float("Precio: ", &p[n].precio)) return;
    if (!leer_entero("Stock: ", &p[n].stock)) return;

    //poscion del vector que quiero cambiar p[4] -> id 5, asi que van descompensados por eso, en este caso
    //n = 5 (inicialmente) le sumo 1 para que el id sea 6 pero n sigue siendo 5 que para la posición del vector
    //p[5] -> id 6: Correcto.

    printf("ID: %d, Nombre: %s, Precio: %.2f, Stock: %d\n\n",
        p[n].id, p[n].nombre, p[n].precio, p[n].stock);
    n++;
    //Error dado: tenía puesto el n++ antes de leer, como el vector empieza
    //por 0 estaba añadiendo el producto en una posicion más a la que deberia ser.
}
void modificar(Producto p[]) {
    int n_select;
    if (!leer_entero("Introduzca el ID del producto a modificar: ", &n_select)) return;

    n_select--;
    // PONGO -1 PORQUE EN LA POSCION P[0] LE CORRESPONDE EL ID 1, POR LO TANTO PARA QUE ESTÉN SINCRONIZADOS
    //DEBO RESTARLE 1.

    if (n_select >= max_producto || p[n_select].id == 0) {
        printf("Producto no encontrado\n");
    } else {
        if (!leer_cadena("Nuevo producto: ", p[n_select].nombre, 20)) return;
        if (!leer_float("Precio: ", &p[n_select].precio)) return;
        if (!leer_entero("Stock: ", &p[n_select].stock)) return;
    }
    printf("ID: %d, Nombre: %s, Precio: %.2f, Stock: %d\n\n",
        p[n_select].id, p[n_select].nombre, p[n_select].precio, p[n_select].stock);
}