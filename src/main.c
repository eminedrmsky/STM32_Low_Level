#include<stm32f030x8.h>
#include"My_HAL_GPIO.h"
//LED 3- green is on PC9 and LED4-  blue is on PC8

int main(){

//configure clock for port C 

GPIO_CLOCK_ENABLE_PORTC;  //GPIO Ports are connected to AHB2 Bus

//configure pins as output

config_pin_output(GPIOC,8,OUTPUT_MODE,PUSH_PULL,MEDIUM_SPEED);
config_pin_output(GPIOC,9,OUTPUT_MODE,PUSH_PULL,MEDIUM_SPEED);

while(1){
    
    gpio_toggle(PORTC,8);  //set pins high
    for(volatile int i=0 ; i<300000; i++);  //delay
    gpio_toggle(PORTC,8);  //reset pins
    for(volatile int i=0 ; i<300000; i++);  //delay
}
}