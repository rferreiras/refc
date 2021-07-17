/***********************************************************************
compilador del nuevo lenguaje Newton

************************************************************************/
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
const char *palabrasReservadas[] = {"print", "else", "if", "retun", "main", "in", "not", "type of"};
const char *Cabecera =
    "#include <string>"
    "#include <vector>"
    "#include <fstream>"
    "#include <iostream>"
    "#include <stdio.h>"
    "using namespace std;"
    "enum TipoDatos"
    "{"
    "    String,"
    "    Integer,"
    "    Float,"
    "    Double,"
    "    Array"
    "};";
enum TipoDatos
{
    String,
    Integer,
    Float,
    Double,
    Array
};
// estas dos varibles acumulan el codigo fuente relativo a las entras y salidas de las funciones
string estructurasParametros, estructurasRetorno;
struct SParametrosFunciones
{
    string Nombre;
    TipoDatos Tipo;
    string ValorPorDefecto;
};
struct SDeclaracionesFunciones
{
    string nombre;
    string codigo;
    vector<SParametrosFunciones> retorno;
    vector<SParametrosFunciones> parametros;
};
map<string, SDeclaracionesFunciones> listaFunciones;
/**************************************************************************************/
// Funciones utilitarias
string tipoDatos2cpp(TipoDatos t)
{
    switch (t)
    {
    case TipoDatos::Integer:
        return "int";
        break;

    case TipoDatos::Float:
        return "float";
        break;

    case TipoDatos::Double:
        return "double";
        break;

    case TipoDatos::String:

    default:
        return "string";
    }
}
/**************************************************************************************/
/*
    Funcion Busca y reemplaza devuelve puntero con *char de la cadena resultado
    *s:         string original
    *rpl:       valor a buscar
    *replTxt:   texto por el que se va a reemplazar
*/
char *Rreplace(const char *s, const char *rpl, const char *replTxt)
{
    char *r;
    char temp[1000];
    int Fs[100];
    int n = 1;
    int i = 0;
    Fs[0] = 0;
    int ls = strlen(s);
    int lrpl = strlen(rpl);
    int lTexto = strlen(replTxt);
    for (i = 0; i < ls; i++)
    {
        memcpy(temp, s + i, lrpl);
        temp[lrpl] = '\0';
        if (strcmp(temp, rpl) == 0)
        {
            Fs[n] = i;
            i += lrpl - 1;
            n++;
        }
    }
    r = (char *)malloc(ls + (lTexto * n) + 1);
    int lp = 0, lps = 0;
    for (i = 1; i < n; i++)
    {
        int d = Fs[i] - lps;
        memcpy(r + lp, s + lps, d);
        memcpy(r + d + lp, replTxt, lTexto);
        //cout << d << " " << lp << " " << lps << endl;
        lp += d + lTexto;
        lps += d + lrpl;
    }
    int d = ls - lps;
    //cout << (lp + d + 1) << " " << (ls + (lTexto * n) + 1) << " " << lps << endl;
    memcpy(r + lp, s + lps, d);
    r[lp + d + 1] = '\0';
    //cout << r << endl;
    return r;
}
/*
    funcion devulve un vector de string de una cadena separada por un un caracter
    "abc,def,1,3,1" 
*/
vector<string> Spit_String(const string S, string D = ",")
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
            pos = i + 1;
        }
    }
    if (len)
        r.push_back(S.substr(pos, len - pos));
    return r;
}
/**************************************************************************************/
/**************************************************************************************/

TipoDatos Get_Tipo_Datos(string s)
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

// vector<SDeclaracionesFunciones> listaFunciones;
/**************************************************
 * Analiza la declaracion de una funcion
 * crea la structura de parametros
**************************************************/
string Analiza_Funcion(string s)
{
    //rututu klk( para1:"",para2:0.0f,paeya:0,parametro:[]){
    size_t posParentesis = s.find_first_of("(", 0);
    size_t posCierreParentesis = s.find_last_of(")");
    string nombre = s.substr(0, posParentesis);
    string estructuraParametros = "",nombreTipoParametros="void";
    SDeclaracionesFunciones funcion;
    char *temp1 = Rreplace(nombre.c_str(), " ", "_");
    string nuevoNombre = temp1;
    free(temp1);

    string parametros = s.substr(posParentesis + 1, posCierreParentesis - (posParentesis + 1));
    // printf("*******\n%i,%i '%s'\n*******\n%s\n*********\n", posParentesis, posCierreParentesis, nombre.c_str(), parametros.c_str());
    if (listaFunciones.find(nombre) == listaFunciones.end())
    {
        funcion.nombre = nombre;
        auto paran1 = Spit_String(parametros);
        if (paran1.size())
        {
            nombreTipoParametros=nuevoNombre + "_Args Args";
            estructuraParametros = "struct " + nuevoNombre + "_Args{\n";
            for (size_t i = 0; i < paran1.size(); i++)
            {
                auto paran2 = Spit_String(paran1[i], ":");
                SParametrosFunciones paran3;
                paran3.Nombre = paran2[0];
                paran3.Tipo = Get_Tipo_Datos(paran2[1]);
                paran3.ValorPorDefecto = paran2[1];
                estructuraParametros += "   " + tipoDatos2cpp(paran3.Tipo) + " " + paran3.Nombre + ";\n";
                funcion.parametros.push_back(paran3);
            }
            estructuraParametros += "}\n";
        }
        string r = "~tipo Retorno~ " + nuevoNombre + "(" + nombreTipoParametros + "){\n~cuerpo funcion~\n}";
        funcion.codigo = estructuraParametros + r;
        listaFunciones[nombre] = funcion;
    }
    return nombre;
}
/**************************************************************************************/
int main()
{
    ifstream in("main.newt"); // Open for reading
    string s;
    string rr = "";
    string funcionActual = "";
    int linea = 1, nivel = 0, velo;
    // analiza el prog linea por linea
    while (getline(in, s))
    {
        //elimina los caractaeres al inicio de las linea
        while (s.at(0) == ' ')
            s.erase(0, 1);
        // recoloca la estructura
        smatch m, m2;
        string nivelStr = "", salidaStr = "";
        int h = 0;
        for (int i = 0; i < nivel; i++)
            nivelStr += "\t";

        /************************************************************************************************************************************************/
        // Evalua lineas de codigo y va creado estructura
        /************************************************************************************************************************************************/
        // si es una funcion
        if (regex_match(s, m, functionReg))
        {
            salidaStr += "Funcion encontrada :" + s + "\n";
            funcionActual = Analiza_Funcion(s);
        }
        /************************************************************************************************************************************************/
        // Evalua valores de retorno
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
        // si es una llamada a una funcion
        if (regex_match(s, m, callReturnFunctionReg))
        {
            salidaStr += "Llamada a Funcion con retorno :" + s + ":\t" + to_string(linea) + "\n";
        }
        if (regex_match(s, m, callVoidFunctionReg))
        {
            salidaStr += "Llamada a Funcion sin retorno :" + s + ":\t" + to_string(linea) + "\n";
        }
        /************************************************************************************************************************************************/
        // si encuentra un Arreglo
        if (regex_match(s, m2, arrayReg))
        {
            salidaStr += "Asignacion de array:" + s + ":\t" + to_string(linea) + "\n";
        }
        // si encuentra una cadena de caracteres
        if (regex_match(s, m2, stringReg))
        {
            salidaStr += "Asignacion de Cadena de Caracteres:" + s + ":\t" + to_string(linea) + "\n";
        }
        // si encuentra un Entero
        if (regex_match(s, m2, intReg))
        {
            salidaStr += "Asignacion de Entero:" + s + ":\t" + to_string(linea) + "\n";
        }
        // si encuentra un punto flotante
        if (regex_match(s, m2, floatReg))
        {
            salidaStr += "Asignacion de punto flotante:" + s + ":\t" + to_string(linea) + "\n";
        }
        // si encuentra un punto Doble flotante
        if (regex_match(s, m2, dobleFloatReg))
        {
            salidaStr += "Asignacion de punto flotante doble:" + s + ":\t" + to_string(linea) + "\n";
        }
        /************************************************************************************************************************************************/
        // Evalua si entra o sale de un bloque de codigo
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
        // cout << s << "\n";
        linea++;
    }
    /************************************************************************************************************************************************/
    // muestra lista de funciones encontradas
    for (auto i = listaFunciones.begin(); i != listaFunciones.end(); i++)
    {
        cout << i->second.nombre << endl;
        cout << i->second.codigo << endl;
    }
    /************************************************************************************************************************************************/
    // todo

    /************************************************************************************************************************************************/
    // muestra analisis del codigo
    // cout << rr << endl
    //      << "end." << endl;
}
