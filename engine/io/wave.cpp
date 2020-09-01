#include "wave.h"
#include <stdio.h>
#include <stdlib.h>

void wav_print(struct WAVFILEHEADER header) {
	printf("(1-4): %s \n", header.riff);
	printf("(5-8) Overall size: bytes:%u, Kb:%u \n", header.overall_size, header.overall_size / 1024);
	printf("(9-12) Wave marker: %s\n", header.wave);
	printf("(13-16) Fmt marker: %s\n", header.fmt_chunk_marker);
	printf("(17-20) Length of Fmt header: %u \n", header.length_of_fmt);
	printf("(21-22) Format type: %u \n", header.format);
	printf("(23-24) Channels: %u \n", header.channels);
	printf("(25-28) Sample rate: %u\n", header.sample_rate);
	printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", header.byte_rate, header.byte_rate * 8);
	printf("(33-34) Block Alignment: %u \n", header.block_align);
	printf("(35-36) Bits per sample: %u \n", header.bits_per_sample);
	printf("(37-40) Data Marker: %s \n", header.data_chunk_header);
	printf("(41-44) Size of data chunk: %u \n", header.data_size);
}

char* wav_load(const char* path, struct WAVFILEHEADER* header) {
	FILE* filePtr = fopen(path, "rb");

	if (filePtr == NULL)
		return NULL;

	fread(header, sizeof(struct WAVFILEHEADER), 1, filePtr);

	char* data = (char*)malloc(header->data_size * sizeof(char));
	fread(data, header->data_size * sizeof(char), 1, filePtr);
	fclose(filePtr);

	return data;
}