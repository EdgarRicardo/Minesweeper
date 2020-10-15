#include "buscaminasmatriz.h"

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

    ///Asignancion memoria a las matrices
    matriz=new int*[filas];
    casillasPrendidas=new bool*[filas];
    for (int i = 0; i < filas; ++i){
        matriz[i] = new int[columnas];
        casillasPrendidas[i] = new bool[columnas];
    }
}

int Buscaminas::getValorIJ(int i, int j) const{
    if(i>filas || j>columnas) throw BuscaminasException("Dato innexistente");
    else if(matriz[i][j]>10) return 10;
    else return matriz[i][j];
}

Buscaminas::~Buscaminas(){
    ///Liberacion memoria de las matrices
    for (int i = 0; i < filas; ++i){
           delete [] matriz[i];
            delete [] casillasPrendidas[i];
    }
    delete [] matriz;
    delete [] casillasPrendidas;
}

void Buscaminas::iniciarMatriz(){
    int i=0,j=0;
    int numeroBombas=this->numeroBombas();
    srand (time(nullptr));

    ///Todos los elementos des las matrice a 0
    for(i=0;i<filas;i++)
        for(j=0;j<columnas;j++){
            matriz[i][j]=0;
            casillasPrendidas[i][j]=false;
        }

   ///Colocar Bombas
   while(numeroBombas>0){
       i=rand() % (filas);
       j=rand() % (columnas);
       if(matriz[i][j]==0){
           matriz[i][j]=10; ///10 representa a una bomba
           numeroBombas--;
       }
   }

   ///Colocar numero de bombas alrededor de una casilla
       ///Todo numero superior o igual a 10  representa a una bomba
   int filas2=filas-1;
   int columnas2=columnas-1;
   for(i=0;i<filas;i++){
       for(j=0;j<columnas;j++){
             if(matriz[i][j]>=10){

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

void Buscaminas::recursividadAbrirCasillas(int i,int j){
    if(i>=filas || i<0 || j>=columnas || j<0 || casillaPrendida(i,j) || getValorIJ(i,j)>0) return;
    prenderCasilla(i,j);

    recursividadAbrirCasillas(i+1,j+1);
    recursividadAbrirCasillas(i-1,j-1);

    recursividadAbrirCasillas(i+1,j);
    recursividadAbrirCasillas(i,j+1);

    recursividadAbrirCasillas(i-1,j);
    recursividadAbrirCasillas(i,j-1);

    recursividadAbrirCasillas(i+1,j-1);
    recursividadAbrirCasillas(i-1,j+1);
}


