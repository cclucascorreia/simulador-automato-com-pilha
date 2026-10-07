#ifndef LEITURA_H
#define LEITURA_H
#include <bits/stdc++.h>
using namespace std;

struct Transicao{
    string estado_origem;
    string estado_destino;
    string simbolo_desempilhado; //deve ter isso no topo da pilha pra poder usar a transicao
    string simbolo_lido; //simbolo q vai ser adicionado a palavra resposta
    string simbolo_empilhado; //simbolo q vai ser empilhado/substituir no topo da pilha
};

struct Automato{
    int n; //numero de estados
    vector<string> estados_finais;
    vector<string> alfabeto_fita; //letras q podem ser usadas na fita
    vector<string> alfabeto_pilha; //letras q podem ser empilhadas
    vector<Transicao> transicoes; //armazena structs de transicao
};

struct Simulacao{ //com base no Automato lido, vai guardar essas informacoes durante a leitura de uma cadeia
    string estado_atual = "q0";
    string palavra = ""; //palavra atual, o objetivo eh deixar igual a cadeia
    int posicao_cadeia=0; //guarda o indice atual em q estamos na cadeia
    vector<string> pilha; //pilha atual, inicia vazia
};

vector<string> extrair_conteudo(string linha);
Transicao extrair_transicao(string linha);
void ler_arquivo_automato(string nome, Automato& automato);

#endif