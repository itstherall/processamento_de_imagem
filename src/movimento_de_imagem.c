#include "movimento_de_imagens.h"

void espelhandovert (pix **imagem, pix **imagemloc, int col, int lin){ /*funcao que espelha a imagem verticalmente*/
    //faz a inversão do preenchimento para imagem fica espelhada
    for(int i = 0 ; i < lin ; ++i)
    {
        for(int j = 0 ; j < col ; ++j)
        {
            imagemloc[i][j].r = imagem[lin - i - 1][col -1 -j].r;
            imagemloc[i][j].g = imagem[lin - i - 1][col -1 -j].g;
            imagemloc[i][j].b = imagem[lin - i - 1][col -1 -j].b;
        }
    }

    //passa a imagem ja refletida para matriz imagem para poder ser salva
    for(int i = 0 ; i < lin ; ++i)
    {
        for(int j = 0 ; j < col ; ++j)
        {
            imagem[i][j].r = imagemloc[i][j].r;
            imagem[i][j].g = imagemloc[i][j].g;
            imagem[i][j].b = imagemloc[i][j].b;
        }
    }
    return;
}


void espelhandohor (pix **imagem, pix **imagemloc, int col, int lin){ /*funcao que espelha a imagem horizontalmente*/

    //faz a inversão do preenchimento para imagem fica espelhada
    for(int i = 0 ; i < lin ; ++i)
    {
        for(int j = 0 ; j < col ; ++j)
        {
            imagemloc[i][j].r = imagem[i][col - j - 1].r;
            imagemloc[i][j].g = imagem[i][col - j - 1].g;
            imagemloc[i][j].b = imagem[i][col - j - 1].b;
        }
    }

    //passa a imagem ja refletida para matriz imagem para poder ser salva
    for(int i = 0 ; i < lin ; ++i)
    {
        for(int j = 0 ; j < col ; ++j)
        {
            imagem[i][j].r = imagemloc[i][j].r;
            imagem[i][j].g = imagemloc[i][j].g;
            imagem[i][j].b = imagemloc[i][j].b;
        }
    }
    return;
}


void zoomintotal (pix **imagem, pix **imagem_zoom, int zoom, int coluna, int linha){
    int i, j, k, l;
    int linzoom = linha*zoom, colzoom=coluna*zoom;

    //faz um alocação para que a imagemzoom seja preenchida com os pixels da imagem
    ///a imagemzoom recebe o 4pixels do mesmo da imagem normal para que possa fazer o zoom
    for(i = 0, k = 0; i < colzoom && k < linzoom ; ++k){
        if(k % zoom == 0 && k!=0){
            ++i;
        }
        for(j = 0, l = 0; j < colzoom && l < colzoom;  l++){
			if(l % zoom == 0 && l != 0){
				j++;
			}
			imagem_zoom[k][l] = imagem[i][j]; //aloca os pixels de imagem para imagem_zoom da (imagem completa)
		}
    }

    return;

}


void zoomin(pix **imagem, pix **tamimagem, int zoom, int coluna, int linha){ /*aplica o zoom in local */

    int i, j, k, l, x , y;
    int loop = 0;

    //faz o pedido de onde você deseja iniciar o zoom local
    while(loop == 0)
    {
        printf("diga aonde você deseja iniciar o seu zoom x de 0 a %d e y de o a %d:\n", linha/2, coluna/2);
        scanf("%d %d", &x, &y);
        if (x < 0 || y < 0 || y > coluna/2 || x > linha/2)
        {
            printf("Digite valores validos!!!\n");
            loop = 0;
        }
        else
        {
            loop = 1;
        }
    }

    //faz um alocação para que a imagemzoom seja preenchida com os pixels da imagem
    ///a imagemzoom recebe o 4pixels do mesmo da imagem normal para que possa fazer o zoom
    for(i = x, k = 0; i < linha && k < linha ; ++k){
        if(k % zoom == 0 && k!=0){
            ++i;
        }
        for(j = y, l = 0; j < coluna && l < coluna;  l++){
            if(l % zoom == 0 && l != 0){
                j++;
            }
            tamimagem[k][l] = imagem[i][j];
        }
    }

    //passa o para matriz imagem a imagem ja com o zoom no local aplicado
    for(int i = 0 ; i < linha ; ++i){
        for(int j = 0; j < coluna ; ++j){
            imagem[i][j]=tamimagem[i][j];
        }
    }

    return;
}


void zoomout(pix **imagem, pix **imagem_zoom, int zoom, int coluna, int linha){/*funcao do zoomout*/
    int i, j, k, l;

    //faz um alocação para que a imagemzoom seja preenchida com os pixels da imagem
    for(i = 0, k = 0; i < linha && k < linha ; ++k){
        if(k % zoom == 0 && k!=0){
            ++i;
        }
        for(j = 0, l = 0; j < coluna && l < coluna;  l++){
			if(l % zoom == 0 && l != 0){
				j++;
			}
			imagem_zoom[i][j] = imagem[k][l];
		}
    }

    //passa a imagem ja reduzida para matriz imagem
    for(i = 0 ; i < linha ; ++i){
        for(j = 0; j < coluna ; ++j){
            imagem[i][j]=imagem_zoom[i][j];
        }
    }
    return;
}


void rotacao_dir(pix **imagem, pix **transposta, int coluna , int linha){ /*Função que rotaciona a imagem 90º a direita*/

    //faz o preenchimento da imagem normal para imagem virada que é feita na matriz transposta aonde a imagem ficara virada para esquerda.
    for(int i = 0 ; i < coluna; ++i){
        for(int j = 0 ; j < linha; ++j){

            transposta[i][j].r = imagem[linha - j - 1][i].r;
            transposta[i][j].g = imagem[linha - j - 1][i].g;
            transposta[i][j].b = imagem[linha - j - 1][i].b;
        }
    }
    return;
}


void rotacao_esq(pix **imagem, pix **transposta, int coluna , int linha){ /*Função que rotaciona a imagem 9º a esquerda*/

    //faz o preenchimento da imagem normal para imagem virada que é feita na matriz transposta aonde a imagem ficara virada para esquerda..
    for(int i = 0 ; i < coluna; ++i){
        for(int j = 0 ; j< linha; ++j){
            transposta[i][j].r = imagem[j][coluna - i- 1].r;
            transposta[i][j].g = imagem[j][coluna - i - 1].g;
            transposta[i][j].b = imagem[j][coluna - i - 1].b;
        }
    }
    return;
}


void centoeoitenta(pix **imagem, pix **imagemloc, int col , int lin){ /*Função que gira a imagem em 180º*/

    //faz a passagem dos pixels da imagem para gerar uma imagem rotacionada 180 graus
    for(int i = 0 ; i < lin ; ++i){
        for(int j = 0 ; j < col ; ++j){

            imagemloc[i][j].r = imagem[lin - 1 - i][col - 1 - j].r;
            imagemloc[i][j].g = imagem[lin - 1 - i][col - 1 - j].g;
            imagemloc[i][j].b = imagem[lin - 1 - i][col - 1 - j].b;
        }
    }

    //transfere a imagem ja virada para matriz de imagem para que ela possa ser salva
    for(int i = 0 ; i < lin ; ++i){
        for(int j = 0 ; j < col ; ++j){

            imagem[i][j].r = imagemloc[i][j].r;
            imagem[i][j].g = imagemloc[i][j].g;
            imagem[i][j].b = imagemloc[i][j].b;
        }
    }
    return;
}
