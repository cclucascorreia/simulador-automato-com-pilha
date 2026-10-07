#ifndef EXECUCAO_H
#define EXECUCAO_H
#include "leitura.h"

/**
 * @brief Retorna o símbolo no topo da pilha da simulação.
 * @param simulacao Referência para a simulação em andamento.
 * @return O símbolo no topo da pilha, ou "@" se a pilha estiver vazia (curinga, indica ausência de topo).
 */
string topo_pilha(Simulacao& simulacao);

/**
 * @brief Aplica uma transição à simulação, atualizando estado, fita lida e pilha.
 * 
 * Atualiza o estado atual para o estado de destino da transição. Se a transição
 * consome um símbolo da fita (diferente de "@"), avança a posição da cadeia e
 * atualiza a palavra lida. Se a transição exige um símbolo no topo da pilha
 * (diferente de "@"), remove esse símbolo. Em seguida, empilha cada caractere
 * da cadeia de substituição (β), caso ela seja diferente de "@".
 * 
 * @param simulacao Referência para a simulação a ser atualizada.
 * @param transicao Transição a ser aplicada.
 */
void aplicar_transicao(Simulacao& simulacao, Transicao& transicao);

/**
 * @brief Procura, no conjunto de transições do autômato, uma transição válida para a configuração atual da simulação.
 * 
 * Uma transição é considerada válida se o estado de origem bate com o estado atual, e
 * se tanto o símbolo lido quanto o símbolo exigido no topo da pilha batem com a situação
 * atual ou são o curinga "@" (que indica "não lê nada"/"não exige nada", respectivamente).
 * 
 * @param cadeia Cadeia de entrada sendo processada.
 * @param automato Referência para o autômato carregado, contendo as transições disponíveis.
 * @param simulacao Estado atual da simulação (estado, pilha, posição na cadeia).
 * @param transicao Parâmetro de saída: recebe a transição encontrada, caso exista.
 * @return true se encontrou uma transição válida; false caso contrário.
 */
bool procurar_transicao(string cadeia, Automato& automato, Simulacao simulacao, Transicao& transicao);

/**
 * @brief Verifica se a cadeia processada foi aceita pelo autômato e imprime o resultado.
 * 
 * A cadeia é aceita se, simultaneamente: (1) toda a cadeia foi lida (a palavra
 * processada é igual à cadeia original), (2) o estado atual da simulação é um
 * estado final do autômato, e (3) a pilha está vazia ao final do processamento.
 * Imprime "ACEITA" ou "REJEITADA" no console.
 * 
 * @param simulacao Referência para a simulação já finalizada (sem mais transições possíveis).
 * @param automato Referência para o autômato, usada para checar o conjunto de estados finais.
 * @param cadeia Referência para a cadeia original que foi testada.
 */
void verificar_aceitacao(Simulacao& simulacao, Automato& automato, string& cadeia);

/**
 * @brief Imprime uma linha do passo a passo (trace) do processamento da cadeia.
 * 
 * Mostra, no formato "fita: <lido>[<estado>]<restante> pilha: <conteudo>", a parte
 * já lida da cadeia, o estado atual entre colchetes, a parte da cadeia que ainda
 * falta ler, e o conteúdo atual da pilha (impresso do topo para o fundo).
 * 
 * @param simulacao Referência para a simulação no momento atual do processamento.
 * @param cadeia Referência para a cadeia original sendo processada.
 */
void imprimir_passo(Simulacao& simulacao, string& cadeia);

/**
 * @brief Lê um arquivo contendo cadeias de entrada (uma por linha) e simula o autômato para cada uma.
 * 
 * Para cada cadeia do arquivo, inicializa uma nova simulação, imprime a configuração
 * inicial, e aplica transições repetidamente (imprimindo o trace a cada passo) até
 * não haver mais nenhuma transição válida. Ao final, verifica e imprime se a cadeia
 * foi aceita ou rejeitada.
 * 
 * @param nome Nome (ou caminho) do arquivo de texto contendo as cadeias a testar.
 * @param automato Referência para o autômato já carregado, usado para simular cada cadeia.
 */
void ler_arquivo_cadeia(string nome, Automato& automato);

#endif