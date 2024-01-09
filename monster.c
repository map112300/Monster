#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print(char** monsterBoard, long rows, long cols){

    for(long i = 0; i < rows; i++){
        for(long j = 0; j < cols; j++){
            printf("%c ", monsterBoard[i][j]);
        }
        printf("\n");
    }

    return;
}

int main(int argc, char* argv[]){
    
    long cols = atol(argv[1]);
    long rows = atol(argv[2]);

    //command line inputs (start of game)
    long playerCol = atol(argv[3]);
    long playerRow = atol(argv[4]);

    long goalCol = atol(argv[5]);
    long goalRow = atol(argv[6]);

    long monsterCol = atol(argv[7]);
    long monsterRow = atol(argv[8]);

    //quick check to make sure board size is possible
    if(playerRow > rows || goalRow > rows || monsterRow > rows){
        printf("invalid dimensions\n");
        return 0;
    }

    if(playerCol > cols || goalCol > cols || monsterCol > cols){
        printf("invalid dimensions\n");
        return 0;
    }

    //create 2d array
    char** monsterBoard = malloc(sizeof(long*) * rows);//allocate number of rows
    for(long i = 0; i < rows; i++){//allocate number of columns
        monsterBoard[i] = malloc(sizeof(long) * cols);
    }
    

    

    //set board positions
    for(long i = 0; i < rows; i++){
        for(long j = 0; j < cols; j++){
            monsterBoard[i][j] = '.';
        }
    }
    //board at the start of game based on cmd line
    monsterBoard[(rows-1) - goalRow][goalCol] = 'G';
    monsterBoard[(rows-1) - playerRow][playerCol] = 'P';
    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';
    
    //print the board at the beginning of the game
    print(monsterBoard, rows, cols);

    
    while(!feof(stdin)){//two cases: monster moves + direction, player moves + direction

        char* userInput = NULL;
        size_t size = 0;
        getline(&userInput, &size, stdin);

        if(feof(stdin)){//winner case
            free(userInput);
            break;
        }


        
        if(strstr(userInput, "N")){//if player moves n
                
                monsterBoard[(rows-1) - playerRow][playerCol] = '.';//reset current player position
                playerRow++;
                //check if move is valid
                if((rows-1) - playerRow < 0){
                    printf("invalid move\n");
                    playerRow--;
                    free(userInput);
                    continue;
                }

                monsterBoard[(rows-1) - playerRow][playerCol] = 'P';
                if((rows-1) - playerRow == (rows-1) - goalRow && playerCol == goalCol){
                    printf("player wins!\n");
                    free(userInput);
                    break;
                }else if((rows-1) - playerRow == (rows-1) - monsterRow && playerCol == monsterCol){// if player moves onto monster spot, monster wins
                    printf("monster wins!\n");
                    free(userInput);
                    break;
                }
        }else if(strstr(userInput, "E")){//player moves east
                monsterBoard[(rows-1) - playerRow][playerCol] = '.';//reset current player position
                playerCol++;
                //check if move is valid
                if(playerCol >= cols){
                    printf("invalid move\n");
                    playerCol--;
                    free(userInput);
                    continue;
                }

                monsterBoard[(rows-1) - playerRow][playerCol] = 'P';
                if((rows-1) - playerRow == (rows-1) - goalRow && playerCol == goalCol){
                    printf("player wins!\n");
                    free(userInput);
                    break;
                }else if((rows-1) - playerRow == (rows-1) - monsterRow && playerCol == monsterCol){// if player moves onto monster spot, monster wins
                    printf("monster wins!\n");
                    free(userInput);
                    break;
                }

        }else if(strstr(userInput, "S")){//player moves south
                monsterBoard[(rows-1) - playerRow][playerCol] = '.';//reset current player position
                playerRow--;

                if((rows-1) - playerRow >= rows){
                    printf("invalid move\n");
                    playerRow++;
                    free(userInput);
                    continue;
                }

                monsterBoard[(rows-1) - playerRow][playerCol] = 'P';
                if((rows-1) - playerRow == (rows-1) - goalRow && playerCol == goalCol){
                    printf("player wins!\n");
                    free(userInput);
                    break;
                }else if((rows-1) - playerRow == (rows-1) - monsterRow && playerCol == monsterCol){// if player moves onto monster spot, monster wins
                    printf("monster wins!\n");
                    free(userInput);
                    break;
                }
                
        }else{//player moves west
                monsterBoard[(rows-1) - playerRow][playerCol] = '.';//reset current player position
                playerCol--;

                //check if move is valid
                if(playerCol < 0){
                    printf("invalid move\n");
                    playerCol++;
                    free(userInput);
                    continue;
                }

                monsterBoard[(rows-1) - playerRow][playerCol] = 'P';
                if((rows-1) - playerRow == (rows-1) - goalRow && playerCol == goalCol){
                    printf("player wins!\n");
                    free(userInput);
                    break;
                }else if((rows-1) - playerRow == (rows-1) - monsterRow && playerCol == monsterCol){// if player moves onto monster spot, monster wins
                    printf("monster wins!\n");
                    free(userInput);
                    break;
                }    
        }
            //NOW CONSIDER MONSTER MOVE
                long verticalDistance;//vertical distance between monster and player if negative then monster moves North if positive then monster moves S
                long horizontalDistance;//horizontal distance between monster and player if negative then monster moves E if positive monster moves W

                horizontalDistance = (monsterCol - playerCol);
                verticalDistance = ((rows - 1) - playerRow) - ((rows - 1) - monsterRow);
            
                if(verticalDistance < 0 && abs(verticalDistance) > abs(horizontalDistance)){//monster will move N

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = '.';//set inital spot to empty
                    monsterRow++;//increment monster row 
                    //check if monster row is valid
                    if((rows-1) - monsterRow < 0){
                        printf("invalid move\n");
                        monsterRow--;
                        free(userInput);
                        continue;
                    }else if((rows-1) - monsterRow == (rows-1) - goalRow && monsterCol == goalCol){//if monster moving north would cause him to be on the goal
                        printf("monster forfeits move. players turn\n");
                        print(monsterBoard,rows,cols);
                        monsterRow--;
                        free(userInput);
                        continue;
                    }

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';//move monster
                    if((rows-1) - monsterRow == (rows-1) - playerRow && monsterCol == playerCol){//case where monster moves to player position
                        printf("monster moves N\n");
                        printf("monster wins!\n");
                        free(userInput);
                        break;
                    }

                    printf("monster moves N\n");

                }else if(verticalDistance > 0 && abs(verticalDistance) > abs(horizontalDistance)){//monster will move S

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = '.';//set inital spot to empty
                    monsterRow--;//decrement monster row 
                    //check if monster row is valid
                    if((rows-1) - monsterRow >= rows){
                        printf("invalid move\n");
                        monsterRow++;
                        free(userInput);
                        continue;
                    }else if((rows-1) - monsterRow == (rows-1) - goalRow && monsterCol == goalCol){//monster forfeits move
                        printf("monster forfeits move. players turn\n");
                        print(monsterBoard,rows,cols);
                        monsterRow++;
                        free(userInput);
                        continue;
                    }

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';//move monster
                    if((rows-1) - monsterRow == (rows-1) - playerRow && monsterCol == playerCol){//case where monster moves to player position
                        printf("monster moves S\n");
                        printf("monster wins!\n");
                        free(userInput);
                        break;
                    }

                    printf("monster moves S\n");

                }else if(horizontalDistance < 0 && abs(horizontalDistance) > abs(verticalDistance)){//monster will E

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = '.';//set inital spot to empty
                    monsterCol++;//increment monster col
                    //check if monster row is valid
                    if(monsterCol >= cols){
                        printf("invalid move\n");
                        monsterCol--;
                        free(userInput);
                        continue;
                    }else if((rows-1) - monsterRow == (rows-1) - goalRow && monsterCol == goalCol){//monster forfeits move
                        printf("monster forfeits move. players turn\n");
                        print(monsterBoard,rows,cols);
                        monsterCol--;
                        free(userInput);
                        continue;
                    }

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';//move monster
                    if((rows-1) - monsterRow == (rows-1) - playerRow && monsterCol == playerCol){//case where monster moves to player position
                        printf("monster moves E\n");
                        printf("monster wins!\n");
                        free(userInput);
                        break;
                    }

                    printf("monster moves E\n");

                }else if(horizontalDistance > 0 && abs(horizontalDistance) > abs(verticalDistance)){//monster will move W

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = '.';//set inital spot to empty
                    monsterCol--;//decrement monster col 
                    //check if monster row is valid
                    if(monsterCol < 0){
                        printf("invalid move\n");
                        monsterCol++;
                        free(userInput);
                        continue;
                    }else if((rows-1) - monsterRow == (rows-1) - goalRow && monsterCol == goalCol){//monster forfeits move
                        printf("monster forfeits move. players turn\n");
                        print(monsterBoard,rows,cols);
                        monsterCol++;
                        free(userInput);
                        continue;
                    }

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';//move monster
                    if((rows-1) - monsterRow == (rows-1) - playerRow && monsterCol == playerCol){//case where monster moves to player position
                        printf("monster moves W\n");
                        printf("monster wins!\n");
                        free(userInput);
                        break;
                    }

                    printf("monster moves W\n");

                }else if(horizontalDistance < 0 && horizontalDistance == verticalDistance){//monster will move N if they are the same and negative

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = '.';//set inital spot to empty
                    monsterRow++;//increment monster row 
                    //check if monster row is valid
                    if((rows-1) - monsterRow < 0){
                        printf("invalid move\n");
                        monsterRow--;
                        free(userInput);
                        continue;
                    }else if((rows-1) - monsterRow == (rows-1) - goalRow && monsterCol == goalCol){//monster forfeits move
                        printf("monster forfeits move. players turn\n");
                        print(monsterBoard,rows,cols);
                        monsterRow--;
                        free(userInput);
                        continue;
                    }

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';//move monster
                    if((rows-1) - monsterRow == (rows-1) - playerRow && monsterCol == playerCol){//case where monster moves to player position
                        printf("monster moves N\n");
                        printf("monster wins!\n");
                        free(userInput);
                        break;
                    }

                    printf("monster moves N\n");

                }else{//monster will move S

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = '.';//set inital spot to empty
                    monsterRow--;//decrement monster row 
                    //check if monster row is valid
                    if((rows-1) - monsterRow >= rows){
                        printf("invalid move\n");
                        monsterRow++;
                        free(userInput);
                        continue;
                    }else if((rows-1) - monsterRow == (rows-1) - goalRow && monsterCol == goalCol){//monster forfeits move
                        printf("monster forfeits move. players turn\n");
                        print(monsterBoard,rows,cols);
                        monsterRow++;
                        free(userInput);
                        continue;
                    }

                    monsterBoard[(rows-1) - monsterRow][monsterCol] = 'M';//move monster
                    if((rows-1) - monsterRow == (rows-1) - playerRow && monsterCol == playerCol){//case where monster moves to player position
                        printf("monster moves S\n");
                        printf("monster wins!\n");
                        free(userInput);
                        break;
                    }
                    printf("monster moves S\n");
                }


        //PLAYER MOVES
        print(monsterBoard,rows, cols);
        free(userInput);

        }
   
    //free dynamically allocated memory
    for(long i = 0; i < rows; i++){
        free(monsterBoard[i]);
    }
    free(monsterBoard);
}
