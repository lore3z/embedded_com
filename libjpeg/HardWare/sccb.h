/**
 ****************************************************************************************************
 * @file        sccb.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-23
 * @brief       SCCB��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� M144Z-M4��Сϵͳ��STM32F407��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __SCCB_H
#define __SCCB_H

#include "main.h"

/* ���Ŷ��� */
#define SCCB_SCL_GPIO_PORT          GPIOD
#define SCCB_SCL_GPIO_PIN           GPIO_PIN_6
#define SCCB_SCL_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)
#define SCCB_SDA_GPIO_PORT          GPIOD
#define SCCB_SDA_GPIO_PIN           GPIO_PIN_7
#define SCCB_SDA_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)

/* ������ÿ�©ģʽ��SCCB�����������裬����Ҫ����������л��ķ�ʽ */
#define OV_SCCB_TYPE_NOD            0
#if (OV_SCCB_TYPE_NOD != 0)
#define SCCB_SDA_IN()               do { GPIOD->MODE &= ~(3 << (7 * 2)); GPIOD->MODE |= 0 << (7 * 2); } while(0)
#define SCCB_SDA_OUT()              do { GPIOD->MODE &= ~(3 << (7 * 2)); GPIOD->MODE |= 1 << (7 * 2); } while(0)
#endif

/* IO���� */
#define SCCB_SCL(x)                 do { (x) ?                                                                      \
                                        HAL_GPIO_WritePin(SCCB_SCL_GPIO_PORT, SCCB_SCL_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(SCCB_SCL_GPIO_PORT, SCCB_SCL_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define SCCB_SDA(x)                 do { (x) ?                                                                      \
                                        HAL_GPIO_WritePin(SCCB_SDA_GPIO_PORT, SCCB_SDA_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(SCCB_SDA_GPIO_PORT, SCCB_SDA_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define SCCB_SDA_READ               ((HAL_GPIO_ReadPin(SCCB_SDA_GPIO_PORT, SCCB_SDA_GPIO_PIN) == GPIO_PIN_RESET) ? 0 : 1)

/* �������� */
void sccb_init(void);                   /* ��ʼ��SCCB */
void sccb_start(void);                  /* ����SCCB��ʼ�ź� */
void sccb_stop(void);                   /* ����SCCBֹͣ�ź� */
void sccb_nack(void);                   /* ����SCCB NACK�ź� */
uint8_t sccb_send_byte(uint8_t data);   /* SCCB����һ���ֽ� */
uint8_t sccb_read_byte(void);           /* SCCB��ȡһ���ֽ� */

#endif
