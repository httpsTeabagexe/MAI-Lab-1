#include "Header.h"
TAObject::TAObject(float x, float y) {
    this->x = x;
    this->y = y;
}
TAObject::~TAObject(){}

TLA::TLA(float x, float y, float V, float xc, float yc)
    : TAObject(x, y) {
    this->xc = xc;
    this->yc = yc;
    this->V = V;
    landed = false;
    this->isLanding = 0;
}
void TLA::move(float t, int isLanding) {
    isLanding==0?isBusy=false:isBusy=true;
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

void TAircraft::move(float t, int isLanding) {
    this->TLA::move(t, this->isLanding);
    double omega = (-1) * (V / r);
    xc = -(x + r * cos(fi + omega * t)) * (this->isLanding - 1) + this->isLanding * (xc - V * dt);
    yc = -(y + r * sin(fi + omega * t)) * (this->isLanding - 1) + yc * this->isLanding;
}
void THelicopter::move(float t, int isLanding) {
    this->TLA::move(t, this->isLanding);
    xc = xc + (this->isLanding * V * cos(fi) * dt);
    yc = yc + (this->isLanding * V * sin(fi) * dt);
}

TAirport::TAirport(){};

TAirport::TAirport(float x, float y, float length)
    : TAObject(x, y) {
        srand(time(NULL));
    this->length = length;
    LA = new TLA* [num];    
    float xc, yc, V;
    for (int i = 0; i < num; i++) {

        xc = rand() % 10000 + 10000;
        cout << "Dist. xc: " << xc << endl;
        yc = rand() % 1000 + 3000;
        cout << "Dist. yc: " << yc << endl;
        V = rand() % 100 + 100;
        cout << "Veloc. V = " << V << endl;
        cout << "_________________" << endl;
        bool type = rand() % 2;
        type? LA[i] = new TAircraft(x, y, V, xc, yc) 
        : LA[i] = new THelicopter(x, y, V, xc, yc);
    }
}
void TAirport::Do(float t0, float tk){
    short rw1=1; short rw2=2;
    ofstream FILE1("LOG1.txt"); ofstream FILE2("LOG2.txt");


    TAirport* AP = new TAirport[RW_count];    
    //if(AP[0].isBusy)
for(int i = 0; i<RW_count ; i++){

    for(float time = t0; time<tk;time+=dt){
        if (LA[i]->landed)
                continue;
            double X = this->x + 1.1 * this->length;
            if (LA[i]->type) {
                if (!LA[i]->isLanding) {
                    if ((!(AP[i].isBusy && !LA[i]->isBusy)) && (LA[i]->xc > X) && (abs(LA[i]->yc - this->y) < (this->length / 50))) {
                        LA[i]->isLanding = 1;
                        
                        AP[i].isBusy = true;
                    }
                    else LA[i]->isLanding = 0;
                }
                else {
                    if ((LA[i]->xc < (this->x + this->length)) && LA[i]->isBusy) {
                        LA[i]->landed = true;
                        index++;
                        AP[i].isBusy = false;
                    }
                    else
                    if (AP[i].isBusy)
                        LA[i]->landed = false;
                }
            }
    }
    }
}
/*
void TAirport::Do(float t0, float tk) {
    short rwy1 = 1; short rwy2 = 2;
    ofstream FILE("LOG1.txt");
    ofstream FILE2("LOG2.txt");
    for (float time = t0; time <= tk; time += dt) {
        for (int i = 0; i < num1; i++) {
            
            else {
                if (!LA[i]->isLanding) {
                    if (!(this->isBusy && !(LA[i]->isBusy))) {
                        LA[i]->isLanding = 1;
                        this->isBusy = true;
                    }
                    else {
                        LA[i]->isLanding = 0;
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
            LA[i]->move(time, LA[i]->isLanding);
            //output to file aircraft type and number, time of landing
            if (LA[i]->landed) {
                if (LA[i]->type)
                    FILE << "Aircraft " << i << " landed at " << time << " sec." << "at the runway №: " << rwy << endl;
                else
                    FILE << "Helicopter " << i << " landed at " << time << " sec." << "at the runway №: "<< rwy << endl;
            }

        }
    }
    FILE.close();
}
*/

