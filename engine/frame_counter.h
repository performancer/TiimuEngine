#ifndef _FRAME_COUNTER_H_
#define _FRAME_COUNTER_H_

#ifdef __cplusplus
extern "C"
{
#endif

	double frame_counter_fps();
	void frame_counter_update(double delta);

#ifdef __cplusplus
}
#endif 

#endif