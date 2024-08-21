/*
	Name:Calculadora lineal
	Author: Eder Said Martinez Ramirez
	Date: 25/11/19 00:33
	Description:
*/

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <ctype.h>


using namespace std;

bool isErrorSintaxis(string);
char getCharRightNumber(string,int);
char getCharLeftNumber(string,int);
float resolverOperaciones(string);
string limpiarEspacios(string);
void descomponerOperacion(vector<char>*,vector<float>*,string);
string desarrollarSignosAgrupacion(string);
float isOperacionPotencia(string,int*,float);
int findCierreAgrupacion(string,char,int);
int findFirstChar(string,char);
void realizarPotencias(vector<char>*,vector<float>*);
void realizarMultiplicacionesDiviciones(vector<char>*,vector<float>*);
void realizarSumasRestas(vector<char>*,vector<float>*);
void eliminarOperador(vector<char>*,int);
void eliminarNumero(vector<float>*,int);


int main() {
  string operacion;
  do{
      cout << "Ingrese Operacion: ";
      getline(cin,operacion);
      operacion = limpiarEspacios(operacion);
  }while(isErrorSintaxis(operacion));
  float resultado = resolverOperaciones(operacion);
  cout << "El Resultado es " << resultado;
  cin.ignore();
  return 0;
}

bool isErrorSintaxis(string operacion){
    if(operacion.find_first_not_of("1234567890.+-*/^()[]{}") != -1){
        cout<<"\n\tError de Sintaxis: caracter erroneo.\n\n\b";
        cin.ignore();
        return true;
    }
    for(int i=0;i<operacion.size();i++){
        if(operacion[i] == '*' || operacion[i] == '/' || operacion[i] == '^'){
            if(i == 0 || i == operacion.size()-1 // si esta al comienzo o final
            || !isdigit(operacion[i-1]) && operacion[i-1] != ')' && operacion[i-1] != ']' && operacion[i-1] != '}' // si no tiene numero o signo de agrupacion a su izquierda
            || !isdigit(operacion[i+1]) && operacion[i+1] != '(' && operacion[i+1] != '[' && operacion[i+1] != '{' && operacion[i+1] != '-'){ // si no tiene numero o signo de agrupacion a su izquierda
                cout<<"\n\tError de Sintaxis: operador (*,/,^) mal ubicado.\n\n\b";
                cin.ignore();
                return true;
            }
        }
        else if(operacion[i] == '+'){
            if(i == 0 || i == operacion.size()-1 // si esta al comienzo o final
            || !isdigit(operacion[i-1]) && operacion[i-1] != ')' && operacion[i-1] != ']' && operacion[i-1] != '}' // si no tiene numero o signo de agrupacion a su izquierda
            || !isdigit(operacion[i+1]) && operacion[i+1] != '(' && operacion[i+1] != '[' && operacion[i+1] != '{'){ // si no tiene numero o signo de agrupacion a su izquierda
                cout<<"\n\tError de Sintaxis: operador (+) mal ubicado.\n\n\b";
                cin.ignore();
                return true;
            }
        }
        else if(operacion[i] == '-'){
            if(i == operacion.size()-1   // si esta al final
            || i != 0 && (operacion[i-1] == '.' || operacion[i-1] == '+' || operacion[i-1] == '-')
            || !isdigit(operacion[i+1]) && operacion[i+1] != ')' && operacion[i+1] != ']' && operacion[i+1] != '}'){
                cout<<"\n\tError de Sintaxis: operador (-) mal ubicado.\n\n\b";
                cin.ignore();
                return true;
            }
        }
        else if(operacion[i] == '.'){
            if(i == 0 || i == operacion.size()-1 || !isdigit(operacion[i-1]) || !isdigit(operacion[i+1])
            || getCharRightNumber(operacion,i) == '.' || getCharLeftNumber(operacion,i) == '.'){
                cout<<"\n\tError de Sintaxis: operador (.) mal ubicado.\n\n\b";
                cin.ignore();
                return true;
            }
        }
    }
    return false;
}

char getCharRightNumber(string text, int pos){
    for(int i=pos+1;i<text.size();i++){
        if(!isdigit(text[i]))
            return text[i];
    }
    return '0';
}

char getCharLeftNumber(string text, int pos){
    for(int i=pos-1;i>0;i--){
        if(!isdigit(text[i]))
            return text[i];
    }
    return '0';
}

float resolverOperaciones(string operacion){
  vector<float> numeros;
  vector<char> operadores;

  operacion = desarrollarSignosAgrupacion(operacion); // Resuelve los (),[] y {} y retorna su resultado
  descomponerOperacion(&operadores,&numeros,operacion); // Descomponiendo Operacion en Numeros y Operadores

  while(numeros.size() > 1){
    realizarPotencias(&operadores,&numeros); // resolviendo las potencias
    realizarMultiplicacionesDiviciones(&operadores,&numeros); // resolviendo las multiplicaciones y diviciones
    realizarSumasRestas(&operadores,&numeros); // resolviendo las sumas y restas
  }
  return numeros.front();
}

string limpiarEspacios(string operacion){
    while(findFirstChar(operacion,' ') != -1){
        for(int i=0;i<operacion.size();i++)
            if(operacion[i] == ' ')
                operacion.replace(i,1,"");
    }
    return operacion;
}

void descomponerOperacion(vector<char> *operadores,vector<float> *numeros,string operacion){
  string num;
  int pos = operacion.find_first_of("+-*/^");
  while(pos != -1){
    if(pos == 0){ // valida la posibilidad de numeros negativos entonces trata el signo como numero y no como operador
        string sub_operacion = operacion.substr(1);
        pos = sub_operacion.find_first_of("+-*/^");
        if(pos != -1) pos++;
        else break;
    }
    num = operacion.substr(0,pos);
    numeros->push_back(atof(num.c_str()));
    operadores->push_back(operacion[pos]);
    operacion.erase(0,pos+1);
    pos = operacion.find_first_of("+-*/^");
  }
  num = operacion.substr(0,pos);
  numeros->push_back(atof(num.c_str()));
}

string desarrollarSignosAgrupacion(string operacion){
    int inicio,fin;
    inicio = operacion.find_first_of("([{");
    while(inicio != -1){
        fin = findCierreAgrupacion(operacion,operacion[inicio],inicio);
        string operacion_agrupada = operacion.substr(inicio+1,fin-inicio-1);
        float result = resolverOperaciones(operacion_agrupada);
        result = isOperacionPotencia(operacion,&fin,result);
        operacion.replace(inicio,fin-inicio+1,to_string(result));
        inicio = operacion.find_first_of("([{");
    }
    return operacion;
}

float isOperacionPotencia(string operacion,int *fin,float base){
    if(operacion[*fin+1] == '^'){
        string sub_cadena = operacion.substr(*fin+2,operacion.size()-*fin-1);
        float exponente = resolverOperaciones(sub_cadena);//atof(sub_cadena.substr(0,exp_long).c_str());
        *fin = *fin + to_string(exponente).size() + 1;
        return pow(base,exponente);
    }
    else
        return base;
}

int findCierreAgrupacion(string text,char signo_apertura, int inicio){
    int cont = 1;
    char signo_cierre;

    switch(signo_apertura){
        case '(': signo_cierre = ')';break;
        case '[': signo_cierre = ']';break;
        case '{': signo_cierre = '}';break;
    }

    for(int i=inicio+1;i<text.size();i++){
        if(text[i] == signo_apertura) cont++;
        else if(text[i] == signo_cierre) cont--;
        if(cont == 0) return i;
    }
    return -1;
}

int findFirstChar(string text,char c){
    for(int i=0;i<text.size();i++)
        if(text[i] == c)
            return i;
    return -1;
}

void realizarPotencias(vector<char> *operadores,vector<float> *numeros){
    for(int i=0;i<operadores->size();i++){
        if(operadores->at(i) == '^'){
            if(operadores->at(i) == '^')
                numeros->at(i) = pow(numeros->at(i),numeros->at(i+1));
            eliminarOperador(operadores,i);
            eliminarNumero(numeros,i+1);
            i--;    // para volver a revisar la posicion ya que se elimino un operador
        }
    }
}

void realizarMultiplicacionesDiviciones(vector<char> *operadores,vector<float> *numeros){
    for(int i=0;i<operadores->size();i++){
        if(operadores->at(i) == '*' || operadores->at(i) == '/'){
            if(operadores->at(i) == '*')
                numeros->at(i) = numeros->at(i) * numeros->at(i+1);
            else
                numeros->at(i) = (float)(numeros->at(i)) / (float)(numeros->at(i+1));
            eliminarOperador(operadores,i);
            eliminarNumero(numeros,i+1);
            i--;    // para volver a revisar la posicion ya que se elimino un operador
        }
    }
}

void realizarSumasRestas(vector<char> *operadores,vector<float> *numeros){
    for(int i=0;i<operadores->size();i++){
        if(operadores->at(i) == '+' || operadores->at(i) == '-'){
            if(operadores->at(i) == '+')
                numeros->at(i) = numeros->at(i) + numeros->at(i+1);
            else
                numeros->at(i) = numeros->at(i) - numeros->at(i+1);
            eliminarOperador(operadores,i);
            eliminarNumero(numeros,i+1);
            i--;    // para volver a revisar la posicion ya que se elimino un operador
        }
    }
}

void eliminarOperador(vector<char> *operadores,int index){
    for(int i=index;i<operadores->size()-1;i++)
        operadores->at(i) = operadores->at(i+1);
    operadores->pop_back();
}

void eliminarNumero(vector<float> *numeros,int index){
    for(int i=index;i<numeros->size()-1;i++)
        numeros->at(i) = numeros->at(i+1);
    numeros->pop_back();
}
