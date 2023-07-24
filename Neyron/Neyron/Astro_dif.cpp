#include "Astrocite.h"
#include "Astro_dif.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

void astro_dif(double t, double dt, double tmax) {
	fstream tx_LV, tx_Ahz;

	const int count = 1;
	Astrocite astrocites[count];
	
		tx_Ahz.open("A_Hz.txt");


		while (astrocites[0].IP3_star < 6.0) {

			tx_LV.open("last_values_A.txt");
			//0.07 0.16 0.67
			for (int i = 0; i < count; i++) {
				tx_LV >> astrocites[i].Ca >> astrocites[i].IP3 >> astrocites[i].z;
			}
			tx_LV.close();

			bool f = true;
			double m_m[3] = { 0.0,0.0,0.0 };
			t = 0.0;
			double max_mein = 0.0; double min_mein = 0.0;
			int max_c = 0; int min_c = 0;
			while (t <= tmax) {
				double fa_next[Na];
				for (int i = 0; i < count; i++) {
					astrocites[i].RungeKutta(dt, astrocites[i].f, fa_next);
					astrocites[i].CopyArray(fa_next, astrocites[i].f);
					//cout << fixed;
					//cout << setprecision(6);
					//cout << t << " " << i << " " << a1[i].Ca << " " << a1[i].IP3 << " " << a1[i].z << '\n';
					


					m_m[0] = m_m[1];
					m_m[1] = m_m[2];
					m_m[2] = astrocites[i].Ca;
					if (t > tmax/4) {
						
						if (astrocites[0].IP3_star < 0.5) {
							max_mein = astrocites[i].Ca;
							min_mein = astrocites[i].Ca;
							max_c++;
							min_c++;
						}

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
			max_mein = max_mein / max_c;
			min_mein = min_mein / min_c;

			tx_LV.open("last_values_A.txt");
			for (int i = 0; i < count; i++) {
				tx_LV << astrocites[i].Ca << " " << astrocites[i].IP3 << " " << astrocites[i].z << '\n';
			}
			tx_LV.close();
			cout << (astrocites[0].IP3_star / 6.0) * 100 << "%" << endl;
			
			//cout << a1[0].IP3_star << " " << max_mein << " " << min_mein << endl;
			tx_Ahz << astrocites[0].IP3_star << " " << max_mein << " " << min_mein<<endl;
			astrocites[0].IP3_star += 0.01;
		}

		while (astrocites[0].IP3_star > 0.0) {

			tx_LV.open("last_values_A.txt");
			//0.07 0.16 0.67
			for (int i = 0; i < count; i++) {
				tx_LV >> astrocites[i].Ca >> astrocites[i].IP3 >> astrocites[i].z;
			}
			tx_LV.close();

			bool f = true;
			double m_m[3] = { 0.0,0.0,0.0 };
			t = 0.0;
			double max_mein = 0.0; double min_mein = 0.0;
			int max_c = 0; int min_c = 0;
			while (t <= tmax) {
				double fa_next[Na];
				for (int i = 0; i < count; i++) {
					astrocites[i].RungeKutta(dt, astrocites[i].f, fa_next);
					astrocites[i].CopyArray(fa_next, astrocites[i].f);
					//cout << fixed;
					//cout << setprecision(6);
					//cout << t << " " << i << " " << a1[i].Ca << " " << a1[i].IP3 << " " << a1[i].z << '\n';


					m_m[0] = m_m[1];
					m_m[1] = m_m[2];
					m_m[2] = astrocites[i].Ca;
					if (t > 50) {

						if (astrocites[0].IP3_star < 0.5) {
							max_mein = astrocites[i].Ca;
							min_mein = astrocites[i].Ca;
							max_c++;
							min_c++;
						}

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
			max_mein = max_mein / max_c;
			min_mein = min_mein / min_c;

			tx_LV.open("last_values_A.txt");
			for (int i = 0; i < count; i++) {
				tx_LV << astrocites[i].Ca << " " << astrocites[i].IP3 << " " << astrocites[i].z << '\n';
			}
			tx_LV.close();
			cout << (astrocites[0].IP3_star / 6.0) * 100 << "%" << endl;

			//cout << a1[0].IP3_star << " " << max_mein << " " << min_mein << endl;
			tx_Ahz << astrocites[0].IP3_star << " " << max_mein << " " << min_mein << endl;
			astrocites[0].IP3_star -= 0.01;
		}
		astrocites[0].IP3_star = 0;
	
	tx_Ahz.close();

}