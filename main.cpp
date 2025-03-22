#include <iostream>
#include <string>
#include "pilha.h"

using namespace std;

int main(){
    Pilha<double> pilha;
    string operacao;
    bool verifInicio;
    cout << "======== Calculadora ========" << endl;
    cout << "      Lista de comandos" << endl;
    cout << " INICIO " << endl;
    cout << " ZERA " << endl;
    cout << " SOMA(valor)" << endl;
    cout << " SUBTRAI(valor) " << endl;
    cout << " MULTIPLICA(valor) " << endl;
    cout << " DIVIDE(valor) " << endl;
    cout << " PARCELAS " << endl;
    cout << " IGUAL " << endl;
    cout << " FIM " << endl;
    cout << "Faça suas operações:" << endl;
    while (operacao != "FIM"){
        getline(cin, operacao);
        if(operacao != "" && operacao != " " && operacao != "  " && operacao != "   " && operacao != "    "){
            try{
            verificaPalavra(pilha, operacao, verifInicio);
            }
            catch(const char* msg){
                cerr << msg << endl;
            }
        }
    }
}
