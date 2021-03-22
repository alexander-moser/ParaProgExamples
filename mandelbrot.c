#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	for(int i = 0; i < X; i++) {
		for(int j = 0; j < Y; j++) {
			float x = 0.0;
			float y = 0.0;
			float cx = ((3.5f * i) / X) - 2.5f;
			float cy = ((2.0f * j) / Y) - 1;
			int iteration = 0;
			while(x * x + y * y <= 2 * 2 && iteration < MAX_ITER) {
				float x_tmp = x * x - y * y + cx;
				y = 2 * x * y + cy;
				x = x_tmp;
				iteration = iteration + 1;
			}
			int norm_iteration = iteration - 250;
			image[j][i] = norm_iteration;
		}
	}
}

int main() {
	clock_t start = clock();

	uint8_t image[Y][X];

	calc_mandelbrot(image);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);

	clock_t end = clock();

	printf("%f seconds\n", (float)(end - start) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}