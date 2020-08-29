#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <windows.h>

using namespace std;

/**************************************************************************************************
Takes a 2D array and initializes it with empty spaces("|   |")

Parameters:
    board(2D string array): The board being initialized
**************************************************************************************************/
void initializeBoard(string board[10][10]){
    for(int i = 0; i < 10; i++){
        for(int x = 0; x < 10; x++){
            board[i][x] = "|   |";
        }
    }
}

/**************************************************************************************************
Prints a 2D array as a battleship board with numeric labels

Parameters:
    board(2D string array): The board being printed
**************************************************************************************************/
void printBoard(string board[10][10]){
    cout << "   ";
    for(int m = 1; m < 10; m++){
        cout << "  " << m << "  ";  //print top row
    }
    cout << " 10" << endl;
    for(int i = 0; i < 10; i++){
        if(i == 9){
            cout << "10 ";
        }                      //print header for each row
        else{
            cout << i + 1 << "  ";
        }
        for(int x = 0; x < 10; x++){
            cout << board[i][x];
        }
        cout << endl;
    }
}

/**************************************************************************************************
Validates if an integer is within a certain range

Parameters:
    value(int): The value being checked
    min(int): The minimun amount for value
    max(int): The maximum amount for value

Returns:
    value(int): The validated version of the value(will be same if no validation was needed)
**************************************************************************************************/
int numValidate(int value, int min, int max){
    while(value > max || value < min){
        cout << "Invalid input, try again: ";
        cin >> value;
    }
    return value;
}

/**************************************************************************************************
Get board coordinates for the user, used to place ships and select spots to fire at

Parameters:
    xspot(int reference): The x-coordinate the user picks
    yspot(int reference): The y-coordinate the user picks
    placing(bool): Says if the function is being used for placing or firing(orientation of the
    ship is asked if it used for placing)

Returns:
    orient(int): Whether ships is being placed horizontally(1) or vertically(2)
**************************************************************************************************/
int getLocation(int& xspot, int& yspot, bool placing){
    cout << "X coordinate[1-10]: ";
    cin >> xspot;
    xspot = numValidate(xspot, 1, 10);
    xspot -= 1;
    cout << "Y coordinate[1-10]: ";
    cin >> yspot;
    yspot = numValidate(yspot, 1, 10);
    yspot -= 1;
    if(placing){
        int orient;
        cout << "Horizontal(1) or Vertical(2): ";
        cin >> orient;
        orient = numValidate(orient, 1, 2);
        return orient;
    }
}

/**************************************************************************************************
Checks if the ship being placed is going outside of the board

Parameters:
    board(2D string array): The board in which the ship is being placed
    shipSize(int): The size(length) of the ship being placed
    coordinate(int): The initial coordinate the user picked for the ship(either the x-coordinate
    or y-coordinate will be passed depending on its orientation)

Returns:
    in_bounds(bool): Whether or not the ship is in bounds
**************************************************************************************************/
bool checkBoundary(string board[10][10], int shipSize, int coordinate){
    bool in_bounds = true;
    for(int i = (11 - shipSize); i < 10; i++){  //loop through all invalid coordinates depending on the ship size
        if(i == coordinate){
            in_bounds = false;
        }
    }
    return in_bounds;
}

/**************************************************************************************************
Checks if the ship being placed is overlaping another ship

Parameters:
    board(2D string array): The board in which the ship is being placed
    shipSize(int): The size of the ship being placed
    orient(int): Whether the ship is being placed horizontally(1) or vertically(2)
    xcor(int): The initial x-coordinate of the ship being placed
    ycor(int): The initial y-coordinate of the ship being placed

Returns:
    overlap(bool): Whether or not the ship overlaps another ship
**************************************************************************************************/
bool checkOverlap(string board[10][10], int shipSize, int orient, int xcor, int ycor){
    bool overlap = true;       //if the spot isn't empty for all spaces the ship occupies, this will become false
    if(orient == 1){
        for(int i = xcor; i < xcor + shipSize; i++){
            if(board[ycor][i] != "|   |"){  
                overlap = false;
            }
        }
    }
    else if(orient == 2){
        for(int m = ycor; m < ycor + shipSize; m++){
            if(board[m][xcor] != "|   |"){
                overlap = false;
            }
        }  
    }
    return overlap;
}

/**************************************************************************************************
Runs the two checks listed above correspondingly

Parameters:
    board(2D string array): The board being checked
    shipSize: Size of the ship being placed
    xcor(int): The initial x-coordinate of the ship being placed
    ycor(int): The initial y-coordinate of the ship being placed
    orient(int): Whether the ship is being placed horizontally(1) or vertically(2)

Returns:
    valid(bool): Whether or not all checks were passed successfully
**************************************************************************************************/
bool allChecks(string board[10][10], int shipSize, int xcor, int ycor, int orient){
    bool valid;
    if(orient == 1){  
        valid = checkBoundary(board, shipSize, xcor);
    }
    else if(orient == 2){ 
        valid = checkBoundary(board, shipSize, ycor);
    }
    if(valid){   //if ship is in bounds, check if it overlaps any other ship
        valid = checkOverlap(board, shipSize, orient, xcor, ycor);
    }
    return valid;
}

/**************************************************************************************************
Places ships on the boards(changes its value in the 2D array to | 2 |, | 3 |...)

Parameters:
    board(2D string array): The board that the ships are being placed on
    shipSize(int): The size of the ship being placed
    xcor(int): The initial x-coordinate of the ship being placed
    ycor(int): The initial y-coordinate of the ship being placed
    orient(int): Whether the ship is being placed horizontally(1) or vertically(2)
**************************************************************************************************/
void placeShips(string board[10][10], int shipSize, int xcor, int ycor, int orient){
    string ship_types[4] = {"| 2 |", "| 3 |", "| 4 |", "| 5 |"};
    if(orient == 1){
        for(int i = 0; i < shipSize; i++){
            board[ycor][xcor + i] = ship_types[shipSize - 2];   //will place the ship horizontally from the starting point 
        }                                                       //[shipSize-2] represents the ship size in for form "| x |"
    }
    else if(orient == 2){
        for(int x = 0; x < shipSize; x++){
            board[ycor + x][xcor] = ship_types[shipSize - 2];    //will place the ship vertically from the starting point
        }
    }
}

/**************************************************************************************************
Gets the coordinates to place the ships, and makes to calls to validate/actually place it

Parameters:
    board(2D string array): The board that the ships are going to be placed on
    shipSize(int): The size of the ship being placed
    player_placing(bool): Whether or not the user is placing the ships
**************************************************************************************************/
void getShips(string board[10][10], int shipSize, bool player_placing){
    bool temp_checker, check = false;
    int xcor, ycor, orient;
    while(!check){
        if(player_placing){
            cout << "Place your " << shipSize << " ship" << endl;
            orient = getLocation(xcor, ycor, true);
        }
        else if(!player_placing){   //the CPU will essentialy keep generating random spots until it finds one that fits
            xcor = rand() % 10;
            ycor = rand() % 10;
            orient = (rand() % 2) + 1;
        }
        temp_checker = allChecks(board, shipSize, xcor, ycor, orient);
        if(player_placing && !temp_checker){  //if any of the checks above resulted to false and a player is placing
            cout << "That spot doesn't fit, try again" << endl;
        }
        if(temp_checker){   //all checks were passed, break while loop and place ships
            check = true;
            placeShips(board, shipSize, xcor, ycor, orient);
        }
    }
}

/**************************************************************************************************
Updates the board depending on the result of the shot, and prints the result

Parameters:
    opp_board(2D string array): The opposing board(the board receiving the shot)
    show_board(2D string array): The board that is shown to the screen ***this will be the same
    as opp_board if the user's board is being updated***
    xshot(int): The x-coordinate being fired at
    yshot(int): The y-coordinate being fired at
    player_picking(bool): Whether or not the player's board is being updated

Returns:
    true(bool): If the shot was a hit
    false(bool): If the shot was not a hit
**************************************************************************************************/
bool updateBoard(string opp_board[10][10], string show_board[10][10], int xshot, int yshot, bool player_picking){
    if(!player_picking){
        cout << "CPU chose: X - " << xshot + 1 << " and Y - " << yshot + 1 << endl;
    }
    if(opp_board[yshot][xshot] == "|   |"){
        cout << "Miss" << endl << endl;
        show_board[yshot][xshot] = "| - |";
        return false;
    }
    else{
        cout << "Hit!" << endl << endl;
        show_board[yshot][xshot] = "| X |";
        return true;
    }
}

/**************************************************************************************************
Takes a shot at the opposing board and makes calls to update it correspondingly

Parameters:
    opp_board(2D string array): The opposing board(the board receiving the shot)
    show_board(2D string array): The board that is shown to the screen ***this will be the same
    as opp_board if the CPU is taking a shot***
    player_picking(bool): Whether or not the player is taking a shot

Returns:
    updateBoard(function - bool): Whether the shot was a hit or a miss
**************************************************************************************************/
bool takeShot(string opp_board[10][10], string show_board[10][10], bool player_picking){
    bool check = false; //represents if the selected spot has been picked already or not
    int xshot, yshot;
    while(!check){
        if(player_picking){
            cout << "Pick a spot to fire at" << endl;
            getLocation(xshot, yshot, false);
        }
        else if(!player_picking){
            xshot = rand() % 10;
            yshot = rand() % 10;
        }
        if(show_board[yshot][xshot] == "| X |" || show_board[yshot][xshot] == "| - |"){
            if(player_picking){
                cout << "You have already picked that spot, try again" << endl;
            }
        }
        else{   //a spot that hasn't been picked is selected, break loop and update board correspondingly
            check = true;
            return updateBoard(opp_board, show_board, xshot, yshot, player_picking);
        }
    }
}

/**************************************************************************************************
Checks if the game has finished or not

Parameters:
    board(2D string array): The board being checked if finished(no more ships left)

Returns:
    true(bool): If the passed board is finished
    false(bool): If the passed board is not finished
**************************************************************************************************/
bool checkFinish(string board[10][10]){
    int hit_count = 0;
    for(int i = 0; i < 10; i++){
        for(int x = 0; x < 10; x++){
            if(board[x][i] == "| X |"){
                hit_count += 1;
            }
        }
    }
    if(hit_count == 17){    //if there is 17 hits on a board, then all ships have sunk
        return true;
    }
    return false;
}

/**************************************************************************************************
Creates the battleship game by making calls to initialize all boards and place ships

Parameters:
    playerBoard(2D string array): The user's board
    cpuBoard(2D string array): The CPU's board
    showBoard(2D string array): The modified version of the CPU's board that is shown to the user
    (as the user should not see where the CPU's ships are placed)
**************************************************************************************************/
void createGame(string playerBoard[10][10], string cpuBoard[10][10], string showBoard[10][10]){
    initializeBoard(playerBoard);
    initializeBoard(cpuBoard);  
    initializeBoard(showBoard);
    for(int i = 2; i < 6; i++){
        getShips(playerBoard, i, true);
        printBoard(playerBoard);
        getShips(cpuBoard, i, false);
        if(i == 3){      //allows there to be two 3-size ships
            getShips(playerBoard, i, true);
            printBoard(playerBoard);
            getShips(cpuBoard, i, false);
        }
    }
}

/**************************************************************************************************
Runs the full game of battleship by appropriately making calls

Parameters:
    playerBoard(2D string array): The user's board
    cpuBoard(2D string array): The CPU's board
    showBoard(2D string array): The modified version of the CPU's board that is shown to the user
    (as the user should not see where the CPU's ships are placed)
**************************************************************************************************/
void run_game(string playerBoard[10][10], string cpuBoard[10][10], string showBoard[10][10]){
    Sleep(1500);
    while(true){    //this while loop will break, through one of the "break" statements written below
        cout << endl << "CPU's board" << endl;
        printBoard(showBoard);
        takeShot(cpuBoard, showBoard, true);    //user shot
        if(checkFinish(showBoard)){    //will trigger only if player wins(so CPU doesn't make a shot unecessarily)
            printBoard(showBoard);
            cout << endl << "Congratulations, you have won!" << endl;
            break;
        }
        Sleep(1500);
        if(takeShot(playerBoard, playerBoard, false)){  //CPU shot
            Sleep(2000);
            cout << "Your board" << endl;
            printBoard(playerBoard);        //the user's board will print if the CPU makes a hit, will skip this if the CPU misses
        }
        Sleep(2000);
        if(checkFinish(playerBoard)){   //will trigger if CPU wins
            cout << "CPU's ships" << endl;
            printBoard(cpuBoard);
            cout << endl << "You have lost :(" << endl;
            break;
        }
    }
}

int main(){
    cout << "Welcome to Battleship!" << endl;
    srand(time(0));
    string playerBoard[10][10];
    string cpuBoard[10][10];
    string showBoard[10][10];
    createGame(playerBoard, cpuBoard, showBoard);
    run_game(playerBoard, cpuBoard, showBoard);
    return 0;
}