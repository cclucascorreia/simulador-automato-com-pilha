#ifndef EXECUCAO_H
#define EXECUCAO_H
#include "leitura.h"

/**
 * Finalidade: Retorna o símbolo no topo da pilha da simulação.
 * Recebe: simulacao Referência para a simulação em andamento.
 * Retorna: O símbolo no topo da pilha, ou "@" se a pilha estiver vazia (curinga, indica ausência de topo).
 */
string topo_pilha(Simulacao& simulacao);

/**
 * Finalidade: Aplica uma transição à simulação, atualizando estado, fita lida e pilha.
 * Recebe: simulacao Referência para a simulação a ser atualizada, transicao Transição a ser aplicada.
 */
void aplicar_transicao(Simulacao& simulacao, Transicao& transicao);

/**
 * Finalidade: Procura, no conjunto de transições do autômato, uma transição válida para a configuração atual da simulação.
 * Parâmetros: cadeia Cadeia de entrada sendo processada, automato Referência para o autômato carregado, contendo as transições disponíveis.
 * simulacao Estado atual da simulação (estado, pilha, posição na cadeia), transicao Parâmetro de saída: recebe a transição encontrada, caso exista.
 * Retorna: true se encontrou uma transição válida; false caso contrário.
 */
bool procurar_transicao(string cadeia, Automato& automato, Simulacao simulacao, Transicao& transicao);

/**
 * Finalidade: Verifica se a cadeia processada foi aceita pelo autômato e imprime o resultado.
 * Parametros: simulacao Referência para a simulação já finalizada (sem mais transições possíveis), automato Referência para o autômato, usada para checar
 * o conjunto de estados finais, automato Referência para o autômato, usada para checar o conjunto de estados finais, cadeia Referência para a cadeia original que foi testada.
 * que foi testada.
 */
void verificar_aceitacao(Simulacao& simulacao, Automato& automato, string& cadeia);

/**
 * Finalidade: Imprime uma linha do passo a passo (trace) do processamento da cadeia.
 * Parametros: simulacao Referência para a simulação no momento atual do processamento, cadeia Referência para a cadeia original sendo processada.
 */
void imprimir_passo(Simulacao& simulacao, string& cadeia);

/**
 * Finalidade: Lê um arquivo contendo cadeias de entrada (uma por linha) e simula o autômato para cada uma.
 * Parametros: nome Nome (ou caminho) do arquivo de texto contendo as cadeias a testar, automato Referência para o autômato já carregado, usado para simular cada cadeia.
 */
void ler_arquivo_cadeia(string nome, Automato& automato);

#endif