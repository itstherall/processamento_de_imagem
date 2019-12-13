#ifndef FILTROS_H_INCLUDED
#define FILTROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "estruturasdef.h"

void grey(pix **imagem, int coluna, int linha);

int bin(pix **imagem, int colunas, int linhas);

void sharpen(pix **imagem, pix **modificada, int coluna, int linha);

void blur(pix **imagem, int coluna, int linha);

void detBord(pix **imagem, pix **transposta, int coluna, int linha);

void sepia(pix **imagem, int coluna, int linha);

void negativo (pix **imagem, int coluna, int linha);

#endif // FILTROS_H_INCLUDED
