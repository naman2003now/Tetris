#include<iostream>
#include<cstdlib>
#include<Windows.h>

const int HEIGHT = 24;
const int WIDTH = 10;
const int FPS = 100;
const int DELTA_TIME = 1000 / FPS;

//Initializing a playing field of Size Height * width
bool MAP[WIDTH][HEIGHT];

void clearscreen() //This is STACKOVERFLOW code Yeah but it's fast as fuck
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void update() {
	
	std::string output_string;

	for (int j = 0; j < HEIGHT; j++) {
		output_string += "|";
		for (int i = 0; i < WIDTH; i++) {
			if (MAP[i][j]) {
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


int main() {
	
	std::cout << CLOCKS_PER_SEC;	
	while (true) {
		Sleep(DELTA_TIME);
		update();
	}
	return 0;
}