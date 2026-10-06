#include "execucao.cpp"

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
