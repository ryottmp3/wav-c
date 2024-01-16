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

	const int duration_seconds = 5;
	const int buffer_size = sample_rate * duration_seconds;

	wavh.dlength = buffer_size * wavh.bytes_per_sample;
	wavh.flength = wavh.dlength + 44;

	short int buffer[buffer_size] = {};

	// Am7#13: A, E, A, C, G, D#
	// am7#13: 
	for (int i = 0; i < buffer_size; i++) {
		short int a_440 = 440.0; // A_440 Hz
		short int wave_a = cos((2 * M_PI * a_440 * i) / sample_rate) * 5000; // A (1st)
		short int wave_b = cos((2 * M_PI * (a_440 / 2) * i) / sample_rate) * 5000; // A (8th)
		short int wave_c = cos((2 * M_PI * (a_440 * 3 / 4) * i) / sample_rate) * 5000; // E (5th)
		short int wave_d = cos((2 * M_PI * (a_440 * 32 / 27) * i) / sample_rate) * 5000; // C (m3rd)
		short int wave_e = cos((2 * M_PI * (a_440 * 16 / 9) * i) / sample_rate) * 5000; // G (m7th)
		short int wave_f = cos((2 * M_PI * (a_440 * 729 / 256) * i) / sample_rate) * 5000; // D# (aug13th)
		short int waveform = wave_a + wave_b + wave_c + wave_d + wave_e + wave_f;
		buffer[i] = waveform; // This is where the music is made
	};
	
	FILE *fp = fopen("a-minor-seventh-augmented-thirteenth.wav", "w");
	fwrite(&wavh, 1, sizeof(wavh), fp);
	fwrite(buffer, 2, buffer_size, fp);


	return 0;	
}


