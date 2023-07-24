#include "Neyron.h"
#include "Neyro_dif.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

void neyro_dif(double t, double dt, double tmax) {
	fstream tx_LV, tx_R1,tx_R2, tx_NHz_up, tx_NHz_down, tx_Vh1, tx_Vh2, tx_Vh3, tx_syn_b, tx_syn_a, tx_gr_2_n;
	double I = 0.0; double dI = 0.001; double Imax = 1.4;
	double I_1, I_2;
	const int count=2;
	tmax = 10; dt = 0.00001;

	Neyron neyrons[count];
	for (int i = 0; i < count; i++) {
		neyrons[i].V = -58.7085; neyrons[i].m = 0.0953; neyrons[i].n = 0.000913; neyrons[i].h = 0.3662;		//-58.7085 0.0953 0.000913 0.3662
	}
	
	/*
	//Построение графика одного нейрона при I<0.9
	I = 0;
	while (I < 0.9) {
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();
		t = 0.0;
		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 0; i < 1; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);
			}
			t += dt;
		}
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I += 0.01;
	}

	tx_R1.open("results.txt");
	t = 0.0;
	while (t <= tmax) {
		double fn_next[Nn];
		for (int i = 0; i < 1; i++) {
			neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
			neyrons[i].CopyArray(fn_next, neyrons[i].f);
				tx_R1 << t << " " << neyrons[i].V << " " << endl;
		}
		t += dt;
	}
	tx_R1.close();

	//Построение графика одного нейрона при I<1.1
	I = 0;
	while (I < 1.1) {
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();


		t = 0.0;
		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 0; i < 1; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);
			}
			t += dt;
		}

		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I += 0.01;
	}

	tx_R2.open("results2.txt");
	t = 0.0;
	while (t <= tmax) {
		double fn_next[Nn];
		for (int i = 0; i < 1; i++) {
			neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
			neyrons[i].CopyArray(fn_next, neyrons[i].f);
				tx_R2 << t << " " << neyrons[i].V << " " << endl;
		}
		t += dt;
	}
	tx_R2.close();
	*/

	//График частот при повышении
	I = 0.0;
	tx_NHz_up.open("N_Hz_up.txt");
	while (I <= 1.4) {
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();

		t = 0.0;

		double m_m[3] = { 0.0,0.0,0.0 };
		double max_mein = 0.0; double min_mein = 0.0;
		int max_c = 0; int min_c = 0;

		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 0; i < 1; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);

				m_m[0] = m_m[1];
				m_m[1] = m_m[2];
				m_m[2] = neyrons[i].V;
				if (t > tmax/4) {
					if (m_m[0]<m_m[1] && m_m[1]>m_m[2]) {
						max_mein += m_m[1];
						max_c++;
					}
					if (m_m[0] > m_m[1] && m_m[1] < m_m[2]) {
						min_mein += m_m[1];
						min_c++;
					}
				}
			}
			t += dt;
		}

		max_mein = max_c / tmax;
		min_mein = min_c / tmax;

		tx_NHz_up << I << " " << max_mein << endl;

		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I += 0.01;
	}
	tx_NHz_up.close();
	//График частот при понижении
	tx_NHz_down.open("N_Hz_down.txt");
	while (I > 0) {
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();
		t = 0.0;

		double m_m[3] = { 0.0,0.0,0.0 };
		double max_mein = 0.0; double min_mein = 0.0;
		int max_c = 0; int min_c = 0;

		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 0; i < 1; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);

				m_m[0] = m_m[1];
				m_m[1] = m_m[2];
				m_m[2] = neyrons[i].V;
				if (t > tmax / 4) {
					if (m_m[0]<m_m[1] && m_m[1]>m_m[2]) {
						max_mein += m_m[1];
						max_c++;
					}
					if (m_m[0] > m_m[1] && m_m[1] < m_m[2]) {
						min_mein += m_m[1];
						min_c++;
					}
				}
			}
			t += dt;
		}

		max_mein = max_c / tmax;
		min_mein = min_c / tmax;

		tx_NHz_down << I << " " << max_mein << endl;

		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I -= 0.01;
	}
	tx_NHz_down.close();
	/*
	//БИФФУРКАЦИИ
	I = 0.0;
	while (I <= 1.037) {
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();

		t = 0.0;

		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 0; i < 1; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);

				if (I == 1.033) {
					tx_Vh1.open("V_h1.txt");
					for (int i = 0; i < 1; i++) {
						tx_Vh1 << neyrons[i].V << " " << neyrons[i].h;
					}
					tx_Vh1.close();
				}
				if (I == 1.035) {
					tx_Vh2.open("V_h2.txt");
					for (int i = 0; i < 1; i++) {
						tx_Vh2 << neyrons[i].V << " " << neyrons[i].h;
					}
					tx_Vh2.close();
				}
				if (I == 1.037) {
					tx_Vh3.open("V_h3.txt");
					for (int i = 0; i < 1; i++) {
						tx_Vh3 << neyrons[i].V << " " << neyrons[i].h;
					}
					tx_Vh3.close();
				}
			}
			t += dt;
		}

		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I += 0.001;
	}

	//ЧАСТЬ С СИНХРОНИЗАЦИЕЙ

	//Приведение обоих нейронов к значениям тока
	for (int i = 0; i < count; i++) {
		neyrons[i].V = -58.7085; neyrons[i].m = 0.0953; neyrons[i].n = 0.000913; neyrons[i].h = 0.3662;		//-58.7085 0.0953 0.000913 0.3662
	}
	t = 0;
	I_1 = 0.0;
	while (I_1 < 1.2) {
		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();

		t = 0.0;

		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 0; i < 1; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I_1);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);
			}
			t += dt;
		}

		tx_LV.open("last_values_N.txt");
		for (int i = 0; i < 1; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I_1 += 0.01;
	}
	t = 0;
	I_2 = 0.0;
	while (I_2 < 1.1) {
		tx_LV.open("last_values_N.txt");
		for (int i = 1; i < count; i++) {
			tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
		}
		tx_LV.close();

		t = 0.0;

		while (t <= tmax) {
			double fn_next[Nn];
			for (int i = 1; i < count; i++) {
				neyrons[i].RungeKutta_default(dt, neyrons[i].f, fn_next, I_2);
				neyrons[i].CopyArray(fn_next, neyrons[i].f);
			}
			t += dt;
		}

		tx_LV.open("last_values_N.txt");
		for (int i = 1; i < count; i++) {
			tx_LV << neyrons[i].V << " " << neyrons[i].m << " " << neyrons[i].n << " " << neyrons[i].h;
		}
		tx_LV.close();

		I_2 += 0.01;
	}

	double m_m1[3] = { 0.0,0.0,0.0 };
	double m_m2[3] = { 0.0,0.0,0.0 };
	double max_mein1 = 0.0; double max_mein2 = 0.0;
	int max_c1 = 0; int max_c2 = 0;
	t = 0;


	tx_LV.open("last_values_N.txt");
	for (int i = 1; i < count; i++) {
		tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
	}
	tx_LV.close();

	//Отрисовка и графики частот до синхронизации
	tx_gr_2_n.open("gr_2_Ney.txt");

	tx_syn_b.open("syn_b.txt");
	while (t <= tmax) {
		double fn_next[Nn];

			neyrons[0].RungeKutta_default(dt, neyrons[0].f, fn_next, I_1);
			neyrons[0].CopyArray(fn_next, neyrons[0].f);

			neyrons[1].RungeKutta_default(dt, neyrons[1].f, fn_next, I_2);
			neyrons[1].CopyArray(fn_next, neyrons[1].f);

			m_m1[0] = m_m1[1];
			m_m1[1] = m_m1[2];
			m_m1[2] = neyrons[0].V;

			m_m2[0] = m_m2[1];
			m_m2[1] = m_m2[2];
			m_m2[2] = neyrons[1].V;

			tx_gr_2_n << t << " " << neyrons[0].V << " " << neyrons[1].V << endl;

				if (m_m1[0]<m_m1[1] && m_m1[1]>m_m1[2] && m_m1[1] > 0) {
					max_c1++;
				}
				if (m_m2[0]<m_m2[1] && m_m2[1]>m_m2[2] && m_m2[1] > 0) {
					max_c2++;
				}

				max_mein1 = max_c1 / t;
				max_mein2 = max_c2 / t;
				tx_syn_b << t << " " << max_mein1 << " " << max_mein2 << endl;
		t += dt;
	}
	tx_syn_b.close();

	tx_gr_2_n.close();


	//Графики частот полсе синхронизации
	m_m1[0] = 0.0; m_m1[1] = 0.0; m_m1[2] = 0.0;
	m_m2[0] = 0.0; m_m2[1] = 0.0; m_m2[2] = 0.0;
	max_mein1 = 0.0; max_mein2 = 0.0;
	max_c1 = 0; max_c2 = 0;
	t = 0;

	tx_LV.open("last_values_N.txt");
	for (int i = 1; i < count; i++) {
		tx_LV >> neyrons[i].V >> neyrons[i].m >> neyrons[i].n >> neyrons[i].h;
	}
	tx_LV.close();

	tx_syn_a.open("syn_a.txt");
	while (t <= tmax) {
		double fn_next[Nn];

		neyrons[0].RungeKutta(dt, neyrons[0].f, fn_next, I_1,0,0);
		neyrons[0].CopyArray(fn_next, neyrons[0].f);

		neyrons[1].RungeKutta(dt, neyrons[1].f, fn_next, I_2,1,neyrons[0].V);
		neyrons[1].CopyArray(fn_next, neyrons[1].f);

		m_m1[0] = m_m1[1];
		m_m1[1] = m_m1[2];
		m_m1[2] = neyrons[0].V;

		m_m2[0] = m_m2[1];
		m_m2[1] = m_m2[2];
		m_m2[2] = neyrons[1].V;

		tx_graft << t << " " << neyrons[0].V << " " << neyrons[1].V << endl;

			if (m_m1[0]<m_m1[1] && m_m1[1]>m_m1[2] && m_m1[1] > 0) {
				max_c1++;
			}
			if (m_m2[0]<m_m2[1] && m_m2[1]>m_m2[2] && m_m2[1] > 0) {
				max_c2++;
			}

			max_mein1 = max_c1 / t;
			max_mein2 = max_c2 / t;
			tx_syn_a << t << " " << max_mein1 << " " << max_mein2 << endl;
		

		t += dt;
	}
	tx_syn_a.close();


	*/
}