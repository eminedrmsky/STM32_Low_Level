#include<stm32f030x8.h>
#include"My_HAL_STM32F0.h"

int main(){

GPIO_CLOCK_ENABLE_PORTC;  //enable green led clock AHB2 bus
TIM3_CLOCK_ENABLE; //enable tim3 clock  APB1 bus

config_pin_output(GPIOC,9,OUTPUT_MODE,PUSH_PULL,MEDIUM_SPEED); // configure GPIO ports

config_timer(TIM3, 7999, 1000 ); //8 Mhz /8000 = 1000 hz /1000 = 1 Hz - 1 sn
timer_init(TIM3, NO_DIVISION, NOT_BUFFERED, EDGE_ALIGN, UP_COUNTER);

enable_timer_interrupt(TIM3, 16);
timer_enable(TIM3);

while(1){
   //do nothing
}

}

void TIM3_IRQHandler(void){

    clear_timer_interrupt(TIM3);
    gpio_toggle(PORTC,9);

}
