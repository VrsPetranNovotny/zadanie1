#include <stddef.h>
#include "stm32l1xx.h"

void delay(uint32_t time)
{
	uint32_t i;
	for(i=0;i<time;i++)
	{
	}
}

int main(void)
{

	uint8_t button;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    /* uloha 1a */

    GPIOA->MODER   |=(0b01)<<(5*2);
  	GPIOA->OTYPER  &= ~((0b1)<<5);
  	GPIOA->PUPDR   |= (0b01)<<(5*2);
  	GPIOA->OSPEEDR |= (0b11)<<(5*2);

  	/* uloha 1b */

  	GPIOA->ODR |= 0b1<<5;      //zapnutie LED
  	GPIOA->ODR &= ~(0b1<<5);   //vypnutie LED
  	GPIOA->BSRRL |= 0b1<<5;    //zapnutie LED
  	GPIOA->BSRRH |= 0b1<<5;    //vypnutie LED

  	/* uloha 1c */

  	GPIOA->ODR ^= 0b1<<5; //zmena stavu LED (zapnute)
  	GPIOA->ODR ^= 0b1<<5; //zmena stavu LED (vypnute)
  	GPIOA->ODR ^= 0b1<<5; //zmena stavu LED (zapnute)

  	/* uloha 2a */

  	GPIOC->MODER  &= ~((0b11)<<(13*2));
  	GPIOC->OTYPER &= ~((0b1)<<13);
  	GPIOC->PUPDR  &= ~(0b11<<(13*2));

  while (1)
  {

	  /* uloha 3a */

	  GPIOA->ODR |= 0b1<<5;
	  delay(1000000);
	  GPIOA->ODR &= ~(0b1<<5);
	  delay(1000000);

       /* uloha 3b a 2b*/

	  button = (GPIOC->IDR & (0b1<<13))>>13;

	 	  if(button==0)
	 	  {
	 		  GPIOA->ODR |= 0b1<<5;
	 	  }
	 	  else
	 	  {
	 		  GPIOA->ODR &= ~(0b1<<5);
	 	  }

        /* uloha 3c */

	   if((button == 0) )
	   	   {
	   		delay(150000);
	   	   }
	   if((button == 0) )
	   {
		   GPIOA->ODR ^= 0b1<<5;
	   }
  }
  return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
