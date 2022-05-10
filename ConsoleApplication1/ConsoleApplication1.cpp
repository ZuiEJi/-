//三子棋游戏
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//游戏开始界面
void game_begin_interface();

//游戏开始页面进行选择
void game_begin_choice();

//游初始化棋盘界面
void game_recheckerboard();

//绘制棋盘
void game_drawcheckerboard();

//游戏开始
void game_start();

//玩家进行输入
void game_player();

//电脑进行输入
void game_computer();

//胜负判定
int game_determine();

//游戏结束
void game_end();

//打印‘*’号
void printf_start(int quantites);

//声明棋盘
char a[11][11];
char* b[9] = {NULL};
char position_contrast[9] = { '1','2','3','4','5','6','7','8','9' };

int main() {
	game_begin_interface();
	game_begin_choice();
	game_start();
}

//游戏开始界面
void game_begin_interface() {
	printf_start(32);
	printf("\n");
	printf("\n");
	printf_start(32);
	printf("\n");
	printf("\n");
	printf_start(5);
	printf("1.开始游戏  2.退出游戏");
	printf_start(5);
	printf("\n");
	printf("\n");
	printf_start(32);
	printf("\n");
	printf("\n");
	printf_start(32);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

//游戏开始页面进行选择
void game_begin_choice() {
	//将用户输入的选择存入number_choice
	int number_choice = -1;

	char choice;
	printf("请输入数字'1'或‘2’进行选择：");

	//此循环对用户的输入检验，只能输入0或者1
	//scanf("%d", &number_choice) != 1  检验用户是否成功输入
	while (scanf("%d", &number_choice) != 1||(number_choice>2||number_choice<1)) {
		//嵌套循环去除多余的输入
		while ((choice=getchar()) != '\n') { 
			continue;
		}
		game_begin_choice();
	}

	if (number_choice == 1) {
		game_recheckerboard();
	}
	else {
		game_end();
	}

	
}

//初始化棋盘界面
void game_recheckerboard() {
	system("cls");

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++) {
			if (i % 4 != 3 && j % 4 != 3) {
				a[i][j] = ' ';

			}
			else if (i % 4 == 1 && j % 4 == 1) {
				if (a[i][j] == NULL) {
					a[i][j] = ' ';
				}

			}
			else {
				a[i][j] = '*';
			}
		}
	}


	//此循环用于将棋子的位置进行赋值数字1~9，并将9个数字的地址传给指针‘*b[9]’便于后期单独处理运算
	int count_1 = 0;
	char count_2 = '1';

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i % 4 == 1 && j % 4 == 1) {
				a[i][j] = count_2;
				count_2++;
				b[count_1] = &a[i][j];
				count_1++;
			}
		}
	}

	game_drawcheckerboard();
}

//绘制棋盘
void game_drawcheckerboard() {
	putchar('\n');
	putchar('\n');
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			putchar(a[i][j]);
		}
		putchar('\n');

	}
}

//游戏开始
void game_start() {
	//通过flag的数字判断结果
	int flag = 0;
	//count为下棋的步数，若步数为9则棋盘已经下满，若此时没有分出胜负则达成平局
	int count = 0;
	while (flag == 0) {

		//玩家下棋
		game_player();
		//更新棋盘
		game_drawcheckerboard();
		//胜负判断
		flag = game_determine();
		if (flag == 1) {
			break;
		}
		//步数加1
		count++;
		//若count=9，结束循环
		if (count == 9) {
			flag = 3;
			break;
		}



		//电脑下棋
		game_computer();
		//同上
		game_drawcheckerboard();
		//同上
		flag = game_determine();
		if (flag == 2) {
			break;
		}
		//同上
		count++;

		//同上
		if (count == 9) {
			flag = 3;
			break;
		}

		flag = game_determine();
	}


	//通过flag判断结果
	if (flag == 1) {
		printf("\n玩家获胜\n");
	}
	else if (flag == 2) {
		printf("\n电脑获胜\n");
	}
	else if (flag == 3) {
		printf("\n平局\n");
	}
}

//玩家输入
void game_player() {
		//玩家输入棋子的位置
		int position_input;
		printf("\n请输入您要下棋的位置:");
		scanf("%d", &position_input);

		//因为数组从0开始而玩家从1开始，所以减1
		position_input = position_input - 1;
		

		//判断位置是否已被占用
		if (position_contrast[position_input] != '0') 
		{
			position_contrast[position_input] = '0';
			*b[position_input] = 'O';
		}
		else {
			printf("\n该位置已经下过，请重新选择位置\n");
			game_player();
		}
}

//电脑进行输入
void game_computer() {
	int random_n1 = 0;
	random_n1 = rand()%9;
	if (position_contrast[random_n1] != '0') 
	{
		position_contrast[random_n1] = '0';
		*b[random_n1] = 'X';
	}
	else {
		game_computer();
	}
}

//胜负判定
int game_determine(){
	//将一维数组a[9]转化为二维数组a[3][3]便于计算
	char* b2[3][3];
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			b2[i][j] = b[count];
			count++;
		}
	}


	//判断每一横
	for (int i = 0; i < 3; i++) {
		if ((*b2[i][0] == *b2[i][1]) && (*b2[i][1] == *b2[i][2])) {
			if (*b2[i][1] == 'O') {
				return 1;
			}
			else if(*b2[i][1] == 'X'){
				return 2;
			}
		}
	}

	//判断每一竖
	for (int i = 0; i < 3; i++) {
		if ((*b2[0][i] == *b2[1][i]) && (*b2[2][i] == *b2[1][i])) {
			if (*b2[1][i] == 'O') {
				return 1;
			}
			else if (*b2[1][i] == 'X') {
				return 2;
			}
		}
	}

	//判断对角线
	if ((*b2[0][0] == *b2[1][1]) && (*b2[1][1] == *b2[2][2])) {
		if (*b2[1][1] == 'O') {
			return 1;
		}
		else if (*b2[1][1] == 'X') {
			return 2;
		}
	}

	if ((*b2[0][2] == *b2[1][1]) && (*b2[1][1] == *b2[2][0])) {
		if (*b2[1][1] == 'O') {
			return 1;
		}
		else if (*b2[1][1] == 'X') {
			return 2;
		}
	}

	return 0;
}


//游戏结束
void game_end() {
	exit(1);
}



//打印‘*’号
void printf_start(int quantites) {
	for (int i = 1; i <= quantites; i++) {
		printf("*");
	}
}