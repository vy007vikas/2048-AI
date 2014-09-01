#ifndef __ALGO_C__
#define __ALGO_C__

#include <bits/stdc++.h>

#include "board.cpp"

using namespace std;

const string possMovesByPlayer = "wasd";

//here we do alpha-beta pruning to find out which move should be best for the computer
/*
    function alpha-beta   --> main function to do minimax with alpha-beta pruning to find the most optimal move for the computer

    -->params
    1. depth --> stores the depth of the tree proceesed
    2. board --> an instance of board at which we do modifications
    3. alpha --> an algorithm parameter (maximum lower bound)
    4. beta --> an algorithm paramter (minimum upper bound)
    5. player --> if 1 then player is user (ie AI) else it is computer (ie random tile placer)

    it returns the best possible move for the AI that is good even in the worst case
*/

int alphabeta(int depth,Board &board,int alpha,int beta,int player){
    int bestScore,bestMove;
    if(board.isGameOver()){
        //return game over case
        return;
    } else if (depth==0){
        //return the leaf node score
        return;
    }
    //if the player is the AI
    if(player==1){
        //iterate over all possible moves ie w,a,s,d
        int tmp;
        for(int a=0;a<4;a++){
            //now init a new board and perform that move on that board
            Board newBoard;
            board.CloneBoard(newBoard);
            Move myMove(possMovesByPlayer[a]);
            myMove.doMove(newBoard);
            //now recursing to more deeper levels and applying the algo
            tmp = alphabeta(depth-1,newBoard,alpha,beta,0);
            //apply aplha-beta pruning conditions to make minimax faster
            if(newBoard.currScore > alpha){
                alpha = newBoard.currScore;
                bestMove = a;
            }
            if(beta<=alpha){
                break;   //cutoff situation
            }
        }
        bestScore = alpha;
    } else {
        //if the player is computer randomizer
        //get a vector of all possible empty situations
        //now there can be 2 tiles that can be placed 2,4
        //so we have 2*(no of empty tiles) nodes from this tree
        vector < pair <int,int> > possMoves;
        possMoves = board.findAllPossMoves();
        int len = possMoves.size();
        bool flag = false;
        for(int a=0;a<len;a++){
            for(int b=2;b<=4;b+=2){
                Board newBoard;
                board.CloneBoard(newBoard);
                newBoard.arr[possMoves[a][b].first][possMoves[a][b].second] = b;
                //now recursing to more deeper levels
                if(newBoard.currScore < beta){
                    beta = newBoard.currScore;
                }
                if(beta<=alpha){
                    flag = true;
                    break;   //cutoff situation
                }
            }
            if(flag)        break;
        }
        bestScore = beta;
        if(len==0)      bestScore = 0;
    }
}

#endif