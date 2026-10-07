#include "execucao.h"

string topo_pilha(Simulacao& simulacao){
    if(simulacao.pilha.empty()){
        return "@";
    }
    return simulacao.pilha.back();
}

void aplicar_transicao(Simulacao& simulacao, Transicao& transicao){
    simulacao.estado_atual = transicao.estado_destino;
    if(transicao.simbolo_lido != "@"){
        simulacao.palavra += transicao.simbolo_lido;
        simulacao.posicao_cadeia++;
    }
    if(transicao.simbolo_desempilhado != "@"){
        simulacao.pilha.pop_back();
    }
    if(transicao.simbolo_empilhado != "@"){
        for(auto x: transicao.simbolo_empilhado){
            simulacao.pilha.push_back(string(1, x));
        }
    }
}

bool procurar_transicao(string cadeia, Automato& automato, Simulacao simulacao, Transicao& transicao){
    string letra_atual = (simulacao.posicao_cadeia < cadeia.size()) ? string(1, cadeia[simulacao.posicao_cadeia]) : "@";
    string topo = topo_pilha(simulacao);
    for(auto x : automato.transicoes){
        bool estado_confere = (x.estado_origem == simulacao.estado_atual);
        bool letra_confere = (x.simbolo_lido == letra_atual || x.simbolo_lido == "@");
        bool topo_confere = (x.simbolo_desempilhado == topo || x.simbolo_desempilhado == "@");
        if(estado_confere && letra_confere && topo_confere){
            transicao = x;
            return true;
        }
    }
    return false;
}

void verificar_aceitacao(Simulacao& simulacao, Automato& automato, string& cadeia){
    bool palavra_confere = (simulacao.palavra == cadeia);
    bool estado_confere = find(automato.estados_finais.begin(), automato.estados_finais.end(), simulacao.estado_atual) != automato.estados_finais.end();
    bool pilha_confere = simulacao.pilha.empty();
    bool aceita = (palavra_confere && estado_confere && pilha_confere);
    aceita ? cout << "ACEITA\n" : cout << "REJEITADA\n";
}

void imprimir_passo(Simulacao& simulacao, string& cadeia){
    cout << "fita: ";
    cout << simulacao.palavra;
    cout << "[" << simulacao.estado_atual << "]";
    cout << cadeia.substr(simulacao.posicao_cadeia);
    cout << " pilha: ";
    for(int i = simulacao.pilha.size() -1; i >= 0; i--){
        cout << simulacao.pilha[i];
    }
    cout << endl;
}

void ler_arquivo_cadeia(string nome, Automato& automato){
    string cadeia;
    ifstream arquivo(nome);
    while(!arquivo.is_open()){
        cout << "ERRO: o arquivo nao foi aberto." << endl;
        cout << "Digite o nome do arquivo .txt com as cadeias a serem testadas: ";
        cin>> nome;
        arquivo.open(nome);
    }
    while(getline(arquivo, cadeia)){
        Simulacao simulacao;
        Transicao transicao;
        imprimir_passo(simulacao, cadeia);
        while(true){
            if(!(procurar_transicao(cadeia, automato, simulacao, transicao))){
                break;
            } else {
                aplicar_transicao(simulacao, transicao);
                imprimir_passo(simulacao, cadeia);
            }
        }
        verificar_aceitacao(simulacao, automato, cadeia);
    }
}
