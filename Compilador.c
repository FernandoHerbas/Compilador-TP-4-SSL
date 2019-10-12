#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define FILAS 20
#define COLUMNAS 20

#define FILAS_ID_C 4            //Filas de la TT de identificador y constantes
#define COLUMNAS_ID_C 3         //Columnas de la TT de identificador y constantes
#define FILAS_PR_OP_CP 3        //Filas de la TT de palabras reservadas, operadores y caracteres de puntuacion
#define COLUMNAS_PR_OP_CP 11    //Columnas de la TT de palabras reservadas, operadores y caracteres de puntuacion

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

int leerTabla(int [][COLUMNAS_ID_C], char [], int, int , int[]); //Retornan 1 si reconoce la palabra,0 sino, con funcion columna
int leerTablaParaToken(int [][COLUMNAS_PR_OP_CP], int, int, int);//Idem leerTabla, para los tokens, con funcion buscarColumnaEn
int columna(char, int []);                                       //Retorna columna de la TT usando isalpha
int buscarColumnaEn(char [][CARACTERES], char [], int, int);     //Retorna columna de la TT usando los tokens

const int Tabla[FILAS][COLUMNAS] = {{ 1,2,3,4,7,13,8,9,10,11,12,13,15,16,17,18,19,20,0,2 },//0
								    { 1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//1
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//2
									{ 2,2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//3			
									{ 2,2,2,2,5,6,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//4
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//5
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//6
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//7
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//8
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//9
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//10
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//11
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//12
									{ 2,2,2,2,2,14,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//13
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//14
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//15
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//16
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//17
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//18
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },//19
									{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 } };//20

int main()
{   
    int ColumnaActual;
    char Opcion;
    int x;
    do
    {
        printf("1 - Para leer un identificador.\n");
        printf("2 - Para leer una constante.\n");
        printf("3 - Para leer una palabra reservada.\n");
        printf("4 - Para leer un operador.\n");
        printf("5 - Para leer un caracter de puntuacion.\n");
        printf("ESC - Para salir.\n");
        do
        {
            Opcion = getch();
        }while(Opcion != 27 && Opcion != '1' && Opcion != '2' && Opcion != '3' && Opcion != '4' && Opcion != '5');
        switch(Opcion)
        {
            case '1':
                printf("\nIngrese un identificador: ");
                scanf("%s",Dato);
                Columnas[0]=0;          //Columna de mayuscula
                Columnas[1]=1;          //Columna de minusculas, de acuerdo a la tabla
                Columnas[2]=2;          //Columna de numeros,columna de rechazo
                x=leerTabla(TTIdentificador,Dato,0,2,Columnas);
                if(x)
                    printf("Identificador %s reconocido.\n", Dato);
                else
                    printf("Identificador %s rechazado.\n", Dato);
                printf("\n");
            break;
            case '2':
                printf("\nIngrese una constante: ");
                scanf("%s",Dato);
                Columnas[0]=2;              //Es de acuerdo a la tabla, rechaza si es mayuscula
                Columnas[1]=1;              //Columna de minusculas, de acuerdo a la tabla
                Columnas[2]=0;              //Columna de numeros
                x=leerTabla(TTConstante,Dato,0,3,Columnas);
                if(x)
                    printf("Constante %s reconocida.\n",Dato);
                else
                    printf("Constante %s rechazada.\n",Dato);
                printf("\n");
            break;
             case '3':
                printf("\nIngrese una palabra: ");
                scanf("%s",Dato);
                ColumnaActual = buscarColumnaEn(Tokens[0],Dato,1,10);
                x=leerTablaParaToken(TTPalabraReservada,0,2,ColumnaActual);
                if(x)
                {
                    printf("Palabra %s reconocida.\n",Dato);
                }
                else
                    printf("Palabra %s rechazada.\n",Dato);
                printf("\n");
            break;
            case '4':
                printf("\nIngrese un operador: ");
                scanf("%s",Dato);
                ColumnaActual = buscarColumnaEn(Tokens[1],Dato,1,10);
                x=leerTablaParaToken(TTOperadores,0,2,ColumnaActual);
                if(x)
                {
                    printf("Operador %s reconocido.\n",Dato);
                }
                else
                    printf("Operador %s rechazado.\n",Dato);
                printf("\n");
            break;
            case '5':
                printf("\nIngrese un caracter de puntuacion: ");
                scanf("%s",Dato);
                ColumnaActual = buscarColumnaEn(Tokens[2],Dato,1,5);
                x=leerTablaParaToken(TTCaractPuntuacion,0,2,ColumnaActual);
                if(x)
                {
                    printf("Caracter %s reconocido.\n",Dato);
                }
                else
                    printf("Caracter %s rechazado.\n",Dato);
                printf("\n");
            break;

        }
    }while(Opcion != 27);


    return 0;
}
int leerTabla(int TT[][COLUMNAS_ID_C],char Dato[],int EstadoInicial,int EstadoRechazo,int Columnas[])
{
    int i=0;
    int EstadoActual = EstadoInicial;
    int ColumnaActual;
    while(Dato[i] != FIN && EstadoActual != EstadoRechazo)
    {
        if(columna(Dato[i],Columnas) == 3)  //Si no es numero, ni letra mayuscula o miniscula
            return 0;
        ColumnaActual = columna(Dato[i],Columnas);
        EstadoActual = TT[EstadoActual][ColumnaActual];
        i++;
    }
    if(EstadoActual != EstadoRechazo)
    {
        return 1;
    }
    else
        return 0;
}

int columna(char letra,int Columnas[])
{
    if(isalpha(letra) == 1)
    {
        return Columnas[0];               //Retorna la columna de mayuscula
    }
    else if(isalpha(letra) == 2)
    {
        return Columnas[1];               //Retorna la columna de minuscula
    }
    else if(isdigit(letra))
        return Columnas[2];                //Retorna la columna de numeros
    return 3;
}

int leerTablaParaToken(int TT[][COLUMNAS_PR_OP_CP],int EstadoInicial,int EstadoRechazo, int Columna)
{
    int EstadoActual=EstadoInicial;
    EstadoActual = TT[EstadoActual][Columna];
    if(EstadoActual != EstadoRechazo)
    {
        return 1;
    }
    else
        return 0;
}

int buscarColumnaEn(char Alfabeto[][CARACTERES],char Dato[],int ColumnaAceptacion,int ColumnaRechazo)
{
    int i;
    for(i=0; Alfabeto[i][CARACTERES]!= FIN;i++)
    {
        if(!strcmp(Alfabeto[i],Dato))
        {
            return ColumnaAceptacion;
        }
    }
    return ColumnaRechazo;
}
