clear all;
close all;
clc;

SNR= 0:0.01:20;

snr=10.^(SNR/10);
B=25e+03;

C = B*log2(1+snr);

figure(1);
plot(SNR, C);
title('Shannon');
xlabel('SNR_{dB}');
ylabel('Channel Capacity');
grid on;