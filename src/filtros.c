#include "filtros.h"
#include <stdio.h>

void grey(pix **imagem, int coluna, int linha){ /*Função que torna a imagem em escala de cinza*/

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            /* Soma-se 30% de vermelho a 60% de verde e 10% de azul e repete isso por todos os pixels*/
            imagem[i][j].r = (int) ((0.299 * imagem[i][j].r) + (0.587 * imagem[i][j].g) + (0.144 * imagem[i][j].b));
            imagem[i][j].g = imagem[i][j].r; //Copia o valor do vermelho para o verde
            imagem[i][j].b = imagem[i][j].r; //Copia o valor do vermelho para o azul

                    if (imagem[i][j].r > 255) {  /*Testa os limites dos pixels e os condiciona a 255 se forem maiores que isso*/
                        imagem[i][j].r = 255;
                        imagem[i][j].g = 255;
                        imagem[i][j].b = 255;
                    }
            }
    }
    return;
}


int bin(pix **imagem, int colunas, int linhas){ /*Função que binariza uma imagem.*/

    int limite, i, j, opt;
    printf("Em que nivel gostaria sua binarizacao?\n1 - Baixo\t2- Medio\t3- Alto\n");
    scanf("%i", &opt);

        switch(opt){ /*Usa a resposta do usuário para realizar a alteraçao correspondente*/

        case 1:
        limite = 72;
        break;

        case 2:
        limite = 82;
        break;

        case 3:
        limite = 92;
        break;

        default:
        printf("Opcao invalida!\n");
        return 1;
}

    for(i = 0; i<linhas; i++){
        for(j = 0; j<colunas; j++){
            /*Testa se a tornalidade dos pixels da imagem são menores que o valor limite e os torna 0 se forem*/
            if(imagem[i][j].r < limite || imagem[i][j].g < limite || imagem[i][j].b < limite ){
                imagem[i][j].r = 0;
                imagem[i][j].g = 0;
                imagem[i][j].b = 0;

            }
            else{
            /*Se as tornalidades não forem menores, devem se tornar 255*/
                imagem[i][j].r = 255;
                imagem[i][j].g = 255;
                imagem[i][j].b = 255;
            }
        }
    }
    return 0;
}


void blur(pix **imagem, int coluna, int linha){ /*Função que aplica o filtro blur*/

    int lin, col, i, j, somaR, somaG, somaB;

    float blrr[3][3] = { {0.0625, 0.125, 0.0625},   /*Valores fixos pelos quais os pixels devem ser multiplicados*/
                          {0.125, 0.25, 0.125},
                          {0.0625, 0.125, 0.0625}
                        };

    for(lin = 1; lin < linha-1; lin++){
        for(col = 1; col < coluna-1; col++){

                somaR = 0;
                somaG = 0;
                somaB = 0;

                    for(i = 0; i < 3; i++){
                        for(j = 0; j < 3; j++){

                            somaR = somaR  + (imagem[lin-1 + i][col-1 + j].r) * blrr[i][j];
                            somaG = somaG  + (imagem[lin-1 + i][col-1 + j].g) * blrr[i][j];
                            somaB = somaB  + (imagem[lin-1 + i][col-1 + j].b) * blrr[i][j];
                        }
                    }

                if(somaR > 255){
                    somaR = 255;
                }
                if(somaG > 255){
                    somaG = 255;
                }
                if(somaB > 255){
                    somaB = 255;
                }

                if(somaR < 0){
                    somaR = 0;
                }
                if(somaG < 0){
                    somaG = 0;
                }
                if(somaB < 0){
                    somaB = 0;
                }

                imagem[lin][col].r = somaR;
                imagem[lin][col].g = somaG;
                imagem[lin][col].b = somaB;

            }
        }


    return;
}


void sharpen(pix **imagem, pix **modificada, int coluna, int linha){ /*Função que aplica o filtro sharpen*/

    int lin, col, i, j, somaR, somaG, somaB;

    float sharp[3][3] = { {0, -1, 0},   /*Valores fixos pelos quais os pixels devem ser multiplicados*/
                          {-1, 5, -1},
                          {0, -1, 0}
                        };
    somaR = 0;
    somaG = 0;
    somaB = 0;

    for(lin = 1; lin < linha-1; lin++){
        for(col = 1; col < coluna-1; col++){

                    for(i = 0; i < 3; i++){
                        for(j = 0; j < 3; j++){

                            somaR = somaR  + (imagem[lin-1 + i][col-1 + j].r) * sharp[i][j];
                            somaG = somaG  + (imagem[lin-1 + i][col-1 + j].g) * sharp[i][j];
                            somaB = somaB  + (imagem[lin-1 + i][col-1 + j].b) * sharp[i][j];
                        }
                    }

                if(somaR > 255){
                    somaR = 255;
                }
                if(somaG > 255){
                    somaG = 255;
                }
                if(somaB > 255){
                    somaB = 255;
                }

                if(somaR < 0){
                    somaR = 0;
                }
                if(somaG < 0){
                    somaG = 0;
                }
                if(somaB < 0){
                    somaB = 0;
                }

                modificada[lin][col].r = somaR;
                modificada[lin][col].g = somaG;
                modificada[lin][col].b = somaB;



            }
        }

    for(i = 0 ; i < coluna; ++i){
        for(j = 0 ; j < linha; ++j){

                imagem[i][j].r = modificada[i][j].r;
                imagem[i][j].g = modificada[i][j].g;
                imagem[i][j].b = modificada[i][j].b;

            }
        }

    return;
}


void detBord(pix **imagem, pix **transposta, int coluna, int linha){ /*Função de detecção de bordas*/

    int lin, col, i, j, somaR, somaG, somaB;

    float detec[3][3] = { {0, 1, 0},   /*Valores fixos pelos quais os pixels devem ser multiplicados*/
                          {1, -4, 1},
                          {0, 1, 0}
                        };

    for(lin = 1; lin < linha-1; lin++){
        for(col = 1; col < coluna-1; col++){

                somaR = 0;
                somaG = 0;
                somaB = 0;

                    for(i = 0; i < 3; i++){
                        for(j = 0; j < 3; j++){

                            somaR = somaR  + (imagem[lin-1 + i][col-1 + j].r) * detec[i][j];
                            somaG = somaG  + (imagem[lin-1 + i][col-1 + j].g) * detec[i][j];
                            somaB = somaB  + (imagem[lin-1 + i][col-1 + j].b) * detec[i][j];
                        }
                    }

                if(somaR > 255){
                    somaR = 255;
                }
                if(somaG > 255){
                    somaG = 255;
                }
                if(somaB > 255){
                    somaB = 255;
                }

                if(somaR < 0){
                    somaR = 0;
                }
                if(somaG < 0){
                    somaG = 0;
                }
                if(somaB < 0){
                    somaB = 0;
                }

                transposta[lin][col].r = somaR;
                transposta[lin][col].g = somaG;
                transposta[lin][col].b = somaB;
        }
    }

    for(i = 0 ; i < coluna; ++i){
        for(j = 0 ; j < linha; ++j){

                imagem[i][j].r = transposta[i][j].r;
                imagem[i][j].g = transposta[i][j].g;
                imagem[i][j].b = transposta[i][j].b;
        }
    }

    return;

}


void sepia(pix **imagem, int coluna, int linha){ /*Função que deixa a imagem em tons de sépia*/

    int i, j;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            imagem[i][j].r = (int) ((0.393 * imagem[i][j].r) + (0.769 * imagem[i][j].g) + (0.189 * imagem[i][j].b));
            imagem[i][j].g = (int) ((0.349 * imagem[i][j].r) + (0.686 * imagem[i][j].g) + (0.168 * imagem[i][j].b));
            imagem[i][j].b = (int) ((0.272 * imagem[i][j].r) + (0.534 * imagem[i][j].g) + (0.131 * imagem[i][j].b));

                    if (imagem[i][j].r > 255) {
                        imagem[i][j].r = 255;
                        imagem[i][j].g = 255;
                        imagem[i][j].b = 255;
                    }
        }
    }
    return;
}


void negativo(pix **imagem, int coluna, int linha){ /*Função que deixa a imagem negativa*/

    for(int i = 0; i<linha; i++){
        for(int j = 0; j<coluna; j++){

            imagem[i][j].r = (255 - imagem[i][j].r);
            imagem[i][j].g = (255 - imagem[i][j].b);
            imagem[i][j].b = (255 - imagem[i][j].b);

        }
    }
    return;
}
