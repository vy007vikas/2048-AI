#ifndef __BOARD_C__
#define __BOARD_C__

#include <bits/stdc++.h>

#include "runner.cpp"

using namespace std;

class Move{
	public:
		int deltaScore;
		int side; //-1 means left 0 means top 1 means right and 2 means bottom
		Move(){
			deltaScore = 0;
		}
};

class Board{
	private:
		int arr[N][N];   //to store the basic grid of 2048
		vector < pair <int,int> > emptySet;
	public:
		int currScore;
		Board(){
			//set the initial board
			for(int a=0;a<N;a++){
				for(int b=0;b<N;b++){
					arr[a][b] = 0;
					emptySet.push_back(make_pair(a,b));
				}
			}
			currScore = 0;
		}
		void genNext(){
			//to generate a random number in the list
			int len = emptySet.size();
			int temp = rand()%len;
			arr[emptySet[temp].first][emptySet[temp].second] = (rand()%2+1)*2;

		}
		/* -------- move functions to change board according to the game ------- */
		void moveLeft(){
			int lI = N-1;
			for(int a=0;a<N;a++){
				lI = N-1;
				for(int b=N-2;b>=0;b--){
					if(arr[a][b] == 0)  continue;
					if(arr[a][lI] == 0){
						arr[a][lI] = arr[a][b];
						arr[a][b] = 0;
					} else if (arr[a][b] == arr[a][lI]) {
						arr[a][lI] = 2*arr[a][b];
						arr[a][b] = 0;
						lI--;
					} else {
						lI--;
						arr[a][lI] = arr[a][b];
						if(b!=lI)   arr[a][b] = 0;
					}
				}
			}
		}
		void moveRight(){
			int lI = 0;
			for(int a=0;a<N;a++){
				lI = 0;
				for(int b=1;b<N;b++){
					if(arr[a][b] == 0)  continue;
					if(arr[a][lI] == 0){
						arr[a][lI] = arr[a][b];
						arr[a][b] = 0;
					} else if (arr[a][b] == arr[a][lI]) {
						arr[a][lI] = 2*arr[a][b];
						arr[a][b] = 0;
						lI++;
					} else {
						lI++;
						arr[a][lI] = arr[a][b];
						if(b!=lI)   arr[a][b] = 0;
					}
				}
			}
		}
		void moveUp(){
			int lI = 0;
			for(int b=0;b<N;b++){
				lI = 0;
				for(int a=1;a<N;a++){
					if(arr[a][b] == 0)  continue;
					if(arr[lI][b] == 0){
						arr[lI][b] = arr[a][b];
						arr[a][b] = 0;
					} else if (arr[a][b] == arr[lI][b]) {
						arr[lI][b] = 2*arr[a][b];
						arr[a][b] = 0;
						lI++;
					} else {
						lI++;
						arr[lI][b] = arr[a][b];
						if(a!=lI)   arr[a][b] = 0;
					}
				}
			}
		}
		void moveDown(){
			int lI = N-1;
			for(int b=0;b<N;b++){
				lI = N-1;
				for(int a=N-2;a>=0;a--){
					if(arr[a][b] == 0)  continue;
					if(arr[lI][b] == 0){
						arr[lI][b] = arr[a][b];
						arr[a][b] = 0;
					} else if (arr[a][b] == arr[lI][b]) {
						arr[lI][b] = 2*arr[a][b];
						arr[a][b] = 0;
						lI--;
					} else {
						lI--;
						arr[lI][b] = arr[a][b];
						if(a!=lI)   arr[a][b] = 0;
					}
				}
			}
		}
		//-------------   END OF MOVE FUNCTIONS --------------//
		int makeMove(){
			char ch;
			cin>>ch;
			if(ch=='w')		moveUp();
			else if (ch=='s')	moveDown();
			else if (ch=='a')	moveRight();
			else if (ch=='d')	moveLeft();
			return 1;
		}
		int countProfit(int x){

		}
		int getVal(int x,int y){
			return arr[x][y];
		}
};

#endif