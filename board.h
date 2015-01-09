#ifndef BOARD_H_
#define BOARD_H_

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

typedef struct point {
	char allocation;
	struct point* left;
	struct point* right;
	struct point* bottom;
	struct point* top;
} point;

void initialize_board();

extern point board[24];

#endif
