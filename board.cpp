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
            int len = emptySet.size();
            int temp = rand()%len;
            arr[emptySet[temp].first][emptySet[temp].second] = 2;
            if(temp > len/2)    arr[emptySet[temp].first][emptySet[temp].second] = 4;
        }
        void moveLeft(){
            for(int a=N-2;a>=0;a--){
                for(int b=0;b<N;b++){
                    if(arr[b][a] == 0)  continue;
                    if(arr[b][a+1] == 0){
                        arr[b][a+1] = arr[b][a];
                        arr[b][a] = 0;
                    } else if(arr[b][a] == arr[b][a+1]) {
                        arr[b][a+1] = 2*arr[b][a];
                        arr[b][a] = 0;
                    }
                }
            }
        }
        int makeMove(){
            moveLeft();
        }
        int countProfit(int x){

        }
        int getVal(int x,int y){
            return arr[x][y];
        }
};

#endif