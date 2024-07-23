#include <iostream>

using namespace std;

int base64Index[]
{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','x',
 '0','1','2','3','4','5','6','7','8','9','+','/'};

int getIndexByChar(char a){
    for(int i = 0; i < 64; i++){
        if(base64Index[i] == a) return i;
    }
    if(a ==  '=')return -2;
    return -1;
}


string decimalABinario(char decimal) {
    string aux = "";
    if (decimal == 0)
        return "0";

    while (decimal > 0) {
        aux = to_string(decimal % 2) + aux;
        decimal /= 2;
    }
    return aux;
}

string stringABinario(string texto){
    char character;
    string finalString;
    for(int i = 0; i < texto.size(); i++){
        character = texto[i];
        string binario = decimalABinario(character);
        while(binario.size() < 8) binario = "0" + binario;
        finalString += binario;
    }
    return finalString;
}

int binarioADecimal(string binario) {
    int finalInt = 0;
    int exp = 1;
    for (int i = binario.size() - 1; i >= 0; i--) {
        if (binario[i] == '1') {
            finalInt += exp;
        }
        exp *= 2;
    }
    return finalInt;
}

string aBase64(string binario){
    string finalString = "";
    for(int i = 0; i < binario.size(); i = i+6){
        string paquete = "";
        for(int j = 0; j < 6; j++)paquete += binario[i+j];
        cout << paquete << endl;
        finalString += (char)base64Index[binarioADecimal(paquete)];
    }
    if(binario.size()%6 == 2)finalString += "==";
    if(binario.size()%6 == 4)finalString += "=";
    return finalString;
}

string convertirATexto(string binario){
    string finalString = "";
    for(int i = 0; i < binario.size(); i = i+8){
        string paquete = "";
        for(int j = 0; j < 8; j++) paquete +=binario[i+j];
        finalString += (char)binarioADecimal(paquete);
    }
    return finalString;
}

string quitarIguales(string cadena){
    int lastIndex = cadena.size()-1;
    string finalString = "";
    while(cadena[lastIndex] == '='){
    finalString += "00";
    lastIndex--;
    }
    return cadena.substr(0, lastIndex+1);
}




bool esBase64(string cadena){
    for(int i = 0; i< cadena.size(); i++){
        if(getIndexByChar(cadena[i]) == -1)return false;
    }
    return true;
}

string base64ABinario(string cadena){
    string finalString = "";
    for(int i = 0; i < cadena.size(); i++){
        int index = getIndexByChar(cadena[i]);
        string binario = decimalABinario(index);
        while(binario.size() < 6) binario = "0" + binario;
        finalString += binario;
    }
    return finalString;
}

void codificar(){
    string cadena;
    cout << "Escribe la cadena a codificar" << endl;
    getline(cin, cadena);
    cin.clear();
    cadena = stringABinario(cadena);
    cadena = aBase64(cadena);
    cout <<"en decimal base 64: "<< cadena << endl;
}

void decodificar(){
    string cadena;
    cout << "Escribe la cadena a decodificar" << endl;
    getline(cin, cadena);
    cin.clear();
    if(!esBase64(cadena)){
        cout << "No es base64" << endl;
        return;
    }
    cadena = quitarIguales(cadena);
    cadena = base64ABinario(cadena);
    cadena = convertirATexto(cadena);
    cout << "Cadena decodificada es: " << cadena << endl;
}

void menu(){
    int choice;
    do{
        cout << "Que desea hacer" << endl;
        cout << "1. Codificar" << endl;
        cout << "2. Decodificar" << endl;
        cout << "3. Salir" << endl;
        cin.clear();
        cin >> choice;
        cin.ignore();
        switch(choice){
        case 1:
            codificar();
            break;
        case 2:
            decodificar();
            break;
        case 3:
            break;
        default:
            cout << "Ingresa una opcion valida" << endl;
        }
        if(choice == 3)break;
    }while(true);
}

int main()
{
    cout << "Base 64" << endl;
    menu();
    return 0;
}
