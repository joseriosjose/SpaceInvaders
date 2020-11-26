//se importan las librerias necesarias para el funcionamiento del proyecto
//ELAHI GIRON CUETO ,JOSE RIOS JOSE
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>
#include <graphics.h>
#include "personajes.h"
#include <pthread.h>
#include <cstdlib>
#include <time.h>
//definir el numero de hilos
#define NUM_THREADS 8
//definicion de variables
int vidas=3,dow=0,b1=3,b2=3,b3=3,b4=3; //vidas del personaje,veces que bajan los aliens, vidas de las barreras
personaje jugad,linea1[11],linea23[22],linea45[22],navee,bala,balaen; //personaje, arreglos de diferentes tipos de personajes, bala del jugador, bala de enemigo
int golpesnave=0; //acumulador de las veces que le das a la nave boss
int puntaje=0; //acumulador de tu puntuacion
bool game=true; //estado que muestra si estas vivo o si ya perdiste

// declaracion matriz de la plataforma
char platafor[18][19]{
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','0','0','0','0'},
  {'0','0','0','0','2','2','2','2','2','2','2','2','2','2','2','0','0','0','0'},
  {'0','0','0','0','2','2','2','2','2','2','2','2','2','2','2','0','0','0','0'},
  {'0','0','0','0','3','3','3','3','3','3','3','3','3','3','3','0','0','0','0'},
  {'0','0','0','0','3','3','3','3','3','3','3','3','3','3','3','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','z','0','0','0','x','0','0','0','c','0','0','0','v','0','0'},
  {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
  {'0','0','0','0','0','0','0','0','0','5','0','0','0','0','0','0','0','0','0'}
};

//funcion que genera los margenes de la plataforma
void plataforma(){
    //pintar lineas del margen
    paint(hacerLinea(10,10,710,10),WHITE);
    paint(hacerLinea(10,10,10,610),WHITE);
    paint(hacerLinea(10,610,710,610),WHITE);
    paint(hacerLinea(710,610,710,10),WHITE);

    paint(hacerLinea(6,6,714,6),WHITE);
    paint(hacerLinea(6,6,6,614),WHITE);
    paint(hacerLinea(6,614,714,614),WHITE);
    paint(hacerLinea(714,614,714,6),WHITE);

    settextstyle(GOTHIC_FONT, HORIZ_DIR, 5); //definir un estilo de texto
    //escribir en pantalla el titulo
    outtextxy(770,70,"SPACE");
    outtextxy(720,110,"INVADERS");

    paint(hacerLinea(720,160,1070,160),WHITE);
    //definir estilos de texto y dibujar en pantalla las leyendas
    settextstyle(GOTHIC_FONT, HORIZ_DIR,1);
    outtextxy(720,220,"PUNTAJE:");
    settextstyle(GOTHIC_FONT, HORIZ_DIR,1);
    outtextxy(720,290,"VIDAS:");
}

//metodo que genera las barreras en forma de circulo
void barreras(int h){
    //crea una barrera dependiendo de cual es

    if(h==1){
        for(int i=1;i<20;i++){
        //si es la primer barrera la crea en la posicion
        hacerCirculo2(115,530,i,WHITE);
    }
    }else if(h==2){
    for(int i=1;i<20;i++){
            //si es la segunda barrera la crea en la posicion
        hacerCirculo2(275,530,i,WHITE);
    }
    } else if(h==3){
    for(int i=1;i<20;i++){
        //si es la tercer barrera la crea en la posicion
        hacerCirculo2(435,530,i,WHITE);
    }
    } else if(h==4){
    for(int i=1;i<20;i++){
        //si es la cuarta barrera la crea en la posicion
        hacerCirculo2(595,530,i,WHITE);
    }
    }

}
//metodo que lee la matriz y la dibuja creando los personajes segun su estado **estos estados son para que los enemigos muevan las manos
void pintar_plataforma(bool estados_){
  //pinta todo lo que esta en el area de juego de negro para no dejar una especie de residuos
  setfillstyle(USER_FILL,0);
  bar(12,40,710,610);
//declaricion de la posiciones en x y en y
  int xc=-60,xtemp=xc;
  int yc=5;
  //declaracion de un contador para rellenar los arreglos de enemigos
  int cl1=0,cl23=0,cl45=0;
  bool forma=estados_; //estado para que el enemigos mueva las manos
//mediante 2 ciclos for se lee la matriz
 for(int f=0;f<18;f++){
    xc=xtemp; //cada salto de fila se reinicia el valor en x
   for(int g=0;g<19;g++){
        //dependiendo de la asignacion en la matriz pinta un personaje segun su tipo y suma a x un 40 para que queden separados
     if(platafor[f][g]=='1'){       linea1[cl1] = personaje(1,1,xc,yc,forma) ;
                             xc=xc+40;
                             cl1++;
     }else if(platafor[f][g]=='2'){  linea23[cl23] = personaje(2,2,xc,yc,forma) ;
                             xc=xc+40;
                             cl23++;
     }else if(platafor[f][g]=='3'){  linea45[cl45] = personaje(3,3,xc,yc,forma) ;
                             xc=xc+40;
                             cl45++;
     }else if(platafor[f][g]=='4'){  navee = personaje(4,4,xc,yc,true) ;
                                     if(golpesnave==3){navee.morirboos();}
                             xc=xc+40;
     }else if(platafor[f][g]=='5'){  jugad = personaje(5,14,xc,yc,true) ;
                             xc=xc+40;
     }else if(platafor[f][g]=='b'){  bala = personaje(7,14,xc,yc,true) ;
                             xc=xc+40;
     }else if(platafor[f][g]=='e'){  balaen = personaje(8,15,xc,yc,true) ;
                             xc=xc+40;
     }else if(platafor[f][g]=='z'){
                                    barreras(1); //crea la primer barrera
                             xc=xc+40;
     }else if(platafor[f][g]=='x'){
                                    barreras(2); //crea la primer barrera
                             xc=xc+40;
     }else if(platafor[f][g]=='c'){
                                    barreras(3); //crea la primer barrera
                             xc=xc+40;
     }else if(platafor[f][g]=='v'){
                                    barreras(4); //crea la primer barrera
                             xc=xc+40;
     }else if(platafor[f][g]=='0') { xc=xc+40; //cuando es un cero solo recorre el valor de la x
   }
                             }
    yc=yc+35;  //se baja el valor de la y en cada fila

    }

}

//metodo que verifica si matamos a todos los enemigos
bool verifcabaenemigos(){
    //recorro la matriz y si ya no hay enemigos 1,2,3 regreso un true
   for(int i=0;i<18;i++){
    for(int j=0;j<19;j++){
        if(platafor[i][j]=='1' || platafor[i][j]=='2' || platafor[i][j]=='3'){
            return false;
        }} }
  return true;
}

//metodo que actualiza la vida, el puntaje y verifica si ganas o pierdes
void puntajeyvida(){
    //convetir el acumulador de puntaje a un arreglo de char
  std::string cadena ="";
  cadena = static_cast<std::ostringstream*>(&(std::ostringstream() << puntaje))->str();
   char* cadepuntos;
   cadepuntos = (char *)cadena.c_str();
  //convertir el acumulador de vidas en un arreglo de char
   std::string cadena2 ="";
  cadena2 = static_cast<std::ostringstream*>(&(std::ostringstream() << vidas))->str();
   char* cadevidas;
   cadevidas = (char *)cadena2.c_str();
     //escribir el puntaje que tenemos
    settextstyle(GOTHIC_FONT, HORIZ_DIR,1);
    outtextxy(900,220,cadepuntos);
    //escribir las vidas que tenemos
    settextstyle(GOTHIC_FONT, HORIZ_DIR,1);
    outtextxy(870,290,cadevidas);
    //verificar si ya no tenemos vidas o si los enemigos ya llegaron al limite
    if(vidas==0 || dow==7){
      game=false; //perder si te matan 3 veces o bajaron mucho
      settextstyle(GOTHIC_FONT, HORIZ_DIR,4);
      outtextxy(750,400,"GAME OVER"); //escribir game over
    }
    //si ya golpeamos el boss 3 veces o matamos a todos
    if(golpesnave==3 || verifcabaenemigos()){
        game=false; //ganar si golpeas a la nave 3 veces
      settextstyle(GOTHIC_FONT, HORIZ_DIR,4);
      outtextxy(750,400,"GANASTE!!!");//escribir ganaste
    }
}
//funcion que genera disparos aleatoreos
void disparaenemigos(){
  //recorrer la matriz solo en la filas
    for(int w=0;w<18;w++){
      //genera un numero aleatoreo para decidir que enemigo dispara
       srand( time( NULL ) );
       int numero = rand() % 19;
          //verifica que solo pueda disparar los enemigos que estan en la parte inferior
          if(platafor[w][numero]=='1' && platafor[w+1][numero]=='0' ){
             platafor[w+1][numero]='e';//modifica la matriz colocando un simbolo de bala abajo del anemigo
          }else if(platafor[w][numero]=='2' && platafor[w+1][numero]=='0'){
             platafor[w+1][numero]='e';
          }else if(platafor[w][numero]=='3' && platafor[w+1][numero]=='0'){
             platafor[w+1][numero]='e';
          }

    }

}

//SABER SI HAY UNA BALA EN EL TABLERO
bool verifcabalaspersona(){
    //recorre la matriz
   for(int i=0;i<18;i++){
    for(int j=0;j<19;j++){
        if(platafor[i][j]=='b'){ //si hay una bala retorna falso, sirve para que solo puedas disparar una bala a la vez
            return false;
        }} }
  return true;
}

//mover el grupo de enemigos hacia abajo
void movdow(){
dow++; //modifica el contador de veces que baja para llevar el control
Sleep(110); //duerme el hilo 110 ms
//recorre la matriz de abajo hacia arriba
     for(int l=18;l>0;l--){
            for(int v=19;v>0;v--){
                    //donde este un enemigo lo asigna a la parte de abajo
                 if(platafor[l][v]=='3'){
                    platafor[l+1][v]='3';
                 }else if(platafor[l][v]=='2'){
                    platafor[l+1][v]='2';
                 }else if(platafor[l][v]=='1'){
                     //con los enemigos que estan hasta arriba borra la linea de arriba y la pasa abajo
                    platafor[l][v]='0';
                    platafor[l+1][v]='1';
                 }
     }}
}
//mover el grupo de enemigos hacia la derecha,izquierda
void movergrupo(int e_,int f_){
  int e=e_,f=f_;
  //recorre la matriz
  for(int veces=0;veces<e;veces++){
    for(int l=18;l>=0;l--){
          Sleep(150); //duerme el hilo
        for(int p=19;p>=0;p--){
          //donde esta un enemigo lo mueve hacia la derecha y la borra de su punto original
            if(platafor[l][p-1]=='1'){
               platafor[l][p-1]='0';
               platafor[l][p]='1';
            }else if(platafor[l][p-1]=='2'){
               platafor[l][p-1]='0';
               platafor[l][p]='2';
            }else if(platafor[l][p-1]=='3'){
               platafor[l][p-1]='0';
               platafor[l][p]='3';
            }}}
}
//mandar a llamar el metodo de mover hacia abajo
movdow();
//mueve de la misma manera lso enemigos pero ahora hacia la izquierda
for(int veces=0;veces<f;veces++){
 for(int l=0;l<19;l++){
      Sleep(150);
        for(int p=0;p<19;p++){

            if(platafor[l][p]=='1'){
               platafor[l][p]='0';
               platafor[l][p-1]='1';
            }else if(platafor[l][p]=='2'){
               platafor[l][p]='0';
               platafor[l][p-1]='2';
            }else if(platafor[l][p]=='3'){
               platafor[l][p]='0';
               platafor[l][p-1]='3';
            }}}}
movdow();//baja una fila
movergrupo(6,f);//se vuelva a ejecutar para que lo haga las veces necesarias hasta que pierdas o ganes
}
//funcion que mueve el boss
void movernave(){
    //recorre la matriz
 for(int d=19;d>1;d--){
        Sleep(300);//duerme el hilo
    if(platafor[1][d]=='4'){  //donde encuentre una nave la pasa hacia la izquierda y la borra en matriz del punto inicial
            platafor[1][d]='0';
            platafor[1][d-1]='4';}}
  //si ya llego al final de la matriz recoloca una nave para cuando sea necesario ya esta en la matriz
   platafor[1][1]='0';
   platafor[1][19]='4';
}
//realizar el movimiento y choque de las balas del jugador
void mover_bala(){
   //recorre la matriz
  for(int i=0;i<18;i++){
  Sleep(10);
        for(int j=0;j<19;j++){
            if(platafor[i][j]=='b'){
               platafor[i][j]='0';
                if(platafor[i-1][j]!='1' && platafor[i-1][j]!='2' && platafor[i-1][j]!='3'){  //si no es un enemigo normal
                           if(platafor[i-1][j]=='4'){ //si es el boos
                            golpesnave++;  //suma uno a las veces que le diste al boss
                            puntaje=puntaje+200;  //suma puntaje
                                if(golpesnave==3){ //si es la 3 veces
                                  platafor[i-1][j]='4';//explota en su lugar
                                }else{
                                    platafor[i-1][j]='0';//choque nave
                                }
                           }else if(platafor[i-1][j]=='z' || platafor[i-1][j]=='x' || platafor[i-1][j]=='c'|| platafor[i-1][j]=='v'){//si es una barrera
                                   switch (platafor[i-1][j]){//revisa que barrera es
                               case 'z': b1--; //en caso de ser la barrera 1 le resta uno de vida
                                   if(b1==0){ //si ya no tiene vidas la borras
                                    platafor[i-1][j]='0';
                                   } break;
                               case 'x': b2--;
                                   if(b2==0){
                                    platafor[i-1][j]='0';
                                   }
                                break;
                               case 'c': b3--;
                                   if(b3==0){
                                    platafor[i-1][j]='0';
                                   }
                                break;
                               case 'v': b4--;
                                   if(b4==0){
                                    platafor[i-1][j]='0';
                                   }
                               break;
                                    }
                           }else{
                               platafor[i-1][j]='b';
                           }
                }else {
                    switch (platafor[i-1][j]){ //si el de arriba es un enemigo lo borras y sumas puntaje
                        case '1':puntaje=puntaje+40;  platafor[i-1][j]='0';  break;
                        case '2':puntaje=puntaje+20;  platafor[i-1][j]='0'; break;
                        case '3':puntaje=puntaje+10;  platafor[i-1][j]='0'; break;
                        }
        }}}}
}
//metodo que mueve las balas enemigas
void mover_bala_ene(){
//recorre la matriz
   for(int y=0;y<18;y++){
    Sleep(125);
    for(int f=0;f<19;f++){
            if(platafor[y][f]=='e'){ //donde este una bala enemiga
               if(platafor[y+1][f]=='5'){ //si el de abajo de la bala es el jugador
                platafor[y][f]='0'; //borras la bala
                vidas=vidas-1;//bajas una vida al jugador
                if(vidas==0){ //si ya no tengo vidas
                 platafor[y][f]='0'; //borras la bala
                 platafor[y+1][f]='0'; //y al jugador
                }

               }else if(platafor[y+1][f]=='z' || platafor[y+1][f]=='x' || platafor[y+1][f]=='c' || platafor[y+1][f]=='v'){ //si le da a una barrera
                     switch(platafor[y+1][f]){ //selecciona que barrera es
                        case 'z':  //si es la primer barrera
                            b1--; //le baja uno de vida
                            platafor[y][f]='0'; //borra la bala
                            if(b1==0){  //si la barrera ya no tiene vidas
                              platafor[y+1][f]='0'; //la borras
                            }
                        break;
                        case 'x':
                            b2--;
                            platafor[y][f]='0';
                            if(b2==0){
                              platafor[y+1][f]='0';
                            }
                        break;
                        case 'c':
                            b3--;
                            platafor[y][f]='0';
                            if(b3==0){
                              platafor[y+1][f]='0';
                            }
                        break;
                        case 'v':
                            b4--;
                            platafor[y][f]='0';
                            if(b4==0){
                              platafor[y+1][f]='0';
                            }
                        break;

                     }

               }else {
                   //si no hay nada debajo
                   platafor[y][f]='0';
                   platafor[y+1][f]='e'; //bajas la bala
               }
            }

    }
   }

}

//metodo para un hilo que ejecuta el metodo de mover al grupo
void *HiloPrincipal(void *threadid) {
    movergrupo(4,6);
  pthread_exit(NULL);
}

void *HiloPrincipal2(void *threadid) {
   while(game){
    movernave();
    Sleep(9000);
    }
    pintar_plataforma(false);
  pthread_exit(NULL);
}
//metodo para un hilo que repinte toda la matriz
void *HiloPrincipal3(void *threadid) {
   bool estados=true;
   while(game){
    puntajeyvida();
    Sleep(90);
    pintar_plataforma(estados);
     estados=!estados;
    }

  pthread_exit(NULL);
}

void *HiloPrincipal4(void *threadid) {
   while(game){
   mover_bala();
   }
  pthread_exit(NULL);
}

void *HiloPrincipal5(void *threadid) {
   while(game){
   disparaenemigos();
   }
  pthread_exit(NULL);
}

void *HiloPrincipal6(void *threadid) {
   while(game){
    mover_bala_ene();
   }
  pthread_exit(NULL);
}

//metodo que esta leyendo el teclado y segun la tecla mueve al personaje
void moverpersonaje(){
while(true){
    if(kbhit()){
       char tecla =getch();
        if(tecla==75){
            for(int i=3;i<19;i++){
            if(platafor[17][i]=='5' && i!=2){
                platafor[17][i]='0';
                platafor[17][i-1]='5';
                break;
                }}
      }else if(tecla==77){
        for(int j=2;j<18;j++){
        if(platafor[17][j]=='5'&& j!=19 ){
            platafor[17][j]='0';
            platafor[17][j+1]='5';
            break;
        }}

        }else if(tecla==' '){
           bool esta=verifcabalaspersona();
           for(int i=2;i<19;i++){
            if(platafor[17][i]=='5'&& i!=19 && esta==true){
            platafor[16][i]='b';
            break;
             }}
        }
//cout <<" "<<platafor[17][0]<<" "<<platafor[17][1]<<" "<<platafor[17][2]<<" "<<platafor[17][3]<<" "<<platafor[17][4]<<" "<<platafor[17][5]<<" "<<platafor[17][6]<<" "<<platafor[17][7]<<" "<<platafor[17][8]<<" "<<platafor[17][9]<<" "<<platafor[17][10]<<" "<<platafor[17][11]<<" "<<platafor[17][12]<<" "<<platafor[17][13]<<" "<<platafor[17][14]<<" "<<platafor[17][15]<<" "<<platafor[17][16]<<" "<<platafor[17][17]<<" "<<platafor[17][18]<<endl;

        }

    }
}


main(){
 pthread_t threads[NUM_THREADS];
 int mg,mn,pp,mb,de,mbe,pv;

	int gd = DETECT, gm;
    initwindow(1100,650,"Space",false,true);


    plataforma();//pintas la plataform
    //creas los hilos
    mg =pthread_create(&threads[1], NULL, HiloPrincipal,NULL); //mover grupos
    mn =pthread_create(&threads[2], NULL, HiloPrincipal2,NULL);//mover nave
    pp =pthread_create(&threads[3], NULL, HiloPrincipal3,NULL); //pintar la plataforma
    mb =pthread_create(&threads[4], NULL, HiloPrincipal4,NULL); //mover balas
    de =pthread_create(&threads[5], NULL, HiloPrincipal5,NULL);//disparos enemigos
    mbe =pthread_create(&threads[6], NULL, HiloPrincipal6,NULL); //mover disparos enemigos
    moverpersonaje();  //metodo de mover personaje

	getch();
  	closegraph();
  	pthread_exit(NULL);

}


