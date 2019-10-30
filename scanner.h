#include <stdio.h>
#include <stdlib.h>
#include <conio.h>>
#include <string.h>

#define FILAS 24
#define COLUMNAS 19

#define FIN '\0'

int columna(char);
int leerTabla(const int [][COLUMNAS],char [],int ,int ,const int[]);
int estadoEsDeAceptacion(int ,const int [],int);

int leerTabla(const int TT[][COLUMNAS],char Dato[],int EstadoInicial,int EstadoRechazo,const int estadosDeAceptacion[])
{
    int i=0;
    int EstadoActual = EstadoInicial;
    int ColumnaActual=0;
    int Longitud = sizeof(estadosDeAceptacion) / sizeof(estadosDeAceptacion[0]);
    while(Dato[i] != FIN && EstadoActual != EstadoRechazo)
    {
        ColumnaActual = columna(Dato[i]);
        EstadoActual = TT[EstadoActual][ColumnaActual];
        i++;
    }
    return estadoEsDeAceptacion(EstadoActual, estadosDeAceptacion, Longitud);
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
int estadoEsDeAceptacion(int EstadoActual, const int EstadosDeAceptacion[], int Longitud)
{
    int i;
    for(i=0;i<Longitud;i++)
    {
        if(EstadoActual == EstadosDeAceptacion[i])
        {
            return 1;
        }
    }
    return 0;
}
