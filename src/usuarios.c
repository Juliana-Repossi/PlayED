#include "../include/usuarios.h"

struct usuario
{
  char *nome;
  SentinelaUsuario *amizades;
  SentinelaPlaylist *Playlist;
};

struct celulausuario
{
  CelulaUsuario *prox;
  Usuario *perfil;
};

struct sentinelausuario
{
  CelulaUsuario *prim;
  CelulaUsuario *ult;
};

SentinelaUsuario* inicializa_lista()
{
  SentinelaUsuario *lista=(SentinelaUsuario*)malloc(sizeof(SentinelaUsuario));
  
  lista->prim=NULL;
  lista->ult=NULL;

  return lista;
}

SentinelaUsuario* inicializa_usuarios_amizades(FILE *amizade)
{  
  SentinelaUsuario *lista=inicializa_lista();
  
  char string[121];
  char aux;

  CelulaUsuario *nova=NULL;

  //inicializar os usuarios
  do
  {
    //primeira linha: nomes dos usuarios com ;
    fscanf(amizade,"%[^;,\n]",string);
    //printf("%s\n",string);(testado)
    fscanf(amizade,"%c",&aux);

    //allocar na lista 

    //alocar celula da lista
    nova=(CelulaUsuario*)malloc(sizeof(CelulaUsuario));
    //alocar perfil
    nova->perfil=(Usuario*)malloc(sizeof(Usuario));
    //atribuir o usuario
    nova->perfil->nome = strdup(string);
    //inicializar a sentinela de amizade 
    nova->perfil->amizades= inicializa_lista();
    //inicializar a sentinela playlist 
    nova->perfil->Playlist=inicializa_sentinela_playlist();

    //encadear na lista(inserir no final)
    nova->prox=NULL;
    //se a lista estiver vazia
    if(lista->ult==NULL)
    {
      lista->prim=nova;
    }
    else
    {
      lista->ult->prox=nova;
    }
    lista->ult=nova;

  }while(aux!='\n');

  //inicializar as amizades

  while(!feof(amizade))
  {
    //amigo 1
    fscanf(amizade,"%[^;]",string);
    fscanf(amizade,"%c",&aux);

    //busca para conseguir os endereço do amigo1
    Usuario *amigo1=busca_usuario(lista,string);  

    //amigo 2
    fscanf(amizade,"%[^\n]",string);
    fscanf(amizade,"%c",&aux);

    //busca para conseguir os endereço do amigo2
    Usuario *amigo2=busca_usuario(lista,string); 

    //segurança: se não for encontrado o amigo
    if(amigo1==NULL || amigo2==NULL){continue;}    
    //allocar na lista amizade de ambos 
    insere_amizade(amigo1,amigo2);
    insere_amizade(amigo2,amigo1);
  }
  return lista;
}

void inicializa_usuarios_playlist(FILE *playlist,SentinelaUsuario *lista)
{
  CelulaUsuario *aux;
  char string[121];
  char c;
  
  for(aux=lista->prim;aux!=NULL;aux=aux->prox)
  {
  
    fscanf(playlist,"%[^;]",string);
    //printf("%s\n",string);
    fscanf(playlist,"%c",&c);
    //printf("%c\n",c);

    //só por segurança verificar o nome
    if(strcmp(string,aux->perfil->nome)==0)
    {
      inicializa_playlist(aux->perfil->Playlist,playlist);
    }

  }
}

void inicializa_usuarios_nova_playlist(SentinelaUsuario *Lista)
{
   CelulaUsuario *aux;

   //para englobar todos os usuarios
   for(aux=Lista->prim;aux!=NULL;aux=aux->prox)
   {
     aux->perfil->Playlist=inicializa_playlist_nova(aux->perfil->Playlist);
   }   
}

void gera_arquivo_usuarios(SentinelaUsuario *Lista)
{
   struct stat estado = {0};

   //verifica se o diretorio ainda não existe
   if(stat("Saída",&estado)==-1)
   {
      //cria um diretorio de saida
      if(mkdir("Saída",0700)!=0)
      {
        printf("Erro na criação do diretorio de Saida\n");
        exit(2);
      }
   }

   CelulaUsuario *aux;

   //criar o arquivo 
   FILE *refat=fopen("Saída/played-refatorada.txt","w");

   //testa se criou o arq
   if(refat==NULL)
   {
     printf("Erro na criação do arquivo played-refatorada.txt\n");
     exit(1);
   }

   for(aux=Lista->prim;aux!=NULL;aux=aux->prox)
   {
        
     fprintf(refat,"%s;",aux->perfil->nome);
     //chama a função da TAD playlist
     gera_arquivo_playlist(aux->perfil->Playlist, refat,aux->perfil->nome);
   }
   fclose(refat);
}

void gera_arquivo_similaridade(SentinelaUsuario *Lista)
{
 CelulaUsuario *amigo1;
 CelulaUsuario *amigo2;
 CelulaUsuario *busca;

 //cria o arquivo similaridades
 FILE *arq=fopen("Saída/similaridades.txt","w");
 //testa erro de abertura
 if(arq==NULL)
 {
   printf("Erro na criação do arquivo similaridades.txt\n");
   exit(1);
 }

  //andar na lista de usuarios
  for(amigo1=Lista->prim;amigo1!=NULL;amigo1=amigo1->prox)
  {
    //andar na lista de amigos do usuario
    for(amigo2=amigo1->perfil->amizades->prim;amigo2!=NULL;amigo2=amigo2->prox)
    {
      //for para verificar se essa amizade já não foi computada
      for(busca=Lista->prim;busca!=amigo1;busca=busca->prox)
      {
        if(strcmp(busca->perfil->nome,amigo2->perfil->nome)==0)
        {
          break;
        }
      }
      if(busca==amigo1)
      {
        //a amizade ainda não foi contada
        //coloca os nomes no arquivo
        fprintf(arq,"%s;%s;",amigo1->perfil->nome,amigo2->perfil->nome);
        testa_similaridade_playlist(amigo1->perfil->Playlist,amigo2->perfil->Playlist,arq);        
      }
    }
  }
  fclose(arq);
}

void libera_memoria(SentinelaUsuario *Lista)
{
  CelulaUsuario *usuario=Lista->prim;
  CelulaUsuario *p=NULL;
  CelulaUsuario *amizade=NULL;
  CelulaUsuario *p1=NULL;


  while(usuario!=NULL)
  {
    p=usuario->prox;
    //libera as playlists
    libera_playlist(usuario->perfil->Playlist);
    //libera as amizades(mais eficiente dentro da função do que modularizado)
    amizade=usuario->perfil->amizades->prim;
    while(amizade!=NULL)
    {
      p1=amizade->prox;
      free(amizade);
      amizade=p1;
    }
    //libera a sentinela das amizades
    free(usuario->perfil->amizades);

    //libera nome 
    if(usuario->perfil->nome!=NULL){free(usuario->perfil->nome);}
    //libera usuario
    if(usuario->perfil!=NULL){free(usuario->perfil);}
    //libero a celula
    free(usuario);
    //pego o proximo
    usuario=p;
  }
  //libero a sentinelausuario
  free(Lista);
} 


static void insere_amizade(Usuario *amigo1, Usuario *amigo2)
{
  //alocar uma celula para a amizade
  CelulaUsuario *nova=(CelulaUsuario*)malloc(sizeof(CelulaUsuario));
  //inicializa a nova apontando para o amigo2
  nova->perfil=amigo2;

  //encadear (no final)
  nova->prox=NULL;
  //se a lista estiver vazia
  if(amigo1->amizades->prim==NULL)
  {
    amigo1->amizades->prim=nova;
  }
  else
  {
    amigo1->amizades->ult->prox=nova;
  }
  amigo1->amizades->ult=nova;  
}


static Usuario* busca_usuario(SentinelaUsuario *lista, char *nome)
{
  CelulaUsuario *aux;
  for(aux=lista->prim; aux!=NULL;aux=aux->prox)
  {
    if(strcmp(aux->perfil->nome,nome)==0)
    {
      return aux->perfil;
    }
  }
  return NULL;
}