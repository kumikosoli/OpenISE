
I=imread("StandardImage/grayscale/woman2.BMP");
J=imread("StandardImage/grayscale/woman1.tiff");

K=imadd(I,J,'uint16'); 
K0=imadd(I,J);

figure(1);
imshow(I)

figure(2);
imshow(J)

figure(3);
imshow(K,[])

figure(4);
imshow(K0)

