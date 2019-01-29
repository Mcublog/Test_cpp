#include "example.h"

static uint32_t _flag = 0;

uint32_t get_state()
{
    return _flag;
}

void set_off()
{
    _flag = 0;
}

void set_on()
{
    _flag = 1;
}