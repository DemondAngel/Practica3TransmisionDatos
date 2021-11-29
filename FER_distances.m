close all
clear all

distances = [0.1, 0.5, 1, 5, 10, 15, 20]; %meters
frames_error = [28, 135, 108, 75, 88, 35, 25]; %frames
total_frames = [98, 172, 158, 155, 98, 37, 26]; %frames

frames_error2 = [588, 513, 368, 375, 43, 29, 22]; %frames
total_frames2 = [1771, 1704, 816, 639, 54, 44, 32]; %frames


for k = 1:length(distances)
    fer(k) = frames_error(k)/total_frames(k);
    fer2(k) = frames_error2(k)/total_frames2(k);
end

plot(distances,fer)
hold on 
plot(distances,fer2)
title('433 MHz transmission FER');
xlabel 'Distances [m]'
ylabel 'FER'
legend('Polynomial 1', ' Polynomial 2')