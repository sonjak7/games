#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;

struct players{
  string name;
  int score;
} player[50];

int getPlayerCount(){
  int playercount;
  cout << "How many players? ";
  cin >> playercount;
  return playercount;
}

void createPlayers(int playercount){
  for(int i = 0; i < playercount; i++){
    stringstream sstm;
    sstm << "Player " << i+1;
    player[i].name = sstm.str();
    player[i].score = 0;
  }
}

int choose(int current){
    int pick;
    cout << player[current].name << "'s turn" << endl;
    cout << "Roll(1) or Hold(2) ";
    cin >> pick;
    cout << endl;
    return pick;
}

dice(){
  int num = (rand() % 5) + 1;
  cout << "Your dice rolled: " << num << endl << endl;
  return num;
}

void hold(int pick, int current, int playercount, int roundscore){
  if(current == playercount){
    current = 0;
  }
}

int main(){
  srand(time(0));
  int pick = 1;
  int current = 0;
  int playercount = getPlayerCount();
  createPlayers(playercount);
  while(2 > 1){
    int num = 0;
    int roundscore = 0;
    while(num != 1){
      num = 0;
      pick = choose(current);
     if(pick == 2){
       break;
     }
     num = dice();
     if(num == 1){
       break;
     }
     player[current].score += num;
     roundscore += num;
     if(player[current].score >= 50){
       break;
     }
    cout << player[current].name << "'s score: " << player[current].score;
    cout << endl << endl;
    }
     if(num == 1){
      cout << player[current].name << " lost ";
      cout << roundscore << " points" << endl;
      player[current].score -= roundscore;
     }
     if(pick == 2){
      hold(pick, current, playercount, roundscore);
     }
     cout << player[current].name << "'s score: " << player[current].score;
     cout << endl;
     if(player[current].score >= 50){
       break;
     }
   current++;
   cout << endl;
   if(current == playercount){
     current = 0;
   }
  }
  cout << player[current].name << " has won with " << player[current].score;
  return 0;
}
