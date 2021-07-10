#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;
struct Sdime_a_ve_Array_1
{
    /* data */
    string e1 = "";
    string e2 = "";
    int e3 = 0;
    float e4 = 0.0f;
};
struct Sdime_a_ve_Array_2
{
    /* data */
    string e1 = "";
    string e2 = "";
    int e3 = 0;
    int e4 = 0;
    int e5 = 0;
    string e6[2];
};
struct rututu_klk_Array_parametro_1
{
    /* data */
    string a1 = "";
    float a2 = 0.0f;
};
struct rututu_klk_Array_parametro_2
{
    /* data */
    int a1 = 0;
    float a2 = 0.0f;
    int a3 = 0;
    int a4 = 0;
};
struct rututu_klk_Args
{
    /* data */
    string para1 = "";
    float para2 = 0.0f;
    int paeya = 0;
    rututu_klk_Array_parametro_1 parametro_call1;
    rututu_klk_Array_parametro_2 parametro_call2;
};
struct rututu_klk_returns
{
    /* data */
    int r1 = 0;
    string r2 = "";
};
const char *NewLine = "\n";
rututu_klk_returns rututu_klk(rututu_klk_Args Args)
{
    rututu_klk_returns r;
    Sdime_a_ve_Array_1 dime_a_ve = {"Wi wichu a meri chisma", "Hola que talis", 5, 200.544};
    printf(
        "%s,%s,%i,%f %s",
        dime_a_ve.e1.c_str(),
        dime_a_ve.e2.c_str(),
        dime_a_ve.e3,
        dime_a_ve.e4,
        NewLine);
    Sdime_a_ve_Array_2 dime_a_ve2 = {"el gallo lester", "Hola de lo mio", 25, 88, 99, {"as", "li"}};
    printf(
        "%s,%s,%i,%i,%i,[%s,%s] %s",
        dime_a_ve2.e1.c_str(),
        dime_a_ve2.e2.c_str(),
        dime_a_ve2.e3,
        dime_a_ve2.e4,
        dime_a_ve2.e5,
        dime_a_ve2.e6[0].c_str(),
        dime_a_ve2.e6[1].c_str(),
        NewLine);
    //print:[parametro,NewLine],
    if (Args.para1 == "si")
    {
        r.r1 = 5;
    }
    else if (Args.para1 == "no")
    {
        r.r1 = 2;
    }
    else
    {
        r.r2 = "baje con trensa";
    }
    return r;
}
int main()
{
    const char saludo[] = "hola que tal";
    int r = rututu_klk({"no", 0.0f, 0, {"hola", 0.5f}, {0, 0.0f, 0, 0}}).r1;
    int r2 = rututu_klk({"si", 8.5f, 23, {"", 0.0f}, {1, 1.01, 5, 8}}).r1;
    string r3 = rututu_klk({"no cojo de esa", 0.0f, 0, {"", 0.0f}, {0, 0.0f, 0, 0}}).r2;
    printf("%i klk %i %s %s", r, r2,r3.c_str(), NewLine);
    if ((r == r2 && r == 5) || r == 1 || r == 2 || r == 8 || r == 4)
    {
        printf("wa chaval");
    }
    else if (r != 24 || r != 25 || r != 45)
    {
        printf("no 24 chaval");
    }
    else
    {
        printf("no ninguno chaval");
    }
}