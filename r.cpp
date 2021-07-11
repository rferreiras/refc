#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <stdio.h>
using namespace std;
/**************************************************************************************/
const char regxFunctionStr[] = ".*\\(*\\)\\{";
const char regxCallVoidFunctionStr[] = "[^:]+\\(*\\),?";
const char regxCallReturnFunctionStr[] = "\\w+[:]+\\w.+\\(*\\),?";

const char regxArrStr[] = ".*(:\\[).*\\]?";
const char regxStringStr[] = ".*(:\").*\"?";
const char regxIntStr[] = ".*:\\d+[^\\.|f|d].*";
const char regxFloatStr[] = ".*:\\d+\\.\\df.*";
const char regxDobleFloatStr[] = ".*:\\d+\\.\\dd.*";

const char regxReturnStringStr[] = "(return) \".*\"";
const char regxReturnIntStr[] = "(return).[0-9]+";
const char regxReturnFloatStr[] = "(return).[0-9]+\\.[0-9]+f.*";
const char regxReturnDobleFloatStr[] = "(return).[0-9]+\\.[0-9]+d.*";
/**************************************************************************************/
regex returnStringReg(regxReturnStringStr, regex::ECMAScript);
regex returnIntReg(regxReturnIntStr, regex::ECMAScript);
regex returnFloatReg(regxReturnFloatStr, regex::ECMAScript);
regex returnDobleFloatReg(regxReturnDobleFloatStr, regex::ECMAScript);

/**************************************************************************************/
regex functionReg(regxFunctionStr, regex::ECMAScript);
regex callVoidFunctionReg(regxCallVoidFunctionStr, regex::ECMAScript);
regex callReturnFunctionReg(regxCallReturnFunctionStr, regex::ECMAScript);

/**************************************************************************************/
regex arrayReg(regxArrStr, regex::ECMAScript);
regex stringReg(regxStringStr, regex::ECMAScript);
regex intReg(regxIntStr, regex::ECMAScript);
regex floatReg(regxFloatStr, regex::ECMAScript);
regex dobleFloatReg(regxDobleFloatStr, regex::ECMAScript);
/**************************************************************************************/
// const char regxFunctionStr[]=".+[(].*[)]{";
enum TipoDatos
{
    String,
    Integer,
    Float,
    Double,
    Array
};
struct SParametrosFunciones
{
    string Nombre;
    TipoDatos Tipo;
    string ValorPorDefecto;
};
struct SDeclaracionesFunciones
{
    string nombre;
    vector<SParametrosFunciones> retorno;
    vector<SParametrosFunciones> parametros;
};
map<string, SDeclaracionesFunciones> listaFunciones;
/**************************************************************************************/
TipoDatos getTipoDatos(string s)
{
    if (s == "0")
    {
        return TipoDatos::Integer;
    }
    if (s == "\"\"")
    {
        return TipoDatos::String;
    }
    if (s == "0.0f")
    {
        return TipoDatos::Float;
    }
    if (s == "[]")
    {
        return TipoDatos::Array;
    }
    if (s == "0.0d")
    {
        return TipoDatos::Double;
    }
}
vector<string> spitStr(const string S, string D = ",")
{
    vector<string> r;
    size_t pos = 0,
           len = S.length(),
           lenD = D.length();
    for (size_t i = 0; i < len; i++)
    {
        if (S.substr(i, lenD) == D)
        {
            r.push_back(S.substr(pos, i - pos));
            pos = i+1;
        }
    }
    if (len)
        r.push_back(S.substr(pos , len - pos));
    return r;
}
// vector<SDeclaracionesFunciones> listaFunciones;
string analizaFuncion(string s)
{
    //rututu klk( para1:"",para2:0.0f,paeya:0,parametro:[]){
    size_t posParentesis = s.find_first_of("(", 0);
    size_t posCierreParentesis = s.find_last_of(")");
    string nombre = s.substr(0, posParentesis);
    SDeclaracionesFunciones funcion;
    string parametros = s.substr(posParentesis + 1, posCierreParentesis - (posParentesis + 1));
    printf("*******\n%i,%i '%s'\n*******\n%s\n*********\n", posParentesis, posCierreParentesis, nombre.c_str(), parametros.c_str());
    if (listaFunciones.find(nombre) == listaFunciones.end())
    {
        funcion.nombre = nombre;
        auto paran1 = spitStr(parametros);
        for (size_t i = 0; i < paran1.size(); i++)
        {
            auto paran2 = spitStr(paran1[i], ":");
            SParametrosFunciones paran3;
            paran3.Nombre = paran2[0];
            paran3.Tipo = getTipoDatos(paran2[1]);
            paran3.ValorPorDefecto = paran2[1];
            funcion.parametros.push_back(paran3);
        }
        listaFunciones[nombre] = funcion;
    }
    return nombre;
}
/**************************************************************************************/
int main()
{
    ifstream in("main.r"); // Open for reading
    string s;
    string rr = "";
    string funcionActual="";
    int linea = 1, nivel = 0, velo;
    while (getline(in, s))
    {
        // Discards newline char
        //
        while (s.at(0) == ' ')
            s.erase(0, 1);
        smatch m, m2;
        string nivelStr = "", salidaStr = "";
        int h = 0;
        // velo == 1 ? h = nivel - 1 : h = nivel;
        for (int i = 0; i < nivel; i++)
            nivelStr += "\t";
        if (regex_match(s, m, functionReg))
        {
            salidaStr += "Funcion encontrada :" + s + "\n";
            funcionActual=analizaFuncion(s);
        }
/************************************************************************************************************************************************/
        if (regex_match(s, m, callReturnFunctionReg))
        {
            salidaStr += "Llamada a Funcion con retorno :" + s + ":\t" + to_string(linea) + "\n";
        }
        if (regex_match(s, m, callVoidFunctionReg))
        {
            salidaStr += "Llamada a Funcion sin retorno :" + s + ":\t" + to_string(linea) + "\n";
        }
/************************************************************************************************************************************************/
        if (regex_match(s, m2, arrayReg))
        {
            salidaStr += "Asignacion de array:" + s + ":\t" + to_string(linea) + "\n";
        }
        if (regex_match(s, m2, stringReg))
        {
            salidaStr += "Asignacion de Cadena de Caracteres:" + s + ":\t" + to_string(linea) + "\n";
        }
        if (regex_match(s, m2, intReg))
        {
            salidaStr += "Asignacion de Entero:" + s + ":\t" + to_string(linea) + "\n";
        }
        if (regex_match(s, m2, floatReg))
        {
            salidaStr += "AsignacionfunctionReg de punto flotante doble:" + s + ":\t" + to_string(linea) + "\n";
        }
/************************************************************************************************************************************************/
        if (regex_match(s, m2, returnStringReg))
        {
            salidaStr += "Retorna Caracteres:" + s + ":\t" + to_string(linea) + "\n";
        }

        if (regex_match(s, m2, returnIntReg))
        {
            salidaStr += "Retorna Entero:" + s + ":\t" + to_string(linea) + "\n";
        }

        if (regex_match(s, m2, returnFloatReg))
        {
            salidaStr += "Retorna flotante:" + s + ":\t" + to_string(linea) + "\n";
        }

        if (regex_match(s, m2, returnDobleFloatReg))
        {
            salidaStr += "Retorna punto flotante doble:" + s + ":\t" + to_string(linea) + "\n";
        }
/************************************************************************************************************************************************/
        velo = 0;
        if (s.at(0) == '{' || s.at(s.length() - 1) == '{')
        {
            salidaStr += "entrada de bloque \t>> : " + to_string(linea) + "\n";
            velo = 1;
        }
        if (s.at(0) == '}')
        {
            salidaStr += "salida de bloque \t<< : " + to_string(linea) + "\n";
            velo = -1;
        }
        nivel += velo;
        if (!salidaStr.empty())
        {
            nivelStr = "";
            h = 0;
            velo == 1 ? h = nivel - 1 : h = nivel;
            for (int i = 0; i < h; i++)
                nivelStr += "\t";
            rr += to_string(nivel) + ":" + nivelStr + salidaStr;
        }
        size_t pos2puntos = s.find_first_of(":", 0);
        size_t posParentesis = s.find_first_of("(", 0);
        size_t posCierraParentesis = s.find_last_of(")", 0);

        size_t posCorchere = s.find_first_of("[", 0);
        size_t posCierraCorchetes = s.find_first_of("]", 0);
        size_t posComa = s.find_last_of(",", 0);
        cout << s << "\n"; 
        linea++;
    }
    for (auto i = listaFunciones.begin(); i != listaFunciones.end(); i++)
    {
        cout << i->second.nombre << endl;
    }
    // cout << rr << endl << "end." << endl;
}
