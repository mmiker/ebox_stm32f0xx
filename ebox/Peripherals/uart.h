/**
  ******************************************************************************
  * @file    ebox_uart.h
  * @author  LQM
  * @version V1.0.0
  * @brief   usart1,2,3
  * @log  
  * @date    2016.6.28   ��ֲ������HAL�̼���STM32F0ƽ̨
  ******************************************************************************
  */
#ifndef __EBOX_UART_H
#define __EBOX_UART_H
#include "common.h"

//�û�����//////////////
#define UART_MAX_SEND_BUF 128

class USART
{
public:
	USART(USART_TypeDef *USARTx, GPIO *tx, GPIO *rx);

	void    begin(uint32_t baud_rate);
	void    begin(uint32_t baud_rate,uint8_t use_dma);
	void    begin(uint32_t baud_rate, uint8_t data_bit, uint8_t parity, float stop_bit);
	void    attach_rx_interrupt(void (*callback_fun)(void));
	void    attach_tx_interrupt(void (*callback_fun)(void));

	int 	put_char(uint16_t ch);
	void 	put_string(const char *str);
	void    printf_length(const char *str, uint16_t length);
	void    printf(const char *fmt, ...); //��Ҫע�⻺�������
	void    wait_busy();

	uint16_t            receive();

private:
	// �˿ڲ���
	GPIO                *tx;
	GPIO                *rx;
	uint8_t             gpio_af_usart;
	// USART����
	USART_TypeDef       *USARTx;
	void                (*rcc_usart_clock_cmd)(uint32_t Periphs);
	uint32_t            usart_rcc;
	IRQn_Type           usart_irq;
	void                usart_config(uint32_t baud_rate);
	// DMA����
	uint8_t             use_dma;
	void                (*rcc_dma_clock_cmd)(uint32_t Periphs);
	uint32_t            dma_rcc;
//   IRQn_Type           dma_irq;
	DMA_TypeDef         *dma;
	uint32_t            dma_channel;
	void                dma_config();
	uint16_t            dma_send_string(const char *str, uint16_t length);
	// ����
	char                send_buf[UART_MAX_SEND_BUF];
	void                put_string(const char *str, uint16_t length);
	void                set_busy();
	void                interrupt(FunctionalState enable);
};


#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
     
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif