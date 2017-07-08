#ifndef PID_H_
#define PID_H_

#include <stdint.h>

#define clamp(value, min, max) (((value) < min) ? min : ((value) > max) ? max : (value))

typedef struct {
    int16_t last_measured;
    int32_t sum_error;
    int16_t p_factor;
    int16_t i_factor;
    int16_t d_factor;
    int16_t max_error;
    int32_t max_sum_error;
} pid_data_t;

void pid_init(pid_data_t *pid, float p_factor, float i_factor, float d_factor);

int16_t pid_update(pid_data_t *pid, int16_t target, int16_t measured);

#endif /* PID_H_ */
