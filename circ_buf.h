
#include "stdint.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
  uint8_t *buf; // data buffer
  uint32_t size; // total size
  uint32_t head; // write index
  uint32_t tail; // read index
  uint32_t count; // number of bytes currently stored
} circbuf_t;

void circbuf_init(circbuf_t *cb, uint8_t *buffer, uint32_t size);
uint32_t circbuf_put(circbuf_t *cb, const uint8_t *data, uint32_t len);
uint32_t circbuf_get(circbuf_t *cb, uint8_t *data, uint32_t len);
uint32_t circbuf_peek(circbuf_t *cb, uint8_t *data, uint32_t len);
