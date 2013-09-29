#pragma once
#include <isr.h>
#include <misc.h>

void timer_init(uint32_t freq);
void timer_callback(registers_t regs);
