#ifndef USUARIOS_H
#define USUARIOS_H

#include "playlist.h"

typedef struct usuario Usuario;

typedef struct celulausuario CelulaUsuario;

typedef struct sentinelausuario SentinelaUsuario;


/**
* @brief Inicializa uma SentinelaUsuario;
* @return ponteiro de alocação da estrutura;
**/
SentinelaUsuario* inicializa_lista();

/**
* @brief aloca a estrutura da played inicializa os usuarios e suas amizades em uma lista simplismente encadeada com sentinela a partir do arquivo amizades;
* @param amizade arquivo de dados válido;
* @return Sentinela da estrutura played válida;
**/
SentinelaUsuario* inicializa_usuarios_amizades(FILE *amizade);

/**
* @brief Inicializa as playlists dos usuarios cadastrados descritas no arquivo passado,  separadas por estilos musicais, e suas musicas dispostas em arquivos de mesmo nome da playlist
* @param playlist - ponteiro válido para o arquivo playlists.txt
* @param lista - ponteiro para lista alocado com usuarios definidos 
**/
void inicializa_usuarios_playlist(FILE *playlist,SentinelaUsuario *lista);

/**
* @brief Troca a forma de armazenamento/organização das Playlists do sistema "Lista" (de separados por estilos musicais, para separados por cantor/banda)
* @param Lista - ponteiro válido com as informações de musicas, playlists e usuarios devidamente alocados;
**/
void inicializa_usuarios_nova_playlist(SentinelaUsuario *Lista);

/**
* @brief Cria um diretorio "Saida" com um arquivo playlist-refatorada.txt com o resumo das playlists por usuarios no programa. E diretorios individuais para cada usuario com suas playlists em arquivos;
* @param Lista - ponteiro para a estrutura da Played válido;
@return retorna mensagem de erro caso ocorra falha na criação do arquivo ou do diretorio
**/
void gera_arquivo_usuarios(SentinelaUsuario *Lista);

/**
@brief Cria o arquivo, computa as similaridades entre os amigos e registra no arquivo criado
@param Lista - ponteiro valido da estrutura da played
**/
void gera_arquivo_similaridade(SentinelaUsuario *Lista);

/**
* @brief Libera toda a memória da estrutura alocada para armazenar os dados da Played
* @param Lista - ponteiro para a estrutura Played
**/
void libera_memoria(SentinelaUsuario *Lista);

/**
* @brief Coloca no final da lista de amizades do amigo 1 o amigo 2;
* @param amigo1 o endereço do amigo1;
* @param amigo2 o endereço do amigo 2;
**/
static void insere_amizade(Usuario *amigo1, Usuario *amigo2);

/**
* @brief Busca na lista pelo usuario de nome "nome";
* @param lista lista válida;
* @param nome nome do usuario que será a chave de busca;
* @return retorna NULL caso não encontrado usuario com o nome passado ou o endereço do perfil do usuario de nome especificado;
**/
static Usuario* busca_usuario(SentinelaUsuario *lista, char *nome);

#endif