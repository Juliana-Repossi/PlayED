#ifndef MUSICA_H
#define MUSICA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sentinelamusica SentinelaMusica;

typedef struct litsamusicaantiga ListaMusicaAntiga; 

typedef struct listamusicanova ListaMusicaNova; 

typedef struct celulamusica CelulaMusica; 

/**
* @brief Aloca uma estrutura do tipo Sentinela Musica
* @return ponteiro da estrutura alocada;
**/
SentinelaMusica* inicializa_sentinela_musica();

/**
* @brief Cria uma lista com as musicas do arquivo de nome passado
* @param nome do arquivo que contem as musicas
* @return Retorna mensagem de erro caso o arquivo não seja aberto com sucesso ou um ponteiro para o inicio da lista de musicas;
**/
ListaMusicaAntiga* cadastrar_musicas(char *nome);

/**
* @brief Testa se um ponteiro do tipo ListaMusicaAntiga é NULL
* @param Ponteiro do tipo Lista Musica Antiga
* @return 1 se for NULL ou 0 caso contrário
**/
int retorna_ponteiro_musica(ListaMusicaAntiga* Lista);

/**
* @brief Retorna a string - nome do cantor/banda - alocada na estrutura ListaMusicaAntiga
* @param ponteiro de lista válido
* @return string com o nome do cantor/banda
**/
char* retorna_nome_cantor(ListaMusicaAntiga *Lista);

/**
* @brief Aloca a Lista se não existir e insere uma musica na mesma;
* @param Lista - Ponteiro para lista, sendo ela alocada ou não;
* @param dados -  celula válida com os dados do antigo armazenamento da musica;
**/
void insere_musica(SentinelaMusica *Lista,ListaMusicaAntiga *dados);

/**
* @brief Retorna a proxima musica da lista;
* @param Lista Válida
* @return ponteiro para a proxima posição da lista;
**/
ListaMusicaAntiga* proximo_ponteiro(ListaMusicaAntiga* lista);

/**
* @brief Desaloca a lista de musica armazenada por gênero musical
* @param lista - Ponteiro para lista de musica;
**/
void desaloca_lista_musica_antiga(ListaMusicaAntiga *lista);

/**
* @brief Insere as musicas da Playlist no arquivo da mesma que encontra-se no caminho de arquivos passado 
* @param pasta - endereço do arquivo da Playlist 
* @param Lista - de musicas válida da Playlist
* @param  nomePlaylist - nome da Playlist 
* @return retorna mensagem de erro de abertura de arquivo caso ocorra
**/
void gera_arquivo_musica(char *pasta,SentinelaMusica *Lista, char *nomePlaylist);

/**
@brief Retorna o número de musicas em comum entre duas playlists
@param amigo1 - sentinela válida da lista de musicas da playlist 1
@param amigo2 - sentinela válida da lista de musicas da playlist 2
@return a quantidade de musicas em comum entre as duas listas 
**/
int testa_similaridade_musicas(SentinelaMusica *amigo1, SentinelaMusica *amigo2);

/**
* @brief Desaloca uma Lista de musica nova com sentinela
* @param Lista - ponteiro para lista válido
**/
void libera_musica_nova(SentinelaMusica *Lista);

#endif