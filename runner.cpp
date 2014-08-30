#ifndef __RUNNER_C__
#define __RUNNER_C__

#include <bits/stdc++.h>
#include <unistd.h>

const int N = 4;
const int DELAY = 5000000;

#include "board.cpp"
#include "algo.cpp"

stringstream ss;
using namespace std;

class game{
    public:
        Board board;
        game(){
            //initialize a game

        }
        void showInit(){
            //show the initial menu for the game
            cout<<"-------------------------<<  2048 AI  >>-------------------------";
            cout<<endl<<endl;
            cout<<"A simple terminal implementation of 2048 to auto-solve the game using minimax and alpha-beta pruning."<<endl;
            cout<<"Any contributions are welcome."<<endl;
            cout<<"To start the game just hit enter."<<endl;
            char ch;
            scanf("%c", &ch);
        }
        void displayBoard(){
            //to display the game board
            cout<<"-------------------------<<  2048 AI  >>-------------------------";
            cout<<endl<<"                      <<< SCORE: "<<board.currScore<<"  >>>";
            cout<<endl<<endl;
            for(int a=0;a<N;a++){
                for(int b=0;b<N;b++){
                    if(b==0)    cout<<"                        ";
                    cout<<board.getVal(a,b)<<"    ";
                }
                cout<<endl;
            }
            cout<<endl<<endl;
        }
        void clearScreen(){
            //to clear the screen after one move
            usleep(DELAY);
            system("clear");
        }
        void dispFinalScore(){
            cout<<"-------------------------<<  2048 AI  >>-------------------------";
            cout<<endl<<endl;
            cout<<"------------------------<<  GAME OVER  >>-------------------------";
            cout<<endl<<endl;
            cout<<"The final score is: "<<board.currScore<<endl;
        }
        void playGame(){
            displayBoard();
            clearScreen();
            board.genNext();
            int x = board.makeMove();
            if(x==101){
                dispFinalScore();
                return;
            }
            playGame();
        }
};

int main(){
    game myGame;
    myGame.showInit();
    myGame.playGame();
    return 0;
}

#endif