/**
 ****************************************************************************************************
 * @file        ov2640.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-23
 * @brief       OV2640驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 M144Z-M4最小系统板STM32F407版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __OV2640_H
#define __OV2640_H

#include "main.h"

/* 引脚定义 */
#define OV_PWDN_GPIO_PORT           GPIOG
#define OV_PWDN_GPIO_PIN            GPIO_PIN_9
#define OV_PWDN_GPIO_CLK_ENABLE()   do { __HAL_RCC_GPIOG_CLK_ENABLE(); } while(0)

#define OV_RESET_GPIO_PORT          GPIOG
#define OV_RESET_GPIO_PIN           GPIO_PIN_15
#define OV_RESET_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOG_CLK_ENABLE(); } while(0)

#define OV_FLASH_GPIO_PORT          GPIOA
#define OV_FLASH_GPIO_PIN           GPIO_PIN_8
#define OV_FLASH_GPIO_CLK_ENABLE()  do { __HAL_RCC_GPIOA_CLK_ENABLE(); } while(0)

/* IO操作 */
#define OV2640_PWDN(x)              do { (x) ?                                                                      \
                                        HAL_GPIO_WritePin(OV_PWDN_GPIO_PORT, OV_PWDN_GPIO_PIN, GPIO_PIN_SET):       \
                                        HAL_GPIO_WritePin(OV_PWDN_GPIO_PORT, OV_PWDN_GPIO_PIN, GPIO_PIN_RESET);     \
                                    } while (0)
#define OV2640_RST(x)               do { (x) ?                                                                      \
                                        HAL_GPIO_WritePin(OV_RESET_GPIO_PORT, OV_RESET_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(OV_RESET_GPIO_PORT, OV_RESET_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)
#define OV2640_FLASH(x)             do { (x) ?                                                                      \
                                        HAL_GPIO_WritePin(OV_FLASH_GPIO_PORT, OV_FLASH_GPIO_PIN, GPIO_PIN_SET):     \
                                        HAL_GPIO_WritePin(OV_FLASH_GPIO_PORT, OV_FLASH_GPIO_PIN, GPIO_PIN_RESET);   \
                                    } while (0)

/* OV2640 MID、PID和SCCB访问地址定义 */
#define OV2640_MID                  0x7FA2
#define OV2640_PID                  0x2642
#define OV2640_ADDR                 0x60

/* OV2640 DSP寄存器地址定义 */
#define OV2640_DSP_R_BYPASS         0x05
#define OV2640_DSP_Qs               0x44
#define OV2640_DSP_CTRL             0x50
#define OV2640_DSP_HSIZE1           0x51
#define OV2640_DSP_VSIZE1           0x52
#define OV2640_DSP_XOFFL            0x53
#define OV2640_DSP_YOFFL            0x54
#define OV2640_DSP_VHYX             0x55
#define OV2640_DSP_DPRP             0x56
#define OV2640_DSP_TEST             0x57
#define OV2640_DSP_ZMOW             0x5A
#define OV2640_DSP_ZMOH             0x5B
#define OV2640_DSP_ZMHH             0x5C
#define OV2640_DSP_BPADDR           0x7C
#define OV2640_DSP_BPDATA           0x7D
#define OV2640_DSP_CTRL2            0x86
#define OV2640_DSP_CTRL3            0x87
#define OV2640_DSP_SIZEL            0x8C
#define OV2640_DSP_HSIZE2           0xC0
#define OV2640_DSP_VSIZE2           0xC1
#define OV2640_DSP_CTRL0            0xC2
#define OV2640_DSP_CTRL1            0xC3
#define OV2640_DSP_R_DVP_SP         0xD3
#define OV2640_DSP_IMAGE_MODE       0xDA
#define OV2640_DSP_RESET            0xE0
#define OV2640_DSP_MS_SP            0xF0
#define OV2640_DSP_SS_ID            0x7F
#define OV2640_DSP_SS_CTRL          0xF8
#define OV2640_DSP_MC_BIST          0xF9
#define OV2640_DSP_MC_AL            0xFA
#define OV2640_DSP_MC_AH            0xFB
#define OV2640_DSP_MC_D             0xFC
#define OV2640_DSP_P_STATUS         0xFE
#define OV2640_DSP_RA_DLMT          0xFF

/* OV2640 Sensor寄存器地址定义 */
#define OV2640_SENSOR_GAIN          0x00
#define OV2640_SENSOR_COM1          0x03
#define OV2640_SENSOR_REG04         0x04
#define OV2640_SENSOR_REG08         0x08
#define OV2640_SENSOR_COM2          0x09
#define OV2640_SENSOR_PIDH          0x0A
#define OV2640_SENSOR_PIDL          0x0B
#define OV2640_SENSOR_COM3          0x0C
#define OV2640_SENSOR_COM4          0x0D
#define OV2640_SENSOR_AEC           0x10
#define OV2640_SENSOR_CLKRC         0x11
#define OV2640_SENSOR_COM7          0x12
#define OV2640_SENSOR_COM8          0x13
#define OV2640_SENSOR_COM9          0x14
#define OV2640_SENSOR_COM10         0x15
#define OV2640_SENSOR_HREFST        0x17
#define OV2640_SENSOR_HREFEND       0x18
#define OV2640_SENSOR_VSTART        0x19
#define OV2640_SENSOR_VEND          0x1A
#define OV2640_SENSOR_MIDH          0x1C
#define OV2640_SENSOR_MIDL          0x1D
#define OV2640_SENSOR_AEW           0x24
#define OV2640_SENSOR_AEB           0x25
#define OV2640_SENSOR_W             0x26
#define OV2640_SENSOR_REG2A         0x2A
#define OV2640_SENSOR_FRARL         0x2B
#define OV2640_SENSOR_ADDVSL        0x2D
#define OV2640_SENSOR_ADDVHS        0x2E
#define OV2640_SENSOR_YAVG          0x2F
#define OV2640_SENSOR_REG32         0x32
#define OV2640_SENSOR_ARCOM2        0x34
#define OV2640_SENSOR_REG45         0x45
#define OV2640_SENSOR_FLL           0x46
#define OV2640_SENSOR_FLH           0x47
#define OV2640_SENSOR_COM19         0x48
#define OV2640_SENSOR_ZOOMS         0x49
#define OV2640_SENSOR_COM22         0x4B
#define OV2640_SENSOR_COM25         0x4E
#define OV2640_SENSOR_BD50          0x4F
#define OV2640_SENSOR_BD60          0x50
#define OV2640_SENSOR_REG5D         0x5D
#define OV2640_SENSOR_REG5E         0x5E
#define OV2640_SENSOR_REG5F         0x5F
#define OV2640_SENSOR_REG60         0x60
#define OV2640_SENSOR_HISTO_LOW     0x61
#define OV2640_SENSOR_HISTO_HIGH    0x62

/* 函数声明 */
uint8_t ov2640_read_reg(uint16_t reg);                                                          /* 读OV2640寄存器 */
uint8_t ov2640_write_reg(uint16_t reg, uint8_t data);                                           /* 写OV2640寄存器 */
uint8_t ov2640_init(void);                                                                      /* 初始化OV2640 */
void ov2640_jpeg_mode(void);                                                                    /* 配置OV2640为JPEG模式 */
void ov2640_rgb565_mode(void);                                                                  /* 配置OV2640为RGB565模式 */
void ov2640_auto_exposure(uint8_t level);                                                       /* 配置OV2640 EV曝光补偿 */
void ov2640_light_mode(uint8_t mode);                                                           /* 配置OV2640白平衡模式 */
void ov2640_color_saturation(uint8_t sat);                                                      /* 配置OV2640色彩饱和度 */
void ov2640_brightness(uint8_t bright);                                                         /* 配置OV2640亮度 */
void ov2640_contrast(uint8_t contrast);                                                         /* 配置OV2640对比度 */
void ov2640_special_effects(uint8_t eft);                                                       /* 配置OV2640特效 */
void ov2640_color_bar(uint8_t mode);                                                            /* OV2640彩条测试 */
void ov2640_window_set(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);              /* 设置传感器输出窗口 */
uint8_t ov2640_outsize_set(uint16_t width, uint16_t height);                                    /* 设置图像输出大小 */
uint8_t ov2640_image_win_set(uint16_t offx, uint16_t offy, uint16_t width, uint16_t height);    /* 设置图像开窗大小 */
uint8_t ov2640_imagesize_set(uint16_t width, uint16_t height);                                  /* 设置图像尺寸大小 */
void ov2640_flash_extctrl(uint8_t sw);                                                          /* 控制外部闪光灯 */
void ov2640_flash_intctrl(void);                                                                /* 内部控制闪光灯 */

#endif
