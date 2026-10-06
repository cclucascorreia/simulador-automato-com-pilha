#include <bits/stdc++.h>
#include "leitura.cpp"
using namespace std;

//------------ EXECUCAO --------------//
string topo_pilha(Simulacao& simulacao){ //funcao p retornar o topo da pilha //passa por referencia pra n criar copia desnecessaria
    if(simulacao.pilha.empty()){
        return "@";
    }
    return simulacao.pilha.back();
}

void aplicar_transicao(Simulacao& simulacao, Transicao& transicao){
    simulacao.estado_atual = transicao.estado_destino;
    if(transicao.simbolo_lido != "@"){
        simulacao.palavra += transicao.simbolo_lido;
        simulacao.posicao_cadeia++; //leu com sucesso ent avanca 1
    }
    if(transicao.simbolo_desempilhado != "@"){
        simulacao.pilha.pop_back();
    }
    if(transicao.simbolo_empilhado != "@"){
        for(auto x: transicao.simbolo_empilhado){
            simulacao.pilha.push_back(string(1, x)); //empilha simbolos (YY..)
        }
    }
}

bool procurar_transicao(string cadeia, Automato automato, Simulacao simulacao, Transicao& transicao){ //procura uma transicao aceitavel //true: achou e aplicou a transicao //false: flopou
    //dado o automato atual, procurar no vetor de transicoes por alguma que:
    //esteja em estado_atual;
    //leia cadeia[simulacao.posicao_cadeia];
    //desempilhe nada OU topo_pilha();
    //se achou, aplicar a transicao, retornando true
    //se n achou, retornar false p indicar a rejeicao da cadeia
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

void verificar_aceitacao(Simulacao& simulacao, Automato automato, string& cadeia){ //verifica se a cadeia esta completa, a pilha esta vazia e o estado atual eh estado final
    //simulacao.palavra == cadeia
    //simulacao.estado_atual tem q estar em automato.transicoes
    //simulacao.pilha deve estar vazia
    bool palavra_confere = (simulacao.palavra == cadeia);
    bool estado_confere = find(automato.estados_finais.begin(), automato.estados_finais.end(), simulacao.estado_atual) != automato.estados_finais.end();
    //find retorna um iterador caso encontre o argumento 3 entre begin e end
    bool pilha_confere = simulacao.pilha.empty();
    bool aceita = (palavra_confere && estado_confere && pilha_confere);
    aceita ? cout << "ACEITA\n" : cout << "REJEITADA\n";
}

void imprimir_passo(Simulacao& simulacao, string& cadeia){ //tem q ser chamada antes e dps da execucao do automato
    cout << "fita: ";
    cout << simulacao.palavra;
    cout << "[" << simulacao.estado_atual << "]";
    cout << cadeia.substr(simulacao.posicao_cadeia); //imprime apenas a parte da cadeia q ainda nao foi lida
    cout << " pilha: ";
    for(int i = simulacao.pilha.size() -1; i >= 0; i--){ //ja q eh uma pilha, imprime de tras pra frente
        cout << simulacao.pilha[i];
    }
    cout << endl;
}

void ler_arquivo_cadeia(string nome, Automato& automato){ //funcao p ler a entrada a ser testada, podendo ser varias linhas
    string cadeia;
    ifstream arquivo(nome);
        if(!arquivo.is_open()){
        cout << "ERRO: o arquivo nao foi aberto." << endl;
        return;
    }
    while(getline(arquivo, cadeia)){
        Simulacao simulacao;
        Transicao transicao;
        imprimir_passo(simulacao, cadeia);
        while(true){ //roda infinito ate n ter transicoes aceitaveis
            if(!(procurar_transicao(cadeia, automato, simulacao, transicao))){
                break;
            } else {
                aplicar_transicao(simulacao, transicao);
                imprimir_passo(simulacao, cadeia);
            }
        }
        verificar_aceitacao(simulacao, automato, cadeia); // printa a resposta pra cada cadeia
    }
}

//------------ MAIN --------------//
int main(){
    string nome;
    cout << "Digite o nome do arquivo .txt com as informacoes do automato: "; //tem q digitar a extensao .txt no fim
    cin >> nome;

    Automato automato;
    ler_arquivo_automato(nome, automato);
 
    cout << "Digite o nome do arquivo .txt com as cadeias a serem testadas: ";
    string nomecadeia; cin>> nomecadeia;
    ler_arquivo_cadeia(nomecadeia, automato);

    return 0;
}
