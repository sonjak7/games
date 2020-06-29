#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <ctime>
using namespace std;

string getAns(){
  string answer;
  cout << "What is the answer word? ";
  cin >> answer;
  return answer; 
}

int lives(){
  int liv;
  cout << "How many lives do you want? ";
  cin >> liv;
  return liv;
}

void makeLines(string answer, int len, char show[]){
  for(int i = 0; i < len; i++){
    if(answer[i] == ' '){
      show[i] = ' ';
    }
    if(answer[i] != ' '){
      show[i] = '_' ;
    }
  }
}

void printLines(int len, char show[]){
  for(int i = 0; i < len; i++){
    cout << show[i];
    cout << " ";
  }
}

void displayLiv(int liv){
  cout << endl << "Lives: ";
  for(int i = 0; i < liv; i++){
    cout << "O ";
  }
  cout << endl;
}

char guessLetter(){
  char guess;
  cout << "Guess a letter: ";
  cin >> guess;
  return guess;
}

int checkLetter(string answer, int len, char guess, char show[], int liv){
  int check = 0;
  for(int i = 0; i < len; i++){
    if(guess == answer[i]){
      show[i] = guess;
      check = 1;
    }
  }
  if(check == 1){
    cout << endl << "Correct!" << endl;
  }
  if(check == 0){
    cout << endl << "Incorrect" << endl;
    liv -= 1;
  }
  int upliv = liv;
  return liv;
}

int checkFinish(string answer, char show[], int len){
  int i;
  for(i = 0; i < len; i++){
    if(show[i] != answer[i]){
      return 0;
    }
  }
}

int main(){
  int keep = 1;
  while(keep == 1){
    string answer = getAns();
    int len = answer.length();
    int liv = lives();
    system("clear");
    char show[len];
    makeLines(answer, len, show);
    while(checkFinish(answer, show, len) == 0 && liv != 0){
      printLines(len, show);
      displayLiv(liv);
      char guess = guessLetter();
      liv = checkLetter(answer, len, guess, show, liv);
    }
    if(checkFinish(answer, show, len) != 0){
      cout << endl << "You have won!" << endl;
    }
    if(liv == 0){
      cout << endl << "You have lost." << endl;
    }
    cout << "The answer was: " << answer << endl;
    cout << endl << "Play again(1) or Quit(2) ";
    cin >> keep;
    cout << endl;
  }
  return 0;
}
