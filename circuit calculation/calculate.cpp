#include<iostream>
#include<math.h>
#include<fstream>
#include<stdlib.h>
using namespace std;
int main() {
	int n, m, sit;
	float U, R_1, R_2, R_3, R_4, I;
	double a[3][4];
	cin >> sit >> U >> R_1 >> R_2 >> R_3 >> R_4;
	if (sit == 1) {
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
	cout << "电流大小为：" << I << endl;
}
