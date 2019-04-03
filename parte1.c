#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "glist.h"
#include "util.h"

// MODO DE USO:
// ./parte1 [nombres.txt] [paises.txt] [salida.txt]
// Se genera un archivo con el nombre [salida.txt] con las personas generadas
// de forma alertoria segun los nombres y pasises ingresados por los archivos

// Los archivos a recibir (nombres.txt o paises.txt) deben cumplir lo siguiente:
//  - Cada linea tiene que ser un pais

// El archivo generado (salida.txt) tendra las siguientes caracteristicas:
//  - Cada linea representa una persona generada
//  - Los campos estan separadas por ","

GList generar_personas(int numDatos, GList nombres, GList paises) {
  GList personas = glist_crear();

  for (int i = 0; i < numDatos; i++) {
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

  GList personas = generar_personas(50, nombres, paises);

  glist_a_archivo(personas, argv[3], escribir_persona);

  return 0;
}
