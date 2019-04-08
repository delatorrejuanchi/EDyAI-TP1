#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento;
} Persona;

char *get_line(FILE *archivo);

void escribir_persona(void *dato, FILE *archivo);
void escribir_cadena(void *dato, FILE *archivo);

void imprimir_persona(void *dato);
void imprimir_cadena(void *dato);

void destruir_persona(void *dato);
void destruir_cadena(void *dato);

void *copiar_persona(void *dato);
void *copiar_cadena(void *dato);

#endif /* __UTIL_H__ */
