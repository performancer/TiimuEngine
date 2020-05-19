#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

#include "AL/al.h"
#include "AL/alc.h"

#include "../io/wave.h"

#define TEST_ERROR(_msg)		\
	error = alGetError();		\
	if (error != AL_NO_ERROR) {	\
		fprintf(stderr, _msg "\n");	\
		return -1;		\
	}

static unsigned int to_al_format(unsigned short channels, unsigned short bits_per_sample) {
	if (channels == 1)
	{
		if (bits_per_sample == 8)
			return AL_FORMAT_MONO8;
		else
			return AL_FORMAT_MONO16;
	}
	else {
		if (bits_per_sample == 8)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_STEREO16;
	}

	return -1;
}

static ALCdevice* device;
static ALCcontext* context;

int audio_initialize() {
	ALCenum error;

	ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

	if (enumeration == AL_FALSE)
		fprintf(stderr, "enumeration extension not available\n");

	const char* defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	device = alcOpenDevice(defaultDeviceName);
	if (!device) {
		fprintf(stderr, "unable to open default device\n");
		return -1;
	}

	fprintf(stdout, "Device: %s\n", alcGetString(device, ALC_DEVICE_SPECIFIER));

	alGetError();

	context = alcCreateContext(device, NULL);

	if (!alcMakeContextCurrent(context)) {
		fprintf(stderr, "failed to make default context\n");
		return -1;
	}

	TEST_ERROR("make default context");

	/* set orientation */
	alListener3f(AL_POSITION, 0, 0, 1.0f);
	TEST_ERROR("listener position");
	alListener3f(AL_VELOCITY, 0, 0, 0);
	TEST_ERROR("listener velocity");
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListenerfv(AL_ORIENTATION, listenerOri);
	TEST_ERROR("listener orientation");

	return 0;
}

int audio_play(const char* path) {
	if (path == NULL)
		return -1;

	ALCenum error;
	ALuint buffer, source;

	alGenSources((ALuint)1, &source);
	TEST_ERROR("source generation");

	alSourcef(source, AL_PITCH, 1);
	TEST_ERROR("source pitch");
	alSourcef(source, AL_GAIN, 1);
	TEST_ERROR("source gain");
	alSource3f(source, AL_POSITION, 0, 0, 0);
	TEST_ERROR("source position");
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	TEST_ERROR("source velocity");
	alSourcei(source, AL_LOOPING, AL_FALSE);
	TEST_ERROR("source looping");

	alGenBuffers(1, &buffer);
	TEST_ERROR("buffer generation");
	
	struct WAVFILEHEADER header;
	char* data = wav_load(path, &header);

	unsigned int format = to_al_format(header.channels, header.bits_per_sample);

	alBufferData(buffer, format, data, header.data_size, header.sample_rate);
	TEST_ERROR("buffer copy");

	alSourcei(source, AL_BUFFER, buffer);
	TEST_ERROR("buffer binding");

	alSourcePlay(source);
	TEST_ERROR("source playing");

	/*
	ALint source_state;
	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	TEST_ERROR("source state get");

	while (source_state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
		TEST_ERROR("source state get");
	}

	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);*/

	return 0;
}