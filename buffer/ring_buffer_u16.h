#ifndef RING_BUFFER_U16_H_
#define RING_BUFFER_U16_H_

#include <stdint.h>

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t mask;
    uint16_t *data;
} rb_u16_t;

#define RB_DECL_U16_7(Name) uint16_t Name_##data[8]; rb_u16_t Name = {0, 0, 0x07, Name_##data};
#define RB_DECL_U16_15(Name) uint16_t Name_##data[16]; rb_u16_t Name = {0, 0, 0x0f, Name_##data}
#define RB_DECL_U16_31(Name) uint16_t Name_##data[32]; rb_u16_t Name = {0, 0, 0x1f, Name_##data}
#define RB_DECL_U16_63(Name) uint16_t Name_##data[64]; rb_u16_t Name = {0, 0, 0x3f, Name_##data}
#define RB_DECL_U16_127(Name) uint16_t Name_##data[128]; rb_u16_t Name = {0, 0, 0x7f, Name_##data}
#define RB_DECL_U16_255(Name) uint16_t Name_##data[256]; rb_u16_t Name = {0, 0, 0xff, Name_##data}

void rb_add_u16(rb_u16_t *p, uint16_t val);                
uint16_t rb_remove_u16(rb_u16_t *p);                        
uint8_t rb_size_u16(rb_u16_t *p);
uint8_t rb_capacity_u16(rb_u16_t *p);
uint16_t rb_peek_u16(rb_u16_t *p);
void rb_clear_u16(rb_u16_t *p);

#endif
