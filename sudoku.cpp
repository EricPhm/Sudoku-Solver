#include <iostream>
#include <cmath>
#include <stdlib.h> // for rand and srand
#include <ctime> // for time
using namespace std;

// Function prototype to let the compiler know it there
bool flipCoin();

bool isValid(int** grid, int x, int y, int n){

    // because generate need more 0 to make it harder
    if (n == 0) return true;

    // check for row
    for(int i = 0; i < 9; i++){
        if(grid[i][y] == n){ 
            return false;
        }
    }

    // check for column 
    for(int j = 0; j < 9; j++){
        if(grid[x][j] == n){
            return false;
        }
    }

    // check for 3x3 square grid
    // int x_0 = floor(x / 3) * 3;
    // int y_0 = floor(y / 3) * 3;
    int x_0 = (x / 3) * 3;
    int y_0 = (y / 3) * 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (grid[x_0 + i][y_0 + j] == n){
                return false;
            }
        }
    }
    return true;
}

// this always create unsolvable sudoku board
// at each step try solve if can solvable?
bool makeBoard(int** grid){
    for (int i = 0; i < 9;i++){
        for(int j = 0; j < 9; j++){
            if(grid[i][j] == -1){
                int n;
                for (int k = 1; k <= 9; k++){
                    if(flipCoin()){  n = 0;  }
                    else{  n = k; } //rand() % 10;  }
                    //n = rand() % 10;
                    if(isValid(grid, i, j, k)){
                        grid[i][j] = n;
                        if (makeBoard(grid)) return true;
                        // if all the positions in the makeBoard lead to dead end
                        // if not true then the position set back to 0
                        // then k+1 keep doing the loop
                        // and keep doing that until reach the base case
                        grid[i][j] = -1; // backtracking
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool flipCoin(){
    int n = rand() % 20; // percentage of 0 appear on board - 12.5
    if (n == 0) return true;
    else 
        return false;
}

// return the grid pointer
int** generateBoard(){
    // seeding the random generator
    // ensure that the random numbers generated are different each time the program is run.
    srand(time(nullptr));

    // allocate memory for grid variables
    int** grid = new int*[9];
    for (int i = 0; i < 9; i++){
        grid[i] = new int[9];
    }

    // assign it to -1 for later rand generate fill in 0
    for (int i = 0; i < 9; i++) 
        for (int j = 0; j < 9; j++)
            grid[i][j] = -1;
    
    makeBoard(grid);
    return grid;
    
}

bool acceptance(int** grid, int x, int y, int n){

    for (int i = 0; i < 9; i++) {
        if(grid[i][y] == n) {
            return false;
        }
    }

    for (int j = 0; j < 9; j++) {
        if(grid[x][j] == n) {
            return false;
        }
    }
    // divided the row by 3 then 0 is for the 1st square row, 1 is for the second square row, 2 is for the third square row
    int x_0 = (x/3) * 3; // check for the beginning row of square
    int y_0 = (y/3) * 3; // check for the beginning column of square

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(grid[x_0 + i][y_0 + j] == n){
                return false;
            }
        }
    }
    return true;
}

bool possibleSolution(int**& grid){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0){
                for (int k = 1; k <= 9; k++) {
                    if(acceptance(grid, i, j, k)) {
                        grid[i][j] = k;
                        if(possibleSolution(grid)){
                            return true;
                        }
                        grid[i][j] = 0;
                    }
                }
                return false; // no valid value k for this cell
            }
        }
    }
    return true;
} 


void solveSudoku(int**& grid){
    if (!possibleSolution(grid)) {
        cout << "No solution exists." << endl;
    }
}


void printBoard(int** grid){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
            if (j == 2 or j == 5)
                cout << grid[i][j] << "  | ";
            else
                cout << grid[i][j] << "   ";
            
        cout  << endl ;
        if (i == 2 or i == 5)
            cout << "------------------------------------"<< endl; 
    }
    cout << "_________________________________________"<< endl; 
}

int main(int argc, char const *argv[])
{
    // hold the address of the dynamically allocated grid array
    int** grid1 = generateBoard();

    // print board
    printBoard(grid1);

    solveSudoku(grid1);
    
    printBoard(grid1);

    // Free memory for the grid
    for (int i = 0; i < 9; i++) {
        delete[] grid1[i];
    }
    delete[] grid1;
    grid1 = nullptr;

    return 0;
}