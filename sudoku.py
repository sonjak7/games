import random

def initialize_board():
    """
    Create an 9 by 9 2D array representing the sudoku board

    Returns:
        board(2D array): The empty 2D array
    """
    board = []
    for yrow in range(9):
        board.append([])
        for _ in range(9):
            cell = [' ', False] #cell value, and if it's a starting digit or not
            board[yrow].append(cell)
    return board

def print_board(board):
    """
    Print a 2D array as a viewable sudoku board

    Paramaters:
        board(2D array): The 9 by 9 2D array to be printed
    """
    print('\n      A    B    C       D    E    F       G    H    I\n') # y-indexes
    for yrow in range(9):
        if yrow % 3 == 0 and yrow != 0: # seperate 3X3 segments vertically
            print()
        print(yrow + 1, end = '')   # x-indexes
        for xrow in range(9):
            if xrow % 3 == 0:   # seperate 3X3 segments horizontally
                print('   ', end = '')
            print('|', board[yrow][xrow][0], '|', end = '')
        print()
    print()

def set_defaults(board):
    """
    Input a certain number of randomized starting digits into the sudoku board

    Parameters:
        board(2D array): The board in which the digits will be placed
    """
    default_digits = get_default_digits()
    for _ in range(default_digits):
        valid = False
        while not valid:
            cell_value = random.randint(1, 9)
            x_pos = random.randint(0, 8)
            y_pos = random.randint(0, 8)
            # check pre-existing starting digits, and if any contraints are broken
            valid = check_position(cell_value, x_pos, y_pos, board) and \
            not board[y_pos][x_pos][1]
        board[y_pos][x_pos][0] = cell_value
        board[y_pos][x_pos][1] = True

def check_position(cell_value, x_pos, y_pos, board):
    """
    Check if an input on the board violates any of the sudoku contraints

    Paramaters:
        cell_value(int): Digit being placed into the board
        x_pos(int): X-coordinate of the value being placed
        y_pos(int): Y-coordinate of the value being placed
        board(2D array): The board being checked on

    Returns:
        True(bool): If the given value fits in the given spot
        False(bool): If any of the sudoku contraints gets violated
    """
    for line_checker in range(9): # check if the value is in the same row/column
        if board[y_pos][line_checker][0] == cell_value:
            return False
        elif board[line_checker][x_pos][0] == cell_value:
            return False
    segments = find_segments(x_pos, y_pos)
    x_segment = segments[0]
    y_segment = segments[1]
    for x_checker in x_segment: # check if value is in same 3X3 segment
        for y_checker in y_segment:
            if board[y_checker][x_checker][0] == cell_value:
                return False
    return True

def find_segments(x_pos, y_pos):
    """
    Given a cell, find the corresponding 3 by 3 segment it is in

    Parameters:
        x_pos(int): X-coordinate of the cell being checked
        y_pos(int): Y-coordinate of the cell being checked

    Returns:
        (x_segment, y_segment)(tuple): A tuple of arrays which represent the rows and
                                       columns of the cell's corresponding segment
    """
    seg1 = [0, 1, 2]
    seg2 = [3, 4, 5]
    seg3 = [6, 7, 8]
    if x_pos in seg1: x_segment = seg1
    elif x_pos in seg2: x_segment = seg2
    else: x_segment = seg3
    if y_pos in seg1: y_segment = seg1
    elif y_pos in seg2: y_segment = seg2
    else: y_segment = seg3
    return (x_segment, y_segment)

def get_default_digits():
    """
    Find and validate the number of starting digits the user wants

    Returns:
        default_digits(int): The number of starting digits
    """
    default_digits = int(input('Enter how many digits to start off with (17 - 30): '))
    while default_digits < 17 or default_digits > 30:
        default_digits = int(input('Invalid input, enter a number between 17 - 30: '))
    return default_digits

def get_user_choice():
    """
    Allow the user to choose whether they want to place or remove a number

    Returns:
        choice(int): 1 represents they want to place a number, 2 represents they
                     want to remove a number
    """
    choice = input('Place number(1) or Remove number(2): ')

    while choice != '1' and choice != '2':
        choice = input('Invalid input... Place number(1) or Remove number(2): ')
    choice = int(choice)
    return choice

def check_cell(board, placing):
    """
    Find and validate the cell that the user wants to modify

    Parameters:
        board(2D array): The board that the user is choosing from
        placing(bool): Whether the user is placing or removing from a cell

    Returns:
        [x_pos, y_pos](array): The validated cell coordinate the user has chosen
    """
    valid = False
    if placing: message = 'Choose a cell to place number (A1 - I9): '
    else: message = 'Choose a cell to remove from (A1 - I9): '
    while not valid:
        coordinate = input(message)
        x_pos = ord(coordinate[0]) - 65 # extract x and y coordinates as 0-8 values
        y_pos = int(coordinate[1]) - 1
        message = check_boundary(x_pos, y_pos, coordinate)
        if message == None: # if the user's cell is in the sudoku board
            if x_pos >= 32 and x_pos <= 40: # if the user's X value was lower case
                x_pos -= 32
            message = validate(board, placing, x_pos, y_pos) # perform all other checks
            if message == None: valid = True
    return [x_pos, y_pos]

def check_boundary(x_pos, y_pos, coordinate):
    """
    Checks if the user's input cell is within the board's 9 by 9 range

    Paramaters:
        x_pos(int): X-coordinate of the cell being checked
        y_pos(int): Y-coordinate of the cell being checked
        coordinate(string): Contains x_pos and y_pos, used to check input length

    Returns:
        *error message*(string): If the provided cell was out of bounds
        None(NULL): If the provided cell was within the board
    """
    # check if Y-coordinate and X-coordinate (lower/upper case) is in bounds
    if (((x_pos < 32 or x_pos > 40) and (x_pos < 0 or x_pos > 8)) or \
    y_pos < 0 or y_pos > 8) or (len(coordinate) > 2):
        return 'Invalid input. Choose cell between A1 - I9. (ex B6, E4, H7...): '
    else:
        return None

def validate(board, placing, x_pos, y_pos):
    """
    Check if a cell in the board is viable for the user's action

    Parameters:
        board(2D array): The board being checked on
        placing(bool): User's action, whether they are placing or removing
        x_pos(int): X-coordinate of the cell being checked
        y_pos(int): Y-coordinate of the cell being checked

    Returns:
        *error message 1*(string): If the user is removing from an empty cell
        *error message 2*(string): If the user is removing from a default starting cell
        *error message 3*(string): If the user is inserting into a populated cell
        None(NULL): If the cell is valid
    """
    if not placing and board[y_pos][x_pos][0] == ' ':
        return 'Invalid input. That spot is already empty. Try again: '
    elif not placing and board[y_pos][x_pos][1]:
        return 'Cannot change value of a deault cell! Try again: '
    elif placing and board[y_pos][x_pos][0] != ' ':
        return 'Invalid input. That spot is already taken. Try again: '
    else: # all tests passed, this is a valid cell
        return None

def check_value():
    """
    Find and validate a number that the user wants to put into a cell

    Returns:
        value(int): A number 1 - 9 that the user wants to place
    """
    in_range = False
    message = 'Select a number to place (1 - 9): '
    while not in_range:
        value = int(input(message))
        if value > 9 or value < 1:
            message = 'Invalid input. Select a number between 1 - 9: '
        else:
            in_range = True
    return value

def place_val(board):
    """
    Allow the user to place a value into the board, and validate their choice
    by making function calls

    Parameters:
        board(2D array): The board being placed into
    """
    valid = False
    coordinate = check_cell(board, True)
    x_pos = coordinate[0]
    y_pos = coordinate[1]
    while not valid:
        value = check_value()
        if not check_position(value, x_pos, y_pos, board):
            print("That number doesn't fit there! Try again.")
        else:
            valid = True
    board[y_pos][x_pos][0] = value  # all checks passed, update board to user's request

def remove_val(board):
    """
    Allow the user to remove a value from the board, and validate their choice
    by making function calls

    Parameters:
        board(2D array): The board being removed from
    """
    coordinate = check_cell(board, False)
    x_pos = coordinate[0]
    y_pos = coordinate[1]
    board[y_pos][x_pos][0] = ' '    # all checks passed, remove cell to user's request

def check_finish(board):
    """
    Check if the user has finished the sudoku puzzle

    Parameters:
        board(2D array): The board being checked for completeness

    Returns:
        finished(bool): Whether or not the game has been finished
    """
    finished = True
    for y_cor in range(9):
        for x_cor in range(9):
            # if any spot is empty, the game isn't finished
            if board[y_cor][x_cor][0] == ' ':
                finished = False
                break
    return finished

def main():
    print("Welcome to Sudoku!\n")
    board = initialize_board()
    set_defaults(board)
    print_board(board)
    while not check_finish(board):
        choice = get_user_choice()
        if choice == 1:
            place_val(board)
        elif choice == 2:
            remove_val(board)
        print_board(board)
    print("Congratulations, you have won!\nGoodbye!")

if __name__ == "__main__":
    main()
