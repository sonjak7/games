#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <ctime>

using namespace std;

/*************************************************************************************
Class to represent a player in the game
**************************************************************************************/
class player{
    public:
        string name;
        int cash;

    add_cash(int amount){
        this->cash += amount;
    }
};

/*************************************************************************************
Get and validate how many players are in the game

Returns:
    player_count(int): The total number of players
**************************************************************************************/
int getCount(){
    int player_count;
    bool in_range = true;
    cout << "Enter number of players: ";
    cin >> player_count;
    if(player_count > 5 || player_count < 1){
        in_range = false;
    }

    while(!in_range){
        cout << "Invalid input, must be 1-5" << endl << "Enter number of players: ";
        cin >> player_count;
        if(player_count <= 5 && player_count >= 1){
            in_range = true;
        }
    }
    return player_count;
}

/*************************************************************************************
Get the answer word that the players have to guess
**************************************************************************************/
string getAns(){
    cin.clear();
    cin.ignore();
    string answer;
    cout << "Enter the answer phrase: ";
    getline(cin, answer);
    return answer;
}

/*************************************************************************************
Get the players' names and initialize them into the player class

Parameters:
    player_count(int): Total number of players
    all[5](player array reference): Empty array of 5 player classes
**************************************************************************************/
void initialize(int player_count, player all[5]){
    string add_name;
    for(int i = 0; i < player_count; i++){
        cout << "Player " << i + 1 << ", enter your name: ";
        getline(cin, add_name);
        all[i].name = add_name;
        all[i].cash = 0;
    }
}

/*************************************************************************************
Create the initial blank lines(underscores) representing the answer phrase

Parameters:
    answer(string): The answer phrase

Returns:
    show(string): String of underscores for each letter in answer phrase
**************************************************************************************/
string make_lines(string answer){
    string show = "";
    for(int i = 0; i < answer.length(); i++){
        if(answer[i] == ' '){
            show += ' ';
        }
        else{
            show += '_';
        }
    }
    return show;
}

/*************************************************************************************
Print the show variable with spaces in between each letter

Parameters:
    show(string): The answer phrase with underscores for unguessed letters
**************************************************************************************/
void print_lines(string show){
    for(int i = 0; i < show.length(); i++){
        cout << show[i];
        cout << ' ';
    }
    cout << endl;
}

/*************************************************************************************
Generates a random number representing the cash value the "wheel" landed on

Returns:
    wheel(int): The random integer value
**************************************************************************************/
int wheel_spin(){
    int wheel = ((rand() % 20) + 1) * 50;    //[100, 150, 200, 250,...,1000]
    cout << "The wheel landed on $" << wheel << endl;
    return wheel;
}

/*************************************************************************************
Validates if the player's selection has already been guessed

Parameters:
    guess(char): The player's guess, the letter being validated
    guessed_letters(string): A string of all previously guessed letters

Returns:
    guess(char): A validated guess(will be same as original guess if no
    validation was needed)
**************************************************************************************/
char validate(char guess, string guessed_letters){
    bool already_guessed = false, temp_checker = false;
    for(int x = 0; x < guessed_letters.length(); x++){
        if(guess == guessed_letters[x]){
            already_guessed = true;     //bad input(already guessed letter)
        }
    }
    while(already_guessed){
        temp_checker = false;
        cout << "That letter has already been guessed, try again: ";
        cin >> guess;
        for(int z = 0; z < guessed_letters.length(); z++){
            if(guess == guessed_letters[z]){
                temp_checker = true;    //another bad input is provided
            }
        }
        if(!temp_checker){              //if NOT bad input, break loop
            already_guessed = false;    
        }
    }
    return guess;
}

/*************************************************************************************
Displays the if the player's guess or correct/# of matches or incorrect

Parameters:
    checker(bool): If the player guessed a correct letter or not
    times(int): The number of matches for that letter(if any)
**************************************************************************************/
void display(bool checker, int times){
    if(checker){
        cout << endl << "Correct!" << endl;
        if(times == 1){
            cout << "1 match" << endl;
        }
        else{
            cout << times << " matches" << endl;
        }
    }
    else{
        cout << endl << "Incorrect" << endl << endl;
    }
}

/*************************************************************************************
Lets the player make a guess

Parameters:
    all[5](player array reference): Array of 5 player classes
    curr(int): The index of whose turn it is in the all array
    answer(string): The answer phrase
    show(string reference): The answer phrase with underlines for unguessed letters
    guessed_letters(string reference): String of all previously guessed letters
    times(int reference): The number of matches for a letter

Returns:
    checker(bool): If the guessed letter was in the phrase or not
**************************************************************************************/
bool make_selection(player all[5], int curr, string answer, string& show, string& guessed_letters, int& times){
    char guess;
    bool checker = false;
    times = 0;  
    cout << all[curr].name << ", choose a letter: ";
    cin >> guess;
    guess = validate(guess, guessed_letters);
    guessed_letters += guess;
    for(int i = 0; i < answer.length(); i++){
        if(guess == answer[i]){
            checker = true;
            times++;
            show[i] = answer[i];    //replace the screen output with guessed character
        }
    }
    display(checker, times);
    return checker;
}

/*************************************************************************************
Checks if the game has ended and all letters have been guessed

Parameters:
    answer(string): The answer phrase
    show(string): The answer phrase with underlines for unguessed letters

Returns:
    true(bool): If the game has ended
    false(bool): If the game has not yet ended
**************************************************************************************/
bool check_finish(string answer, string show){
    for(int i = 0; i < answer.length(); i++){
        if(answer[i] != show[i]){
            return false;
        }
    }
    return true;
}

/*************************************************************************************
Determines who the winner is by seeing who has the most cash in the end

Parameters:
    all[5](player array reference): Array of 5 player classes
    player_count(int): The total number of players

Returns:
    index(int): The index of the winning player in the all array
**************************************************************************************/
int find_winner(player all[5], int player_count){
    int index = 0;
    for(int i = 1; i < player_count; i++){
        if(all[index].cash < all[i].cash){
            index = i;
        }
    }
    return index;
}

/*************************************************************************************
Display the the final answer, everyone's final cash, and who won

Parameters:
    all[5](player array reference): Array of 5 player classes
    winner_index(int): The index of the winning player in the all array
    answer(string): The answer phrase
    player_count(int): The total number of players
**************************************************************************************/
void final_results(player all[5], int winner_index, string answer, int player_count){
    cout << "Answer: " << answer << endl;
    cout << endl << "Final results: " << endl;
    for(int i = 0; i < player_count; i++){
        cout << all[i].name << " finished with $" << all[i].cash << endl;
    }
    cout << endl << all[winner_index].name << " is the winner!" << endl;
}

/*************************************************************************************
Updates whose turn it is OR how much cash the current player has

Parameters:
    all[5](player array reference): Array of 5 player classes
    correct(bool): If the player's guess was correct or not
    curr(int): Index of whose turn it is in the all array
    player_count(int): Total number of players
    wheel_cash(int): The amount the current player has earned(if any)

Returns:
    curr(int): The updated current player(will be same if player guessed correctly)
**************************************************************************************/
int update_game(player all[5], bool correct, int curr, int player_count, int wheel_cash){
    if(!correct){
        curr++;
        if(curr == player_count){    //loop back to player1 if at last player
            curr = 0;
        }
    }
    else{
        all[curr].add_cash(wheel_cash);
        cout << all[curr].name << " now has $" << all[curr].cash << endl << endl;
    }
    return curr;
}

/*************************************************************************************
Runs the full game until it has ended

Parameters:
    all[5](string array reference): Array of 5 player classes
    answer(string): The answer phrase
    player_count(int): The total number of players
**************************************************************************************/
void run_game(player all[5], string answer, int player_count){
    int wheel_cash, times, curr = 0;
    string guessed_letters, show = make_lines(answer);
    bool correct, finish = false;
    while(!finish){
        print_lines(show);
        wheel_cash = wheel_spin();
        correct = make_selection(all, curr, answer, show, guessed_letters, times);
        wheel_cash *= times;    //value the wheel landed on * number of matches
        finish = check_finish(answer, show);
        curr = update_game(all, correct, curr, player_count, wheel_cash);
    }
    int winner = find_winner(all, player_count);
    final_results(all, winner, answer, player_count);
}

int main(){
    srand(time(0));
    cout << "Welcome to Wheel of Fortune!" << endl;
    int player_count = getCount();
    string answer = getAns();
    player all[5];
    initialize(player_count, all);
    system("clear");
    run_game(all, answer, player_count);
    return 0;
}