#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define FINCHAR '\0'

#define FILAS 22
#define COLUMNAS 18
#define TAMMAX 100

#define ESPACIO 16
#define ESTADORECHAZO 21
typedef enum{INICIO,FIN,ID,PLBRRESERVADA,CONSTANTE,PARENIZQUIERDO,PARENDERECHO,CORCHETEIZQ,CORCHETEDER,PUNTO,ASIGNACION
            SUMA,RESTA,PRODUCTO,AND,IGUAL,FDT,ERRORLEXICO}TOKEN;
/*--------------------------------------Declaracion de funciones-----------------------*/
TOKEN scanner(FILE *);

int esEstadoFinal(int);
int columna(char);
void chequear(char *);
/*----------------------------------------Datos globales-------------------------------*/
//                                    0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13,14,15,16
const int TT[FILAS][COLUMNAS] = {   { 1 ,3 ,5 ,7 ,9 ,10,12,13,14,15,16,17,18,19,20,0 ,21},//0
                                    { 1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 },//1
                                    { 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//2
                                    { 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//2
                                    { 4 ,3 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 ,4 },//3
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//4
									{ 6 ,6 ,5 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 ,6 },//5
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//6
									{ 21,21,21,21,8 ,21,21,21,21,21,21,21,21,21,21,21,21},//7
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//8
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//9
									{ 21,21,21,21,21,11,21,21,21,21,21,21,21,21,21,21,21},//10
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//11
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//12
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//13
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//14
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//15
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//16
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//17
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//18
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//19
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21},//20
									{ 21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21}};//21

const int EstadosFinales []= {2,4,6,8,9,11,12,13,14,15,16,17,18,19,20};
const char PalabrasReservadas[][20]= {"inicio", "fin", "si", "pedir", "mostrar", "vof", "plbr", "num"};
char Buffer[TAMMAX];

TOKEN scanner(FILE *Arch){
    char Caracter;
    int  Columna;
    int  Estado = 0;
    int  i      = 0;
    do
    {
        Caracter = fgetc(Arch);
        Columna  = columna(Caracter);
        Estado   = TT[Estado][Columna];
        if(Columna != ESPACIO)
        {
            Buffer[i] = Caracter;
            i++;
        }
    }while(!esEstadoFinal(Estado) && Estado != ESTADORECHAZO);
    Buffer[i] = FINCHAR;
    switch(Estado)
    {
        case 2:
            if(Estado != ESPACIO)
            {
                ungetc(Caracter,Arch);
                Buffer[i-1] = FINCHAR;
            }
            return ID;
        case 4:
            if(Estado != ESPACIO)
            {
                ungetc(Caracter,Arch);
                Buffer[i-1] = FINCHAR;
            }
            return PLBRRESERVADA;
        case 6:
            if(Estado != ESPACIO)
            {
                ungetc(Caracter,Arch);
                Buffer[i-1] = FINCHAR;
            }
            return CONSTANTE;
        case 8 : return ASIGNACION;
        case 11: return IGUAL;
        case 9 : return RESTA;
        case 12: return SUMA;
        case 13: return PRODUCTO;
        case 14: return AND;
        case 15: return PUNTO;
        case 16: return PARENIZQUIERDO;
        case 17: return PARENDERECHO;
        case 18: return CORCHETEIZQ;
        case 19: return CORCHETEDER;
        case 20: return FDT;
        case 21: return ERRORLEXICO;
    }
    return 0;
}


int columna(char letra)
{
    if(isalpha(letra) == 1) return 0;           //Retorna la columna de mayuscula
    if(isalpha(letra) == 2) return 1;           //Retorna la columna de minuscula
    if(isdigit(letra)) return 2;                //Retorna la columna de numeros
    if(isspace(letra)) return 15;
    switch(letra)
	{
		case '<': return 3;
		case '-': return 4;
		case '=': return 5;
		case '+': return 6;
		case '*': return 7;
		case '&': return 8;
		case '.': return 9;
		case '(': return 10;
		case ')': return 11;
		case '[': return 12;
		case ']': return 13;
		case EOF: return 14;
		default:  return 16;
	}
}
int esEstadoFinal(int EstadoActual)
{
    int i;
    for(i=0;i<16;i++)
    {
        if(EstadoActual == EstadosFinales[i])
            return 1;
    }
    return 0;
}
char *esPalabraReservada(char Lexema[])
{
    int i;
    for(i=0;PalabrasReservadas[i][20] != FINCHAR;i++)
    {
        if(!strcmp(PalabrasReservadas[i],Lexema))
        {
            return "sep";
        }
    }
    return "nop";
}
void chequear(char Lexema[])
{
    printf("\nLexema: %s\n", Lexema);
    printf("Es palabra reservada? %s \n", esPalabraReservada(Lexema));

    return;
}

/*void lectura(void)
{
    char CodigoFuente[] = "MiPrograma.txt";
    FILE *Arch = fopen(CodigoFuente,"r");
    if (!Arch)
        printf("El archivo '%s' no existe.\n", CodigoFuente);
    char Caracter;
    char Lexema[20];
    int EstadoActual  =0;
    int ColumnaActual =0;
    int EstadoRechazo =21;
    Lexemas *misLexemas = NULL;
    Lexema[0] = FIN;
    while(!feof(Arch))
    {
        Caracter = fgetc(Arch);
        while(!esEstadoFinal(EstadoActual) && EstadoActual != EstadoRechazo)
        {
            insertarCaracterA(Lexema,Caracter);
            ColumnaActual = columna(Caracter);
            EstadoActual = TT[EstadoActual][ColumnaActual];
            printf("caracteres: %c\n",Caracter);
            Caracter = fgetc(Arch);
        }
        ungetc(Caracter,Arch);
        eliminarUltimo(Lexema);
       // chequear(Lexema);
        //insertarLexemaA(misLexemas,Lexema);
    }
    fclose(Arch);
    return;
}*/
