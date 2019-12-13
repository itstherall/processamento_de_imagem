#include <stdio.h>
#include <stdlib.h>
#include "movimento_de_imagens.h"
#include "abertura_e_copia.h"
#include "filtros.h"
#include "estruturasdef.h"

typedef enum{  /* Estrutura para determinar as opções do menu e enumerá-las*/

    gr = 1,
    sep,
    ngt,
    sharp,
    blr,
    binr,
    det,
    zmi,
    zmo,
    rot90e,
    rot90d,
    rot180,
    espel,
    espelv,
    save,
    quit

}options;




void menu(){/*Função para exibir menu*/
    printf("\t1. Escala de cinza\n\t2. Sepia\n\t3. Negativo\n\t4. Sharpening\n\t5. Blurring\n\t");
    printf("6. Binarizacao\n\t7. Detecao de bordas\n\t8. Zoom in\n\t9. Zoom out\n\t10. Rotacionar 90 graus a esquerda\n\t11. Rotacionar 90 graus a direita\n\t");
    printf("12. Rotacionar 180 graus\n\t13. Espelhar Horizontal\n\t14. Espelhar vertical\n\t15. Salvar\n\t16. Sair\n");
}

int main(){

    int i, maxTon, larg, alt; //Largura = Colunas; Altura = Linhas;
    int option, opt = 0, sav, men = 0;
    int zoom, prmt = 0;
    char IDF[3], nome[50];
    int loopdois = 0, resposta;
    FILE *arquivo;
    pix **imagem, **transposta, **imagemloc, **imagemzoom;

    printf("Entre com o nome do arquivo:\n");
    scanf("%s", nome); //Lê o nome do arquivo

    arquivo = fopen(nome, "r"); //Abre o arquivo para leitura

    if(arquivo == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }

    ler(arquivo, IDF, &maxTon, &larg, &alt); /* Realiza a leitura da imagem antes da alocação da matriz
                                                        para os pixels pois precisamos dos valores de largura e altura*/

    /* Aloca a matriz que armazena os pixels da imagem*/
    imagem = (pix **)calloc(alt, sizeof(pix *));
    for(i = 0; i<alt; i++){
        imagem[i] = (pix *)calloc(larg, sizeof(pix));
    }

    /* Pega os pixels da imagem e os coloca na matriz alocada anteriormente*/
    pegar_pixels(imagem, arquivo, alt, larg);

    /*  Aloca a matriz transposta(col x lin) que será usada para a função que a utilizem
                  como blur, sharp, rotacionar 90 graus esq e direita  */
    transposta=(pix **)calloc(larg , sizeof(pix *));
    for(i = 0; i < larg ; ++i){
        transposta[i]=(pix *)calloc(alt ,sizeof(pix ));
    }

    /*Uma matriz do mesmo tamanho da do arquivo aberto para funções como zoom e centoeoitenta*/
    imagemloc= (pix **)calloc(alt, sizeof(pix *));
    for(i = 0; i < alt; i++){
        imagemloc[i] = (pix*)calloc(larg, sizeof(pix ));
    }

    /* Escolher as opções */
    do{

        if(men == 0){
                printf("\n\t\tM  E  N  U\t\t\n\n");
        menu();
        }else{
        printf("\n\t\tO que mais deseja?\n\n");
        menu();
        }
        printf("\t\t>> ");
        scanf("%i", &option);

        switch(option){
            case espelv:
                espelhandovert(imagem, imagemloc, larg, alt);
                prmt = 3;
                break;

            case espel:
                espelhandohor(imagem, imagemloc , larg, alt);
                prmt = 3;
                break;

            case rot90d:
                rotacao_dir(imagem, transposta, larg, alt);
                prmt = 4;
                break;

            case rot90e:
                rotacao_esq(imagem, transposta, larg, alt);
                prmt = 4;
                break;

            case rot180:
                centoeoitenta(imagem, imagemloc, larg, alt);
                prmt = 3;
                break;

            case gr:
                grey(imagem, larg, alt);
                prmt = 3;
                break;

            case sep:
                sepia(imagem, larg, alt);
                prmt = 3;
                break;

            case binr:
                bin(imagem, larg, alt);
                prmt = 3;
                break;

            case blr:
                blur(imagem, larg, alt);
                prmt = 3;
                break;

            case sharp:
                sharpen(imagem, transposta, larg, alt);
                prmt = 3;
                break;

            case det:
                detBord(imagem, transposta, larg, alt);
                prmt = 4;
                break;

            case zmi:
                while(loopdois == 0)
                {   /*pede para escolher se vai ser o zoom em um local escolhindo ou na imagem inteira*/
                    printf("Qual zoom você deseja aplicar:\n");
                    printf("\t1 - Zoom local\n\t2 - Zoom imagem inteira\n");
                    scanf("%d", &resposta);
                    if(resposta < 0 && resposta > 2)
                    {
                        printf("Digite uma opcao valida!!!\n");
                    }
                    else
                    {
                        loopdois = 1;
                    }
                }

                if(resposta == 1)
                {
                    prmt = 3;
                    printf("> Quanto de zoom in deseja aplicar? (apenas inteiros maiores que dois e pares!)\n");
                    scanf("%d", &zoom);
                    zoomin(imagem, imagemloc, zoom, larg, alt); //aplica zoom no local escolhido
                }
                else if (resposta == 2)
                {
                    prmt = 2;
                    printf("> Quanto de zoom in deseja aplicar? (apenas inteiros maiores que dois e pares!)\n");
                    scanf("%d", &zoom);
                    imagemzoom=(pix **)calloc(alt*zoom, sizeof(pix *));
                    for(i = 0 ; i < alt*zoom ; ++i)
                    {
                        imagemzoom[i]=(pix *)calloc(larg*zoom, sizeof(pix ));
                    }
                    zoomintotal(imagem , imagemzoom, zoom, larg, alt); //aplica zoom na imagem inteira
                }
                break;

            case zmo:
                printf("> Quanto de zoom out deseja aplicar? (apenas inteiros maiores que dois e pares!)\n");
                scanf("%d", &zoom);
                zoomout(imagem, imagemloc, zoom, larg, alt);
                prmt = 1;
                break;

            case ngt:
                negativo(imagem, larg, alt);
                prmt = 3;
                break;

            case save:

                if(prmt == 1 )
                {
                    copiando(imagemzoom, maxTon, larg, alt, zoom);
                }
                if(prmt == 2)
                {
                   copiado(imagemzoom , zoom, maxTon, larg , alt);
                }
                if(prmt == 3)
                {
                    copia(imagem, maxTon, larg, alt);
                }
                if(prmt == 4)
                {
                    copya(imagem, transposta, maxTon, larg, alt);
                }
                opt++;
                break;

            case quit:
                printf("Deseja salvar antes de sair?1. Sim\t2.Nao\n");
                scanf("%d", &sav);
                if(sav == 1){
                    if(prmt == 3){
                        copia(imagem, maxTon, larg, alt);
                    }else if (prmt == 4){
                        copya(imagem, transposta, maxTon, larg, alt);
                    }
                    else if (prmt == 2){
                        copiado(imagemzoom , zoom, maxTon, larg , alt);
                    }
                    else if (prmt == 0){
                        copiando(imagemzoom, maxTon, larg, alt, zoom);
                    }
                opt++;
                break;

                }else{
                    opt++;
                    break;
                }

            default:
                opt++;
                printf("Opçao invalida\n");
        }
    men++;
    }while(opt == 0);

    fclose(arquivo);    /*Fecha o arquivo*/
    return 0;
}
