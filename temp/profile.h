/*
 * profile.h
 *
 *  Created on: Jun 9, 2015
 *      Author: mrenouf
 */

#ifndef PROFILE_H_
#define PROFILE_H_

#include <stdint.h>

// PREHEAT:  increase temp to SOAK_START temp over PREHEAT_TIME
// SOAK:     increase temp to SOAK_END over SOAK_TIME
// RAMP:     increase to PEAK_TEMP over RAMP_TIME
// PEAK:     hold at PEAK_TEMP for PEAK_HOLD sec
// COOLDOWN: reduce temp to ambient

typedef struct {
	float jct;
	float ref;
	uint8_t fault;
	uint8_t scv;
	uint8_t scg;
	uint8_t oc;
} therm_t;

typedef struct {
	const char *name;
	uint16_t liquidous_temp; // 183C

	// control values
	uint16_t preheat_time;    // 30s, max 4C/s
	uint16_t soak_time;	      // 100s, max 0.5C/s
	uint16_t soak_temp_start; // 100C
	uint16_t soak_temp_end;   // 150C
    uint16_t ramp_time;       // 30s, max 4C/s
	uint16_t peak_temp;       // 235C
    uint16_t peak_hold;       // 10-30s
} profile_t;

typedef enum {
	STAGE_PREHEAT = 0,
    STAGE_SOAK = 1,
    STAGE_RAMP = 2,
    STAGE_PEAK = 3,
    STAGE_COOL = 4
} stage_enum;

// Sn/Pb 63/37 Reflow Profile
static profile_t TEST_PROFILE = {
		.name 				= "Generic - Sn/Pb 63/37",
		.liquidous_temp 	= 183,
		.preheat_time 		= 30,
		.soak_time 			= 100,
		.soak_temp_start 	= 100,
		.soak_temp_end 		= 150,
		.ramp_time 			= 30,
		.peak_temp 			= 235,
		.peak_hold 			= 30,
};

int16_t profile_target_temp(const profile_t *profile, uint16_t time_seconds);

#endif /* PROFILE_H_ */
