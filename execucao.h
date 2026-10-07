#ifndef EXECUCAO_H
#define EXECUCAO_H
#include "leitura.h"

string topo_pilha(Simulacao& simulacao);

void aplicar_transicao(Simulacao& simulacao, Transicao& transicao);

bool procurar_transicao(string cadeia, Automato& automato, Simulacao simulacao, Transicao& transicao);

void verificar_aceitacao(Simulacao& simulacao, Automato& automato, string& cadeia);

void imprimir_passo(Simulacao& simulacao, string& cadeia);

void ler_arquivo_cadeia(string nome, Automato& automato);

#endif