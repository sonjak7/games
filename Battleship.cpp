#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>
#include <windows.h>
using namespace std;

void printBoard(string board[]){
  for(int i = 0; i < 100; i+=10){
    for(int t = 0; t < 10; t++){
      cout << board[t + i];
    }
    cout << endl;
  }
}

void placeShip(string board[], int shipsize){
  int check = 0;
  int xcor;
  int ycor;
  int cor;
  int orient;
  while(check == 0){
    int temp = 0;
    int tem = 0;
    cout << endl << "Place your " << shipsize << " ship" << endl;
    cout << "X coordinate(1-10): ";
    cin >> xcor;
    cout << "Y coordinate(1-10): ";
    cin >> ycor;
    cor = ((ycor-1) * 10) + (xcor-1);
    cout << "Horizontal(1) or Vertical(2): ";
    cin >> orient;
    if(orient == 1){
      if(shipsize == 2){
        for(int y = 9; y <= 99; y+=10){
          if(y == cor){
            temp = 5;
          }
        }
      }
      else if(shipsize == 3){
        for(int c = 8; c <= 98; c+=10){
          if(c == cor || c+1 == cor){
            temp = 5;
          }
        }
      }
      else if(shipsize == 4){
        for(int r = 7; r <= 97; r+=10){
          if(r == cor || r+1 == cor || r+2 == cor){
            temp = 5;
          }
        }
      }
      else if(shipsize == 5){
        for(int m = 6; m <= 96; m+=10){
          if(m == cor || m+1 == cor || m+2 == cor || m+3 == cor){
            temp = 5;
          }
        }
      }
      if(temp != 5){
        for(int e = cor; e < cor+shipsize; e++){
          if(board[e] != "|   |"){
            temp = 5;
          }
        }
      }
      if(temp == 5){
        check = 0;
        cout << endl;
        cout << "That spot doesn't fit. Try again." << endl;
      }
      else{
        if(shipsize == 2){
          board[cor] = "| 2 |";
          board[cor+1] = "| 2 |";
        }
        else if(shipsize == 3){
          board[cor] = "| 3 |";
          board[cor+1] = "| 3 |";
          board[cor+2] = "| 3 |";
        }
        else if(shipsize == 4){
          board[cor] = "| 4 |";
          board[cor+1] = "| 4 |";
          board[cor+2] = "| 4 |";
          board[cor+3] = "| 4 |";
        }
        else if(shipsize == 5){
          board[cor] = "| 5 |";
          board[cor+1] = "| 5 |";
          board[cor+2] = "| 5 |";
          board[cor+3] = "| 5 |";
          board[cor+4] = "| 5 |";
        }
        check = 1;
      }
    }
    else if(orient == 2){
      for(int m = (110-(shipsize*10)); m <= 99; m++){
        if(m == cor){
          tem = 5;
        }
      }
      if(tem != 5){
        for(int e = 0; e < shipsize; e++){
          if(board[cor+(e*10)] != "|   |"){
            tem = 5;
          }
        }
      }
      if(tem == 5){
        check = 0;
        cout << endl;
        cout << "That spot doesn't fit. Try again." << endl;
      }
      else{
        if(shipsize == 2){
          board[cor] = "| 2 |";
          board[cor+10] = "| 2 |";
        }
        else if(shipsize == 3){
          board[cor] = "| 3 |";
          board[cor+10] = "| 3 |";
          board[cor+20] = "| 3 |";
        }
        else if(shipsize == 4){
          board[cor] = "| 4 |";
          board[cor+10] = "| 4 |";
          board[cor+20] = "| 4 |";
          board[cor+30] = "| 4 |";
        }
        else if(shipsize == 5){
          board[cor] = "| 5 |";
          board[cor+10] = "| 5 |";
          board[cor+20] = "| 5 |";
          board[cor+30] = "| 5 |";
          board[cor+40] = "| 5 |";
        }
        check = 1;
      }
    }
  }
}

void playerShot(int cpukey[], string cpuboard[]){
  int xshot;
  int yshot;
  int shot;
  int check = 0;
  while(check == 0){
    cout << "Pick a spot to fire at" << endl;
    cout << "X coordinate: ";
    cin >> xshot;
    cout << "Y coordinate: ";
    cin >> yshot;
    shot = ((yshot-1) * 10) + (xshot-1);
    if(cpuboard[shot] != "|   |"){
      cout << "You've already picked that spot" << endl;
    }
    else{
      check = 1;
    }
  }
  if(cpukey[shot] == 1){
    cout << "Hit!" << endl << endl;
    cpuboard[shot] = "| X |";
  }
  else{
    cout << "Miss" << endl << endl;
    cpuboard[shot] = "| - |";
  }
}

int cpuShot(string board[]){
  int disp;
  int shot = 0;
  int yshow;
  int xshow;
  int check[100] = {0};
  shot = rand() % 100;
  while(check[shot] == 1){
    shot = rand() % 100;
  }
  check[shot] = 1;
  xshow = shot % 10 + 1;
  yshow = ((shot-(xshow-1))/10)+1;
  cout << "CPU chose: X - " << xshow << " and Y - " << yshow;

  if(board[shot] == "| 2 |" || board[shot] == "| 3 |" ||
    board[shot] == "| 4 |" || board[shot] == "| 5 |"){
    cout << endl << "Hit!" << endl << endl;
    board[shot] = "| X |";
    disp = 1;
  }
  else{
    cout << endl << "Miss" << endl << endl;
  }
  return disp;
}

void cpuShips(int cpukey[], int shipsize){
  int check = 0;
  int xcor;
  int ycor;
  int cor;
  int orient;
  while(check == 0){
    int temp = 0;
    int tem = 0;
    xcor = rand() % 10;
    ycor = rand() % 10;
    cor = ((ycor) * 10) + (xcor);
    orient = rand() % 2;
    if(orient == 0){
      if(shipsize == 2){
        for(int m = 9; m <= 99; m+=10){
          if(m == cor){
            temp = 5;
          }
        }
      }
      else if(shipsize == 3){
        for(int d = 8; d <= 98; d += 10){
          if(d == cor || d+1 == cor){
            temp = 5;
          }
        }
      }
      else if(shipsize == 4){
        for(int u = 7; u <= 97; u += 10){
          if(u == cor || u+1 == cor || u+2 == cor){
            temp = 5;
          }
        }
      }
      else if(shipsize == 5){
        for(int n = 6; n <= 97; n += 10){
          if(n == cor || n+1 == cor || n+2 == cor || n+3 == cor){
            temp = 5;
          }
        }
      }
      for(int w = cor; w < (cor+shipsize); w++){
        if(cpukey[w] != 0){
          temp = 5;
        }
      }
      if(temp == 5){
        check = 0;
      }
      else{
        for(int t = 0; t < shipsize; t++){
          cpukey[cor+t] = 1;
        }
        check = 1;
      }
    }
    else if(orient == 1){
      for(int t = (110 - (shipsize*10)); t <= 99; t++){
        if(t == cor){
          tem = 5;
        }
      }
      for(int v = 0; v < shipsize; v++){
        if(cpukey[cor+(v*10)] != 0){
          tem = 5;
        }
      }
      if(tem == 5){
        check = 0;
      }
      else{
        for(int t = 0; t < (shipsize*10); t+=10){
          cpukey[cor+t] = 1;
        }
        check = 1;
      }
    }
  }
}

int checkFinish(string board[], string cpuboard[]){
  //0 - still going, 1 - user won, 2 - cpu won
  int fin = 0;
  int pcount = 0;
  int ccount = 0;
  for(int h = 0; h < 100; h++){
    if(board[h] == "| X |"){
      ccount += 1;
    }
    if(cpuboard[h] == "| X |"){
      pcount += 1;
    }
  }
  if(ccount == 17){
    fin = 2;
    cout << "CPU has won";
  }
  if(pcount == 17){
    fin = 1;
    cout << "You have won!";
  }
  return fin;
}

int main(){
  cout << "Welcome to battleship!" << endl;
  srand(time(0));
  int finish = 0;
  string board[100];
  int cpukey[100] = {0};
  string cpuboard[100];
  for(int i = 0; i < 100; i++){
    board[i] = "|   |";
    cpuboard[i] = "|   |";
  }

  for(int t = 2; t <= 5; t++){
    placeShip(board, t);
    cpuShips(cpukey, t);
    if(t == 3){
      printBoard(board);
      placeShip(board, 3);
      cpuShips(cpukey, t);
    }
      printBoard(board);
  }

// SHOW CPU BOARD
//   for(int v = 0; v < 100; v+=10){
//     for(int g = 0; g < 10; g++){
//       if(cpukey[g+v] == 1){
//         cout << "| X |";
//       }
//       else{
//         cout << "|   |";
//       }
//     }
//     cout << endl;
//   }

  Sleep(2000);
  cout << endl << endl << endl;

  while(finish == 0){
    int disp = 0;
    cout << "CPU's board" << endl;
    printBoard(cpuboard);
    playerShot(cpukey, cpuboard);
    Sleep(1000);
    finish = checkFinish(board, cpuboard);
    disp = cpuShot(board);
    if(disp == 1){
      Sleep(1500);
      printBoard(board);
      cout << endl << endl;
      Sleep(800);
    }
    Sleep(1500);
    finish = checkFinish(board, cpuboard);
  }

  return 0;
}
