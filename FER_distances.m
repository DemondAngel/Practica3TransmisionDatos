close all
clear all

distances = [0.1, 0.5, 1, 5, 10, 15, 20]; %meters
frames_error = [100, 79, 75, 63, 40, 32, 10]; %frames
total_frames = [1, 2, 3, 4, 5, 6, 7]; %frames
for k = 1:length(distances)
    fer(k) = frames_error(k)/total_frames(k);
end
plot(distances,fer)
xlabel 'Distances [m]'
ylabel 'FER'
