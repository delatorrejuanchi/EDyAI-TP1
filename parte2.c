#include <stdlib.h>
#include <string.h>
#include "glist.h"
#include "util.h"

GList map_y_escribir(GList lista, char *nombre, FMap f, FEscritora e) {
  GList nuevaLista = glist_map(lista, f);
  glist_a_archivo(nuevaLista, nombre, e);
  return nuevaLista;
}

GList filter_y_escribir(GList lista, char *nombre, FPredicado p, FEscritora e) {
  GList nuevaLista = glist_filter(lista, p);
  glist_a_archivo(nuevaLista, nombre, e);
  return nuevaLista;
}

void *parse_persona(void *dato) {
  Persona *persona = malloc(sizeof(Persona));
  persona->nombre = malloc(sizeof(char) * strlen(dato));
  persona->lugarDeNacimiento = malloc(sizeof(char) * strlen(dato));

  sscanf(dato, "%[^,], %d, %[^\n]", persona->nombre, &persona->edad,
         persona->lugarDeNacimiento);

  persona->nombre = realloc(persona->nombre, strlen(persona->nombre));
  persona->lugarDeNacimiento =
      realloc(persona->lugarDeNacimiento, strlen(persona->lugarDeNacimiento));

  return persona;
}

// FMap
void *envejecer(void *dato) {
  Persona *persona = duplicar_persona(dato);
  persona->edad += 100;
  return persona;
}

void *obtener_nombre(void *dato) {
  Persona *persona = dato;
  char *nombre = malloc(sizeof(char) * strlen(persona->nombre));
  strcpy(nombre, persona->nombre);
  return nombre;
}

int main() {
  GList personasRaw = glist_desde_archivo("personas.txt");
  GList personas = glist_map(personasRaw, parse_persona);
  glist_destruir(personasRaw);

  glist_recorrer(personas, imprimir_persona);

  // Maps
  // 1)
  GList envejecidas =
      map_y_escribir(personas, "envejecidas.txt", envejecer, escribir_persona);
  glist_recorrer(envejecidas, imprimir_persona);
  // 2)
  GList nombres =
      map_y_escribir(personas, "nombres.txt", obtener_nombre, escribir_cadena);
  glist_recorrer(nombres, imprimir_cadena);

  // Filters
  // 1)
  // 2)

  return 0;
}
