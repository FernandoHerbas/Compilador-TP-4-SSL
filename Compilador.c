#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"

/// El AN�LISIS SINT�CTICO es realizado por un modulo llamado Parser.
/// Este analizador procesa los tokens que le entrega el Scanner hasta que reconoce
/// una construcci�n sint�ctica que requiere un procesamiento sem�ntico.
/// Entonces, invoca directamente a la rutina sem�ntica que corresponde.
/*--------------------------------------Declaracion de funciones-----------------------*/
void listaSentencias();
void objetivo();
void programa();

/************************Programa Principal************************/ 
FILE *Arch;
int main()
{  
    char CodigoFuente[] = "MiPrograma.txt";
    Arch = fopen(CodigoFuente,"r");
    if (!Arch)
        printf("El archivo '%s' no existe.\n", CodigoFuente);  
/**********************Inicio Compilacion***************************/ 
    Objetivo(); 
/***********************Se cierra el Archivo Fuente******************/ 
    fclose(in); 
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
    listaSentencias();
    match(FIN);
}

void listaSentencias()
{
    sentencia();
    while(1)
    {
        switch(proximoToken())
        {
            case DECLAVAR: case ID: case SI:
            sentencia();
            break;
            default: return;
        }
    }
}

void sentencia()
{
    TOKEN tok = proximoToken();
    switch(tok)
    {
        case DECLAVAR:
            match(DECLAVAR);
            tipo();
            match(ASIGNACION);
            match(CONSTANTE);
            match(PUNTO);
            break;
        case ID:
            match(ID);
            match(ASIGNACION);
            expresion();
            match(PUNTO);
        case SI:
            match(SI);
            match(PARENIZQUIERDO);
            expresion();
            match(PARENDERECHO);
            match(CORCHETEIZQ);
            listaSentencias();
            match(CORCHETEDER);
            break;
        default: break;
    }
}

void expresion()
{
    TOKEN tok;
    for(tok = proximoToken(); tok == SUMA || tok == RESTA; tok = proximoToken();)
    {
        expAnd();
    }
}

void match(TOKEN tok)
{
    if(tok != proximoToken())
    {
        errorSintactico();
    }
    flagToken = 0;
}

TOKEN proximoToken()
{
    if(!flagToken)
    {
        tokenActual = scanner(Arch);
        if(tokenActual == ERRORLEXICO)
            errorLexico();
        flagToken = 1;
        if(tokenActual == ID)
        {
            buscar(buffer, TS, &tokenActual);
        }
    }
    return tokenActual;
}

void errorLexico() {  printf("Error Lexico\n"); }  
void errorSintactico() {  printf("Error Sintactico\n"); }

int buscar(char *id,char )