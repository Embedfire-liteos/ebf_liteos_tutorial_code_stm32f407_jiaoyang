/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "./key/bsp_key.h" 
#include "./usart/bsp_debug_usart.h"

#include "los_sys.h"
#include "los_task.ph"
#include "los_queue.h"
#include "los_sem.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//  HAL_IncTick();
//}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

uint32_t wi = 0;
/* ������Ϣ���еľ�� */
extern UINT32 Test_Queue_Handle;
/* �����ֵ�ź����ľ�� */
extern UINT32 BinarySem_Handle;

static uint32_t send_data1 = 1;
static uint32_t send_data2 = 2;


void KEY1_IRQHandler(void)
{
	UINTPTR uvIntSave;
	
	uvIntSave = LOS_IntLock();		//���ж�
  
  //ȷ���Ƿ������EXTI Line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY1_INT_GPIO_PIN) != RESET) 
	{
    /* ������д�루���ͣ��������У��ȴ�ʱ��Ϊ 0  */
    LOS_QueueWrite(	Test_Queue_Handle,	/* д�루���ͣ����е�ID(���) */
                    &send_data1,				/* д�루���ͣ������� */
                    sizeof(send_data1),	/* ���ݵĳ��� */
                    0);									/* �ȴ�ʱ��Ϊ 0  */
    //����жϱ�־λ
		__HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);     
	}  
  
	LOS_IntRestore(uvIntSave);	//���ж�
}

void KEY2_IRQHandler(void)
{
	UINTPTR uvIntSave;
	
	uvIntSave = LOS_IntLock();		//���ж�
  
  //ȷ���Ƿ������EXTI Line�ж�
	if(__HAL_GPIO_EXTI_GET_IT(KEY2_INT_GPIO_PIN) != RESET) 
	{
		/* ������д�루���ͣ��������У��ȴ�ʱ��Ϊ 0  */
		LOS_QueueWrite(	Test_Queue_Handle,	/* д�루���ͣ����е�ID(���) */
										&send_data2,				/* д�루���ͣ������� */
										sizeof(send_data2),	/* ���ݵĳ��� */
										0);									/* �ȴ�ʱ��Ϊ 0  */
    //����жϱ�־λ
		__HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);     
	}  
  
	LOS_IntRestore(uvIntSave);	//���ж�
}


void  DEBUG_USART_IRQHandler(void)
{
	UINTPTR uvIntSave;
  /* �����ж� */	
	uvIntSave = LOS_IntLock();		//���ж�
	
	if(__HAL_UART_GET_FLAG(&UartHandle,UART_FLAG_IDLE)!=RESET)
	{
		//�����жϲ�����˵��������ɣ�ֹͣ���ڽ��գ��˺�����ֹͣDMA�Ľ��գ�������HAL_UART_AbortReceiveCpltCallback
		HAL_UART_AbortReceive_IT(&UartHandle);
		//��������жϱ�־λ
		__HAL_UART_CLEAR_IDLEFLAG(&UartHandle);
	}
	
  /* �뿪�ж� */
	LOS_IntRestore(uvIntSave);	//���ж�
}

void DMA2_Stream5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(UartHandle.hdmarx);
}

void KEY3_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(KEY3_INT_GPIO_PIN);
}
void KEY4_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(KEY4_INT_GPIO_PIN);
}
void KEY5_IRQHandler(void)
{
	__HAL_GPIO_EXTI_CLEAR_IT(KEY5_INT_GPIO_PIN);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
