clear all;
close all;
clc;

SNR= 0:0.01:20;
B=25e+03;
snr=1*10.^(SNR/10);
C = B*log2(1+snr);

shannonImage = figure(1);
plot(SNR, C);
title('Shannon-Hartley Capacity');
xlabel('SNR_{dB}');
ylabel('Channel Capacity');
grid on;

saveas(shannonImage, 'images/shannon_capacity.png');