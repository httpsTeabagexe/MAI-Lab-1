#include "Header.h"
int main() {
    // setlocale(LC_ALL, "Ru");
    float x = 0, y = 0, length = 3000;
    float t0 = 1, tk = 5000;
    TAirport DEMO_AIRPORT(x, y, length);
    DEMO_AIRPORT.Do(t0, tk);
    return 0;
    //create test file with 20 aircrafts and 20 helicopters and check if they land at the airport and at what time
    // std::ofstream FILE("TEST.txt");
    // float x = 0, y = 0, length = 3000;
    // float t0 = 1, tk = 5000;
    // TAirport DEMO_AIRPORT(x, y, length);
    // for (int i = 0; i < num; i++) {
    //     if (i % 2) {
    //         DEMO_AIRPORT.LA[i] = new TAircraft(x, y, 100, x + 1.1 * length, y);
    //     }
    //     else {
    //         DEMO_AIRPORT.LA[i] = new THelicopter(x, y, 100, x + 1.1 * length, y);
    //     }
    // }

}
