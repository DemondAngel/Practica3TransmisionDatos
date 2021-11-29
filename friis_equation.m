clear all;
close all;
clc;

Gtx = 3; 
Grx = 3;
c = 3e+08;
fc = 433e+06;
Ptx = 40;
d = 0:0.01:20;
r = [0.1 0.5 1 5 10 15 20];
Prx = @(d) Ptx + Gtx + Grx + 20*log10(c/fc) - 20*log(4*pi*d);

figure(1);
plot(d, Prx(d));
title('Friis Equation');
xlabel('Distance (m)');
ylabel('Reception Power (W)');
hold on
plot(r,Prx(r),'r*');
grid on;

