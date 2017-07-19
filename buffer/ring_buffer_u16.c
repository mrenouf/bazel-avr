#include "buffer/ring_buffer_u16.h"

void rb_add_u16(rb_u16_t *p, uint16_t val) {
  p->data[p->head] = val;                               
  p->head++;                                            
  p->head &= p->mask;                                   
  if (p->head == p->tail) {                             
    p->tail++;                                          
    p->tail &= p->mask;                                 
  }                                                     
}                                                       

uint16_t rb_remove_u16(rb_u16_t *p) {
  if (p->tail == p->head) {                             
    return 0;                                    
  }                                                     
  uint16_t value = p->data[p->tail];                        
  p->tail++;                                            
  p->tail &= p->mask;                                   
  return value;                                         
}                                                        

uint8_t rb_size_u16(rb_u16_t *p) {           
  return ((p->head + p->mask + 1) - p->tail) & p->mask;
}                                                       

uint8_t rb_capacity_u16(rb_u16_t *p) {
  return p->mask;
}                                                       

uint16_t rb_peek_u16(rb_u16_t *p) {
  if (p->tail == p->head) {
    return 0;
  }
  return p->data[p->tail];
}

void rb_clear_u16(rb_u16_t *p) {
  p->tail = p->head;
}

