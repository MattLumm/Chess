/**********
Matthew Lum 
Chess
01/25/2015

**************
stuff I need to add
fix bishop #done
add queen #done
add king
add black side
add turns
add checkmate mech


*************/

#include<iostream> 
#include <windows.h>
using namespace std;

//map size
#define mapWidth 8
#define mapHeight 8
//pieces
#define blank 0
#define wPawn 1
#define wRook 2
#define wKnight 3
#define wBishop 4
#define wQueen 5
#define wKing 6
#define bPawn 7
#define bRook 8
#define bKnight 9
#define bBishop 10
#define bQueen 11
#define bKing 12
//#define cursore 13
#define open 14
#define check 15

//number of keys detected
#define numKeys 6
//number of icons
#define numIcons 16

//gobal vaules
int cursorHeight = 4;
int cursorWidth = 4;
int selectedPiece;
int selectedHeight;
int selectedWidth;
int tempIcon = 0;
int g;
int temp = 0;
bool go = true;

//function prototypes
bool checkW(int Height, int Width);
bool checkB(int Height, int Width);

//array of piece icons
char pieceIcons[numIcons] = { '.', 'p', 'r', 'n', 'b', 'q', 'k', 'P', 'R', 'N', 'B', 'Q', 'K', '@','#','C' };

//array of arrow key's virtual key's
int arrowKeys[numKeys] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE, VK_RETURN};

//map creation
//int mapArray[mapHeight][mapWidth];
int mapArray[mapHeight][mapWidth] = {
		{ 2, 3, 4, 5, 6, 4, 3, 2, },
		{ 1, 1, 1, 1, 1, 1, 1, 1, },
		{ 0, 9, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 4, 2, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 7, 7, 7, 7, 7, 7, 7, 7, },
		{ 8, 9, 10, 11, 12, 10, 9, 8, }
};
//map copy
int mapCopy[mapHeight][mapWidth] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 1, 1, 1, 1, 1, 1, 1, 1, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, },
		{ 7, 7, 7, 7, 7, 7, 7, 7, },
		{ 8, 9, 10, 11, 12, 10, 9, 8, }
};

void drawMap()
{
	for (int clear = 0; clear < 15; clear++)
	{
		cout << endl;
	}
	for (int i = 0; i < mapHeight; i++)
	{
		//moves prints to next line
		cout << endl;
		for (int j = 0; j < mapWidth; j++)
		{
			//checks for and prints piece
			for (int index = 0; index < numIcons; index++)
			{
				if (mapArray[i][j] == index)
					cout << pieceIcons[index];
			}
		}
	}
	cout << endl;
}
void drawCopy()
{
	for (int clear = 0; clear < 15; clear++)
	{
		cout << endl;
	}
	for (int i = 0; i < mapHeight; i++)
	{
		//moves prints to next line
		cout << endl;
		for (int j = 0; j < mapWidth; j++)
		{
			//checks for and prints piece
			for (int index = 0; index < numIcons; index++)
			{
				if (mapCopy[i][j] == index)
					cout << pieceIcons[index];
			}
		}
	}
	cout << endl;
}
//cursore displayed as @
void drawCursor()
{
	tempIcon = mapArray[cursorHeight][cursorWidth];
	mapArray[cursorHeight][cursorWidth] = 13;


}
//used to see move options for chess piece
//called by crusorMove when enter is pressed
//should display possible plays
// 2 for each chess piece (black/white)
//copys the ints to a snd Map
void copyMap()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			mapCopy[i][j] = mapArray[i][j];
		}
	}

}
//puts copy onto origanl
void reverseCopyMap()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			mapArray[i][j] = mapCopy[i][j];
		}
	}

}
//copys map only when no #'s are on map
void checkBoard()
{
	
	int counter = 0;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (mapArray[i][j] != open)
			{

				counter++;
				if (counter == mapHeight*mapWidth)
				{
					copyMap();
					
				}
			}

		}
	}
}

void select()
{

	//copys map only when no #'s are on map
	checkBoard();


	//note to self add cancle button
	switch (tempIcon)
	{
	case open:
		if (mapArray[cursorHeight][cursorWidth] == open)
		{
			mapCopy[cursorHeight][cursorWidth] = selectedPiece;
			mapCopy[selectedHeight][selectedWidth] = blank;
			reverseCopyMap();

		}

		break;

		//if (tempIcon == wPawn)
	case wPawn:
		//nts add promotion ability
		reverseCopyMap();
		//allows the wPawn it's first double jump
		//checks both 1 and 2 in front of pawn
		if (cursorHeight == 1 && mapArray[cursorHeight + 2][cursorWidth] == blank && mapArray[cursorHeight + 1][cursorWidth] == blank)
		{
			mapArray[cursorHeight + 2][cursorWidth] = open;
		}
		//checks 1 in front
		if (mapArray[cursorHeight + 1][cursorWidth] == blank)
		{
			mapArray[cursorHeight + 1][cursorWidth] = open;
		}
		//checks diagonal right for black 
		if (mapArray[cursorHeight + 1][cursorWidth + 1] == 7
			|| mapArray[cursorHeight + 1][cursorWidth + 1] == 8
			|| mapArray[cursorHeight + 1][cursorWidth + 1] == 9
			|| mapArray[cursorHeight + 1][cursorWidth + 1] == 10
			|| mapArray[cursorHeight + 1][cursorWidth + 1] == 11
			//|| mapArray[cursorHeight + 1][cursorWidth + 1] == 12
			)
		{
			mapArray[cursorHeight + 1][cursorWidth + 1] = open;
		}
		//checks diagonal left for ememies
		if (mapArray[cursorHeight + 1][cursorWidth - 1] == 7
			|| mapArray[cursorHeight + 1][cursorWidth - 1] == 8
			|| mapArray[cursorHeight + 1][cursorWidth - 1] == 9
			|| mapArray[cursorHeight + 1][cursorWidth - 1] == 10
			|| mapArray[cursorHeight + 1][cursorWidth - 1] == 11
			//|| mapArray[cursorHeight + 1][cursorWidth - 1] == 12
			)
		{
			mapArray[cursorHeight + 1][cursorWidth - 1] = open;
		}
		//makes the next # selected a wPawn
		selectedPiece = wPawn;
		selectedWidth = cursorWidth;
		selectedHeight = cursorHeight;
		break;

	case wRook:
		reverseCopyMap();
		//checks up
		for (int i = cursorHeight - 1; i >= 0; i--)
		{
			if (mapArray[i][cursorWidth] == blank)
			{
				mapArray[i][cursorWidth] = open;
			}
			//checks for black 
			if (checkB(i,cursorWidth)
			{
				//checks for king
				if (mapArray[i][cursorWidth] == bKing)
				{
					break;
				}
				mapArray[i][cursorWidth] = open;
				break;
			}
			//checks for whites
			if (mapArray[i][cursorWidth] == wPawn
				|| mapArray[i][cursorWidth] == wRook
				|| mapArray[i][cursorWidth] == wKnight
				|| mapArray[i][cursorWidth] == wBishop
				|| mapArray[i][cursorWidth] == wQueen
				|| mapArray[i][cursorWidth] == wKing
				)
			{
				break;
			}



		}
		
		//check down
		for (int i = cursorHeight + 1; i <= mapHeight - 1; i++)
		{
			if (mapArray[i][cursorWidth] == blank)
			{
				mapArray[i][cursorWidth] = open;
			}
			//checks for black 
			if (checkB(i, cursorWidth))
			{
				//checks for king
				if (mapArray[i][cursorWidth] == bKing)
				{
					break;
				}
				mapArray[i][cursorWidth] = open;
				break;
			}
			//checks for whites
			if (mapArray[i][cursorWidth] == wPawn
				|| mapArray[i][cursorWidth] == wRook
				|| mapArray[i][cursorWidth] == wKnight
				|| mapArray[i][cursorWidth] == wBishop
				|| mapArray[i][cursorWidth] == wQueen
				|| mapArray[i][cursorWidth] == wKing
				)
			{
				break;
			}
		}
		//check left
		for (int i = cursorWidth - 1; i >= 0; i--)
		{
			if (mapArray[cursorHeight][i] == blank)
			{
				mapArray[cursorHeight][i] = open;
			}
			//checks for black 
			if (mapArray[cursorHeight][i] == bPawn
				|| mapArray[cursorHeight][i] == bRook
				|| mapArray[cursorHeight][i] == bKnight
				|| mapArray[cursorHeight][i] == bBishop
				|| mapArray[cursorHeight][i] == bQueen
				|| mapArray[cursorHeight][i] == bKing
				)
			{
				//checks for king
				if (mapArray[cursorHeight][i] == bKing)
				{
					break;
				}
				mapArray[cursorHeight][i] = open;
				break;
			}
			//checks for whites
			if (mapArray[cursorHeight][i] == wPawn
				|| mapArray[cursorHeight][i] == wRook
				|| mapArray[cursorHeight][i] == wKnight
				|| mapArray[cursorHeight][i] == wBishop
				|| mapArray[cursorHeight][i] == wQueen
				|| mapArray[cursorHeight][i] == wKing
				)
			{
				break;
			}
		}
		//check right
		for (int i = cursorWidth + 1; i <= mapWidth - 1; i++)
		{
			if (mapArray[cursorHeight][i] == blank)
			{
				mapArray[cursorHeight][i] = open;
			}
			//checks for black 
			if (mapArray[cursorHeight][i] == bPawn
				|| mapArray[cursorHeight][i] == bRook
				|| mapArray[cursorHeight][i] == bKnight
				|| mapArray[cursorHeight][i] == bBishop
				|| mapArray[cursorHeight][i] == bQueen
				|| mapArray[cursorHeight][i] == bKing
				)
			{
				//checks for king
				if (mapArray[i][cursorWidth] == bKing)
				{
					break;
				}
			mapArray[cursorHeight][i] = open;
			break;
			}
			//checks for whites
			if (mapArray[cursorHeight][i] == wPawn
				|| mapArray[cursorHeight][i] == wRook
				|| mapArray[cursorHeight][i] == wKnight
				|| mapArray[cursorHeight][i] == wBishop
				|| mapArray[cursorHeight][i] == wQueen
				|| mapArray[cursorHeight][i] == wKing
				)
			{
				break;
			}
		}
		//makes the next # selected a wRook
		selectedPiece = wRook;
		selectedWidth = cursorWidth;
		selectedHeight = cursorHeight;

		break;


	case wKnight:
		reverseCopyMap();
		//down moves
		// left
		temp = -1;
		if (cursorHeight + 1 <= mapHeight - 1 && cursorWidth - 2 >= 0)
			temp = mapArray[cursorHeight + 1][cursorWidth - 2];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight + 1][cursorWidth - 2] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight + 1][cursorWidth - 2] = check;
			}
		}
		//right
		temp = -1;
		if (cursorHeight + 1 <= mapHeight - 1 && cursorWidth + 2 <= mapWidth - 1)
			temp = mapArray[cursorHeight + 1][cursorWidth + 2];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight + 1][cursorWidth + 2] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight + 1][cursorWidth + 2] = check;
			}
		}
		//bottom right
		temp = -1;
		if (cursorHeight + 2 <= mapHeight - 1 && cursorWidth + 1 <= mapWidth - 1)
			temp = mapArray[cursorHeight + 2][cursorWidth + 1];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight + 2][cursorWidth + 1] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight + 2][cursorWidth + 1] = check;
			}
		}
		//bottom left
		temp = -1;
		if (cursorHeight + 2 <= mapHeight - 1 && cursorWidth - 1 >= 0)
			temp = mapArray[cursorHeight + 2][cursorWidth - 1];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight + 2][cursorWidth - 1] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight + 2][cursorWidth - 1] = check;
			}
		}
		//up moves
		//right
		temp = -1;
		if (cursorHeight - 1 >= 0 && cursorWidth + 2 <= mapWidth - 1)
			temp = mapArray[cursorHeight - 1][cursorWidth + 2];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight - 1][cursorWidth + 2] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight - 1][cursorWidth + 2] = check;
			}
		}
		//upper right
		temp = -1;
		if (cursorHeight - 2 >= 0 && cursorWidth + 1 <= mapWidth - 1)
			temp = mapArray[cursorHeight - 2][cursorWidth + 1];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight - 2][cursorWidth + 1] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight - 2][cursorWidth + 1] = check;
			}
		}
		//upper left
		temp = -1;
		if (cursorHeight - 2 >= 0 && cursorWidth - 1 >= 0)
			temp = mapArray[cursorHeight - 2][cursorWidth - 1];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight - 2][cursorWidth - 1] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight - 2][cursorWidth - 1] = check;
			}
		}
		//left
		temp = -1;
		if (cursorHeight - 1 >= 0 && cursorWidth - 2 >= 0)
			temp = mapArray[cursorHeight - 1][cursorWidth - 2];
		if (temp == blank || temp == bPawn || temp == bRook || temp == bKnight || temp == bBishop || temp == bQueen || temp == bKing)
		{

			mapArray[cursorHeight - 1][cursorWidth - 2] = open;
			if (temp == bKing)
			{
				mapArray[cursorHeight - 1][cursorWidth - 2] = check;
			}
		}

		//makes the next # selected a wKnight
		selectedPiece = wKnight;
		selectedWidth = cursorWidth;
		selectedHeight = cursorHeight;
		break;

	case wBishop:
		reverseCopyMap();
		//checks top left
		
		
		for (int i = 1; i < mapHeight; i++)
		{
			if (cursorHeight-i>=0 && cursorWidth-i >= 0)
			{


				if (mapArray[cursorHeight - i][cursorWidth - i] == blank)
				{
					mapArray[cursorHeight - i][cursorWidth - i] = open;
				}
				//checks for black 
				if (mapArray[cursorHeight - i][cursorWidth - i] == bPawn
					|| mapArray[cursorHeight - i][cursorWidth - i] == bRook
					|| mapArray[cursorHeight - i][cursorWidth - i] == bKnight
					|| mapArray[cursorHeight - i][cursorWidth - i] == bBishop
					|| mapArray[cursorHeight - i][cursorWidth - i] == bQueen
					|| mapArray[cursorHeight - i][cursorWidth - i] == bKing
					)
				{
					//checks for king
					if (mapArray[cursorHeight - i][cursorWidth - i] == bKing)
					{
						break;
					}
					mapArray[cursorHeight - i][cursorWidth - i] = open;
					break;
				}
				//checks for whites
				if (mapArray[cursorHeight - i][cursorWidth - i] == wPawn
					|| mapArray[cursorHeight - i][cursorWidth - i] == wRook
					|| mapArray[cursorHeight - i][cursorWidth - i] == wKnight
					//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
					|| mapArray[cursorHeight - i][cursorWidth - i] == wQueen
					|| mapArray[cursorHeight - i][cursorWidth - i] == wKing
					)
				{
					break;
				}
			}
		}
		
		//checks for bot right
		
		for (int i = 0; i < mapHeight; i++)
		{
			if (cursorHeight+i<mapHeight && cursorWidth+i< mapWidth)
			{


				if (mapArray[cursorHeight + i][cursorWidth + i] == blank)
				{
					mapArray[cursorHeight + i][cursorWidth + i] = open;
				}
				//checks for black 
				if (mapArray[cursorHeight + i][cursorWidth + i] == bPawn
					|| mapArray[cursorHeight + i][cursorWidth + i] == bRook
					|| mapArray[cursorHeight + i][cursorWidth + i] == bKnight
					|| mapArray[cursorHeight + i][cursorWidth + i] == bBishop
					|| mapArray[cursorHeight + i][cursorWidth + i] == bQueen
					|| mapArray[cursorHeight + i][cursorWidth + i] == bKing
					)
				{
					//checks for king
					if (mapArray[cursorHeight + i][cursorWidth + i] == bKing)
					{
						break;
					}
					mapArray[cursorHeight + i][cursorWidth + i] = open;
					break;
				}
				//checks for whites
				if (mapArray[cursorHeight + i][cursorWidth + i] == wPawn
					|| mapArray[cursorHeight + i][cursorWidth + i] == wRook
					|| mapArray[cursorHeight + i][cursorWidth + i] == wKnight
					//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
					|| mapArray[cursorHeight + i][cursorWidth + i] == wQueen
					|| mapArray[cursorHeight + i][cursorWidth + i] == wKing
					)
				{
					break;
				}
			}
		}
		
		//checks for top right
		
		
		for (int i = 0; i < mapHeight; i++)
		{
			if (cursorHeight-i>=0 && cursorWidth+i< mapWidth)
			{


				if (mapArray[cursorHeight - i][cursorWidth + i] == blank)
				{
					mapArray[cursorHeight - i][cursorWidth + i] = open;
				}
				//checks for black 
				if (mapArray[cursorHeight - i][cursorWidth + i] == bPawn
					|| mapArray[cursorHeight - i][cursorWidth + i] == bRook
					|| mapArray[cursorHeight - i][cursorWidth + i] == bKnight
					|| mapArray[cursorHeight - i][cursorWidth + i] == bBishop
					|| mapArray[cursorHeight - i][cursorWidth + i] == bQueen
					|| mapArray[cursorHeight - i][cursorWidth + i] == bKing
					)
				{
					//checks for king
					if (mapArray[cursorHeight - i][cursorWidth + i] == bKing)
					{
						break;
					}
					mapArray[cursorHeight - i][cursorWidth + i] = open;
					break;
				}
				//checks for whites
				if (mapArray[cursorHeight - i][cursorWidth + i] == wPawn
					|| mapArray[cursorHeight - i][cursorWidth + i] == wRook
					|| mapArray[cursorHeight - i][cursorWidth + i] == wKnight
					//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
					|| mapArray[cursorHeight - i][cursorWidth + i] == wQueen
					|| mapArray[cursorHeight - i][cursorWidth + i] == wKing
					)
				{
					break;
				}
			}
		}

		//checks for bot left


		for (int i = 0; i < mapHeight; i++)
		{
			if (cursorHeight + i<mapHeight && cursorWidth - i>=0)
			{


				if (mapArray[cursorHeight + i][cursorWidth - i] == blank)
				{
					mapArray[cursorHeight + i][cursorWidth - i] = open;
				}
				//checks for black 
				if (mapArray[cursorHeight + i][cursorWidth - i] == bPawn
					|| mapArray[cursorHeight + i][cursorWidth - i] == bRook
					|| mapArray[cursorHeight + i][cursorWidth - i] == bKnight
					|| mapArray[cursorHeight + i][cursorWidth - i] == bBishop
					|| mapArray[cursorHeight + i][cursorWidth - i] == bQueen
					|| mapArray[cursorHeight + i][cursorWidth - i] == bKing
					)
				{
					//checks for king
					if (mapArray[cursorHeight + i][cursorWidth - i] == bKing)
					{
						break;
					}
					mapArray[cursorHeight + i][cursorWidth - i] = open;
					break;
				}
				//checks for whites
				if (mapArray[cursorHeight + i][cursorWidth - i] == wPawn
					|| mapArray[cursorHeight + i][cursorWidth - i] == wRook
					|| mapArray[cursorHeight + i][cursorWidth - i] == wKnight
					//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
					|| mapArray[cursorHeight + i][cursorWidth - i] == wQueen
					|| mapArray[cursorHeight + i][cursorWidth - i] == wKing
					)
				{
					break;
				}
			}
		}


				selectedPiece = wBishop;
				selectedWidth = cursorWidth;
				selectedHeight = cursorHeight;
				break;
			
		case wQueen:
			reverseCopyMap();
			//diagonals
			//checks top left
			for (int i = 1; i < mapHeight; i++)
			{
				if (cursorHeight - i >= 0 && cursorWidth - i >= 0)
				{


					if (mapArray[cursorHeight - i][cursorWidth - i] == blank)
					{
						mapArray[cursorHeight - i][cursorWidth - i] = open;
					}
					//checks for black 
					if (mapArray[cursorHeight - i][cursorWidth - i] == bPawn
						|| mapArray[cursorHeight - i][cursorWidth - i] == bRook
						|| mapArray[cursorHeight - i][cursorWidth - i] == bKnight
						|| mapArray[cursorHeight - i][cursorWidth - i] == bBishop
						|| mapArray[cursorHeight - i][cursorWidth - i] == bQueen
						|| mapArray[cursorHeight - i][cursorWidth - i] == bKing
						)
					{
						//checks for king
						if (mapArray[cursorHeight - i][cursorWidth - i] == bKing)
						{
							break;
						}
						mapArray[cursorHeight - i][cursorWidth - i] = open;
						break;
					}
					//checks for whites
					if (mapArray[cursorHeight - i][cursorWidth - i] == wPawn
						|| mapArray[cursorHeight - i][cursorWidth - i] == wRook
						|| mapArray[cursorHeight - i][cursorWidth - i] == wKnight
						|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
						//|| mapArray[cursorHeight - i][cursorWidth - i] == wQueen
						|| mapArray[cursorHeight - i][cursorWidth - i] == wKing
						)
					{
						break;
					}
				}
			}

			//checks for bot right

			for (int i = 1; i < mapHeight; i++)
			{
				if (cursorHeight + i<mapHeight && cursorWidth + i< mapWidth)
				{


					if (mapArray[cursorHeight + i][cursorWidth + i] == blank)
					{
						mapArray[cursorHeight + i][cursorWidth + i] = open;
					}
					//checks for black 
					if (mapArray[cursorHeight + i][cursorWidth + i] == bPawn
						|| mapArray[cursorHeight + i][cursorWidth + i] == bRook
						|| mapArray[cursorHeight + i][cursorWidth + i] == bKnight
						|| mapArray[cursorHeight + i][cursorWidth + i] == bBishop
						|| mapArray[cursorHeight + i][cursorWidth + i] == bQueen
						|| mapArray[cursorHeight + i][cursorWidth + i] == bKing
						)
					{
						//checks for king
						if (mapArray[cursorHeight + i][cursorWidth + i] == bKing)
						{
							break;
						}
						mapArray[cursorHeight + i][cursorWidth + i] = open;
						break;
					}
					//checks for whites
					if (mapArray[cursorHeight + i][cursorWidth + i] == wPawn
						|| mapArray[cursorHeight + i][cursorWidth + i] == wRook
						|| mapArray[cursorHeight + i][cursorWidth + i] == wKnight
						//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
						|| mapArray[cursorHeight + i][cursorWidth + i] == wQueen
						|| mapArray[cursorHeight + i][cursorWidth + i] == wKing
						)
					{
						break;
					}
				}
			}

			//checks for top right


			for (int i = 1; i < mapHeight; i++)
			{
				if (cursorHeight - i >= 0 && cursorWidth + i< mapWidth)
				{


					if (mapArray[cursorHeight - i][cursorWidth + i] == blank)
					{
						mapArray[cursorHeight - i][cursorWidth + i] = open;
					}
					//checks for black 
					if (mapArray[cursorHeight - i][cursorWidth + i] == bPawn
						|| mapArray[cursorHeight - i][cursorWidth + i] == bRook
						|| mapArray[cursorHeight - i][cursorWidth + i] == bKnight
						|| mapArray[cursorHeight - i][cursorWidth + i] == bBishop
						|| mapArray[cursorHeight - i][cursorWidth + i] == bQueen
						|| mapArray[cursorHeight - i][cursorWidth + i] == bKing
						)
					{
						//checks for king
						if (mapArray[cursorHeight - i][cursorWidth + i] == bKing)
						{
							break;
						}
						mapArray[cursorHeight - i][cursorWidth + i] = open;
						break;
					}
					//checks for whites
					if (mapArray[cursorHeight - i][cursorWidth + i] == wPawn
						|| mapArray[cursorHeight - i][cursorWidth + i] == wRook
						|| mapArray[cursorHeight - i][cursorWidth + i] == wKnight
						//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
						|| mapArray[cursorHeight - i][cursorWidth + i] == wQueen
						|| mapArray[cursorHeight - i][cursorWidth + i] == wKing
						)
					{
						break;
					}
				}
			}

			//checks for bot left


			for (int i = 1; i < mapHeight; i++)
			{
				if (cursorHeight + i<mapHeight && cursorWidth - i >= 0)
				{


					if (mapArray[cursorHeight + i][cursorWidth - i] == blank)
					{
						mapArray[cursorHeight + i][cursorWidth - i] = open;
					}
					//checks for black 
					if (mapArray[cursorHeight + i][cursorWidth - i] == bPawn
						|| mapArray[cursorHeight + i][cursorWidth - i] == bRook
						|| mapArray[cursorHeight + i][cursorWidth - i] == bKnight
						|| mapArray[cursorHeight + i][cursorWidth - i] == bBishop
						|| mapArray[cursorHeight + i][cursorWidth - i] == bQueen
						|| mapArray[cursorHeight + i][cursorWidth - i] == bKing
						)
					{
						//checks for king
						if (mapArray[cursorHeight + i][cursorWidth - i] == bKing)
						{
							break;
						}
						mapArray[cursorHeight + i][cursorWidth - i] = open;
						break;
					}
					//checks for whites
					if (mapArray[cursorHeight + i][cursorWidth - i] == wPawn
						|| mapArray[cursorHeight + i][cursorWidth - i] == wRook
						|| mapArray[cursorHeight + i][cursorWidth - i] == wKnight
						//|| mapArray[cursorHeight-i][cursorWidth-i] == wBishop
						|| mapArray[cursorHeight + i][cursorWidth - i] == wQueen
						|| mapArray[cursorHeight + i][cursorWidth - i] == wKing
						)
					{
						break;
					}
				}
			}

			// sides #note sides can cap king plz fix also rook can cap king
			for (int i = cursorHeight - 1; i >= 0; i--)
			{
				if (mapArray[i][cursorWidth] == blank)
				{
					mapArray[i][cursorWidth] = open;
				}
				//checks for black 
				if (mapArray[i][cursorWidth] == bPawn
					|| mapArray[i][cursorWidth] == bRook
					|| mapArray[i][cursorWidth] == bKnight
					|| mapArray[i][cursorWidth] == bBishop
					|| mapArray[i][cursorWidth] == bQueen
					|| mapArray[i][cursorWidth] == bKing
					)
				{
					//checks for king
					if (mapArray[i][cursorWidth] == bKing)
					{
						break;
					}
					mapArray[i][cursorWidth] = open;
					break;
				}
				//checks for whites
				if (mapArray[i][cursorWidth] == wPawn
					|| mapArray[i][cursorWidth] == wRook
					|| mapArray[i][cursorWidth] == wKnight
					|| mapArray[i][cursorWidth] == wBishop
					|| mapArray[i][cursorWidth] == wQueen
					|| mapArray[i][cursorWidth] == wKing
					)
				{
					break;
				}



			}

			//check down
			for (int i = cursorHeight + 1; i <= mapHeight - 1; i++)
			{
				if (mapArray[i][cursorWidth] == blank)
				{
					mapArray[i][cursorWidth] = open;
				}
				//checks for black 
				if (mapArray[i][cursorWidth] == bPawn
					|| mapArray[i][cursorWidth] == bRook
					|| mapArray[i][cursorWidth] == bKnight
					|| mapArray[i][cursorWidth] == bBishop
					|| mapArray[i][cursorWidth] == bQueen
					|| mapArray[i][cursorWidth] == bKing
					)
				{
					//checks for king
					if (mapArray[i][cursorWidth] == bKing)
					{
						break;
					}
					mapArray[i][cursorWidth] = open;
					break;
				}
				//checks for whites
				if (mapArray[i][cursorWidth] == wPawn
					|| mapArray[i][cursorWidth] == wRook
					|| mapArray[i][cursorWidth] == wKnight
					|| mapArray[i][cursorWidth] == wBishop
					|| mapArray[i][cursorWidth] == wQueen
					|| mapArray[i][cursorWidth] == wKing
					)
				{
					break;
				}
			}
			//check left
			for (int i = cursorWidth - 1; i >= 0; i--)
			{
				if (mapArray[cursorHeight][i] == blank)
				{
					mapArray[cursorHeight][i] = open;
				}
				//checks for black 
				if (mapArray[cursorHeight][i] == bPawn
					|| mapArray[cursorHeight][i] == bRook
					|| mapArray[cursorHeight][i] == bKnight
					|| mapArray[cursorHeight][i] == bBishop
					|| mapArray[cursorHeight][i] == bQueen
					|| mapArray[cursorHeight][i] == bKing
					)
				{
					//checks for king
					if (mapArray[cursorHeight][i] == bKing)
					{
						break;
					}
					mapArray[cursorHeight][i] = open;
					break;
				}
				//checks for whites
				if (mapArray[cursorHeight][i] == wPawn
					|| mapArray[cursorHeight][i] == wRook
					|| mapArray[cursorHeight][i] == wKnight
					|| mapArray[cursorHeight][i] == wBishop
					|| mapArray[cursorHeight][i] == wQueen
					|| mapArray[cursorHeight][i] == wKing
					)
				{
					break;
				}
			}
			//check right
			for (int i = cursorWidth + 1; i <= mapWidth - 1; i++)
			{
				if (mapArray[cursorHeight][i] == blank)
				{
					mapArray[cursorHeight][i] = open;
				}
				//checks for black 
				if (mapArray[cursorHeight][i] == bPawn
					|| mapArray[cursorHeight][i] == bRook
					|| mapArray[cursorHeight][i] == bKnight
					|| mapArray[cursorHeight][i] == bBishop
					|| mapArray[cursorHeight][i] == bQueen
					|| mapArray[cursorHeight][i] == bKing
					)
				{
					//checks for king
					if (mapArray[cursorHeight][i] == bKing)
					{
						break;
					}
					mapArray[cursorHeight][i] = open;
					break;
				}
				//checks for whites
				if (mapArray[cursorHeight][i] == wPawn
					|| mapArray[cursorHeight][i] == wRook
					|| mapArray[cursorHeight][i] == wKnight
					|| mapArray[cursorHeight][i] == wBishop
					|| mapArray[cursorHeight][i] == wQueen
					|| mapArray[cursorHeight][i] == wKing
					)
				{
					break;
				}
			}
			selectedPiece = wQueen;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
			break;

			case wKing:
				reverseCopyMap();

	}
}

void cursorMove()
{
	//how the arrow keys work
	system("pause");
	for (int i = 0; i < numKeys; i++)
	{
		int ch = GetAsyncKeyState(arrowKeys[i]);

		if (ch)
		{
			//note to self clean this up
			
			mapArray[cursorHeight][cursorWidth] = tempIcon;
			if (i == 0 && cursorHeight>0)
			{
				cursorHeight--;
			}
			else if (i == 1 && cursorHeight<mapHeight-1)
			{
				cursorHeight++;
			}
			else if (i == 2 && cursorWidth>0)
			{
				cursorWidth--;
			}
			else if (i == 3 && cursorWidth<mapWidth-1)
			{
				cursorWidth++;
			}
			else if (i == 4)
			{
				go = false;
			}
			else if (i == 5)
			{
				
				select();
			}
			drawCursor();
		}
	}

}



int main()
{
	


	
	
	/*	
	HANDLE hstdin;
	DWORD  mode;
	//access
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	//for the rest
	GetConsoleMode(hstdin, &mode);
	SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);  // see note below
	cout << "Press any key..." << flush;
	*/
	
	drawCursor();
	drawMap();
	
	
	while (go==true)
	{
	cursorMove();
	drawMap();
	}
	
	

	
	//how the arrow keys work
	/*
	system("pause");
	int ch = GetAsyncKeyState(arrowKeys[0]);
	if (ch) cout << "\nYou pressed UP\n";
	else          cout << "\n\nYou did not press ENTER\n";
	*/


	//SetConsoleMode(hstdin, mode); 
	//system("pause");
	

	return 0;
}

bool checkB(int Height, int Width)
{
	if (mapArray[Height][Width] == bPawn
		|| mapArray[Height][Width] == bRook
		|| mapArray[Height][Width] == bKnight
		|| mapArray[Height][Width] == bBishop
		|| mapArray[Height][Width] == bQueen
		|| mapArray[Height][Width] == bKing
		)
	{
		return true;
	}
	
	return false;
}

bool checkW(int Height, int Width)
{
	if (mapArray[Height][Width] == wPawn
		|| mapArray[Height][Width] == wRook
		|| mapArray[Height][Width] == wKnight
		|| mapArray[Height][Width] == wBishop
		|| mapArray[Height][Width] == wQueen
		|| mapArray[Height][Width] == wKing
		)
	{
		return true;
	}

	return false;
}
