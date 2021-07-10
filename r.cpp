#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;
bool buscaDeclarfacionFuncion(string s)
{
    size_t posParentesis = s.find_first_of("(", 0);
    size_t posCierraParentesis = s.find_last_of(")", 0);
    size_t posCorchete = s.find_last_of("{", 0);
}
const char regxFunctionStr[] = ".*\\(*\\)\\{";
const char regxArrStr[] = "[:|,|=|\\s]\\[.*\\]";
// const char regxFunctionStr[]=".+[(].*[)]{";
int main()
{
    regex functionReg(regxFunctionStr, regex::ECMAScript);
    regex arrayReg(regxArrStr, regex::ECMAScript);
    ifstream in("main.r"); // Open for reading
    string s;
    stringstream rr("");
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
            salidaStr +=  "Funcion encontrada :" + nivelStr + s + "\n" + nivelStr;
        }
        if (regex_match(s, m2, arrayReg))
        {
            salidaStr += "Asignacion de array:\n" + s;
        }
        velo = 0;
        if (s.at(0) == '{' || s.at(s.length() - 1) == '{')
        {
            stringstream p("");
            p << "entrada de bloque \t>> : " << linea;
            salidaStr += p.str();
            velo = 1;
        }
        if (s.at(0) == '}')
        {
            stringstream p("");
            p << "salida de bloque \t<< : " << linea;
            salidaStr += p.str();
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
            rr << nivel << ":" << nivelStr << salidaStr << endl;
        }
        size_t pos2puntos = s.find_first_of(":", 0);
        size_t posParentesis = s.find_first_of("(", 0);
        size_t posCierraParentesis = s.find_last_of(")", 0);

        size_t posCorchere = s.find_first_of("[", 0);
        size_t posCierraCorchetes = s.find_first_of("]", 0);
        size_t posComa = s.find_last_of(",", 0);

        bool declaracionFuncion = posParentesis != string::npos && pos2puntos != string::npos && posParentesis < pos2puntos;

        // if(pos2puntos!=string::npos){
        //     string la=s.substr(0,pos2puntos),ra=s.substr(pos2puntos+1);
        //     rr<<"Asignacion :"<<la.c_str()<<" :=: "<<ra.c_str()<<endl;

        // }
        cout << s << "\n"; // ... must add it back
        linea++;
    } ///:~
    cout << rr.str() << endl
         << "end." << endl;
}
/*
//: C02:Scopy.cpp
// Copy one file to another, a line at a time
#include <string>
#include <fstream>
using namespace std;
int main() {
ifstream in("Scopy.cpp"); // Open for reading
ofstream out("Scopy2.cpp"); // Open for writing
string s;
while(getline(in, s)) // Discards newline char
out << s << "\n"; // ... must add it back
} ///:~

*/