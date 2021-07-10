{
    NewLine:"\n", 
    rututu klk( para1:"",para2:0.0f,paeya:0,parametro:[]):{
        dime a ve:["Wi wichu a meri chisma","Hola que talis",5,200.544],
        print:[dime a ve,NewLine],
        dime a ve:["el gallo lester","Hola de lo mio",25,88,99,["as","li"]],
        print:[dime a ve,NewLine],
        print:[parametro,NewLine],
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
        r:rututu klk(para1="no",parametro=["hola",0.5]),
        r2:rututu klk("si",8.5f,23,[1,1.01,5,8]),
        r3:rututu klk(para1="no cojo de esa"),
        print:["$r klk $r2 $r3",NewLine],
        if[r=r2,r=5;r in [1,2,8,4]]:{
            print:"wa chaval"
        },
        else[r not in [24,25,45]]:{
            print:"no 24 chaval"
        },
        else:{
            print:"no ninguno chaval"
        }
    }
}