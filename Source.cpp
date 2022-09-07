#include "Header.h"
using namespace std;
TAObject::TAObject(float x, float y) {
    this->x = x;
    this->y = y;
}
//TAObject::~TAObject(){};
TLA::TLA(float x, float y, float V, float xc, float yc)
    : TAObject(x, y) {
    this->xc = xc;
    this->yc = yc;
    this->V = V;
    landed = false;
    this->a = 0;
}
void TLA::move(float t, int a) {
    a==0?isBusy=false:isBusy=true;
    // if (a == 0)  isBusy = false; 
    // if (a == 1)  isBusy = true; 
    if (x > xc) b = 0;
    if (x <= xc && y <= yc) { b = -1; }
    if (x <= xc && y >= yc) { b = 1; }
    fi = b * PI + atan((y - yc) / (x - xc));
    r = sqrt(pow((x - xc), 2) + pow((y - yc), 2));
}
TAircraft::TAircraft(float x, float y, float V, float xc, float yc) 
    : TLA(x, y, V, xc, yc) {
    type = 1;
}
THelicopter::THelicopter(float x, float  y, float V, float xc, float yc)
    : TLA(x, y, V, xc, yc) {
    type = 0;
}
void TAircraft::move(float t, int a) {
    this->TLA::move(t, this->a);
    double omega = (-1) * (V / r);
    xc = -(x + r * cos(fi + omega * t)) * (this->a - 1) + this->a * (xc - V * dt);
    yc = -(y + r * sin(fi + omega * t)) * (this->a - 1) + yc * this->a;
}
void THelicopter::move(float t, int a) {
    this->TLA::move(t, this->a);
    xc = xc + (this->a * V * cos(fi) * dt);
    yc = yc + (this->a * V * sin(fi) * dt);
}
TAirport::TAirport(float x, float y, float length)
    : TAObject(x, y) {
    this->length = length;
    LA = new TLA * [num];
    float xc, yc, V;
    srand(time(NULL));
    for (int i = 0; i < num; i++) {

        xc = rand() % 10000 + 10000;
        cout << "Dist. xc: " << xc << endl;
        yc = rand() % 1000 + 3000;
        cout << "Dist. yc: " << yc << endl;
        V = rand() % 100 + 100;
        cout << "Veloc. V = " << V << endl;
        cout << "_________________" << endl;
        bool type = rand() % 2;
        type? LA[i] = new TAircraft(x, y, V, xc, yc): LA[i] = new THelicopter(x, y, V, xc, yc);
    }
}
void TAirport::Do(float t0, float tk) {
    ofstream FILE("LOG.txt");
    for (float time = t0; time <= tk; time += dt) {
        for (int i = 0; i < num; i++) {
            if (LA[i]->landed)
                continue;
            double X = this->x + 1.1 * this->length;
            if (LA[i]->type) {
                if (!LA[i]->a) {
                    if ((!(this->isBusy && !LA[i]->isBusy)) && (LA[i]->xc > X) && (abs(LA[i]->yc - this->y) < (this->length / 50))) {
                        LA[i]->a = 1;
                        this->isBusy = true;
                    }
                    else LA[i]->a = 0;
                }
                else {
                    if ((LA[i]->xc < (this->x + this->length)) && LA[i]->isBusy) {
                        LA[i]->landed = true;
                        index++;
                        this->isBusy = false;
                    }
                    else
                    if (this->isBusy) LA[i]->landed = false;
                }
            }
            else {
                if (!LA[i]->a) {
                    if (!(this->isBusy && !(LA[i]->isBusy))) {
                        LA[i]->a = 1;
                        this->isBusy = true;
                    }
                    else {
                        LA[i]->a = 0;
                    }
                }
                else {
                    if (((pow((LA[i]->xc - this->x), 2) + pow((LA[i]->yc - this->y), 2)) < pow((this->length / 50), 2)) && LA[i]->isBusy) {
                        LA[i]->landed = true;
                        index++;
                        this->isBusy = false;
                    }
                    else {
                        LA[i]->landed = false;
                    }
                }
            }
            LA[i]->move(time, LA[i]->a);
            // if ((LA[i]->landed)) {
            //     LA[i]->type? FILE << "Aircraft " << i << " landed at " << time << " sec." << endl
            //     : FILE << "Helicopter " << i << " landed at " << time << " sec." << endl;
            // }

            //output to file aircraft type and number, time of landing
            if (LA[i]->landed) {
                if (LA[i]->type) 
                FILE << "Aircraft " << i << " landed at " << time << " sec." << endl;
                else
                FILE << "Helicopter " << i << " landed at " << time << " sec." << endl;
            }
        }
    }
    FILE.close();
}