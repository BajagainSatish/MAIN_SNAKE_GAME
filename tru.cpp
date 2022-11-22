#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#define height 700
#define width 1280

int i, X[100], Y[100],M[0],N[0], rx, ry, gm, gd, l, d = 2, s = 16, score, hscore;
FILE *fptr;

void boundary();
void snakeinit();
void food();
void highScore();
void startGame();
void homeScreen();
void gameOver();
void text(int, int, int, char *);
void nice_intro();
void moveCode(int startX, int startY, int endX, int endY, char direction[]);

int main()
{
	fptr = fopen("highscore.txt", "r");
	if (fptr == NULL)
	{
		fptr = fopen("highscore.txt", "w");
		fprintf(fptr, "%d%d", 0, 0);
		fclose(fptr);
	}
	initwindow(width, height);
	nice_intro();
	homeScreen();
	closegraph();
	getch();
	return 0;
}
void homeScreen()
{
	int i, j, margin_x = 20, margin_y = 20, borderColor = 10, fillColor = 10, size = 50;
	score = 0;

	setfillstyle(SOLID_FILL, fillColor);

	// horizontal boxes
	for (i = margin_x, j = margin_y; i < width - 50; i += size)
	{
		setcolor(borderColor);
		rectangle(i, j, i + (size - 10), j + (size - 10));
		floodfill(i + 1, j + 1, borderColor);

		// i = current pos + (size * no of boxes) this is the last box in the horizontal row
		if (i == margin_x + (size * 24))
		{

			j = j + size;

			// boxes in the last column
			for (int k = 0; k < 3; k++)
			{

				setcolor(borderColor);
				rectangle(i, j, i + (size - 10), j + (size - 10));
				floodfill(i + 1, j + 1, borderColor);
				j += size;
			}

			// last crosshair box
			rectangle(i + 14, j, i + (size - 10) - 13, j + (size - 10) - 28);
			floodfill(i + 15, j + 1, borderColor);

			rectangle(i, j + (size - 10) - 27, i + 13, j + (size - 10) - 14);
			floodfill(i + 2, j + 14, borderColor);

			rectangle(i + 28, j + (size - 10) - 27, i + (size - 10), j + (size - 10) - 14);
			floodfill(i + 29, j + 14, borderColor);

			rectangle(i + 14, j + (size - 12) - 11, i + (size - 10) - 13, j + (size - 12));
			floodfill(i + 15, j + 30, borderColor);
		}
	}

	// vertical boxes in home screen
	for (i = margin_x, j = margin_y + size; j <= height - 50; j += size)
	{
		rectangle(i, j, i + (size - 10), j + (size - 10));
		floodfill(i + 1, j + 1, borderColor);
		// j = current pos + (size * no of boxes) this is the last box in the vertical column

		if (j == (margin_y + size) + (size * 11))
		{
			i += size;
			rectangle(i, j, i + (size - 10), j + (size - 10));
			floodfill(i + 1, j + 1, borderColor);
		}
	}
	char ch;
	while (1)
	{

		setcolor(9);
		// writes text in main screen
		text(10, (width / 2), 350, (char *)"Snake Game");
		text(5, (width / 2), 450, (char *)"Press Space To Play");

		// checks for keyboard entry
		// 32 -- space
		// 13 -- enter
		// 27 -- esc
		ch = getch();
		if (int(ch) == 32)
		{
			printf("Space pressed");
			cleardevice();
			startGame();
		}
	}
}

void startGame()
{

	score = 0;
	cleardevice();
	Sleep(300);

	// detectgraph(&gd,&gm);
	// initgraph(&gd,&gm,NULL);

	// set boundary
	boundary();
	// fill initial snake body
	snakeinit();
	// food at random location
	food();
	delay(1000);

	while (1)
	{
		// updating the snake
		setfillstyle(1, 0); // trace entire path of snake
		bar(X[l - 1] - s / 2, Y[l - 1] - s / 2, X[l - 1] + s / 2, Y[l - 1] + s / 2);
		for (i = l - 1; i > 0; i--)
		{
			X[i] = X[i - 1];
			Y[i] = Y[i - 1];
		}

		// updating the head
		if (d == 0)
			X[0] = X[0] - s;
		else if (d == 1)
			Y[0] = Y[0] - s;
		else if (d == 2)
			// we initialized d=2, so snake moves right by default
			X[0] = X[0] + s;
		else if (d == 3)
			Y[0] = Y[0] + s;

		// terminating condition
		if (getpixel(X[0], Y[0]) == 5 || getpixel(X[0], Y[0]) == 6)
		{
			gameOver();
		}

		// updating direction
		if ((GetAsyncKeyState(VK_RIGHT)) && (d != 0))
			d = 2;
		else if ((GetAsyncKeyState(VK_UP)) && (d != 3))
			d = 1;
		else if ((GetAsyncKeyState(VK_LEFT)) && (d != 2))
			d = 0;
		else if ((GetAsyncKeyState(VK_DOWN)) && (d != 1))
			d = 3;

		// food taken
		if (getpixel(X[0], Y[0]) == 2)
		{
			food();
			l = l + 1;
			score++;
		}

		// displaying the snake
		setfillstyle(1, 5);
		for (i = 0; i < l; i++)
			bar(X[i] - s / 2, Y[i] - s / 2, X[i] + s / 2, Y[i] + s / 2);
		delay(50);
	}
}

void gameOver()
{
	char ch;
	char str[3];
	char hstr[5];
	char scr[10] = "Score: ";
	char hscr[20] = "High Score: ";

	cleardevice();

	fscanf(fptr, "%d", &hscore);
	printf("\n\n This feom gameOver: %d \n\n", hscore);

	sprintf(str, "%d", score);
	sprintf(hstr, "%d", hscore);

	strcat(scr, str);
	strcat(hscr, hstr);

	setcolor(RED);
	/// Writes Text in game over screen
	text(10, (width / 2), 150, (char *)"GAME");
	text(10, (width / 2), 250, (char *)"OVER");
	text(5, (width / 2), 400, (char *)scr);
	text(5, (width / 2), 350, (char *)hscr);

	if (score > hscore)
	{
		text(3, (width / 2), 500, (char *)"You have beaten the highscore !!!!");
		text(3, (width / 2) - 150, 600, (char *)"Press Space to play again.");
		text(3, (width / 2) + 200, 600, (char *)"Press Esc to quit the game.");
	}
	else
	{
		text(3, (width / 2) - 150, 550, (char *)"Press Space to play again.");
		text(3, (width / 2) + 200, 550, (char *)"Press Esc to quit the game.");
	}
	highScore();

	while (1)
	{
		ch = getch();
		if (int(ch) == 32)
		{
			printf("Enter pressed");
			startGame();
		}
		else if (int(ch) == 27)
		{
			exit(0);
		}
		// if (kbhit())
		// {
		// }
	}
}

void boundary()
{

	setfillstyle(4, 6);

	bar(8, 8, 1270, 24);
	bar(8, 8, 24, 684);
	bar(8, 668, 1270, 684);
	bar(1258, 8, 1274, 684);
}

void snakeinit()
{
	setfillstyle(1, 5); // display snake when immediately game opens
	X[0] = s * (1270 / (2 * s));
	Y[0] = s * (680 / (2 * s));
	bar(X[0] - s / 2, Y[0] - s / 2, X[0] + s / 2, Y[0] + s / 2);
	l = 5;
	for (i = 1; i < l; i++)
	{
		X[i] = X[0] - (i * s);
		Y[i] = Y[0];
		bar(X[i] - s / 2, Y[i] - s / 2, X[i] + s / 2, Y[i] + s / 2);
	}
}

void food()
{
	srand(time(0));
	rx = s;
	ry = s;
	setfillstyle(1, 2);
	while (getpixel(rx, ry) != 0)
	{
		rx = s * (1 + rand() % (1268 / s - 1));
		ry = s * (1 + rand() % (678 / s - 1));
	}
	bar(rx - s / 2, ry - s / 2, rx + s / 2, ry + s / 2);
}

void highScore()
{
	char fnum[5];

	fptr = fopen("highscore.txt", "r");
	// fscanf(fptr, "%d", &hscore);
	fgets(fnum, 5, fptr);
	hscore = atoi(fnum);
	fclose(fptr);
	if (score > hscore)
	{
		hscore = score;
		fptr = fopen("highscore.txt", "w");

		fprintf(fptr, "%d", hscore);
		fclose(fptr);
		printf("Highscore: %d", hscore);
	}
}

void text(int fontSize, int x_pos, int y_pos, char *str)
{
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, fontSize);
	outtextxy(x_pos, y_pos, str);
}

void moveCode(int startX, int startY, int endX, int endY, char direction[])
{

	setfillstyle(7, 3); // display snake when immediately game opens
	X[0] = s * (startX / s);
	Y[0] = s * (startY / s);
	bar(X[0] - s / 2, Y[0] - s / 2, X[0] + s / 2, Y[0] + s / 2);

	M[0] = s * (endX / s);
	N[0] = s * (endY / s);
	setfillstyle(4, 3);
	bar(M[0] - s / 2, N[0] - s / 2, M[0] + s / 2, N[0] + s / 2);

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
		if (direction == "up")
		{
			Y[0] = Y[0] - s;
		}
		else if (direction == "down")
		{
			Y[0] = Y[0] + s;
		}
		else if (direction == "right")
		{
			X[0] = X[0] + s;
		}
		else if (direction == "left")
		{
			X[0] = X[0] - s;
		}
		else if (direction == "bottomright")
		{
			X[0] = X[0] + s;
			Y[0] = Y[0] + s;
		}
		else if (direction == "upright")
		{
			X[0] = X[0] + s;
			Y[0] = Y[0] - s;
		}
		else if (direction == "upleft")
		{
			X[0] = X[0] - s;
			Y[0] = Y[0] - s;
		}

		if (getpixel(X[0], Y[0]) == 3)
		{
			return;
		}
	}
}

void nice_intro()
{

	// P
	moveCode(100, 200, 100, 100, "up");
	moveCode(100, 100, 150, 100, "right");
	moveCode(150, 100, 150, 150, "down");
	moveCode(150, 150, 100, 150, "left");

	// R
	moveCode(180, 200, 180, 100, "up");
	moveCode(180, 100, 230, 100, "right");
	moveCode(230, 100, 230, 150, "down");
	moveCode(230, 150, 180, 150, "left");
	moveCode(180, 150, 230, 200, "bottomright");

	// E
	moveCode(260, 200, 260, 100, "up");
	moveCode(260, 100, 310, 100, "right");
	moveCode(260, 150, 310, 150, "right");
	moveCode(260, 200, 310, 200, "right");

	// P
	moveCode(340, 200, 340, 100, "up");
	moveCode(340, 100, 390, 100, "right");
	moveCode(390, 100, 390, 150, "down");
	moveCode(390, 150, 340, 150, "left");

	// A
	moveCode(420, 200, 420, 100, "up");
	moveCode(420, 100, 470, 100, "right");
	moveCode(470, 100, 470, 200, "down");
	moveCode(420, 150, 470, 150, "right");

	// R
	moveCode(500, 200, 500, 100, "up");
	moveCode(500, 100, 550, 100, "right");
	moveCode(550, 100, 550, 150, "down");
	moveCode(550, 150, 500, 150, "left");
	moveCode(500, 150, 550, 200, "bottomright");

	// E
	moveCode(580, 200, 580, 100, "up");
	moveCode(580, 100, 630, 100, "right");
	moveCode(580, 150, 630, 150, "right");
	moveCode(580, 200, 630, 200, "right");

	// D
	moveCode(660, 200, 660, 100, "up");
	moveCode(660, 100, 710, 100, "right");
	moveCode(710, 100, 710, 200, "down");
	moveCode(710, 200, 660, 200, "left");

	// B
	moveCode(840, 200, 840, 100, "up");
	moveCode(840, 100, 890, 100, "right");
	moveCode(890, 100, 890, 200, "down");
	moveCode(890, 200, 840, 200, "left");
	moveCode(840, 150, 890, 150, "right");

	// Y
	moveCode(970, 150, 970, 100, "up");
	moveCode(970, 150, 920, 100, "upleft");
	moveCode(920, 200, 970, 150, "upright");

	//:
	setfillstyle(1, 2);
	bar(1050, 120, 1070, 140);
	bar(1050, 160, 1070, 180);
	// moveCode(1050,170,1050,160,"up");
	// moveCode(1050,140,1050,130,"up");

	// R
	moveCode(180, 400, 180, 300, "up");
	moveCode(180, 300, 230, 300, "right");
	moveCode(230, 300, 230, 350, "down");
	moveCode(230, 350, 160, 350, "left");
	moveCode(160, 350, 230, 400, "bottomright");

	// O
	moveCode(260, 400, 260, 300, "up");
	moveCode(260, 300, 310, 300, "right");
	moveCode(310, 300, 310, 400, "down");
	moveCode(310, 400, 260, 400, "left");

	// J
	moveCode(340, 300, 390, 300, "right");
	moveCode(375, 300, 375, 400, "down");
	moveCode(375, 400, 340, 400, "left");
	moveCode(340, 400, 340, 350, "up");

	// A
	moveCode(420, 400, 420, 300, "up");
	moveCode(420, 300, 470, 300, "right");
	moveCode(470, 300, 470, 400, "down");
	moveCode(420, 350, 470, 350, "right");

	// L
	moveCode(500, 300, 500, 400, "down");
	moveCode(500, 400, 550, 400, "right");

	// S, 710,760 x 300 400
	moveCode(760, 300, 710, 300, "left");
	moveCode(710, 300, 710, 350, "down");
	moveCode(710, 350, 760, 350, "right");
	moveCode(760, 350, 760, 400, "down");
	moveCode(760, 400, 710, 400, "left");

	// A, 790,840
	moveCode(790, 400, 790, 300, "up");
	moveCode(790, 300, 840, 300, "right");
	moveCode(840, 300, 840, 400, "down");
	moveCode(840, 350, 790, 350, "left");

	// T
	moveCode(870, 300, 930, 300, "right");
	moveCode(900, 300, 900, 400, "down");

	// I, 950, 1000
	moveCode(975, 300, 975, 400, "down");

	// S, 1020,1070 x 300 400
	moveCode(1070, 300, 1020, 300, "left");
	moveCode(1020, 300, 1020, 350, "down");
	moveCode(1020, 350, 1070, 350, "right");
	moveCode(1070, 350, 1070, 400, "down");
	moveCode(1070, 400, 1020, 400, "left");

	// H
	moveCode(1100, 350, 1100, 300, "up");
	moveCode(1100, 350, 1100, 400, "down");
	moveCode(1100, 350, 1150, 350, "right");
	moveCode(1150, 350, 1150, 300, "up");
	moveCode(1150, 350, 1150, 400, "down");

	// P
	moveCode(420, 600, 420, 500, "up");
	moveCode(420, 500, 470, 500, "right");
	moveCode(470, 500, 470, 550, "down");
	moveCode(470, 550, 420, 550, "left");

	// R
	moveCode(500, 600, 500, 500, "up");
	moveCode(500, 500, 550, 500, "right");
	moveCode(550, 500, 550, 550, "down");
	moveCode(550, 550, 500, 550, "left");
	moveCode(500, 550, 550, 600, "bottomright");

	// A
	moveCode(580, 600, 580, 500, "up");
	moveCode(580, 500, 630, 500, "right");
	moveCode(630, 500, 630, 600, "down");
	moveCode(630, 550, 580, 550, "left");

	// T
	moveCode(660, 500, 720, 500, "right");
	moveCode(690, 500, 690, 600, "down");

	// Y 660+80 = 740, + 50 = 790 750,800
	moveCode(800, 550, 800, 500, "up");
	moveCode(800, 550, 760, 500, "upleft");
	moveCode(760, 600, 800, 550, "upright");

	// U
	moveCode(840, 500, 840, 600, "down");
	moveCode(840, 600, 890, 600, "right");
	moveCode(890, 600, 890, 500, "up");

	// S
	moveCode(970, 500, 920, 500, "left");
	moveCode(920, 500, 920, 550, "down");
	moveCode(920, 550, 970, 550, "right");
	moveCode(970, 550, 970, 600, "down");
	moveCode(970, 600, 920, 600, "left");

	// H
	moveCode(1000, 550, 1000, 500, "up");
	moveCode(1000, 550, 1000, 600, "down");
	moveCode(1000, 550, 1050, 550, "right");
	moveCode(1050, 550, 1050, 500, "up");
	moveCode(1050, 550, 1050, 600, "down");

	// loading row
	moveCode(10, 700, 1280, 700, "right");

	homeScreen();
}

