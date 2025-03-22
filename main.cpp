#include <iostream>
#include <cctype>
#include <cstring>
#define TAM 6

using namespace std;

typedef struct{
    string data;
    string diaSemana[7] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
    string horaInicial[6];
    string horaFinal[6];
    string tipo[6];
    string local[6];
    string assunto[6];
}infSemana;


int menu();
void iniciaNovaSemana(infSemana agendaSemana[], int contHora[]);
void formataAgenda(infSemana agendaSemana[]);
void incluirCompromisso(infSemana agendaSemana[], int contHora[]);
int buscaDataRec(string dia, int contDia, infSemana agendaSemana[]);
bool checaHr(string hrInicial, string hrFinal, infSemana agendaSemana[], int contHora[], int x);
void armazenaTipo(string tipo, infSemana agendaSemana[], int contDia, int contHora[]);
void exclueCompromisso(infSemana agendaSemana[], int contHora[]);
int buscaCompRec(string hrInicial, string hrFinal, int contDia, int compEncontrado, infSemana agendaSemana[], int contHora[]);
void exclueCompRec(int contDia, int contHora[], int compEncontrado, infSemana agendaSemana[]);
void relatorio1(infSemana agendaSemana[], int contHora[]);
void ordenaVetRec(int contHora[], int contDDia, int contador, string hrInicial, string hrFinal, infSemana agendaSemana[]);
void alteraPos(int contDia, int contador, infSemana agendaSemana[]);
void relatorio2(infSemana agendaSemana[], int contHora[]);
bool verificaNum(string x, string limInf, string limSup);
bool validaHora(string busca);
bool limitaData(string data);


int main(){
    infSemana agendaSemana[7];
    int resp=0, contHora[7]={0};
    do{
        resp = menu();
        switch(resp){
        case 1:
            iniciaNovaSemana(agendaSemana, contHora);
            break;
        case 2:
            incluirCompromisso(agendaSemana, contHora);
            break;
        case 3:
            exclueCompromisso(agendaSemana, contHora);
            break;
        case 4:
            relatorio1(agendaSemana, contHora);
            break;
        case 5:
            relatorio2(agendaSemana, contHora);
        }
    }while(resp != 6);
    return 0;
}

int menu(){
    string resp;
    int respNum;
    bool verif = false;
    do{
    system("cls");
    cout << "------------- Agenda Semanal! -------------" << endl;
    cout << "1) Inicializar uma nova semana." << endl;
    cout << "2) Inclusao de um novo compromisso." << endl;
    cout << "3) Exclusao de compromisso" << endl;
    cout << "4) Relatorio 1." << endl;
    cout << "5) Relatorio 2." << endl;
    cout << "6) Sair." << endl;
    cout << "------------ Escolha uma opcao ------------" << endl;
    cout << "Opcao:";
    cin >> resp;
    verif = verificaNum(resp, "1", "6");
    }while(verif==false);
    respNum = atoi(resp.c_str());
    return respNum;

}

bool verificaNum(string x, string limInf, string limSup){
    int xNum, infNum, supNum;
    if(x == "")
        return false;
    else
    if(!isdigit(x.at(0)))
        return false;
    xNum = atoi(x.c_str());
    infNum = atoi(limInf.c_str());
    supNum = atoi(limSup.c_str());
    if(xNum<infNum or xNum>supNum)
            return false;
    return true;
}


void iniciaNovaSemana(infSemana agendaSemana[], int contHora[]){
    char confirmacao;
    string data;
    bool verif, verif2;
    system("cls");
    cout << "Certeza que deseja abrir uma nova semana?" << endl;
    cout << "AVISO: Perdera Agenda JA REGISTRADA!" << endl;
    cout << "[S/N]: "; cin >> confirmacao;
    if(toupper(confirmacao) == 'S'){
        cin.ignore();
        for(int i=0; i<7 ;i++){
            contHora[i] = 0;
            for(int j=0; j<6; j++){
                agendaSemana[i].horaInicial[j] = {""};
                agendaSemana[i].horaFinal[j] = {""};
                agendaSemana[i].tipo[j] = {""};
                agendaSemana[i].local[j] = {""};
                agendaSemana[i].assunto[j] = {""};
            }
        }
        do{
        cout << "--------------------------------------------" << endl;
        cout << "Digite data inicial da semana [xx/xx/xxxx]: "; getline(cin, data);
        verif2 = limitaData(data);
        }while(verif2 == false);
        agendaSemana[0].data = data;
        cout << "Agenda Inicializada!";
        formataAgenda(agendaSemana);
        getchar();
    }

}

bool limitaData(string data){
    int convertDia, convertMes, convertAno;
    string dia, mes, ano;

    if(data == "")
        return false;

    if(data.size() != 10){
        return false;
    }
    if(!isdigit(data.at(0)) and !isdigit(data.at(1)) and !isdigit(data.at(3)) and !isdigit(data.at(4)) and !isdigit(data.at(6)) and !isdigit(data.at(7)) and !isdigit(data.at(8)) and !isdigit(data.at(9))){
       return false;
    }
    if(data.at(2) != '/' and data.at(5) != '/'){
        return false;

    }else{
        for(int i=0; i<2; i++)
            dia += data.at(i);
        for(int i=3; i<5; i++)
            mes += data.at(i);
        for(int i=6;i<10; i++)
            ano += data.at(i);
        convertDia = atoi(dia.c_str());
        convertMes = atoi(mes.c_str());
        convertAno = atoi(ano.c_str());
        if(convertMes == 1 or convertMes == 3 or convertMes == 5 or convertMes == 7 or convertMes == 8 or convertMes == 10 or convertMes == 12){
            if(convertDia > 31)
                return false;
        }
        if(convertMes == 2){
            if(convertDia > 28)
                return false;
        }
        if(convertMes == 4 or convertMes == 6 or convertMes == 9 or convertMes == 11){
            if(convertDia>30)
                return false;
        }
        if(convertMes > 12 or convertMes < 0)
            return false;

        if(convertDia < 0)
            return false;

        if(convertAno < 0)
            return false;


    }
    return true;
}


void formataAgenda(infSemana agendaSemana[]){
    int convertDia[7], convertMes[7], convertAno[7];
    string dia[7], mes[7], ano[7];
    for(int i=0; i<2; i++)
        dia[0] += agendaSemana[0].data.at(i);
    for(int i=3; i<5; i++)
        mes[0] += agendaSemana[0].data.at(i);
    for(int i=6; i<10; i++)
        ano[0] += agendaSemana[0].data.at(i);
    convertDia[0] = atoi(dia[0].c_str());
    convertMes[0] = atoi(mes[0].c_str());
    convertAno[0] = atoi(ano[0].c_str());
    for(int i=1; i<7;i++){
    convertDia[i] = convertDia[i-1];
    convertMes[i] = convertMes[i-1];
    convertAno[i] = convertAno[i-1];

    if(convertMes[i] == 1 or convertMes[i] == 3 or convertMes[i] == 5 or convertMes[i] == 7 or convertMes[i] == 8 or convertMes[i] == 10){
        if(convertDia[i]>=31){
            convertDia[i] = 0;
            convertMes[i]++;
        }
    }
        if(convertMes[i] == 2){
            if(convertDia[i] >=28){
                convertDia[i] = 0;
                convertMes[i]++;
            }
        }
        else
            if(convertMes[i] == 4 or convertMes[i] == 6 or convertMes[i] == 9 or convertMes[i] == 11){
                if(convertDia[i]>=30){
                    convertDia[i] = 0;
                    convertMes[i]++;
                }
            }else
                if(convertMes[i] == 12){
                    if(convertDia[i]>=31){
                        convertDia[i] = 0;
                        convertMes[i] = 1;
                        convertAno[i]++;
                    }

                }
        convertDia[i]++;
        dia[i] = to_string(convertDia[i]);
        mes[i] = to_string(convertMes[i]);
        ano[i] = to_string(convertAno[i]);

    }

    for(int j=1; j<7; j++){

        if(convertDia[j]>0 and convertDia[j]<10)
            agendaSemana[j].data = "0" + dia[j];
        else
            agendaSemana[j].data = dia[j];
        if(convertMes[j]>=1 and convertMes[j]<10)
            agendaSemana[j].data += "/0" + mes[j];

        else
            agendaSemana[j].data += "/" + mes[j];

        agendaSemana[j].data += "/" + ano[j];

    }
}


void incluirCompromisso(infSemana agendaSemana[], int contHora[]){
    string dia, hrInicial, hrFinal, tipo;
    int contDia = 7, contador=0;
    bool verifica, verif, verif2;

    system("cls");
    cin.ignore();
        cout << "Dia para adicionar compromisso [xx/xx/xxxx]: "; getline(cin,dia);
        contDia = buscaDataRec(dia, contDia, agendaSemana);
        if(contDia < 0){
            cout << "Dia da semana Invalido!";
            getchar();
        }else{
            do{
                system("cls");
                cout << "----------------------------------------------------" << endl;
                cout << "Horario Inicial que deseja incluir o compromisso [xxhxx]: "; getline(cin, hrInicial);
                verif = validaHora(hrInicial);
                cout << "Horario Final que deseja incluir o compromisso [xxhxx]: "; getline(cin, hrFinal);
                verif2 = validaHora(hrFinal);
                cout << "----------------------------------------------------" << endl;
            }while(verif == false or verif2 ==false);
            verifica = checaHr(hrInicial, hrFinal, agendaSemana, contHora, contDia);
            if(verifica == false){
                cout << "Esse horario ja possui compromisso ou horario Invalido!";
                getchar();
            }
            if(verifica){
                do{
                cout << "---------------------------------------------" << endl;
                cout << "|                 Tipo :                    |" << endl;
                cout << "| 1)Reuniao.  2)Atividade.  3)Aniversario.  |" << endl;
                cout << "---------------------------------------------" << endl;
                cout << "opcao: "; getline(cin, tipo);
                verif = verificaNum(tipo, "1", "3");
                }while(verif==false);
                armazenaTipo(tipo, agendaSemana, contDia, contHora);
                cout << "----------------------------------" << endl;
                cout << "Digite o Local: "; getline(cin, agendaSemana[contDia].local[contHora[contDia]]);
                cout << "----------------------------------" << endl;
                cout << "Digite o Assunto: "; getline(cin, agendaSemana[contDia].assunto[contHora[contDia]]);
                cout << "----------------------------------" << endl;
                agendaSemana[contDia].horaInicial[contHora[contDia]] = hrInicial;
                agendaSemana[contDia].horaFinal[contHora[contDia]] = hrFinal;
                contador = contHora[contDia];
                contHora[contDia]++;
                cout << "Adicionado com Sucesso!";
                getchar();
            }
        }
        ordenaVetRec(contHora, contDia, contador, hrInicial, hrFinal, agendaSemana);
}

bool validaHora(string busca){
    if(busca == ""){
        return false;
    }

    if(busca.size() != 5){
        return false;
    }
    if(!isdigit(busca.at(0)) and !isdigit(busca.at(1)) and !isdigit(busca.at(3)) and !isdigit(busca.at(4))){
       return false;
    }
    if(busca.at(2) != 'h')
        return false;

    return true;
}


void ordenaVetRec(int contHora[], int contDia, int contador, string hrInicial, string hrFinal, infSemana agendaSemana[]){
    string horaInicialC, horaFinalC;
    int horaInicial, horaFinal, horaInicialVet, horaFinalVet;
    if(contador < 1)
        contador=0;
    if(contador > 0){
        for(int i=0; i<5; i++){
            if(isdigit(hrInicial.at(i)))
                horaInicialC += hrInicial.at(i);
            if(isdigit(hrFinal.at(i)))
                horaFinalC += hrFinal.at(i);
    }
        horaInicial = atoi(horaInicialC.c_str());
        horaFinal = atoi(horaFinalC.c_str());
        horaInicialC = "";
        horaFinalC = "";
        horaInicialVet = 0;
        horaFinalVet = 0;
        for(int j=0; j<5; j++){
            if(isdigit(agendaSemana[contDia].horaInicial[contador-1].at(j)))
                horaInicialC += agendaSemana[contDia].horaInicial[contador-1].at(j);
            if(isdigit(agendaSemana[contDia].horaFinal[contador-1].at(j)))
                horaFinalC += agendaSemana[contDia].horaFinal[contador-1].at(j);
        }
        horaInicialVet = atoi(horaInicialC.c_str());
        horaFinalVet = atoi(horaFinalC.c_str());
        if(horaInicial < horaInicialVet and horaFinal < horaFinalVet)
            alteraPos(contDia, contador, agendaSemana);
        ordenaVetRec(contHora, contDia, contador-1, hrInicial, hrFinal, agendaSemana);
    }

}

void alteraPos(int contDia, int contador, infSemana agendaSemana[]){
    string aux;
    aux = agendaSemana[contDia].horaInicial[contador-1];
    agendaSemana[contDia].horaInicial[contador-1] = agendaSemana[contDia].horaInicial[contador];
    agendaSemana[contDia].horaInicial[contador] = aux;
    aux = agendaSemana[contDia].horaFinal[contador-1];
    agendaSemana[contDia].horaFinal[contador-1] = agendaSemana[contDia].horaFinal[contador];
    agendaSemana[contDia].horaFinal[contador] = aux;
    aux = agendaSemana[contDia].tipo[contador-1];
    agendaSemana[contDia].tipo[contador-1] = agendaSemana[contDia].tipo[contador];
    agendaSemana[contDia].tipo[contador] = aux;
    aux = agendaSemana[contDia].local[contador-1];
    agendaSemana[contDia].local[contador-1] = agendaSemana[contDia].local[contador];
    agendaSemana[contDia].local[contador] = aux;
    aux = agendaSemana[contDia].assunto[contador-1];
    agendaSemana[contDia].assunto[contador-1] = agendaSemana[contDia].assunto[contador];
    agendaSemana[contDia].assunto[contador] = aux;
}

void armazenaTipo(string tipo, infSemana agendaSemana[], int contDia, int contHora[]){
    if(tipo == "1")
        agendaSemana[contDia].tipo[contHora[contDia]] = "Reuniao.";
    else
        if(tipo == "2")
            agendaSemana[contDia].tipo[contHora[contDia]] = "Atividade.";
        else
            if(tipo == "3")
                agendaSemana[contDia].tipo[contHora[contDia]] = "Aniversario.";
}

int buscaDataRec(string dia, int contDia, infSemana agendaSemana[]){
    if(contDia < 0)
        return -1;
    if(dia == agendaSemana[contDia].data)
        return contDia;

    return buscaDataRec(dia, contDia-1, agendaSemana);
}

bool checaHr(string hrInicial, string hrFinal, infSemana agendaSemana[], int contHora[], int contDia){
    string horaInicialC, horaFinalC;
    int horaInicial, horaFinal, horaInicialVet, horaFinalVet;
    for(int i=0; i<5; i++){
        if(isdigit(hrInicial.at(i)))
            horaInicialC += hrInicial.at(i);
        if(isdigit(hrFinal.at(i)))
            horaFinalC += hrFinal.at(i);
    }
    horaInicial = atoi(horaInicialC.c_str());
    horaFinal = atoi(horaFinalC.c_str());

    for(int i=0; i<contHora[contDia]; i++){
        horaInicialC = "";
        horaFinalC = "";
        horaInicialVet = 0;
        horaFinalVet = 0;
        for(int j=0; j<5; j++){
            if(isdigit(agendaSemana[contDia].horaInicial[i].at(j)))
                horaInicialC += agendaSemana[contDia].horaInicial[i].at(j);
            if(isdigit(agendaSemana[contDia].horaFinal[i].at(j)))
                horaFinalC += agendaSemana[contDia].horaFinal[i].at(j);
        }
        horaInicialVet = atoi(horaInicialC.c_str());
        horaFinalVet = atoi(horaFinalC.c_str());
        if((horaInicial >= horaInicialVet and horaInicial <= horaFinalVet) or (horaFinal >= horaInicialVet and horaFinal <= horaFinalVet))
            return false;
    }
    if((horaInicial < 0000 or horaInicial>2359) or (horaFinal < 0000 or horaFinal>2359))
        return false;
    if(horaInicial >= horaFinal and horaFinal != 0000)
        return false;
    return true;
}


void exclueCompromisso(infSemana agendaSemana[],int contHora[]){
    string dataEx, hrInicial, hrFinal;
    int compEncontrado, contDia=7;
    bool verif, verif2;

    system("cls");
    cin.ignore();
    cout << "Dia para excluir compromisso [xx/xx/xxxx]: "; getline(cin,dataEx);
    contDia = buscaDataRec(dataEx, contDia, agendaSemana);
    if(contDia < 0){
        cout << "Dia da semana Invalido!";
        getchar();
    }else{
        compEncontrado = contHora[contDia]-1;
        do{
            system("cls");
            cout << "----------------------------------------------------" << endl;
            cout << "Horario Inicial que deseja incluir o compromisso [xxhxx]: "; getline(cin, hrInicial);
            verif = validaHora(hrInicial);
            cout << "Horario Final que deseja incluir o compromisso [xxhxx]: "; getline(cin, hrFinal);
            verif2 = validaHora(hrFinal);
            system("cls");
            cout << "----------------------------------------------------" << endl;
        }while(verif == false and verif2 == false);
        compEncontrado = buscaCompRec(hrInicial, hrFinal, contDia, compEncontrado, agendaSemana, contHora);
        if(compEncontrado < 0){
            cout << "Horario Inexistente!" << endl;
            getchar();
        }
        if(compEncontrado >= 0){
            exclueCompRec(contDia, contHora, compEncontrado, agendaSemana);
            cout << "Horario Excluido!";
            getchar();
        }
    }

}

int buscaCompRec(string hrInicial, string hrFinal, int contDia, int compEncontrado, infSemana agendaSemana[], int contHora[]){
    if(compEncontrado < 0)
        return -1;
    if((hrInicial == agendaSemana[contDia].horaInicial[compEncontrado]) and (hrFinal == agendaSemana[contDia].horaFinal[compEncontrado])){
        return compEncontrado;
    }

    return buscaCompRec(hrInicial, hrFinal, contDia, compEncontrado-1, agendaSemana, contHora);
}

void exclueCompRec(int contDia, int contHora[], int compEncontrado, infSemana agendaSemana[]){
    if(compEncontrado > 0){
        for(int i=compEncontrado; i<contHora[contDia]; i++){
            agendaSemana[contDia].horaInicial[i] = agendaSemana[contDia].horaInicial[i + 1];
            agendaSemana[contDia].horaFinal[i] = agendaSemana[contDia].horaFinal[i + 1];
            agendaSemana[contDia].tipo[i] = agendaSemana[contDia].tipo[i + 1];
            agendaSemana[contDia].local[i] = agendaSemana[contDia].local[i + 1];
            agendaSemana[contDia].assunto[i] = agendaSemana[contDia].assunto[i + 1];
        }
    }
    agendaSemana[contDia].horaInicial[contHora[contDia]-1] = "";
    agendaSemana[contDia].horaFinal[contHora[contDia]-1] = "";
    agendaSemana[contDia].tipo[contHora[contDia]-1] = "";
    agendaSemana[contDia].local[contHora[contDia]-1] = "";
    agendaSemana[contDia].assunto[contHora[contDia]-1] = "";
    contHora[contDia]--;

}

void relatorio1(infSemana agendaSemana[], int contHora[]){
    string dataEx;
    int contDia=7;
    system("cls");
    cin.ignore();
    cout << "Dia para visualizar compromisso [xx/xx/xxxx]: "; getline(cin,dataEx);
    contDia = buscaDataRec(dataEx, contDia, agendaSemana);
    if(contDia < 0){
        cout << "Dia da semana Invalido!";
        getchar();
    }else{
        if(contHora[contDia] <= 0){
            cout << "Dia sem Compromisso!" << endl;
            getchar();
        }else{
            cout << "-------------------------------------" << endl;
            cout << agendaSemana[contDia].data << endl;
            cout << "-------------------------------------" << endl;
            cout << "Dia: " << agendaSemana[contDia].diaSemana[contDia] << endl;
            cout << endl;
            for(int i=0; i<contHora[contDia]; i++){
                cout << "-------------------------------------" << endl;
                cout << "Hora Inicial: " << agendaSemana[contDia].horaInicial[i] << endl;
                cout << "Tipo: " << agendaSemana[contDia].tipo[i] << endl;
                cout << "Local: " << agendaSemana[contDia].local[i] << endl;
                cout << "Assunto: " << agendaSemana[contDia].assunto[i] << endl;
                cout << "Hora Final: " << agendaSemana[contDia].horaFinal[i] << endl;
                cout << "-------------------------------------" << endl;
                getchar();
            }
        }
    }
}



void relatorio2(infSemana agendaSemana[], int contHora[]){
    system("cls");
    for(int i=0; i<7; i++){
        cout << "-------------------------------------" << endl;
        cout << agendaSemana[i].data << endl;
        cout << "-------------------------------------" << endl;
        cout << "Dia: " << agendaSemana[i].diaSemana[i] << endl;
        if(contHora[i] <=0){
            cout <<  "-------------------------------------" << endl;
            cout <<  "Dia sem compromissos!" << endl;
            cout <<  "-------------------------------------" << endl;
            getchar();
        }
        for(int j=0; j<contHora[i]; j++){
            cout << "-------------------------------------" << endl;
            cout << "Hora Inicial: " << agendaSemana[i].horaInicial[j] << endl;
            cout << "Tipo: " << agendaSemana[i].tipo[j] << endl;
            cout << "Local: " << agendaSemana[i].local[j] << endl;
            cout << "Assunto: " << agendaSemana[i].assunto[j] << endl;
            cout << "Hora Final: " << agendaSemana[i].horaFinal[j] << endl;
            cout << "-------------------------------------" << endl;
            getchar();
        }
        getchar();
        system("cls");
    }
}
