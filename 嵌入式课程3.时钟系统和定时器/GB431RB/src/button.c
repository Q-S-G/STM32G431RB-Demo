#include "button.h"

void button_init(buttonType* button)
{
		button->cur_button=released;
		button->last_button= released;
		button->press_cnt=0;
		button->release_cnt=0;
}
void button_check(buttonType* button)
{
		switch(button->cur_button)
		{
				case(released):
				{
						if(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin) == GPIO_PIN_SET)
						{
								button->cur_button= press_shake;
						}
						break;
				}
			  case(pressed):
				{
						if(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin) == GPIO_PIN_RESET)
						{
								button->cur_button= release_shake;
						}
						break;
				}
				case(release_shake):
				{
						button->release_cnt++;
						if(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin) == GPIO_PIN_SET)
						{
								button->cur_button= pressed;
						}else{
								if(button->release_cnt >=10)
								{
										button->cur_button=released;
										button->release_cnt=0;
									  if(button->last_button != button->cur_button)
										{
												HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
												TIM2->CCR2=TIM2->CCR2+100;
												if(TIM2->CCR2 >= 1000)
												{
													TIM2->CCR2=100;
												}
										}
								}
						}
						break;
				}
				case(press_shake):
				{
						button->press_cnt++;
						if(HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin) == GPIO_PIN_RESET)
						{
								button->cur_button= released;
						}else{
								if(button->press_cnt >=10)
								{
										button->cur_button=pressed;
										button->press_cnt=0;
										if(button->last_button != button->cur_button)
										{
												HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
												TIM2->CCR2=TIM2->CCR2+100;
												if(TIM2->CCR2 >= 1000)
												{
													TIM2->CCR2=100;
												}
										}
								}
						}
						break;
				}
		}

}
