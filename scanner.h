#include <stdio.h>
#include <stdlib.h>
#include <conio.h>>
#include <string.h>

#define FILAS 24
#define COLUMNAS 19

#define FIN '\0'
const int TT[FILAS][COLUMNAS] = {   { 1,3,5,7,10,11,13,14,15,16,17,11,18,19,20,21,22,0,24 },//0
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

const int EstadosCentinelas []= {2,4,6,8,9,10,12,13,14,15,16,17,18,19,20,21,22};




typedef enum Tokens = {PalabraReservada, CaracteresDePuntacion, Operadores};

int columna(char);
int leerTabla(int ,int );
int centinelas(int ,int);

int leerTabla(int EstadoInicial,int EstadoRechazo)
{

    return 0;
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
int centinelas(int EstadoActual, int Longitud)
{
    int i;
    for(i=0;i<Longitud;i++)
    {
        if(EstadoActual == EstadosCentinelas[i])
        {
            return 1;
        }
    }
    return 0;
}
void lectura()
{

}
