#ifndef __BOARD_C__
#define __BOARD_C__

#include <bits/stdc++.h>

#include "runner.cpp"

using namespace std;

class Board{
	public:
		int arr[N][N];   //to store the basic grid of 2048
		int currScore;
		Board(){
			//set the initial board
			for(int a=0;a<N;a++){
				for(int b=0;b<N;b++){
					arr[a][b] = 0;
				}
			}
			currScore = 0;
		}
		bool genNext();
		int makePlayerMove();
		int makeCompMove();
		void CloneBoard(Board& tbc);
		int countProfit(int x);
};

class Move{
	public:
		int deltaScore;
		int side; //1 means left 2 means top 3 means right and 4 means bottom and 0 means invalid
		Move(char s){
			deltaScore = 0;
			if(s=='a')	side=1;
			else if (s=='w')	side=2;
			else if (s=='d')	side=3;
			else if (s=='s')	side=4;
			else 	side = 0;
		}
		void moveLeft(Board& tbc);
		void moveUp(Board& tbc);
		void moveRight(Board& tbc);
		void moveDown(Board& tbc);
		void doMove(Board& tbc);
};

/*

CLASS MOVE FUNCTIONS --------------------------------- START --------------------------------------------

*/
/* -------- move functions to change board according to the game ------- */
inline void Move::moveRight(Board& tbc){
	int lI = N-1;
	for(int a=0;a<N;a++){
		lI = N-1;
		for(int b=N-2;b>=0;b--){
			if(tbc.arr[a][b] == 0)  continue;
			if(tbc.arr[a][lI] == 0){
				tbc.arr[a][lI] = tbc.arr[a][b];
				tbc.arr[a][b] = 0;
			} else if (tbc.arr[a][b] == tbc.arr[a][lI]) {
				tbc.arr[a][lI] = 2*tbc.arr[a][b];
				deltaScore += tbc.arr[a][lI];
				tbc.arr[a][b] = 0;
				lI--;
			} else {
				lI--;
				tbc.arr[a][lI] = tbc.arr[a][b];
				if(b!=lI)   tbc.arr[a][b] = 0;
			}
		}
	}
}
inline void Move::moveLeft(Board& tbc){
	int lI = 0;
	for(int a=0;a<N;a++){
		lI = 0;
		for(int b=1;b<N;b++){
			if(tbc.arr[a][b] == 0)  continue;
			if(tbc.arr[a][lI] == 0){
				tbc.arr[a][lI] = tbc.arr[a][b];
				tbc.arr[a][b] = 0;
			} else if (tbc.arr[a][b] == tbc.arr[a][lI]) {
				tbc.arr[a][lI] = 2*tbc.arr[a][b];
				deltaScore += tbc.arr[a][lI];
				tbc.arr[a][b] = 0;
				lI++;
			} else {
				lI++;
				tbc.arr[a][lI] = tbc.arr[a][b];
				if(b!=lI)   tbc.arr[a][b] = 0;
			}
		}
	}
}
inline void Move::moveUp(Board& tbc){
	int lI = 0;
	for(int b=0;b<N;b++){
		lI = 0;
		for(int a=1;a<N;a++){
			if(tbc.arr[a][b] == 0)  continue;
			if(tbc.arr[lI][b] == 0){
				tbc.arr[lI][b] = tbc.arr[a][b];
				tbc.arr[a][b] = 0;
			} else if (tbc.arr[a][b] == tbc.arr[lI][b]) {
				tbc.arr[lI][b] = 2*tbc.arr[a][b];
				deltaScore += tbc.arr[a][lI];
				tbc.arr[a][b] = 0;
				lI++;
			} else {
				lI++;
				tbc.arr[lI][b] = tbc.arr[a][b];
				if(a!=lI)   tbc.arr[a][b] = 0;
			}
		}
	}
}
inline void Move::moveDown(Board& tbc){
	int lI = N-1;
	for(int b=0;b<N;b++){
		lI = N-1;
		for(int a=N-2;a>=0;a--){
			if(tbc.arr[a][b] == 0)  continue;
			if(tbc.arr[lI][b] == 0){
				tbc.arr[lI][b] = tbc.arr[a][b];
				tbc.arr[a][b] = 0;
			} else if (tbc.arr[a][b] == tbc.arr[lI][b]) {
				tbc.arr[lI][b] = 2*tbc.arr[a][b];
				deltaScore += tbc.arr[a][lI];
				tbc.arr[a][b] = 0;
				lI--;
			} else {
				lI--;
				tbc.arr[lI][b] = tbc.arr[a][b];
				if(a!=lI)   tbc.arr[a][b] = 0;
			}
		}
	}
}
//-------------   END OF MOVE FUNCTIONS --------------//
inline void Move::doMove(Board& b){
	if(side==0)					return;
	else if(side==1)			moveLeft(b);
	else if(side==2)			moveUp(b);
	else if(side==3)			moveRight(b);
	else if(side==4)			moveDown(b);
}
/*

CLASS MOVE FUNCTIONS --------------------------------- END ----------------------------------------------

*/


/*

CLASS BOARD FUNCTIONS -------------------------------- START --------------------------------------------

*/
inline bool Board::genNext(){
	//generates a random number at a tile and returns true if generation was poss and false if the game is over
	vector < pair <int,int> >	allPoss;
	for(int a=0;a<N;a++){
		for(int b=0;b<N;b++){
			if(arr[a][b]==0)	allPoss.push_back(make_pair(a,b));
		}
	}
	int len = allPoss.size();
	if(len==0)		return false;
	len = rand()%len;
	arr[allPoss[len].first][allPoss[len].second] = (rand()%2+1)*2;
	return false;
}
inline int Board::makePlayerMove(){
	char ch;
	cin>>ch;
	Move playerMove(ch);
	playerMove.doMove(*this);
	currScore += playerMove.deltaScore;
}
inline int Board::makeCompMove(){

}
//------------ HELPER FUNCTIONS TO FIND BEST MOVE ------//
inline void Board::CloneBoard(Board& tbc){
	for(int a=0;a<N;a++){
		for(int b=0;b<N;b++){
			tbc.arr[a][b] = arr[a][b];
			tbc.currScore = currScore;
		}
	}
}
inline int Board::countProfit(int x){

}

/*

	CLASS BOARD FUCNTIONS -------------------------- END -----------------------------------------------
*/

#endif