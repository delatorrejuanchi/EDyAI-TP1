#include <stdlib.h>
#include <string.h>
#include "glist.h"
#include "util.h"

// MODO DE USO:
// Si no lo hizo todavia, para copilar debe ejecutar los siguientes comandos:
//  $ gcc -c util.c -Wall -pedantic
//  $ gcc -c glist.c -Wall -pedantic
//  $ gcc -o parte2 parte2.c glist.o util.o -Wall -pedantic
// Luego:
//  $ ./parte2 [personas.txt]

// El archivo a recibir tiene las caracteristicas iguales al archivo de salida
// de la parte 1

// map_y_escribir: GList char* FMap FEscritora -> GList
// Recibe una lista, un nombre de archivo, una FMap y una FEscritora,
// Aplica map usando FMap a la lista y escribe un archivo con el nombre recibido
// y el contenido generado por la FEscritora sobre la nueva lista. Devuelve la
// nueva lista
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

// FPredicado
int tiene_nombre_corto(void *dato) {
  return strlen(((Persona *)dato)->nombre) <= 6;
}

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
