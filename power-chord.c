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

	const int duration_seconds = 10;
	const int buffer_size = sample_rate * duration_seconds;

	wavh.dlength = buffer_size * wavh.bytes_per_sample;
	wavh.flength = wavh.dlength + 44;

	short int buffer[buffer_size] = {};

	for (int i = 0; i < buffer_size; i++) {
		short int a_440 = 440.0;
		short int wave_a = cos((2 * M_PI * a_440 * i) / sample_rate) * 5000;
		short int wave_b = cos((2 * M_PI * (a_440 / 2) * i) / sample_rate) * 5000;
		short int wave_c = cos((2 * M_PI * (a_440 * 3 / 2) * i) / sample_rate) * 5000;
		short int waveform = wave_a + wave_b + wave_c;
		buffer[i] = waveform; // This is where the music is made
	};
	
	FILE *fp = fopen("test-power-chord.wav", "w");
	fwrite(&wavh, 1, sizeof(wavh), fp);
	fwrite(buffer, 2, buffer_size, fp);


	return 0;	
}


