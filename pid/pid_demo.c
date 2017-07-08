#include <stdio.h>
#include "pid/pid.h"


pid_data_t pid;

float avg(float t) {
	static float t1 = 0;
	static float t2 = 0;
	static float t3 = 0;
	static float t4 = 0;

	float r = t + t1 + t2 + t3 + t4;
	r /= 5.0;
	t4 = t3;
	t3 = t2;
	t2 = t1;
	t1 = t;
	return r;
}

int main() {
  int16_t target_value = PID_FIXED(10);
  int16_t measure_value = 0;
  int16_t control_output = 0;

  pid_init(&pid, 1.3f, 0.59f, 0.8f);

  for (int i = 0; i < 50; i++) {
    measure_value = avg(PID_FLOAT(control_output)) * PID_SCALE;
    control_output = pid_update(&pid, target_value, measure_value);
    printf("%f\t%f\t%f\n", PID_FLOAT(target_value), PID_FLOAT(measure_value), PID_FLOAT(control_output));   
  }

  target_value = PID_FIXED(20);

  for (int i = 0; i < 50; i++) {
    measure_value = avg(PID_FLOAT(control_output)) * PID_SCALE;
    control_output = pid_update(&pid, target_value, measure_value);
    printf("%f\t%f\t%f\n", PID_FLOAT(target_value), PID_FLOAT(measure_value), PID_FLOAT(control_output));   
    target_value += 32;
  }

  
  target_value = PID_FIXED(50);
  
  for (int i = 0; i < 50; i++) {
    measure_value = avg(PID_FLOAT(control_output)) * PID_SCALE;
    control_output = pid_update(&pid, target_value, measure_value);
    printf("%f\t%f\t%f\n", PID_FLOAT(target_value), PID_FLOAT(measure_value), PID_FLOAT(control_output));   
  }

}
