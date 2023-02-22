/**********
Matthew Lum
Chess
01/25/2015

**************
stuff I need to add

fix bishop #done
add queen #done
add king #done
add black side #done
add turns #done 3.8.2016
add checkmate mech 
add pawn promotion #done
add pawn En Passant #done
add castling #done 3/1/2015
add stalemates 
add AI?
add online multiplayer?
figure out how to export/host this program on web to show it off
*****************
fix bugs

Rook placement bug[fixed]
(3.6.2016)if you try to move any piece a r will apear instead and an R will disapear...
this only seems to happen when any rooks are in play
linked to the rookB and rookW methods

solution:
bad code had to get deleted. I must have left it from an earlier method that worked slightly differently.
strange thing was that rookB/W was called to mark mapX (used to determine whether king is enter check) 
left it being called this way not sure if it'll be an issue, but atleast bug is fixed.
//selectedPiece = wRook;
//selectedWidth = cursorWidth;
//selectedHeight = cursorHeight;
turns out I needed that code in the select() case rookB/W opps well it's all fixxed up now

[not fixed?]
if you switch from one king to the other it keeps the same Xmap and is trouble some
3.8.2016 looked into this, but Doesn't seem to happen to me... might have been linked to other code I changed.
solution:
???

[fixed]
bug where turnover method doesn't work in switching turn from true to false.
At first I thougth because I messsed up == with =, which I did, but problem pursists.
I suspect that the method is being run twice thus negating it's self??? 
but have no evidence to support this
solution:
nvm I'm an idiot I forgot to add else to the 2nd if statement to check if true then false, 
but then it would say if false then true.


[bug]
kings can enter eachother's attack zones

//remove comments
****************
Notes
had to fix stuff after opening this after a couple of mounths left it in an bugged state, 
which took me 2 hours+ of looking to move 6 lines of code. Don't do that again.

3.8.2016
I made a mistake.... maybe.... hmmm I should save different states of my code (not sure if it auto does this)
So I added turns hard coded it into every piece select so now testing for checkmate mech is more difficult
but there are ways around this such as... useing old code(saved a copy when I started this month), 
delete the turn system, just work with it, or make it so only one color is always selected for it's turn...
I ended up adding the code below to blank spots too be able to switch while debugging and I deleted the inside of turnOver method.
if (turn == true)
{
turn = false;
}
else if (turn == false)
{
turn = true;
}


Chechmate Mech
I plan to enable all moves to be shown as normal, 
and just implement a check that prevents a turn from being completed, 
unless the king of who's ever turn it is, is safe.
found an old method I made a while back called bKingCheck
It checks if the king is in check so I can just use that in an if statement
everytime a piece trys to move... After those changes it'll be diffucult to bug test so I'll save a copy of my code.

tehc chechmate mech will rely and thus only work with the turn base system.
hmm another issue is that I want to be able to move a piece into position to body guard the king
in order to do this I would need to pretend to move the piece then check if the king is still in check if he's not then allow the move and continue.
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
#define cursor 13
#define open 14
#define check 15
#define double 16
#define enPass 17
#define castling 18
//number of keys detected
#define numKeys 6
//number of icons
#define numIcons 19

//gobal vaules
bool turn;
int cursorHeight = 4;
int cursorWidth = 4;
int selectedPiece;
int selectedHeight;
int selectedWidth;
int tempIcon = 0;
int g;
int temp = 0;
bool go = true;
//for king
int tempHeight = 0;
int tempWidth = 0;
void drawBKingCheck();
void drawWKingCheck();
//for En Passant
int enPassantW = 0;
int enPassantH = 0;
//for pawn promotion
int promoHeight = 0;
int promoWidth = 0;
bool promo = true;
//for castling
bool wRookr = true;
bool wRookl = true;
bool bRookr = true;
bool bRookl = true;
bool wKingCastl = true;
bool bKingCastl = true;
bool wCheck = false;
bool bCheck = false;
int cCount = 0;
void checkMoves();
bool wKingCheck();
bool bKingCheck();
void checkMate();
//function prototypes
bool checkW(int Height, int Width);
bool checkW(int pieceTemp);
bool checkB(int Height, int Width);
bool checkB(int pieceTemp);

//array of piece icons
char pieceIcons[numIcons] = { '.', 'p', 'r', 'n', 'b', 'q', 'k', 'P', 'R', 'N', 'B', 'Q', 'K', '@', '#', 'C','D','E','^' };

//array of arrow key's virtual key's
int arrowKeys[numKeys] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE, VK_RETURN };

//map creation
//int mapArray[mapHeight][mapWidth];
int mapArray[mapHeight][mapWidth] = {
	{ 2, 3, 4, 5, 6, 4, 3, 2, },
	{ 1, 1, 1, 1, 1, 1, 1, 1, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 5, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
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
//'x' copy for checking where the king can go
int mapX[mapHeight][mapWidth] = {
	{ 1, 1, 1, 1, 0, 0, 0, 0, },
	{ 1, 1, 1, 1, 1, 1, 1, 1, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 8, 9, 10, 11, 12, 10, 9, 8, }
};
//'CheckMate' copy for checking wheather a move is legal
int mapCheck[mapHeight][mapWidth] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 1, 1, 1, 1, 1, 1, 1, 1, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 0, 0, 0, 0, 0, 0, 0, 0, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 8, 9, 10, 11, 12, 10, 9, 8, }
};
//promotion screen White
int promoW[1][4] = {
	{ 2, 3, 4, 5 }
};
//promotion screen Blackj
int promoB[1][4] = {
	{ 8, 9, 10, 11 }
};

//chess piece function prototypes
void pawnW(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void pawnB(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void rookW(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void rookB(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void knightW(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void knightB(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void bishopW(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void bishopB(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void queenW(int arry[][mapWidth], int cursorHeight, int cursorWidth);
void queenB(int arry[][mapWidth], int cursorHeight, int cursorWidth);

void wking(int array[][mapWidth], int cursorHeight, int cursorWidth);
//methods must be dysplayed here if they are written under the main method (learned about this in school still confused on why though, figure it's just... becasue how compiler is written)
void turnOver();

//displays the pawn promotion screen
void promoDisplay(int arry[][4])
{
	
	promoHeight = 0;
	promoWidth = 0;

	//drawpromo(arry);
	tempIcon = arry[promoHeight][promoWidth];
	//makes the mapArray[promoHeight][promoWidth] = '@';
	arry[promoHeight][promoWidth] = cursor;
	for (int clear = 0; clear < 24; clear++)
	{
		cout << endl;
	}
	cout << "Pawn Promotion \nPromote pawn to which unit?\n";
	while (promo == true)
	{
		for (int i = 0; i < 4; i++)
		{
			//checks for and prints piece
			for (int index = 0; index < numIcons; index++)
			{
				if (arry[0][i] == index)
				{
					cout << pieceIcons[index];
					index = numIcons;
				}
					
			}
		}
		//prints empty lines so only one board is shown at a time
		for (int clear = 0; clear < 24; clear++)
		{
			cout << endl;
		}

		

		

		//movepromo();
		//how the arrow keys work
		//pause so a new board isn't constantly printed
		system("pause");
		for (int i = 0; i < numKeys; i++)
		{
			//gets currently pressed arrow key
			int ch = GetAsyncKeyState(arrowKeys[i]);

			if (ch)
			{
				//tempIcon = mapArray[promoHeight][promoWidth];
				//when drawpromo() which is called which is where the '@' is drawn
				arry[promoHeight][promoWidth] = tempIcon;
				//up
				if (i == 0 && promoHeight>0)
				{
					promoHeight--;
				}
				/*
				
				//down
				else if (i == 1 && promoHeight< - 1)
				{
					promoHeight++;
				}
				*/
				//left
				else if (i == 2 && promoWidth>0)
				{
					promoWidth--;
				}
				//right
				else if (i == 3 && promoWidth<4 - 1)
				{
					promoWidth++;
				}
				//escape was pressed so the while loop ends and the console exits
				else if (i == 4)
				{
					promo = false;
					go = false;
				}
				//enter was pressed so an icon was selected 
				//check select() for more specifc details
				else if (i == 5)
				{
					promo = false;
					mapArray[cursorHeight][cursorWidth] = arry[promoHeight][promoWidth];

					//select();
				}
				//moves the promo on the board
				
				//drawpromo(arry);
				tempIcon = arry[promoHeight][promoWidth];
				//makes the mapArray[promoHeight][promoWidth] = '@';
				arry[promoHeight][promoWidth] = cursor;
			}
		}

		

	}
	//resets the promo while loop for next promotion
	arry[promoHeight][promoWidth] = tempIcon;
	promo = true;
	promoHeight = 0;
	promoWidth = 0;
}


//needed for king to ingore pawn's non attack movements
void wPawnAttack(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//checks diagonal right for black 
	if ((cursorHeight + 1) < mapHeight && (cursorWidth + 1) < mapWidth)
	{

		if (checkW(cursorHeight + 1, cursorWidth + 1) || arry[cursorHeight + 1][cursorWidth + 1] == blank)
		{
			//king check
			if (arry[cursorHeight + 1][cursorWidth + 1] != bKing)
			{
				arry[cursorHeight + 1][cursorWidth + 1] = open;
			}
		}
	}
	//checks diagonal left for ememies
	if ((cursorHeight + 1) < mapHeight && (cursorWidth - 1) >= 0)
	{

		if (checkW(cursorHeight + 1, cursorWidth - 1) || arry[cursorHeight + 1][cursorWidth - 1] == blank)
		{
			if (arry[cursorHeight + 1][cursorWidth - 1] != bKing)
			{
				arry[cursorHeight + 1][cursorWidth - 1] = open;
			}
		}
	}
}
void bPawnAttack(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{

	//checks diagonal right for black
	if ((cursorHeight - 1) >= 0 && (cursorWidth + 1) < mapWidth)
	{
		if (checkB(cursorHeight - 1, cursorWidth + 1) || arry[cursorHeight - 1][cursorWidth + 1] == blank)
		{
			//king check
			if (arry[cursorHeight - 1][cursorWidth + 1] != wKing)
			{
				arry[cursorHeight - 1][cursorWidth + 1] = open;
			}
		}
	}
	//checks diagonal left for ememies
	if ((cursorHeight - 1) >= 0 && (cursorWidth - 1) >= 0)
	{
		if (checkB(cursorHeight - 1, cursorWidth - 1) || arry[cursorHeight - 1][cursorWidth - 1] == blank)
		{
			if (arry[cursorHeight - 1][cursorWidth - 1] != wKing)
			{
				arry[cursorHeight - 1][cursorWidth - 1] = open;
			}
		}
	}
}
void drawMap()
{
	//prints empty lines so only one board is shown at a time
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
//was used for testing purposes
//is currently never called
void drawMapX()
{
	
	for (int i = 0; i < mapHeight; i++)
	{
		//moves prints to next line
		cout << endl;
		for (int j = 0; j < mapWidth; j++)
		{
			//checks for and prints piece
			for (int index = 0; index < numIcons; index++)
			{
				if (mapX[i][j] == index)
					cout << pieceIcons[index];
			}
		}
	}
	cout << endl;
}
//was used for testing purposes
//is currently never called
void drawMapCopy()
{
	
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
//cursor displayed as @
void drawCursor(int arry[][mapWidth])
{
	tempIcon = arry[cursorHeight][cursorWidth];
	//makes the mapArray[cursorHeight][cursorWidth] = '@';
	arry[cursorHeight][cursorWidth] = cursor;


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
			mapX[i][j] = mapArray[i][j];
		}
	}

}
//called everytime a piece is selected
//puts copyMap onto mapArray
//puts mapX...broken
void reverseCopyMap()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			mapArray[i][j] = mapCopy[i][j];
			//mapArray[i][j] = mapX[i][j];
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

	//copys mapArray to copyMap only when no #'s are on map
	//and copys mapArray to mapX
	checkBoard();


	
	switch (tempIcon)
	{
		//works as a cancle when blank is selected
	case blank:
		if (turn == true)
		{
			turn = false;
		}
		else if (turn == false)
		{
			turn = true;
		}
		reverseCopyMap();
		break;

	case double:
		//note to self I don't think the if statement of == double is necessary
		//if (selectedPiece == wPawn&&wKingCheck()||selectedPiece ==bPawn&&bKingCheck()) old check mech
		
		
		turnOver();
		if (mapArray[cursorHeight][cursorWidth] == double)
		{

			enPassantH = cursorHeight;
			enPassantW = cursorWidth;
			//makes the mapCopy's spot the chess piece
			mapCopy[cursorHeight][cursorWidth] = selectedPiece;
			//makes the origanl spot of the chess piece blank
			mapCopy[selectedHeight][selectedWidth] = blank;



			//copys the copyMap, that has no '#'s and has moved the chess piece, onto mapArray
			reverseCopyMap();

		}
		
		break;
		
	case enPass:
		turnOver();
		mapCopy[cursorHeight][cursorWidth] = selectedPiece;
		//makes the origanl spot of the chess piece blank
		mapCopy[selectedHeight][selectedWidth] = blank;

		//depending on whos turn it is the piece north or south of this posistion is take
		if (selectedPiece == bPawn)
		{
			mapCopy[cursorHeight + 1][cursorWidth] = blank;
		}

		if (selectedPiece == wPawn)
		{
			mapCopy[cursorHeight - 1][cursorWidth] = blank;
		}

		enPassantH = 0;
		enPassantW = 0;
		//copys the copyMap, that has no '#'s and has moved the chess piece, onto mapArray
		reverseCopyMap();

		//This places the chess piece. 
		//if a '#' is selected it is replaced with the last selected Icon
	case open:

		turnOver();

		//if (mapArray[cursorHeight][cursorWidth] == open)
		
			//for castling
			checkMoves();

			//for check mech
			if (bKingCheck())
			{
				bCheck = true;
			}

			if (wKingCheck())
			{
				wCheck = true;
			}

			//makes the mapCopy's spot the chess piece
			mapCopy[cursorHeight][cursorWidth] = selectedPiece;
			//makes the origanl spot of the chess piece blank
			mapCopy[selectedHeight][selectedWidth] = blank;

			

			//copys the copyMap, that has no '#'s and has moved the chess piece, onto mapArray
			reverseCopyMap();

		
		break;
		//needs to address four different stituations based on selectedHeight and selectedWidth
		//work on later 3/1/2015
		//^
		//might want to change the mapArray to mapCopy... idk
	case castling:
		
		
		turnOver();
		//black left
		if (mapArray[7][2] == castling&&cursorWidth == 2)
		{
			//removes king
			mapCopy[7][4] = blank;
			//adds king
			mapCopy[7][2] = bKing;
			//removes rook
			mapCopy[7][0] = blank;
			//adds rook
			mapCopy[7][3] = bRook;
			//king can no longer castle
			bKingCastl = false;
		}
		//black right
		if (mapArray[7][6] == castling&&cursorWidth == 6)
		{
			//removes king
			mapCopy[7][4] = blank;
			//adds king
			mapCopy[7][6] = bKing;
			//removes rook
			mapCopy[7][7] = blank;
			//adds rook
			mapCopy[7][5] = bRook;
			//no longer castl
			bKingCastl = false;
		}
		
		
		//white left
		if (mapArray[0][2] == castling&&cursorWidth==2)
		{
			//removes king
			mapCopy[0][4] = blank;
			//adds king
			mapCopy[0][2] = wKing;
			//removes rook
			mapCopy[0][0] = blank;
			//adds rook
			mapCopy[0][3] = wRook;
			//no longer castl
			wKingCastl = false;
		}
		//white right
		if (mapArray[0][6] == castling&&cursorWidth == 6)
		{
			//removes king
			mapCopy[0][4] = blank;
			//adds king
			mapCopy[0][6] = wKing;
			//removes rook
			mapCopy[0][7] = blank;
			//adds rook
			mapCopy[0][5] = wRook;
			//no longer castl
			wKingCastl = false;
		}
		
		reverseCopyMap();
		
		break;

	case bPawn:
		if (turn == true)
		{
		
		reverseCopyMap();
		pawnB(mapArray, cursorHeight, cursorWidth);
		selectedPiece = bPawn;
		selectedWidth = cursorWidth;
		selectedHeight = cursorHeight;
		}
		break;
		

		//if (tempIcon == wPawn)
		//nts add promotion ability (and a movement limit)
	case wPawn:
		if (turn == false)
		{
			//clears map of '#'s
			reverseCopyMap();

			pawnW(mapArray, cursorHeight, cursorWidth);

			//makes the next # selected a wPawn
			selectedPiece = wPawn;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case bRook:
		if (turn == true)
		{
			//clears '#'s
			reverseCopyMap();
			//adds new '#'s
			rookB(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a bRook
			selectedPiece = bRook;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case wRook:
		if (turn == false)
		{
			//clears '#'s
			reverseCopyMap();
			//adds new '#'s
			rookW(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a wRook
			selectedPiece = wRook;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case bKnight:
		if (turn == true)
		{
			reverseCopyMap();
			knightB(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a bKnight
			selectedPiece = bKnight;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;
		

	case wKnight:
		if (turn == false)
		{
			reverseCopyMap();
			knightW(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a wKnight
			selectedPiece = wKnight;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;
		
	case bBishop:
		if (turn == true)
		{
			reverseCopyMap();
			bishopB(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a bBishop
			selectedPiece = bBishop;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case wBishop:
		if (turn == false)
		{
			reverseCopyMap();
			bishopW(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a wBishop
			selectedPiece = wBishop;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case bQueen:
		if (turn == true)
		{
			reverseCopyMap();
			queenB(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a bQueen
			selectedPiece = bQueen;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case wQueen:
		if (turn == false)
		{
			reverseCopyMap();
			queenW(mapArray, cursorHeight, cursorWidth);
			//makes the next # selected a wQueen
			selectedPiece = wQueen;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;
		//remove comments

		
		
	case bKing:
		if (turn == true)
		{
			reverseCopyMap();

			//draws the map for white attacks
			drawBKingCheck();
			//for testing purposes
			//drawMapCopy();
			//system("PAUSE");


			//black king castling
			//cCount used to check if path between rook and king is unblocked
			if (bKingCastl == true && bCheck == false)
			{
				//left
				//cCount needs 3 because queen.
				cCount = 0;
				for (int i = 0; i <= 2; i++)
				{
					if (mapX[7][1 + i] == blank)
					{
						cCount = cCount + 1;
					}
				}
				// checks if space between king and rook is safe
				if (cCount == 3 && bRookl == true)
				{
					mapArray[7][2] = castling;

				}

				//right
				cCount = 0;
				for (int i = 0; i <= 1; i++)
				{
					if (mapX[7][5 + i] == blank)
					{
						cCount++;
					}
				}
				// checks if space between king and rook is safe
				if (cCount == 2 && bRookr == true)
				{
					mapArray[7][6] = castling;

				}

			}



			for (int index = -1; index <= 1; index++)
			{
				//reason for i++?
				for (int j = -1; j <= 1; j++)
				{


					//checks if [cursorHeight+i][cursorWidth+j] is under attack aka there's a '#' there on mapX
					if (mapX[cursorHeight + index][cursorWidth + j] != open)
					{

						//use drawmap()'s loop and the mapArray to calculate attack zones of blacks write them in as 'x' on a seprate Arraycopy then place '#'s on mapArray where king can move.

						//put jndex switch in index switch

						//checks if in bondaries
						//i checks for height limits
						//used for the 8 box around king for movement
						switch (index)
						{
						case -1:
							//1 or index?
							if (cursorHeight + index >= 0)
							{
								switch (j)
								{
								case -1:
									if (cursorWidth + j >= 0)
									{
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for white
										//replace with # then break if white
										if (checkW(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
									}
									break;
									//add mark


								case 0:
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for white
									//replace with # then break if white
									if (checkW(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
									break;

								case 1:
									if (cursorWidth + j <= mapWidth - 1)
									{
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for white
										//replace with # then break if white
										if (checkW(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
										break;
										//add mark
									}
									break;
								}
								//end of j switch
							}
							break;

						case 0:
							switch (j)
							{
							case -1:
								if (cursorWidth + j >= 0)
								{
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for white
									//replace with # then break if white
									if (checkW(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
								}
								break;
								//add mark


							case 0:
								if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
								{
									mapArray[cursorHeight + index][cursorWidth + j] = open;
								}

								//check for white
								//replace with # then break if white
								if (checkW(cursorHeight + index, cursorWidth + j))
								{
									mapArray[cursorHeight + index][cursorWidth + j] = open;
									//don't need break?
									break;
								}
								break;

							case 1:
								if (cursorWidth + j <= mapWidth - 1)
								{
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for white
									//replace with # then break if white
									if (checkW(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
									break;
									//add mark
								}
								break;
							}
							//end of j switch
							break;

						case 1:
							if (cursorHeight + index <= mapHeight - 1)
							{
								switch (j)
								{
								case -1:
									if (cursorWidth + j >= 0)
									{
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for white
										//replace with # then break if white
										if (checkW(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
									}
									break;
									//add mark


								case 0:
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for white
									//replace with # then break if white
									if (checkW(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
									break;

								case 1:
									if (cursorWidth + j <= mapWidth - 1)
									{
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for white
										//replace with # then break if white
										if (checkW(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
										break;
										//add mark
									}
									break;
								}
								//end of j switch
							}
							break;
						}

						//j checks for width limits

					}
				}
			}
			//makes the next # selected a bKing
			selectedPiece = bKing;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
		break;

	case wKing:
		if (turn == false)
		{
			//make a 'x'Array copy of mapArray
			reverseCopyMap();
			//original spot of wKing
			//remove these two and their initiator 
			tempWidth = cursorWidth;
			tempHeight = cursorHeight;

			//draws the board for attack posistions of black units
			drawWKingCheck();


			//for testing purposes
			//drawMapX();
			//system("PAUSE");

			//white king castling
			//replace wKingCheck with wCheck...
			if (wKingCastl == true && wCheck == false)
			{
				//left
				// checks if space between king and rook is safe
				cCount = 0;
				for (int i = 0; i <= 2; i++)
				{
					if (mapX[0][1 + i] == blank)
					{
						cCount++;
					}
				}
				if (cCount == 3 && wRookl == true)
				{
					mapArray[0][2] = castling;

				}

				//right
				// checks if space between king and rook is safe
				cCount = 0;
				for (int i = 0; i <= 1; i++)
				{
					if (mapX[0][5 + i] == blank)
					{
						cCount++;
					}
				}

				//checks king is safe
				if (cCount == 2 && wRookr == true)
				{
					mapArray[0][6] = castling;

				}

			}

			for (int index = -1; index <= 1; index++)
			{
				//reason for i++?
				for (int j = -1; j <= 1; j++)
				{


					//checks if [cursorHeight+i][cursorWidth+j] is under attack aka there's a '#' there on mapX
					if (mapX[cursorHeight + index][cursorWidth + j] != open)
					{


						//use drawmap()'s loop and the mapArray to calculate attack zones of blacks write them in as 'x' on a seprate Arraycopy then place '#'s on mapArray where king can move.

						//checks if in bondaries
						//i checks for height limits
						switch (index)
						{
						case -1:
							if (cursorHeight + index >= 0)
							{
								//j checks for width limits
								switch (j)
								{
								case -1:
									if (cursorWidth + j >= 0)
									{
										//check if blank
										//replace with # if blank
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for blacks
										//replace with # then break if black
										if (checkB(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
									}
									break;
									//add mark


								case 0:
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for blacks
									//replace with # then break if black
									if (checkB(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
									break;

								case 1:
									if (cursorWidth + j <= mapWidth - 1)
									{
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for blacks
										//replace with # then break if black
										if (checkB(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
										break;
										//add mark
									}
									break;
								}
								//end of j switch


							}
							break;

						case 0:
							//j checks for width limits
							switch (j)
							{
							case -1:
								if (cursorWidth + j >= 0)
								{
									//check if blank
									//replace with # if blank
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for blacks
									//replace with # then break if black
									if (checkB(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
								}
								break;
								//add mark


							case 0:
								if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
								{
									mapArray[cursorHeight + index][cursorWidth + j] = open;
								}

								//check for blacks
								//replace with # then break if black
								if (checkB(cursorHeight + index, cursorWidth + j))
								{
									mapArray[cursorHeight + index][cursorWidth + j] = open;
									//don't need break??
									break;
								}
								break;

							case 1:
								if (cursorWidth + j <= mapWidth - 1)
								{
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for blacks
									//replace with # then break if black
									if (checkB(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
									break;
									//add mark
								}
								break;
							}
							//end of j switch

						case 1:
							if (cursorHeight + index <= mapHeight - 1)
							{
								//j checks for width limits
								switch (j)
								{
								case -1:
									if (cursorWidth + j >= 0)
									{
										//check if blank
										//replace with # if blank
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for blacks
										//replace with # then break if black
										if (checkB(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
									}
									break;
									//add mark


								case 0:
									if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
									}

									//check for blacks
									//replace with # then break if black
									if (checkB(cursorHeight + index, cursorWidth + j))
									{
										mapArray[cursorHeight + index][cursorWidth + j] = open;
										//don't need break?
										break;
									}
									break;

								case 1:
									if (cursorWidth + j <= mapWidth - 1)
									{
										if (mapArray[cursorHeight + index][cursorWidth + j] == blank)
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
										}

										//check for blacks
										//replace with # then break if black
										if (checkB(cursorHeight + index, cursorWidth + j))
										{
											mapArray[cursorHeight + index][cursorWidth + j] = open;
											//don't need break?
											break;
										}
										break;
										//add mark
									}
									break;
								}
								//end of j switch
							}
							break;
						}


					}
				}
			}
			selectedPiece = wKing;
			selectedWidth = cursorWidth;
			selectedHeight = cursorHeight;
		}
	}
}

//moves where the '@' is

void cursorMove(int arry[][mapWidth])
{
	//how the arrow keys work
	//pause so a new board isn't constantly printed
	//draw maps method was for debuging
	//drawMapX();
	//drawMapCopy();
	system("pause");
	for (int i = 0; i < numKeys; i++)
	{
		//gets currently pressed arrow key
		int ch = GetAsyncKeyState(arrowKeys[i]);

		if (ch)
		{
			//tempIcon = mapArray[cursorHeight][cursorWidth];
			//when drawCursor() which is called which is where the '@' is drawn
			arry[cursorHeight][cursorWidth] = tempIcon;
			//up
			if (i == 0 && cursorHeight>0)
			{
				cursorHeight--;
			}
			//down
			else if (i == 1 && cursorHeight<mapHeight - 1)
			{
				cursorHeight++;
			}
			//left
			else if (i == 2 && cursorWidth>0)
			{
				cursorWidth--;
			}
			//right
			else if (i == 3 && cursorWidth<mapWidth - 1)
			{
				cursorWidth++;
			}
			//escape was pressed so the while loop ends and the console exits
			else if (i == 4)
			{
				go = false;
			}
			//enter was pressed so an icon was selected 
			//check select() for more specifc details
			else if (i == 5)
			{

				select();
			}
			//moves the cursor on the board
			drawCursor(mapArray);
		}
	}

}



int main()
{
	turn = false;
	
	if (turn==true)
	cout << "true";
	if (turn == false)
		cout << "false";
	cout << "3.6.2016";


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

	drawCursor(mapArray);
	drawMap();


	while (go == true)
	{
		cursorMove(mapArray);
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


//chess pieces functions
void pawnW(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//promotion
	if (cursorHeight == 7)
	{
		//display promotion screen
		promoDisplay(promoW);
		
	}
	//allows the wPawn it's first double jump
	//checks both 1 and 2 in front of pawn
	if (cursorHeight == 1 && arry[cursorHeight + 2][cursorWidth] == blank && arry[cursorHeight + 1][cursorWidth] == blank)
	{
		//arry[cursorHeight + 2][cursorWidth] = open;
		//mark 
		arry[cursorHeight + 2][cursorWidth] = double;
	}
	//checks 1 in front
	if (arry[cursorHeight + 1][cursorWidth] == blank)
	{
		arry[cursorHeight + 1][cursorWidth] = open;
	}
	
	//checks for diagonal right for EnPassant
	if (cursorHeight == enPassantH && cursorWidth + 1 == enPassantW)
	{
		arry[cursorHeight + 1][cursorWidth + 1] = enPass;
	}
	//checks for diagonal left for EnPassant
	if (cursorHeight == enPassantH && cursorWidth - 1 == enPassantW)
	{
		arry[cursorHeight + 1][cursorWidth - 1] = enPass;
	}

	//this below is wPawnAttack() but without the checkW and open as attack spots
	//checks diagonal right for black 
	if (checkB(cursorHeight + 1, cursorWidth + 1)&&cursorWidth+1<=mapWidth-1 )
	{
		//king check
		if (arry[cursorHeight + 1][cursorWidth + 1] != bKing)
		{
			arry[cursorHeight + 1][cursorWidth + 1] = open;
		}
	}
	//checks diagonal left for ememies
	if (checkB(cursorHeight + 1, cursorWidth - 1) && cursorWidth - 1>=0)
	{
		if (arry[cursorHeight + 1][cursorWidth - 1] != bKing)
		{
			arry[cursorHeight + 1][cursorWidth - 1] = open;
		}
	}
}

void pawnB(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//promotion
	if (cursorHeight == 0)
	{
		//display promotion screen
		promoDisplay(promoB);

	}
	//allows the wPawn it's first double jump
	//checks both 1 and 2 in front of pawn
	if (cursorHeight == 6 && arry[cursorHeight - 2][cursorWidth] == blank && arry[cursorHeight - 1][cursorWidth] == blank)
	{
		//arry[cursorHeight - 2][cursorWidth] = open;
		//mark
		arry[cursorHeight - 2][cursorWidth] = double;
	}
	//checks 1 in front
	if (arry[cursorHeight - 1][cursorWidth] == blank)
	{
		arry[cursorHeight - 1][cursorWidth] = open;
	}

	//checks diagonal right for En Passant
	if (cursorHeight == enPassantH && cursorWidth + 1 == enPassantW)
	{

		arry[cursorHeight - 1][cursorWidth + 1] = enPass;

	}
	//checks diagonal left for En Passant
	if (cursorHeight == enPassantH && cursorWidth - 1 == enPassantW)
	{

		arry[cursorHeight - 1][cursorWidth - 1] = enPass;

	}
	//this below is bPawnAttack() but without the checkB and open as attack spots
	//checks diagonal right for black 
	if (checkW(cursorHeight - 1, cursorWidth + 1) && cursorWidth + 1 <= mapWidth - 1)
	{
		//king check
		if (arry[cursorHeight - 1][cursorWidth + 1] != wKing)
		{
			arry[cursorHeight - 1][cursorWidth + 1] = open;
		}
	}
	//checks diagonal left for ememies
	if (checkW(cursorHeight - 1, cursorWidth - 1) && cursorWidth - 1 >= 0)
	{
		if (arry[cursorHeight - 1][cursorWidth - 1] != wKing)
		{
			arry[cursorHeight - 1][cursorWidth - 1] = open;
		}
	}
}

//white rook
void rookW(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	
	
		//checks up
		for (int i = cursorHeight - 1; i >= 0; i--)
		{
			if (arry[i][cursorWidth] == blank)
			{
				arry[i][cursorWidth] = open;
			}
			//checks for black 
			if (checkB(i, cursorWidth))
			{
				//checks for king
				if (arry[i][cursorWidth] == bKing)
				{
					arry[i][cursorWidth] = check;
					break;
				}
				arry[i][cursorWidth] = open;
				break;
			}
			//checks for whites
			if (checkW(i, cursorWidth))
			{
				break;
			}
		}

		//check down
		for (int i = cursorHeight + 1; i <= mapHeight - 1; i++)
		{
			if (arry[i][cursorWidth] == blank)
			{
				arry[i][cursorWidth] = open;
			}
			//checks for black 
			if (checkB(i, cursorWidth))
			{
				//checks for king
				if (arry[i][cursorWidth] == bKing)
				{
					break;
				}
				arry[i][cursorWidth] = open;
				break;
			}
			//checks for whites
			if (checkW(i, cursorWidth))
			{
				break;
			}
		}
		//check left
		for (int i = cursorWidth - 1; i >= 0; i--)
		{
			if (arry[cursorHeight][i] == blank)
			{
				arry[cursorHeight][i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight, i))
			{
				//checks for king
				if (arry[cursorHeight][i] == bKing)
				{
					break;
				}
				arry[cursorHeight][i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight, i))
			{
				break;
			}
		}
		//check right
		for (int i = cursorWidth + 1; i <= mapWidth - 1; i++)
		{
			if (arry[cursorHeight][i] == blank)
			{
				arry[cursorHeight][i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight, i))
			{
				//checks for king
				if (arry[cursorHeight][i] == bKing)
				{
					break;
				}
				arry[cursorHeight][i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight, i))
			{
				break;
			}
		}
		//makes the next # selected a wRook
		//glitch remove later if not needed
		//selectedPiece = wRook;
		//selectedWidth = cursorWidth;
		//selectedHeight = cursorHeight;
		
	}

	//for black rook
void rookB(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	
	
	//checks up
	for (int i = cursorHeight - 1; i >= 0; i--)
	{
		if (arry[i][cursorWidth] == blank)
		{
			arry[i][cursorWidth] = open;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			break;
		}
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == wKing)
			{
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
	}

	//check down
	for (int i = cursorHeight + 1; i <= mapHeight - 1; i++)
	{
		if (arry[i][cursorWidth] == blank)
		{
			arry[i][cursorWidth] = open;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			break;
		}
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == wKing)
			{
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
	}
	//check left
	for (int i = cursorWidth - 1; i >= 0; i--)
	{
		if (arry[cursorHeight][i] == blank)
		{
			arry[cursorHeight][i] = open;
		}
		//checks for black 
		if (checkB(cursorHeight, i))
		{
			break;
		}
		//checks for whites
		if (checkW(cursorHeight, i))
		{
			//checks for king
			if (arry[cursorHeight][i] == wKing)
			{
				break;
			}
			arry[cursorHeight][i] = open;
			break;
		}
	}
	//check right
	for (int i = cursorWidth + 1; i <= mapWidth - 1; i++)
	{
		if (arry[cursorHeight][i] == blank)
		{
			arry[cursorHeight][i] = open;
		}
		//checks for black 
		if (checkB(cursorHeight, i))
		{
			break;
		}
		//checks for whites
		if (checkW(cursorHeight, i))
		{
			//checks for king
			if (arry[cursorHeight][i] == wKing)
			{
				break;
			}
			arry[cursorHeight][i] = open;
			break;
		}
	}
	//makes the next # selected a bRook
	//remove this it gliches out the game and places bRook's instead of moving pieces
	//selectedPiece = bRook;
	//selectedWidth = cursorWidth;
	//selectedHeight = cursorHeight;
	
}
void knightW(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//down moves
	// left
	temp = -1;
	if (cursorHeight + 1 <= mapHeight - 1 && cursorWidth - 2 >= 0)
		temp = arry[cursorHeight + 1][cursorWidth - 2];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight + 1][cursorWidth - 2] = open;
		if (temp == bKing)
		{
			arry[cursorHeight + 1][cursorWidth - 2] = check;
		}
	}
	//right
	temp = -1;
	if (cursorHeight + 1 <= mapHeight - 1 && cursorWidth + 2 <= mapWidth - 1)
		temp = arry[cursorHeight + 1][cursorWidth + 2];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight + 1][cursorWidth + 2] = open;
		if (temp == bKing)
		{
			arry[cursorHeight + 1][cursorWidth + 2] = check;
		}
	}
	//bottom right
	temp = -1;
	if (cursorHeight + 2 <= mapHeight - 1 && cursorWidth + 1 <= mapWidth - 1)
		temp = arry[cursorHeight + 2][cursorWidth + 1];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight + 2][cursorWidth + 1] = open;
		if (temp == bKing)
		{
			arry[cursorHeight + 2][cursorWidth + 1] = check;
		}
	}
	//bottom left
	temp = -1;
	if (cursorHeight + 2 <= mapHeight - 1 && cursorWidth - 1 >= 0)
		temp = arry[cursorHeight + 2][cursorWidth - 1];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight + 2][cursorWidth - 1] = open;
		if (temp == bKing)
		{
			arry[cursorHeight + 2][cursorWidth - 1] = check;
		}
	}
	//up moves
	//right
	temp = -1;
	if (cursorHeight - 1 >= 0 && cursorWidth + 2 <= mapWidth - 1)
		temp = arry[cursorHeight - 1][cursorWidth + 2];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight - 1][cursorWidth + 2] = open;
		if (temp == bKing)
		{
			arry[cursorHeight - 1][cursorWidth + 2] = check;
		}
	}
	//upper right
	temp = -1;
	if (cursorHeight - 2 >= 0 && cursorWidth + 1 <= mapWidth - 1)
		temp = arry[cursorHeight - 2][cursorWidth + 1];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight - 2][cursorWidth + 1] = open;
		if (temp == bKing)
		{
			arry[cursorHeight - 2][cursorWidth + 1] = check;
		}
	}
	//upper left
	temp = -1;
	if (cursorHeight - 2 >= 0 && cursorWidth - 1 >= 0)
		temp = arry[cursorHeight - 2][cursorWidth - 1];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight - 2][cursorWidth - 1] = open;
		if (temp == bKing)
		{
			arry[cursorHeight - 2][cursorWidth - 1] = check;
		}
	}
	//left
	temp = -1;
	if (cursorHeight - 1 >= 0 && cursorWidth - 2 >= 0)
		temp = arry[cursorHeight - 1][cursorWidth - 2];
	if (temp == blank || checkB(temp))
	{

		arry[cursorHeight - 1][cursorWidth - 2] = open;
		if (temp == bKing)
		{
			arry[cursorHeight - 1][cursorWidth - 2] = check;
		}
	}
	
}

void knightB(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//down moves
	// left
	temp = -1;
	if (cursorHeight + 1 <= mapHeight - 1 && cursorWidth - 2 >= 0)
		temp = arry[cursorHeight + 1][cursorWidth - 2];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight + 1][cursorWidth - 2] = open;
		if (temp == wKing)
		{
			arry[cursorHeight + 1][cursorWidth - 2] = check;
		}
	}
	//right
	temp = -1;
	if (cursorHeight + 1 <= mapHeight - 1 && cursorWidth + 2 <= mapWidth - 1)
		temp = arry[cursorHeight + 1][cursorWidth + 2];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight + 1][cursorWidth + 2] = open;
		if (temp == wKing)
		{
			arry[cursorHeight + 1][cursorWidth + 2] = check;
		}
	}
	//bottom right
	temp = -1;
	if (cursorHeight + 2 <= mapHeight - 1 && cursorWidth + 1 <= mapWidth - 1)
		temp = arry[cursorHeight + 2][cursorWidth + 1];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight + 2][cursorWidth + 1] = open;
		if (temp == wKing)
		{
			arry[cursorHeight + 2][cursorWidth + 1] = check;
		}
	}
	//bottom left
	temp = -1;
	if (cursorHeight + 2 <= mapHeight - 1 && cursorWidth - 1 >= 0)
		temp = arry[cursorHeight + 2][cursorWidth - 1];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight + 2][cursorWidth - 1] = open;
		if (temp == wKing)
		{
			arry[cursorHeight + 2][cursorWidth - 1] = check;
		}
	}
	//up moves
	//right
	temp = -1;
	if (cursorHeight - 1 >= 0 && cursorWidth + 2 <= mapWidth - 1)
		temp = arry[cursorHeight - 1][cursorWidth + 2];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight - 1][cursorWidth + 2] = open;
		if (temp == wKing)
		{
			arry[cursorHeight - 1][cursorWidth + 2] = check;
		}
	}
	//upper right
	temp = -1;
	if (cursorHeight - 2 >= 0 && cursorWidth + 1 <= mapWidth - 1)
		temp = arry[cursorHeight - 2][cursorWidth + 1];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight - 2][cursorWidth + 1] = open;
		if (temp == wKing)
		{
			arry[cursorHeight - 2][cursorWidth + 1] = check;
		}
	}
	//upper left
	temp = -1;
	if (cursorHeight - 2 >= 0 && cursorWidth - 1 >= 0)
		temp = arry[cursorHeight - 2][cursorWidth - 1];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight - 2][cursorWidth - 1] = open;
		if (temp == wKing)
		{
			arry[cursorHeight - 2][cursorWidth - 1] = check;
		}
	}
	//left
	temp = -1;
	if (cursorHeight - 1 >= 0 && cursorWidth - 2 >= 0)
		temp = arry[cursorHeight - 1][cursorWidth - 2];
	if (temp == blank || checkW(temp))
	{

		arry[cursorHeight - 1][cursorWidth - 2] = open;
		if (temp == wKing)
		{
			arry[cursorHeight - 1][cursorWidth - 2] = check;
		}
	}
}

void bishopW(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//checks top left
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight - i >= 0 && cursorWidth - i >= 0)
		{
			if (arry[cursorHeight - i][cursorWidth - i] == blank)
			{
				arry[cursorHeight - i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth - i] == bKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth - i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth - i))
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
			if (arry[cursorHeight + i][cursorWidth + i] == blank)
			{
				arry[cursorHeight + i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth + i] == bKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth + i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth + i))
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


			if (arry[cursorHeight - i][cursorWidth + i] == blank)
			{
				arry[cursorHeight - i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth + i] == bKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth + i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth + i))
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


			if (arry[cursorHeight + i][cursorWidth - i] == blank)
			{
				arry[cursorHeight + i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth - i] == bKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth - i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth - i))
			{
				break;
			}
		}
	}
}

void bishopB(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	
	//checks top left
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight - i >= 0 && cursorWidth - i >= 0)
		{
			if (arry[cursorHeight - i][cursorWidth - i] == blank)
			{
				arry[cursorHeight - i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth - i))
			{
				
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth - i] == wKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth - i] = open;
				break;
			}
		}
	}

	//checks for bot right
	
	
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight + i<mapHeight && cursorWidth + i< mapWidth)
		{
			if (arry[cursorHeight + i][cursorWidth + i] == blank)
			{
				arry[cursorHeight + i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth + i))
			{
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth + i] == wKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth + i] = open;
				break;
			}
		}
	}
	
	//checks for top right

	
	
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight - i >= 0 && cursorWidth + i< mapWidth)
		{


			if (arry[cursorHeight - i][cursorWidth + i] == blank)
			{
				arry[cursorHeight - i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth + i))
			{
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth + i] == wKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth + i] = open;
				break;
			}
		}
	}
	
	//checks for bot left


	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight + i<mapHeight && cursorWidth - i >= 0)
		{


			if (arry[cursorHeight + i][cursorWidth - i] == blank)
			{
				arry[cursorHeight + i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth - i))
			{
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth - i] == wKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth - i] = open;
				break;
			}
		}
	}
}

void queenW(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//straights
	//checks up
	for (int i = cursorHeight - 1; i >= 0; i--)
	{
		if (arry[i][cursorWidth] == blank)
		{
			arry[i][cursorWidth] = open;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == bKing)
			{
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			break;
		}
	}

	//check down
	for (int i = cursorHeight + 1; i <= mapHeight - 1; i++)
	{
		if (arry[i][cursorWidth] == blank)
		{
			arry[i][cursorWidth] = open;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == bKing)
			{
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			break;
		}
	}
	//check left
	for (int i = cursorWidth - 1; i >= 0; i--)
	{
		if (arry[cursorHeight][i] == blank)
		{
			arry[cursorHeight][i] = open;
		}
		//checks for black 
		if (checkB(cursorHeight, i))
		{
			//checks for king
			if (arry[cursorHeight][i] == bKing)
			{
				break;
			}
			arry[cursorHeight][i] = open;
			break;
		}
		//checks for whites
		if (checkW(cursorHeight, i))
		{
			break;
		}
	}
	//check right
	for (int i = cursorWidth + 1; i <= mapWidth - 1; i++)
	{
		if (arry[cursorHeight][i] == blank)
		{
			arry[cursorHeight][i] = open;
		}
		//checks for black 
		if (checkB(cursorHeight, i))
		{
			//checks for king
			if (arry[cursorHeight][i] == bKing)
			{
				break;
			}
			arry[cursorHeight][i] = open;
			break;
		}
		//checks for whites
		if (checkW(cursorHeight, i))
		{
			break;
		}
	}

	//Diagonals

	//checks top left
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight - i >= 0 && cursorWidth - i >= 0)
		{
			if (arry[cursorHeight - i][cursorWidth - i] == blank)
			{
				arry[cursorHeight - i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth - i] == bKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth - i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth - i))
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
			if (arry[cursorHeight + i][cursorWidth + i] == blank)
			{
				arry[cursorHeight + i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth + i] == bKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth + i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth + i))
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


			if (arry[cursorHeight - i][cursorWidth + i] == blank)
			{
				arry[cursorHeight - i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth + i] == bKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth + i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth + i))
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


			if (arry[cursorHeight + i][cursorWidth - i] == blank)
			{
				arry[cursorHeight + i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth - i] == bKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth - i] = open;
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth - i))
			{
				break;
			}
		}
	}
}

void queenB(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//checks up
	for (int i = cursorHeight - 1; i >= 0; i--)
	{
		if (arry[i][cursorWidth] == blank)
		{
			arry[i][cursorWidth] = open;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			break;
		}
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == wKing)
			{
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
	}

	//check down
	for (int i = cursorHeight + 1; i <= mapHeight - 1; i++)
	{
		if (arry[i][cursorWidth] == blank)
		{
			arry[i][cursorWidth] = open;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			break;
		}
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == wKing)
			{
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
	}
	//check left
	for (int i = cursorWidth - 1; i >= 0; i--)
	{
		if (arry[cursorHeight][i] == blank)
		{
			arry[cursorHeight][i] = open;
		}
		//checks for black 
		if (checkB(cursorHeight, i))
		{
			break;
		}
		//checks for whites
		if (checkW(cursorHeight, i))
		{
			//checks for king
			if (arry[cursorHeight][i] == wKing)
			{
				break;
			}
			arry[cursorHeight][i] = open;
			break;
		}
	}
	//check right
	for (int i = cursorWidth + 1; i <= mapWidth - 1; i++)
	{
		if (arry[cursorHeight][i] == blank)
		{
			arry[cursorHeight][i] = open;
		}
		//checks for black 
		if (checkB(cursorHeight, i))
		{
			break;
		}
		//checks for whites
		if (checkW(cursorHeight, i))
		{
			//checks for king
			if (arry[cursorHeight][i] == wKing)
			{
				break;
			}
			arry[cursorHeight][i] = open;
			break;
		}
	}
	//diagonals
	//checks top left
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight - i >= 0 && cursorWidth - i >= 0)
		{
			if (arry[cursorHeight - i][cursorWidth - i] == blank)
			{
				arry[cursorHeight - i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth - i))
			{

				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth - i] == wKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth - i] = open;
				break;
			}
		}
	}

	//checks for bot right


	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight + i<mapHeight && cursorWidth + i< mapWidth)
		{
			if (arry[cursorHeight + i][cursorWidth + i] == blank)
			{
				arry[cursorHeight + i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth + i))
			{
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth + i] == wKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth + i] = open;
				break;
			}
		}
	}

	//checks for top right
	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight - i >= 0 && cursorWidth + i< mapWidth)
		{


			if (arry[cursorHeight - i][cursorWidth + i] == blank)
			{
				arry[cursorHeight - i][cursorWidth + i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight - i, cursorWidth + i))
			{
				break;
			}
			//checks for whites
			if (checkW(cursorHeight - i, cursorWidth + i))
			{
				//checks for king
				if (arry[cursorHeight - i][cursorWidth + i] == wKing)
				{
					break;
				}
				arry[cursorHeight - i][cursorWidth + i] = open;
				break;
			}
		}
	}

	//checks for bot left


	for (int i = 1; i < mapHeight; i++)
	{
		if (cursorHeight + i<mapHeight && cursorWidth - i >= 0)
		{


			if (arry[cursorHeight + i][cursorWidth - i] == blank)
			{
				arry[cursorHeight + i][cursorWidth - i] = open;
			}
			//checks for black 
			if (checkB(cursorHeight + i, cursorWidth - i))
			{
				break;
			}
			//checks for whites
			if (checkW(cursorHeight + i, cursorWidth - i))
			{
				//checks for king
				if (arry[cursorHeight + i][cursorWidth - i] == wKing)
				{
					break;
				}
				arry[cursorHeight + i][cursorWidth - i] = open;
				break;
			}
		}
	}
}

//color checks
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
bool checkB(int pieceTemp)
{
	if (pieceTemp == bPawn
		|| pieceTemp == bRook
		|| pieceTemp == bKnight
		|| pieceTemp == bBishop
		|| pieceTemp == bQueen
		|| pieceTemp == bKing
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
bool checkW(int pieceTemp)
{
	if (pieceTemp == wPawn
		|| pieceTemp == wRook
		|| pieceTemp == wKnight
		|| pieceTemp == wBishop
		|| pieceTemp == wQueen
		|| pieceTemp == wKing
		)
	{
		return true;
	}

	return false;
}
//for castling
//marks if a rook or king is moved
void checkMoves()
{
	
	//if it's a black rook
	//marks it as moved
	if (selectedPiece == bRook)
	{
		//if it's on the right
		if (selectedWidth == 7 && selectedHeight == 7)
		{
			bRookr = false;
		}
		//if it's on the left
		if (selectedWidth == 0 && selectedHeight == 7)
		{
			bRookl = false;
		}
	}

	//if it's a white rook
	//marks it as moved
	if (selectedPiece == wRook)
	{
		//if it's on the right
		if (selectedWidth == 7 && selectedHeight == 0)
		{
			wRookr = false;
		}
		//if it's on the left
		if (selectedWidth == 0 && selectedHeight == 0)
		{
			wRookl = false;
		}
	}
	//if it's either king has moved
	//marks as moved
	if (selectedPiece == wKing || selectedPiece == bKing)
	{
		if (selectedWidth == 4 && selectedHeight == 7)
		{
			bKingCastl = false;
		}
		if (selectedWidth == 4 && selectedHeight == 0)
		{
			wKingCastl = false;
		}
	}

}
//for kings

//draws the board for attack posistions of white units
void drawBKingCheck()
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			//cursorWidth = j;
			//cursorHeight = i;
			//checks for and prints piece
			for (int index = 0; index < numIcons; index++)
			{
				if (mapArray[i][j] == index)
				{
					switch (index)
					{
						//reversed the functions so king won't attack something that is targeted by another except wpawnattack
						// functions relies on cursorHeight
						//need to ingore jump and move foward
					case wPawn:
						wPawnAttack(mapX, i, j);
						break;

					case wRook:
						rookB(mapX, i, j);
						break;

					case wKnight:
						knightB(mapX, i, j);
						break;

					case wBishop:
						bishopB(mapX, i, j);
						break;

					case wQueen:
						queenB(mapX, i, j);
						break;

						//just make it so kings can't go next to eachother (aka use full 8 cirlce)
					case wKing:
						for (int index = -1; index <= 1; index++)
						{
							for (int jndex = -1; jndex <= 1; jndex++)
							{
								//note to self why is this commented out?
								//			mapX[i + index][j + jndex] = open;
							}
						}
						break;
					}
				}
			}
		}
	}
}
//draws the board for attack posistions of black units
void drawWKingCheck()
{
	//for checking the attack zones of ememies
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			//cursorWidth = j;
			//cursorHeight = i;
			//checks for and prints piece
			for (int index = 0; index < numIcons; index++)
			{
				if (mapArray[i][j] == index)
				{
					switch (index)
					{
						//reversed the functions so king won't attack something that is targeted by another
						// functions relies on cursorHeight
						//need to ingore jump and move foward
					case bPawn:
						bPawnAttack(mapX, i, j);
						break;

					case bRook:
						rookW(mapX, i, j);
						break;

					case bKnight:
						knightW(mapX, i, j);
						break;

					case bBishop:
						bishopW(mapX, i, j);
						break;

					case bQueen:
						queenW(mapX, i, j);
						break;

						//just make it so kings can't go next to eachother (aka use full 8 cirlce)
					case bKing:
						for (int index = -1; index <= 1; index++)
						{
							for (int jndex = -1; jndex <= 1; jndex++)
							{
								mapX[i + index][j + jndex] = open;
							}
						}
						break;
					}
				}
			}
		}
	}
}
//for check mech

// checks if wKing is in check 
//true if checked
//false if not
bool wKingCheck()
{
	drawWKingCheck();
	//if king is in check

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (mapX[i][j] == wKing)
			{
				return false;
			}
		}
	}
	return true;
}
// checks if bKing is in check 
//true if checked
//false if not
bool bKingCheck()
{
	drawBKingCheck();
	//if king is in check

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (mapX[i][j] == bKing)
			{
				return false;
			}
		}
	}
	return true;
}
//switches who's turn it is black pieces can only move on true and white pieces can only move on false (b==true/w==false) 
void turnOver()
{
	/*
	if (turn == true)
	{
		turn = false;
	}
	else if (turn == false)
	{
		turn = true;
	}
	*/
	
}
void rookWCheck(int arry[][mapWidth], int cursorHeight, int cursorWidth)
{
	//down	 note to self finsh adding other attack directions
	for (int i = cursorHeight - 1; i >= 0; i--)
	{
		//checks for whites
		if (checkW(i, cursorWidth))
		{
			break;
		}
		//checks for black 
		if (checkB(i, cursorWidth))
		{
			//checks for king
			if (arry[i][cursorWidth] == bKing)
			{
				arry[i][cursorWidth] = check;
				break;
			}
			arry[i][cursorWidth] = open;
			break;
		}
		if (arry[i][cursorWidth] == blank)
		{
			//moves the wRook to it's new position
			mapCheck[cursorHeight][cursorWidth] = blank;
			//arry[i][cursorWidth] = open;
			mapCheck[i][cursorWidth] = wRook;
			//if wKingCheck true continue the search else end the search
			if (wKingCheck() == false)
			{
				return;
			}
			//after check resets
			mapCheck[i][cursorWidth] = blank;
			mapCheck[cursorHeight][cursorWidth] = wRook;
		}


	}
}
void checkMate()
{
	//copy board after the king is placed in check
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			mapCheck[i][j] = mapArray[i][j];
		}
	}

	//loop through this new map and test if you can save the king
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			switch (mapCheck[i][j])
			{

			case wRook:
				//clears map of '#'s
				//not sure if any of this should be used as is...
				reverseCopyMap();
				//note to self add map check copy... at the beginning of it's calling
				//i and j are the posistion of the piece that'll be called instead of cursor width and stuff
				rookWCheck(mapCheck, i, j);




				//makes the next # selected a wRook
				selectedPiece = wRook;
				selectedWidth = cursorWidth;
				selectedHeight = cursorHeight;
				break;

			}

				
		}
	}
}
