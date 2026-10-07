#include "execucao.h"

int main(){
    string nome;
    cout << "Digite o nome do arquivo .txt com as informacoes do automato: ";
    cin >> nome;

    Automato automato;
    ler_arquivo_automato(nome, automato);
 
    string nomecadeia; 
    cout << "Digite o nome do arquivo .txt com as cadeias a serem testadas: ";
    cin>> nomecadeia;
    ler_arquivo_cadeia(nomecadeia, automato);

    return 0;
}