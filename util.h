#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>

typedef struct {
  char *nombre;
  int edad;
  char *lugarDeNacimiento;
} Persona;

Persona *duplicar_persona(Persona *persona);

char *get_line(FILE *archivo);

void escribir_persona(void *dato, FILE *archivo);
void escribir_cadena(void *dato, FILE *archivo);

void imprimir_persona(void *dato);
void imprimir_cadena(void *dato);

#endif /* __UTIL_H__ */
