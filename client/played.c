#include "../include/usuarios.h"

int main() {
 
 /*abertura do arquivo amizade*/
 FILE *amizade=fopen("data/amizade.txt","r");
 //teste na main para agilizar
 if(amizade==NULL)
 {
   printf("Falha na abertura do arquivo amizade.txt\n");
   exit(1);
 }

 //Inicializa e preenche a lista de usuarios e as amizades
 SentinelaUsuario *ListaPessoas=inicializa_usuarios_amizades(amizade);

 //fecha o arquivo
 fclose(amizade);

 //abertura do arquivo playlist
 FILE *playlist=fopen("data/playlists.txt","r");
 //teste na main para agilizar
 if(playlist==NULL)
 {
   printf("Falha na abertura do arquivo playlists.txt\n");
   exit(1);
 }

 //inicializa as playlists dos usuarios cadastrados
 inicializa_usuarios_playlist(playlist,ListaPessoas);

 fclose(playlist);

 //Começou a Brincadeira: Troca a forma de organização antiga das playlists para o das Novas Playlists
 inicializa_usuarios_nova_playlist(ListaPessoas);
 
 //arquivos de saida:

 //gera a playlist refatorada e as pastas com as playlists de cada usuario
 gera_arquivo_usuarios(ListaPessoas);

 //gera o arquivo de similaridade 
 gera_arquivo_similaridade(ListaPessoas);
 
 //libera toda a memoria 
 libera_memoria(ListaPessoas);

 return 0;
}