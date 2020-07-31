#Author: Sanjay Ramanathan
#Date: 6/3/2020
#Description: A program to play the board game Gess

class GessGame():
    """
    This class creates a new gess game

    Attributes:
        turn(char): Represents whose turn it is, starts off as black's turn
        game_state(string): Says whether game is unfinished, white won, or black won
        grid(2D list): Represents the board, starts off as the initial gess board
    """
    def __init__(self):
        self._turn = "BLACK_TURN"
        self._game_state = "UNFINISHED"
        self._grid = initialize_board()

    def get_game_state(self):
        return self._game_state

    def resign_game(self):
        if self._turn == "BLACK_TURN":
            self._game_state = "WHITE_WON"
        elif self._turn == "WHITE_TURN":
            self._game_state = "BLACK_WON"
        self.change_turn()

    def make_move(self, old_center, new_center):
        """
        Allows a player to make a move on the board, also checks for any invalid moves

        Parameters:
            old_center(string): The coordinates of the center of the piece being moved
            new_center(string): The coordinates of where the center of the new piece will be

        Returns:
            True(bool): If the move was valid and successfully executed
            False(bool): If the move was invalid
        """
        old_cors = string_parser(old_center)
        new_cors = string_parser(new_center)
        if self.all_checks(old_cors, new_cors):
            move_piece(old_cors[0], old_cors[1], new_cors[0], new_cors[1], self._grid)
            self.change_turn()
            self.set_game_state()
            return True
        else:
            return False

    def all_checks(self, old_cors, new_cors):
        """
        A combination of all the move checking functions

        Parameters:
            old_cors(string): The coordinates of the center of the piece being moved
            new_center(string): The coordinates of where the center of the new piece will be

        Returns:
            True(bool): If all checks return true and move can be made
            False(bool): If any check returns false and the move cannot be made
        """
        if check_move_piece(old_cors[0], old_cors[1], self._turn, self._grid)  == True and \
        check_rings(old_cors[0], old_cors[1], new_cors[0], new_cors[1], self._turn, self._game_state, self._grid) \
        == True and check_new_spot(old_cors[0], old_cors[1], new_cors[0], new_cors[1], self._grid) == True and \
        check_interference(old_cors[0], old_cors[1], new_cors[0], new_cors[1], self._grid) == True:
            return True
        else:
            return False
        
    def change_turn(self):
        """
        Method to change the turn after every move
        """
        if self._turn == "BLACK_TURN":
            self._turn = "WHITE_TURN"
        elif self._turn == "WHITE_TURN":
            self._turn = "BLACK_TURN"

    def set_game_state(self):
        """
        Checks if there's still rings on both sides
        """
        rings = find_rings(self._grid)
        if rings[0] == 0:
            self._game_state = "BLACK_WON"
        elif rings[1] == 0:
            self._game_state = "WHITE_WON"

    def print_board(self):
        """
        Prints the current board

        Parameters:
            grid(2D array): The current gess board
        """
        for horiz in range(19, -1, -1):
            for vert in range(0, 20):
                if self._grid[vert][horiz] == "E":    #so empty spots will appear empty(won't show 'E')
                    marker = " "
                else:           
                    marker = self._grid[vert][horiz]
                print('| ', marker, ' |', end = '')
            print()

def string_parser(coordinate):
    """
    Takes a string as those passed to the make_move method and turns them into coordinates

    Parameters:
        coordinate(string): The string that's being parsed
    
    Returns:
        [xcor, ycor](list): A list containing the x-coordinate and y-coordinate that the given string represents
    """
    xcor = ord(coordinate[0]) - 97
    if len(coordinate) == 2:
        ycor = int(coordinate[1]) - 1
    elif len(coordinate) == 3:
        val = coordinate[1] + coordinate[2]
        ycor = int(val) - 1
    return [xcor, ycor]

def find_piece(xcor, ycor, grid):
    """
    Takes coordinates on the board and returns the correlating piece around it(assuming the given
    coordinates represent the center of the piece)

    Parameters:
        xcor(int): The x-coordinate of the center piece
        ycor(int): The y-coordinate of the center piece
        grid(2D array): The current gess board

    Returns:
        piece(list): The values of each spot in the piece(empty, black, or white)
    """
    piece = []
    piece.append(grid[xcor][ycor])  #append center spot
    piece.append(grid[xcor - 1][ycor - 1])  #append all surrounding spots
    piece.append(grid[xcor][ycor - 1])
    piece.append(grid[xcor + 1][ycor - 1])
    piece.append(grid[xcor - 1][ycor])
    piece.append(grid[xcor + 1][ycor])
    piece.append(grid[xcor - 1][ycor + 1]) 
    piece.append(grid[xcor][ycor + 1])  
    piece.append(grid[xcor + 1][ycor + 1])
    return piece

def find_direction(prev_xcor, prev_ycor, new_xcor, new_ycor):
    """
    After submitting a move, this checks what direction the player is trying to move their piece

    Parameters:
        prev_xcor(int): The x-coordinate of the center of piece trying to be moved
        prev_ycor(int): The y-coordinate of the center of piece trying to be moved
        new_xcor(int): The x-coordinate of the center of the location trying to be moved to
        new_ycor(int): The y-coordinate of the center of the location trying to be moved to

    Returns:
        direction(string): The direction that the player is trying to move
        *can possibly be a combination, such as northeast, southwest, etc.*
    """
    direction = ""
    if prev_ycor > new_ycor:
        direction += "south"  
    if prev_ycor < new_ycor:
        direction += "north"
    if prev_xcor < new_xcor:
        direction += "east"    
    if prev_xcor > new_xcor:
        direction += "west"   
    return direction

def check_move_piece(xcor, ycor, turn, grid):
    """
    Checks that the piece the player is trying to move is valid

    Parameters:
        xcor(int): The x-coordinate of the center of piece trying to be moved
        ycor(int): The y-coordinate of the center of piece trying to be moved
        grid(2D array): The current gess board
        turn(string): Represents whose turn it is

    Returns:
        False(bool): If piece being moved is invalid
        True(bool): If the piece is valid
    """
    piece = find_piece(xcor, ycor, grid)

    if "W" in piece and "B" in piece:   #if different color stones are in the piece
        return False
    if "W" not in piece[1:] and "B" not in piece[1:]:   #if there's no edge stones
        return False
    if turn == "BLACK_TURN" and "W" in piece:   #if you're moving the other player's stones
        return False
    elif turn == "WHITE_TURN" and "B" in piece:
        return False
    return True

def check_rings(prev_xcor, prev_ycor, new_xcor, new_ycor, turn, end, grid):
    """
    Checks if the game is already over or if a player is removing their own rings

    Parameters:
        prev_xcor(int): The x-coordinate of the center of piece trying to be moved
        prev_ycor(int): The y-coordinate of the center of piece trying to be moved
        new_xcor(int): The x-coordinate of the center of the location trying to be moved to
        new_ycor(int): The y-coordinate of the center of the location trying to be moved to
        turn(string): Represents whose turn it is
        end(string): Represents the current game state
        grid(2D array): The current gess board

    Returns:
        True(bool): If there'll still be rings after the move
        False(bool): If the rings incorrectly gets altered by the move
    """
    if end == "BLACK_WON" or end == "WHITE_WON":  #if game is over
        return False
    temp_board = list(map(list, grid))  
    move_piece(prev_xcor, prev_ycor, new_xcor, new_ycor, temp_board)
    if find_rings(temp_board)[0] == 0 and turn == "WHITE_TURN": #if white removes its own rings
        return False
    elif find_rings(temp_board)[1] == 0 and turn == "BLACK_TURN": #if black removes its own rings
        return False
    return True

def check_new_spot(prev_xcor, prev_ycor, new_xcor, new_ycor, grid):
    """
    Checks the spot the piece is trying to move to

    Parameters:
        prev_xcor(int): The x-coordinate of the center of piece trying to be moved
        prev_ycor(int): The y-coordinate of the center of piece trying to be moved
        new_xcor(int): The x-coordinate of the center of the location trying to be moved to
        new_ycor(int): The y-coordinate of the center of the location trying to be moved to
        grid(2D array): The current gess board

    Returns:
        True(bool): If the piece is moving in a correct way
        False(bool): If the piece is moving incorrectly
    """
    prev_piece = find_piece(prev_xcor, prev_ycor, grid)
    direction = find_direction(prev_xcor, prev_ycor, new_xcor, new_ycor)
    all_directions = ["southwest", "south", "southeast", "west", "east", "northwest", "north", "northeast"]
    if new_xcor == 0 or new_xcor == 19 or new_ycor == 0 or new_ycor == 19:  #if new center is out of bounds
        return False
    if prev_piece[0] == "E":   #if center spot is empty
        horiz_shift = prev_xcor - new_xcor
        vert_shift = prev_ycor - new_ycor
        if horiz_shift > 3 or horiz_shift < -3 or vert_shift > 3 or vert_shift < -3: #if piece is moving 3+ spots
            return False
    for test in range(8):
        if all_directions[test] == direction and prev_piece[test+1] == "E": #if it's moving in a direction with no stone
            return False
    return True

def check_interference(prev_xcor, prev_ycor, new_xcor, new_ycor, grid):
    """
    Checks if the piece runs into another stone in its path

    Parameters:
        prev_xcor(int): The x-coordinate of the center of piece trying to be moved
        prev_ycor(int): The y-coordinate of the center of piece trying to be moved
        new_xcor(int): The x-coordinate of the center of the location trying to be moved to
        new_ycor(int): The y-coordinate of the center of the location trying to be moved to
        grid(2D array): The current gess board

    Returns:
        True(bool): If the piece either doesn't run into a stone or only overtakes a stone
        False(bool): If the piece is trying to move past a stone
    """
    direction = find_direction(prev_xcor, prev_ycor, new_xcor, new_ycor)
    x_check = prev_xcor #x-coordiate of the center of the testing piece
    y_check = prev_ycor #y-coordinate of the center of the testing peice
    last_move = False
    #this while loop moves a test piece one spot at a time to see if it runs into any stones
    while x_check != new_xcor or y_check != new_ycor:
        if last_move:   #if the piece has run into another stone and still trying to move past it
            return False
        #move the center of the testing piece depending on the direction
        if "north" in direction:
            y_check += 1
        elif "south" in direction:
            y_check -= 1
        if "east" in direction:
            x_check += 1
        elif "west" in direction:
            x_check -= 1
        check_piece = find_piece(x_check, y_check, grid)
        #_border represents the 3 spots of each side of the new testing piece
        up_border = check_piece[6:]
        down_border = check_piece[1:4]
        right_border = [check_piece[3], check_piece[5], check_piece[8]]
        left_border = [check_piece[1], check_piece[4], check_piece[6]]
        #any of these statements will run if a stone falls under the footprint of the test piece
        if "north" in direction and ("W" in up_border or "B" in up_border):
            last_move  = True
        elif "south" in direction and ("W" in down_border or "B" in down_border):
            last_move  = True
        if "east" in direction and ("W" in right_border or "B" in right_border):
            last_move  = True
        elif "west" in direction and ("W" in left_border or "B" in left_border):
            last_move  = True
    return True

def move_piece(prev_xcor, prev_ycor, new_xcor, new_ycor, grid):
    """
    The function that moves a piece on the board

    Parameters:
        prev_xcor(int): The x-coordinate of the center of piece trying to be moved
        prev_ycor(int): The y-coordinate of the center of piece trying to be moved
        new_xcor(int): The x-coordinate of the center of the location trying to be moved to
        new_ycor(int): The y-coordinate of the center of the location trying to be moved to
        grid(2D array): The current gess board
    """
    prev_piece = find_piece(prev_xcor, prev_ycor, grid)
    modify_piece(prev_xcor, prev_ycor, grid)
    modify_piece(new_xcor, new_ycor, grid, prev_piece)

    if new_xcor == 1 or new_ycor == 1 or new_xcor == 18 or new_ycor == 18: #if center stone is now on edge of board
        for empty in range(20): #empties any potential stones out of bounds
            grid[0][empty] = "E"
            grid[empty][0] = "E"
            grid[19][empty] = "E"
            grid[empty][19] = "E"

def modify_piece(xcor, ycor, grid, change_to = ["E"] * 9):
    """
    Updates all spots of a given piece, helper function to the move_piece function

    Parameters:
        xcor(int): The x-coordinate of the center of piece being updated
        ycor(int): The y-coordinate of the center of piece being updated
        grid(2D list): The current gess board
        change_to(list): The list of values the new piece is being updated to, defaulted to
        a list of 9 "E"s, which will empty the piece
    """
    grid[xcor][ycor] = change_to[0]
    grid[xcor - 1][ycor - 1] = change_to[1]
    grid[xcor][ycor - 1] = change_to[2]
    grid[xcor + 1][ycor - 1] = change_to[3]
    grid[xcor - 1][ycor] = change_to[4]
    grid[xcor + 1][ycor] = change_to[5]
    grid[xcor - 1][ycor + 1] = change_to[6]
    grid[xcor][ycor + 1] = change_to[7]
    grid[xcor + 1][ycor + 1] = change_to[8]

def find_rings(grid):
    """
    Checks if the game has been won by looking through the board for ring

    Parameters:
        grid(2D array): The current gess board

    Returns:
        [white_rings, black_rings](list): The number of white rings and black rings
    """
    white_rings = 0
    black_rings = 0
    for horiz_check in range(1, 19):
        for vert_check in range(1, 19):
            check_piece = find_piece(horiz_check, vert_check, grid)
            if check_piece[1:] == (["W"] * 8) and check_piece[0] == "E":  #if there is a white ring 
                white_rings += 1
            elif check_piece[1:] == (["B"] * 8) and check_piece[0] == "E":    #if there is a black ring
                black_rings += 1
    return [white_rings, black_rings]

def initialize_board():
    """
    Function to initialize the board in its starting position

    Returns:
        grid(2D array): The initial gess board
    """
    grid = []
    for yrow in range(20):
        grid.append([])
        for xrow in range(20):
            grid[yrow].append(None)
    for blank in range(20): #initialize all empty rows
        grid[blank][0] = "E"  #E = empty
        grid[blank][4] = "E"
        grid[blank][5] = "E"
        for middle in range(7, 13):
            grid[blank][middle] = "E"
        grid[blank][14] = "E"
        grid[blank][15] = "E"
        grid[blank][19] = "E"
    for black1 in range(1, 4, 2): #intialize rows 1 and 3 (2 and 4 on actual board)
        for place in range(20):
            if place == 0 or place == 1 or place == 3 or place == 5 or place == 14 or \
            place == 16 or place == 18 or place == 19:
                grid[place][black1] = "E"
            else:
                grid[place][black1] = "B" #B = black stone
    for white1 in range(16, 19, 2): #intialize rows 16 and 18 (17 and 19 on actual board)
        for place in range(20):
            if place == 0 or place == 1 or place == 3 or place == 5 or place == 14 or \
            place == 16 or place == 18 or place == 19:
                grid[place][white1] = "E"
            else:
                grid[place][white1] = "W" #W = white stone
    for longrow in range(2, 18, 15): #initialize rows 2 and 17 (3 and 18 on actual board)
        for place in range(20):
            if place == 0 or place == 4 or place == 6 or place == 11 or \
            place == 13 or place == 15 or place == 19:
                grid[place][longrow] = "E"
            else:
                if longrow == 2:
                    grid[place][2] = "B"
                elif longrow == 17:
                    grid[place][17] = "W"
    for smallrow in range(6, 14, 7): #initialize rows 6 and 13 (7 and 14 on actual board)
        for place in range(20):
            if place % 3 != 2:
                grid[place][smallrow] = "E"
            else:
                if smallrow == 6:
                    grid[place][6] = "B"
                elif smallrow == 13:
                    grid[place][13] = "W"
    return grid
