#include"My_HAL_GPIO.h"

void config_pin_output(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t mode_type, uint32_t output_type, uint32_t pinSpeed){

            switch(mode_type){

                case INPUT_MODE:
                    port ->MODER  &= ~( (1<<POS_BIT1(pinNumber) )| (1<< POS_BIT2(pinNumber) ));
                break;

                case OUTPUT_MODE:
                    port ->MODER |= (1<<POS_BIT1(pinNumber)) ;
                    port ->MODER &= ~ (1<< POS_BIT2(pinNumber)) ;
                break;

                case ALT_FUNC_MODE:
                    port ->MODER |= (1<< POS_BIT2(pinNumber)) ;
                    port ->MODER &= ~ (1<<POS_BIT1(pinNumber)) ;
                break;

                case ANALOG_MODE:
                    port ->MODER |= ( (1<<POS_BIT1(pinNumber) )| (1<< POS_BIT2(pinNumber) ));
                break;


            }

            
                if(output_type ==PUSH_PULL){
                    port -> OTYPER &= ~ (1<<pinNumber );
                }else{
                    port ->MODER |= (1<<pinNumber) ;                
               }


                switch(pinSpeed){
                    case LOW_SPEED:
                        port ->OSPEEDR  &= ~( (1<<POS_BIT1(pinNumber) )| (1<< POS_BIT2(pinNumber) ));
                    break;

                    case MEDIUM_SPEED:
                        port ->OSPEEDR |= (1<<POS_BIT1(pinNumber)) ;
                        port ->OSPEEDR &= ~ (1<< POS_BIT2(pinNumber)) ;
                    break;

                    case HIGH_SPEED:
                       port ->OSPEEDR |= ( (1<<POS_BIT1(pinNumber) )| (1<< POS_BIT2(pinNumber) )); 
                    break;
                }


}

void config_pin_input(GPIO_TypeDef *port, uint32_t pinNumber,uint32_t mode_type, uint32_t resistor_type){

                switch(mode_type){

                case INPUT_MODE:
                    port ->MODER  &= ~( (1<<POS_BIT1(pinNumber) )| (1<< (POS_BIT2(pinNumber)  )));
                break;

                case OUTPUT_MODE:
                    port ->MODER |= (1<<POS_BIT1(pinNumber)) ;
                    port ->MODER &= ~ (1<<(POS_BIT2(pinNumber) )) ;
                break;

                case ALT_FUNC_MODE:
                    port ->MODER |= (1<<(POS_BIT2(pinNumber) )) ;
                    port ->MODER &= ~ (1<<POS_BIT1(pinNumber)) ;
                break;

                case ANALOG_MODE:
                    port ->MODER |= ( (1<<POS_BIT1(pinNumber) )| (1<<( POS_BIT2(pinNumber)  )));
                break;


            }

            switch(resistor_type){

                case NO_RESISTOR:
                    port ->PUPDR  &= ~( (1<<POS_BIT1(pinNumber) )| (1<< (POS_BIT2(pinNumber)  )));
                break;

                case PULL_UP_RESISTOR:
                    port ->PUPDR |= (1<<POS_BIT1(pinNumber)) ;
                    port ->PUPDR &= ~ (1<<(POS_BIT2(pinNumber) )) ;
                break;

                case PULL_DOWN_RESISTOR:
                    port ->PUPDR |= (1<<(POS_BIT2(pinNumber) )) ;
                    port ->PUPDR &= ~ (1<<POS_BIT1(pinNumber)) ;
                break;
            }

}


void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinState){

    if(pinState == LOW){
        port -> BSRR |= (1<< POS_BIT3(pinNumber));
    }else{
        port -> BSRR |= (1<<pinNumber);
    }
}



void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber){

    port ->ODR ^= (1<<pinNumber);
}

void gpio_init(GPIO_TYPE gpio_type){

    if(gpio_type.port == PORTA){
        GPIO_CLOCK_ENABLE_PORTA;
    }
    if(gpio_type.port == PORTB){
        GPIO_CLOCK_ENABLE_PORTB;
    }
    if(gpio_type.port == PORTC){
        GPIO_CLOCK_ENABLE_PORTC;
    }
    if(gpio_type.port == PORTD){
        GPIO_CLOCK_ENABLE_PORTD;
    }

    config_pin_output(gpio_type.port,gpio_type.pin,gpio_type.mode,gpio_type.type,gpio_type.speed);

}