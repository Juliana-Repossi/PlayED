#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "musica.h"

//para a criação do diretorio
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct sentinelaplaylist SentinelaPlaylist;

typedef struct celulaplaylist CelulaPlaylist;

/**
* @brief Inicializa uma Sentinela Playlist 
* @return ponteiro com o endereço da alocação
**/
SentinelaPlaylist* inicializa_sentinela_playlist();

/**
* @brief inicializa a partir do arquivo  a playlist e suas musicas de um usuario passado o ponteiro de sua playlist;
* @param playlist - ponteiro válido para inicializar a lista de playlist
* @param lista - ponteiro para lista alocado com usuarios definidos 
**/
void inicializa_playlist(SentinelaPlaylist *Playlist, FILE *arquivo);

/**
* @brief Aloca o novo tipo de armazenamento de playlist (dividido por cantor/banda), copia dados do antigo armazenamento(por gênero) e libera o ultimo;
* @param Lista - ponteiro válido para a lista de playlists por gênero do usuario
@return Ponteiro de alocação do novo armazenamento;
**/
SentinelaPlaylist* inicializa_playlist_nova(SentinelaPlaylist *Lista);

/**
* @brief Desaloca todo o armazenamento da playlist antiga
* @param lista - ponteiro para lista 
**/
void desaloca_playlist(SentinelaPlaylist *lista);

/**
* @brief Insere as playlist da lista (do usuario) no arquivo. Cria os diretorios individuais dos usuarios, cria arquivos das playlists e imprime suas musicas dentro deles
* @param Lista - de playlists de um usuario
* @param arq - ponteiro para o arquivo válido 
* @param nome - nome do usuario cadastrado na played
* @return retorna mensagem de erro na criação dos diretorios dos usuarios caso haja falha na criação
**/
void gera_arquivo_playlist(SentinelaPlaylist *Lista, FILE *arq, char *nome);

/**
@brief Faz o teste entre quais são as playlists iguais entre os usuários e chama a função de comparar as musicas iguais, ao final coloca a quantidades de musicas iguais de um mesmo cantor/ banda no arq
@param amigo1 - ponteiro válido para a playlist de um amigo;
@param amigo2 - ponteiro válido para a playlist do 2º amigo;
@param arq - ponteiro de arquivo válido que permite escrita;
**/
void testa_similaridade_playlist(SentinelaPlaylist *amigo1,  SentinelaPlaylist *amigo2, FILE *arq);

/**
* @brief Libera a Lista (com sentinela) de Playlists do usuario
* @param Lista - ponteiro para a lista de Playlists válido
**/
void libera_playlist(SentinelaPlaylist *Lista);

/**
* @brief Aloca, encadeia e inicializa uma playlist com o nome do cantor ou banda;
* @param cantor - string com o nome do cantor/banda;
* @param Ponteiro para a lista de Playlists por cantor/banda;
* @return o endereço da nova celula alocada (por mais que já esteja encadeada);
**/
static CelulaPlaylist* inicializa_nova_celula(SentinelaPlaylist *Playlist, char *nome);

/**
* @brief Busca na lista pela celula com o cantor/banda desejada;
* @param cantor - string com o nome do cantor;
* @param Ponteiro para a lista de Playlists por cantor/banda;
* @return Retorna o endereço da celula procurada ou NULL caso não encontrado ou lista vazia;
**/
static CelulaPlaylist* Busca_Playlist(char *cantor,CelulaPlaylist *Lista);

#endif