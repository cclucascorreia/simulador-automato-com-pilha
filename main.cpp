#include <bits/stdc++.h>
using namespace std;

struct Transicao{
    string estado_origem;
    string estado_destino;
    string simbolo_requerido; //deve ter isso no topo da pilha pra poder usar a transicao
    string simbolo_lido; //simbolo q vai ser adicionado a palavra resposta
    string simbolo_empilhado; //simbolo q vai substituir o topo da pilha
};

struct Automato{
    int n; //numero de estados
    string estado_inicial;
    vector<string> estados_finais;
    vector<string> alfabeto_fita; //letras q podem ser usadas na fita
    vector<string> alfabeto_pilha; //letras q podem ser empilhadas
    vector<Transicao> transicoes; //armazena structs de transicao
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

void lerArquivo(string nome, Automato& automato){
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
            string nova_linha = extrair_conteudo(linha);
            Transicao Atual;
        }
        l++;
    }
}

int main(){
    string nome;
    cout << "Digite o nome do arquivo .txt: "; //tem q digitar o .txt no fim
    cin >> nome;

    Automato automato;
    lerArquivo(nome, automato);

    cout << "INFORMACOES LIDAS:" << endl;
    cout << "qtd de estados: " << automato.n << endl;
    cout << "estados finais aceitos: "; for(auto x:automato.estados_finais) cout << x << " "; cout << endl;
    cout << "alfabeto da fita: "; for(auto x:automato.alfabeto_fita) cout << x << " "; cout << endl;
    cout << "alfabeto da pilha: "; for(auto x:automato.alfabeto_pilha) cout << x << " "; cout << endl;

    return 0;
}
