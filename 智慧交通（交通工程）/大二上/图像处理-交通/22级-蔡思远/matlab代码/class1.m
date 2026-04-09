A=imread("StandardImage/grayscale/barbara.BMP");
maxA=max(max(A));
minA=min(min(A));
figure(1);
imshow(A)

B1=255-A; 
maxB1=max(max(B1));
minB1=min(min(B1));
figure(2);
imshow(B1);

B2=A+50;
maxB2=max(max(B2))
minB2=min(min(B2))
figure(3)
imshow(B2)

B3=uint16(A)+50
maxB3=max(max(B3))
minB3=min(min(B3))
figure(5)
imshow(B3)

A=imread("StandardImage/grayscale/barbara.BMP")
B=A-46;
c=45; 
B1=c*log(double(B)+1); 
maxB1=max(max(B1)); 
minB1=min(min(B1)); 
figure(4)
imshow(uint8(B1)); 

