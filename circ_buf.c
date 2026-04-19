#include <string.h>
#include "circ_buf.h"

void circbuf_init(circbuf_t *cb, uint8_t *buffer, uint32_t size) {
  cb->buf = buffer;
  cb->size = size;
  cb->head = 0;
  cb->tail = 0;
  cb->count = 0;
}

uint32_t circbuf_put(circbuf_t *cb, const uint8_t *data, uint32_t len) {

  if (len == 0 || cb->count == cb->size) return 0; /* Space available */

  uint32_t free     = cb->size - cb->count;
  uint32_t to_write = MIN(len, free); /* Write first chunk (until buffer end) */
  uint32_t first    = MIN(to_write, cb->size - cb->head);
  memcpy(&cb->buf[cb->head], data, first); /* Write wrap-around chunk */

  uint32_t second = to_write - first;
  if (second > 0) {
    memcpy(&cb->buf[0], data + first, second);
  }
  cb->head   = (cb->head + to_write) % cb->size;
  cb->count += to_write;
  return to_write;
}

uint32_t circbuf_get(circbuf_t *cb, uint8_t *data, uint32_t len) {

  if (len == 0 || cb->count == 0) return 0;

  uint32_t to_read = MIN(len, cb->count); /* Read first chunk */
  uint32_t first = MIN(to_read, cb->size - cb->tail);
  memcpy(data, &cb->buf[cb->tail], first); /* Read wrap-around chunk */

  uint32_t second = to_read - first;
  if (second > 0) {
    memcpy(data + first, &cb->buf[0], second);
  }
  cb->tail = (cb->tail + to_read) % cb->size;
  cb->count -= to_read;
  return to_read;
}

uint32_t circbuf_peek(circbuf_t *cb, uint8_t *data, uint32_t len) {

  if (len == 0 || cb->count == 0) return 0;
  uint32_t to_read = MIN(len, cb->count);
  uint32_t idx = cb->tail;
  uint32_t first = MIN(to_read, cb->size - idx);
  memcpy(data, &cb->buf[idx], first);

  uint32_t second = to_read - first;
  if (second > 0) {
    memcpy(data + first, &cb->buf[0], second);
  }
  return to_read;
}

uint32_t circbuf_available(const circbuf_t *cb) { return cb->count; }
uint32_t circbuf_free(const circbuf_t *cb) { return cb->size - cb->count; }
int circbuf_is_empty(const circbuf_t *cb) { return cb->count == 0; }
int circbuf_is_full(const circbuf_t *cb) { return cb->count == cb->size; }

