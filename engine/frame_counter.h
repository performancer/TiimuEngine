#ifndef _FRAME_COUNTER_H_
#define _FRAME_COUNTER_H_

#ifdef __cplusplus
extern "C"
{
#endif

	float frame_counter_fps();
	float frame_counter_update(float delta);

#ifdef __cplusplus
}
#endif 

#endif