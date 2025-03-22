#include <iostream>
#include <cctype>
#include <string>
#include <fstream>

using namespace std;

typedef struct Aeroporto
{
    string cidade;
    int codigo;
    string codigoCid;
    int contVoos;
    int numeroVoos[50];
} infAeroporto;

typedef struct listaVoo
{
    int numVoo;
    string origem;
    string destino;
    listaVoo* proximo;
} infVoo;
struct Nodo
{
    infVoo voos;
    struct Nodo *proximo;
};
typedef struct Nodo nodo;



int menu();
bool verificaNum(string x, string limInf, string limSup);
void CadastraAeroporto(infAeroporto aeroportos[], int &contAero, int &z);
void MostraAeroporto(infAeroporto aeroportos[],int contAero);
void ExcluiAeroporto (infAeroporto aeroportos[], int &contAero, string &buscaExcluiAero, string &orig, int &contVoo);
void ordenaVetDec(infAeroporto aeroportos[], int contAero);
void ordenaVetCre(infAeroporto aeroportos[], int contAero);
void CadastraVoo(infVoo **ptr_lista, int &contVoo, infAeroporto aeroportos[], int contAero, int &k);
void MostraVoo(infVoo *lista, infVoo voos, infAeroporto aeroportos[], int contAero);
void excluiVoo (infVoo **ptr_lista, infVoo voos, infAeroporto aeroportos[], int contAero, int &contVoo);
void excluiAeroportoVoos (infVoo **ptr_lista, infVoo voos, string buscaExcluiAero, string orig);
int verifExisteAero(infAeroporto aeroportos[], string busca, int contAero);
int verifExisteVoo(infVoo *lista, infVoo voos, int busca);
void gravainfo(ofstream &ofs, infAeroporto aeroportos[], int contAero, infVoo *ptr_lista, infVoo voos, int contVoo);
int verifExisteVoo2(infVoo *lista, infVoo voos, string busca);
void recupInfo(ifstream &ifs, infAeroporto aeroportos[], int &contAero, infVoo **ptr_lista, int &contVoo);
void recupVoo(infVoo **ptr_lista, int numeroVooTemp, string destinoVooTemp, string origemVooTemp);
void excluiAeroportoVoosDestino(infVoo **ptr_lista, infVoo voos, string busca, infAeroporto aeroportos[], int contAero, int &v, string orig);
bool verificaSeENum(string numero);

int main()
{
    infVoo voos, *umalista=NULL;
    infAeroporto aeroportos[10];
    string buscaExcluiAero, verifica4, orig="";
    ofstream ofs;
    ifstream ifs;
    int opcao, contAero=0, z=0, contVoo=0, v=0, k, num;
    do
    {
        opcao = menu();
        switch(opcao)
        {
        case 1:
            CadastraAeroporto(aeroportos,contAero,z);
            break;
        case 2:
            ExcluiAeroporto(aeroportos,contAero,buscaExcluiAero,orig,contVoo);
            //cout << orig << endl;
            for(int i=0; i<contVoo; i++)
            {
            //if(aeroportos[i].contVoos != 0){
            excluiAeroportoVoos(&umalista,voos,buscaExcluiAero,orig);
            //excluiAeroportoVoosDestino(&umalista,voos,buscaExcluiAero,aeroportos,contAero,v,orig);
            }
            //}
            //cout << v;
      //for(int m=0;m<contAero;m++){
            //for(int c=0;c<aeroportos[m].contVoos;c++){
                //if(v==aeroportos[m].numeroVoos[c]){
                //cout << aeroportos[m].cidade << endl;
                //getchar();
                //getchar();
                //aeroportos[m].contVoos--;
                //}
            //}
        //}
            break;
        case 3:
            MostraAeroporto(aeroportos,contAero);
            break;
        case 4:
            CadastraVoo(&umalista,contVoo,aeroportos,contAero,k);
            break;
        case 5:
            excluiVoo(&umalista,voos,aeroportos,contAero,contVoo);
            break;
        case 6:
            MostraVoo(umalista,voos,aeroportos,contAero);
            break;
        case 8:
            gravainfo(ofs,aeroportos,contAero,umalista,voos,contVoo);
            break;
        case 9:
            recupInfo(ifs,aeroportos,contAero,&umalista,contVoo);
            break;
        }
    }
    while(opcao != 10);
}

int menu()
{
    string resp;
    int respNum;
    bool verif = false;
    do
    {
        system("cls");
        cout << "------------- Aeroportos -------------" << endl;
        cout << "1) Cadastrar aeroporto." << endl;
        cout << "2) Remover aeroporto." << endl;
        cout << "3) Mostrar aeroportos." << endl;
        cout << "4) Cadastrar voo" << endl;
        cout << "5) Remove voo" << endl;
        cout << "6) Mostrar voo" << endl;
        cout << "7) Procurar voo." << endl;
        cout << "8) Gravar informacoes. " << endl;
        cout << "9) Recuperar informacoes. " << endl;
        cout << "10) Sair." << endl;
        cout << "------------ Escolha uma opcao ------------" << endl;
        cout << "Opcao:";
        cin >> resp;
        verif = verificaNum(resp, "1", "10");
    }
    while(verif==false);
    respNum = atoi(resp.c_str());
    return respNum;
}

bool verificaNum(string x, string limInf, string limSup)
{
    int xNum, infNum, supNum;
    if(x == "")
        return false;
    else if(!isdigit(x.at(0)))
        return false;
    xNum = atoi(x.c_str());
    infNum = atoi(limInf.c_str());
    supNum = atoi(limSup.c_str());
    if(xNum<infNum or xNum>supNum)
        return false;
    return true;
}
void CadastraAeroporto(infAeroporto aeroportos[], int &contAero, int &z)
{

    string nomeCidade, codigoAero;
    int verifica;

    cout << "Digite o nome da cidade: " << endl;
    cin.ignore();
    getline(cin, nomeCidade);
    cout << "Digite o codigo do aeroporto: " << endl;
    cin >> codigoAero;
    verifica = verifExisteAero(aeroportos,codigoAero,contAero);
    if(verifica == 1)
    {
        cout << "Aeroporto ja existe" << endl;
        getchar();
        getchar();
    }
    else
    {
        aeroportos[contAero].cidade = nomeCidade;
        aeroportos[contAero].codigoCid = codigoAero;
        aeroportos[contAero].codigo = z+1;
        aeroportos[contAero].contVoos = 0;
        contAero++;
        z++;
        cout << "Aeroporto cadastrado com sucesso!" << endl;
        getchar();
        getchar();
    }
}
void ExcluiAeroporto (infAeroporto aeroportos[], int &contAero, string &buscaExcluiAero, string &orig, int &contVoo)
{

    infVoo *umalista;
    int verifica;


    cout << "Digite o codigo do aeroporto que deseja excluir: ";
    cin >> buscaExcluiAero;
    verifica = verifExisteAero(aeroportos,buscaExcluiAero,contAero);
    if(verifica == 0)
    {
        cout << "Aeroporto nao encontrado" << endl;
        getchar();
    }
    else
    {
        if(contAero==1)
        {
            for(int i=0; i<contAero; i++)
            {
                if(buscaExcluiAero==aeroportos[i].codigoCid)
                {
                    orig = aeroportos[i].cidade;
                    contVoo = contVoo - aeroportos[i].contVoos;
                    aeroportos[i].cidade = "";
                    aeroportos[i].codigo = 0;
                    aeroportos[i].codigoCid = "";
                    aeroportos[i].contVoos = 0;
                    cout << "Aeroporto excluido!" << endl;
                    contAero--;
                    getchar();

                }
            }
        }
        else
        {
            for(int i=0; i<contAero; i++)
            {
                if(buscaExcluiAero==aeroportos[i].codigoCid)
                {
                    orig = aeroportos[i].cidade;
                    contVoo = contVoo - aeroportos[i].contVoos;
                    aeroportos[i].cidade = "";
                    aeroportos[i].codigo = 0;
                    aeroportos[i].codigoCid = "";
                    aeroportos[i].contVoos = 0;
                    cout << "Aeroporto excluido!" << endl;
                    ordenaVetDec(aeroportos,contAero);
                    contAero--;
                    ordenaVetCre(aeroportos,contAero);
                    getchar();
                }
            }
        }
    }
}


void MostraAeroporto(infAeroporto aeroportos[], int contAero)
{
    if(contAero==0){
        cout << "Nenhum aeroporto cadastrado." << endl;
        getchar();
        getchar();
    }else{
    cout << "Indice / Nome / Codigo / Quantidade de voos."<< endl;
    for(int i=0; i<contAero; i++)
    {
        cout << "[" << aeroportos[i].codigo << "] " << aeroportos[i].cidade << " / " << aeroportos[i].codigoCid << " / " << aeroportos[i].contVoos << endl;
    }
    getchar();
    getchar();
    }

}
void ordenaVetDec(infAeroporto aeroportos[], int contAero)
{

    unsigned int posicao=0;
    for(unsigned int i=0; i<contAero-1; i++)
    {
        posicao = i;
        for(unsigned int j=i+1; j<contAero; j++)
        {
            if(aeroportos[j].codigo > aeroportos[posicao].codigo) posicao = j;
        }
        swap(aeroportos[posicao].codigo, aeroportos[i].codigo);
        swap(aeroportos[posicao].cidade, aeroportos[i].cidade);
        swap(aeroportos[posicao].codigoCid, aeroportos[i].codigoCid);
        swap(aeroportos[posicao].contVoos, aeroportos[i].contVoos);

    }
}
void ordenaVetCre(infAeroporto aeroportos[], int contAero)
{

    unsigned int posicao=0;
    for(unsigned int i=0; i<contAero-1; i++)
    {
        posicao = i;
        for(unsigned int j=i+1; j<contAero; j++)
        {
            if(aeroportos[j].codigo < aeroportos[posicao].codigo) posicao = j;
        }
        swap(aeroportos[posicao].codigo, aeroportos[i].codigo);
        swap(aeroportos[posicao].cidade, aeroportos[i].cidade);
        swap(aeroportos[posicao].codigoCid, aeroportos[i].codigoCid);
        swap(aeroportos[posicao].contVoos, aeroportos[i].contVoos);
    }
}
void CadastraVoo(infVoo **ptr_lista, int &contVoo, infAeroporto aeroportos[], int contAero, int &k)
{
    listaVoo *p, *pant;
    infVoo voos;
    string origem, destino, busca, numeroSt;
    int verifica1, verifica2, n, numero;
    bool verificaSeNum=false;
    p = new listaVoo;
    if(p==NULL)
    {
        cout << "sem memória";
        cin.get();
        exit(1);
    }
    do{
    cout << "Digite o numero de voo: " << endl;
    cin >> numeroSt;
    verificaSeNum = verificaSeENum(numeroSt);
    }while(verificaSeNum==false);
    numero = atoi(numeroSt.c_str());
    verifica1 = verifExisteVoo(*ptr_lista,voos,numero);
    if(verifica1==1)
    {
        cout << "Voo ja existe" << endl;
        getchar();
        getchar();
    }
    else
    {
        cout << "Digite a origem do voo: " << endl;
        cin>>origem;
        busca=origem;
        verifica2 = verifExisteAero(aeroportos,busca,contAero);
        if(verifica2==0)
        {
            cout << "Aeroporto nao encontrado" << endl;
            getchar();
            getchar();
        }
        else
        {
            verifica2 = 0;
            cout << "Digite o destino do voo: " << endl;
            cin>>destino;
            busca=destino;
            verifica2 = verifExisteAero(aeroportos,busca,contAero);
            if(verifica2==0)
            {
                cout << "Aeroporto nao encontrado" << endl;
                getchar();
                getchar();
            }
            else
            {
                if(origem==destino)
                {
                    cout << "ERRO: Aeroporto de origem igual a de destino." << endl;
                    getchar();
                    getchar();
                }
                else
                {
                    p->numVoo = numero;
                    p->origem = origem;
                    p->destino = destino;
                    for(int i=0; i<contAero; i++)
                    {
                        if(aeroportos[i].codigoCid == origem)
                            n=i;
                    }
                    contVoo++;
                    aeroportos[n].numeroVoos[aeroportos[n].contVoos] = numero;
                    aeroportos[n].contVoos++;

                    p->proximo = NULL;
                    if (*ptr_lista==NULL)
                    {
                        *ptr_lista = p;
                        return;
                    }
                    pant = *ptr_lista;
                    while (pant->proximo != NULL)
                        pant = pant->proximo;
                    pant->proximo = p;
                }
            }
        }
    }
}
void MostraVoo(infVoo *lista, infVoo voos, infAeroporto aeroportos[], int contAero)
{

    listaVoo *p = lista;
    string busca;
    int encontrou=0, verifica;

    cout << "Digite o codigo do aeroporto para mostrar voos: " << endl;
    cin >> busca;
    verifica = verifExisteAero(aeroportos,busca,contAero);
    if(verifica == 0)
    {
        cout << "Aeroporto nao encontrado" << endl;
        getchar();
        getchar();
    }
    else
    {
        while(p != NULL)
        {
            if(p->origem == busca)
            {
                cout << "Numero do voo: " << p->numVoo << endl;
                cout << "Origem do voo: " << p->origem << endl;
                cout << "Destino do voo: " << p->destino << endl;
                encontrou++;
            }
            p=p->proximo;
        }
        if(encontrou==0)
        {
            cout << "Nao foi encontrado voos";
        }
        getchar();
        getchar();
    }
}
void excluiVoo (infVoo **ptr_lista, infVoo voos, infAeroporto aeroportos[], int contAero, int &contVoo)
{
    infVoo *p, *pant = NULL;
    int busca;
    string buscaSt;
    bool verificaSeNum=false;
    int encontrou=0;
    p = *ptr_lista;
    do{
    cout << "Digite o numero do voo a ser excluido: " << endl;
    cin >> buscaSt;
    verificaSeNum = verificaSeENum(buscaSt);
    }while(verificaSeNum==false);
    busca = atoi(buscaSt.c_str());
    if (p!=NULL)
    {
        if (p->numVoo == busca)
        {
            for(int i=0; i<contAero; i++)
            {
                if(p->origem == aeroportos[i].codigoCid)
                    aeroportos[i].contVoos--;
            }
            encontrou++;
            contVoo--;

            *ptr_lista = p->proximo;
            delete p;
            return;
        }
        pant = *ptr_lista;
        p = p->proximo;
        while (p != NULL && p->numVoo != busca)
        {
            pant = p;
            p=p->proximo;
        }
        if (p!=NULL)
        {
            pant->proximo = p->proximo;
            delete p;
        }
    }
    if(encontrou == 0)
        cout << "Voo nao encontrado." << endl;
    getchar();
    getchar();
}
void excluiAeroportoVoos(infVoo **ptr_lista, infVoo voos, string busca, string orig)
{
    infVoo *p, *pant = NULL;
    p = *ptr_lista;
    if (p!=NULL)
    {
        if (p->origem == busca)
        {
            *ptr_lista = p->proximo;
            delete p;
            return;
        }
        pant = *ptr_lista;
        p = p->proximo;
        while (p != NULL && p->origem != busca)
        {
            pant = p;
            p=p->proximo;
        }
        if (p!=NULL)
        {
            pant->proximo = p->proximo;
            delete p;
        }
    }
}
void excluiAeroportoVoosDestino(infVoo **ptr_lista, infVoo voos, string busca, infAeroporto aeroportos[], int contAero, int &v, string orig)
{
    infVoo *p, *pant = NULL;
    p = *ptr_lista;
    if (p!=NULL)
      if (p->destino == busca)
        {
            v=p->numVoo;
            *ptr_lista = p->proximo;
            delete p;
            return;
        }
        pant = *ptr_lista;
        p = p->proximo;
        while (p != NULL && p->destino != busca){
        while(p->origem != orig){
            pant = p;
            p=p->proximo;
        }
        }
        if (p!=NULL)
        {
            pant->proximo = p->proximo;
            v=p->numVoo;
            delete p;
        }
}
int verifExisteVoo(infVoo *lista, infVoo voos, int busca)
{

    listaVoo *p = lista;
    int encontrou=0;
    while(p != NULL)
    {
        if(p->numVoo == busca)
        {
            return 1;
        }
        p=p->proximo;
    }
    return 0;
}
int verifExisteVoo2(infVoo *lista, infVoo voos, string busca)
{

    listaVoo *p = lista;
    int encontrou=0;
    while(p != NULL)
    {
        if(p->origem == busca)
        {
            return 1;
        }
        p=p->proximo;
    }
    return 0;
}
int verifExisteAero(infAeroporto aeroportos[], string busca, int contAero)
{
    for(int i=0; i<contAero; i++)
    {
        if(busca==aeroportos[i].codigoCid)
            return 1;
    }
    return 0;
}

void gravainfo(ofstream &ofs, infAeroporto aeroportos[], int contAero, infVoo *ptr_lista, infVoo voos, int contVoo)
{
    listaVoo *p = ptr_lista;
    string busca;
    int verifica;
    ofstream fout("teste.txt");
    fout << contAero << endl;
    fout << contVoo << endl;
    for (int i = 0; i < contAero; i++)
    {
        fout << aeroportos[i].codigo << endl;
        fout << aeroportos[i].cidade << endl;
        fout << aeroportos[i].codigoCid << endl;
        fout << aeroportos[i].contVoos << endl;
        busca = aeroportos[i].codigoCid;
        for(int j = 0; j<aeroportos[i].contVoos; j++)
        {
            verifica = verifExisteVoo2(p,voos,busca);
            if(verifica == 1)
            {
                fout << p->numVoo << endl;
                fout << p->destino << endl;
                p=p->proximo;
            }
        }
    }
    cout << "Informacoes gravadas com sucesso!" << endl;
    getchar();
    getchar();
    fout.close();
}
void recupInfo(ifstream &ifs, infAeroporto aeroportos[], int &contAero, infVoo **ptr_lista, int &contVoo)
{
    ifstream fin("teste.txt");
    int numeroVooTemp;
    string destinoVooTemp, origemVooTemp, auxCid;
    fin >> contAero;
    fin >> contVoo;
    for(int i=0; i<contAero; i++)
    {
        fin >> aeroportos[i].codigo;
        fin >> aeroportos[i].cidade;
        fin >> aeroportos[i].codigoCid;
        origemVooTemp = aeroportos[i].codigoCid;
        fin >> aeroportos[i].contVoos;
        for(int j=0; j<aeroportos[i].contVoos; j++)
        {
            fin >> numeroVooTemp;
            aeroportos[i].numeroVoos[j] = numeroVooTemp;
            fin >> destinoVooTemp;
            recupVoo(ptr_lista,numeroVooTemp,destinoVooTemp,origemVooTemp);
        }
    }
    cout << "Informacoes recuperadas com sucesso!" << endl;
    getchar();
    getchar();
    fin.close();
}
void recupVoo(infVoo **ptr_lista, int numeroVooTemp, string destinoVooTemp, string origemVooTemp)
{
    listaVoo *p, *pant;
    infVoo voos;
    p = new listaVoo;

    p->numVoo = numeroVooTemp;
    p->origem = origemVooTemp;
    p->destino = destinoVooTemp;

    p->proximo = NULL;
    if (*ptr_lista==NULL)
    {
        *ptr_lista = p;
        return;
    }
    pant = *ptr_lista;
    while (pant->proximo != NULL)
        pant = pant->proximo;
    pant->proximo = p;
}
bool verificaSeENum(string numero){
for(int i=0;i<numero.size();i++){
if(!isdigit(numero.at(i))){
    return false;
}
}
return true;
}
