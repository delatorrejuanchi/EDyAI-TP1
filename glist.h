#ifndef __GLIST_H__
#define __GLIST_H__

#include <stdio.h>

typedef void (*FDestructora)(void *dato);
typedef void (*FVisitante)(void *dato);
typedef void (*FEscritora)(void *dato, FILE *archivo);
typedef void *(*FCopiadora)(void *dato);
typedef void *(*FMap)(void *dato);
typedef int (*FPredicado)(void *dato);

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

// glist_crear: -> GList
// Devuelve una lista vacía
GList glist_crear();

// TODO: corregir
// glist_destruir: GList -> void;
// Recibe una lista,
// La destruye.
void glist_destruir(GList lista, FDestructora destruir);

// glist_vacia: GList -> int;
// Recibe una lista,
// Devuelve 1 si la lista es vacía, 0 en caso contrario.
int glist_vacia(GList lista);

// glist_agregar_inicio: GList void* -> GList
// Recibe una lista y un puntero a un dato,
// Lo agrega al inicio,
// Devuelve la lista.
GList glist_agregar_inicio(GList lista, void *dato);

// glist_agregar_final: GList void* -> GList
// Recibe una lista y un puntero a un dato,
// Lo agrega al final,
// Devuelve la lista.
GList glist_agregar_final(GList lista, void *dato);

// glist_recorrer: GList FVisitante -> void
// Recibe una lista y una FVisitante,
// Recorre la lista y ejecuta la FVisitante al dato de cada nodo.
void glist_recorrer(GList lista, FVisitante visitar);

// glist_longitud: GList -> int
// Recibe una lista,
// Devuelve la longitud de la lista.
int glist_longitud(GList lista);

// glist_dato_random: GList -> void*
// Recibe una lista,
// Devuelve el dato de un nodo de la lista (elegido al azar)
void *glist_dato_random(GList lista);

// glist_desde_archivo: char* -> GList
// Recibe un nombre de archivo,
// Crea y devuelve una lista cuyos nodos contienen las lineas del archivo.
// Si el archivo no existe, devuelve NULL.
GList glist_desde_archivo(char *nombre);

// glist_a_archivo: GList char* FEscritora -> void
// Recibe una lista, un nombre de archivo y una FEscritora,
// Recorre la lista y ejecuta la FEscritora con el dato de cada nodo,
// escribiendo asi un archivo con el nombre recibido y contenido generado por la
// FEscritora.
void glist_a_archivo(GList lista, char *nombre, FEscritora escribir);

// TODO: corregir
// glist_map: GList FMap -> GList
// Recibe una lista y una FMap,
// Crea y devuelve una lista cuyos datos son los resultados de aplicar la FMap a
// cada dato de la lista recibida.
GList glist_map(GList lista, FMap f, FCopiadora copiar);

// TODO: corregir
// glist_filter: GList FPredicado -> GList
// Recibe una lista y una FPredicado,
// Crea y devuelve una lista cuyos datos son solo aquellos para los cuales la
// FPredicado aplicada a cada dato devuelve verdadero.
GList glist_filter(GList lista, FPredicado p, FCopiadora copiar);

#endif /* __GLIST_H__ */
