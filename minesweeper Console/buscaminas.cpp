#include "buscaminas.h"

/* 
Definimos el constructor de la clase buscaminas, validando sus campos gracias a la clase BuscaminasException, 
limitamos el numero de filas(30) y columnas(50), asi logramos evitar que la pantalla se sature (se puede lograr
una mejora si ajustamos estos parametros en funcion del tamaño de la pantalla), tambien se limita el porcentaje de
bombas entre 5 y 50%, asi mantenemos un juego agradable. Como usamos variables para el numero de filas y columnas
debemos hacer la asignacion dinamica de memoria correspondiente a la clase Casilla con el fin de simular el tablero
*/

Buscaminas::Buscaminas(int f,int c, int pB){
    if(f>30) throw BuscaminasException("Quieres muchas filas");
    if(c>50) throw BuscaminasException("Quieres muchas columnas");
    if(c<5) throw BuscaminasException("Muy pocas columnas");
    if(f<5) throw BuscaminasException("Muy pocas filas");
    if(pB>50) throw BuscaminasException("Oye tranquilo viejo!!!\nMuchas bombas");
    if(pB<5) throw BuscaminasException("Oye tranquilo viejo!!!\nMuy pocas bombas");
    filas=f;
    columnas=c;
    porcentajeBombas=pB;

    ///Asignancion memoria a las matriz
    matriz=new Casilla*[filas];
    for (int i = 0; i < filas; ++i)
        matriz[i] = new Casilla[columnas];
}

/* 
Esta funcion permite obtener el valor de una casilla del tablero en un punto i,j. Se verifica que este 
punto i,j este dentro del tamaño de tablero
*/
int Buscaminas::getValorIJ(int i, int j) const{
    if(i>filas || j>columnas) throw BuscaminasException("Dato innexistente");
    return matriz[i][j].getVal();
}

/*
Definimos el destructor de la clase Buscaminas. No podemos dejar el destructor por default ya que en el constructor
de dicha clase asigamos memoria dinamicamente simulando un tablero de buscaminas, por ello debemos liberar esa memoria.  
*/
Buscaminas::~Buscaminas(){
    ///Liberacion memoria de las matriz
    for (int i = 0; i < filas; ++i)
        delete [] matriz[i];

    delete [] matriz;
}

/*
Obtenemos el numero de bombas que tendremos en nuestro buscaminas, basandonos en este numero a través de un while colocamos las bombas
de manera aleatoria (representadas por el numero 10), una vez puestas las bombas hacemos un recorrido por el tablero (matriz 
bidimencional de la clase Casilla) y al encontrar un bomba, a las casillas de alrededor les aumentamos su valor en una unidad,
este incremento solo se hara si la casilla a la que se le aumentara su valor esta dentro del tablero, esto se verifica a través
de una serie de ifs
*/
void Buscaminas::iniciarMatriz(){
    int i=0,j=0;
    int numeroBombas=this->numeroBombas();
    srand (time(nullptr));

   ///Colocar Bombas
   while(numeroBombas>0){
       i=rand() % (filas);
       j=rand() % (columnas);
       if(matriz[i][j].getVal()==0){
           matriz[i][j].newVal(10); ///10 representa a una bomba
           numeroBombas--;
       }
   }

   ///Colocar numero de bombas alrededor de una casilla
       ///Todo numero superior o igual a 10  representa a una bomba
   int filas2=filas-1;
   int columnas2=columnas-1;
   for(i=0;i<filas;i++){
       for(j=0;j<columnas;j++){
             if(matriz[i][j].getVal()>=10){

                   if(i!=filas2) matriz[i+1][j]++; 
                   if(i!=0) matriz[i-1][j]++; 

                   if(j!=columnas2) matriz[i][j+1]++;
                   if(j!=0) matriz[i][j-1]++;

                   if(i!=0 && j!=0) matriz[i-1][j-1]++;
                   if(i!=filas2 && j!=0) matriz[i+1][j-1]++;
                   if(i!=0 && j!=columnas2)matriz[i-1][j+1]++;
                   if(i!=filas2 && j!=columnas2)matriz[i+1][j+1]++;

             }
       }
   }
}

/*
Esta es la función principal del juego ya que con ella se simula el funcionamiento del Buscaminas.
Es una funcion recursiva que nos permitira abrir una casilla,
es decir simular que usuario ha elegido esa casilla. Al entrar tenemos una condicion que nos permitira evitar los ciclos
infinitos de la recursividad (verificamos si la casilla ya esta prendida) y verificar que la coordenada i,j a abrir este 
dentro del tablero, si se valida una de las condiciones del if, saldremos inmediatamente de la funcion.
Ahora bien, si tenemos un i,j que aun no ha sido abierto entonces llamamos a la funcion prenderCasilla(i,j) que cambiara
el parametro que nos permite saber si la casilla esta abierta o no, una vez hecho esto agregamos una unidad a nuestra variable que
nos permite saber cuantas casillas ya estan abiertas y que mas adelanta nos ayudara a saber si el usuario ya ha ganado.
Una vez hecho lo anterior, verificamos si el valor de la casilla abierta es mayor a 0, si es el caso salimos de la función (esto tambien
detendra a que función deje de llamarse así misma en algún punto), en caso contrario si la casilla abierta es 0, eso significa 
que debemos abrir tambien las casillas de alrededor por lo la función se llama así misma, pero con los diferentes indices de las
casillas alrededor.   
*/
void Buscaminas::recursividadAbrirCasillas(int i,int j){
    if(i>=filas || i<0 || j>=columnas || j<0 || casillaPrendida(i,j)) return;
    prenderCasilla(i,j);
    numCasillasAbiertas++;

    if(getValorIJ(i,j)>0) return;

    recursividadAbrirCasillas(i+1,j+1);
    recursividadAbrirCasillas(i-1,j-1);

    recursividadAbrirCasillas(i+1,j);
    recursividadAbrirCasillas(i,j+1);

    recursividadAbrirCasillas(i-1,j);
    recursividadAbrirCasillas(i,j-1);

    recursividadAbrirCasillas(i+1,j-1);
    recursividadAbrirCasillas(i-1,j+1);
}

/*
De esta funcion no hay mucho que decir, simplemente nos sirve para darle al usuario una visualización del juego.
Primero imprimimos una linea horizontal para crear un margen. El tamaño de esta linea dependara el numero de columnas  
Despues se imprime una linea vertical para completar el margen y enseguida imprimimos el juego, si la casilla ya ha sido 
prendida, entonces le mostramos el valor de esa casilla al usuario (si es 0 simplemente mostramos un espacio), en caso
contrario imprimemos un caracter especial.
La forma en que se imprime todo esto se hace un forma de matriz simulando el juego. 
*/
void Buscaminas::imprimirMatriz(){
    int i=0,j=0;
    cout<<"   "<<(char)186<<" ";
    //for(j=0;j<columnas;j++) cout<<j<<" ";
    cout<<"\n";
    for(j=0;j<=2.8*columnas;j++){
        if(j==3) cout<<(char)206;
        else cout<<(char)205;
    }
    cout<<"\n";
    for(i=0;i<filas;i++){
        if(i/10>0) cout<<i<<" "<<(char)186<<" ";
        else cout<<i<<"  "<<(char)186<<" ";
        for(j=0;j<columnas;j++){
            if(casillaPrendida(i,j)){
                if (matriz[i][j].getVal()==0 ) cout<<"  ";
                else cout<<matriz[i][j].getVal()<<" ";
            }else{
                cout<<(char)254<<" ";
            }
        }
        cout<<"\n";
    }
}

/*
Esta funcion es parecida a la anterior, lo unico que cambia es que esta sera llamada cuando usuario pierde.
Si el usuario pierde en el juego original podemos ver donde estaban las bombas colocadas y las casillas que ya habiamos abierto, 
esto es lo que simulamos en esta función.
*/
void Buscaminas::verBombas(){
    int i=0,j=0;
    cout<<"   "<<(char)186<<" ";
    //for(j=0;j<columnas;j++) cout<<j<<" ";
    cout<<"\n";
    for(j=0;j<=2.8*columnas;j++){
        if(j==3) cout<<(char)206;
        else cout<<(char)205;
    }
    cout<<"\n";
    for(i=0;i<filas;i++){
        if(i/10>0) cout<<i<<" "<<(char)186<<" ";
        else cout<<i<<"  "<<(char)186<<" ";
        for(j=0;j<columnas;j++){
            if(matriz[i][j].getVal()>=10) cout<<"X ";
            else if(casillaPrendida(i,j)){
                if (matriz[i][j].getVal()==0 ) cout<<"  ";
                else cout<<matriz[i][j].getVal()<<" ";
            }else{
                cout<<(char)254<<" ";
            }

        }
        cout<<"\n";
    }
}




