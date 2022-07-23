#ifndef _MY_HAL_STM32F0
#define _MY_HAL_STM32F0

#include<stm32f030x8.h>

//STATES

#define LOW   0
#define HIGH  1

//PORT NAMES
#define PORTA   GPIOA
#define PORTB   GPIOB
#define PORTC   GPIOC
#define PORTD   GPIOD
#define PORTF   GPIOF

//PIN MODE

#define INPUT_MODE   ((uint32_t)  0x00)
#define OUTPUT_MODE  ((uint32_t)  0x01)
#define ALT_FUNC_MODE  ((uint32_t)  0x02)
#define ANALOG_MODE   ((uint32_t)  0x03)

//OUTPUT PIN TYPES

#define PUSH_PULL  ((uint32_t)  0x00)
#define OPEN_DRAIN  ((uint32_t)  0x01)

//OUTPUT PIN SPEED

#define LOW_SPEED  ((uint32_t)  0x00)
#define MEDIUM_SPEED  ((uint32_t)  0x01)
#define HIGH_SPEED  ((uint32_t)  0x03)

//CLOCK ENABLE

#define GPIO_CLOCK_ENABLE_PORTA     (RCC ->AHBENR |= (1<<17))
#define GPIO_CLOCK_ENABLE_PORTB     (RCC ->AHBENR |= (1<<18))
#define GPIO_CLOCK_ENABLE_PORTC     (RCC ->AHBENR |= (1<<19))
#define GPIO_CLOCK_ENABLE_PORTD     (RCC ->AHBENR |= (1<<20))
#define GPIO_CLOCK_ENABLE_PORTF     (RCC ->AHBENR |= (1<<22))

//PULL-UP-DOWN RESISTORS

#define NO_RESISTOR ((uint32_t)  0x00)
#define PULL_UP_RESISTOR ((uint32_t)  0x01)
#define PULL_DOWN_RESISTOR  ((uint32_t)  0x02)

//BIT POSITIONS for MODER, OSPEEDR, PUPDR

#define POS_BIT1(x)        (x*2) 
#define POS_BIT2(x)        ((x*2)+1) 
#define POS_BIT3(x)        (x+16)

//Input Data

#define IDRA      (GPIOA->IDR)
#define IDRB      (GPIOB->IDR)
#define IDRC      (GPIOC->IDR)
#define IDRD      (GPIOD->IDR)

//CONFIGURATION STRUCTURE

typedef struct 
{
    GPIO_TypeDef *port;
    uint32_t pin;
    uint32_t mode;
    uint32_t type;
    uint32_t resistor;
    uint32_t speed;
    uint32_t alt_func;

}GPIO_TYPE;

typedef enum{
    RISING_EDGE,
    FALLING_EDGE,
    RISING_FALLING_EDGE
}edge_select;


//*********************************************Timers *************************************************************

#define TIM3_CLOCK_ENABLE    (RCC->APB1ENR |= (1<<1))

typedef enum{
    CEN,
    UDIS,
    URS,
    OPM,
    DIR,
    CMS0,
    CMS1,
    ARPE,
    CKD0,
    CKD1
}position_select;

#define NO_DIVISION        ((uint32_t)  0x00)
#define DIVIDE_BY_TWO      ((uint32_t)  0x01)
#define DIVIDE_BY_FOUR     ((uint32_t)  0x02)


#define NOT_BUFFERED             0
#define BUFFERED                 1


#define EDGE_ALIGN          ((uint32_t)  0x00)
#define CENTER_ALIGN_1      ((uint32_t)  0x01)
#define CENTER_ALIGN_2      ((uint32_t)  0x02)
#define CENTER_ALIGN_3      ((uint32_t)  0x03)


#define UP_COUNTER             0
#define DOWN_COUNTER           1






//FUNCTION PROTOTYPES
//******************************************************************************************
//GPIO CONFIGIRATION

void config_pin_output(GPIO_TypeDef *port, uint32_t , uint32_t , uint32_t , uint32_t );
void config_pin_input(GPIO_TypeDef *port, uint32_t ,uint32_t, uint32_t );

//GPIO PIN FUNCTION
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinState);
void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber);
void gpio_init(GPIO_TYPE gpio_type);

//GPIO INTERRUPT
void config_gpio_interrupt(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge);
void enable_gpio_interrupt(uint32_t pinNumber, IRQn_Type irqNumber);
void clear_gpio_interrupt(uint32_t pinNumber);

//TIMER FUNCTIONS

void config_timer(TIM_TypeDef *port, uint16_t prescaler, uint16_t auto_reload);
void timer_init(TIM_TypeDef *port, uint32_t division, uint32_t buffer, uint32_t edge_align, uint32_t direction);
void timer_enable(TIM_TypeDef *port);

//Timer interrupts

void enable_timer_interrupt(TIM_TypeDef *port, IRQn_Type irqNumber);
void clear_timer_interrupt(TIM_TypeDef* port);

#endif // _MY_HAL_GPIO