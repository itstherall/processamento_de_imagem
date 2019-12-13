#include "abertura_e_copia.h"
#include <stdio.h>

void ler(FILE *arquivo, char *IDF, int *maxTon, int *coluna, int *linha){/*Função que realiza a leitura da imagem*/

        fscanf(arquivo, "%s", IDF); //le o codigo
        fscanf(arquivo, "%d", coluna);//le a coluna (largura)
        fscanf(arquivo, "%d", linha);//le a linha (altura)
        fscanf(arquivo, "%d", maxTon);//le a maxima tonalidade do pixel

}


void pegar_pixels(pix **imagem, FILE *arquivo, int linha, int coluna){/*Função que pega cada um dos pixels da imagem
                                                                            lida e armazena numa matriz tipo Pix. */
    for(int i = 0; i < linha; ++i){
        for(int j = 0 ; j < coluna; ++j){

           fscanf(arquivo, "%d", &imagem[i][j].r);
           fscanf(arquivo, "%d", &imagem[i][j].g);
           fscanf(arquivo, "%d", &imagem[i][j].b);

        }
    }
    return;
}


void copia(pix **imagem, int maxTon, int coluna, int linha) {/*Função que cria uma cópia da imagem original*/

    int i, j;
    FILE *copy;

    char nome_arq[50];
    printf("\nComo deseja nomear sua imagem?\n"); /*Solicita ao usuário o nome para salvar a imagem*/
    scanf("%s", nome_arq);

    copy = fopen(nome_arq, "w");    /*Abre o arquivo para escrita*/

    fprintf(copy, "P3\n"); //Passa para o arquivo o código
    fprintf(copy, "%d\n ", coluna); //Passa a largura
    fprintf(copy, "%d\n", linha); //Passa a altura
    fprintf(copy, "%d\n", maxTon); //Passa a máxima tonalidade

    for (i = 0; i < linha; i++) {      /*Estruturas para percorrer a matriz dos pixels e copiar os dados da imagem original*/
        for (j = 0; j < coluna; j++) {

            fprintf(copy, "%d ", imagem[i][j].r);
            fprintf(copy, "%d ", imagem[i][j].g);
            fprintf(copy, "%d\n", imagem[i][j].b);

        }
    }

    fclose(copy);
    printf("\nImagem salva com sucesso!\n");
    return;
}


void copya(pix **imagem, pix **transposta, int maxTon, int coluna, int linha) {/*Função que criar uma copia de matriz transposta */

    int i, j, aux;
    FILE *copy;

    //faz a troca de lin e col caso diferentes
    if(linha != coluna){
        aux = linha;
        linha = coluna;
        coluna = aux;
    }


    char nome_arq[50];
    printf("Como deseja nomear sua imagem?\n");
    scanf("%s", nome_arq);

    copy = fopen(nome_arq, "w");

    fprintf(copy, "P3\n");
    fprintf(copy, "%d\n ", coluna);
    fprintf(copy, "%d\n", linha);
    fprintf(copy, "%d\n", maxTon);

    if(linha != coluna){
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {

            fprintf(copy, "%d ", transposta[i][j].r);
            fprintf(copy, "%d ", transposta[i][j].g);
            fprintf(copy, "%d\n", transposta[i][j].b);

            }
        }
    }
    else{
        for (i = 0; i < linha; i++) {
            for (j = 0; j < coluna; j++) {
                imagem[i][j].r = transposta[i][j].r;
                imagem[i][j].g = transposta[i][j].g;
                imagem[i][j].b = transposta[i][j].b;
            }
        }
         for (i = 0; i < linha; i++) {
            for (j = 0; j < coluna; j++) {
                fprintf(copy, "%d ", imagem[i][j].r);
                fprintf(copy, "%d ", imagem[i][j].g);
                fprintf(copy, "%d\n", imagem[i][j].b);
            }
        }
    }

    fclose(copy);
    printf("\nImagem salva com sucesso!\n");
}


void copiando(pix **diminuir, int maxTon, int col, int lin, int zoom){/*Função que cria copia dimansionada (menor ou maior) para funções zoom*/

    FILE *copian;

    char nome_arq[50];
    printf("\nComo deseja nomear sua imagem?\n"); /*Solicita ao usuário o nome para salvar a imagem*/
    scanf("%s", nome_arq);

    copian = fopen(nome_arq, "w");    /*Abre o arquivo para escrita*/

    fprintf(copian, "P3\n"); //Passa para o arquivo o código
    fprintf(copian, "%d\n ", col/zoom); //Passa a largura
    fprintf(copian, "%d\n", lin/zoom); //Passa a altura
    fprintf(copian, "%d\n", maxTon); //Passa a máxima tonalidade

    /*Estruturas para percorrer a matriz dos pixels e copiar os dados da imagem original alterada*/
    for (int i = 0; i < lin/zoom; i++)
    {
        for (int j = 0; j < col/zoom; j++)
        {
            fprintf(copian, "%d ", diminuir[i][j].r);
            fprintf(copian, "%d ", diminuir[i][j].g);
            fprintf(copian, "%d\n", diminuir[i][j].b);
        }
    }

    fclose(copian);
    printf("\nImagem salva com sucesso!\n");
    return;
}


void copiado(pix **imagem, int zoom, int maxTon, int coluna, int linha) {/* funcao que faz copia do zoom na imagem inteira*/

    int i, j;
    FILE *cop;

    char nome_arq[50];
    printf("Entre com o nome que deseja salvar:\n");
    scanf("%s", nome_arq);

    cop = fopen(nome_arq, "w");

    fprintf(cop, "P3\n");
    fprintf(cop, "%d\n ", coluna*zoom);
    fprintf(cop, "%d\n", linha*zoom);
    fprintf(cop, "%d\n", maxTon);

    for (i = 0; i < linha*zoom; i++) {
        for (j = 0; j < coluna*zoom; j++) {
            fprintf(cop, "%d ", imagem[i][j].r);
            fprintf(cop, "%d ", imagem[i][j].g);
            fprintf(cop, "%d\n", imagem[i][j].b);
        }
    }

    fclose(cop);
    printf("\nImagem salva com sucesso!\n");
}

