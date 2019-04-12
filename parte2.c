#include <stdlib.h>
#include <string.h>
#include "glist.h"
#include "util.h"

// TODO: cambiar documentacion sobre maps y filters usados
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

// map_y_escribir: GList char* FMap FEscritora  FCopiadora -> GList
// Recibe una lista, un nombre de archivo, una FMap, una FEscritora y una
// FCopiadora,
// Aplica la FMap a una copia (creada por la FCopiadora) de cada dato de la
// lista. Escribe un archivo con el nombre recibido y contenido generado por la
// FEscritora sobre esta nueva lista,
// Devuelve esta nueva lista.
GList map_y_escribir(GList lista, char *nombre, FMap f, FEscritora e,
                     FCopiadora copiar) {
  GList nuevaLista = glist_map(lista, f, copiar);
  glist_a_archivo(nuevaLista, nombre, e);
  return nuevaLista;
}

// filter_y_escribir: GList char* FPredicado FEscritora FCopiadora -> GList
// Recibe una lista, un nombre de archivo, una FPredicado, una FEscritora y una
// FCopiadora,
// Filtra la lista creando una copia (aplicando la FCopiadora) de cada elemento
// que satisface la FPredicado. Escribe un archivo con el nombre recibido y
// contenido generado por la FEscritora sobre esta nueva lista,
// Devuelve esta nueva lista.
GList filter_y_escribir(GList lista, char *nombre, FPredicado p, FEscritora e,
                        FCopiadora copiar) {
  GList nuevaLista = glist_filter(lista, p, copiar);
  glist_a_archivo(nuevaLista, nombre, e);
  return nuevaLista;
}

void *parse_persona(void *dato) {
  Persona *persona = malloc(sizeof(Persona));

  persona->nombre = malloc(sizeof(char) * strlen(dato));
  persona->lugarDeNacimiento = malloc(sizeof(char) * strlen(dato));

  sscanf(dato, "%[^,], %d, %[^\n]", persona->nombre, &persona->edad,
         persona->lugarDeNacimiento);

  free(dato);

  persona->nombre =
      realloc(persona->nombre, sizeof(char) * (strlen(persona->nombre) + 1));
  persona->lugarDeNacimiento =
      realloc(persona->lugarDeNacimiento,
              sizeof(char) * (strlen(persona->lugarDeNacimiento) + 1));

  return persona;
}

// envejecer: void* -> void*
// Recibe un puntero a un dato (Persona*),
// Le suma 100 años a su edad,
// Devuelve la persona.
// Esta funcion es de tipo FMap.
void *envejecer(void *dato) {
  Persona *persona = dato;
  persona->edad += 100;
  return persona;
}

// argentinizar?persona: void* -> void*
// Recibe un puntero a un dato (Persona*),
// Cambia el lugarDeNacimiento a "Argentina",
// Devuelve la persona.
// Esta funcion es de tipo FMap.
void *argentinizar_persona(void *dato) {
  Persona *persona = dato;
  free(persona->lugarDeNacimiento);
  persona->lugarDeNacimiento = copiar_cadena("Argentina");

  return persona;
}

// tiene_nombre_corto: void* -> int
// Recibe un puntero a un dato (Persona*),
// Devuelve verdadero si la longitud del nombre es menor o igual a 6, falso en
// caso contrario.
// Esta funcion es de tipo FPredicado.
int tiene_nombre_corto(void *dato) {
  return strlen(((Persona *)dato)->nombre) <= 6;
}

// es_mayor_de_edad: void* -> int
// Recibe un puntero a un dato (Persona*),
// Devuelve verdadero si la edad es mayor o igual a 18, falso en caso contrario.
// Esta funcion es de tipo FPredicado.
int es_mayor_de_edad(void *dato) { return ((Persona *)dato)->edad >= 18; }

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error: El número de argumentos ingresados es incorrecto.\n");
    printf("Modo de uso: %s [personas.txt]\n", argv[0]);
    return -1;
  }

  GList personasRaw = glist_desde_archivo(argv[1], 1);
  GList personas = glist_map(personasRaw, parse_persona, copiar_cadena);
  glist_destruir(personasRaw, destruir_cadena);

  glist_recorrer(personas, imprimir_persona);

  // Maps
  // 1)
  GList envejecidas = map_y_escribir(personas, "envejecidas.txt", envejecer,
                                     escribir_persona, copiar_persona);
  glist_destruir(envejecidas, destruir_persona);
  // 2)
  GList argentinizados =
      map_y_escribir(personas, "argentinizados.txt", argentinizar_persona,
                     escribir_persona, copiar_persona);
  glist_destruir(argentinizados, destruir_persona);

  // Filters
  // 1)
  GList conNombresCortos =
      filter_y_escribir(personas, "con_nombres_cortos.txt", tiene_nombre_corto,
                        escribir_persona, copiar_persona);
  glist_destruir(conNombresCortos, destruir_persona);
  // 2)
  GList mayoresDeEdad =
      filter_y_escribir(personas, "mayores_de_edad.txt", es_mayor_de_edad,
                        escribir_persona, copiar_persona);
  glist_destruir(mayoresDeEdad, destruir_persona);

  glist_destruir(personas, destruir_persona);

  return 0;
}
