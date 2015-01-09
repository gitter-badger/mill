#include <stdlib.h>
#include "board.h"

point board[24];

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
