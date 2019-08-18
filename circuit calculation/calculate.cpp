/**
 * @file Circuilt Calculator
 * @brief 电流计算器
 * @details 基于基尔霍夫定律和矩阵运算计算给定电路中电流值
 * @mainpage Circuilt Calculator
 * @author LGY's team
 * @email 569831010@qq.com
 * @version 1.0.0
 * @date 2019-8-16
 */
#include<iostream>
#include<math.h>
#include<fstream>
#include<stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>

//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//TEST_CASE("I is computed", "[calculation]") {
	//REQUIRE(Calculation(1, 1, 1, 1, 1, 1) == 1);
//}
using namespace std;


 /**
 * @brief A calculator for electric current , labeled as I.
 */
class Calculation
{
public:
	/// Choose the first or second image given.
	int type;
	/// Insert an integer in the UI surface to decide to calculate which type of circuits.
	int input;
	/// Assign a value for voltage , labeled as U.
	float U;
	/// Assign a value for R1.
	float R_1;
	/// Assign a value for R2.
	float R_2;
	/// Assign a value for R3.
	float R_3;
	/// Assign a value for R4.
	float R_4;
	float I;
	void init();
	void out();
	float calculate();
};
/**
 * @brief To initialize all the parameters needed in the calculator.
 */
void Calculation::init() {
	cout << "Please enter the value of U(/V), R1(/Ω), R2(/Ω), R3(/Ω), R4(/Ω) in order :";
	cin >> U >> R_1 >> R_2 >> R_3 >> R_4;
}
/**
 * @brief To systhesize all parts in the program , including parameter init, UI surface and calculation.
 */
void Calculation::out() {
	initgraph(640, 480);   // 这里和 TC 略有区别
	IMAGE starup_window;
	loadimage(&starup_window, _T("资源文件夹\\登陆界面.jpg"), 640, 480);
	putimage(0, 0, 640, 480, &starup_window, 0, 0);


	IMAGE circuit1;
	loadimage(&circuit1, _T("资源文件夹\\图形1.jpg"), 280, 240);
	putimage(30, 150, 280, 240, &circuit1, 0, 0);

	IMAGE circuit2;
	loadimage(&circuit2, _T("资源文件夹\\图形2.jpg"), 280, 240);
	putimage(330, 150, 280, 240, &circuit2, 0, 0);

	TCHAR s1[50];
	_stprintf_s(s1, _T("电路图形: %d"), 1);
	outtextxy(100, 100, s1);

	TCHAR s2[50];
	_stprintf_s(s2, _T("电路图形: %d"), 2);
	outtextxy(440, 100, s2);
	FlushBatchDraw();                    //防频闪绘图

loop:
	input = _getch();
	if (input == '1')
	{
		type = 1;
		closegraph();
		init();
		I = calculate();
		cout << "电流大小为：" << I << "A" << endl;
	}
	if (input == '2')
	{
		type = 2;
		closegraph();
		init();
		I = calculate();
		cout << "电流大小为：" << I << "A" << endl;
	}
	else
	{
		goto loop;
	}
}
/**
 * @brief Use all the parameters and matrix calculation to calculate the value of electric current.
 */
float Calculation::calculate() {
	int n, m;
	float I;
	double a[3][4];
	if (type == 1) {
		a[0][0] = R_1 + R_2;
		a[0][1] = -R_1;
		a[0][2] = -R_2;
		a[0][3] = U;
		a[1][0] = -R_1;
		a[1][1] = R_1 + R_3;
		a[1][2] = -R_3;
		a[1][3] = 0;
		a[2][0] = -R_2;
		a[2][1] = -R_3;
		a[2][2] = R_2 + R_3 + R_4;
		a[2][3] = 0;
	}
	else {
		a[0][0] = R_1 + R_4;
		a[0][1] = -R_1;
		a[0][2] = -R_4;
		a[0][3] = U;
		a[1][0] = -R_1;
		a[1][1] = R_1 + R_2 + R_3;
		a[1][2] = -R_2;
		a[1][3] = 0;
		a[2][0] = -R_4;
		a[2][1] = -R_2;
		a[2][2] = R_2 + R_4;
		a[2][3] = 0;
	}
	int i, j;
	n = 3;
	for (j = 0; j < n; j++) {
		double max = 0;
		double imax = 0;
		for (i = j; i < n; i++) {
			if (imax < fabs(a[i][j])) {
				imax = fabs(a[i][j]);
				max = a[i][j];
				m = i;
			}
		}
		if (fabs(a[j][j]) != max) {
			double b = 0;
			for (int k = j; k < n + 1; k++) {
				b = a[j][k];
				a[j][k] = a[m][k];
				a[m][k] = b;
			}
		}

		for (int r = j; r < n + 1; r++) {
			a[j][r] = a[j][r] / max;
		}

		for (i = j + 1; i < n; i++) {
			double c = a[i][j];
			if (c == 0) continue;
			for (int s = j; s < n + 1; s++) {
				double tempdata = a[i][s];
				a[i][s] = a[i][s] - a[j][s] * c;

			}

		}

	}
	for (i = n - 2; i >= 0; i--) {
		for (j = i + 1; j < n; j++) {
			double tempData = a[i][j];
			double data1 = a[i][n];
			double data2 = a[j][n];
			a[i][n] = a[i][n] - a[j][n] * a[i][j];

		}
	}
	I = a[0][3];
	return I;
}

int main() {
	Calculation cal;
	cal.out();
	return 0;
}
