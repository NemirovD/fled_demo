%clear the figure and variables
clf
clear

%setting up the variables
%plot axes at origin
x1 = [0;1];
y1 = [0;0];
z1 = [0;0];
x2 = [0;0];
y2 = [0;1];
z2 = [0;0];
x3 = [0;0];
y3 = [0;0];
z3 = [0;1];
subplot(1,2,1);
plot3(x1,y1,z1,'b',x2,y2,z2,'b',x3,y3,z3,'b');
hold on;

%Point world uses homogeneous coords
Pw =[2;
    2;
    10;
    1];

Pwn=[Pw(1);
    Pw(2);
    Pw(3)];

plot3(Pw(1), Pw(2), Pw(3),'+g');

%%Camera coords
C = [0; 0; -5];
%camera
plot3(C(1),C(2),C(3),'or');
plot3([C(1) C(1)] ,[C(2) C(2)] ,[C(3) C(3)+2],'r');

boxx = [C(1)-0.5 C(1)-0.5 C(1)+0.5 C(1)+0.5 C(1)-0.5];
boxy = [C(2)+0.5 C(2)-0.5 C(2)-0.5 C(2)+0.5 C(1)+0.5];
boxz = [C(3)+1 C(3)+1 C(3)+1 C(3)+1 C(3)+1];
plot3(boxx,boxy,boxz,'r');

I = eye(3);

%assuming that the camera is perfectly aligned with the axes
R = [1 0 0;
    0 1 0;
    0 0 1];

%K is the same k from the camera calibration programs
K = [7.4094755240421250e+002 0 3.1950000000000000e+002;
    0 7.4094755240421250e+002 2.3950000000000000e+002;
    0 0 1];

%let's create an imaginary camera with a principal point of 50,50 and a
%focal length of 200 A will denote it's camera matrix

A = [200 0 50;
    0 200 50;
    0 0 1];

Pc = K * R * [I -C] * Pw;
%In order to get accurate results we must divide Pc by w or Pc(3)
Pcn = Pc/Pc(3);

Pcn = [Pcn(1); Pcn(2); 1];

disp('With w')
Cans = -I * inv(R) * inv(K) * Pc +Pwn %#ok<NOPTS>

disp('Without w');
Ca = -I * inv(R) * inv(K) * Pcn +Pwn %#ok<*MINV,NOPTS>  


hold off;

xlabel('X')
ylabel('Y')
zlabel('Z')

grid on;
axis equal;

subplot(1,2,2);
plot(Pcn(1),Pcn(2),'+g');
axis([0 640 0 480]);
axis square;
