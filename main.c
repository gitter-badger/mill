#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <unistd.h>




typedef struct points {
	char allocation;
	struct points* left;
	struct points* right;
	struct points* bottom;
	struct points* top;
}points;

points board[24];

/*
	::Board::

	00____________01____________02
	|              |             |
	|   08________09________10   |
	|    |         |         |   |
	|    |	 16___17___18    |   |
	|    |    |         |    |   |
    07__15___23        19___11__03
    |    |    |         |    |   |
    |    |   22___21___20    |   |
    |    |         |         |   |
	|   14________13________12   |
	|              |             |
	06____________05____________04
	
	all Points can be classified by 8 classes 0-7 describable by calculating i mod 8
	there are 4 points with special forms depending on their position
	i mod 8 == 1
	i mod 8 == 3
	i mod 8 == 5
	i mod 8 == 7

	all need to be tested on the cases 
	(1) i>8 for getting an additional edge back to the previous vertex and
	(2) i<2*8 for getting an edge to the next vertex


 */



void initialize_board(){
	int i;

	//Grundinitialisierung
	for (i = 0; i < 24; i++)
	{
		board[i].allocation=0;

		board[i].left=NULL;
		board[i].right=NULL;
		board[i].bottom=NULL;
		board[i].top=NULL;


		//set the edges ... see sketch above
		switch(i%8) {
			case 0: 
			board[i].right=&board[i+1];
			board[i].bottom=&board[i+7];
			break;
			
			case 1: 
			board[i].left=&board[i-1];
			board[i].right=&board[i+1];
			if(i<2*8) board[i].bottom=&board[i+8];
			if(i>8) board[i].top=&board[i-8];
			break;

			case 2: 
			board[i].left=&board[i-1];
			board[i].bottom=&board[i+1];
			break;

			case 3: 
			board[i].top=&board[i-1];
			board[i].bottom=&board[i+1];
			if(i<2*8) board[i].left=&board[i+8];
			if(i>8) board[i].right=&board[i-8]; 
			break;

			case 4: 
			board[i].left=&board[i+1];
			board[i].top=&board[i-1];
			break;

			case 5: 
			board[i].left=&board[i+1];
			board[i].right=&board[i-1];
			if(i<2*8) board[i].top=&board[i+8];
			if(i>8) board[i].bottom=&board[i-8];
			break;

			case 6: 
			board[i].top=&board[i+1];
			board[i].right=&board[i-1];
			break;
			
			case 7: 
			board[i].bottom=&board[i-1];
			board[i].top=&board[i-7];
			if(i<2*8) board[i].right=&board[i+8]; 
			if(i>8) board[i].left=&board[i-8];
			break;

			default: break;
		}
	}

}

int creates_mill_hor (int player, int targetpoint){

		int result=0;
		//set the edges ... see sketch above
		switch(targetpoint%8) {
			case 0: 
			result=board[targetpoint].allocation * board[targetpoint+1].allocation * board[targetpoint+2].allocation;
			break;
			
			case 1: 
			result=board[targetpoint-1].allocation * board[targetpoint].allocation * board[targetpoint+1].allocation;
			break;

			case 2: 
			result=board[targetpoint-2].allocation * board[targetpoint-1].allocation * board[targetpoint].allocation;
			break;

			case 3: 
			result=board[targetpoint-2].allocation * board[targetpoint-1].allocation * board[targetpoint].allocation; 
			break;

			/*case 4: 
			board[i].left=&board[i+1];
			board[i].top=&board[i-1];
			break;

			case 5: 
			board[i].left=&board[i+1];
			board[i].right=&board[i-1];
			if(i<2*8) board[i].top=&board[i+8];
			if(i>8) board[i].bottom=&board[i-8];
			break;

			case 6: 
			board[i].top=&board[i+1];
			board[i].right=&board[i-1];
			break;
			
			case 7: 
			board[i].bottom=&board[i-1];
			board[i].top=&board[i-7];
			if(i<2*8) board[i].right=&board[i+8]; 
			if(i>8) board[i].left=&board[i-8];
			break;

			default: break;*/
		}
	
	return 0;
}


void get_token(int point_number, char token[]){
	char player_token[2]={64, 35};

	//if point is not set
	if(board[point_number].allocation==0){
		//set first digit
		if (point_number<10){
			token[0]=48;			
		}else if(point_number<20){
			token[0]=49;
		} else{
			token[0]=50;
		}
		//set second digit
		token[1]=48+(point_number%10); // point_number mod 10 being last digit of the number
	
	//if point is set
	}else{
		//set the char-array to the token-signs of the player that has a token at the point
		char allocation = (board[point_number].allocation)-1;

		token[0]=player_token[allocation];
		token[1]=player_token[allocation];
	}
}

void print_board_allocation(){


	int i;
	char* token;
	char* token_list[24];

	for (i = 0; i<24;i++){
		token = (char*)malloc(2*sizeof(char));
		get_token(i, token);
		token_list[i]=token;
		
	}

	printf("%s____________%s____________%s\n", token_list[0], token_list[1], token_list[2] );
	printf("|              |             |\n");
	printf("|   %s________%s________%s   |\n", token_list[8], token_list[9], token_list[10]);
	printf("|    |         |         |   |\n");
	printf("|    |	 %s___%s___%s    |   |\n", token_list[16], token_list[17], token_list[18]);
	printf("|    |    |         |    |   |\n");
	printf("%s__%s___%s        %s___%s__%s\n", token_list[7], token_list[15], token_list[23], token_list[19], token_list[11], token_list[3]);
	printf("|    |    |         |    |   |\n");
	printf("|    |   %s___%s___%s    |   |\n", token_list[22], token_list[21], token_list[20]);
	printf("|    |         |         |   |\n");
	printf("|   %s________%s________%s   |\n", token_list[14], token_list[13], token_list[12]);
	printf("|              |             |\n");
	printf("%s____________%s____________%s\n\n", token_list[6], token_list[5], token_list[4]);
}



int main(int argc, char const *argv[])
{


	initialize_board();
	print_board_allocation();

	
	//phase 1 -- set all points
	int move, player=1, targetpoint, success;
	srand(time(NULL));

	for ( move = 0; move < 9*2; ++move)
	{
		
		if(player==1){
			printf("\n\n================\nSpieler\n");
		}else {
			printf("\n\n================\nComputer\n");
		}


		success=0;

		while(!success){
			printf("Auf welches Spielfeld willst du setzen?\n");
			if (player==1){
				scanf("%d", &targetpoint);
			}
			else{
			 	targetpoint = rand() % 24;
			 	//sleep(1);
			 	printf("%d\n", targetpoint);
			 }
			

			if (targetpoint<24)
			{		
				if (board[targetpoint].allocation==0)
				{
					board[targetpoint].allocation=player;
					success=1;
					print_board_allocation();
				}else{
					printf("Nein das Feld ist schon besetzt!!!\nNochmal..");
				}
			}else{
				printf("Nein das Feld gibt es nicht!!!\nNochmal..");
			}

		}

		//TODO: creates_mill???
			


		//player = (player==1)?2:1; 
		if (player==1)
			player=2;
		else 
			player=1;
	}

	return 0;
}