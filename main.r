{
    NewLine:"\n", 
    rututu klk( para1:"",para2:0.0f,paeya:0,parametro:[]){
        dime a ve:["Wi wichu a meri chisma","Hola que talis",5,200.544],
        print(dime a ve,NewLine),
        dime a ve:["el gallo lester","Hola de lo mio",25,88,99,["as","li"]],
        print(dime a ve,NewLine),
        print(parametro,NewLine),
        if[para1="si"]:{
             return 5
        },
        else[para1="no"]:{
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
        r:rututu klk(para1="no",parametro=["hola",0.5]),
        r2:rututu klk("si",8.5f,23,[1,1.01,5,8]),
        r3:rututu klk(para1="no cojo de esa"),
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