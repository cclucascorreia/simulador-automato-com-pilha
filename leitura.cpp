#include "leitura.h"

vector<string> extrair_conteudo(string linha){
    vector<string> conteudo;
    int pos_inicio = linha.find('{');
    int pos_final = linha.find('}');
    string linha_util = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1);

    stringstream ss(linha_util);
    string parte;
    while(getline(ss, parte, ',')){
        conteudo.push_back(parte);
    }
    return conteudo;
}

Transicao extrair_transicao(string linha){
    Transicao atual;
        int pos_inicio = linha.find('(');
        int pos_final = linha.find(',');
        atual.estado_origem = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1);

        pos_inicio = pos_final;
        pos_final = linha.find(',', pos_final + 1);
        atual.simbolo_lido = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1);

        pos_inicio = pos_final;
        pos_final = linha.find(')', pos_final + 1);
        atual.simbolo_desempilhado = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1);

        pos_inicio = linha.find('(', pos_final + 1);
        pos_final = linha.find(',', pos_inicio + 1);
        atual.estado_destino = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1);

        pos_inicio = pos_final;
        pos_final = linha.find(')', pos_inicio + 1);
        atual.simbolo_empilhado = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1);
    return atual;
}

void ler_arquivo_automato(string nome, Automato& automato){
    ifstream arquivo(nome);
    while(!arquivo.is_open()){
        cout << "ERRO: o arquivo nao foi aberto." << endl;
        cout << "Digite o nome do arquivo .txt com as informacoes do automato: ";
        cin >> nome;
        ler_arquivo_automato(nome, automato);
        return;
    }
    string linha;
    int l=1;
    while(getline(arquivo, linha)){
        if(l==1){
            int pos = linha.find('=');
            automato.n = stoi(linha.substr(pos+1));
        } else if (l==2){
            automato.estados_finais = extrair_conteudo(linha);
        } else if (l==3){
            automato.alfabeto_fita = extrair_conteudo(linha);
        } else if (l==4){
            automato.alfabeto_pilha = extrair_conteudo(linha);
        } else {
            automato.transicoes.push_back(extrair_transicao(linha));
        }
        l++;
    }
}
