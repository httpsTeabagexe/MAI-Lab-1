#include "Header.h"

//todo вторая впп и ввыыводить в файл на какую впп приземлился летательный аппарат
int main() {
	float x = 0, y = 0, length = 4000;
	float t0 = 1, tk = 7500;
	float XY_offset = 1000;
	float l_offset = 1000;
	TAirport DEMO(x, y, length); //first airport
	TAirport DEMO2(x+XY_offset, y+XY_offset, length); //second airport
	DEMO.Do(t0, tk);
	DEMO2.Do(t0, tk);


}