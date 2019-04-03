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

void escribir_persona(void *dato, FILE *archivo) {
  Persona *persona = dato;
  fprintf(archivo, "%s, %d, %s\n", persona->nombre, persona->edad,
          persona->lugarDeNacimiento);
}

void escribir_cadena(void *dato, FILE *archivo) {
  fprintf(archivo, "%s\n", (char *)dato);
}

void imprimir_persona(void *dato) {
  Persona *persona = dato;
  printf("%s, %d, %s\n", persona->nombre, persona->edad,
         persona->lugarDeNacimiento);
}

void imprimir_cadena(void *dato) { printf("%s\n", (char *)dato); }
