#pragma once
#include "gameClass.h"
#include<iostream>
#include"windowManager.h"
#include"entityClass.h"
#include"playerClass.h"
#include<time.h>
#include"buttonClass.h"
#include<vector>

using namespace sf;
using namespace std;



class actualGame :
    public gameClass
{

public:

    sf::Clock c;
    sf::Time t;

   /* sf::Clock clocks;
    sf::Time times;*/


    int i, j;

    Sprite background, frame, s;
    Texture t2, t3;

    sf::Texture t1;
    std::vector<sf::Sprite> s_Vector;
    bool pushBackBool;
    
    
    
    sf::Music music;
    bool gameOverBool = false, forBool = true, forBool2 = true, lastBool = false;
    

    int dx = 0; bool rotate = 0; int colorNum = 1;
    float timer = 0, delay = 0.3;

    Clock clock;
    static float time;

    struct Point
    {
        int x = 0, y = 0;
    } a[4], b[4];


    static const int M = 20;
    static const int N = 10;

    inline static int field[M][N] = { 0 };


    int figures[7][4] =
    {
        1,3,5,7, // I
        2,4,5,7, // Z
        3,5,4,6, // S
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };

    actualGame();
    ~actualGame();

    sf::Event ev;
    sf::Font font;
    sf::Text myText;

    
    bool check();    

    void loadFile();
    //bool startFirstFrame();
    void update();
    void draw();
};

