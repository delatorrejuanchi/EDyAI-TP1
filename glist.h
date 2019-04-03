#ifndef __GLIST_H__
#define __GLIST_H__

#include <stdio.h>

typedef void (*FVisitante)(void *dato);
typedef void (*FEscritora)(void *dato, FILE *archivo);
typedef void *(*FMap)(void *dato);
typedef int (*FPredicado)(void *dato);

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruye la lista.
 */
void glist_destruir(GList lista);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al final de la lista.
 */
GList glist_agregar_final(GList lista, void* dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato);

/**
 * Recorrido de la lista, utilizando la FVisitante recibida como
 * parametro.
 */
void glist_recorrer(GList lista, FVisitante visitar);

/**
 * Devuelve la longitud de una lista.
 */
int glist_longitud(GList lista);

/**
 * Devuelve un dato al azar de la lista.
 */
void *glist_dato_random(GList lista);

/**
 * Crea una lista con las lineas de un archivo. Si el archivo no existe,
 * devuelve NULL.
 */
GList glist_desde_archivo(char *nombre);

/**
 * Escribe una lista a un archivo, recorriendo la lista y escribiendo cada nodo
 * con una FEscritora recibida como parametro.
 */
void glist_a_archivo(GList lista, char *nombre, FEscritora escribir);

/*
 * Devuelve una nueva lista con el resultado de aplicar a los elementos la
 * funcion pasada
 */
GList glist_map(GList lista, FMap f);

/*
 * Devuelve una nueva lista con los elementos que cumplen con el predicado dado
 */
GList glist_filter(GList lista, FPredicado p);

#endif /* __GLIST_H__ */
