%%% spremenljivke (index se za?ne od 1)
a = 1
B = [1 2 3 4]
B(2) = 8
C = [1 2 3 4; 5 6 7 8; 1 1 1 1]
C(2,1) = 7

%%% operacije
a = 4
B = [1 2 3 4]
C = a*B

A = [1 2; 3 4]
B = [4 3; 2 1]
C = A*B

A = [1 2 3; 4 5 6]
B = [1 4; 2 5; 3 6]
C = A*B

A = [1 2; 3 4]
B = [1 0; 0 1]
C = A.*B

a = 4;
B =[1 2; 3 4];
C = a+B

%%% funkcije
A = [1 2 3 4]
B = length(A)
C = max(A)
D = min(A)
S = sum(A)
P = prod(A)

A = [1 2 3 4; 5 6 7 8]
N = ndims(A)
[By, Bx] = size(A)
C = max(max(A))
D = min(min(A))

A = [1 5 3 2]
B = sort(A)
[B I] = sort(A)

%%% grafi
a = 1;
f = 1;
t = 0:0.01:10;
A = a * sin(t*f);

plot(A);

f = 2;
A = a * sin(t*f);

plot(A, 'r');

f = 4;
A = a * sin(t*f);

hold on;
plot(A, 'r');
plot(A * 2, 'b');
hold off;

%%% ui
figUI = figure;
uicontrol('Parent', figUI, 'Style', 'edit','String','hello');
help guide % gui de, ne guide %

%%% lastne funkcije
A = [1 2 3 4 5 6 7]
[B, C] = minmax(A)

%%% logika
A = 3
if (A==1) % ce je A enak 1
    B = 7;
elseif (A~=2) % drugace ce je A razlicen od 2  
    B = 5;
else
    B = 0;
end
display(B)

A = 10;
while (A>0)
    A = A-1
end

s = 0;
for f = 1:0.1:5 %f naj gre od 1 do 5 po koraku 0.1
    f
    s = s+f
end

%%% zvok
audioinfo('churchbell.wav');
[y, Fs] = audioread('churchbell.wav');
display(Fs);

plot(y);

predvajalnik = audioplayer(y, Fs*2);

play(predvajalnik);
pause(predvajalnik);
resume(predvajalnik);
stop(predvajalnik);

playblocking(predvajalnik);

