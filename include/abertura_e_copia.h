#ifndef ABERTURA_E_COPIA_H_INCLUDED
#define ABERTURA_E_COPIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "estruturasdef.h"

void ler(FILE *arquivo, char *IDF, int *maxTon, int *coluna, int *linha);

void pegar_pixels(pix **imagem, FILE *arquivo, int linha, int coluna);

void copia(pix **imagem, int maxTon, int coluna, int linha);

void copya(pix **imagem, pix **transposta, int maxTon, int coluna, int linha);

void copiando(pix **diminuir, int maxTon, int col, int lin, int zoom);

void copiado(pix **imagem, int zoom, int maxTon, int coluna, int linha);
#endif // ABERTURA_E_COPIA_H_INCLUDED
