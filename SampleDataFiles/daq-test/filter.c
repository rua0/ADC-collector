#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	uint16_t sample;
	uint16_t sig;
	uint8_t clk;
	uint8_t oldclk;
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
		clk = sample&1;
		sig = sample>>1;
		if (!oldclk && clk) {
			fwrite(&sample, 2, 1, stdout);
		}
		oldclk=clk;
	}
}
