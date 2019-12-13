#ifndef MOVIMENTO_DE_IMAGENS_H_INCLUDED
#define MOVIMENTO_DE_IMAGENS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "estruturasdef.h"

void espelhandovert (pix **imagem, pix **imagemloc, int col, int lin);

void espelhandohor (pix **imagem, pix **imagemloc, int col, int lin);

void zoomintotal (pix **imagem, pix **imagem_zoom, int zoom, int coluna, int linha);

void zoomin(pix **imagem, pix **tamimagem, int zoom, int coluna, int linha);

void zoomout(pix **imagem, pix **imagem_zoom, int zoom, int coluna, int linha);

void rotacao_dir(pix **imagem, pix **transposta, int coluna , int linha);

void rotacao_esq(pix **imagem, pix **transposta, int coluna , int linha);

void centoeoitenta(pix **imagem, pix **imagemloc, int col , int lin);


#endif // MOVIMENTO_DE_IMAGENS_H_INCLUDED
