#ifndef LEITURA_H
#define LEITURA_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * @brief Representa uma transição do autômato com pilha, no formato (qi, σ, X) = (qj, β).
 */
struct Transicao{
    string estado_origem;        ///< Estado atual (qi) de onde a transição parte.
    string estado_destino;       ///< Estado (qj) para onde a transição leva.
    string simbolo_desempilhado; ///< Símbolo (X) exigido no topo da pilha para a transição ser válida. "@" indica que não há exigência.
    string simbolo_lido;         ///< Símbolo (σ) exigido na fita para a transição ser válida. "@" indica transição vazia (não consome fita).
    string simbolo_empilhado;    ///< Cadeia (β) que substitui o topo da pilha. "@" indica que nada é empilhado (apenas remove o topo).
};

/**
 * @brief Representa a especificação completa de um autômato com pilha determinístico.
 */
struct Automato{
    int n;                              ///< Número total de estados do autômato.
    vector<string> estados_finais;      ///< Conjunto de estados finais (F).
    vector<string> alfabeto_fita;       ///< Alfabeto de entrada (Σ): símbolos válidos na fita.
    vector<string> alfabeto_pilha;      ///< Alfabeto de pilha (Γ): símbolos válidos para empilhar.
    vector<Transicao> transicoes;       ///< Conjunto de transições (δ) do autômato.
};

/**
 * @brief Representa o estado de uma simulação em andamento, enquanto uma cadeia é processada.
 */
struct Simulacao{
    string estado_atual = "q0";  ///< Estado atual do autômato durante a simulação (sempre inicia em q0).
    string palavra = "";         ///< Parte da cadeia já consumida até o momento.
    int posicao_cadeia = 0;      ///< Índice da próxima posição a ser lida na cadeia de entrada.
    vector<string> pilha;        ///< Pilha atual da simulação (topo = último elemento do vetor). Inicia vazia.
};

/**
 * @brief Extrai uma lista de itens de uma linha no formato "rotulo = {item1,item2,...}".
 * @param linha Linha do arquivo de especificação contendo o conteúdo entre chaves.
 * @return Vetor de strings com cada item extraído, sem as chaves e sem o rótulo.
 */
vector<string> extrair_conteudo(string linha);

/**
 * @brief Interpreta uma linha de transição no formato "(qi,σ,X) = (qj,β)" e monta a struct correspondente.
 * @param linha Linha do arquivo de especificação contendo uma transição.
 * @return Struct Transicao preenchida com os 5 campos extraídos da linha.
 */
Transicao extrair_transicao(string linha);

/**
 * @brief Lê o arquivo de especificação do autômato e preenche a struct Automato.
 * 
 * Lê as 4 primeiras linhas (quantidade de estados, estados finais, alfabeto da fita
 * e alfabeto da pilha) e, a partir da 5ª linha, interpreta cada linha como uma transição.
 * 
 * @param nome Nome (ou caminho) do arquivo de texto com a especificação do autômato.
 * @param automato Referência para a struct Automato que será preenchida pela função.
 */
void ler_arquivo_automato(string nome, Automato& automato);

#endif