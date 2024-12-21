#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#pragma warning(disable : 4996)

int Menu1(int choice, bool ispole)
{
	system("cls");
	printf("Лабиринт\n\n");
	if (ispole)
	{
		printf("%s%s\n", (choice == 1) ? "1)Создать/редактировать лабиринт <== " : "1)Создать/редактировать лабиринт  ", "");
	}
	else
	{
		printf("%s%s\n", (choice == 1) ? "1)Создать лабиринт <== " : "1)Создать лабиринт  ", "");
	}
	printf("%s\%s\n", (choice == 2) ? "2)Найти решение <== " : "2)Найти решение  ", "");
	printf("%s%s\n", (choice == 3) ? "3)Выход <== " : "3)Выход  ", "");
}

int Menu2(int choice, int len, int high)
{
	system("cls");
	printf("%s длина: %d\n", (choice == 1) ? "1)Ввести длину <== " : "1)Ввести длину  ", len);
	printf("%s ширина: %d\n", (choice == 2) ? "2)Ввести ширину <== " : "2)Ввести ширину  ", high);
	printf("%s%s\n", (choice == 3) ? "3)Создать лабиринт <== " : "3)Создать лабиринт  ", "");
}

int PoleIgr(int len, int high, int posY, int posX, char pole[][21])
{
	for (int i = 0; i < high; i++) {
		for (int j = 0; j < len; j++) {
			if (i == posY && j == posX) {
				pole[i][j] = '+';
				printf("%c", pole[i][j]);
			}
			else {
				printf("%c", pole[i][j]);
			}
		}
		printf("\n");
	}
}

int PoleSymb(int len, int high, char polesymb[][21])
{
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < len; j++)
		{
			printf("%c", polesymb[i][j]);
		}
		printf("\n");
	}
}

int setLenght() {
	int r;
	while (1) {
		system("cls");
		printf("Введите длину поля (от 3 до 20): ");

		if (scanf("%d", &r) != 1) {
			printf("Неверный ввод, введите только цифры.\n");
			_getch();
			while (getchar() != '\n');
			continue;
		}

		if (r >= 3 && r <= 20) {
			printf("Введенная длина: %d\n", r);
			_getch();
			return r;
		}
		else {
			printf("Неверный формат длины, введите число от 3 до 20.\n");
			_getch();
		}
	}
}

//Ширина
int setHeight() {
	int r;
	while (1) {
		system("cls");
		printf("Введите ширину поля (от 3 до 20): ");

		if (scanf("%d", &r) != 1) {
			printf("Неверный ввод, введите только цифры.\n");
			_getch();
			while (getchar() != '\n');
			continue;
		}

		if (r >= 3 && r <= 20) {
			printf("Введенная ширина: %d\n", r);
			_getch();
			return r;
		}
		else {
			printf("Неверный формат ширины, введите число от 3 до 20.\n");
			_getch();
		}
	}
}

int rules()
{
	printf("Для установки / удаления стен нажмите w\n");
	printf("Для установки старта нажмите s\n");
	printf("Для установки конца нажмите e\n\n");
	printf("Для выхода и сохранения лабиринта нажмите q\n");
}

int Pole(int len, int high, char pole[][21], char polesymb[][21])
{
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (i == 1 && j == 1)
			{
				polesymb[i][j] = '.';
				pole[i][j] = '+';
				printf("%c", pole[i][j]);
			}
			else if (i == 0 || i == high - 1)
			{
				polesymb[i][j] = '#';
				pole[i][j] = polesymb[i][j];
				printf("%c", pole[i][j]);
			}

			else
			{
				if (j == 0 || j == len - 1)
				{
					polesymb[i][j] = '#';
					pole[i][j] = polesymb[i][j];
					printf("%c", pole[i][j]);
				}
				else
				{
					polesymb[i][j] = '.';
					pole[i][j] = polesymb[i][j];
					printf("%c", pole[i][j]);
				}
			}
		}
		printf("\n");
	}
}

int solve(int startY, int startX, int endY, int endX, char poleway[][21], int len, int high)
{
	if (startY == endY && startX == endX)
	{
		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < len; j++)
			{
				if (poleway[i][j] == '.' || poleway[i][j] == '1' || poleway[i][j] == '0')
				{
					poleway[i][j] = '2';
				}
			}
		}
	}
	else
	{
		poleway[startY][startX] = '1';
		if (poleway[startY - 1][startX] == '.' || poleway[startY - 1][startX] == 'e')
			solve(startY - 1, startX, endY, endX, poleway, len, high);
		if (poleway[startY][startX - 1] == '.' || poleway[startY][startX - 1] == 'e')
			solve(startY, startX - 1, endY, endX, poleway, len, high);
		if (poleway[startY + 1][startX] == '.' || poleway[startY + 1][startX] == 'e')
			solve(startY + 1, startX, endY, endX, poleway, len, high);
		if (poleway[startY][startX + 1] == '.' || poleway[startY][startX + 1] == 'e')
			solve(startY, startX + 1, endY, endX, poleway, len, high);
		if (poleway[startY][startX] == '#' || poleway[startY][startX] == '1'
			|| poleway[startY][startX] == '0' || poleway[startY][startX] == '2')
		{
			for (int i = 0; i < high; i++)
			{
				for (int j = 0; j < len; j++) {
					if (poleway[i][j] == '2')
					{
						poleway[startY][startX] = '*';
					}
					else if (poleway[i][j] == '0')
					{
						poleway[startY][startX] = '0';
					}
				}
			}
			return;
		}
		if (poleway[startY - 1][startX] == '.' || poleway[startY - 1][startX] == 'e')
			solve(startY - 1, startX, endY, endX, poleway, len, high);
		if (poleway[startY][startX - 1] == '.' || poleway[startY][startX - 1] == 'e')
			solve(startY, startX - 1, endY, endX, poleway, len, high);
		if (poleway[startY + 1][startX] == '.' || poleway[startY + 1][startX] == 'e')
			solve(startY + 1, startX, endY, endX, poleway, len, high);
		if (poleway[startY][startX + 1] == '.' || poleway[startY][startX + 1] == 'e')
			solve(startY, startX + 1, endY, endX, poleway, len, high);
		else
		{
			return;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");

	int currPos = 1;
	int choose2 = 1;
	int choose4 = 1;

	char pole_symb[20][21];
	char pole[20][21];
	char pole_way[20][21];

	int startY = -1;
	int startX = -1;
	int endY = -1;
	int endX = -1;
	int posY = 1;
	int posX = 1;

	int length = 0;
	int height = 0;

	bool ispole = false;

	while (true)
	{
		bool first = true;
		bool second = true;
		bool third = true;

		Menu1(currPos, ispole);

		int arr = _getch();
		if (arr >= '2' && arr <= '4')
		{
			currPos = arr - '1';
		}
		else if (arr == 224)
		{
			switch (_getch())
			{
			case 72:
				currPos = (currPos > 1) ? currPos - 1 : 3;
				break;
			case 80:
				currPos = (currPos < 3) ? currPos + 1 : 1;
				break;
			}
		}
		else if (arr == '\r')
		{
			switch (currPos)
			{
			case 1:
				if (ispole)
				{
					system("cls");
					printf("Создать новый лабиринт (1)\n");
					printf("Редактировать старый лабиринт (2)\n");

					while (first)
					{
						int choose3 = _getch();
						switch (choose3)
						{
						case 49:

							length = 0;
							height = 0;

							while (second)
							{
								Menu2(choose4, length, height);

								int press2 = _getch();
								if (press2 >= '2' && press2 <= '4')
								{
									choose4 = press2 - '1';
								}
								else if (press2 == 224)
								{
									switch (_getch())
									{
									case 72:
										choose4 = (choose4 > 1) ? choose4 - 1 : 3;
										break;
									case 80:
										choose4 = (choose4 < 3) ? choose4 + 1 : 1;
										break;
									}
								}

								else if (press2 == '\r')
								{
									switch (choose4)
									{
									case 1:
										length = setLenght();
										Menu2(choose3, length, height);
										break;
									case 2:
										height = setHeight();
										Menu2(choose3, length, height);
										break;
									case 3:
										posY = 1;
										posX = 1;
										system("cls");
										Pole(length, height, pole, pole_symb);
										rules();
										while (third)
										{
											int move = _getch();

											switch (move)
											{
											case 224:
												move = _getch();
												if (move == 72)
												{
													pole[posY][posX] = pole_symb[posY][posX];
													if (posY != 0) {
														posY -= 1;
													}
													else
													{
														posY = height - 1;
													}
													system("cls");
													PoleIgr(length, height, posY, posX, pole);
													rules();
												}
												if (move == 80)
												{
													pole[posY][posX] = pole_symb[posY][posX];
													if (posY != height - 1)
													{
														posY += 1;
													}
													else
													{
														posY = 0;
													}
													system("cls");
													PoleIgr(length, height, posY, posX, pole);
													rules();
												}

												if (move == 75)
												{
													pole[posY][posX] = pole_symb[posY][posX];
													if (posX != 0) {
														posX -= 1;
													}
													else
													{
														posX = length - 1;
													}
													system("cls");
													PoleIgr(length, height, posY, posX, pole);
													rules();
												}
												if (move == 77)
												{
													pole[posY][posX] = pole_symb[posY][posX];
													if (posX != length - 1)
													{
														posX += 1;
													}
													else
													{
														posX = 0;
													}
													system("cls");
													PoleIgr(length, height, posY, posX, pole);
													rules();
												}
												break;
											case 's':
												for (int i = 0; i < height; i++)
												{
													for (int j = 0; j < length; j++)
													{
														if (pole_symb[i][j] == 's')
														{
															if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
															{
																printf("Ошибка: Нельзя установить символ 's' на границе поля!\n");
															}
															else
															{
															
																pole_symb[i][j] = '.';
																pole[i][j] = pole_symb[i][j];
															}
														}
													}
												}

											
												if (posY == 0 || posY == height - 1 || posX == 0 || posX == length - 1)
												{
													printf("Ошибка: Нельзя установить символ 's' на границе поля!\n");
												}
												else
												{
													pole_symb[posY][posX] = 's'; 
													pole[posY][posX] = pole_symb[posY][posX]; 
												}

												system("cls");
												PoleSymb(length, height, pole_symb);
												rules();
												break;
											case 'e':
												for (int i = 0; i < height; i++)
												{
													for (int j = 0; j < length; j++)
													{
														if (pole_symb[i][j] == 'e')
														{
															if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
															{
																pole_symb[i][j] = '#'; 
																pole[i][j] = pole_symb[i][j];
															}
															else
															{
																pole_symb[i][j] = '.';
																pole[i][j] = pole_symb[i][j];
															}
														}
													}
												}

											
												if (posY == 0 || posY == height - 1 || posX == 0 || posX == length - 1)
												{
													pole_symb[posY][posX] = 'e';
													pole[posY][posX] = pole_symb[posY][posX]; 
												}
												else
												{
													printf("Ошибка: Символ 'e' можно установить только на границе поля!\n");
													_getch();
												}

												system("cls");
												PoleSymb(length, height, pole_symb);
												rules();
												break;
											case 'w':
												if (pole_symb[posY][posX] == '#')
												{
													if (posY != 0 && posY != height - 1 && posX != 0 && posX != length - 1)
													{
														pole_symb[posY][posX] = '.';
													}
												}
												else if (pole_symb[posY][posX] == '.' || pole_symb[posY][posX] == 's' || pole_symb[posY][posX] == 'e')
												{
													pole_symb[posY][posX] = '#';
												}
												system("cls");
												PoleSymb(length, height, pole_symb);
												rules();
												break;
											case 'q':
												first = false;
												second = false;
												third = false;
												printf("Лабиринт сохранён");
												_getch();
												Menu1(currPos, ispole);

												break;
											}
										}
										break;
									}
								}
							}
							break;
						case 50:
							system("cls");
							PoleIgr(length, height, posY, posX, pole);
							rules();
							while (third)
							{

								int move = _getch();

								switch (move)
								{
								case 224:
									move = _getch();
									if (move == 72)
									{
										pole[posY][posX] = pole_symb[posY][posX];
										if (posY != 0)
										{
											posY -= 1;
										}
										else {
											posY = height - 1;
										}
										system("cls");
										PoleIgr(length, height, posY, posX, pole);
										rules();
									}

									if (move == 80)
									{
										pole[posY][posX] = pole_symb[posY][posX];
										if (posY != height - 1)
										{
											posY += 1;
										}
										else
										{
											posY = 0;
										}
										system("cls");
										PoleIgr(length, height, posY, posX, pole);
										rules();
									}
									if (move == 75)
									{
										pole[posY][posX] = pole_symb[posY][posX];
										if (posX != 0)
										{
											posX -= 1;
										}
										else
										{
											posX = length - 1;
										}
										system("cls");
										PoleIgr(length, height, posY, posX, pole);
										rules();
									}
									if (move == 77)
									{
										pole[posY][posX] = pole_symb[posY][posX];
										if (posX != length - 1)
										{
											posX += 1;
										}
										else
										{
											posX = 0;
										}
										system("cls");
										PoleIgr(length, height, posY, posX, pole);
										rules();
									}
									break;
								case 's':
									for (int i = 0; i < height; i++)
									{
										for (int j = 0; j < length; j++)
										{
											if (pole_symb[i][j] == 's')
											{
						
												if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
												{
													printf("Ошибка: Нельзя установить символ 's' на границе поля!\n");
													_getch();
												}
												else
												{
													pole_symb[i][j] = '.';
													pole[i][j] = pole_symb[i][j];
												}
											}
										}
									}

									if (posY == 0 || posY == height - 1 || posX == 0 || posX == length - 1)
									{
										printf("Ошибка: Нельзя установить символ 's' на границе поля!\n");
										_getch();
									}
									else
									{
										pole_symb[posY][posX] = 's'; 
										pole[posY][posX] = pole_symb[posY][posX];
									}

									system("cls");
									PoleSymb(length, height, pole_symb);
									rules();
									break;
								case 'e':
									for (int i = 0; i < height; i++)
									{
										for (int j = 0; j < length; j++)
										{
											if (pole_symb[i][j] == 'e')
											{
												if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
												{
													pole_symb[i][j] = '#';
													pole[i][j] = pole_symb[i][j];
												}
												else
												{
													pole_symb[i][j] = '.';
													pole[i][j] = pole_symb[i][j];
												}
											}
										}
									}


									if (posY == 0 || posY == height - 1 || posX == 0 || posX == length - 1)
									{
										pole_symb[posY][posX] = 'e';
										pole[posY][posX] = pole_symb[posY][posX];
									}
									else
									{
										printf("Ошибка: Символ 'e' можно установить только на границе поля!\n");
										_getch();
									}

									system("cls");
									PoleSymb(length, height, pole_symb);
									rules();
									break;
								case 'w':
									if (pole_symb[posY][posX] == '#')
									{
										if (posY != 0 && posY != height - 1 && posX != 0 && posX != length - 1)
										{
											pole_symb[posY][posX] = '.';
										}
									}
									else if (pole_symb[posY][posX] == '.' || pole_symb[posY][posX] == 's' || pole_symb[posY][posX] == 'e')
									{
										pole_symb[posY][posX] = '#';
									}
									system("cls");
									PoleSymb(length, height, pole_symb);
									rules();
									break;
								case 'q':
									first = false;
									second = false;
									third = false;
									printf("Лабиринт сохранён");
									_getch();
									Menu1(currPos, ispole);

									break;
								}
							}
							break;
						}
					}
				}
				if (!ispole)
				{
					while (first)
					{
						Menu2(choose2, length, height);

						int press3 = _getch();
						if (press3 >= '2' && press3 <= '4')
						{
							choose2 = press3 - '1';
						}
						else if (press3 == 224)
						{
							switch (_getch())
							{
							case 72:
								choose2 = (choose2 > 1) ? choose2 - 1 : 3;
								break;
							case 80:
								choose2 = (choose2 < 3) ? choose2 + 1 : 1;
								break;
							}
						}

						else if (press3 == '\r')
						{
							switch (choose2)
							{
							case 1:
								length = setLenght();
								Menu2(choose2, length, height);
								break;
							case 2:
								height = setHeight();
								Menu2(choose2, length, height);
								break;
							case 3:
								if (length == 0 || height == 0)
								{
									system("cls");
									printf("Недостаточно данных для создания поля\n");
									_getch();
									break;
								}
								system("cls");
								Pole(length, height, pole, pole_symb);
								rules();
								while (third)
								{
									int move = _getch();
									int s_num = 0;
									int e_num = 0;
									switch (move)
									{
									case 224:
										move = _getch();
										if (move == 72)
										{
											pole[posY][posX] = pole_symb[posY][posX];
											if (posY != 0)
											{
												posY -= 1;
											}
											else
											{
												posY = height - 1;
											}
											system("cls");
											PoleIgr(length, height, posY, posX, pole);
											rules();
										}
										if (move == 80)
										{
											pole[posY][posX] = pole_symb[posY][posX];
											if (posY != height - 1)
											{
												posY += 1;
											}
											else {
												posY = 0;
											}
											system("cls");
											PoleIgr(length, height, posY, posX, pole);
											rules();
										}
										if (move == 75)
										{
											pole[posY][posX] = pole_symb[posY][posX];
											if (posX != 0)
											{
												posX -= 1;
											}
											else
											{
												posX = length - 1;
											}
											system("cls");
											PoleIgr(length, height, posY, posX, pole);
											rules();
										}

										if (move == 77)
										{
											pole[posY][posX] = pole_symb[posY][posX];
											if (posX != length - 1)
											{
												posX += 1;
											}
											else {
												posX = 0;
											}
											system("cls");
											PoleIgr(length, height, posY, posX, pole);
											rules();
										}
										break;
									case's':
										for (int i = 0; i < height; i++)
										{
											for (int j = 0; j < length; j++)
											{
												if (pole_symb[i][j] == 's')
												{
													
													if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
													{
														printf("Ошибка: Нельзя установить символ 's' на границе поля!\n");
														_getch();
													}
													else
													{
													
														pole_symb[i][j] = '.';
														pole[i][j] = pole_symb[i][j];
													}
												}
											}
										}

										
										if (posY == 0 || posY == height - 1 || posX == 0 || posX == length - 1)
										{
											printf("Ошибка: Нельзя установить символ 's' на границе поля!\n");
											_getch();
										}
										else
										{
											pole_symb[posY][posX] = 's';
											pole[posY][posX] = pole_symb[posY][posX]; 
										}

										system("cls");
										PoleSymb(length, height, pole_symb);
										rules();
										break;
									case 'e':
										for (int i = 0; i < height; i++)
										{
											for (int j = 0; j < length; j++)
											{
												if (pole_symb[i][j] == 'e')
												{
													if (i == 0 || i == height - 1 || j == 0 || j == length - 1)
													{
														pole_symb[i][j] = '#';
														pole[i][j] = pole_symb[i][j];
													}
													else
													{
														pole_symb[i][j] = '.';
														pole[i][j] = pole_symb[i][j];
													}
												}
											}
										}


										if (posY == 0 || posY == height - 1 || posX == 0 || posX == length - 1)
										{
											pole_symb[posY][posX] = 'e';
											pole[posY][posX] = pole_symb[posY][posX];
										}
										else
										{
											printf("Ошибка: Символ 'e' можно установить только на границе поля!\n");
											_getch();
										}

										system("cls");
										PoleSymb(length, height, pole_symb);
										rules();
										break;

									case 'w':
										if (pole_symb[posY][posX] == '#')
										{
											if (posY != 0 && posY != height - 1 && posX != 0 && posX != length - 1)
											{
												pole_symb[posY][posX] = '.';
											}
										}
										else if (pole_symb[posY][posX] == '.' || pole_symb[posY][posX] == 's' || pole_symb[posY][posX] == 'e')
										{
											pole_symb[posY][posX] = '#';
										}
										system("cls");
										PoleSymb(length, height, pole_symb);
										rules();
										break;
									case 'q':
										first = false;
										second = false;
										third = false;
										ispole = true;
										printf("Лабиринт сохранён");
										_getch();
										Menu1(currPos, ispole);
										break;
									}
								}
								break;
							}
						}
					}
				}
				break;
			case 2:
				if (ispole)
				{
					Menu1(currPos, ispole);

					startY = -1;
					startX = -1;
					endY = -1;
					endX = -1;
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < length; j++)
						{
							if (pole_symb[i][j] == 's')
							{
								startY = i;
								startX = j;
							}
						}
					}
					for (int i = 0; i < height; i++) {
						for (int j = 0; j < length; j++) {
							if (pole_symb[i][j] == 'e') {
								endY = i;
								endX = j;
							}
						}
					}
					if (startY == -1 || startX == -1 || endY == -1 || endX == -1)
					{
						Menu1(currPos, ispole);
						printf("Вы не обозначили позиции старта или выхода\n");
						_getch();
					}
					if (startY != -1 && startX != -1 && endY != -1 && endX != -1)
					{
						for (int i = 0; i < height; i++) {
							for (int j = 0; j < length; j++) {
								pole_way[i][j] = pole_symb[i][j];
							}
						}
						solve(startY, startX, endY, endX, pole_way, length, height);
						int wayCount = 0;
						if (pole_way[endY - 1][endX] == '*' || pole_way[endY][endX + 1] == '*' || pole_way[endY][endX - 1] == '*' || pole_way[endY + 1][endX] == '*')
						{
							for (int i = 0; i < height; i++)
							{
								for (int j = 0; j < length; j++)
								{
									if (pole_way[i][j] == '2')
									{
										pole_way[i][j] = '.';
									}
									if (i == startY && j == startX)
									{
										pole_way[i][j] = 's';
									}
									if (pole_way[i][j] == '*')
									{
										wayCount += 1;
									}
									printf("%c", pole_way[i][j]);
								}
								printf("\n");
							}
							printf("Длина пути: %d\n", wayCount);
							_getch();
						}
						else
						{
							for (int i = 0; i < height; i++) {
								for (int j = 0; j < length; j++) {
									if (pole_way[i][j] == '1' || pole_way[i][j] == '*') {
										pole_way[i][j] = '.';
									}
									if (i == startY && j == startX)
									{
										pole_way[i][j] = 's';
									}
									printf("%c", pole_way[i][j]);
								}
								printf("\n");
							}
							printf("Пути к выходу из лабиринта нет\n");
							_getch();
						}
					}
				}
				if (!ispole)
				{
					Menu1(currPos, ispole);
					printf("Вы не создали лабиринт\n");
					_getch();
				}
				break;
			case 3:
				exit(0);
				break;
			}
		}
		if (arr == 27)
		{
			exit(0);
		}
	}
}


