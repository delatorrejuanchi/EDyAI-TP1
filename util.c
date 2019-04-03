#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Persona *duplicar_persona(Persona *persona) {
  Persona *personaNueva = malloc(sizeof(Persona));
  personaNueva->nombre = malloc(sizeof(char) * strlen(persona->nombre));
  strcpy(personaNueva->nombre, persona->nombre);
  personaNueva->edad = persona->edad;
  personaNueva->lugarDeNacimiento =
      malloc(sizeof(char) * strlen(persona->lugarDeNacimiento));
  strcpy(personaNueva->lugarDeNacimiento, persona->lugarDeNacimiento);

  return personaNueva;
}

char *get_line(FILE *archivo) {
  int tamano = 16;
  char *buffer = malloc(sizeof(char) * tamano);

  char c = fgetc(archivo);
  while ((c == '\n' || c == '\r') && c != EOF) c = fgetc(archivo);
  if (c == EOF) return NULL;

  int i = 0;
  while ((c != '\n' && c != '\r')) {
    if (i == tamano) {
      tamano *= 2;
      buffer = realloc(buffer, tamano);
    }

    buffer[i++] = c;
    c = fgetc(archivo);
  }
  buffer[i] = '\0';

  buffer = realloc(buffer, sizeof(char) * strlen(buffer));
  return buffer;
}

// imprimir_persona: void* -> void
// Recibe un puntero a un dato (Persona*),
// Muestra en pantalla los datos de la persona con el formato:
// "nombre, edad, lugarDeNacimiento"
// Esta funcion es de tipo FVisitante.
void imprimir_persona(void *dato) {
  Persona *persona = dato;
  printf("%s, %d, %s\n", persona->nombre, persona->edad,
         persona->lugarDeNacimiento);
}

// imprimir_cadena: void* -> void
// Recibe un puntero a un dato (char*),
// Muestra en pantalla el contenido de la cadena.
// Esta funcion es de tipo FVisitante.
void imprimir_cadena(void *dato) { printf("%s\n", (char *)dato); }

// escribir_persona: void* FILE* -> void
// Recibe un puntero a un dato (Persona*) y un puntero a un archivo,
// Escribe una linea en el archivo con los datos de la persona con el formato:
// "nombre, edad, lugarDeNacimiento"
// Esta funcion es de tipo FEscritora.
void escribir_persona(void *dato, FILE *archivo) {
  Persona *persona = dato;
  fprintf(archivo, "%s, %d, %s\n", persona->nombre, persona->edad,
          persona->lugarDeNacimiento);
}

// escribir_cadena: void* FILE* -> void
// Recibe un puntero a un dato (char*) y un puntero a un archivo,
// Escribe una linea en el archivo con el contenido de la cadena.
// Esta funcion es de tipo FEscritora.
void escribir_cadena(void *dato, FILE *archivo) {
  fprintf(archivo, "%s\n", (char *)dato);
}
