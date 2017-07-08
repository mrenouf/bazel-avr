/*
 * usb_log.h
 *
 *  Created on: Aug 27, 2012
 *      Author: mrenouf
 */

#ifndef USB_LOG_H_
#define USB_LOG_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "usb_serial.h"

#ifndef USB_LOG_MAX_LEN
#define USB_LOG_MAX_LEN  32
#endif

void usb_log(const char *__fmt, ...);


#endif /* USB_LOG_H_ */
