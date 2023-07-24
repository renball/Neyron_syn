close all;
clc;
clear;

FontSize = 10;

filename1 = '/users/q/source/repos/Neyron/Neyron/results.txt';
filename2 = '/users/q/source/repos/Neyron/Neyron/results2.txt';
filename3 = '/users/q/source/repos/Neyron/Neyron/N_Hz_up.txt';
filename7 = '/users/q/source/repos/Neyron/Neyron/N_Hz_down.txt';
filename4 = '/users/q/source/repos/Neyron/Neyron/gr_2_Ney.txt';
filename5 = '/users/q/source/repos/Neyron/Neyron/syn_a.txt';
filename6 = '/users/q/source/repos/Neyron/Neyron/syn_b.txt';

#filename7 = '/users/q/source/repos/Neyron/Neyron/V_h.txt';
#filename8 = '/users/q/source/repos/Neyron/Neyron/V_n.txt';
#filename9 = '/users/q/source/repos/Neyron/Neyron/V_m.txt';


#filename10 = '/users/q/source/repos/Neyron/Neyron/A_Hz.txt';

Data = importdata( [ filename1 ] );
t1 = Data(:,1);
V1 = Data(:,2);

Data = importdata( [ filename2 ] );
t2 = Data(:,1);
V2 = Data(:,2);

Data = importdata( [ filename3 ] );
t_Hz_u = Data(:,1);
Hz_Up = Data(:,2);

Data = importdata( [ filename7 ] );
t_Hz_d = Data(:,1);
Hz_down = Data(:,2);

Data = importdata( [ filename4 ] );
t_d = Data(:,1);
V1_d = Data(:,2);
V2_d = Data(:,3);

Data = importdata( [ filename5 ] );
t_N_Hz_b = Data(:,1);
Hz1_b = Data(:,2);
Hz2_b = Data(:,3);

Data = importdata( [ filename6 ] );
t_N_Hz_a = Data(:,1);
Hz1_a = Data(:,2);
Hz2_a = Data(:,3);

#Data = importdata( [ filename7 ] );
#v1 = Data(:,1);
#h = Data(:,2);

#Data = importdata( [ filename8 ] );
#v2 = Data(:,1);
#n = Data(:,2);

#Data = importdata( [ filename9 ] );
#v3 = Data(:,1);
#m = Data(:,2);

#Data = importdata( [ filename10 ] );
#t_Hz_Astr = Data(:,1);
#Hz_Up_Astr = Data(:,2);
#Hz_Down_Astr = Data(:,3);

fig1 = figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(1, 1, 1);
plot(t1, V1, 'r', 'LineWidth', 1);

fig2 = figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(1, 1, 1);
plot(t2, V2, 'r', 'LineWidth', 1);

fig3 = figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(1, 1, 1);
plot(t_Hz_u, Hz_Up,'LineWidth', 2, t_Hz_d, Hz_down, 'LineWidth', 2);

fig4 = figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(1, 1, 1);
plot(t_d, V1_d,t_d,V2_d , 'r', 'LineWidth', 1);

fig5 = figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(1, 1, 1);
plot(t_N_Hz_b, Hz1_b, t_N_Hz_b, Hz2_b , 'r', 'LineWidth', 1);

fig6 = figure('units', 'normalized', 'outerposition', [0 0 1 1]);
subplot(1, 1, 1);
plot(t_N_Hz_a, Hz1_a, t_N_Hz_a, Hz2_a , 'r', 'LineWidth', 1);




