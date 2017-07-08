#include <stdint.h>
#include "pid.h"

/**
 * A basic PID controller. All integer operation using 9.7 fixed point.
 * Input and output may range between -16,383 to 16,383.
 */

// bits=7
#define PID_SCALE  128

// Maximum value of variables
#define PID_MAX_P            INT16_MAX

#define PID_MAX_INT         INT16_MAX
#define PID_MAX_LONG        INT32_MAX
#define PID_MAX_I_TERM      (PID_MAX_LONG / 2)

/**
 * Initializes a PID controller.
 *
 * @param pid pointer to a pid structure
 * @param p_factor the proportional factor
 * @param i_factor the integral factor
 * @param d_factor the derivitive factor
 */
void pid_init(pid_data_t *pid, float p_factor, float i_factor, float d_factor) {
    pid->sum_error = 0;
    pid->last_measured = 0;
    pid->p_factor = (int16_t) (p_factor * PID_SCALE);
    pid->i_factor = (int16_t) (i_factor * PID_SCALE);
    pid->d_factor = (int16_t) (d_factor * PID_SCALE);
    pid->max_error = INT16_MAX / (pid->p_factor + 1);
    pid->max_sum_error = (INT32_MAX / 2) / (pid->i_factor + 1);
}

/**
 * Updates the control state. This method should be run at a regular interval
 * to update the control output. It can be called to update as frequently as
 * desired, but the interval must not change.
 *
 * Target and measured values should not exceed +/- 16,383 to avoid overflow.
 *
 * @param pid the control parameters and running state
 * @param target the target for the measured value
 * @param measured the actual measured value
 */
int16_t pid_update(pid_data_t *pid, int16_t target, int16_t measured) {
    int16_t p, d;
    int32_t i;

    clamp(target, INT16_MAX / 2, INT16_MIN / 2);
    clamp(measured, INT16_MAX / 2, INT16_MIN / 2);
    int16_t error = target - measured;

    // Compute proportional
    if (error > pid->max_error) {
        p = INT16_MAX;
    } else if (error < -pid->max_error) {
        p = INT16_MIN;
    } else {
        p = pid->p_factor * error;
    }

    // Compute integral
    int32_t sum = pid->sum_error + error;
    if (sum > pid->max_sum_error) {
        pid->sum_error = pid->max_sum_error;
        i = INT32_MAX / 2;
    } else if (sum < -pid->max_sum_error) {
        pid->sum_error = -pid->max_sum_error;
        i = INT32_MIN / 2;
    } else {
        pid->sum_error = sum;
        i = pid->i_factor * pid->sum_error;
    }

    // Compute derivative
    d = pid->d_factor * (pid->last_measured - measured);
    pid->last_measured = measured;

    int32_t result = (p + i + d) / PID_SCALE;
    return (int16_t) clamp(result, INT16_MIN, INT16_MAX);
}
