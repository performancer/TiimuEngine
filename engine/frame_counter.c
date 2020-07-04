#define sample_count 5

float _samples[sample_count];
float _average;

float frame_counter_fps()
{
	return _average;
}

void frame_counter_update(float delta)
{
	float current = 1 / delta;

	for (int i = sample_count - 1; i > 0; i--)
		_samples[i] = _samples[i - 1];

	_samples[0] = current;

	_average = 0;

	for (int i = 0; i < sample_count; i++)
		_average += _samples[i];

	_average /= sample_count;
}