/*
 * usb_log.c
 *
 *  Created on: Aug 27, 2012
 *      Author: mrenouf
 */

#ifdef USB

#include "usb_log.h"

static char __usb_log_buffer[USB_LOG_MAX_LEN];

void usb_log(const char *__fmt, ...) {
  va_list arguments;
  va_start( arguments, __fmt);
  if (!(usb_serial_get_control() & USB_SERIAL_DTR)) {
    // nobody is listening :-(
    return;
  }
  vsnprintf(__usb_log_buffer, USB_LOG_MAX_LEN, __fmt, arguments);
  va_end(arguments);
  usb_serial_flush_input();
  usb_serial_write((uint8_t *) __usb_log_buffer, strlen(__usb_log_buffer));
  usb_serial_flush_output();
}
#endif
