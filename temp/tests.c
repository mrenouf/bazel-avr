
#include <stdio.h>
#include "byte_buffer.h"
#include "pid.h"
#include "macros.h"

static pid_data_t pid;

double prev_value = 0;
double curr_value = 0;
double value[5] = {0, 0, 0, 0, 0};

#define DECAY 0.95

void update(int control) {
        value[3] = clamp(value[2] * DECAY,0,control);
        value[2] = clamp(value[1] * DECAY,0,control);
        value[1] = clamp(value[0] * DECAY,0,control);
        value[0] = control * 0.2;
        curr_value += (value[0] + value[1] + value[2] + value[3]) / 4.0;
        curr_value *= DECAY;
}

void run_tests() {
    pid_init(&pid, 0.5, 0.05, 0.02);
    int16_t control = 0;
    printf("target\tcontrol\tmeasured\n");
    for (int i = 20; i < 150; i+=2) {
        update(control);
        control = pid_update(&pid, i, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", i, control, curr_value);
    }
    for (int i = 150; i < 180; i++) {
        update(control);
        control = pid_update(&pid, i, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", i, control, curr_value);
        update(control);
        control = pid_update(&pid, i, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", i, control, curr_value);
        update(control);
        control = pid_update(&pid, i, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", i, control, curr_value);
    }
    for (int i = 180; i < 235; i+=4) {
        update(control);
        control = pid_update(&pid, i, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", i, control, curr_value);
    }
    for (int i = 0; i < 50; i++) {
        update(control);
        control = pid_update(&pid, 235, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", 235, control, curr_value);
    }
    for (int i = 0; i < 100; i+=1) {
        update(control);
        control = pid_update(&pid, 20, curr_value);
        control = (control < 0 ? 0 : control);
        printf("%d\t%d\t%1.1f\n", 0, control, curr_value);
    }
}
