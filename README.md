# Simulador de autômato com pilha determinístico em C++

## Funcionalidades do programa
1.1 Estrutura de dados referente ao autômato
  struct Automato{
    int n;                             
    vector<string> estados_finais;      
    vector<string> alfabeto_fita;    
    vector<string> alfabeto_pilha;
    vector<Transicao> transicoes;
  };

1.2 Estrutura de dados referente a transição
  struct Transicao{
    string estado_origem;    
    string estado_destino;
    string simbolo_desempilhado; 
    string simbolo_lido;   
    string simbolo_empilhado; 
  };

1.3 Estrutura de dados referente ao processo em cadeia em andamento
  struct Simulacao{
    string estado_atual = "q0";
    string palavra = "";  
    int posicao_cadeia = 0;
    vector<string> pilha; 
  };

1.4 Funções

bool procurar_transicao: procura uma transição válida para a configuração atual da simulação. retorna true se encontrou, false caso contrário.

void aplicar_transicao: aplica uma transição na simulação, atualiza estado, fita e pilha.

void verificar_aceitacao: verifica se a cadeia processada foi aceita pelo autômato e imprime o resultado.

string topo_pilha: função que retorna o símbolo no topo da pilha na simulação em andamento.

1.5 Como usar
Para utilizar esse software, o usuário deve ter dois arquivos texto preparados:

1.5.1 automato.txt
Um arquivo contendo as informações do autômato, conforme no exemplo:
Q=8
F={q7}
alfabeto_fita = {a,b,c,d}
alfabeto_pilha = {X,Y}
(q0,@,@) = (q1,$)
(q1,a,@) = (q2,@)
(q1,c,@) = (q4,YY)
(q2,b,@) = (q3,X)
(q3,a,@) = (q2,@)
(q3,c,@) = (q4,YY)
(q3,d,X) = (q6,@)
(q4,c,@) = (q4,YY)
(q4,d,Y) = (q5,@)
(q5,d,Y) = (q5,@)
(q5,d,X) = (q6,@)
(q6,d,X) = (q6,@)
(q6,@,$) = (q7,@)

1.5.2 entrada.txt
Um arquivo contendo as cadeias a serem testada pela simulação:
abcddd
ccddd
abababddd

O projeto tem 5 arquivos (main.cpp, execucao.cpp, execucao.h, leitura.cpp, leitura.h). Os .cpp precisam ser compilados juntos, e os .h são incluídos automaticamente. 

1.5.3 Windows:
Para rodar em Windows, no CMD:

g++ main.cpp execucao.cpp leitura.cpp -o automato.exe
automato.exe

No Powershell:

g++ main.cpp execucao.cpp leitura.cpp -o automato.exe
.\automato.exe
1.5.4 Linux:

g++ main.cpp execucao.cpp leitura.cpp -o automato
./automato

## Construção do software
As operações de leitura de dados e organização nas structs são feitas na chamada da função ler_arquivo_automato().

A leitura do arquivo de cadeias é feita pela função ler_arquivo_cadeia(), que chama as demais funções de simulação.

O progresso do autômato é impresso a cada iteração, exibindo o estado atual, a posição sendo lida na cadeia e a pilha.

As seguintes bibliotecas foram utilizadas:
<iostream>
Entrada e saída padrão no console: cout, cin e endl.
<vector> 
Aparece na pilha de simulação, nas listas do autômato, e no retorno de extrair_conteudo.
<string>
Fornece o tipo string e suas operações, como substr, find, size e stoi.
<algorithm> 
Utilizada na função de verificar aceitação, em find()
<fstream> 
Leitura e escrita de arquivos.
<sstream> 
Utilizada para separar o conteúdo entre chaves em itens, com getline().

IDE utilizada: Visual Studio Code v1.143.1
compilador utilizado: MinGW v13.1.0

1.6 Referências

CPPREFERENCE. C++ Reference. Disponível em: https://en.cppreference.com/. Acesso em: 24 out. 2026. 
SILVA, Rômulo César. Linguagens Livres de Contexto. Unioeste, jun. 2020. Apresentação de slides. 
