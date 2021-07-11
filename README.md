New programing language csim
es un lenguaje de programacion en proceso de definicion

El objetivo es tener un lenguaje tan poderoso como c++ pero mas facil de escribir que se parece a json , su nombre no esta aun definido de momento tiene el nombre temporal de csim.

Algunas de sus caracteristicas son:

* los nombres de varibles y funciones pueden incluir espacios
* el tipo de una varible esta definida por el primer valor que se le asigna
* el pipo de variable puede cambiar
* compila a c++ , en el futuro compilara a lenguaje ensamblador
* el codigo en c++ es compacto, facil y humanamente legible, nada de runtime 
* la asignacion de valor a una variable se hace con ":"
* la comparacion de igualdad usa el signo de "=" una sola vez
* permite comparar varibles de tipos de datos diferentes por ejemplo "0"=0.0f 
* en una avaluacion logica "," es AND, ";" es OR y la negacion es "not"
* permite comparar o buscar en un array con la palabra "in"
* en lugar de usar "for(i=0;i < 10; i++ ){/* bloque codigo*/}" se usa "var[0..9]{## bloque codigo ##}"
* usa "#" para comentario de una linea y "##" para comenrario por bloque
* una fucion puede retornar diferentes tipo de valores  
* como todo buen lenguaje de uso general permite variables globales

tipos de datos nativos
    String,
    Integer,
    Float,
    Double,
    Array

palabras reservadas
	"main",
	"print",
	"if",
	"else",
	"retun",
	"in",
	"not",
	"type of"

Todo esto esta sujeto a cambio a medida que el proyecto madure

this is a new programing languaje based on c++ but far more easy that looks like JSON, has no named jet , a temporary name is csim but will change in the future
refc
this is how looks now

{
    NewLine:"\n", 
    funcion de prueva( para1:"",para2:0.0f,paeya:0,parametro:[]){
        variable numero 1:["Hello world","Hola que tal",5,200.544],
        print(variable numero 1,NewLine),
        variable numero 1:["el gallo lester","Hola de lo mio",25,88,99,["as","li"]],
        print(variable numero 1,NewLine),
        print(parametro,NewLine),
        if para1="si" {
             return 5
        },
        else para1="no" {
            return 2
        },
        return "baje con trensa"
    },
    main(){
        saludo:"hola que tal",
        a:5,
        b:"a",
        c:0.0f,
        d:0.0d,
        e:(c+d)+a,
        miArray:[24,25,45],
        r:funcion de prueva(para1="no",parametro=["hola",0.5]),
        r2:funcion de prueva("si",8.5f,23,[1,1.01,5,8]),
        r3:funcion de prueva(para1="no cojo de esa"),
        print("$r klk $r2 $r3",NewLine),
        if[r=r2,r=5;r in [1,2,8,4]]:{
            print("r=5 es = r2  o r es 1,2,4 o 8"),
            if[r=5]:{
                print("r=5")
            },
        },
        else[r not in miArray]:{
            print("no 24 ni 25 ni 45 ")
        },
        else:{
            print("r no es = a 1,2,4,5,8,24,25,45")
        }
    }
}