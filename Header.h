#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#define PI 3.14159265
const float dt = 0.1;
const short num = 40;
// const short num1 = rand()%num;                   //LA for 1st runway
// const short num2 = num - num1;           //LA for 2nd runway
const short RW_count;
using namespace std;

//tla** la //массив для хранения динамических переменных, 
    //чтобы можно было удалять не только массив, но и его объекты

//предварительные объявления класса/проттоипы классаё
class TAObject {
public:
    float x, y;
    bool isBusy;
    TAObject(float x, float y);
    ~TAObject();

};

class TLA : public TAObject {
public:
    int isLanding, b;
    float xc, yc, r, fi, V;
    bool landed,type;
    TLA(float x, float y, float V, float xc, float yc);
    virtual void move(float t, int a);
};

class TAircraft : public TLA {
public:
    TAircraft(float x, float  y, float V, float xc, float yc);
    //override makes sure that the method is actually overridden 
    void move(float t, int a) override;
};

class  THelicopter : public TLA {
public:
    THelicopter(float x, float  y, float V, float xc, float yc);
    void move(float t, int a) override;
};

class TAirport : public TAObject {
public:
    int index = 0;
    float length;
    TLA** LA;
    TAirport(float x, float y, float length);
    void Do(float t0, float tk);
};

