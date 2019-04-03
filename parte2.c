#include <stdlib.h>
#include <string.h>
#include "glist.h"
#include "util.h"

// MODO DE USO:
// Si no lo hizo todavia, compile ejecutando:
//  $ gcc -c util.c -Wall -pedantic
//  $ gcc -c glist.c -Wall -pedantic
//  $ gcc -o parte2 parte2.c glist.o util.o -Wall -pedantic
// Luego:
//  $ ./parte2 [personas.txt]
// Lee la lista de personas en [personas.txt], y crea 4 archivos usando las
// funciones glist_map y glist_filter.
// glist_map:
// - "envejecidas.txt": contiene los datos de las personas pero con 100 años mas
// - "solo_nombres.txt": contiene solo los nombres de las personas
// glist_filter:
// - "con_nombres_cortos.txt": contiene solo los datos de las personas cuyos
//                             nombres tienen 6 caracteres o menos.
// - "mayores_de_edad.txt": contiene solo los datos de las personas mayores de
//                          edad
// El archivo a recibir tiene las caracteristicas iguales al archivo de salida
// de la parte 1.

// map_y_escribir: GList char* FMap FEscritora -> GList
// Recibe una lista, un nombre de archivo, una FMap y una FEscritora,
// Escribe un archivo con el nombre recibido y contenido generado por la
// FEscritora sobre una nueva lista generada por la FMap aplicada a la lista
// recibida,
// Devuelve esta nueva lista
GList map_y_escribir(GList lista, char *nombre, FMap f, FEscritora e) {
  GList nuevaLista = glist_map(lista, f);
  glist_a_archivo(nuevaLista, nombre, e);
  return nuevaLista;
}

// filter_y_escribir: GList char* FPredicado FEscritora -> GList
// TODO: completar
GList filter_y_escribir(GList lista, char *nombre, FPredicado p, FEscritora e) {
  GList nuevaLista = glist_filter(lista, p);
  glist_a_archivo(nuevaLista, nombre, e);
  return nuevaLista;
}

// TODO: completar
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

// TODO: completar
void *envejecer(void *dato) {
  Persona *persona = duplicar_persona(dato);
  persona->edad += 100;
  return persona;
}

// TODO: completar
void *obtener_nombre(void *dato) {
  Persona *persona = dato;
  char *nombre = malloc(sizeof(char) * strlen(persona->nombre));
  strcpy(nombre, persona->nombre);
  return nombre;
}

// TODO: completar
int tiene_nombre_corto(void *dato) {
  return strlen(((Persona *)dato)->nombre) <= 6;
}

// TODO: completar
int es_mayor_de_edad(void *dato) { return ((Persona *)dato)->edad >= 18; }

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: El número de argumentos ingresados es incorrecto.\n");
    printf("Modo de uso: %s [personas.txt]\n", argv[0]);
    return -1;
  }

  GList personasRaw = glist_desde_archivo(argv[1]);
  GList personas = glist_map(personasRaw, parse_persona);
  glist_destruir(personasRaw);

  glist_recorrer(personas, imprimir_persona);

  // Maps
  // 1)
  map_y_escribir(personas, "envejecidas.txt", envejecer, escribir_persona);
  // 2)
  map_y_escribir(personas, "solo_nombres.txt", obtener_nombre, escribir_cadena);

  // Filters
  // 1)
  filter_y_escribir(personas, "con_nombres_cortos.txt", tiene_nombre_corto,
                    escribir_persona);
  // 2)
  filter_y_escribir(personas, "mayores_de_edad.txt", es_mayor_de_edad,
                    escribir_persona);

  return 0;
}
