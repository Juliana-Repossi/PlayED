#include "../include/playlist.h"

struct sentinelaplaylist
{
CelulaPlaylist *prim;
CelulaPlaylist *ult;
int quant;
};

struct celulaplaylist
{
char *nome;
void *listaMusica;
CelulaPlaylist *prox;
};


SentinelaPlaylist* inicializa_sentinela_playlist()
{
  SentinelaPlaylist *Playlist=(SentinelaPlaylist*)malloc(sizeof(SentinelaPlaylist));

  Playlist->prim=NULL;
  Playlist->ult=NULL;
  Playlist->quant=0;

  return Playlist;
}

void inicializa_playlist(SentinelaPlaylist *Playlist, FILE *arquivo)
{
  int tam;
  char c;
  char string[121];

   //lendo a quantidade de playlist
   fscanf(arquivo,"%d",&tam);
   //printf("%d\n",tam);
   fscanf(arquivo,"%c",&c);
   //printf("%c\n",c);
   
  //pegar todas as playlists
  for(int i=0;i<tam;i++)
  {
    CelulaPlaylist* nova=(CelulaPlaylist*)malloc(sizeof(CelulaPlaylist));

    fscanf(arquivo,"%[^;,\n]",string);
    //printf("%s\n",string);
    fscanf(arquivo,"%c",&c);
    //printf("%c\n",c);
        
    
    nova->nome = strdup(string);
    nova->listaMusica= cadastrar_musicas(nova->nome);

    //encadear no armazenamento tipo 1 (no final);
    nova->prox=NULL;
    //se lista vazia
    if(Playlist->prim==NULL)
    {
      Playlist->prim=nova;
    }
    else
    {
      Playlist->ult->prox=nova;
    }
    Playlist->ult=nova;
  }
}

SentinelaPlaylist* inicializa_playlist_nova(SentinelaPlaylist *Lista)
{ 
  //aloca sentinela de playlists
  SentinelaPlaylist *NewPlay=inicializa_sentinela_playlist();
  
  //caminhar nos estilos musicais 
  for(CelulaPlaylist *aux=Lista->prim;aux!=NULL;aux=aux->prox)
  {
    ListaMusicaAntiga *interno=aux->listaMusica;
    //caminhar nas listas de musicas
    // enquanto a lista não acabar
    while((retorna_ponteiro_musica(interno))==0)
    {
      char *cantor=retorna_nome_cantor(interno);
      
      CelulaPlaylist *endereco = Busca_Playlist(cantor,NewPlay->prim);

      if (endereco==NULL)
      {
        //ainda não há a playlist desse cantor
        endereco=inicializa_nova_celula(NewPlay,cantor);       
      }

      //alocar ela no endereço (playlist do seu cantor ou banda)
      insere_musica(endereco->listaMusica,interno);

      //vai para a proxima musica da playlist
      interno=proximo_ponteiro(interno);    
    }    
  }

  //desalocar antiga playlist
  desaloca_playlist(Lista);

  //retorna o endereço do novo armazenamento no lugar
  return NewPlay;
}


void desaloca_playlist(SentinelaPlaylist *lista)
{
  CelulaPlaylist *aux=lista->prim;
  CelulaPlaylist *p=NULL;

  while(aux!=NULL)
  {
    p=aux->prox;
  
    desaloca_lista_musica_antiga(aux->listaMusica);

    if(aux->nome!=NULL){free(aux->nome);}
    if(aux!=NULL){free(aux);}
    aux=p;
  }
  if(lista!=NULL){free(lista);}
}

void gera_arquivo_playlist(SentinelaPlaylist *Lista, FILE *arq, char *nome)
{
  char pasta[150]="Saída/";

  //nome completo da pasta
  strcat(pasta,nome);

  struct stat estado = {0};

  //verifica se o diretorio ainda não existe
  if(stat(pasta,&estado)==-1)
   {
     //cria um diretorio de do usuario
     if(mkdir(pasta,0700)!=0)
     {
       printf("Erro na criação do diretorio de %s\n",nome);
       exit(2);
     }
   }

  CelulaPlaylist *aux;

  //para fazer o caminho para a criação de arquivos
  strcat(pasta,"/");

  //quantidade de playlist do usuario no arquivo
  fprintf(arq,"%d",Lista->quant);

  for(aux=Lista->prim;aux!=NULL;aux=aux->prox)
  {
    fputc(';',arq);
    fprintf(arq,"%s.txt",aux->nome);
    gera_arquivo_musica(pasta,aux->listaMusica,aux->nome);
  }
  fputc('\n',arq);
}

void testa_similaridade_playlist(SentinelaPlaylist *amigo1,  SentinelaPlaylist *amigo2, FILE *arq)
{
  CelulaPlaylist *aux1;
  CelulaPlaylist *aux2;
  int similaridades=0;

  //caminhar na playlist de um amigo
  for(aux1=amigo1->prim;aux1!=NULL;aux1=aux1->prox)
  {
    //caminhar na playlist do outro amigo
    for(aux2=amigo2->prim;aux2!=NULL;aux2=aux2->prox)
    {
      //se a playlist for igual
      if(strcmp(aux1->nome,aux2->nome)==0)
      {
        
        similaridades=similaridades + testa_similaridade_musicas(aux1->listaMusica,aux2->listaMusica);
        break;
      }
    }
  }
  fprintf(arq,"%d\n",similaridades);
}

void libera_playlist(SentinelaPlaylist *Lista)
{
  CelulaPlaylist *Playlist=Lista->prim;
  CelulaPlaylist *p=NULL;

  while(Playlist!=NULL)
  {
    p=Playlist->prox;
    libera_musica_nova(Playlist->listaMusica);
    if(Playlist->nome!=NULL){free(Playlist->nome);}
    free(Playlist);

    Playlist=p;
  }
  //liberar a sentinela
  free(Lista);
}

static CelulaPlaylist* inicializa_nova_celula(SentinelaPlaylist *Playlist, char *nome)
{
  //aloca
  CelulaPlaylist *nova=(CelulaPlaylist*)malloc(sizeof(CelulaPlaylist));
  //inicializa
  nova->nome=strdup(nome);
  nova->listaMusica=inicializa_sentinela_musica();
  //encadeia no final:
  nova->prox=NULL;
  //testa se é vazia
  if(Playlist->prim==NULL)
  {
    Playlist->prim=nova;
  }
  else
  {
    Playlist->ult->prox=nova;
  }
  Playlist->ult=nova;

  //incrementa uma playlist na quant do usuario;
  Playlist->quant=Playlist->quant+1;
  //retornar o endereço de onde foi alocada para inserir a musica;
  return nova;
}

static CelulaPlaylist* Busca_Playlist(char *cantor,CelulaPlaylist *Lista)
{ 
  CelulaPlaylist *aux;

  for(aux=Lista;aux!=NULL;aux=aux->prox)
  {
    if(strcmp(aux->nome,cantor)==0)
    {
      //já tem playlist com esse cantor ou banda
      //retorna o endereço da celulaplaylist
      return aux;
    }
  }
  return NULL;
}
