#ifndef RING_BUFFER_U8_H_
#define RING_BUFFER_U8_H_

#include <stdint.h>

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t mask;
    uint8_t *data;
} rb_u8_t;

#define RB_DECL_U8_7(Name) uint8_t Name_##data[8]; rb_u8_t Name = {0, 0, 0x07, Name_##data};
#define RB_DECL_U8_15(Name) uint8_t Name_##data[16]; rb_u8_t Name = {0, 0, 0x0f, Name_##data}
#define RB_DECL_U8_31(Name) uint8_t Name_##data[32]; rb_u8_t Name = {0, 0, 0x1f, Name_##data}
#define RB_DECL_U8_63(Name) uint8_t Name_##data[64]; rb_u8_t Name = {0, 0, 0x3f, Name_##data}
#define RB_DECL_U8_127(Name) uint8_t Name_##data[128]; rb_u8_t Name = {0, 0, 0x7f, Name_##data}
#define RB_DECL_U8_255(Name) uint8_t Name_##data[256]; rb_u8_t Name = {0, 0, 0xff, Name_##data}

void rb_add_u8(rb_u8_t *p, uint8_t val);                
uint8_t rb_remove_u8(rb_u8_t *p);                        
uint8_t rb_size_u8(rb_u8_t *p);
uint8_t rb_full_u8(rb_u8_t *p);
uint8_t rb_capacity_u8(rb_u8_t *p);
uint8_t rb_peek_u8(rb_u8_t *p);
void rb_clear_u8(rb_u8_t *p);

#endif
