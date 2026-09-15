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
    string estado_inicial;
    vector<string> estados_finais;
    vector<string> alfabeto_fita; //letras q podem ser usadas na fita
    vector<string> alfabeto_pilha; //letras q podem ser empilhadas
    vector<Transicao> transicoes; //armazena structs de transicao
    string palavra; //palavra sendo lida atualmente, objetivo eh ficar igual a cadeia
    int posicao_cadeia=0; //marca a posicao atual na cadeia sendo lida
};

vector<string> extrair_conteudo(string linha){
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

Transicao extrair_transicao(string linha){
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

void topo_pilha(){ //funcao p retornar o topo da pilha

}

bool procurar_transicao(string cadeia, Automato automato){ //procura uma transicao aceitavel dado o automato atual //true: achou e aplicou a transicao //false: flopou

}

void verificar_aceitacao(){ //verifica se a cadeia esta completa, a pilha esta vazia e o estado atual eh estado final

}

void ler_arquivo_cadeia(string nome, Automato& automato){ //funcao p ler a entrada a ser testada, pode ter varias linhas
    string cadeia;
    ifstream arquivo(nome); //abre o arquivo
        if(!arquivo.is_open()){
        cout << "ERRO: o arquivo nao foi aberto." << endl;
        return;
    }
    string cadeia;
    while(getline(arquivo, cadeia)){
        while(true){ //roda infinito ate n ter transicoes aceitaveis
            if(!(procurar_transicao(cadeia, automato))){
                break;
            }
        }
        verificar_aceitacao();
    }
}

int main(){
    string nome;
    cout << "Digite o nome do arquivo .txt: "; //tem q digitar o .txt no fim
    cin >> nome;

    Automato automato;
    ler_arquivo_automato(nome, automato);

    cout << "AUTOMATO LIDO:" << endl;
    cout << "qtd de estados: " << automato.n << endl;
    cout << "estados finais aceitos: "; for(auto x:automato.estados_finais) cout << x << " "; cout << endl;
    cout << "alfabeto da fita: "; for(auto x:automato.alfabeto_fita) cout << x << " "; cout << endl;
    cout << "alfabeto da pilha: "; for(auto x:automato.alfabeto_pilha) cout << x << " "; cout << endl;

    cout << "TRANSICOES LIDAS:" << endl;
    int i=1;
    for(auto x:automato.transicoes){
        cout << "transicao " << i << ": " << x.estado_origem << " -> " << x.estado_destino
        << " // le: " << x.simbolo_lido << ", empilha: " << x.simbolo_empilhado << ", desempilha: " << x.simbolo_desempilhado << endl;
        i++;
    }


    return 0;
}
