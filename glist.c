#include "glist.h"
#include <stdlib.h>
#include <string.h>
#include "util.h"

GList glist_crear() { return NULL; }

void glist_destruir(GList lista) {
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int glist_vacia(GList lista) { return lista == NULL; }

GList glist_agregar_inicio(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

GList glist_agregar_final(GList lista, void *dato) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  GNodo *nodo = lista;
  while (nodo != NULL) nodo = nodo->sig;

  nodo->sig = nuevoNodo;
  return lista;
}

void glist_recorrer(GList lista, FVisitante visitar) {
  for (GNodo *nodo = lista; nodo != NULL; nodo = nodo->sig) visitar(nodo->dato);
}

int glist_longitud(GList lista) {
  int longitud = 0;
  for (GList i = lista; i != NULL; i = i->sig) longitud++;
  return longitud;
}

void *glist_dato_random(GList lista) {
  int tamano = glist_longitud(lista);

  int indice = rand() % tamano;
  GNodo *nodo = lista;
  for (int i = 0; i < indice; i++) nodo = nodo->sig;

  return nodo->dato;
}

GList glist_desde_archivo(char *nombre) {
  FILE *archivo = fopen(nombre, "r");

  if (archivo == NULL) return NULL;

  GList lista = glist_crear();

  char *linea;
  while ((linea = get_line(archivo)) != NULL) {
    lista = glist_agregar_inicio(lista, linea);
  }

  fclose(archivo);
  return lista;
}

void glist_a_archivo(GList lista, char *nombre, FEscritora escribir) {
  FILE *archivo;
  archivo = fopen(nombre, "w+");

  for (GNodo *nodo = lista; nodo != NULL; nodo = nodo->sig) {
    escribir(nodo->dato, archivo);
  }

  fclose(archivo);
}

GList glist_map(GList lista, FMap f) {
  GList nuevaLista = glist_crear();
  for (GNodo *nodo = lista; nodo != NULL; nodo = nodo->sig) {
    nuevaLista = glist_agregar_inicio(nuevaLista, f(nodo->dato));
  }

  return nuevaLista;
}

GList glist_filter(GList lista, FPredicado p) {
  GList nuevaLista = glist_crear();
  for (GNodo *nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (p(nodo->dato))
      nuevaLista = glist_agregar_inicio(nuevaLista, nodo->dato);
  }

  return nuevaLista;
}
