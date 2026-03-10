#ifndef FUNCIONES_H
#define FUNCIONES_H

int leer_entero(const char *prompt, int *out);
int leer_float(const char *prompt, float *out);
int leer_cadena(const char *prompt, char *dst, size_t cap);

#define max_producto 10

typedef struct {
    int id;
    char nombre[20];
    float precio;
    int stock;
} Producto;

int contar_productos(Producto p[], int n);
void imprimir(Producto p[], int n);
void anadir(Producto p[], int n);
void modificar(Producto p[]);
#endif