#include<stm32f030x8.h>
#include"My_HAL_GPIO.h"
//LED 3- green is on PC9 and LED4-  blue is on PC8
//void Polling_Handler(void);
int main(){

//configure clock for port C and A to HSI 8 Mhz 

GPIO_CLOCK_ENABLE_PORTC; 
GPIO_CLOCK_ENABLE_PORTA; //GPIO Ports are connected to AHB2 Bus

//configure pins as output

config_pin_output(GPIOC,8,OUTPUT_MODE,PUSH_PULL,MEDIUM_SPEED);
config_pin_output(GPIOC,9,OUTPUT_MODE,PUSH_PULL,MEDIUM_SPEED);
config_pin_input(GPIOA,0,INPUT_MODE,PULL_DOWN_RESISTOR);


config_gpio_interrupt(GPIOA, 0, FALLING_EDGE);
enable_gpio_interrupt(0,EXTI0_1_IRQn);

while(1){
    
   // Polling_Handler();
    gpio_toggle(PORTC,8);  //set pins high
    for(volatile int i=0 ; i<300000; i++);  //delay
    gpio_toggle(PORTC,8);  //reset pins
    for(volatile int i=0 ; i<300000; i++);  //delay
}
}

void EXTI0_1_IRQHandler(void){
  clear_gpio_interrupt(0);
   gpio_toggle(PORTC,9);
}

//void Polling_Handler(void){
//  if ((GPIO_IDR_0 & IDRA)){
//    gpio_toggle(PORTC,9);
//  }
//}