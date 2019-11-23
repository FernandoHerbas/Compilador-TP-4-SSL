#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

#define FILAS 24
#define COLUMNAS 19

#define FIN '\0'
/// El AN�LISIS SINT�CTICO es realizado por un modulo llamado Parser.
/// Este analizador procesa los tokens que le entrega el Scanner hasta que reconoce
/// una construcci�n sint�ctica que requiere un procesamiento sem�ntico.
/// Entonces, invoca directamente a la rutina sem�ntica que corresponde.
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

        }
    }while(Opcion != 27);

    return 0;
}
