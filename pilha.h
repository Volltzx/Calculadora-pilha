#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct Nodo
{
    T elemento;
    Nodo<T>* prox;
};

template<typename T>
struct Pilha
{
    Nodo<T>* inicio;
    int cardinalidade = 0;
};
template<typename T>
void criaPilha(Pilha<T> &pilha)
{
    pilha.cardinalidade = 0;
    pilha.inicio = NULL;
}
template<typename T>
void destruirPilha(Pilha<T> &pilha)
{
    Nodo<T> *p = pilha.inicio;
    while(p != NULL)
    {
        pilha.inicio = pilha.inicio->prox;
        delete p;
        p = pilha.inicio;
        pilha.cardinalidade--;
    }
}
template<typename T>
bool verificaVazia(Pilha<T> pilha)
{
    if(pilha.cardinalidade == 0)
        return true;
    return false;
}
template<typename T>
int numeroElementos(Pilha<T> pilha)
{
    return pilha.cardinalidade;
}
template<typename T>
bool verificaElemento(Pilha<T> pilha, T elemento)
{
    Nodo<T> *p = pilha.inicio;
    while(p != NULL)
    {
        if(p->elemento == elemento)
        {
            return true;
        }
        p = p->prox;
    }
    return false;
}
template<typename T>
T recuperaElemento(Pilha<T> pilha, int posicao)
{
    int cont=1;
    if(posicao <= 1 || posicao > pilha.cardinalidade)
    {
        //throw "Posicao invalida";
    }
    Nodo<T> *p = pilha.inicio;
    if(posicao == 1)
    {
        return pilha.inicio->elemento;
    }
    while(posicao != cont)
    {
        p=p->prox;
        cont++;
    }
    return p->elemento;
}

template<typename T>
void empilhar(Pilha<T> &pilha, T elemento)
{
    if(pilha.cardinalidade == 0){
        Nodo<T> *p = new Nodo<T>;
        p->elemento = elemento;
        p->prox = NULL;
        pilha.inicio = p;
    }else{
        Nodo<T> *p = new Nodo<T>;
        p->elemento = elemento;
        p->prox = pilha.inicio;
        pilha.inicio = p;
    }
    pilha.cardinalidade++;
}

template<typename T>
void desempilhar(Pilha<T> &pilha)
{
    Nodo<T> *p = pilha.inicio;
    pilha.inicio = p->prox;
    delete p;
    pilha.cardinalidade--;
}

template<typename T>
void mostra(Pilha<T> pilha)
{
    int cont;
   for(int i = 2; i<=pilha.cardinalidade;i++){
    Nodo<T> *p = pilha.inicio;
    cont = i;
   while(cont != pilha.cardinalidade){
    p=p->prox;
    cont++;
   }
   cout << p->elemento << endl;
   }
}


void somaElemento(Pilha<double> &pilha, double resultado)
{
    if(verificaVazia(pilha))
        empilhar(pilha, resultado);
    else if(numeroElementos(pilha) == 1){
        resultado = recuperaElemento(pilha,1) + resultado;
        empilhar(pilha,resultado);
    }
    else
    {
        double elementoAnt = recuperaElemento(pilha, 1);
        double soma = resultado + elementoAnt;
        empilhar(pilha,soma);
    }

}

void subtraiElemento(Pilha<double> &pilha, double resultado)
{
    if(verificaVazia(pilha))
        empilhar(pilha, resultado);
    else if(numeroElementos(pilha) == 1){
        resultado = recuperaElemento(pilha,1) - resultado;
        empilhar(pilha,resultado);
    }
    else
    {
        double elementoAnt = recuperaElemento(pilha, 1);
        double sub = elementoAnt - resultado;
        empilhar(pilha, sub);
    }

}

void multiplicaElemento(Pilha<double> &pilha, double resultado)
{
    if(verificaVazia(pilha))
        empilhar(pilha, resultado);
    else if(numeroElementos(pilha) == 1){
        resultado = recuperaElemento(pilha,1) * resultado;
        empilhar(pilha,resultado);
    }
    else
    {
        double elementoAnt = recuperaElemento(pilha, 1);
        double multi = resultado * elementoAnt;
        empilhar(pilha, multi);
    }

}void divideElemento(Pilha<double> &pilha, double resultado)
{
    if(verificaVazia(pilha))
        empilhar(pilha, resultado);
    else if(numeroElementos(pilha) == 1){
        resultado = recuperaElemento(pilha, 1) / resultado;
        empilhar(pilha,resultado);
    }
    else
    {
        double elementoAnt = recuperaElemento(pilha, 1);
        double div = elementoAnt / resultado;
        empilhar(pilha, div);
    }

}

void verificaPalavra(Pilha<double> &pilha, string operacao, bool &verifInicio)
{
    string subString = "";
    int tamanhoPalavra = operacao.size()-1;
    int achaParenteses, achaParenteses2;
    string numero;
    double resultado;

    string verificaInicio = operacao;

    if(verificaInicio == "INICIO" && verifInicio == false){
        verifInicio = true;
        criaPilha(pilha);
        return;
    }
    if(verifInicio == false){
        cout << "**INICIE A PILHA PRIMEIRO!**" << endl;
        return;
    }
    if(verifInicio == true && verificaInicio == "INICIO"){
        cout << "** PILHA JA FOI INICIADA **" << endl;
        return;
    }
    else if(operacao == "ZERA" && verifInicio == true)
    {
        destruirPilha(pilha);
        criaPilha(pilha);
        return;
    }
    else if(operacao == "PARCELAS" && verifInicio == true){
        if(pilha.cardinalidade == 0){
        cout << "** PILHA ESTA VAZIA! **" << endl;
        return;
        }
        if(pilha.cardinalidade >= 1){
        mostra(pilha);
        return;
        }
    }
    else if (operacao == "IGUAL" && pilha.cardinalidade == 0){
        cout << "** PILHA ESTA VAZIA! **" << endl;
        return;
    }
    else if(operacao == "IGUAL" && verifInicio == true && pilha.cardinalidade != 0){
        cout << recuperaElemento(pilha,1);
        return;
    }
    else if (operacao == "FIM" && verifInicio == true){
        destruirPilha(pilha);
        cout << "Tchau!";
        return;
    }

        for(int i = 0; i <= tamanhoPalavra; i++)
    {
        if(operacao.at(i) == '('){
            subString += operacao.at(i);
            achaParenteses = i;
            break;
        }
        subString += operacao.at(i);
    }

    for(int i = achaParenteses;  i <= tamanhoPalavra; i++)
        if(operacao.at(i) == ')'){
            achaParenteses2 = i;
            break;
        }

    if(achaParenteses2 != tamanhoPalavra)
        throw "** COMANDO INVALIDO **";

    try
    {
        for(int i = achaParenteses+1 ; i < achaParenteses2; i++)
        {
            numero += operacao.at(i);
        }

        resultado = stod(numero);
    }
    catch(invalid_argument& e)
    {
        throw "** COMANDO INVALIDO **";
    }

    if(subString == "SOMA(" && verifInicio == true)
        somaElemento(pilha, resultado);
    else if(subString == "SUBTRAI(" && verifInicio == true)
        subtraiElemento(pilha, resultado);
    else if(subString == "MULTIPLICA(" && verifInicio == true)
        multiplicaElemento(pilha, resultado);
    else if(subString == "DIVIDE(" && verifInicio == true)
        divideElemento(pilha, resultado);
    else
        throw "** COMANDO INVALIDO **";

}
#endif // HEADER_H_INCLUDED
