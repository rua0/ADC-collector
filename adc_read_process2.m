% close all; 
% clear all;

Fs = 250000;%\exp1_online\pi2
fileID = fopen(fullfile([pwd '\0820\exp1\pi1'],'0010'));%mydata23%raw_unflipped
A = fread(fileID, 'int16');

for i=1:1:length(A)
   if A(i)>bitsll(1,14)
%        A(i)=bitor(A(i),bitsll(1,16));
        A(i)=A(i)-bitsll(1,15);
   end
end

% A=bitand(A,32767);
figure(4);clf
plot(A); 

L = length(A);
time = (0:(L-1))*(1/Fs);

% FFTA = fft(A); fftshift(FFTA);
% 
% P2 = abs(FFTA/L);
% P1 = P2(1:L/2+1);
% P1(2:end-1) = 2*P1(2:end-1);
% f = Fs*(0:(L/2))/L;
% figure(2);clf
% plot(f, P1);
% title('Single-Sided Amplitude Spectrum of Output of ADC')
% xlabel('f (Hz)')
% ylabel('magnitude')

figure(5);clf
B=A./(2^15-1).*10;
plot(time,B);

% 
% decimal = decimal/(2^16);

% 
% % concat all rows next to each other
% % find the number in decimal
% % divide that by the max it can be 2^16
% % multiply by (Vmax-Vmin)