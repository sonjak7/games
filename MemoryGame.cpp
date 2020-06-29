#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

getLevel(){
  int levels;
  cout << "How many levels do you want? ";
  cin >> levels;
  return levels;
}

getDifficulty(){
  int diff;
  cout << "Select difficulty - Easy(1)  Medium(2)  Hard(3) : ";
  cin >> diff;
  return diff;
}

displayLevel(int levels, int curr){
  for(int i = levels; i > 0; i--){
    cout << endl;
    if(i == curr){
      cout << "| X |" << endl;
    }
    else{
      cout << "| _ |" << endl;
    }
  }
  cout << endl;
}

transition(){
  char pass;
  cout << "You have 5 seconds to remember the numbers. ";
  cout << "Press S to show numbers. ";
  cin >> pass;
  cout << endl;
}

generate(int answer[], int diff){
  for(int i = 0; i < diff + 2; i++){
    answer[i] = rand() % 100;
    cout << answer[i] << " ";
  }
}

waitClear(){
  Sleep(3000);
  system("clear");
}

getInput(int input[], int diff){
  for(int i = 0; i < diff + 2; i++){
    cout << "Number " << i + 1 << ": ";
    cin >> input[i];
    cout << endl;
  }
}

check(int input[], int answer[], int curr, int diff){
  int add = 0;
  for(int i = 0; i < diff + 2; i++){
    if(input[i] != answer[i]){
      curr -= 1;
      add = 1;
      break;
    }
  }
  if(curr == 0){
    curr = 1;
  }
  if(add != 1){
    curr += 1;
    cout << "Correct, you are now on level " << curr << endl;
  }
  else{
    cout << "Incorrect, you are now on level " << curr << endl;
  }
  return curr;
}

int main(){
  srand(time(0));
  int cont = 1;
  while(cont == 1){
    int curr = 1;
    int levels = getLevel();
    int diff = getDifficulty();
    int answer[diff + 2];
    int input[diff + 2];
    while(curr != levels){
      displayLevel(levels, curr);
      transition();
      generate(answer, diff);
      cout << endl;
      waitClear();
      getInput(input, diff);
      curr = check(input, answer, curr, diff);
    }
    displayLevel(levels, curr);
    cout << "You have won!" << endl << "Play again(1) or Quit(2) ";
    cin >> cont;
    cout << endl;
  }
  return 0;
}
