#include <graphics.h>
#include <stdlib.h>
#define width 1280
#define height 700

int i,X[100],Y[100],M[100],N[100],s=16,l,d=2;

void nice_intro();
void moveCode(int startX, int startY, int endX, int endY, char direction[]);

int main(){

    initwindow(width,height);

    nice_intro();

    getch();
    closegraph();
    return 0;
}

void moveCode(int startX, int startY, int endX, int endY, char direction[]){

    setfillstyle(7, 3); // display snake when immediately game opens
	X[0] = s*(startX/s);
	Y[0] = s*(startY/s);
	bar(X[0] - s / 2, Y[0] - s / 2, X[0] + s / 2, Y[0] + s / 2);

	M[0] = s * (endX/s);
	N[0] = s * (endY/s);
    setfillstyle(4,3);
	bar(M[0] - s/2,N[0] - s/2,M[0] + s/2,N[0] + s/2);

	l = 1;

	while (1)
	{
	    // displaying the snake
		setfillstyle(7, 3);
		for (i = 0; i < l; i++)
			bar(X[i] - s / 2, Y[i] - s / 2, X[i] + s / 2, Y[i] + s / 2);
		delay(1);

		for (i = l - 1; i > 0; i--)
		{
			X[i] = X[i - 1];
			Y[i] = Y[i - 1];
		}
    if(direction == "up"){
		Y[0] = Y[0] - s;
    }
    else if (direction == "down"){
        Y[0] = Y[0] + s;
    }
    else if (direction == "right"){
        X[0] = X[0] + s;
    }
    else if (direction == "left"){
        X[0] = X[0] - s;
    }
    else if (direction == "bottomright"){
        X[0] = X[0] + s;
        Y[0] = Y[0] + s;
    }
    else if (direction == "upright"){
            X[0] = X[0] + s;
            Y[0] = Y[0] - s;
    }
    else if(direction == "upleft"){
            X[0] = X[0] - s;
            Y[0] = Y[0] - s;
    }

		if (getpixel(X[0], Y[0]) == 3)
		{
			return;
		}
    }
}

void nice_intro(){

//P
   moveCode(100,200,100,100,"up");
   moveCode(100,100,150,100,"right");
   moveCode(150,100,150,150,"down");
   moveCode(150,150,100,150,"left");

//R
    moveCode(180,200,180,100,"up");
    moveCode(180,100,230,100,"right");
    moveCode(230,100,230,150,"down");
    moveCode(230,150,180,150,"left");
    moveCode(180,150,230,200,"bottomright");

//E
    moveCode(260,200,260,100,"up");
    moveCode(260,100,310,100,"right");
    moveCode(260,150,310,150,"right");
    moveCode(260,200,310,200,"right");

//P
   moveCode(340,200,340,100,"up");
   moveCode(340,100,390,100,"right");
   moveCode(390,100,390,150,"down");
   moveCode(390,150,340,150,"left");

//A
    moveCode(420,200,420,100,"up");
    moveCode(420,100,470,100,"right");
    moveCode(470,100,470,200,"down");
    moveCode(420,150,470,150,"right");

//R
    moveCode(500,200,500,100,"up");
    moveCode(500,100,550,100,"right");
    moveCode(550,100,550,150,"down");
    moveCode(550,150,500,150,"left");
    moveCode(500,150,550,200,"bottomright");

//E
    moveCode(580,200,580,100,"up");
    moveCode(580,100,630,100,"right");
    moveCode(580,150,630,150,"right");
    moveCode(580,200,630,200,"right");

//D
   moveCode(660,200,660,100,"up");
   moveCode(660,100,710,100,"right");
   moveCode(710,100,710,200,"down");
   moveCode(710,200,660,200,"left");


//B
   moveCode(840,200,840,100,"up");
   moveCode(840,100,890,100,"right");
   moveCode(890,100,890,200,"down");
   moveCode(890,200,840,200,"left");
   moveCode(840,150,890,150,"right");

//Y
   moveCode(970,150,970,100,"up");
    moveCode(970,150,920,100,"upleft");
    moveCode(920,200,970,150,"upright");

//:
setfillstyle(1,2);
    bar(1050,120,1070,140);
    bar(1050,160,1070,180);
   // moveCode(1050,170,1050,160,"up");
    //moveCode(1050,140,1050,130,"up");


//R
    moveCode(180,400,180,300,"up");
    moveCode(180,300,230,300,"right");
    moveCode(230,300,230,350,"down");
    moveCode(230,350,160,350,"left");
    moveCode(160,350,230,400,"bottomright");

//O
    moveCode(260,400,260,300,"up");
   moveCode(260,300,310,300,"right");
   moveCode(310,300,310,400,"down");
   moveCode(310,400,260,400,"left");

//J
    moveCode(340,300,390,300,"right");
    moveCode(375,300,375,400,"down");
    moveCode(375,400,340,400,"left");
    moveCode(340,400,340,350,"up");

//A
    moveCode(420,400,420,300,"up");
    moveCode(420,300,470,300,"right");
    moveCode(470,300,470,400,"down");
    moveCode(420,350,470,350,"right");

//L
    moveCode(500,300,500,400,"down");
    moveCode(500,400,550,400,"right");

//S, 710,760 x 300 400
   moveCode(760,300,710,300,"left");
   moveCode(710,300,710,350,"down");
    moveCode(710,350,760,350,"right");
    moveCode(760,350,760,400,"down");
    moveCode(760,400,710,400,"left");

//A, 790,840
    moveCode(790,400,790,300,"up");
    moveCode(790,300,840,300,"right");
    moveCode(840,300,840,400,"down");
    moveCode(840,350,790,350,"left");

//T
    moveCode(870,300,930,300,"right");
    moveCode(900,300,900,400,"down");

//I, 950, 1000
    moveCode(975,300,975,400,"down");

//S, 1020,1070 x 300 400
   moveCode(1070,300,1020,300,"left");
   moveCode(1020,300,1020,350,"down");
    moveCode(1020,350,1070,350,"right");
    moveCode(1070,350,1070,400,"down");
    moveCode(1070,400,1020,400,"left");

//H
   moveCode(1100,350,1100,300,"up");
   moveCode(1100,350,1100,400,"down");
   moveCode(1100,350,1150,350,"right");
   moveCode(1150,350,1150,300,"up");
   moveCode(1150,350,1150,400,"down");

//P
   moveCode(420,600,420,500,"up");
   moveCode(420,500,470,500,"right");
   moveCode(470,500,470,550,"down");
   moveCode(470,550,420,550,"left");

//R
    moveCode(500,600,500,500,"up");
   moveCode(500,500,550,500,"right");
   moveCode(550,500,550,550,"down");
   moveCode(550,550,500,550,"left");
   moveCode(500,550,550,600,"bottomright");

//A
     moveCode(580,600,580,500,"up");
     moveCode(580,500,630,500,"right");
     moveCode(630,500,630,600,"down");
    moveCode(630,550,580,550,"left");

//T
    moveCode(660,500,720,500,"right");
    moveCode(690,500,690,600,"down");

//Y 660+80 = 740, + 50 = 790 750,800
    moveCode(800,550,800,500,"up");
    moveCode(800,550,760,500,"upleft");
    moveCode(760,600,800,550,"upright");

//U
    moveCode(840,500,840,600,"down");
    moveCode(840,600,890,600,"right");
    moveCode(890,600,890,500,"up");

//S
    moveCode(970,500,920,500,"left");
    moveCode(920,500,920,550,"down");
    moveCode(920,550,970,550,"right");
    moveCode(970,550,970,600,"down");
    moveCode(970,600,920,600,"left");

//H
    moveCode(1000,550,1000,500,"up");
    moveCode(1000,550,1000,600,"down");
    moveCode(1000,550,1050,550,"right");
    moveCode(1050,550,1050,500,"up");
    moveCode(1050,550,1050,600,"down");

    //loading row
    moveCode(10,700,1280,700,"right");
}
