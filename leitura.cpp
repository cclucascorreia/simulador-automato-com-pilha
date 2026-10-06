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

vector<string> extrair_conteudo(string linha){ //le cada linha do arquivo do automato e atualiza ele com suas informacoes
    vector<string> conteudo; //vetor resposta
    int pos_inicio = linha.find('{');
    int pos_final = linha.find('}');
    string linha_util = linha.substr(pos_inicio + 1, pos_final - pos_inicio - 1); //cria uma substring so com oq ta entre { } da string, excluindo eles

    stringstream ss(linha_util); //comeca a ler uma string tipo ifstream
    string parte;
    while(getline(ss, parte, ',')){ //le cada parte da string, dividindo pelas virgulas, e poe no vetor resposta
        conteudo.push_back(parte);
    }
    return conteudo;
}

Transicao extrair_transicao(string linha){ //le do arquivo do automato as transicoes 
    Transicao atual;
        // entrada no formato (q0,@,@) = (q1,$)
        // (inicial,simbolo lido, simbolo desempilhado) = (estado final, simbolo empilhado)
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
    ifstream arquivo(nome); //abre o arquivo
    if(!arquivo.is_open()){
        cout << "ERRO: o arquivo nao foi aberto." << endl;
        return;
    }
    string linha;
    int l=1; //conta qual linha vai ser lida
    while(getline(arquivo, linha)){ //loop ate parar de ler
        if(l==1){
            int pos = linha.find('='); //pos armazena a posicao do =
            automato.n = stoi(linha.substr(pos+1)); //stoi transforma uma string em int; faz isso com a substring q ta depois do =
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
