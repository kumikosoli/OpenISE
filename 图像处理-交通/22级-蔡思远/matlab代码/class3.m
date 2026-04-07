a=imread('StandardImage/grayscale/milkdrop.BMP');
b=fspecial("laplacian");
c=fspecial("sobel");
figure,imshow(a);
figure,imshow(b);
figure,imshow(c);