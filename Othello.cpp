#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<time.h>
#define tamanho 8
FILE *file;
void grade(char gradeJogo[][tamanho]);
void fazMovimento(char gradeJogo[][tamanho], int linha, int coluna, char jogador);
int calcularPontos(char gradeJogo[][tamanho], char jogador);
void jogadaComputador(char gradeJogo[][tamanho], int movimento[][tamanho], char jogador);
int validarMovimento(char gradeJogo[][tamanho], int movimento[][tamanho], char jogador);
void iniciarJogo1();
void iniciarJogo2();
void Pontos();

	
int main(){
	int exit=1, escolha=5, i;
	printf("\n-----------------------------------\n           Seja Bem-Vindo\n-----------------------------------\n");
	printf("Trabalho de: Monica Hillman\n");
	printf("Disciplina: Programacao Estruturada\n");
	printf("Bacharelado em Tecnologias Digitais\n");
	for(i=1;i=exit;i=i){
		printf("\nDigite 1 para iniciar o jogo multiplayer");
		printf("\nDigite 2 para iniciar o jogo vs computador");
		printf("\nDigite 3 para pontuacoes");	
		printf("\nDigite 0 para sair");
		printf("\nEscolha:");
		scanf("%d",&escolha);
		switch(escolha){
			case 1:
				iniciarJogo1();
				break;
			case 2:
				iniciarJogo2();
			    break;
			case 3:
				Pontos();
			    break;
			case 0:
				exit=0;
				break;			
			default:
				printf("\n Digite uma opcao valida!\n");
				break;
		}
	}
	fclose(file);
	system("pause");
}

void grade(char gradeJogo[][tamanho]){   //Funcao pra exibir a grade do jogo
   int linha  = 0;          
   int coluna = 0;          
   char col_label = 'a';
   printf("\n ");         
   for(coluna = 0 ; coluna<tamanho ;coluna++)
     printf("   %c", col_label+coluna); 
   printf("\n");                     
   
   for(linha = 0; linha < tamanho; linha++){
     printf("  ~");
     for(coluna = 0; coluna<tamanho; coluna++)
       printf("---~");
     printf("\n%2d|",linha + 1);

     for(coluna = 0; coluna<tamanho; coluna++)
       printf(" %c |", gradeJogo[linha][coluna]);  
     printf("\n");
   }

   printf("  ~");                 
   for(coluna = 0 ; coluna<tamanho ;coluna++)
     printf("---~");               
   printf("\n");                
}

void fazMovimento(char gradeJogo[][tamanho], int linha, int coluna, char jogador){ //Faz um movimento do jogador;
   int linhadelta = 0, coldelta = 0, x = 0, y = 0;                      
   char oponent = (jogador == 'A')? 'V' : 'A';  

   gradeJogo[linha][coluna] = jogador;       

   for(linhadelta = -1; linhadelta <= 1; linhadelta++)
     for(coldelta = -1; coldelta <= 1; coldelta++){      
       if(linha + linhadelta < 0 || linha + linhadelta >= tamanho || coluna + coldelta < 0 || coluna + coldelta >= tamanho || (linhadelta==0 && coldelta== 0)){
	   continue;
	   } 
       if(gradeJogo[linha + linhadelta][coluna + coldelta] == oponent){
         x = linha + linhadelta;       
         y = coluna + coldelta;        

         for(;;){
           x += linhadelta;          
           y += coldelta;
           if(x < 0 || x >= tamanho || y < 0 || y >= tamanho){
        	break;
		   }   
           if(gradeJogo[x][y] == ' '){
		   break;
		   }            
           if(gradeJogo[x][y] == jogador){
             while(gradeJogo[x-=linhadelta][y-=coldelta]==oponent) 
               gradeJogo[x][y] = jogador;    
             break;                     
           }
         }
       }
     }
}

int calcularPontos(char gradeJogo[][tamanho], char jogador){    //Calcula a pontuacao;
   int score = 0, linha = 0, coluna = 0; 
   char oponent = jogador == 'A' ? 'V' : 'A';
   for(linha = 0; linha < tamanho; linha++)
     for(coluna = 0; coluna < tamanho; coluna++){
     score -= gradeJogo[linha][coluna] == oponent; 
     score += gradeJogo[linha][coluna] == jogador;  
   }
   return score;
}

int melhorMovimento(char gradeJogo[][tamanho], int movimento[][tamanho], char jogador) {  //Identifica o melhor movimento para o pc;


int linha = 0, coluna = 0, i = 0, j = 0;
char oponent = jogador == 'A'? 'V': 'A';
char nova_grade[tamanho][tamanho] = {0};
int pontuacao = 0;
int nova_pontuacao = 0;

for (linha = 0; linha < tamanho; linha++)
for (coluna = 0; coluna < tamanho; coluna++)
{
	if (!movimento[linha][coluna])
	continue;
	for (i = 0; i< tamanho; i++)
	for (j = 0; j < tamanho; j++)
	nova_grade[i][j] = gradeJogo[i][j];
	
	fazMovimento(nova_grade, linha, coluna, jogador);
	nova_pontuacao = calcularPontos(nova_grade, jogador);
	
	if (pontuacao < nova_pontuacao)
	pontuacao = nova_pontuacao;
}
return pontuacao;
}

void jogadaComputador(char gradeJogo[][tamanho], int movimento[][tamanho], char jogador){ //Jogada do computador;
   int linha = 0, coluna = 0, melhorlinha =0, melhorcoluna = 0, i = 0, j = 0, nova_pontuacao = 0, pontuacao = 100;
   char oponent = (jogador == 'A')? 'V' : 'A';
   char temp_grade[tamanho][tamanho];
   int temp_movimento[tamanho][tamanho]; 
   
   for(linha = 0; linha < tamanho; linha++)
     for(coluna = 0; coluna < tamanho; coluna++)
     {
       if(movimento[linha][coluna] == 0)
         continue;
     for(i = 0; i < tamanho; i++)
         for(j = 0; j < tamanho; j++)
           temp_grade[i][j] = gradeJogo[i][j];
      fazMovimento (temp_grade, linha, coluna, oponent);     
    validarMovimento (temp_grade, temp_movimento, oponent);
    nova_pontuacao = melhorMovimento(temp_grade, temp_movimento, oponent);
	
	if (nova_pontuacao < pontuacao)
	{
		pontuacao = nova_pontuacao;
		melhorlinha = linha;
		melhorcoluna = coluna;
	 } 
  }
   fazMovimento(gradeJogo, melhorlinha, melhorcoluna, jogador); 
}

int validarMovimento(char gradeJogo[][tamanho], int movimento[][tamanho], char jogador){  //Identifica os moviimentos validos;
   int linhadelta = 0, coldelta = 0, linha = 0, coluna = 0, x = 0, y = 0, contarMovimentos = 0;  
   char oponent = (jogador == 'A')? 'V' : 'A';
   for(linha = 0; linha < tamanho; linha++)
     for(coluna = 0; coluna < tamanho; coluna++)
       movimento[linha][coluna] = 0;
       
   for(linha = 0; linha < tamanho; linha++)
     for(coluna = 0; coluna < tamanho; coluna++){
       if(gradeJogo[linha][coluna] != ' ')  
         continue;                 

       for(linhadelta = -1; linhadelta <= 1; linhadelta++)
         for(coldelta = -1; coldelta <= 1; coldelta++){
           if(linha + linhadelta < 0 || linha + linhadelta >= tamanho || coluna + coldelta < 0 || coluna + coldelta >= tamanho ||(linhadelta==0 && coldelta==0)){
			continue;
		   }             
		
           if(gradeJogo[linha + linhadelta][coluna + coldelta] == oponent){            
             x = linha + linhadelta;              
             y = coluna + coldelta;
             for(;;){
               x += linhadelta;                  
               y += coldelta;
               if(x < 0 || x >= tamanho || y < 0 || y >= tamanho){			   
                 break;
                }
               if(gradeJogo[x][y] == ' '){
               	break;
			   }
               if(gradeJogo[x][y] == jogador){
                 movimento[linha][coluna] = 1;  
                 contarMovimentos++;         
                 break;                 
               }
             }
           }
         }
     }
   return contarMovimentos;
}

void iniciarJogo1(){ //Inicia jogo player vs player;
  char gradeJogo[tamanho][tamanho] = { 0 };  
  int movimento[tamanho][tamanho] = { 0 };  
  system ("color 0F");   
  int linha = 0, coluna = 0, num_jog = 1, contarMovimentos = 0, invalidarMovimento = 0;            
  int pontosJogador2 = 0, pontosJogador1 = 0, x = 0, jogador = 0, escol = 0;
  char y = 0, flag = 0, jogador1[20], jogador2[20];
  do{  
  printf ("\nO jogo tem como meta capturar pecas adversarias e transforma-las nas da sua cor, vence quem tiver mais pecas.\n");
  printf ("O jogo sera em turnos, o jogador 1 sera a cor AMARELA (A) e o jogador 2 sera VERDE (V).\nEscreva a linha em numeros e a coluna em letras, sem espaco entre os dois.\n");
  printf("\nNome do jogador 1: ");
  scanf("%s", &jogador1); 
  printf("\nNome do jogador 2: ");   
  scanf("%s", &jogador2);   
  scanf("%c", &flag);
  printf("\n ----------------------------------------------------------");   
  printf("\n  Voce deve digitar o numero e a letra em que deseja jogar\n ");   
  printf("----------------------------------------------------------");
  jogador = ++ num_jog % 2;
  contarMovimentos = 4;    // comeca com 4 movimentos já feitos;          
     
     for(linha = 0; linha < tamanho; linha++)
       for(coluna = 0; coluna < tamanho; coluna++)
         gradeJogo[linha][coluna] = ' ';
         
     gradeJogo[tamanho/2-1][tamanho/2-1] = gradeJogo[tamanho/2][tamanho/2] = 'A';
     gradeJogo[tamanho/2-1][tamanho/2] = gradeJogo[tamanho/2][tamanho/2-1] = 'V';

     do{
        system("cls");
       grade(gradeJogo); // mostra a grade;
       if(jogador++ % 2){ // jogador A;
         if(validarMovimento(gradeJogo, movimento, 'A')){
           for(;;){
             fflush(stdin);  
             system ("color 0E");              
             printf("Digite o numero e a letra, %s ('A' AMARELO): ",jogador1);
             scanf("%d%c", &x, &y); //le a linha e a coluna;
             
             y = tolower(y) - 'a';        
             x--;    
             if( x>=0 && y>=0 && x<tamanho && y<tamanho && movimento[x][y]){  //requisitos para o movimento ser válido;
               fazMovimento(gradeJogo, x, y, 'A'); // faz o movimento;
               contarMovimentos++;            //aumenta a contagem de movimentos;
               break;
             }
             else
               printf("Digite uma linha valida!\n"); //se nao preencher o requisito de ser valido, pedira para inserir denovo;
           }
         }
         else                             
           if(++invalidarMovimento<2){
             fflush(stdin);
             printf("\n Para passar Pressione 'Enter'"); //se nao houver movimentos validos, aperte enter para passar;
             scanf("%c", &flag);
           }
           else
             printf("\n Nenhum pode seguir, o jogo acabou.\n"); //se ambos não houver movimentos validos, fim de jogo;
       }
else

 if(validarMovimento(gradeJogo, movimento, 'V')){ //jogador B
           for(;;){
             fflush(stdin);
             system ("color 0A");           
             printf("Digite o numero e a letra, %s ('V' VERDE): ",jogador2);
             scanf("%d%c", &x, &y);
             
             y = tolower(y) - 'a';       
             x--;                        
             if( x>=0 && y>=0 && x<tamanho && y<tamanho && movimento[x][y]){
               fazMovimento(gradeJogo, x, y, 'V');
               contarMovimentos++;                                  
               break;
             }
             else
               printf("Digite uma linha valida!\n");
           }
         }
         else                              
           if(++invalidarMovimento<2){
             fflush(stdin);
             printf("\n Para passar Pressione 'Enter'");
             scanf("%c", &flag);
           }
           else
             printf("\n Nenhum pode seguir, o jogo acabou.\n");

     }while(contarMovimentos < tamanho*tamanho && invalidarMovimento<2);
     
     grade(gradeJogo);      
     pontosJogador2 = pontosJogador1 = 0;
     for(linha = 0; linha < tamanho; linha++)
       for(coluna = 0; coluna < tamanho; coluna++){
         pontosJogador2 += gradeJogo[linha][coluna] == 'V';
         pontosJogador1 += gradeJogo[linha][coluna] == 'A';
       }
     
     printf("Pontuacao Final: \n");
     printf("%s %d \n",jogador1,pontosJogador1);
     
     printf("%s %d \n\n",jogador2,pontosJogador2);     
     if(pontosJogador1 > pontosJogador2){
         printf("Vencedor: %s \n\n",jogador1);
         
     }
     else if(pontosJogador1==pontosJogador2){
         printf("EMPATOU\n\n");
     }
     else{
         printf("Vencedor: %s \n\n",jogador2);
     }
     
    int i = 0;
    int j = 0;
    printf ("Salvando o Jogo...");
    file = fopen("file.txt", "a"); //Salvando pontuacao no arquivo texto;
  	fprintf(file,"Pontuacao: \n");
    fprintf(file,"%s %d \n",jogador1,pontosJogador1); //pontos jogador 1
    fprintf(file,"%s %d \n\n",jogador2,pontosJogador2);     //pontos jogador 2
     if(pontosJogador1 > pontosJogador2){
         fprintf(file,"Vencedor: %s \n\n",jogador1); //informa vencedor caso for o 1
             }
     else if(pontosJogador1==pontosJogador2){ //informa empate;
         fprintf(file,"EMPATOU\n\n");
     }
     else{
         fprintf(file,"Vencedor: %s \n\n",jogador2); //informa vencedor caso for o 2
     }
	fprintf(file,"\n");
	fclose(file);
     system ("color 0F");   
     printf("Jogar novamente? SIM = 'S', NAO = 'N' "); //se escolher jogar novamente irá voltar para a tela de pedir nomes, se não, para menu inicial;
     scanf("%s", &flag);     
     
   }while(tolower(flag) == 's'); 
}

void iniciarJogo2(){ //Inicio jogo player vs computador;
  char gradeJogo[tamanho][tamanho] = { 0 };  
  int movimento[tamanho][tamanho] = { 0 };  
  system ("color 0F");   
  int linha = 0, coluna = 0, num_jog = 1, contarMovimentos = 0, invalidarMovimento = 0;            
  int pontosJogador2 = 0, pontosJogador1 = 0, x = 0, jogador = 0, escol = 0;
  char y = 0, flag = 0, jogador1[20];
  
  do
  { 
  printf ("\nO jogo tem como meta capturar pecas adversarias e transforma-las nas da sua cor, vence quem tiver mais pecas.\n");
  printf ("O jogo sera em turnos, o jogador tera a cor AMARELA (A) e o computador sera VERDE (V).\nEscreva a linha em numeros e a coluna em letras, sem espaco entre os dois.\n");
  printf("\nNome do jogador 1: "); //pede nome do jogador;
  scanf("%s", &jogador1);
  char jogador2[] = "Computador"; //informa automaticamente que o jogador 2 é o computador;
  scanf("%c", &flag);
  printf("\n ----------------------------------------------------------");   
  printf("\n  Voce deve digitar o numero e a letra em que deseja jogar\n ");   
  printf("----------------------------------------------------------");
  jogador = ++ num_jog % 2;
  contarMovimentos = 4;              
     
     for(linha = 0; linha < tamanho; linha++)
       for(coluna = 0; coluna < tamanho; coluna++)
     gradeJogo[linha][coluna] = ' ';        
     gradeJogo[tamanho/2-1][tamanho/2-1] = gradeJogo[tamanho/2][tamanho/2] = 'A';
     gradeJogo[tamanho/2-1][tamanho/2] = gradeJogo[tamanho/2][tamanho/2-1] = 'V';

     do{
        system("cls");
       grade(gradeJogo);             
       if(jogador++ % 2){ 
         if(validarMovimento(gradeJogo, movimento, 'A'))
		 {
           for(;;)
		   {
             fflush(stdin);  
             system ("color 0E");              
             printf("Digite o numero e a letra, %s ('A' AMARELO): ",jogador1);
             scanf("%d%c", &x, &y);
             y = tolower(y) - 'a';        
             x--;    
             if( x>=0 && y>=0 && x<tamanho && y<tamanho && movimento[x][y])
			 {
               fazMovimento(gradeJogo, x, y, 'A');
               contarMovimentos++;            
               break;
             }
             else
               printf("Digite uma linha valida!\n");
           }
         }
         else                             
           if(++invalidarMovimento<2)
		   {
             fflush(stdin);
             printf("\n Para passar Pressione 'Enter'");
             scanf("%c", &flag);
           }
           else
             printf("\n Nenhum pode seguir, o jogo acabou.\n");
       }
else
{
 if(validarMovimento(gradeJogo, movimento, 'V')){ //se jogador 2 = PC;
           invalidarMovimento = 0;   
           jogadaComputador(gradeJogo, movimento, 'V'); //chama funcao da jogada do computador;
           contarMovimentos++;           //conta movimentos;
         }
         else
         {
           if(++invalidarMovimento<2)
             printf("\nNao tenho movimentos validos, sua vez.\n"); //se o pc nao tiver movimentos validos, ira dizer que não tem movimentos validos e é a vez do usuário;
           else
             printf("\nNenhum de nos temos movimentos validos, fim de jogo.\n"); //se nenhum tiver movimentos validos, fim do jogo;
         }
       }
     }while(contarMovimentos < tamanho*tamanho && invalidarMovimento<2);
     
     grade(gradeJogo);      
     pontosJogador2 = pontosJogador1 = 0;
     for(linha = 0; linha < tamanho; linha++){ 
       for(coluna = 0; coluna < tamanho; coluna++){
         pontosJogador2 += gradeJogo[linha][coluna] == 'V';
         pontosJogador1 += gradeJogo[linha][coluna] == 'A';
		}
	}
 printf("Pontuacao Final: \n");
     printf("%s %d \n",jogador1,pontosJogador1);
     
     printf("%s %d \n\n",jogador2,pontosJogador2);     
     if(pontosJogador1 > pontosJogador2){
         printf("Vencedor: %s \n\n",jogador1);
         
     }
     else if(pontosJogador1==pontosJogador2){
         printf("EMPATOU\n\n");
     }
     else{
         printf("Vencedor: %s \n\n",jogador2);
     }
	
	
    int i = 0;
    int j = 0;
    printf ("Salvando o Jogo...");
    file = fopen("file.txt", "a");
  	fprintf(file,"Pontuacao: \n");
    fprintf(file,"%s %d \n",jogador1,pontosJogador1);
    fprintf(file,"%s %d \n\n",jogador2,pontosJogador2);     
     if(pontosJogador1 > pontosJogador2){
         fprintf(file,"Vencedor: %s \n\n",jogador1);
             }
     else if(pontosJogador1==pontosJogador2){
         fprintf(file,"EMPATOU\n\n");
     }
     else{
         fprintf(file,"Vencedor: %s \n\n",jogador2);
     }
	fprintf(file,"\n");
	fclose(file);
     system ("color 0F");   
     printf("Jogar novamente? SIM = 'S', NAO = 'N' ");
     scanf("%s", &flag);     
     
   }while(tolower(flag) == 's'); 
}

void Pontos(){ //Leitura de jogos salvos;
	file = fopen("file.txt", "rt");
	char var[50];
	while (fscanf(file, "%s", var) != EOF) {
		printf("%s\n", var);
	}
	fclose(file);
}



