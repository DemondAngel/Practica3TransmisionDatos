clear all;
close all;
clc;

SNR= 0:0.01:20;
SNR_points = 0:1:20;
B=25e+03;
snr=1*10.^(SNR/10);
snr_points = 1*10.^(SNR_points/10);
C = @ (snr) B*log2(1+snr);

shannonImage = figure(1);
plot(SNR, C(snr));
title('Shannon-Hartley Capacity');
xlabel('SNR_{dB}');
ylabel('ChannelCapacity');
hold on;
plot(SNR_points, C(snr_points), 'r*');
grid on;

saveas(shannonImage, 'images/shannon_capacity.png');