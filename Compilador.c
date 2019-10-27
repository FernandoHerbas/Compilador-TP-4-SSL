#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //si compilas en windows
//#include <ncurses.h> //si compilas en linux
#include <ctype.h>
#include <string.h>
#include "scanner.h"

#define FILAS 24
#define COLUMNAS 19

#define FIN '\0'
///caracter a analizar: primer caracter de la cadena
///estado actual el automata: estado inicial
///mientras haya caracteres en la cadena y el estado
///actual no sea el del rechazo, repetir:
///         -determinar el nuevo estado actual(estado de llegada de la
///             transicion)
///         -actualizar el caracter a analizar
/// si el ultimo estado actual es un estado final, entonces la
/// cadena procesada es una palabra del lenguaje; en caso contrario,
/// la cadena no pertenece al lenguaje

const int TT[FILAS][COLUMNAS] = {{ 1,3,5,7,10,11,13,14,15,16,17,11,18,19,20,21,22,0,24 },//0
                                 { 1,1,24,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//1
                                 { 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//2
                                 { 24,3,24,24,24,24,24,24,24,24,24,24,24,4,24,24,24,4,24 },//3
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//4
									{ 6,6,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },//5
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//6
									{ 24,24,24,24,8,9,24,24,24,24,24,24,24,24,24,24,24,24,24 },//7
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//8
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//9
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//10
									{ 24,24,24,24,24,12,24,24,24,24,24,24,24,24,24,24,24,24,24 },//11
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//12
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//13
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//14
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//15
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//16
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//17
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//18
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//19
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//20
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//21
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//22
								//	{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 },//23s
									{ 24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24 } };//24

int main()
{
    char Opcion;
    char Dato[20];
    int x;
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
                printf("\nIngrese una palabra: ");
                scanf("%s",Dato);
                x=leerTabla(TT,Dato,0,24);
                if(x)
                    printf("palabra %s reconocido.\n", Dato);
                else
                    printf("palabra %s rechazado.\n", Dato);
                printf("\n");
            break;
        }
    }while(Opcion != 27);

    return 0;
}


