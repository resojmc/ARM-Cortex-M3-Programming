#include <stdint.h>

// Define base addresses for RCC (clock control) and GPIOC
#define RCC_BASE (*(volatile uint32_t *)(0x40021000UL))
#define GPIOC_BASE (*(volatile uint32_t *)(0x40011000UL))

// Define specific peripheral registers using offsets
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18UL))  // Peripheral clock enable
#define GPIOC_CRH (*(volatile uint32_t *)(GPIOC_BASE + 0x04UL))  // GPIOC configuration high register
#define GPIOC_ODR (*(volatile uint32_t *)(GPIOC_BASE + 0x0CUL))  // GPIOC output data register

int main(){
    RCC_APB2ENR |= (1 << 4);        // Enable clock for GPIOC
    GPIOC_CRH &= ~(1 << 20);        // Configure PC13 as general-purpose output
    GPIOC_CRH &= ~(1 << 23);        // Ensure proper output mode setting

    // Infinite loop to blink LED connected to PC13
    while(1){
        GPIOC_ODR |= (1 << 13);     // Set PC13 high (turn off LED on most STM32 boards)
        for(volatile int i = 0; i < 5000000; i++){}  // Delay loop

        GPIOC_ODR &= ~(1 << 13);    // Set PC13 low (turn on LED)
        for(volatile int i = 0; i < 5000000; i++){}  // Delay loop
    }

    return 0;
}
