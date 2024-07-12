#ifndef button_H
#define button_H


#include "main.h"

typedef enum{
		release_shake,
		press_shake,
		pressed,
		released,
}button_enum;
typedef struct{
		uint16_t press_cnt;
		uint16_t release_cnt;
	  button_enum last_button;
		button_enum cur_button;
}buttonType;

void button_check(buttonType* button);
void button_init(buttonType* button);

#endif
