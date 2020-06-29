#include <iostream>
using namespace std;

makeGrid(string slots[]){
slots[0] = "|___|";
slots[1] = "|___|";
slots[2] = "|___|";
slots[3] = "|___|";
slots[4] = "|___|";
slots[5] = "|___|";
slots[6] = "|___|";
slots[7] = "|___|";
slots[8] = "|___|";
}

makeInitial(string ini[]){
  ini[0] = "| 1 |";
  ini[1] = "| 2 |";
  ini[2] = "| 3 |";
  ini[3] = "| 4 |";
  ini[4] = "| 5 |";
  ini[5] = "| 6 |";
  ini[6] = "| 7 |";
  ini[7] = "| 8 |";
  ini[8] = "| 9 |";
  cout << endl << "Click number to place marker" << endl << endl;
}

printInitial(string ini[]){
  for(int i = 0; i < 9; i += 3){
    cout << ini[i] << ini[i+1] << ini[i+2] << endl;
  }
}

alternate(int alt){
  int alter;
  if(alt % 2 == 0){
    alter = 1;
  }
  else{
    alter = 2;
  }
  return alter;
}

getInput(int alter, string slots[]){
  int input;
  if(alter == 1){
    cout << endl << "It is X's turn - ";
    cin >> input;
  }
  if(alter == 2){
    cout << endl << "It is O's turn - ";
    cin >> input;
  }
  while(slots[input - 1] == "| X |" || slots[input - 1] == "| O |"){
    cout << "That spot has been taken. Try again. ";
    cin.clear();
    cin.ignore(100, '\n');
    cin >> input;
  }
  cout << endl;
  return input;
}

process(int input, string slots[], int alter){
  for(int i = 0; i < 9; i++){
    if(input == i + 1){
      if(alter == 1){
        slots[i] = "| X |";
      }
      if(alter == 2){
        slots[i] = "| O |";
      }
    }
  }
}

printGrid(string slots[]){
  for(int i = 0; i < 9; i += 3){
    cout << slots[i] << slots[i+1] << slots[i+2] << endl;
  }
}

checkFinish(string slots[]){
  int fin = 0;
  for(int i = 0; i < 9; i += 3){
    if(slots[i] == "| X |" && slots[i+1] == "| X |" && slots[i+2] == "| X |"){
      fin = 1;
    }
    if(slots[i] == "| O |" && slots[i+1] == "| O |" && slots[i+2] == "| O |"){
      fin = 2;
    }
  }
  for(int x = 0; x < 3; x++){
    if(slots[x] == "| X |" && slots[x+3] == "| X |" && slots[x+6] == "| X |"){
      fin = 1;
    }
    if(slots[x] == "| O |" && slots[x+3] == "| O |" && slots[x+6] == "| O |"){
      fin = 2;
    }
  }
  for(int y = 0; y <= 2; y+=2){
    if(slots[y] == "| X |" && slots[4] == "| X |" && slots[-y + 8] == "| X |"){
      fin = 1;
    }
    if(slots[y] == "| O |" && slots[4] == "| O |" && slots[-y + 8] == "| O |"){
      fin = 2;
    }
  }             //0-4-8       2-4-6
  return fin;
}

int main(){
  string slots[9];
  string ini[9];
  makeInitial(ini);
  printInitial(ini);
  makeGrid(slots);
  int alt = 0;
  int finish = 0;
  while(finish == 0 && alt < 9){
    int alter = alternate(alt);
    int input = getInput(alter, slots);
    process(input, slots, alter);
    printGrid(slots);
    finish = checkFinish(slots);
    alt++;
  }
  if(finish == 1){
    cout << endl << "X has won!";
  }
  else if(finish == 2){
    cout << endl << "O has won!";
  }
  else{
    cout << endl << "Draw!";
  }
  return 0;
}
