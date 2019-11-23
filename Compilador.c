#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

#define FILAS 24
#define COLUMNAS 19

#define FIN '\0'
/// El ANÁLISIS SINTÁCTICO es realizado por un módulo llamado Parser.
/// Este analizador procesa los tokens que le entrega el Scanner hasta que reconoce
/// una construcción sintáctica que requiere un procesamiento semántico.
/// Entonces, invoca directamente a la rutina semántica que corresponde.
//
void listaSentencias();

int main()
{
    char Opcion;
    do
    {
        printf("1 - Para leer una palabra.\n");
        printf("ESC - Para salir.\n");
        do
        {
            Opcion = getch();
        }while(Opcion != 27 && Opcion != '1');
        switch(Opcion)
        {
            case '1':
            lectura();
        }
    }while(Opcion != 27);

    return 0;
}
