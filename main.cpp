#include "Header.h"
int main() {
	// setlocale(LC_ALL, "Ru");
	float x = 0, y = 0, length = 3000;
	float t0 = 1, tk = 5000;
	TAirport DEMO_AIRPORT(x, y, length);
	DEMO_AIRPORT.Do(t0, tk);
	return 0;
}