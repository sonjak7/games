#include <iostream>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <ctime>
using namespace std;

getRound(){
  int rounds;
  cout << "Winning score: ";
  cin >> rounds;
  return rounds;
}

userPick(string pick[]){
  int user;
  cout << "Rock(1) Paper(2) Scissors(3) ";
  cin >> user;
  cout << endl;
  user = user - 1;
  return user;
}

cpuPick(string pick[]){
  int cpu = (rand() % 3);
  return cpu;
}

show(int user, int cpu, string pick[]){
  cout << "You chose " << pick[user] << endl;
  cout << "CPU chose " << pick[cpu] << endl << endl;
}

processU(int user, int cpu, int userscore, int cpuscore){
  if(user - cpu == -2 || user - cpu == 1){
    cout << "You won this round" << endl;
    userscore += 1;
  }
  return userscore;
}

processC(int user, int cpu, int userscore, int cpuscore){
  if(user - cpu == 2 || user - cpu == -1){
    cout << "You lost this round" << endl;
    cpuscore += 1;
  }
  if(user == cpu){
    cout << "This round was a tie" << endl;
  }
  cout << endl << "Your score: " << userscore << endl;
  cout << "CPU score: " << cpuscore << endl << endl;
  return cpuscore;
}

int main(){
  srand(time(0));
  int userscore = 0;
  int cpuscore = 0;
  string pick[3] = {"Rock", "Paper", "Scissors"};
  int rounds = getRound();
  while(userscore != rounds && cpuscore != rounds){
    int uscore = userscore;
    int cscore = cpuscore;
    int user = userPick(pick);
    int cpu = cpuPick(pick);
    show(user, cpu, pick);
    userscore = processU(user, cpu, userscore, cpuscore);
    cpuscore = processC(user, cpu, userscore, cpuscore);
    cout << "-----------------------------------------------" << endl;
  }
  if(userscore == rounds){
    cout << "You have won!";
  }
  else{
    cout << "You lost.";
  }
  return 0;
}
