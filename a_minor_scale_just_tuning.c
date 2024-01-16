#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

struct wav_header {
	char riff[4];
	int32_t flength;
	char wave[4];
	char fmt[4];
	int32_t chunk_size;
	int16_t format_tag;
	int16_t num_chans;
	int32_t sample_rate;
	int32_t bytes_per_second;
	int16_t bytes_per_sample;
	int16_t bits_per_sample;
	char data[4];
	int32_t dlength;
};

int main() {
	const int sample_rate = 8000;

	struct wav_header wavh;

	strncpy(wavh.riff, "RIFF", 4);
	strncpy(wavh.wave, "WAVE", 4);
	strncpy(wavh.fmt, "fmt ", 4);
	strncpy(wavh.data, "data", 4);

	wavh.chunk_size = 16;
	wavh.format_tag = 1;
	wavh.num_chans = 1;
	wavh.sample_rate = sample_rate;
	wavh.bits_per_sample = 16;
	wavh.bytes_per_sample = (wavh.bits_per_sample / 8) * wavh.num_chans;
	wavh.bytes_per_second = sample_rate * wavh.bits_per_sample;

	const int duration_seconds = 8;
	const int buffer_size = sample_rate * duration_seconds;

	wavh.dlength = buffer_size * wavh.bytes_per_sample;
	wavh.flength = wavh.dlength + 44;

	short int buffer[buffer_size] = {};
	
	// A minor scale: A, B, C, D, E, F, G, A.
	// Ratios for Just Intonation: 1:1, 9:8, 6:5, 4:3, 3:2, 8:5, 9:5, 2:1.
	for (int i = 0; i < buffer_size; i++) {
		if (i <= (sample_rate * 1)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * i) / sample_rate) * 5000);
		}
		else if (i <= (sample_rate * 2)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (9 / 8) * i) / sample_rate) * 5000);
		}
		else if (i <= (sample_rate * 3)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (6 / 5) * i) / sample_rate) * 5000);
		}
		else if (i <= (sample_rate * 4)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (4 / 3) * i) / sample_rate) * 5000);
		}
		else if (i <= (sample_rate * 5)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (3 / 2) * i) / sample_rate) * 5000);
		}
		else if (i <= (sample_rate * 6)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (8 / 5) * i) / sample_rate) * 5000);
		}
		else if (i <= (sample_rate * 7)) {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (9 / 5) * i) / sample_rate) * 5000);
		}
		else {
			buffer[i] = (short int)(cos((2 * M_PI * 440.0 * (2 / 1) * i) / sample_rate) * 5000);
		}
	}
	
	FILE *fp = fopen("a_minor_scale_just_intonation.wav", "w");
	fwrite(&wavh, 1, sizeof(wavh), fp);
	fwrite(buffer, 2, buffer_size, fp);


	return 0;	
}


