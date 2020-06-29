#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int getAnswer(){
  int answer = (rand() % 100) + 1;
  return answer;
}

int guessNum(){
  int guess;
  cout << "Guess a number between 1 and 100: ";
  cin >> guess;
  return guess;
}


int main(){

  srand(time(0));
  int answer = getAnswer();
  int guess = guessNum();
  while(guess != answer){
    if(guess > answer){
      cout << "Lower" << endl;
      cout << "Guess again: ";
      cin >> guess;
    }
    else if(guess < answer){
      cout << "Higher" << endl;
      cout << "Guess again: ";
      cin >> guess;
    }
  }
    cout << "Correct! The number was " << answer << "!";

  return 0;
}
