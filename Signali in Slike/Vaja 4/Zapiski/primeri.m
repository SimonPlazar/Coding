%% Primeri za DFT %%


%% skalarni produkt dveh sinusoid
clear
close all
Fvz = 512; % frekvenca vzorcenja
T = 1; % dolzina signala (v sekundah)
i = [0:T*Fvz-1]/Fvz; % casovni trenutki vzorcenja
f1 = 6; % frekvenca prve sinusoide (v Hz) - igrajte se z njeno vrednostjo in jo spreminjajte po korakih 0.1 Hz (med 5 Hz in 7 Hz)
f2 = 5; % frekvenca drugo sinusoide (v Hz)
s1 = sin(2*pi*f1*i);
s2 = sin(2*pi*f2*i);
figure; 
subplot(2,1,1); plot(i,s1); title([num2str(f1) ' Hz']);
subplot(2,1,2); plot(i,s2,'r'); title([num2str(f2) ' Hz']);
xlabel('cas (s)');
ylabel('amplituda');

skalarni_produkt = s1*s2';
display(skalarni_produkt);


%% skalarni produkt dveh RAZLICNIH sinusoid pri RAZLICNIH fazah
clear
close all
Fvz = 512; % frekvenca vzorcenja
T = 1; % dolzina signala (v sekundah)
i = [0:T*Fvz-1]/Fvz; % casovni trenutki vzorcenja
f1 = 5; % frekvenca prve sinusoide (v Hz)
f2 = 6; % frekvenca druge sinusoide (v Hz)
s1 = sin(2*pi*f1*i);
skalarni_produkt = [];
figure; 
for faza = -1:0.05:1; % fazo povecujemo v koraku 0.05pi, od -pi do +pi
    s2 = sin(2*pi*f2*i + faza*pi); 
    subplot(2,1,1); plot(i,s1); title([num2str(f1) ' Hz']);
    subplot(2,1,2); plot(i,s2,'r'); title([num2str(f2) ' Hz, faza = ' num2str(faza) '*pi' ]);
    pause;
    skalarni_produkt(end+1) = s1*s2'; % shranjujemo vrednost skalarnega produkta
end
figure; plot(-1:0.05:1,skalarni_produkt); xlabel('faza (/pi)'); % izrisemo vrednost skalarnega produkta pri razlicnih fazah... 


%% skalarni produkt ob frekvencnem neujemanju - spektralno prepuscanje (Spectral leakage)
% vec o tem v spodnjih zgledih - razlaga na voljo tudi na: https://en.wikipedia.org/wiki/Spectral_leakage
clear
close all
Fvz = 512; % frekvenca vzorcenja
T = 2; % dolzina signala (v sekundah)
i = [0:T*Fvz-1]/Fvz; % casovni trenutki vzorcenja
f1 = 5; faza1=0; %rand;
f2 = 5; faza2=0; %rand;
s1 = sin(2*pi*f1*i + faza1*pi); 
skalarni_produkt = [];
for dfrek = -1:0.001:1;  % frekvencno neujemanje dfrek povecujemo v koraku 0.001 Hz, od -1 Hz do + 1 Hz
    s2 = sin(2*pi*(f2+dfrek)*i + faza2*pi); 
    skalarni_produkt(end+1) = s1*s2';
end
figure; plot(-1:0.001:1,skalarni_produkt); xlabel('frekvencno neujemanje (Hz)'); 
hold on;
plot([-1,1],[0,0],'r');
hold off;


%% skalarni produkt dveh sinusoid z ENAKIMA FREKVENCAMA IN RAZLICNIMA FAZAMA
% pregled kompleksnega stevila
clear
close all
Fvz = 512;
T = 1;
i = [0:T*Fvz-1]/Fvz; % vektor casovnih indeksov
f1 = 5; A1 = 1; 
f2 = 5; faza2 = 0;

figure;
for faza1 = -1:0.05:1  % fazo povecujemo v koraku 0.05pi, od -pi do +pi
    % ustvarimo signal
    x = A1*sin(2*pi*f1*i+faza1*pi);
    % ustvarimo sinusoido
    s1 = A1*sin(2*pi*f2*i+faza2*pi);
  
    Xs1 = s1*x'; % skalarni produkt s sinusoido
        
    subplot(2,1,1);
    plot(i,x);      hold on;  % narisemo prvo 
    plot(i,s1,'r'); hold off; % in se drugo sinusoido  
    xlabel('cas (s)'); ylabel('Amplituda');
    title(['frekvecna = ' num2str(f1) ', faza = ' num2str(faza1) ' \pi' ]); 
    axis tight
    
    subplot(2,1,2);
    plot( [0,0] , [0,Xs1] , 'LineWidth', 2); % narisemo amplitude kosinusov
    xlabel('realna os'); ylabel('imaginarna os');
    axis equal;
    set(gca,'YLim',[-300,300]);
    set(gca,'XLim',[-300,300]);
    title(['frekvecna sin = ' num2str(f2) ', faza2 = ' num2str(faza2) ' \pi' ]);
    pause(0.5);
end


%% skalarni produkt dveh sinusoid z ENAKIMA FREKVENCAMA IN RAZLICNIMA FAZAMA
% analiza s sinusoidami in kosinusoidami
clear
close all
Fvz = 512;
T = 1;
i = [0:T*Fvz-1]/Fvz; % vektor casovnih indeksov
f1 = 5; A1 = 1; 
f2 = 5; faza2 = 0;

figure;
for faza1 = -1:0.05:1
    % ustvarimo signal
    x = A1*sin(2*pi*f1*i+faza1*pi);
    % ustvarimo sinusoido
    s1 = 1*sin(2*pi*f2*i+faza2*pi);
    % ustvarimo kosinusoido
    c1 = 1*cos(2*pi*f2*i+faza2*pi);
    
    Xs1 = s1*x'; % skalarni produkt s sinusoido
    Xc1 = c1*x'; % skalarni produkt s kosinusoido
        
    subplot(2,1,1);
    plot(i,x);      hold on;  % narisemo prvo 
    plot(i,s1,'r'); hold off; % in se drugo sinusoido  
    xlabel('cas (s)'); ylabel('Amplituda');
    title(['frekvecna = ' num2str(f1) ', faza1 = ' num2str(faza1) ' \pi' ]); 
    axis tight
    
    subplot(2,1,2);
    X = fft(x); % FFT!!
    plot( [0,Xc1], [0,Xs1], 'LineWidth', 2 ); % narisemo amplitude kosinusov
    xlabel('x os'); ylabel('y os');
    axis equal;
    set(gca,'YLim',[-300,300]);
    set(gca,'XLim',[-300,300]);
    title(['frekvecna sin in cos = ' num2str(f2) ', faza2 = ' num2str(faza2) ' \pi' ]);
    pause(0.5);
end



%% skalarni produkt dveh sinusoid z ENAKIMA FREKVENCAMA IN RAZLIcNIMA FAZAMA
% komplesna analiza s fft
clear
close all
Fvz = 512;
T = 1;
i = [0:T*Fvz-1]/Fvz; % vektor casovnih indeksov
f1 = 5; A1 = 1; faza1 = 0.5;

figure;
for faza1 = -1:0.05:1
    % ustvarimo sinusiudo
    x = A1*sin(2*pi*f1*i+faza1*pi);
    
    subplot(2,1,1);
    plot(i,x);      hold on;  % narisemo prvo 
    plot(i,s1,'r'); hold off; % in se drugo sinusoido  
    xlabel('cas (s)'); ylabel('Amplituda');
    title(['faza = ' num2str(faza1) ' \pi' ]); 
    axis tight
    
    subplot(2,1,2);
    X = fft(x); % FFT!!
    plot( [0,real(X(f1+1))] , [0,imag(X(f1+1))], 'LineWidth', 2 ); % narisemo amplitude kosinusov
    xlabel('realna os'); ylabel('imaginarna os');
    axis equal;
    set(gca,'YLim',[-300,300])
    set(gca,'XLim',[-300,300])
    
    pause(0.5);
end


%% skalarni produkt dveh sinusoid z ENAKIMA FREKVENCAMA IN RAZLIcNIMA FAZAMA
% komplesna analiza s fft - pogled z druge perspektive (realni in imaginarni del fft-ja)
clear
close all
Fvz = 512;
T = 1;
i = [0:T*Fvz-1]/Fvz; % vektor casovnih indeksov
f1 = 5; A1 = 5; faza1 = 0.5;

figure;
for faza1 = -1:0.05:1
    % ustvarimo sinusiudo
    x = A1*sin(2*pi*f1*i+faza1*pi);
    
    X = fft(x); % FFT!!
    subplot(2,1,1);
    stem(i/T*Fvz,real(X)); % narisemo amplitude kosinusov
    xlabel('Frekvenca (Hz)'); ylabel('Amplituda');
    title(['realni del fft; faza = ' num2str(faza1) ' \pi' ]); axis tight; 
    set(gca,'YLim',[-1500,1500])
    
    subplot(2,1,2);
    stem(i/T*Fvz,imag(X)); % narisemo amplitude sinusov
    xlabel('Frekvenca (Hz)'); ylabel('Amplituda');
    title('imaginarni del fft'); axis tight;axis tight;
    set(gca,'YLim',[-1500,1500])
    
    pause(0.5);
end


%% superpozicija sinusoid, cosinusiode in sinusoide
clear
close all
Fvz = 512;
T = 1;
i = [0:T*Fvz-1]/Fvz; % vektor casovnih indeksov
f1 = 5; A1=5; faza1=0.5;
f2 = 32; A2=3; faza2=0.3;

% ustvarimo superpozicijo sinusoid 
x = A1*sin(2*pi*f1*i+faza1*pi)+A2*sin(2*pi*f2*i+faza2*pi); 

figure;
plot(i,x); % narisemo signal  
xlabel('cas (s)'); ylabel('Amplituda');
axis tight

X = fft(x); % FFT!!

figure;
subplot(2,1,1);
stem(i/T*Fvz,real(X)); % narisemo amplitude kosinusov
xlabel('Frekvenca (Hz)'); ylabel('Amplituda'); 
title('realni del fft'); axis tight;
subplot(2,1,2);
stem(i/T*Fvz,-imag(X)); % narisemo amplitude sinusov
xlabel('Frekvenca (Hz)'); ylabel('Amplituda'); 
title('imaginarni del fft'); axis tight;axis tight;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
figure;
M = abs(X); % dobimo amplitude
P = atan2(imag(X),real(X)); % dobimo faze
stem(i/T*Fvz,M); % Narisemo amplitude. Na X osi so frekvence!!
xlabel('Frekvenca'); ylabel('Amplituda'); 
title('Amplituda fft-ja')
axis tight

% niso vse faze zanimive...
figure;
plot(P); % Narisemo faze. Zaradi racunskih napak je "malo cudna"
title('Faza fft-ja');
axis tight

% le faze tistih sinusoid, ki so dejansko prisotne v signalu
figure
P1 = P.*(M>0.1); % obdrzimo le faze pri tistih frekvencah, ki so vecje od dolocenega praga
stem(i/T*Fvz,P1); % Narisemo faze
xlabel('Frekvenca'); ylabel('Faza');
title('Faza fft-ja');
axis tight

% POJASNILO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% atan2(imag(X),real(X)) vrne faze za enacbo M*sin(x-pi/2+theta), torej moramo ocenjeni fazi pristeti se pi/2; 
%      P = P + pi/2;
% Ne pozabimo tudi, da smo pri generiranju signala x spremenjivko faza2 pomnozili s pi, torej je faza izrazena v enotah pi
% KONEC POJASNILA %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%             L A S T N O S T I   D F T
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% linearnost DFT-ja
x = randn(128,1); % ustvarim signal x 
X = fft(x); % in njegovo frekvencno transformiranko 
y = randn(128,1); % ustvarim signal y
Y = fft(y); % in njegovo frekvencno transformiranko 

a = rand(1); % ustvarimo nakljucne mnozilne faktorje
b = rand(1);

z = a*x + b*y; % signal z je linearna kombinacija signalov x in y
Z = fft(z); % izracunamo DFT signala z

% graficni preizkus linearnosti DFT-ja
figure; 
subplot(2,1,1); hold on
plot(real(Z),'LineWidth',2);
plot(real(a*X+b*Y),'r','LineWidth',1);
xlabel('frekvenca');
ylabel('realni del');
title('fft(a*x + b*y) in a*fft(x) + b*fft(y): primerjava realnih delov')
axis tight
subplot(2,1,2); hold on
plot(imag(Z),'LineWidth',2);
plot(imag(a*X+b*Y),'r','LineWidth',1);
ylabel('imaginarni del');
xlabel('frekvenca');
title('fft(a*x + b*y) in a*fft(x) + b*fft(y): primerjava imaginarnih delov')
axis tight


%% Parsevalov teorem
x=randn(128,1); % ustvarim signal 
X=fft(x); % in njegovo frekvencno transformiranko 
energija_v_t_domeni = x'*x   
energija_v_f_domeni = mean(abs(X).^2)


%% fft in konvoluciija
clear
close all
Fs = 44100; % vzorcevalna frekvenca
bits = 16; % bitna locljivost
T1 = 3; T2 = 2; % dolzina signalov

my_recorder = audiorecorder(Fs,bits,1);

disp(['Snemam prvi posnetek v dolzini ' num2str(T1) 's...']);
recordblocking(my_recorder,T1);
posnetek1 = getaudiodata(my_recorder);

disp(['Snemam drugi posnetek v dolzini ' num2str(T2) 's...']);
recordblocking(my_recorder,T2);
posnetek2 = getaudiodata(my_recorder);

disp('predvajam prvi posnetek')
my_player = audioplayer(posnetek1,Fs);
playblocking(my_player);

disp('predvajam drugi posnetek')
my_player = audioplayer(posnetek2,Fs);
playblocking(my_player);


clc
disp('konvolucija posnetkov v casovnem prostoru')
efekt1 = [];
tic
efekt1(:,1) = conv(posnetek1(:,1),posnetek2(:,1));
t = toc;
efekt1 = efekt1/max(efekt1)*max(posnetek1); % poskrbimo, da ne zasicimo zvocne kartice
disp(['Potrebovali smo "samo" ' num2str(round(t*100)/100) ' s']);

disp(['... in rezultat se slisi takole:']);
my_player = audioplayer(efekt1,Fs);
playblocking(my_player);

disp('konvolucija posnetkov v frekvencnem prostoru')
efekt2 = [];
tic;
X = fft([posnetek1(:,1); zeros(length(posnetek2(:,1))-1,1)]);
Y = fft([posnetek2(:,1); zeros(length(posnetek1(:,1))-1,1)]);
efekt2(:,1) = ifft(X.*Y);
t = toc;
efekt2 = efekt2/max(efekt2)*max(posnetek1); % poskrbimo, da ne zasicimo zvocne kartice
disp(['Potrebovali smo ' num2str(round(t*100)/100) ' s']);

disp(['... in rezultat se slisi takole:']);
my_player = audioplayer(efekt2,Fs);
playblocking(my_player);


%% fft vsebina lastnega zvocnega posnetka
clear
close all

Fs = 44100; % vzorcevalna frekvenca
bits = 16; % bitna locljivost
T1 = 5;

my_recorder = audiorecorder(Fs,bits,1);
 
disp(['Snemam prvi posnetek v dolzini ' num2str(T1) 's...']);
recordblocking(my_recorder,T1);
posnetek = getaudiodata(my_recorder);
 
figure;
plot(posnetek);

X = (fft(posnetek)); % fourijeva transformacija

N = size(posnetek,1);
dF = Fs/N; % hz
f = [dF:dF:Fs/2 Fs/2-dF:-dF:0];

figure;
plot(f,abs(X)/N);
xlabel('Frekvenca (H)');
title('Odziv magnitude');


%% Primeri za STDFT %%

% razmerje med casovno in frekvencno nedoloecenostjo
ai = audioinfo('Sinus.wav');
[sig, Fs] = audioread('Sinus.wav');
disp(['Vzorcevalna frekvenca: ' num2str(Fs) ' Hz']);
disp(['Locljivost audio datoteke: ' num2str(ai.BitsPerSample) ' bitov']);

sound(0.5 * sig,Fs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
T = 512;
N = 512;
[TFD,f,t] = specgram(sig,N,Fs,window(@rectwin,T),0);

figure;
imagesc(t,f,abs(TFD));
axis xy;
xlabel('cas (s)');
ylabel('frekvenca (Hz)');
title(['T=' num2str(T) ',N=' num2str(N)]);
disp(size(TFD));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
T = 1024;
N = 1024;
[TFD,f,t] = specgram(sig,N,Fs,window(@rectwin,T),0);

figure;
imagesc(t,f,abs(TFD));
axis xy;
xlabel('cas (s)');
ylabel('frekvenca (Hz)');
title(['T=' num2str(T) ',N=' num2str(N)]);
disp(size(TFD));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
figure; 
T = [8,32,128,512,1024];
N = [8,32,128,512,1024];
for k1 = 1:length(T)
   for k2 = k1:length(N)
    [TFD,f,t] = specgram(sig,N(k2),Fs,window(@rectwin,T(k1)),0);
    
    subplot(length(T),length(N),(k1-1)*length(N)+k2)
    imagesc(t,f,abs(TFD));
    axis xy;
    set(gca,'XTickLabel',[]);
    set(gca,'YTickLabel',[]);
    %xlabel('t (s)');
    %ylabel('f (Hz)');
    title(['T=' num2str(T(k1)) ',N=' num2str(N(k2))]);
   end
end


%% vpliv prekrivanja casovnih intervalov
close all;
figure; 
T = 512;
N = 512;
dT = [0,T/4,T/2,T-1]
for k1 = 1:length(dT)
    [TFD,f,t] = specgram(sig,N,Fs,window(@rectwin,T),dT(k1));
    subplot(2,2,k1)
    imagesc(t,f,abs(TFD));
    axis xy;
    set(gca,'XTickLabel',[]);
    set(gca,'YTickLabel',[]);
    %xlabel('t (s)');
    %ylabel('f (Hz)');
    title(['T=' num2str(T) ',N=' num2str(N) ',dT=' num2str(dT(k1))]);
end

%% vpliv okna
win = [];
win{end+1} ='@bartlett';       %  - Bartlett window.
win{end+1} ='@barthannwin';    %  - Modified Bartlett-Hanning window. 
win{end+1} ='@blackman';       %  - Blackman window.
win{end+1} ='@blackmanharris'; %  - Minimum 4-term Blackman-Harris window.
win{end+1} ='@bohmanwin';      %  - Bohman window.
win{end+1} ='@chebwin';        %  - Chebyshev window.
win{end+1} ='@flattopwin';     %  - Flat Top window.
win{end+1} ='@gausswin';       %  - Gaussian window.
win{end+1} ='@hamming';        %  - Hamming window.
win{end+1} ='@hann';           %  - Hann window.
win{end+1} ='@kaiser';         %  - Kaiser window.
win{end+1} ='@nuttallwin';     %  - Nuttall defined minimum 4-term Blackman-Harris window.
win{end+1} ='@parzenwin';      %  - Parzen (de la Valle-Poussin) window.
win{end+1} ='@rectwin';        %  - Rectangular window.
win{end+1} ='@tukeywin';       %  - Tukey window.
win{end+1} ='@triang';         %  - Triangular window.

T = 512;
N = 512;
dT = [0];
close all;
ScreenSize = get(0,'ScreenSize');
for k1 = 1:length(win)/3
    figure;
    set(gcf,'Position',ScreenSize);
    for k2 = 1:3
        
        subplot(3,3,(k2-1)*3+1);
        plot(window(eval(win{(k1-1)*3+k2}),T));
        xlabel('t (s)');
        axis tight;
        title([win{(k1-1)*3+k2}]);
        
        subplot(3,3,(k2-1)*3+2);
        tmp = abs(fft(window(eval(win{(k1-1)*3+k2}),T),N));
        stem(tmp(1:20));
        xlabel('f (Hz)');
        axis tight;
        set(gca,'Xlim',[0,20]);
        title([win{(k1-1)*3+k2}]);
        
        [TFD,f,t] = specgram(sig,N,Fs,window(eval(win{(k1-1)*3+k2}),T),dT);
        subplot(3,3,(k2-1)*3+3);
        imagesc(t,f,abs(TFD));
        axis xy;
%         set(gca,'XTickLabel',[]);
%         set(gca,'YTickLabel',[]);
        xlabel('t (s)');
        ylabel('f (Hz)');
        title([win{(k1-1)*3+k2}]);
    end
    pause;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure;
subplot(2,1,1); hold on; 
plot(window(@gausswin,T),'LineWidth',2); 
plot(window(@hamming,T),'r','LineWidth',2);
plot(window(@rectwin,T),'g','LineWidth',2);
xlabel('t (s)');
axis tight;
legend('Gauss','Hamming')

subplot(2,1,2); hold on; 
tmp = abs(fft(window(@gausswin,T),N));
stem(tmp(1:20),'LineWidth',2);
tmp = abs(fft(window(@hamming,T),N));
stem(tmp(1:20),'r','LineWidth',2);
tmp = abs(fft(window(@rectwin,T),N));
stem(tmp(1:20),'g','LineWidth',2);
xlabel('f (Hz)');
axis tight;
legend('Gauss','Hamming')


%% vpliv okna 2 - okno aplicirano na celotni signal
win = [];
win{end+1} ='@bartlett';       %  - Bartlett window.
win{end+1} ='@barthannwin';    %  - Modified Bartlett-Hanning window. 
win{end+1} ='@blackman';       %  - Blackman window.
win{end+1} ='@blackmanharris'; %  - Minimum 4-term Blackman-Harris window.
win{end+1} ='@bohmanwin';      %  - Bohman window.
win{end+1} ='@chebwin';        %  - Chebyshev window.
win{end+1} ='@flattopwin';     %  - Flat Top window.
win{end+1} ='@gausswin';       %  - Gaussian window.
win{end+1} ='@hamming';        %  - Hamming window.
win{end+1} ='@hann';           %  - Hann window.
win{end+1} ='@kaiser';         %  - Kaiser window.
win{end+1} ='@nuttallwin';     %  - Nuttall defined minimum 4-term Blackman-Harris window.
win{end+1} ='@parzenwin';      %  - Parzen (de la Valle-Poussin) window.
win{end+1} ='@rectwin';        %  - Rectangular window.
win{end+1} ='@tukeywin';       %  - Tukey window.
win{end+1} ='@triang';         %  - Triangular window.

T = 128;
N = 512;
Nstem = 100;
dT = [0]
close all;
ScreenSize = get(0,'ScreenSize')
for k1 = 1:length(win)/3
    figure;
    set(gcf,'Position',ScreenSize);
    for k2 = 1:3
        
        tmpWin = [zeros(T,1); window(eval(win{(k1-1)*3+k2}),T); zeros(T,1)];
        
        subplot(3,3,(k2-1)*3+1);
        plot(tmpWin);
        xlabel('t (s)');
        axis tight;
        title([win{(k1-1)*3+k2}]);
        
        subplot(3,3,(k2-1)*3+2);
        tmp = abs(fft(tmpWin));
        stem(tmp(1:Nstem));
        xlabel('f (Hz)');
        axis tight;
        set(gca,'Xlim',[0,Nstem]);
        title([win{(k1-1)*3+k2}]);
        
        [TFD,f,t] = specgram(sig,N,Fs,tmpWin,dT);
        subplot(3,3,(k2-1)*3+3);
        imagesc(t,f,abs(TFD));
        axis xy;
%         set(gca,'XTickLabel',[]);
%         set(gca,'YTickLabel',[]);
        xlabel('t (s)');
        ylabel('f (Hz)');
        title([win{(k1-1)*3+k2}]);
    end
end


%% bolj realisticem primer casovno-frekvencne analize
ai = audioinfo('Zvizganje.wav');
[sig, Fs] = audioread('Zvizganje.wav');
%[sig, Fs] = audioread('Zvizganje2.wav');

sig = sig(:,1); % stereo posnetek - vzamemo samo 1 kanal

disp(['Vzorcevalna frekvenca: ' num2str(Fs) ' Hz']);
disp(['Locljivost audio datoteke: ' num2str(ai.BitsPerSample) ' bitov']);

sound(0.5 * sig,Fs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all

T = 30;
N = 512;
dT = T/2;
[TFD,f,t] = specgram(sig,N,Fs,window(@hamming,T),dT);
figure; 
mesh(t,f,abs(TFD)); axis tight;
axis tight;
title(['T=' num2str(T) ',N=' num2str(N) ',dT=' num2str(dT)]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
T = 512;
N = 512;
dT = T/2;
[TFD,f,t] = specgram(sig,N,Fs,window(@hamming,T),dT);
figure; 
mesh(t,f,abs(TFD)); axis tight;
axis tight;
title(['T=' num2str(T) ',N=' num2str(N) ',dT=' num2str(dT)]);


%% primer elektricne kitare   (https://ccrma.stanford.edu/~jos/waveguide/Sound_Examples.html)
ai = audioinfo('ElectricGuitar.wav');
[sig, Fs] = audioread('ElectricGuitar.wav');
%ai = audioinfo('gtr-dist-yes.wav');
%[sig, Fs] = audioread('gtr-dist-yes.wav');

sig = sig(:,1); % stereo signal - vzamemo samo 1 kanal

disp(['Vzorcevalna frekvenca: ' num2str(Fs) ' Hz']);
disp(['Locljivost audio datoteke: ' num2str(ai.BitsPerSample) ' bitov']);

sound(0.5 * sig,Fs);

close all
T = 1024;
N = 1024;
dT = T/2;
[TFD,f,t] = specgram(sig,N,Fs,window(@hamming,T),dT);
imagesc(t,f/1000,abs(TFD)); axis xy;
xlabel('cas (s)'); ylabel('f (kHz)');
axis tight;
title(['T=' num2str(T) ',N=' num2str(N) ',dT=' num2str(dT)]);

%% primer lastnega zvocnega posnetka
clc;
clear;
close all
Fs = 44100; % vzorcevalna frekvenca
bits = 16; % bitna locljivost
T1 = 5;

my_recorder = audiorecorder(Fs,bits,1);

disp(['Snemam posnetek dolzine ' num2str(T1) 's...']);
recordblocking(my_recorder, T1);
sig = getaudiodata(my_recorder);

disp('predvajam prvi posnetek')
my_player = audioplayer(sig,Fs);
playblocking(my_player);

T = 512;
N = 512;
dT = T/2;
[TFD,f,t] = specgram(sig,N,Fs,window(@hamming,T),dT);
figure; 
% mesh(t,f/1000,abs(TFD)); axis tight;
% xlabel('cas (s)'); ylabel('f (kHz)'); zlabel('amplituda')
imagesc(t,f/1000,abs(TFD)); axis xy;
xlabel('cas (s)'); ylabel('f (kHz)')
axis tight;
title(['T=' num2str(T) ',N=' num2str(N) ',dT=' num2str(dT)]);
