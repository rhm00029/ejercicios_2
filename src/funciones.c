#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"

int leer_entero(const char *prompt, int *out) {
    // lee como entero un input (entradas: prompt donde se pone el input, out hacia donde se guarda
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        // lee lo que se escriba desde stdin usando fgets
        if (!fgets(buf, sizeof(buf), stdin)) return 0; // EOF
        errno = 0; // variable global de error en strol
        char *end = NULL;
        long v = strtol(buf, &end, 10); //convierte la cadena a número
        // Saltar espacios finales
        while (end && isspace((unsigned char)*end)) end++;

        if (errno == 0 && end && *end == '\0') {
            *out = (int)v;
            return 1; // si ha sido correcto devuelve 1 si no 0
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}
int leer_float(const char *prompt, float *out) {
    // lee como float un input (entradas: prompt donde se pone el input, out hacia donde se guarda
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        // lee lo que se escriba desde stdin usando fgets
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        errno = 0; // variable global de error en strof
        char *end = NULL;
        float v = strtof(buf, &end); // convierte la cadena a float
        while (end && isspace((unsigned char)*end)) end++;
        if (errno == 0 && end && *end == '\0') {
            *out = v;
            return 1; //si ha sido correcto devuelve 1 si no 0
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}
int leer_cadena(const char *prompt, char *dst, size_t cap) {
    // lee un input como string (entradas: prompt donde se pone el input, dst hacia donde se guarda, cap maximo de caracteres
    printf("%s", prompt);
    // lee la cadena que se ha escrito respetando el límite de cap
    if (!fgets(dst, cap, stdin)) return 0;
    // quitar \n si existe
    size_t n = strlen(dst);
    if (n > 0 && dst[n - 1] == '\n') //comprueba si termina por \n y la cambia por \0
        dst[n - 1] = '\0';
    return 1; // si ha sido correcto devolverá 1, si no 0
}
int guardar_texto(const char *ruta, const Producto *arr, int n) {
    // guarda los productos en un .txt (entrada: ruta a la que se guarda, nombre del array de la estrucuta, cantidad que se guarda
    FILE *f = fopen(ruta, "w");
    // abre el archivo (o lo crea) desde la ruta impuesta, si no se abre devuelve 0
    if (!f) return 0;
    for (int i = 0; i < n; i++) {
        // imprime en el archivo los productos
        fprintf(f, "%d;%s;%.2f;%d\n",
        arr[i].id, arr[i].nombre, arr[i].precio, arr[i].stock);
    }
    fclose(f);
    return 1; // si ha sido correcto devuelve 1
}
int cargar_texto(const char *ruta, Producto *arr, int cap) {
    //carga los productos de un .txt (entrada: ruta a la que se guarda, nombre del array de la estrucuta, valor maximo
    FILE *f = fopen(ruta, "r");
    if (!f) return 0;
    //abre el archivo (o lo crea) desde la ruta impuesta, si no se abre devuelve 0
    char linea[256];
    int n = 0;

    while (n < cap && fgets(linea, sizeof(linea), f)) {
        // quitar \n
        size_t L = strlen(linea);
        if (L && linea[L-1] == '\n') linea[L-1] = '\0'; // si termina por \n lo cambia por \0
        Producto p;
        // parsing simple: ojo, esto NO valida a prueba de balas (mejorarlo como ejercicio)
        if (sscanf(linea, "%d;%31[^;];%f;%d", &p.id, p.nombre, &p.precio, &p.stock) == 4) {
            arr[n++] = p;
        }
    }
    fclose(f);
    return 1;
}
int guardar_bin(const char *ruta, const Producto *arr, int n) {
    // guarda los productos en un .bin (entrada: ruta a la que se guarda, nombre del array de la estrucuta, cantidad que se guarda

    FILE *f = fopen(ruta, "wb");
    if (!f) return 0; // si no se abre correctamente devolverá un 0, en cualquier otro caso 1
    // guardamos primero el contador
    fwrite(&n, sizeof(n), 1, f);
    // luego el array
    fwrite(arr, sizeof(Producto), (size_t)n, f);
    fclose(f);
    return 1;
}
int cargar_bin(const char *ruta, Producto *arr, int cap) {
    //carga los productos de un .bin (entrada: ruta a la que se guarda, nombre del array de la estrucuta, valor maximo

    FILE *f = fopen(ruta, "rb"); //si no se abre correctamente devolverá un 0, en cualquier otro caso 1
    if (!f) return 0;
    int n = 0;
    // si da algun problema el fread, n sea negativo, supere el maximo, ... que cierre el
    // archivo y devuelva un 0
    if (fread(&n, sizeof(n), 1, f) != 1) { fclose(f); return 0; }
    if (n < 0 || n > cap) { fclose(f); return 0; }
    if (fread(arr, sizeof(Producto), (size_t)n, f) != (size_t)n) {
        fclose(f); return 0;
    }
    fclose(f);
    return 1; // si es correcto devuelve 1
}
int contar_productos(Producto p[], int n) {
    // funcion que cuenta los productos que hay (entrada: array de la estructura, maximo de producto. Salida: variable contador)
    // inicializo la variable contador a 0
    int contador = 0;
    // creo un for que va comprobando los ids de los distintos productos, si existen suma 1 al contador
    // si llega a un producto cuyo id es 0 para y devuelve el valor del contador.
    for (int i = 0; i < n; i++) {
        if (p[i].id != 0) {
            contador++;
        }
    }
    return contador;
}
void imprimir(Producto p[], int n) {
    // funcion que imprime los productos(entradas: array de la estructura, numero de productos
    // creo la plantilla de columnas para estructurar los datos
    printf("-----PRODUCTOS-----\n"
           "ID   Nombre%9s  Precio  Stock\n", "");
    // copio los productos existentes y paro cuando llegue al valor del contador
    for (int i = 0; i < n; i++) {
        printf("%-2d | %-15s | %.2f | %d\n",
        p[i].id, p[i].nombre, p[i].precio, p[i].stock
        );
    }
    printf("\n");
}
void anadir(Producto p[], int n) {
    //funcion que añade un nuevo producto (entradas: array de la estructura, numero de productos
    // si se pretende añadir un producto cuando ya hallan 10 (que es el máximo) dará un mensaje de error.
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
    // funcion que modifica el valor de un producto (entradas: array de la estructura
    // creo una variable que rellenaré para saber que producto quiero modificar
    int n_select;
    if (!leer_entero("Introduzca el ID del producto a modificar: ", &n_select)) return;

    n_select--;
    // PONGO -1 PORQUE EN LA POSCION P[0] LE CORRESPONDE EL ID 1, POR LO TANTO PARA QUE ESTÉN SINCRONIZADOS
    //DEBO RESTARLE 1.

    // si he puesto un valor mayor al limite de la estructura o he seleccionado un producto no
    // existente (id = 0) saldrá un mensaje de error.
    if (n_select >= max_producto || p[n_select].id == 0) {
        printf("Producto no encontrado\n");
    } else {
        if (!leer_cadena("Nuevo producto: ", p[n_select].nombre, 20)) return;
        if (!leer_float("Precio: ", &p[n_select].precio)) return;
        if (!leer_entero("Stock: ", &p[n_select].stock)) return;
    }
    // mostramos el producto modificado
    printf("ID: %d, Nombre: %s, Precio: %.2f, Stock: %d\n\n",
        p[n_select].id, p[n_select].nombre, p[n_select].precio, p[n_select].stock);
}