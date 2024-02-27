I = imread('beach.jpg');
% hsv = rgb2hsv(I);
% figure,imshow(hsv(:,:,1));
% figure,imshow(hsv(:,:,2));
% figure,imshow(hsv(:,:,3));
mm = rgb2gray(I);
mm = 255 -mm;
imshow(mm);