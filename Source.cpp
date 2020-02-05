#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TXLib.h"
#include <math.h>
#include <windows.h>

int H, W;
char A[100][100] = { NULL };
char C[100][100] = { NULL };

int main()
{
	int H, W, pok, k = 0, j, i, bak = 0, sch = 0, f = 0, x, y;
	char znak;
	const char* c = NULL;
	char c1[10] = { 0 };
	char c2[10] = { 0 };
	char c3 = 0;
	c = txInputBox(" Welcome to the game!\nRecommended  field dimension is 30*30 or 40*40\nThe maximum dimension is 75*115", "Life", "Enter the dimensions of the field: height, width");
	for (i = 0; c[i] != ','; i++)  c1[i] = c[i];
	j = i + 1;
	for (i = 0; j < strlen(c); i++) {
		c2[i] = c[j]; j++;
	}
	W = atoi(c2);
	H = atoi(c1);
	txCreateWindow(W * 10 + 200, H * 10, LEFT_ALT_PRESSED);
	txSetColor(TX_WHITE, 1);
	for (i = 0; i < W; i++) txLine(10 * i + 200, 0, 10 * i + 200, H * 10);
	for (i = 1; i < H; i++) txLine(200, 10 * i, 10 * W + 200, 10 * i);
	txSetFillColor(TX_PINK);
	do { //ввод бактерий
		txSelectFont("Arial", 18, 6, 10, 0, 0, 0, 0);
		printf("Want to introduce\nyour bacteria?\n(+ - yes, - - no)");


		znak = getchar();
		if (znak == '+')
		{
			while (!(txMouseButtons() & 2))
			{
				txSleep(50);
				if (txMouseButtons() & 1) {
					x = txMouseX();
					y = txMouseY();
					if ((x > 200) && ((x % 10) != 0) && ((y % 10) != 0) && (x < (W * 10 + 201)) && (y>0) && (y < H * 10)) {
						if (A[(int)(y / 10)][(int)((x - 201) / 10)] == '+') {
							A[(int)(y / 10)][(int)((x - 201) / 10)] = '-';
							txSetFillColor(TX_BLACK);
							txFloodFill(x, y);
						}
						else {
							A[(int)(y / 10)][(int)((x - 201) / 10)] = '+';
							txSetFillColor(TX_PINK);
							txFloodFill(x, y);
						}
					}
					else i--; txSleep(0);


				}
				txSleep(0);


			}
			for (f = 0; f < 300; f++) {

				if (sch == 0)
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (A[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (A[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (A[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (A[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (A[i][j + 1] == '+' && (j + 1) < W) k++;
							if (A[i + 1][j] == '+' && (i + 1) < H) k++;
							if (A[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (A[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { C[i][j] = '-'; k = 0; }
							else if (k < 3 && A[i][j] == '+') { C[i][j] = '+'; k = 0; }
							else if (k == 3) { C[i][j] = '+'; k = 0; }
							else { C[i][j] = '-'; k = 0; }
						}
					sch++;
				}
				else
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (C[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (C[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (C[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (C[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (C[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (C[i][j + 1] == '+' && (j + 1) < W) k++;
							if (C[i + 1][j] == '+' && (i + 1) < H) k++;
							if (C[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (C[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { A[i][j] = '-'; k = 0; }
							else if (k < 3 && C[i][j] == '+') { A[i][j] = '+'; k = 0; }
							else if (k == 3) { A[i][j] = '+'; k = 0; }
							else { A[i][j] = '-'; k = 0; }
						}
					sch--;
				}
			}


		}
		else if (znak == '-');
		else printf("Invalid symbol!\n");
	} while (znak != '+' && znak != '-');

	//представление
	//-------------------------------------------------------------------------------------
	while (getchar() != '0')
	{
		printf("What do you want?\na-Glider\nb-random\nc-Tagalong\nd-Acorn\n0-exit\n");
		c3 = getchar();
		if ((c3 != 'a') && (c3 != 'b') && (c3 != '0') && (c3 != 'd') && (c3 != 'c'))
		{
			printf("error");
			return 0;
		}
		if (c3 == 'b')
		{
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					if ((0 + rand() % (21)) % 3 == 0) A[i][j] = '+';
					else A[i][j] = '-';
					for (f = 0; f < 100; f++) {

						if (sch == 0)
						{
							txSetFillColor(TX_BLACK);
							for (i = 0; i < H; i++)
								for (j = 0; j < W; j++)
									txFloodFill(201 + j * 10, i * 10 + 1);
							txSetFillColor(TX_PINK);
							for (i = 0; i < H; i++)
								for (j = 0; j < W; j++)
								{
									if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
								}
							txSleep(400);
							for (i = 0; i < H; i++) //смена поколений
								for (j = 0; j < W; j++)
								{
									if (A[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
									if (A[i][j - 1] == '+' && (j - 1) >= 0) k++;
									if (A[i - 1][j] == '+' && (i - 1) >= 0) k++;
									if (A[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
									if (A[i][j + 1] == '+' && (j + 1) < W) k++;
									if (A[i + 1][j] == '+' && (i + 1) < H) k++;
									if (A[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
									if (A[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
									if (k < 2) { C[i][j] = '-'; k = 0; }
									else if (k < 3 && A[i][j] == '+') { C[i][j] = '+'; k = 0; }
									else if (k == 3) { C[i][j] = '+'; k = 0; }
									else { C[i][j] = '-'; k = 0; }
								}
							sch++;
						}
						else
						{
							txSetFillColor(TX_BLACK);
							for (i = 0; i < H; i++)
								for (j = 0; j < W; j++)
									txFloodFill(201 + j * 10, i * 10 + 1);
							txSetFillColor(TX_PINK);
							for (i = 0; i < H; i++)
								for (j = 0; j < W; j++)
								{
									if (C[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
								}
							txSleep(400);
							for (i = 0; i < H; i++) //смена поколений
								for (j = 0; j < W; j++)
								{
									if (C[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
									if (C[i][j - 1] == '+' && (j - 1) >= 0) k++;
									if (C[i - 1][j] == '+' && (i - 1) >= 0) k++;
									if (C[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
									if (C[i][j + 1] == '+' && (j + 1) < W) k++;
									if (C[i + 1][j] == '+' && (i + 1) < H) k++;
									if (C[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
									if (C[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
									if (k < 2) { A[i][j] = '-'; k = 0; }
									else if (k < 3 && C[i][j] == '+') { A[i][j] = '+'; k = 0; }
									else if (k == 3) { A[i][j] = '+'; k = 0; }
									else { A[i][j] = '-'; k = 0; }
								}
							sch--;
						}
					}

		}
		if (c3 == '0') break;
		if (c3 == 'c') {
			txSetFillColor(TX_BLACK);
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					txFloodFill(201 + j * 10, i * 10 + 1);
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					A[i][j] = '-';
			while (!(txMouseButtons() & 2))
			{
				if (txMouseButtons() & 1) {
					txSleep(50);
					x = txMouseX();
					y = txMouseY();
					if ((x >(340)) && ((x % 10) != 0) && ((y % 10) != 0) && (x < (W * 10 + 60)) && (y > 100) && (y < (H * 10 - 100)))
					{
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) - 12] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) - 12] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) - 12] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 11] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) - 11] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) - 10] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) - 9] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) - 6] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) - 12] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) - 12] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) - 12] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 11] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) - 11] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) - 10] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) - 9] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 6] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 5] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 4] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 3] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) - 3] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 4] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 5] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) - 6] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10)] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10)] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10)] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) - 6][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) - 7][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 2] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 5] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 11] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 5] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 11] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 12] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 11] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 12] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) - 5][(int)((x - 201) / 10) + 7] = '+';
						A[(int)(y / 10) - 7][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) - 7][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) - 7][(int)((x - 201) / 10) + 7] = '+';
						A[(int)(y / 10) - 8][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) - 8][(int)((x - 201) / 10) + 7] = '+';
						A[(int)(y / 10) - 8][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) - 8][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10) - 9][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10)] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10)] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) + 6][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) + 7][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 2] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 5] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 11] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 5] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 11] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) + 12] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 10] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 11] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 12] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) + 5][(int)((x - 201) / 10) + 7] = '+';
						A[(int)(y / 10) + 7][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) + 7][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) + 7][(int)((x - 201) / 10) + 7] = '+';
						A[(int)(y / 10) + 8][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) + 8][(int)((x - 201) / 10) + 7] = '+';
						A[(int)(y / 10) + 8][(int)((x - 201) / 10) + 8] = '+';
						A[(int)(y / 10) + 8][(int)((x - 201) / 10) + 9] = '+';
						A[(int)(y / 10) + 9][(int)((x - 201) / 10) + 9] = '+';
						txSetFillColor(TX_PINK);
						for (i = 0; i < H; i++)
							for (j = 0; j < W; j++)
							{
								if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
							}
					}
					else i--; txSleep(0);
				}
				txSleep(0);
			}
			sch = 0;
			for (f = 0; f < 500; f++) {

				if (sch == 0)
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (A[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (A[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (A[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (A[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (A[i][j + 1] == '+' && (j + 1) < W) k++;
							if (A[i + 1][j] == '+' && (i + 1) < H) k++;
							if (A[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (A[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { C[i][j] = '-'; k = 0; }
							else if (k < 3 && A[i][j] == '+') { C[i][j] = '+'; k = 0; }
							else if (k == 3) { C[i][j] = '+'; k = 0; }
							else { C[i][j] = '-'; k = 0; }
						}
					sch++;
				}
				else
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (C[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (C[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (C[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (C[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (C[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (C[i][j + 1] == '+' && (j + 1) < W) k++;
							if (C[i + 1][j] == '+' && (i + 1) < H) k++;
							if (C[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (C[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { A[i][j] = '-'; k = 0; }
							else if (k < 3 && C[i][j] == '+') { A[i][j] = '+'; k = 0; }
							else if (k == 3) { A[i][j] = '+'; k = 0; }
							else { A[i][j] = '-'; k = 0; }
						}
					sch--;
				}
			}

		}
		if (c3 == 'd') {
			txSetFillColor(TX_BLACK);
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					txFloodFill(201 + j * 10, i * 10 + 1);
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					A[i][j] = '-';
			while (!(txMouseButtons() & 2))
			{
				if (txMouseButtons() & 1) {
					txSleep(50);
					x = txMouseX();
					y = txMouseY();
					if ((x >(240)) && ((x % 10) != 0) && ((y % 10) != 0) && (x < (W * 10 + 160)) && (y > 20) && (y < (H * 10 - 20)))
					{
						A[(int)(y / 10)][(int)((x - 201) / 10)] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 3] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) + 1] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) + 2] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) + 3] = '+';
						txSetFillColor(TX_PINK);
						for (i = 0; i < H; i++)
							for (j = 0; j < W; j++)
							{
								if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
							}
					}
					else i--; txSleep(0);
				}
				txSleep(0);
			}
			sch = 0;
			for (f = 0; f < 500; f++) {

				if (sch == 0)
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (A[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (A[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (A[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (A[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (A[i][j + 1] == '+' && (j + 1) < W) k++;
							if (A[i + 1][j] == '+' && (i + 1) < H) k++;
							if (A[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (A[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { C[i][j] = '-'; k = 0; }
							else if (k < 3 && A[i][j] == '+') { C[i][j] = '+'; k = 0; }
							else if (k == 3) { C[i][j] = '+'; k = 0; }
							else { C[i][j] = '-'; k = 0; }
						}
					sch++;
				}
				else
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (C[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (C[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (C[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (C[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (C[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (C[i][j + 1] == '+' && (j + 1) < W) k++;
							if (C[i + 1][j] == '+' && (i + 1) < H) k++;
							if (C[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (C[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { A[i][j] = '-'; k = 0; }
							else if (k < 3 && C[i][j] == '+') { A[i][j] = '+'; k = 0; }
							else if (k == 3) { A[i][j] = '+'; k = 0; }
							else { A[i][j] = '-'; k = 0; }
						}
					sch--;
				}
			}

		}
		if (c3 == 'a') {
			txSetFillColor(TX_BLACK);
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					txFloodFill(201 + j * 10, i * 10 + 1);
			for (i = 0; i < H; i++)
				for (j = 0; j < W; j++)
					A[i][j] = '-';
			while (!(txMouseButtons() & 2))
			{
				if (txMouseButtons() & 1) {
					txSleep(50);
					x = txMouseX();
					y = txMouseY();
					if ((x >(400)) && ((x % 10) != 0) && ((y % 10) != 0) && (x < (W * 10 + 10)) && (y > 70) && (y < (H * 10 - 70)))
					{
						A[(int)(y / 10)][(int)((x - 201) / 10) - 18] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) - 17] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 18] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 17] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 8] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) - 7] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) - 7] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 6] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) - 5] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) - 6] = '+';
						A[(int)(y / 10) + 4][(int)((x - 201) / 10) - 5] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 4] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) - 3] = '+';
						A[(int)(y / 10) + 3][(int)((x - 201) / 10) - 3] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) - 2] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) - 1] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) + 2] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) + 2] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 2] = '+';
						A[(int)(y / 10)][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 3] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) + 4] = '+';
						A[(int)(y / 10) - 3][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) - 4][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) + 1][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) + 2][(int)((x - 201) / 10) + 6] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) + 16] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 16] = '+';
						A[(int)(y / 10) - 1][(int)((x - 201) / 10) + 17] = '+';
						A[(int)(y / 10) - 2][(int)((x - 201) / 10) + 17] = '+';
						txSetFillColor(TX_PINK);
						for (i = 0; i < H; i++)
							for (j = 0; j < W; j++)
							{
								if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
							}
					}
					else i--; txSleep(0);
				}
				txSleep(0);
			}
			sch = 0;
			for (f = 0; f < 500; f++) {

				if (sch == 0)
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (A[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (A[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (A[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (A[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (A[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (A[i][j + 1] == '+' && (j + 1) < W) k++;
							if (A[i + 1][j] == '+' && (i + 1) < H) k++;
							if (A[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (A[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { C[i][j] = '-'; k = 0; }
							else if (k < 3 && A[i][j] == '+') { C[i][j] = '+'; k = 0; }
							else if (k == 3) { C[i][j] = '+'; k = 0; }
							else { C[i][j] = '-'; k = 0; }
						}
					sch++;
				}
				else
				{
					txSetFillColor(TX_BLACK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
							txFloodFill(201 + j * 10, i * 10 + 1);
					txSetFillColor(TX_PINK);
					for (i = 0; i < H; i++)
						for (j = 0; j < W; j++)
						{
							if (C[i][j] == '+') txFloodFill(201 + j * 10, i * 10 + 1);
						}
					txSleep(400);
					for (i = 0; i < H; i++) //смена поколений
						for (j = 0; j < W; j++)
						{
							if (C[i - 1][j - 1] == '+' && (i - 1) >= 0 && (j - 1) >= 0) k++;
							if (C[i][j - 1] == '+' && (j - 1) >= 0) k++;
							if (C[i - 1][j] == '+' && (i - 1) >= 0) k++;
							if (C[i + 1][j + 1] == '+' && (i + 1) < H && (j + 1) < W) k++;
							if (C[i][j + 1] == '+' && (j + 1) < W) k++;
							if (C[i + 1][j] == '+' && (i + 1) < H) k++;
							if (C[i - 1][j + 1] == '+' && (i - 1) >= 0 && (j + 1) < W) k++;
							if (C[i + 1][j - 1] == '+' && (i + 1) < H && (j - 1) >= 0) k++;
							if (k < 2) { A[i][j] = '-'; k = 0; }
							else if (k < 3 && C[i][j] == '+') { A[i][j] = '+'; k = 0; }
							else if (k == 3) { A[i][j] = '+'; k = 0; }
							else { A[i][j] = '-'; k = 0; }
						}
					sch--;
				}
			}

		}
		system("cls");
	}
	return 0;
}