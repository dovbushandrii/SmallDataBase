#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include "RandomClass.h"
#include <cmath>

using namespace std;

string Random::randstr()
{
    string newgeneratedstr;
    for (int i = 0; i < 15; i++) {
        time_t a = time(NULL);
        int newsymbol = (rand() + a) % 25;
        newgeneratedstr += (char)newsymbol + 'a';
    }
    return newgeneratedstr;
}

int Random::randbyte() {
    time_t a = time(NULL);
    int newsymbol = (rand() + a) % 10;
    return newsymbol;
}

Type Random::randtype() {
    time_t a = time(NULL);
    int newsymbol = (rand() + a) % 4;
    switch (newsymbol) {
    case 1: return Type::INTER; break;
    case 2: return Type::INTERCITY; break;
    case 3: return Type::STANDART; break;
    case 0: return Type::SPEED; break;
    }
}

float Random::randrate() {
    int size = this->randbyte();
    float res = 1;
    for (int i = 0; i < size; i++) {
        res += this->randbyte();
        res += randbyte() * pow(10, i);
    }
    res = res / (randbyte() % 5);
    return res;
}

Date Random::randdate() {
    Date newdate;
    newdate.day = randbyte();
    newdate.month = randbyte();
    newdate.year = randbyte();
    newdate.hours = randbyte();
    newdate.minutes = randbyte();
    newdate.hours2 = randbyte();
    newdate.minutes2 = randbyte();
    return newdate;
}