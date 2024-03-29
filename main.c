#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

void tabl0(char stolb[], char stroka[], char tabl1[][10]);
void output(char stolb[], char stroka[], char tabl1[][10], char tablproverka1[][10], char tablproverka2[][10], int k1);
int proverka(char tabl1[][10], char tablproverka1[][10], char tablproverka2[][10]);
void hard();
void rules();
void cheatcode(char tabl1[][10]);


int main() {
	setlocale(LC_ALL, "RUS");
	char numberok = '1';
	puts("Для начала нажмите клавишу Enter");
	char line[500];
	FILE* file = fopen("trees.txt", "r");
	if (file == NULL) {
		perror("Ошибка при открытии файла");
		return -1;
	}
	for (int i = 0;i < 9;i++) {
		fgets(line, 500, file);
		printf("%s", line);
	}
	fclose(file);
	//создание необходимых массивов для использования их в функции
	char stolb[10] = { '3', '1', '2', '2', '2', '1', '3', '2', '2', '2' }; //количество палаток в столбце
	char stroka[10] = { '1', '3', '1', '3', '1', '2', '3', '1', '1', '4' };//количество палаток в строке
	char tabl1[10][10] =
	{
		{'0','0','0','0','0','1','2','0','0','0'},
		{'0','0','2','0','2','0','0','1','2','0'},
		{'0','0','1','0','1','0','2','0','0','0'},
		{'2','0','0','2','1','0','1','0','2','1'},
		{'1','0','0','0','0','0','2','1','0','1'},
		{'2','0','0','0','0','0','0','0','0','2'},
		{'1','0','1','2','0','2','0','2','1','0'},
		{'0','2','0','0','0','1','0','0','0','0'},
		{'1','1','0','0','0','0','0','0','1','2'},
		{'2','0','2','1','2','1','1','2','0','0'}
	},                                                          //tabl1 - начальная таблица первый раз на выводе не выписываем палатки
		tablproverka1[10][10] =
	{
		{'0','0','0','0','0','1','2','0','0','0'},
		{'0','0','2','0','2','0','0','1','2','0'},
		{'0','0','1','0','1','0','2','0','0','0'},
		{'2','0','0','2','1','0','1','0','2','1'},
		{'1','0','0','0','0','0','2','1','0','1'},
		{'2','0','0','0','0','0','0','0','0','2'},
		{'1','0','1','2','0','2','0','2','1','0'},
		{'0','2','0','0','0','1','0','0','0','0'},
		{'1','1','0','0','0','0','0','0','1','2'},
		{'2','0','2','1','2','1','1','2','0','0'}
	},                                                          //tablproverka1 необходим для ввода ответа
		tablproverka2[10][10] =
	{
		{'0','0','0','0','0','1','0','0','0','0'},
		{'0','0','0','0','0','0','0','1','0','0'},
		{'0','0','1','0','1','0','0','0','0','0'},
		{'0','0','0','0','1','0','1','0','0','1'},
		{'1','0','0','0','0','0','0','1','0','1'},
		{'0','0','0','0','0','0','0','0','0','0'},
		{'1','0','1','0','0','0','0','0','1','0'},
		{'0','0','0','0','0','1','0','0','0','0'},
		{'1','1','0','0','0','0','0','0','1','0'},
		{'0','0','0','1','0','1','1','0','0','0'}
	};
	/*Создаём новый массив чтобы сделать проверку на сходство координаты пользователя с координатой задачи*/
	//Присвоение 1 необходимо для обозначения дерева, 0 - это пустая клетка, куда возможно будет установлена палатка, 2 - это правильное место расположения палатки


	while (numberok != '0') {
		getchar();
		system("cls");
		puts("  ***Лагерь***");
		char number = '0';
		int k2, difficulty = 0;


		puts("\nВыберите действие:\n1. Начать игру.\n2. Правила.\n3. О сложностях.\n4. Выход.\n");
		scanf("%c", &number);
		getchar();

		switch (number) {
		case '1'://кнопка 1
			tabl0(stolb, stroka, tabl1, tablproverka1, tablproverka2);

			printf("\n\nВам необходимо отгадать расположение 20-ти палаток.\nВы будете вводить координаты палаток через пробел следующим образом:\n1. Строка.\n2. Столбец.\n");

			int n = 2;
			for (int x = 0; x < n;x++) {
				puts("\nВыберите сложность игры:\n1. Лёгкая.\n2. Средняя.\n3. Сложная.\n");
				scanf("%d", &difficulty); //выбор сложности уровня
				if (difficulty == 1) {
					k2 = 0;
					puts("Отлично, вы выбрали самый простой уровень сложности. Для понимания игры этого будет достаточно.");
					break;
				}
				else if (difficulty == 2) {
					k2 = 5;
					puts("Что ж, вы выбрали не самый простой путь на пути к победе, потому что вы можете ошибиться лишь 5 раз!");
					break;
				}
				else if (difficulty == 3) {
					k2 = 8;
					puts("Без комментариев..., удачи!");
					break;
				}
				else {
					puts("***Введено не верное значение!***");
					n += 2;
				}
			}
			for (int i = 0;i < 20;i++) {//start for 1
				int k1 = 0;
				printf("\nВведите координату клетки номер %d\n", i + 1);
				while (k1 != 1) {
					int errorgrandtotal = proverka(tabl1, tablproverka1, tablproverka2);
					if (errorgrandtotal == 1) {
						k1 += 1;
						output(stolb, stroka, tabl1, tablproverka1, tablproverka2, k1);
					}
					else if (errorgrandtotal == 2) {
						printf("\nКоординаты введены были введены раннее, попробуйте снова\n");
					}
					else
					{
						k2 += 1;
						if (k2 == 10) {
							break;
						}
						if (10 - k2 == 1) {
							printf("\nКоординаты введены неверно, попробуйте снова. У вас есть ещё 1 раз совершить ошибку.\n");
						}
						else {
							printf("\nКоординаты введены неверно, попробуйте снова. У вас есть ещё %d раза совершить ошибку.\n", 10 - k2);
						}
					}
					if (k2 == 10) {
						k1 += 1;
					}
				}	//цикл вайл закрытие
				if (k2 == 10) {
					break;
				}
			}//end for 1

			if (k2 < 10) {
				printf("\nУра, победа!\n");
			}
			else {
				printf("\nУвы, попробуйте снова или повторите попытку позже.\n");
			}
			system("pause");
			break;
		case '2'://кнопка 2
			rules();
			puts("Для продолжения нажмите клавишу Enter");
			break;
		case '3'://кнопка 3
			hard();
			puts("Для продолжения нажмите клавишу Enter");
			break;
		case '4'://кнопка 4
			return '0';
		case '5'://кнопка 5

			cheatcode(tabl1);
			puts("Для продолжения нажмите клавишу Enter");
			break;
		default:
			printf("Введено неверное значение\n");
			puts("Для продолжения нажмите клавишу Enter");
			break;
		}
	}
}

/*Функция которая делает уровень*/

void tabl0(char stolb[], char stroka[], char tabl1[][10]) {
	printf("   ");
	for (int i = 0;i < 10;i++) {
		printf("%3c ", stolb[i]);
	}

	printf("\n   _________________________________________\n");
	for (int i = 0;i < 10;i++) {
		printf(" %c ", stroka[i]);
		for (int j = 0;j < 10;j++) {
			if ((tabl1[i][j] == '0') || (tabl1[i][j] == '2')) {
				printf("|   ");
			}
			else {
				printf("| %c ", 6);
			}
		}
		printf("|\n   |___|___|___|___|___|___|___|___|___|___|\n");
	}
}


void output(char stolb[], char stroka[], char tabl1[][10], char tablproverka1[][10], char tablproverka2[][10], int k1) {
	system("cls");	//это действие сделано для того, чтобы пользователю всё сразу не выскакивало одним шквалом информации+это обновляет таблицу
	printf("   ");
	for (int z = 0;z < 10;z++) {			//Начало цикла 2
		printf("%3c ", stolb[z]);			//печатает сколько палаток будет в каждом столбце
	}										//Конец цикла 2




	printf("\n   _________________________________________\n");
	for (int i = 0;i < 10;i++) {			//Начало цикла 3
		printf(" %c ", stroka[i]);			//каждую новую строку печатает сколько палаток должно быть в строке
		for (int j = 0;j < 10;j++) {		//Начало цикла 4
			if (tabl1[i][j] == '1') {
				printf("| %c ", 6);
			}
			else if (tablproverka2[i][j] == '2') {	//Добавляет 1 символ правильного ответа
				printf("| %c ", 30);
			}
			else {
				printf("|   ");
			}
		}									//Конец цикла 4
		printf("|\n   |___|___|___|___|___|___|___|___|___|___|\n");
	}										//Конец цикла 3
}


int proverka(char tabl1[][10], char tablproverka1[][10], char tablproverka2[][10]) {

	int x = 0, y = 0;
	scanf("%d %d", &x, &y);//Пользователь вводит координаты палатки		
	tablproverka1[x][y] = '2';

	if (tablproverka1[x][y] != tablproverka2[x][y]) {//если координаты были введены правильно, и они не совпадают, то выполняется следующее условие

		if (tablproverka1[x][y] == tabl1[x][y]) {	//Если координаты пользователя совпадают с координатами правильного ответа,
			tablproverka2[x][y] = '2';
			return 1;
		}


		else {
			return 0;
		}
	}
	if (tablproverka1[x][y] == tablproverka2[x][y]) {
		return 2;
	}
}



void rules() {
	setlocale(LC_ALL, "RUS");
	puts("\nПеред вами игра - головоломка Лагерь.\nОна представляет собой прямоугольную сетку, \nнекоторые клетки которой содержат «деревья».\n");
	puts("Необходимо разместить рядом с деревьями «палатки», соблюдая следующие правила :");
	puts("1. Число палаток равняется числу деревьев.");
	puts("2. Каждая палатка располагается рядом со «своим» деревом по горизонтали или вертикали, \nно не по диагонали. Если это условие выполнено, расположение по отношению к «чужим» деревьям значения не имеет.");
	puts("3. Две палатки не могут располагаться в соседних клетках, в том числе и по диагонали. \nЧисла сбоку и сверху означают, сколько палаток находится в этой строке или столбце.\n");
	system("pause");
	system("cls");
}

void hard() {
	puts("По правилам, если игрок ошибается определённое количество раз, то как только закончатся ""ОШИБКИ"",\n игра будет закончена.");
	puts("Есть три сложности:\n   Лёгкая сложность - игроку допускается ошибиться 10 раз.\n   Средняя сложность - игроку допускается ошибиться 5 раз\n   Сложная сложность - игроку допускается ошибиться всего лишь 1 раз!\n");
}

void cheatcode(char tabl1[][10]) {
	int k = 1;
	for (int i=0; i<10; i++)
		for (int j=0; j<10; j++)
			if (tabl1[i][j] == '2') {
				printf("\nТочка %d -> [%d][%d]\n", k, i, j);
				k++;
			}
}
