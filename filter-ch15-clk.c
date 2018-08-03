#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	uint16_t sample;
	uint16_t sig;
	uint8_t clk;
	uint8_t oldclk;
	//uint16_t tmp;
	while (1) {
		int r = fread(&sample, 2, 1, stdin);
		if (r<0) {
			perror("stdin");
			return 1;
		} else if (r==0) {
			// eof
			return 0;
		}
		//printf("[%x]\n",sample);
		//mask out the 15th bit as the clk
		clk = sample>>15;
		//left shift to take out the msb then rescale
		sig = (sample<<1)>>1;
		if (!oldclk && clk) {
			fwrite(&sample, 2, 1, stdout);
		}
		oldclk=clk;
	}
}
