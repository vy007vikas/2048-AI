#ifndef __RUNNER_C__
#define __RUNNER_C__

#include <bits/stdc++.h>
#include <unistd.h>

const int N = 4;
const int LOOK_AHEAD = 4;
const int DELAY = 5000000;
const int INF = 99999999;

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
		string set_color(int number){
			stringstream sss;
			sss<<"\033[";
			if(number==2)	sss<<"0";
			else {
				if (number==16 || number==128)		sss<<29+5;
				else if (number==8 || number==32)		sss<<29+3;
				else if (number==4 || number==256)		sss<<29+4;
				else if (number==64 || number==512)		sss<<29+7;
				else		sss<<29+2;
			}
			sss<<"m";
			return sss.str();
		}
		void showInit(){
			//show the initial menu for the game
			ss<<"-------------------------<<  2048 AI  >>-------------------------";
			ss<<endl<<endl;
			ss<<"A simple terminal implementation of 2048 to auto-solve the game using minimax and alpha-beta pruning."<<endl;
			ss<<"Any contributions are welcome."<<endl;
			ss<<"To start the game just hit enter."<<endl;
			cout<<ss.str();
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
					cout<<set_color(board.arr[a][b])<<board.arr[a][b]<<"    ";
				}
				cout<<endl;
			}
			cout<<endl<<endl;
		}
		void clearScreen(){
			//to clear the screen after one move
			usleep(DELAY);
			//system("clear");
		}
		void dispFinalScore(){
			ss<<"-------------------------<<  2048 AI  >>-------------------------";
			ss<<endl<<endl;
			ss<<"------------------------<<  GAME OVER  >>-------------------------";
			ss<<endl<<endl;
			ss<<"The final score is: "<<board.currScore<<endl;
			cout<<ss.str();
		}
		void playGame(){
			clearScreen();
			board.genNext();
			displayBoard();
			int x = board.makeCompMove();
			if(x==-1){
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