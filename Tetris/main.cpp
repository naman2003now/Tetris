#include<iostream>
#include<cstdlib>
#include<Windows.h>
#include "tetris.cpp"

//constant variables
const int HEIGHT = 24;
const int WIDTH = 10;
const int FPS = 100;
const int DELTA_TIME = 1000 / FPS;
int tempcoord = 0;

//Initializing a playing field of Size Height * width
bool STATIC_MAP[WIDTH][HEIGHT];
bool MOVING_MAP[WIDTH][HEIGHT];


bool addPiece(int, int, int, int, bool[WIDTH][HEIGHT]);
bool xyCheck(int, int, bool);
bool input = false;


class Block {
public:
	int x = 4;
	int y = 0;
	int pieceNumber = 3;
	int rotation = 0;

	bool moveDown() {
		bool possible;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				MOVING_MAP[i][j] = 0;
			}
		}
		y++;
		if (addPiece(x, y, pieceNumber, rotation, MOVING_MAP)) {

			return true;
		}
		else {
			y--;
			for (int i = 0; i < WIDTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					MOVING_MAP[i][j] = 0;
				}
			}
			addPiece(x, y, pieceNumber, rotation, MOVING_MAP);
			return false;
		}
	}

	bool moveRight() {
		bool possible;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				MOVING_MAP[i][j] = 0;
			}
		}
		x++;
		if (addPiece(x, y, pieceNumber, rotation, MOVING_MAP)) {

			return true;
		}
		else {
			x--;
			for (int i = 0; i < WIDTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					MOVING_MAP[i][j] = 0;
				}
			}
			addPiece(x, y, pieceNumber, rotation, MOVING_MAP);
			return false;
		}
	}

	bool moveLeft() {
		bool possible;
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				MOVING_MAP[i][j] = 0;
			}
		}
		x = x - 1;
		if (addPiece(x, y, pieceNumber, rotation, MOVING_MAP)) {

			return true;
		}
		else {
			x++;
			for (int i = 0; i < WIDTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					MOVING_MAP[i][j] = 0;
				}
			}
			addPiece(x, y, pieceNumber, rotation, MOVING_MAP);
			return false;
		}
	}

	bool rotate() {
		for (int i = 0; i < WIDTH; i++) {
			for (int j = 0; j < HEIGHT; j++) {
				MOVING_MAP[i][j] = 0;
			}
		}
		if (rotation >= 3) {
			rotation = 0;
		}
		else {
			rotation++;
		}
		if (addPiece(x, y, pieceNumber, rotation, MOVING_MAP)) {
			return true;
		}
		else {
			if (rotation >= 3) {
				rotation = 3;
			}
			else {
				rotation--;
			}
			for (int i = 0; i < WIDTH; i++) {
				for (int j = 0; j < HEIGHT; j++) {
					MOVING_MAP[i][j] = 0;
				}
			}
			addPiece(x, y, pieceNumber, rotation, MOVING_MAP);
			return false;
		}
	}

};

void clearscreen() //This is STACKOVERFLOW code Yeah but it's fast as fuck
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

//update the display the current MAP
void update(bool funcMap[WIDTH][HEIGHT], bool funcMovingMap[WIDTH][HEIGHT]) {
	
	std::string output_string;

	for (int j = 0; j < HEIGHT; j++) {
		output_string += "|";
		for (int i = 0; i < WIDTH; i++) {
			if (funcMap[i][j] || funcMovingMap[i][j]) {
				output_string += "[]";
			}
			else {
				output_string += "  ";
			}
		}
		output_string += "|\n";
	}
	clearscreen();
	std::cout << output_string;
}

//Update The piece in the map
bool addPiece(int x, int y, int piece, int rotation, bool funcMap[WIDTH][HEIGHT]) {
	bool returnVariable = true;
	for (int i = 0; i < 4; i++) {
		int coordX = x + tetris::piece(piece, rotation, i, 0);
		int coordY = y + tetris::piece(piece, rotation, i, 1);
		if (xyCheck(coordX, coordY, true)) {
			funcMap[coordX][coordY] = 1;
		}
		else {
			returnVariable = false;
		}
	}
	return returnVariable;
}

//this will be called every frame
bool gameloop(Block &block) {
	if (GetAsyncKeyState(VK_LEFT)) {
		if (input) {
			input = false;
			block.moveLeft();
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)) {
		if (input) {
			input = false;
			block.moveRight();
		}
	}
	else if (GetAsyncKeyState(VK_UP)) {
		if (input) {
			input = false;
			block.rotate();
		}
	}
	else {
		input = true;
	}
	return false;
}

bool xyCheck(int x, int y, bool top) {
	if (x >= WIDTH || x < 0) {
		return false;
	}
	else if (y >= HEIGHT) {
		return false;
	}
	else if (top && y < 0) {
		return false;
	}
	else if (STATIC_MAP[x][y]) {
		return false;
	}
	return true;
}


//this will be called everytime the block drops one unit
void actOfGravity() {

}

//Main Function
int main() {
	int current_level = 9;
	std::cout << CLOCKS_PER_SEC;	
	while (true) {
		Block block;
		for (int steps = 0; steps < 32; steps++) {
			block.moveDown();
			actOfGravity();
			for (int _ = 0; _ < tetris::level(current_level); _++) {
				Sleep(DELTA_TIME);
				gameloop(block);
				update(STATIC_MAP, MOVING_MAP);
			}
		}
		addPiece(block.x, block.y, block.pieceNumber, block.rotation, STATIC_MAP);
	}
	return 0;
}