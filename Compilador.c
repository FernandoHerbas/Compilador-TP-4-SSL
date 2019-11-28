#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define FINCHAR '\0'

#define FILAS 24
#define COLUMNAS 17
#define TAMMAX 100

#define ESPACIO 15
#define ESTADORECHAZO 21

typedef enum{INICIO,FIN,SI,CONSTANTE,ID,PLBRRESERVADA,PARENIZQUIERDO,PARENDERECHO,CORCHETEIZQ,CORCHETEDER,
            PUNTO,ASIGNACION,SUMA,RESTA,PRODUCTO,AND,IGUAL,FDT,ERRORLEXICO}TOKEN;

/*--------------------------------------Declaracion de funciones-----------------------*/

void objetivo(void);
void programa(void);
void listaSentencias();
void sentencia();
void expresion();
void primaria();

void match(TOKEN );
void matchear(TOKEN);
TOKEN proximoToken();
void errorLexico();
void errorSintactico();
void chequear(char *);
void mostrarMensajeCompilacionExitosa();

TOKEN scanner();
int esEstadoFinal(int);
int columna(char);
/*-----------------------Variables y constantes globales--------------------------*/
//                                 0 ,1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13,14,15,16
const int TT[FILAS][COLUMNAS] = {{ 1 ,3 ,5 ,7 ,9 ,10,12,13,14,15,16,17,18,19,20,0 ,21},//0
                                 { 1 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 },//1
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

char Buffer[TAMMAX];
int flagToken = 0;
TOKEN tokenActual;
FILE *Arch;
/*-----------------------Programa Principal--------------------------*/
int main()
{
    char CodigoFuente[] = "MiPrograma.txt";
    Arch = fopen(CodigoFuente,"r");
    if (!Arch)
        printf("El archivo '%s' no existe.\n", CodigoFuente);
    objetivo();   // Comienza la lectura del archivo.
    mostrarMensajeCompilacionExitosa();
    fclose(Arch);
    return 0;
}
void objetivo()
{
    programa();
    match(FDT);
}

void programa()
{
    match(INICIO);
    match(PUNTO);
    listaSentencias();
    match(FIN);
    match(PUNTO);
}

void listaSentencias()
{
    sentencia();
    while(1)
    {
        switch(proximoToken())
        {
            case ID: case SI:
            sentencia();
            break;
            default: return;
        }
    }
    return;
}

void sentencia()
{
    TOKEN tok = proximoToken();
    switch(tok)
    {
        case SI:
            match(SI);
            match(PARENIZQUIERDO);
            expresion();
            match(PARENDERECHO);
            match(CORCHETEIZQ);
            listaSentencias();
            match(CORCHETEDER);
            break;
        case ID:
            match(ID);
            match(ASIGNACION);
            expresion();
            match(PUNTO);
            break;
        default: break;
    }
}

void expresion()
{
    TOKEN tok;
    primaria();
    for(tok = proximoToken(); tok == SUMA || tok == RESTA || tok == AND || tok == IGUAL; tok = proximoToken()){
        operadorAditivo();
        primaria();
    }
    return;

}

void primaria()
{
    TOKEN tok = proximoToken();
    switch(tok)
    {
        case CONSTANTE:
            match(CONSTANTE);
            break;
        case ID:
            match(ID);
            break;
        default : errorSintactico();break;
    }
}
void operadorAditivo(){
    TOKEN tok = proximoToken();
    if(tok == SUMA || tok == RESTA || tok == AND || tok == IGUAL){
        match(tok);
    }
    else
        errorSintactico();
    return;
}


void match(TOKEN tok)
{
    if(!(tok == proximoToken()))
    {
        errorSintactico();
    }
    flagToken = 0;
    return;
}


TOKEN proximoToken()
{
    if(!flagToken)
    {
        tokenActual = scanner();
        if(tokenActual == ERRORLEXICO)
            errorLexico();
        flagToken = 1;
        if(tokenActual == PLBRRESERVADA)
        {
            if(!strcmp(Buffer,"inicio")){
                tokenActual = INICIO;
            }

            if(!strcmp(Buffer,"fin")){
                tokenActual = FIN;
            }
            if(!strcmp(Buffer,"si")){
                tokenActual = SI;
            }
        }
    }
    return tokenActual;
}

void errorLexico() {  printf("Error Lexico\n"); }
void errorSintactico() {  printf("Error Sintactico\n"); }

TOKEN scanner(){
    char Caracter;
    int  Columna;
    int  Estado = 0;
    int  i      = 0;
    Buffer[0] = FINCHAR;
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
    for(i=0;i<15;i++)
    {
        if(EstadoActual == EstadosFinales[i])
            return 1;
    }
    return 0;
}
void mostrarMensajeCompilacionExitosa(){
    printf("Compilacion exitosa.");
}

