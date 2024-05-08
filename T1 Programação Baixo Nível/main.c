#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct pixel
{
 int r;
 int g;
 int b;   
};

int main()
{
 printf("\f");   
 int opcao1;
 int opcao2;   
 char imagem[8];
 do
 {
  printf("Qual imagem deseja modificar?\n");
  printf("(1) Leao\n");
  printf("(2) Pintura\n");
  scanf("%d", &opcao1);  
 }
 while(opcao1 != 1 && opcao1 != 2);
 
 if(opcao1 == 1)
 {
  strcpy(imagem, "leao.ppm");//Copia a string leao.ppm para imagem(imagem=leao.ppm)
 }
 else
 {
  strcpy(imagem, "obra.ppm");
 } 
 
  //abrir o arquivo
 FILE *fp; 
 fp = fopen(imagem, "r");
 char tipoImg[3];//P3
 int i, j, linhas, colunas, valor, r, g, b;

 fscanf(fp, "%s", tipoImg);//lê o tipo da imagem
 fscanf(fp, "%d %d", &colunas, &linhas );// lê a quantidade de colunas e linhas da imagem
 fscanf(fp, "%d", &valor);// lê o valor máximo de cada pixel
 strcpy(tipoImg,"P3");
 valor = 255;
 if(opcao1==1)
 {
  colunas = 275;
  linhas = 183;
 }
 else
 {
  colunas = 685;
  linhas = 979;
 }

 //Alocação de memória da matriz de pixels rgb
 struct pixel **matriz = (struct pixel **)malloc(linhas * sizeof(struct pixel *));
 for( int i =0; i< linhas;i++)
 {
  matriz[i] = (struct pixel *) malloc(colunas * sizeof(struct pixel));
 } 

 //Leitura dos valores de pixel rgb
 for (int i = 0; i < linhas; i++) 
 {
  for (int j = 0; j < colunas; j++) 
  {
   fscanf(fp, "%d", &r); // Leitura do valor R
   fscanf(fp, "%d", &g); // Leitura do valor G
   fscanf(fp, "%d", &b); // Leitura do valor B
   matriz[i][j].r = r;
   matriz[i][j].g = g;
   matriz[i][j].b = b;
      //printf("(%d, %d, %d)\t", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b);
  }
   // printf("\n");
 }
 
 // Fecha o arquivo.    
 fclose(fp);




 // printf("VALOR Maximo %d\n", valor);
  //printf("tipoImg %s\n", tipoImg);
  //printf("Coluna e linha %d %d\n", colunas, linhas );


 do
 {
  printf("O que voce deseja fazer?\n");
  printf("(1) Criar uma imagem tom de cinza\n");
  printf("(2) Criar uma imagem negativa a partir de uma tom de cinza \n");  
  printf("(3) Aumentar o brilho de uma imagem tom de cinza\n");  
  printf("(4) Diminuir o brilho de uma imagem tom de cinza\n");   
  printf("(5) Rotacionar a imagem colorida -90 graus \n");  
  printf("(6) Envelhecimento da imagem colorida \n");   
  scanf("%d", &opcao2);  
 }
 while (opcao2<1 || opcao2>6);

 if(opcao2==1)
 {
  ImagemCinza(colunas,linhas,matriz, opcao1);
 }

 if(opcao2==2)
 {
  ImagemNegativa(colunas,linhas,matriz, opcao1);
 }

 if(opcao2==3)
 {
  ImagemMaisBrilho(colunas,linhas,matriz, opcao1);
 }

  if(opcao2==4)
 {
  ImagemMenosBrilho(colunas,linhas,matriz, opcao1);
 }

  if(opcao2==5)
 {
  ImagemRotacionada(colunas,linhas,matriz, opcao1);
 }
  if(opcao2==6)
 {
  ImagemEnvelhecida(colunas,linhas,matriz, opcao1);
 }

 printf("Arquivo criado!");
     for(int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
 return 0;
}

void ImagemCinza(int colunas, int linhas, struct pixel **matriz, int opcao1)
{
 // Criação do novo arquivo ppm
 FILE *fp_novo;
 if( opcao1==1)
 {
  fp_novo = fopen("leao_copiaCinza.ppm", "w");
 }
 else
 {
  fp_novo = fopen("obra_copiaCinza.ppm", "w");
 }

 if(fp_novo == NULL)
 {
  printf("Erro ao criar o arquivo");
  exit(1);
 } 
 // Escrita do cabeçalho do novo arquivo
 fprintf(fp_novo, "P3\n");
 fprintf(fp_novo, "%d %d\n", colunas, linhas);
 int valor = 255;
 fprintf(fp_novo, "%d\n", valor);
 //Escreve os valores RGB da matriz no arquivo
 for(int i =0; i<linhas;i++)
 {
  for(int j=0; j<colunas; j++)
  {
   fprintf(fp_novo, "%d \n %d \n %d\n", (int)(matriz[i][j].r*0.30), (int)(matriz[i][j].g*0.59), (int)(matriz[i][j].b *0.11) );
  }
  fprintf(fp_novo, "\n");
 }
 fclose(fp_novo);//fecha o arquivo
 
 //Libera memória alocada para a matriz de pixels rgb
 for(int i =0; i<linhas;i++)
 {
  free(matriz[i]);
 }
 free(matriz);
}

void ImagemNegativa(int colunas, int linhas, struct pixel **matriz, int opcao1)
{
 // Criação do novo arquivo ppm
 FILE *fp_novo;
 if( opcao1==1)
 {
  fp_novo = fopen("leao_copiaNegativa.ppm", "w");
 }
 else
 {
  fp_novo = fopen("obra_copiaNegativa.ppm", "w");
 }

 if(fp_novo == NULL)
 {
  printf("Erro ao criar o arquivo");
  exit(1);
 } 
 // Escrita do cabeçalho do novo arquivo
 fprintf(fp_novo, "P3\n");
 fprintf(fp_novo, "%d %d\n", colunas, linhas);
 int valor = 255;
 fprintf(fp_novo, "%d\n", valor);
 //Escreve os valores RGB da matriz no arquivo
 for(int i =0; i<linhas;i++)
 {
  for(int j=0; j<colunas; j++)
  { //primeiro transforma a imagem em cinza
   matriz[i][j].r = (matriz[i][j].r * 0.3);   
   matriz[i][j].g = (matriz[i][j].g * 0.59);
   matriz[i][j].b = (matriz[i][j].b * 0.11); 
   //Depois transforma em negativa
   matriz[i][j].r = (int)(255 - matriz[i][j].r);
   matriz[i][j].g = (int)(255 - matriz[i][j].g);
   matriz[i][j].b = (int)(255 - matriz[i][j].b); 
   fprintf(fp_novo, "%d \n %d \n %d\n", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b  );
  }
  fprintf(fp_novo, "\n");
 }
 fclose(fp_novo);//fecha o arquivo
 
 //Libera memória alocada para a matriz de pixels rgb
 for(int i =0; i<linhas;i++)
 {
  free(matriz[i]);
 }
 free(matriz); 
}

void ImagemMaisBrilho(int colunas, int linhas, struct pixel **matriz, int opcao1)
{
 // Criação do novo arquivo ppm
 float brilho =2;// SE QUISER AUMENTAR O BRILHO, AUMENTAR O VALOR
 FILE *fp_novo;
 if( opcao1==1)
 {
  fp_novo = fopen("leao_copiaMaisBrilho.ppm", "w");
 }
 else
 {
  fp_novo = fopen("obra_copiaMaisBrilho.ppm", "w");
 }

 if(fp_novo == NULL)
 {
  printf("Erro ao criar o arquivo");
  exit(1);
 } 
 // Escrita do cabeçalho do novo arquivo
 fprintf(fp_novo, "P3\n");
 fprintf(fp_novo, "%d %d\n", colunas, linhas);
 int valor = 255;
 fprintf(fp_novo, "%d\n", valor);
//Escreve os valores RGB da matriz no arquivo
 for(int i =0; i<linhas;i++)
 {
  for(int j=0; j<colunas; j++)
  {
   matriz[i][j].r = (int)((matriz[i][j].r * 0.30) * brilho);
   matriz[i][j].g = (int)((matriz[i][j].g * 0.59) * brilho);
   matriz[i][j].b = (int)((matriz[i][j].b * 0.11) * brilho);
   if(matriz[i][j].r>255)
   matriz[i][j].r = 255; 
   if(matriz[i][j].g>255)
   matriz[i][j].g = 255; 
   if(matriz[i][j].b>255)
   matriz[i][j].b = 255;   
   fprintf(fp_novo, "%d \n %d \n %d\n", matriz[i][j].r ,  matriz[i][j].g ,  matriz[i][j].b );
  }
  fprintf(fp_novo, "\n");
 }
 fclose(fp_novo);//fecha o arquivo
 
 //Libera memória alocada para a matriz de pixels rgb
 for(int i =0; i<linhas;i++)
 {
  free(matriz[i]);
 }
 free(matriz);
}

void ImagemMenosBrilho(int colunas, int linhas, struct pixel **matriz, int opcao1)
{
  // Criação do novo arquivo ppm
  float brilho =0.5;// SE QUISER DIMINUIR O BRILHO, DIMINUIR O VALOR
  FILE *fp_novo;
  if( opcao1==1)
  {
   fp_novo = fopen("leao_copiaMenosBrilho.ppm", "w");
  }
 else
 {
 fp_novo = fopen("obra_copiaMenosBrilho.ppm", "w");
 }

 if(fp_novo == NULL)
 {
  printf("Erro ao criar o arquivo");
  exit(1);
 } 
 // Escrita do cabeçalho do novo arquivo
 fprintf(fp_novo, "P3\n");
 fprintf(fp_novo, "%d %d\n", colunas, linhas);
 int valor = 255;
 fprintf(fp_novo, "%d\n", valor);
//Escreve os valores RGB da matriz no arquivo
 for(int i =0; i<linhas;i++)
 {
  for(int j=0; j<colunas; j++)
  {
   matriz[i][j].r = (int)((matriz[i][j].r * 0.30) * brilho);
   matriz[i][j].g = (int)((matriz[i][j].g * 0.59) * brilho);
   matriz[i][j].b = (int)((matriz[i][j].b * 0.11) * brilho);
   if(matriz[i][j].r<0)
    matriz[i][j].r = 0; 
   if(matriz[i][j].g<0)
    matriz[i][j].g = 0; 
   if(matriz[i][j].b<0)
    matriz[i][j].b = 0;
   fprintf(fp_novo, "%d \n %d \n %d\n", matriz[i][j].r ,  matriz[i][j].g ,  matriz[i][j].b );
  }
  fprintf(fp_novo, "\n");
 }
 fclose(fp_novo);//fecha o arquivo
 
 //Libera memória alocada para a matriz de pixels rgb
 for(int i =0; i<linhas;i++)
 {
  free(matriz[i]);
 }
 free(matriz);
}

void ImagemRotacionada(int colunas, int linhas, struct pixel **matriz, int opcao1)//VER SE ESTÁ CORRETO DEPOIS
{
  // Criação do novo arquivo ppm
  FILE *fp_novo;
  if( opcao1==1)
  {
   fp_novo = fopen("leao_copiaRotacionada.ppm", "w");
  }
 else
 {

 fp_novo = fopen("obra_copiaRotacionada.ppm", "w");
 }

 if(fp_novo == NULL)
 {
  printf("Erro ao criar o arquivo");
  exit(1);
 } 
 // Escrita do cabeçalho do novo arquivo
 fprintf(fp_novo, "P3\n");
 fprintf(fp_novo, "%d %d\n", linhas, colunas);//Vai rotacionar -90 graus, então os valores de linhas e colunas são trocados
 int valor = 255;
 fprintf(fp_novo, "%d\n", valor);

//Escreve os valores RGB da matriz no arquivo
  for (int i = colunas - 1; i >= 0; i--) 
  {
   for (int j = 0; j < linhas; j++) 
   {
    fprintf(fp_novo, "%d\n %d\n %d\n", matriz[j][i].r, matriz[j][i].g, matriz[j][i].b);
   }
 }

 fclose(fp_novo);//fecha o arquivo
 
 //Libera memória alocada para a matriz de pixels rgb
 for(int i =0; i<linhas;i++)
 {
  free(matriz[i]);
 }
 free(matriz);
}

void ImagemEnvelhecida(int colunas, int linhas, struct pixel **matriz, int opcao1)
{
  // Criação do novo arquivo ppm
  FILE *fp_novo;
  if( opcao1==1)
  {
   fp_novo = fopen("leao_copiaEnvelhecida.ppm", "w");
  }
 else
 {

 fp_novo = fopen("obra_copiaEnvelhecida.ppm", "w");
 }

 if(fp_novo == NULL)
 {
  printf("Erro ao criar o arquivo");
  exit(1);
 } 
 // Escrita do cabeçalho do novo arquivo
 fprintf(fp_novo, "P3\n");
 fprintf(fp_novo, "%d %d\n", colunas, linhas);
 int valor = 255;
 fprintf(fp_novo, "%d\n", valor);
//Escreve os valores RGB da matriz no arquivo
 for(int i =0; i<linhas;i++)
 {
  for(int j=0; j<colunas; j++)
  {
   matriz[i][j].r = matriz[i][j].r -20;
   matriz[i][j].g = matriz[i][j].g -20;
   matriz[i][j].b = matriz[i][j].b -20;
   if(matriz[i][j].r<0)
    matriz[i][j].r = 0; 
   if(matriz[i][j].g<0)
    matriz[i][j].g = 0; 
   if(matriz[i][j].b<0)
    matriz[i][j].b = 0;

   fprintf(fp_novo, "%d \n %d \n %d\n", matriz[i][j].r, matriz[i][j].g, matriz[i][j].b);
  }
  fprintf(fp_novo, "\n");
 }
 fclose(fp_novo);//fecha o arquivo
 
 //Libera memória alocada para a matriz de pixels rgb
 for(int i =0; i<linhas;i++)
 {
  free(matriz[i]);
 }
 free(matriz);
}