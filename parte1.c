#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glist.h"
#include "util.h"

#define CANTIDAD 2000

// TODO: terminar la documentacion, revisar la de todas las funciones porque
// hubieron muchos cambios. Documentar como resolvemos el tema de los caracteres
// especiales y pensar si pueden haber bugs en ese tema. Explicar por que
// sacrificamos performance por usar una GList doblemente enlazada circular.

// MODO DE USO: Si no lo hizo todavia, compile
// ejecutando:
//  $ gcc -c util.c -Wall -pedantic
//  $ gcc -c glist.c -Wall -pedantic
//  $ gcc -o parte1 parte1.c glist.o util.o -Wall -pedantic
// Luego:
//  $ ./parte1 [nombres.txt] [paises.txt] [salida.txt]
// Se genera un archivo con el nombre [salida.txt] con las personas generadas
// de forma alertoria segun los nombres y pasises en los archivos ingresados.
// Los archivos [nombres.txt] y [paises.txt] deben tener un dato por linea.
// Aunque la funcion que lee las lineas de los archivos está preparada, se
// recomienda finalizar los archivos con un salto de linea.
// El archivo generado [salida.txt] tendra las siguientes caracteristicas:
//  - Cada linea representa una persona generada
//  - El formato de salida es: nombre, edad, lugarDeNacimiento

// generar_personas: GList GList -> GList
// Recibe una lista de nombres y una de paises,
// Genera y devuelve una lista de CANTIDAD personas con nombre y
// lugarDeNacimiento elegidos aleatoriamente y edad entre 1 y 100.
GList generar_personas(GList nombres, GList paises) {
  GList personas = glist_crear();

  for (int i = 0; i < CANTIDAD; i++) {
    Persona* persona = malloc(sizeof(Persona));

    persona->nombre = copiar_cadena(glist_dato_random(nombres));
    persona->edad = rand() % 100 + 1;
    persona->lugarDeNacimiento = copiar_cadena(glist_dato_random(paises));

    personas = glist_agregar_inicio(personas, persona);
  }

  return personas;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Error: El número de argumentos ingresados es incorrecto.\n");
    printf("Modo de uso: %s [nombres.txt] [paises.txt] [salida.txt]\n",
           argv[0]);
    return -1;
  }

  srand(time(NULL));

  GList nombres = glist_desde_archivo(argv[1], 0);
  glist_recorrer(nombres, imprimir_cadena);

  GList paises = glist_desde_archivo(argv[2], 0);
  if (nombres == NULL || paises == NULL) {
    printf("Error: Verifique que los archivos ingresados existen y que son no");
    printf(" vacíos.\n");
    return -1;
  }

  GList personas = generar_personas(nombres, paises);
  glist_a_archivo(personas, argv[3], escribir_persona);

  glist_destruir(nombres, destruir_cadena);
  glist_destruir(paises, destruir_cadena);
  glist_destruir(personas, destruir_persona);

  return 0;
}
