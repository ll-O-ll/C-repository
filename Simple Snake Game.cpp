#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100],tailY[100];
int nTail;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
//This program will run a simple snake game;
//The structure will have four core components: the setup, the drawing; the input and the logic


void Setup(){
    //initialize game settings
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void Draw(){
    system("cls");//linux system("clear")
    //print top boundary
    for (int i = 0; i < width+2; i++){
        cout << "# ";

    }
    cout << endl;
    for (int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //print first column
            if (j==0){
                cout << "#";
            }
            //print head of snake
            if (i == y && j == x){
                cout << "O ";
            }
            //print the fruit
            else if (i == fruitY && j == fruitX){
                cout << "F ";
            }
            else{
                bool print = false;
                for (int k = 0; k <nTail; k++){
                    //print the tail of the snake if it exists
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                // if there's no tail, print nothing
                if (!print){
                        cout << " ";
                }
                cout << " ";
            }
            //print last column
            if (j == width-1){
               cout << " #";
            }
        }
        cout << endl;
    }
    //print bottom boundary
    for (int i = 0; i < width+2; i++){
        cout << "# ";
    }
    cout << endl;
    //print current score
    cout << "Score:" << score << endl;
}
void Input(){
    //using console library for user input to control the snake movement
    if (_kbhit()){
        switch (_getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }

    }
}

void Logic(){
    //the previous tail segments are located closer to the head in this logic
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    //initialize tail to be at head i.e. no tail at start
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1;i < nTail; i++){ //Ooooo the tail segment will have the position of the head in the following move of the snake
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }
    //movement logic
    switch(dir){
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if the snake goes out of bounds, terminate the game
    if (x > width || x < 0 || y >= height || y < 0){
        gameOver = true;
    }
    //if the head intersects the tail, terminate the game
    for (int i =0; i <nTail; i++){
        if (tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    //if the snake eats a fruits, respawn the fruit somewhere else and increase the tail size
    if (x == fruitX && y == fruitY){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;

    }



}
int main()
{
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(10);// slows the game down
    }

    return 0;
}
