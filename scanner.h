#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //si compilas en windows
//#include <ncurses.h> //si compilas en linux#include <ctype.h>
#include <string.h>

#define FILAS 24
#define COLUMNAS 19

#define FIN '\0'

int columna(char);
int leerTabla(const int [][19],char [],int ,int );
int estadoEsDeAceptacion(int );

int leerTabla(const int TT[][COLUMNAS],char Dato[],int EstadoInicial,int EstadoRechazo)
{
    int i=0;
    int EstadoActual = EstadoInicial;
    int ColumnaActual=0;
    printf("Estado actual: %d \n" ,EstadoActual);
    printf("Columna actual: %d \n" ,ColumnaActual);

    while(Dato[i] != FIN && EstadoActual != EstadoRechazo)
    {
        ColumnaActual = columna(Dato[i]);
        EstadoActual = TT[EstadoActual][ColumnaActual];
        printf("Estado actual: %d \n" ,EstadoActual);
        printf("Columna actual: %d \n" ,ColumnaActual);

        i++;
    }
    return estadoEsDeAceptacion(EstadoActual);
}
int columna(char letra)
{
    if(isalpha(letra) == 1)
    {
        return 0;               //Retorna la columna de mayuscula
    }
    if(isalpha(letra) == 2)
    {
        return 1;               //Retorna la columna de minuscula
    }
    if(isdigit(letra))
        return 2;                //Retorna la columna de numeros

    switch(letra)
	{
		case '<':
			return 3;
			break;
		case '-':
			return 4;
			break;
		case '=':
			return 5;
			break;
		case '+':
			return 6;
			break;
		case '*':
			return 7;
			break;
		case '/':
			return 8;
			break;
		case '|':
			return 9;
			break;
		case '&':
			return 10;
			break;
		case '>':
			return 11;
			break;
		case '.':
			return 12;
			break;
		case '(':
			return 13;
			break;
		case ')':
			return 14;
			break;
		case '[':
			return 15;
			break;
		case ']':
			return 16;
			break;
		case ' ':
			return 17;
			break;
		default:
            return 18;
         //   break;
	}
}
int estadoEsDeAceptacion(int EstadoActual)
{
    int i;
    int EstadosDeAceptacion []= {2,4,6,8,9,10,12,13,14,15,16,17,18,19,20,21,22};
    for(i=0;i<16;i++)
    {
        if(EstadoActual == EstadosDeAceptacion[i])
        {
            return 1;
        }
    }
    return 0;
}
