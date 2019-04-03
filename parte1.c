#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glist.h"
#include "util.h"

// MODO DE USO:
// Si no lo hizo todavia, para copilar debe ejecutar los siguientes comandos:
//  $ gcc -c util.c -Wall -pedantic
//  $ gcc -c glist.c -Wall -pedantic
//  $ gcc -o parte1 parte1.c glist.o util.o -Wall -pedantic
// Luego:
//  $ ./parte1 [nombres.txt] [paises.txt] [salida.txt]
// Se genera un archivo con el nombre [salida.txt] con las personas generadas
// de forma alertoria segun los nombres y pasises ingresados por los archivos

// Los archivos a recibir ([nombres.txt] o [paises.txt]) deben cumplir lo
// siguiente:
//  - Cada linea representa un dato

// El archivo generado [salida.txt] tendra las siguientes caracteristicas:
//  - Cada linea representa una persona generada
//  - El formato de salida es: nombre, edad, pais

// generar_personas: GList GList -> GList
// Recibe una lista de nombres y una de paises,
// Genera una lista de 2000 personas con:
//  - nombre y pais alertorios
//  - 0 < edad <= 100
// Devuelve una lista con las personas generadas.
GList generar_personas(GList nombres, GList paises) {
  GList personas = glist_crear();

  for (int i = 0; i < 2000; i++) {
    Persona* persona = malloc(sizeof(Persona));
    persona->nombre = glist_dato_random(nombres);
    persona->edad = rand() % 100 + 1;
    persona->lugarDeNacimiento = glist_dato_random(paises);

    personas = glist_agregar_final(personas, persona);
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

  GList nombres = glist_desde_archivo(argv[1]);
  GList paises = glist_desde_archivo(argv[2]);
  if (nombres == NULL || paises == NULL) {
    printf("Error: Verifique que los archivos ingresados existen y que son no");
    printf("vacíos.\n");
    return -1;
  }

  GList personas = generar_personas(nombres, paises);

  glist_a_archivo(personas, argv[3], escribir_persona);

  return 0;
}
