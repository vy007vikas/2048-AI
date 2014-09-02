#ifndef __ALGO_C__
#define __ALGO_C__

#include <bits/stdc++.h>

#include "board.cpp"

using namespace std;

const string possMovesByPlayer = "wasd";

/*
    how do i calculate the heuristicScore:

    basically give priority to the score increased and the number of cells freed
*/

void calculateHeuristicScore(Board& board){
    board.heuristicScore = (board.currScore)*(100);
    board.heuristicScore += pow(2,board.noOfEmptyCells);
}

//here we do alpha-beta pruning to find out which move should be best for the computer
/*
    function alpha-beta   --> main function to do minimax with alpha-beta pruning to find the most optimal move for the computer

    -->params
    1. depth --> stores the depth of the tree proceesed
    2. board --> an instance of board at which we do modifications
    3. alpha --> an algorithm parameter (maximum lower bound)
    4. beta --> an algorithm paramter (minimum upper bound)
    5. player --> if 1 then player is user (ie AI) else it is computer (ie random tile placer)

    it returns the best possible move for the AI that is good even in the worst case and the best heuristic score
*/

pair <int,int> alphabeta(int depth,Board& board,int alpha,int beta,int player){
    //cout<<"A"<<endl;
    pair <int,int> tmp;
    pair <int,int> bestPair;   //stores the best move and the best score
    bestPair = make_pair(0,0);
    if(board.isGameOver()){
        //return game over case
        return make_pair(0,0);
    } else if (depth==0){
        //return the leaf node score
        calculateHeuristicScore(board);
        return make_pair(0,board.heuristicScore);
    }
    //if the player is the AI
    if(player==1){
        //iterate over all possible moves ie w,a,s,d
        for(int a=0;a<4;a++){
            //now init a new board and perform that move on that board
            Board newBoard;
            board.CloneBoard(newBoard);
            Move myMove(possMovesByPlayer[a]);
            myMove.doMove(newBoard);
            //if there is no change
            if(board.isEqual(newBoard)){
                continue;
            }
            //now recursing to more deeper levels and applying the algo
            tmp = alphabeta(depth-1,newBoard,alpha,beta,0);
            //apply aplha-beta pruning conditions to make minimax faster
            if(tmp.second > alpha){
                alpha = tmp.second;
                bestPair.first = a;
            }
            if(beta<=alpha){
                break;   //cutoff situation
            }
        }
        bestPair.second = alpha;
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
                newBoard.arr[possMoves[a].first][possMoves[a].second] = b;
                calculateHeuristicScore(board);
                //now recursing to more deeper levels
                tmp = alphabeta(depth-1,newBoard,alpha,beta,1);
                if(tmp.second < beta){
                    beta = tmp.second;
                }
                if(beta<=alpha){
                    flag = true;
                    break;   //cutoff situation
                }
            }
            if(flag)        break;
        }
        bestPair.second = beta;
        if(len==0)      bestPair.second = 0;
    }
    return bestPair;
}

#endif