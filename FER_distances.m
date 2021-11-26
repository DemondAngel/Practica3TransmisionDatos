close all
clear all

distances = [0.1, 0.5, 1, 5, 10, 15, 20]; %meters
frames_error = [100, 79, 75, 63, 40, 32, 10]; %frames
total_frames = 100; %frames
fer = frames_error/total_frames;
plot(distances,fer)
xlabel 'Distances [m]'
ylabel 'FER'