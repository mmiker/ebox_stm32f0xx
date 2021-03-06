/**
  ******************************************************************************
  * @file    gpio.cpp
  * @author  shentq
  * @version V1.2
  * @date    2016/08/14
  * @brief   
  ******************************************************************************
  * @attention
  *
  * No part of this software may be used for any commercial activities by any form 
  * or means, without the prior written consent of shentq. This specification is 
  * preliminary and is subject to change at any time without notice. shentq assumes
  * no responsibility for any errors contained herein.
  * <h2><center>&copy; Copyright 2015 shentq. All Rights Reserved.</center></h2>
  ******************************************************************************
  */
/**
 * Modification History:
 * -LQM (2016/8/25)
 *      *移植到STM32F0,基于HAL库LL层
 *		*添加mode(PIN_MODE mode, uint8_t af_configration)方法
 * -LQM (2016/9/11)
 *		*添加AF_OD_PU，PD;AF_PP_PU，PD;OUTPUT_PP_PU,PD;OUTPUT_OD_PU,PD;
 */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

 /**
 *@brief    Gpio构造函数
 *@param    NONE
 *@retval   NONE
*/
Gpio::Gpio(GPIO_TypeDef *port, uint16_t pin)
{
    uint8_t temp1,temp2;
    this->port = port;
    this->pin = pin;
   switch((uint32_t)(port))
   {
       case (uint32_t)GPIOA_BASE:
           temp1 = 0;
       break;
           
       case (uint32_t)GPIOB_BASE:
           temp1 = 1;
       break;
           
       case (uint32_t)GPIOC_BASE:
           temp1 = 2;
       break;
           
       case (uint32_t)GPIOD_BASE:
           temp1 = 3;
       break;
#if !(defined(STM32F030x6)||defined(STM32F031x6))            
       case (uint32_t)GPIOE_BASE:
           temp1 = 4;
       break;
#endif           
       case (uint32_t)GPIOF_BASE:
           temp1 = 5;
       break;
           
//        case (uint32_t)GPIOG_BASE:
//            temp1 = 6;
//        break;
       default:
           temp1 = 0;
       break;
   }
   for(int i = 0; i <= 15; i ++)
   {
       if((this->pin >> i) == 0)
       {
           temp2 = i -1;
           break;
       }
   }
   this->id = (PIN_ID_t)(temp1*16 + temp2);
}

/**
 *@name     void GPIO::mode(PIN_MODE mode)
 *@brief    GPIO????
 *@param    mode:   PIN_MODE??????
 *@retval   None
*/
void Gpio::mode(PIN_MODE mode, uint8_t af_configration)
{  
	switch ((uint32_t)port)
	{
	case (uint32_t)GPIOA_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		break;
	case (uint32_t)GPIOB_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
		break;
	case (uint32_t)GPIOC_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
		break;
	case (uint32_t)GPIOD_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
		break;
#if !(defined(STM32F030x6)||defined(STM32F031x6))
	case (uint32_t)GPIOE_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
		break;
#endif
	case (uint32_t)GPIOF_BASE:
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		break;
	}

	switch ((uint8_t)mode)
	{
		/*analog input mode
		*/
	case AIN:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ANALOG);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);		
		break;

		/* digital input mode
		*/
	case INPUT:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		break;

	case INPUT_PD:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		break;

	case INPUT_PU:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		break;

		/*digital output mode
		*/
	case OUTPUT_OD:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		break;

	case OUTPUT_OD_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);;
		break;

	case OUTPUT_OD_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		break;

	case OUTPUT_PP:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		break;

	case OUTPUT_PP_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		break;

	case OUTPUT_PP_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_OUTPUT);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		

		break;

		/*af mode
		*/
	case AF_OD:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_OD_PU:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLUP;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_OD_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_OPENDRAIN);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_PP:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}

		break;

	case AF_PP_PU:

		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_UP);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;

	case AF_PP_PD:
		// GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
		// GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		// GPIO_InitStructure.Pull = GPIO_PULLDOWN;
		// GPIO_InitStructure.Alternate = af_configration;
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetPinOutputType(port,pin,LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinSpeed(port,pin,LL_GPIO_SPEED_FREQ_HIGH);		
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_DOWN);
		if (pin< LL_GPIO_PIN_8)
		{
			LL_GPIO_SetAFPin_0_7(port,pin,af_configration);
		}else{
			LL_GPIO_SetAFPin_8_15(port,pin,af_configration);
		}
		break;
		/* if parament is other mode,set as INPUT mode
		*/
	default:
		LL_GPIO_SetPinMode(port,pin,LL_GPIO_MODE_INPUT);
		LL_GPIO_SetPinPull(port,pin,LL_GPIO_PULL_NO);	
		break;
	}
}
/**
 *@brief    GPIO模式设置
 *@param    mode:PIN_MODE枚举变量类型
 *@retval   None
*/
void Gpio::mode(PIN_MODE _mode)
{
	mode(_mode,40);
}


/**
 *@brief    GPIO输出高电平
 *@param    NONE
 *@retval   NONE
*/
void Gpio::set()
{
    this->port->BSRR = this->pin;
}

/**
 *@brief    GPIO输出低电平
 *@param    NONE
 *@retval   NONE
*/
void Gpio::reset()
{
    this->port->BRR = this->pin;
}


/**
 *@brief    GPIO输出设置
 *@param    val：1：输出高电平；0：输出低电平
 *@retval   NONE
*/
void Gpio::write(uint8_t val)
{
    if(val == 0)
        this->port->BRR = this->pin;
    else
        this->port->BSRR = this->pin;
}


/**
 *@brief    GPIO输出高电平
 *@param    NONE
 *@retval   NONE
*/
void Gpio::read(uint8_t *val)
{
    *val = this->port->IDR & this->pin;
}


/**
 *@brief    读取GPIO引脚状态
 *@param    NONE
 *@retval   返回引脚当前的电平状态
*/
uint8_t Gpio::read(void)
{
    if(this->port->IDR & this->pin)
        return 1;
    return  0;
}

/**
 *@brief    GPIO输出电平翻转
 *@param    NONE
 *@retval   NONE
*/
void Gpio::toggle()
{
    port->ODR ^= this->pin;
}


int Gpio::operator =(Gpio&) 
{
    return read();
}

Gpio::operator int()
{
    return read();
}

Gpio Gpio::operator= (int value)
{
    write(value);
    return *this;
}
