#include "../include/musica.h"

struct sentinelamusica
{
  void *prim;
  void *ult;
};

struct litsamusicaantiga
{
  char* cantor;
  char*musica;
  ListaMusicaAntiga *prox;  
}; 

struct listamusicanova
{
  char *musica;
  ListaMusicaNova *prox;  
};

SentinelaMusica* inicializa_sentinela_musica()
{
  SentinelaMusica *Lista=(SentinelaMusica*)malloc(sizeof(SentinelaMusica));

  Lista->prim=NULL;
  Lista->ult=NULL;

  return Lista;
}


ListaMusicaAntiga* cadastrar_musicas(char *nome)
{

  SentinelaMusica *Sentinela=inicializa_sentinela_musica();
  char arquivo[151]="data/";

  strcat(arquivo,nome);
  //printf("%s\n",arquivo);

  FILE* musicas= fopen(arquivo,"r");
  if(musicas==NULL)
  {
    printf("Erro na abertura do arquivo %s",nome);
    exit(1);
  }

  char cantor[121];
  char c; 
  char musica[121];
  int tam=0;

  ListaMusicaAntiga *ant=NULL;

  while(!feof(musicas))
  {
    //formato: Ed Sheeran - Photograph 
    fscanf(musicas,"%[^-]",cantor);
    fscanf(musicas,"%c",&c);
    fscanf(musicas," %[^\n]",musica);
    fscanf(musicas,"%c",&c);

    ListaMusicaAntiga *nova=(ListaMusicaAntiga*)malloc(sizeof(ListaMusicaAntiga));

    //para tirar o espaço do final
    tam=strlen(cantor);
    //substituir o ultimo caracter ' ' por \0
    cantor[tam-1]='\0';
    nova->cantor=strdup(cantor);
        
    //printf(".%s.\n",nova->cantor);
    nova->musica=strdup(musica);
    //printf(".%s.\n",nova->musica);

    //encadear na lista (inserir no final)
    nova->prox=NULL;
    //se lista vazia
    if(Sentinela->prim==NULL)
    {
      Sentinela->prim=nova;
    }
    else
    {
      ant=Sentinela->ult;
      ant->prox=nova;
    }
    Sentinela->ult=nova;
  }
  fclose(musicas);
  //pegar o endereço do primeiro item da lista, não vou mais precisar da sentinela(economia de memoria)
  ant=Sentinela->prim;
  free(Sentinela);
  return ant;
}

int retorna_ponteiro_musica(ListaMusicaAntiga* Lista)
{
  if(Lista==NULL)
  {
    return 1;
  }
  return 0;
}

char* retorna_nome_cantor(ListaMusicaAntiga *Lista)
{
  return Lista->cantor;
}

void insere_musica(SentinelaMusica *Lista,ListaMusicaAntiga *dados)
{  
  ListaMusicaNova *nova=(ListaMusicaNova*)malloc(sizeof(ListaMusicaNova));

  nova->musica=strdup(dados->musica);

  //encadear (no final)
  nova->prox=NULL;

  ListaMusicaNova *aux=NULL;
  //se lista vazia
  if(Lista->prim==NULL)
  {
    Lista->prim=nova;
  }
  else
  {
    aux=Lista->ult;
    aux->prox=nova;
  }
  Lista->ult=nova;
}

ListaMusicaAntiga* proximo_ponteiro(ListaMusicaAntiga* lista)
{
  return lista->prox;
}

void desaloca_lista_musica_antiga(ListaMusicaAntiga *lista)
{
  ListaMusicaAntiga *aux=lista;
  ListaMusicaAntiga *p;

  while(aux!=NULL)
  {
    p=aux->prox;

    if(aux->musica!=NULL){free(aux->musica);}
    if(aux->cantor!=NULL){free(aux->cantor);}
    free(aux);
    aux=p;
  }
}

void gera_arquivo_musica(char *pasta,SentinelaMusica *Lista, char *nomePlaylist)
{
  char arquivo[200];

  //fazendo o caminho do arquivo
  strcpy(arquivo,pasta);
  strcat(arquivo,nomePlaylist);
  strcat(arquivo,".txt");
  //teste: ok
  //printf("%s\n",arquivo);

  //criar aquivo na pasta do usuario com a Playlist
  FILE *arq=fopen(arquivo,"w");

  //teste de abertura
  if(arq==NULL)
  {
    printf("Erro na abertura do arquivo %s\n",arquivo);
    exit(1);
  }

  //colocar as musicas
  ListaMusicaNova *aux;

  for(aux=Lista->prim;aux!=NULL;aux=aux->prox)
  {
    fprintf(arq,"%s - %s\n",nomePlaylist,aux->musica);
  }
  fclose(arq);
}

int testa_similaridade_musicas(SentinelaMusica *amigo1, SentinelaMusica *amigo2)
{
  ListaMusicaNova *aux1;
  ListaMusicaNova *aux2;
  int similaridade=0;
  //percorrer as musicas da playlist do primeiro amigo
  for(aux1=amigo1->prim;aux1!=NULL;aux1=aux1->prox)
  {
    //percorrer as músicas da playlist do segundo amigo
    for(aux2=amigo2->prim;aux2!=NULL;aux2=aux2->prox)
    {
      if(strcmp(aux1->musica,aux2->musica)==0)
      {
        //se as musicas forem iguais
        similaridade++;
      }
    }
  }
  return similaridade;
}


void libera_musica_nova(SentinelaMusica *Lista)
{
  ListaMusicaNova* aux=Lista->prim;
  ListaMusicaNova*p=NULL;

  while(aux!=NULL)
  {
    p=aux->prox;
    if(aux->musica!=NULL){free(aux->musica);}
    free(aux);
    aux=p;
  }
  free(Lista);
} 

