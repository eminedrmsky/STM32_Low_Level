#include"My_HAL_STM32F0.h"

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
                    port ->OTYPER |= (1<<pinNumber) ;                
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



//****************************************INTERRUPT*********************************************************

void config_gpio_interrupt(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge){
    
    if(port == PORTA){
        switch(pinNumber){
        case 0:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
        break;
        case 1:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;
        break;
        case 2:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PA;
        break;
        case 3:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PA;
        break;
        case 4:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PA;
        break;
        case 5:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PA;
        break;
        case 6:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PA;
        break;
        case 7:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PA;
        break;
        case 8:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PA;
        break;
        case 9:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PA;
        break;
        case 10:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PA;
        break;
        case 11:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PA;
        break;
        case 12:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PA;
        break;
        case 13:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PA;
        break;
        case 14:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PA;
        break;
        case 15:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PA;
        break;
        }
    }

        if(port == PORTB){
        switch(pinNumber){
        case 0:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PB;
        break;
        case 1:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PB;
        break;
        case 2:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PB;
        break;
        case 3:
            SYSCFG ->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;
        break;
        case 4:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PB;
        break;
        case 5:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PB;
        break;
        case 6:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PB;
        break;
        case 7:
            SYSCFG ->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PB;
        break;
        case 8:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PB;
        break;
        case 9:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PB;
        break;
        case 10:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PB;
        break;
        case 11:
            SYSCFG ->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PB;
        break;
        case 12:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PB;
        break;
        case 13:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PB;
        break;
        case 14:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PB;
        break;
        case 15:
            SYSCFG ->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PB;
        break;
        }
    }

    //Do again for ports C and D

    if(edge == RISING_EDGE){
        EXTI -> RTSR |= (1<<pinNumber);
    }
    if(edge == FALLING_EDGE){
        EXTI -> FTSR |= (1<<pinNumber);
    }
    else{
        EXTI -> RTSR |= (1<<pinNumber);
        EXTI -> FTSR |= (1<<pinNumber);
    }
}

void enable_gpio_interrupt(uint32_t pinNumber, IRQn_Type irqNumber){

    EXTI ->IMR |= (1<<pinNumber); //enable interrupt in EXTI
    NVIC_EnableIRQ(irqNumber);
}

void clear_gpio_interrupt(uint32_t pinNumber){
    EXTI -> PR |= (1<<pinNumber);
}




//**********************************TIMER FUNCTIONS****************************************************************************



void config_timer(TIM_TypeDef *port, uint16_t prescaler, uint16_t auto_reload){
    port -> PSC = prescaler;
    port -> ARR = auto_reload;
}

void timer_init(TIM_TypeDef *port, uint32_t division, uint32_t buffer, uint32_t edge_align, uint32_t direction){
                switch(division){

                case NO_DIVISION:
                    port ->CR1  &= ~( (1<<CKD0 )| (1<< CKD1));
                break;

                case DIVIDE_BY_TWO:
                    port ->CR1 |= (1<<CKD0) ;
                    port ->CR1 &= ~ (1<<CKD1) ;
                break;

                case DIVIDE_BY_FOUR:
                    port ->CR1|= (1<<CKD1) ;
                    port ->CR1 &= ~ (1<<CKD0) ;
                break;
            }

            switch(buffer){

                case NOT_BUFFERED:
                    port ->CR1  &= ~ (1<<ARPE );
                break;

                case BUFFERED:
                    port ->CR1 |= (1<<ARPE) ;
                break;

            }

            switch(edge_align){

                case EDGE_ALIGN:
                    port ->CR1  &= ~( (1<<CMS0 )| (1<< CMS1));
                break;

                case CENTER_ALIGN_1:
                    port ->CR1 |= (1<<CMS0) ;
                    port ->CR1 &= ~ (1<<CMS1) ;
                break;

                case CENTER_ALIGN_2:
                    port ->CR1|= (1<<CMS1) ;
                    port ->CR1 &= ~ (1<<CMS0) ;
                break;

                case CENTER_ALIGN_3:
                    port ->CR1  |= ( (1<<CMS0 )| (1<< CMS1));
                break;
            }

            switch(direction){

                case UP_COUNTER:
                    port ->CR1  &= ~ (1<<DIR );
                break;

                case DOWN_COUNTER:
                    port ->CR1 |= (1<<DIR) ;
                break;

            }


}


void timer_enable(TIM_TypeDef *port){
    port ->CR1 |= (1<<CEN) ;
}

void enable_timer_interrupt(TIM_TypeDef *port, IRQn_Type irqNumber){
    port -> DIER |= (1<<0); //enable timer interrupt
    NVIC_EnableIRQ(irqNumber);  //enable NVIC

}

void clear_timer_interrupt(TIM_TypeDef *port){
    port -> SR &= ~ (1<<0 );

}