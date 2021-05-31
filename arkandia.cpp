#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <windows.h>
using namespace std;
//FUNCIONES//
void gotoxy(int x, int y);
void pintarPrincipio();
void pintarBordes();
void pintarFinal();
void verificacionesMapa();
void guardarPuntos();
void mostrarPuntos();
void mostrarNivel();
void verificacionesJug();
void ocultarCursor();
//ESTRUCTURA BOLA//
typedef struct{
  int direccion;
  int x = 0, y = 0;
  char figura = char(184);
}TBola;
//ESTRUCTURA JUGADOR//
typedef struct{
  int x = 0, y = 20;
  char key;
  char figura = char(220);
}TJug;
//GLOBAL SCOPE//
TBola bola;
TJug jug;
const char DERECHA = 'd';
const char IZQUIERDA = 'a';
int nivel = 0;
bool salir = false;
int puntos = 0;
//FUNCION PRINCIPAL MAIN//
int main(){
  srand(time(NULL));

  //PRINCIPIO//
  ocultarCursor();
  pintarPrincipio();
  Sleep(3000);

  bola.x = 40;
  bola.y = 5;
  jug.x = 38;

  bola.direccion = rand()%3;

  while(salir == false){
    system("cls");
    if(puntos >= 1000){nivel = 1;}
    if(puntos >= 2000){nivel = 2;}
    if(puntos >= 5000){nivel = 3;}
    ocultarCursor();
    mostrarPuntos();
    mostrarNivel();
    pintarBordes();

      switch(bola.direccion){
        case 0:bola.x--;bola.y--;break;
        case 1:bola.x++;bola.y--;break;
        case 2:bola.x--;bola.y++;break;
        case 3:bola.x++;bola.y++;break;
      }

      verificacionesMapa();

      gotoxy(bola.x, bola.y);
      cout << bola.figura;
      gotoxy(jug.x, jug.y);
      for(int i = 0; i <= 4; i++){cout << jug.figura;}

      if(salir == true){pintarFinal();}

      if(kbhit()){
        jug.key = getch();
        if(jug.key == IZQUIERDA && jug.x > 2){jug.x-=3;gotoxy(jug.x, 20);cout << jug.figura;}
        if(jug.key == DERECHA && jug.x <= 72){jug.x+=3;gotoxy(jug.x, 20);cout << jug.figura;}
      }

      verificacionesJug();
      Sleep(30);
  }
  guardarPuntos();

  //FINAL//
  system("pause");
  return 0;
}
//CREACION PARA PODER OCULTAR EL CURSOR//
void ocultarCursor(){
  HANDLE hCon;
  hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  cci.dwSize = 50;
  cci.bVisible = FALSE;

  SetConsoleCursorInfo(hCon, &cci);
}
//CREACION DE GOTOXY//
void gotoxy(int x,int y){
     HANDLE hcon;
     hcon = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD dwPos;
     dwPos.X = x;
     dwPos.Y= y;
     SetConsoleCursorPosition(hcon,dwPos);
}
//PINTAR AL PRINCIPIO//
void pintarPrincipio(){
  pintarBordes();
  gotoxy(40, 12);
  cout << "BIENVENIDO AL JUEGO DE LA BOLA";
}
//PINTAR AL FINAL//
void pintarFinal(){
  system("cls");
  gotoxy(40, 12);
  cout << "HAS PERDIDO! TU PUNTUACION ES: " << puntos << "\n";
  Sleep(1000);
}
//PINTAR BORDES//
void pintarBordes(){
  for(int i = 0; i <= 80; i++){
    //ABAJO//
    /*gotoxy(i, 25);
    printf("%c", 205);*/
    //ARRIBA//
    /*gotoxy(i, 0);
    printf("%c", 205);*/
  }
  for(int i = 0; i <= 24; i++){
    //IZQUIERDA//
    /*gotoxy(0, i);
    printf("%c", 186);*/
    //DERECHA//
    gotoxy(80, i);
    printf("%c", 186);
  }
  /*gotoxy(0, 0);
  printf("%c", 201);
  gotoxy(0, 80);
  printf("%c", 187);
  gotoxy(24, 0);
  printf("%c", 200);
  gotoxy(24, 80);
  printf("%c", 188);*/
}
//VERIFICACIONES MAPA//
void verificacionesMapa(){
      if(bola.x == 1 && bola.direccion == 0) {bola.direccion = rand()%3;bola.direccion = 1;puntos += 150;}
      if(bola.x == 1 && bola.direccion == 2) {bola.direccion = rand()%3;bola.direccion = 3;puntos += 150;}
      if(bola.y == 1 && bola.direccion == 1) {bola.direccion = rand()%3;bola.direccion = 3;puntos += 150;}
      if(bola.y == 1 && bola.direccion == 0) {bola.direccion = rand()%3;bola.direccion = 2;puntos += 150;}
      if(bola.y == 23){salir = true;}
      if(bola.x == 79 && bola.direccion == 1){bola.direccion = rand()%3;bola.direccion = 0;puntos += 150;}
      if(bola.x == 79 && bola.direccion == 3){bola.direccion = rand()%3;bola.direccion = 2;puntos += 150;}
      if(jug.x == 79 && jug.key == DERECHA){jug.key = IZQUIERDA;}
      if(jug.x == 1 && jug.key == IZQUIERDA){jug.key = DERECHA;}
}
//GUARDAR PUNTOS EN EL FICHERO//
void guardarPuntos(){
  ofstream ranking;
  /*char fecha[25];
  time_t current_time;
  current_time=time(NULL);
  ctime(&current_time);
  strcpy(fecha, ctime(&current_time));*/

  ranking.open("Ranking.txt", ios::app);
  ranking << puntos << endl;
  ranking.close();
}
//VERIFACIONES JUGADOR//
void verificacionesJug(){
  if((bola.y == jug.y + 1 && bola.x == jug.x) || (bola.y == 19 && bola.x - 1 == jug.x) ||
  (bola.y == 19 && bola.x + 1== jug.x) || (bola.y == jug.y && bola.x == jug.x + 1) ||
  (bola.y == jug.y && bola.x == jug.x + 2) || (bola.y == jug.y && bola.x == jug.x + 3) ||
  (bola.y == jug.y && bola.x == jug.x + 4)){

    if(bola.direccion == 2){bola.direccion = 0;}
    if(bola.direccion == 3){bola.direccion = 1;}
  }
}
//MOSTRAR LOS PUNTOS A LA DERECHA DEL MAPA
void mostrarPuntos(){
  gotoxy(82, 0);
  cout << "PUNTOS: " << puntos;
}
//MOSTRAR EL NIVEL A LA DERECHA DEL MAPA
void mostrarNivel(){
  gotoxy(82, 1);
  cout << "NIVEL: " << nivel;
}
