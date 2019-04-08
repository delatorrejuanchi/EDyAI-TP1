#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_BUFFER_INICIAL 32

// TODO: ver el tema de los caracteres especiales
// TODO: completar
char *get_line(FILE *archivo) {
  int tamano = TAMANO_BUFFER_INICIAL;

  char c = fgetc(archivo);
  while ((c == '\n' || c == '\r') && c != EOF) c = fgetc(archivo);
  if (c == EOF) return NULL;

  char *line = malloc(sizeof(char) * (tamano + 1));

  int i = 0;
  while ((c != '\n' && c != '\r')) {
    if (i == tamano) {
      tamano *= 2;
      line = realloc(line, sizeof(char) * (tamano + 1));
    }

    line[i++] = c;
    c = fgetc(archivo);
  }
  line[i] = '\0';

  line = realloc(line, sizeof(char) * (strlen(line) + 1));

  return line;
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

// TODO: completar
void destruir_cadena(void *dato) { free(dato); }

// TODO: completar
void destruir_persona(void *dato) {
  Persona *persona = dato;
  free(persona->nombre);
  free(persona->lugarDeNacimiento);
  free(persona);
}

// TODO: completar
void *copiar_persona(void *dato) {
  Persona *persona = dato;
  Persona *nueva = malloc(sizeof(Persona));
  nueva->nombre = malloc(sizeof(char) * (strlen(persona->nombre) + 1));
  strcpy(nueva->nombre, persona->nombre);
  nueva->edad = persona->edad;
  nueva->lugarDeNacimiento =
      malloc(sizeof(char) * (strlen(persona->lugarDeNacimiento) + 1));
  strcpy(nueva->lugarDeNacimiento, persona->lugarDeNacimiento);

  return nueva;
}

void *copiar_cadena(void *dato) {
  char *nuevaCadena = malloc(sizeof(char) * (strlen(dato) + 1));
  strcpy(nuevaCadena, dato);
  return nuevaCadena;
}
