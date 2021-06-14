#include<iostream>
#include<cstdlib>
#include<Windows.h>

//constant variables
const int HEIGHT = 24;
const int WIDTH = 10;
const int FPS = 100;
const int DELTA_TIME = 1000 / FPS;

//I want to push this kind of information in a header file
int level[] = { 80, 72, 64, 56, 48, 40, 32, 24, 16, 10, 8, 8, 8, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

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

//update the display the current MAP
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

//this will be called every frame
bool gameloop() {
	
	return false;
}

//this will be called everytime the block drops one unit
void actOfGravity() {

}

//Main Function
int main() {
	int current_level = 0;
	std::cout << CLOCKS_PER_SEC;	
	while (true) {
		actOfGravity();
		for (int _ = 0; _ < level[current_level]; _++) {
			Sleep(DELTA_TIME);
			gameloop();
			update();
		}
	}
	return 0;
}