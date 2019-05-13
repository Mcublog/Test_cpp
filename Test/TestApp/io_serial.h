#ifndef IO_SERIAL_H
#define IO_SERIAL_H

#include <stdint.h>

typedef enum
{
    IO_NONE,    
    IO_UART,
    IO_USB,
}io_serial_type_h;

typedef enum
{
    TX_CALLBACK = 0,
    RX_CALLBACK = 1,
    IDLE_CALLBACK = 2,
//-----------------    
    LAST_CALLBACK
}io_callback_id_t;

typedef void (*io_callback_handler_t)(void *context);

typedef struct
{
    io_serial_type_h type;
    io_callback_handler_t callback_list[LAST_CALLBACK];
    void *phuart;
    void *phdma;
}io_serial_h;

void io_serial_init(io_serial_h *ser);
void io_serial_deinit(io_serial_h *ser);

io_serial_type_h io_serial_get_type(io_serial_h *ser);
void io_serial_set_idle_irq(io_serial_h *ser);

void io_serial_tx(io_serial_h *ser, uint8_t *buf, uint32_t size);

uint32_t io_serial_get_dma_bytes_waiting(io_serial_h *ser);
void io_serial_set_dma_rx_and_idle_irq(io_serial_h *ser, uint8_t *buf, uint32_t size);

uint32_t io_serial_callback_reg(io_serial_h *ser, io_callback_id_t id, io_callback_handler_t func);
uint32_t io_serial_callback_unreg(io_serial_h *ser, io_callback_id_t id);
void io_serial_callback_call(io_serial_h *ser);

#endif // IO_SERIAL_H
