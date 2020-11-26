#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include "Pila.h"


float const PI=3.1415926536; //declaracion del valor PI

//funcion que regresa una pila con los puntos para dibujar una linea
Pila hacerLinea(int Xi, int Yi, int Xf, int Yf){
    Pila pi;
    int dx, dy, p;
    bool b = true;
    bool d = false;
	if((Xf<Xi & Yf>Yi)|(Xf>Xi & Yf<Yi & (Yf-Yi)<0 & (Xf-Xi)<0)|(Xf<Xi & Yf<Yi)|(Xf==Xi & Yf<Yi)|(Yi==Yf & Xi>Xf )){
		int t1 = Xi; 		int t2 = Yi;
		Xi = Xf;	Yi = Yf;	Xf = t1;	Yf = t2;
	}
	int aY = Yf -Yi;
	int aX = Xf -Xi;
	if(aY >0 & aX > 0 & aY > aX | aX == 0){
		int t1 = Xi;	int t2 = Xf;
		Xi = Yi;	Yi = t1;	Xf = Yf;	Yf = t2;
		b = false;
	}
	else if(aY < 0 & aX > 0 & aY < aX & (aY/aX)<=-1){
		int t1 = Xi;	int t2 = Yi;
		Xi = Yf;		Yi = Xf;		Xf = t2;		Yf = t1;
		b = false; 		d = true;
	}
	else if(aY < 0 & aX > 0 & aY < aX & (aY/aX)>-1){    d = true;	}

    dx=abs(Xf-Xi);
    dy=abs(Yf-Yi);
	p=(2*dy)-dx;
	if(b){   pi.push(Xi,Yi);       }
	else {   pi.push(Yi,Xi);       }
	while(Xi<Xf ){
        if(p<0){
            Xi=Xi+1;
            p=p+2*dy;
        }
        else if(p>=0){
            Xi=Xi+1;
            if(!d){ 	Yi=Yi+1; }
			else {	    Yi=Yi-1; }
            p=p+2*(dy-dx);
        }
        if(b){   pi.push(Xi,Yi);       }
        else {   pi.push(Yi,Xi);       }
    }
    return pi;
}

//funcion que regresa una pila con los puntos pra dibujar un circulo
Pila hacerCirculo(int xc, int yc, int r){

    Pila pi;
    int x = 0;
    double yr = r;
    int y = r;
    while (x < yr){
        pi.push((xc + x),(yc + y));
        pi.push((xc - x),(yc - y));
        pi.push((xc - x),(yc + y));
        pi.push((xc + x),(yc - y));

        pi.push((xc + y),(yc + x));
        pi.push((xc - y),(yc - x));
        pi.push((xc - y),(yc + x));
        pi.push((xc + y),(yc - x));
        x = x + 1;
        yr = sqrt(r*r-x*x);
        y = (int)round(yr);
    }
    pi.push((xc + x),(yc + y));
    pi.push((xc - x),(yc - y));
    pi.push((xc - x),(yc + y));
    pi.push((xc + x),(yc - y));
    return pi;
}

//funcion que realiza la traslacion a un punto x,y y regresa una pila con los nuevos puntos
Pila traslacion(int t [], Pila pila){
    Pila& p = pila;
    Pila temp;
    int x = t[0], y = t[1];
    int * a = new int[2];

    while(!p.estaVacia()){
      a = p.pop();
      temp.push((a[0]+x),(a[1]+y));
    }
    return temp;
}

//funcion que disminuye o aumneta el tamaño de una figura y regresa los nuevos puntos en una pila
//vector de escalado, pila origen, punto de referencia
Pila escalado(int s[],Pila pila,int xc, int yc){
  Pila& p = pila;
  Pila temp;
  int x = s[0], y = s[1];
  int xp,yp;
  int * a = new int[2];
  while(!p.estaVacia()){
        a = p.pop();
        xp=xc+x*(a[0]-xc);
        yp=yc+y*(a[1]-yc);
        temp.push(xp,yp);
    }
  return temp;
}

//funcion que realiza la rotacion de una figura y lo regresa en una pila
//grados al rotar, pila de puntos en original,punto de referencia
Pila rotacionge(int grados,Pila pila,int xc,int yc){
    Pila& p= pila;
    int *a= new int[2];
    Pila temp;
    int xp,yp;
    while(!p.estaVacia()){
       a=p.pop();
       xp=xc+(a[0]-xc)*cos(grados*PI/180)-(a[1]-yc)*sin(grados*PI/180);
       yp=yc+(a[0]-xc)*sin(grados*PI/180)+(a[1]-yc)*cos(grados*PI/180);
       temp.push(xp,yp);
    }
   return temp;
}

//pinta los puntos de una pila que recibe segun el color que recibe
//pila con los puntos,color
void paint(Pila pila, int color){
    Pila& p = pila;
    int * a = new int[2];
    while(!p.estaVacia()){
        a = p.pop();
        putpixel((a[0]),(a[1]),color);
    }
}

//añadir putos de una pila origen a una destino para realizar solo una
//pila de origen , pila destino
void juntaPilas(Pila o,Pila& d){
    int * a = new int[2];
    while(!o.estaVacia()){
        a = o.pop();
       d.push(a[0],a[1]);
    }
}

//crar un pixel de 3x3 segun el punto de referencia
//punto de referencia
Pila cuadropixel(int x, int y){
    Pila p1;
    juntaPilas(hacerLinea(x,y,x+2,y),p1);
    juntaPilas(hacerLinea(x,y-1,x+2,y-1),p1);
    juntaPilas(hacerLinea(x,y-2,x+2,y-2),p1);
    return p1;
}

void cuadropixel2(int x, int y,int colo){
    paint(hacerLinea(x,y,x+2,y),colo);
    paint(hacerLinea(x,y-1,x+2,y-1),colo);
    paint(hacerLinea(x,y-2,x+2,y-2),colo);
}
//pinta de negro la figura y repinta en otra posicion
//pila de puntos
void borra(Pila pila){
    Pila& p = pila;
    int * a = new int[2];
    while(!p.estaVacia()){
        a = p.pop();
        putpixel((a[0]),(a[1]),BLACK);
    }
}

//realiza circulo pintando directamente
void hacerCirculo2(int xc, int yc, int r,int colorc){
    int x = 0;
    double yr = r;
    int y = r;
    while (x < yr){
       putpixel(xc + x,yc + y,colorc);
       putpixel(xc - x,yc - y,colorc);
       putpixel(xc - x,yc + y,colorc);
       putpixel(xc + x,yc - y,colorc);
       putpixel(xc + y,yc + x,colorc);
       putpixel(xc - y,yc - x,colorc);
       putpixel(xc - y,yc + x,colorc);
       putpixel(xc + y,yc - x,colorc);
        x = x + 1;
        yr = sqrt(r*r-x*x);
        y = (int)round(yr);
    }
       putpixel(xc + x,yc + y,colorc);
       putpixel(xc - x,yc - y,colorc);
       putpixel(xc - x,yc + y,colorc);
       putpixel(xc + x,yc - y,colorc);

}



