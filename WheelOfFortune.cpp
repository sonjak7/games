#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <ctime>
using namespace std;

struct players{
  string name;
  int money;
};

struct players player[3];


char sentence[0];

int getPlayerCount(){
  int count;
  cout << "Enter the number of players: ";
  cin >> count;
  if(count > 3){
    cout << "3 or less players: ";
    cin.clear();
    cin.ignore(100, '\n');
    cin >> count;
  }
  return count;
}

void createPlayers(int count){
  if(count >= 1){
    player[0].name = "Player 1";
    player[0].money = 0;
  }
  if(count >= 2){
    player[1].name = "Player 2";
    player[1].money = 0;
  }
  if(count == 3){
      player[2].name = "Player 3";
      player[2].money = 0;
    }
}

string getSentence(){
  string answer;
  cout << "Enter the answer: ";
  getline(cin, answer);
  return answer;
}

void makeLines(string answer, int len){
  int i;
  for(i = 0; i < len; i++){
    if(answer[i] != ' '){
      sentence[i] = '_';
    }
    else{
      sentence[i] = ' ';
    }
  }
}

void printLines(int len){
  int t;
  for(t = 0; t < len; t++){
    cout << sentence[t];
    cout << ' ';
  }
}

char guessLetter(int len, int count, int current){
  char letter;
  int i;

  cout << player[current].name << ", guess a letter: ";
  cin >> letter;
  while(!cin){
    cin.clear();
    cin.ignore(100, '\n');
    cin >> letter;
  }

  return letter;
}

int randWheel(){
  srand(time(0));
  int random = (rand() % 21) + 1;
  return random;
}

int checkLetter(char letter, string answer, int len, int current, int random){
  int i;
  int x = 2;
  for(i = 0; i < len; i++){
    if(answer[i] == letter){
      x = 1;
      sentence[i] = letter;
      player[current].money += random;
      cout << "Correct";
    }
  }
  if(x != 1){
    cout << "Incorrect";
    return 4;
  }
}

int checkFinish(int len, string answer){
  int i;
  for(i = 0; i < len; i++){
    if(sentence[i] != answer[i]){
      return 55;
    }
  }
}

void everythingElse(int len, string answer, int count){
int current = 0;
while(checkFinish(len, answer) == 55){
  cout << endl << endl;
  printLines(len);
  cout << endl;
  int random = randWheel();
  cout << "The wheel landed on $" << random << endl;
  char letter = guessLetter(len, count, current);

  if(checkLetter(letter, answer, len, current, random) == 4){
    current++;
    if(current == count){
      current = 0;

  cout << endl;
    }
  }
}

cout << endl << endl;

cout << answer;
cout << endl << endl;

for(int i = 0; i < count; i++){
  cout << player[i].name << " finished with $" << player[i].money;
cout << endl;
}

cout << endl;
cout << endl;
cout << "You've finished the puzzle!";
};

int main(){

cout << "Wheel of Fortune!" << endl;
string answer = getSentence();
int count = getPlayerCount();
createPlayers(count);
system("clear");
int len = answer.length();
makeLines(answer, len);
everythingElse(len, answer, count);


return 0;
}
