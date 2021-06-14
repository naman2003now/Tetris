#include<iostream>
#include<cstdlib>
#include<time.h>

const int HEIGHT = 24;
const int WIDTH = 10;
//Initializing a playing field of Size Height * width
bool MAP[WIDTH][HEIGHT];

void update() {
	system("cls");
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

	std::cout << output_string;
}

int main() {

	std::cout << "Hello, Tetris!!" << std::endl;
	clock_t current_time = clock();
	clock_t delta_time = 1 / CLOCKS_PER_SEC * 60;
	while (true) {
		while (current_time - clock() < delta_time){

		}
		update();
	}
	return 0;
}