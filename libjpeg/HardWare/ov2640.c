/**
 ****************************************************************************************************
 * @file        ov2640.c
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

#include "ov2640.h"
#include "sccb.h"
#include "ov2640cfg.h"
#include "main.h"
#include "stdio.h"

extern SRAM_HandleTypeDef hsram1;
extern DMA_HandleTypeDef hdma_dcmi;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
char buf[100];
/**
 * @brief       读OV2640寄存器
 * @param       reg: 寄存器地址
 * @retval      寄存器的值
 */
uint8_t ov2640_read_reg(uint16_t reg)
{
    uint8_t data;
    
    sccb_start();
    sccb_send_byte(OV2640_ADDR);        /* 写命令 */
    delay_us(100);
    sccb_send_byte(reg);
    delay_us(100);
    sccb_stop();
    delay_us(100);
    
    sccb_start();
    sccb_send_byte(OV2640_ADDR | 0x01); /* 读命令 */
    delay_us(100);
    data = sccb_read_byte();
    sccb_nack();
    sccb_stop();
    
    return data;
}

/**
 * @brief       写OV2640寄存器
 * @param       reg : 寄存器地址
 * @param       data: 待写入寄存器的值
 * @retval      写入结果
 *              0: 成功
 *              1: 失败
 */
uint8_t ov2640_write_reg(uint16_t reg, uint8_t data)
{
    uint8_t res = 0;
    
    sccb_start();
    delay_us(100);
    if (sccb_send_byte(OV2640_ADDR) != 0)
    {
        res = 1;
    }
    delay_us(100);
    if (sccb_send_byte(reg) != 0)
    {
        res = 1;
    }
    delay_us(100);
    if (sccb_send_byte(data) != 0)
    {
        res = 1;
    }
    delay_us(100);
    sccb_stop();
    
    return res;
}

/**
 * @brief       初始化OV2640
 * @param       无
 * @retval      初始化结果
 *              0: 成功
 *              1: 失败
 */
uint8_t ov2640_init(void)
{  

    GPIO_InitTypeDef gpio_init_struct = {0};
    uint16_t reg;
    uint16_t i;
    
    HAL_GPIO_Init(OV_FLASH_GPIO_PORT, &gpio_init_struct);   /* 配置OV_FLASH引脚 */
    
    OV2640_PWDN(0);                                         /* Power on */
    delay_ms(10);
    OV2640_RST(0);                                          /* 使能OV2640复位 */
    delay_ms(20);
    OV2640_RST(1);                                          /* 释放OV2640复位 */
    delay_ms(20);
    
    sccb_init();                                            /* 初始化SCCB */
    delay_ms(5);
    
    ov2640_write_reg(OV2640_DSP_RA_DLMT, 0x01);             /* 操作Sensor寄存器 */
    ov2640_write_reg(OV2640_SENSOR_COM7, 0x80);             /* 软件复位OV2640 */
    delay_ms(50);
    
    /* 校验MID */
    reg = ov2640_read_reg(OV2640_SENSOR_MIDH) << 8;         /* 获取OV2640 MID */
    reg |= ov2640_read_reg(OV2640_SENSOR_MIDL);
    if (reg != OV2640_MID)
    {
        return 1;
    }
    
    /* 校验PID */
    reg = ov2640_read_reg(OV2640_SENSOR_PIDH) << 8;         /* 获取OV2640 PID */
    reg |= ov2640_read_reg(OV2640_SENSOR_PIDL);
    if (reg != OV2640_PID)
    {
        return 1;
    }
		
    /* 初始化OV2640寄存器 */
    for (i=0; i<(sizeof(ov2640_uxga_init_reg_tbl) / 2); i++)
    {
        ov2640_write_reg(ov2640_uxga_init_reg_tbl[i][0], ov2640_uxga_init_reg_tbl[i][1]);
    }
    
    return 0;
}

/**
 * @brief       配置OV2640为JPEG模式
 * @param       无
 * @retval      无
 */
void ov2640_jpeg_mode(void)
{
    uint16_t i;
    
    /* 配置YUV422格式 */
    for (i=0; i<(sizeof(ov2640_yuv422_reg_tbl) / 2); i++)
    {
        ov2640_write_reg(ov2640_yuv422_reg_tbl[i][0], ov2640_yuv422_reg_tbl[i][1]);
    }
    
    /* 配置输出JPEG数据 */
    for (i=0; i<(sizeof(ov2640_jpeg_reg_tbl) / 2); i++)
    {
        ov2640_write_reg(ov2640_jpeg_reg_tbl[i][0], ov2640_jpeg_reg_tbl[i][1]);
    }
}

/**
 * @brief       配置OV2640为RGB565模式
 * @param       无
 * @retval      无
 */
void ov2640_rgb565_mode(void)
{
    uint16_t i;
    
    /* 配置输出RGB565数据 */
    for (i=0; i<(sizeof(ov2640_rgb565_reg_tbl) / 4); i++)
    {
        ov2640_write_reg(ov2640_rgb565_reg_tbl[i][0], ov2640_rgb565_reg_tbl[i][1]);
    }
}

/* 自动曝光参数配置
 * 支持5个等级
 */
static const uint8_t OV2640_AUTOEXPOSURE_LEVEL[5][8] = {
    {
        0xFF, 0x01,
        0x24, 0x20,
        0x25, 0x18,
        0x26, 0x60,
    },
    {
        0xFF, 0x01,
        0x24, 0x34,
        0x25, 0x1C,
        0x26, 0x00,
    },
    {
        0xFF, 0x01,
        0x24, 0x3E,
        0x25, 0x38,
        0x26, 0x81,
    },
    {
        0xFF, 0x01,
        0x24, 0x48,
        0x25, 0x40,
        0x26, 0x81,
    },
    {
        0xFF, 0x01,
        0x24, 0x58,
        0x25, 0x50,
        0x26, 0x92,
    },
};

/**
 * @brief       配置OV2640 EV曝光补偿
 * @param       level: EV曝光补偿等级，范围：0~4
 * @retval      无
 */
void ov2640_auto_exposure(uint8_t level)
{
    uint8_t i;
    uint8_t *p;
    
    p = (uint8_t*)OV2640_AUTOEXPOSURE_LEVEL[level];
    for (i=0; i<4; i++)
    { 
        ov2640_write_reg(p[i * 2], p[i * 2 + 1]); 
    }
}

/**
 * @brief       配置OV2640白平衡模式
 * @param       mode : 白平衡模式，范围：0~4
 *   @arg       0: Auto
 *   @arg       1: Sunny
 *   @arg       2: Office
 *   @arg       3: Cloudy
 *   @arg       4: Home
 * @retval      无
 */
void ov2640_light_mode(uint8_t mode)
{
    uint8_t regccval = 0x5E;                /* 默认为Sunny */
    uint8_t regcdval = 0x41;
    uint8_t regceval = 0x54;
    
    switch (mode)
    { 
        case 0:                             /* Auto */
        {
            ov2640_write_reg(0xFF, 0x00);
            ov2640_write_reg(0xC7, 0x00);
            return;
        }
        case 1:                             /* Sunny */
        {
            regccval = 0x5E;
            regcdval = 0x41;
            regceval = 0x54;
            break;
        }
        case 2:                             /* Cloudy */
        {
            regccval = 0x65;
            regcdval = 0x41;
            regceval = 0x4F;
            break;
        }
        case 3:                             /* Office */
        {
            regccval = 0x52;
            regcdval = 0x41;
            regceval = 0x66;
            break;
        }
        case 4:                             /* Home */
        {
            regccval = 0x42;
            regcdval = 0x3F;
            regceval = 0x71;
            break;
        }
        default:
        {
            break;
        }
    }
    
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0xC7, 0x40);           /* AWB OFF  */
    ov2640_write_reg(0xCC, regccval);
    ov2640_write_reg(0xCD, regcdval);
    ov2640_write_reg(0xCE, regceval);
}

/**
 * @brief       配置OV2640色彩饱和度
 * @param       set: 色彩饱和度，范围：0~4
 *   @arg       0: -2
 *   @arg       1: -1
 *   @arg       2: 0
 *   @arg       3: 1
 *   @arg       4: 2
 * @retval      无
 */
void ov2640_color_saturation(uint8_t sat)
{
    uint8_t reg7dval;
    
    reg7dval = ((sat + 2) << 4) | 0x08;
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0x7C, 0x00);
    ov2640_write_reg(0x7D, 0x02);
    ov2640_write_reg(0x7C, 0x03);
    ov2640_write_reg(0x7D, reg7dval);
    ov2640_write_reg(0x7D, reg7dval);
}

/**
 * @brief       配置OV2640亮度
 * @param       bright: 亮度，范围：0~4
 *   @arg       0: -2
 *   @arg       1: -1
 *   @arg       2: 0
 *   @arg       3: 1
 *   @arg       4: 2
 * @retval      无
 */
void ov2640_brightness(uint8_t bright)
{
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0x7C, 0x00);
    ov2640_write_reg(0x7D, 0x04);
    ov2640_write_reg(0x7C, 0x09);
    ov2640_write_reg(0x7D, bright << 4);
    ov2640_write_reg(0x7D, 0x00);
}

/**
 * @brief       配置OV2640对比度
 * @param       contrast: 对比度，范围：0~4
 *   @arg       0: -2
 *   @arg       1: -1
 *   @arg       2: 0
 *   @arg       3: 1
 *   @arg       4: 2
 * @retval      无
 */
void ov2640_contrast(uint8_t contrast)
{
    uint8_t reg7d0val = 0x20;   /* 默认为0 */
    uint8_t reg7d1val = 0x20;
    
    switch (contrast)
    {
        case 0:                 /* -2 */
        {
            reg7d0val = 0x18;
            reg7d1val = 0x34;
            break;
        }
        case 1:                 /* -1 */
        {
            reg7d0val = 0x1C;
            reg7d1val = 0x2A;
            break;
        }
        case 2:                 /* 0 */
        {
            reg7d0val = 0x20;
            reg7d1val = 0x20;
            break;
        }
        case 3:                 /* 1 */
        {
            reg7d0val = 0x24;
            reg7d1val = 0x16;
            break;
        }
        case 4:                 /* 2 */
        {
            reg7d0val = 0x28;
            reg7d1val = 0x0C;
            break;
        }
        default:
        {
            break;
        }
    }
    
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0x7C, 0x00);
    ov2640_write_reg(0x7D, 0x04);
    ov2640_write_reg(0x7C, 0x07);
    ov2640_write_reg(0x7D, 0x20);
    ov2640_write_reg(0x7D, reg7d0val);
    ov2640_write_reg(0x7D, reg7d1val);
    ov2640_write_reg(0x7D, 0x06);
}

/**
 * @brief       配置OV2640特效
 * @param       eft: 特效效果，范围：0~6
 *   @arg       0: 正常
 *   @arg       1: 负片
 *   @arg       2: 黑白
 *   @arg       3: 偏红色
 *   @arg       4: 偏绿色
 *   @arg       5: 偏蓝色
 *   @arg       6: 复古
 * @retval      无
 */
void ov2640_special_effects(uint8_t eft)
{
    uint8_t reg7d0val = 0x00;   /* 默认为正常 */
    uint8_t reg7d1val = 0x80;
    uint8_t reg7d2val = 0x80;
    
    switch(eft)
    {
        case 0:                 /* 正常 */
        {
            reg7d0val = 0x00;
            reg7d1val = 0x80;
            reg7d2val = 0x80;
            break;
        }
        case 1:                 /* 负片 */
        {
            reg7d0val = 0x40;
            reg7d1val = 0x80;
            reg7d2val = 0x80;
            break;
        }
        case 2:                 /* 黑白 */
        {
            reg7d0val = 0x18;
            reg7d1val = 0x80;
            reg7d2val = 0x80;
            break;
        }
        case 3:                 /* 偏红色 */
        {
            reg7d0val = 0x18;
            reg7d1val = 0x40;
            reg7d2val = 0xC0;
            break;
        }
        case 4:                 /* 偏绿色 */
        {
            reg7d0val = 0x18;
            reg7d1val = 0x40;
            reg7d2val = 0x40;
            break;
        }
        case 5:                 /* 偏蓝色 */
        {
            reg7d0val = 0x18;
            reg7d1val = 0xA0;
            reg7d2val = 0x40;
            break;
        }
        case 6:                 /* 复古 */
        {
            reg7d0val = 0x18;
            reg7d1val = 0x40;
            reg7d2val = 0xA6;
            break;
        }
        default:
        {
            break;
        }
    }
    
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0x7C, 0x00);
    ov2640_write_reg(0x7D, reg7d0val);
    ov2640_write_reg(0x7C, 0x05);
    ov2640_write_reg(0x7D, reg7d1val);
    ov2640_write_reg(0x7D, reg7d2val);
}

/**
 * @brief       OV2640彩条测试
 * @param       mode: 模式
 *   @arg       0: 关闭
 *   @arg       1: 彩条
 * @retval      无
 */
void ov2640_color_bar(uint8_t mode)
{
    uint8_t reg;
    
    ov2640_write_reg(0xFF, 0x01);
    reg = ov2640_read_reg(0x12);
    reg &= ~(1 << 1);
    if (mode)
    {
        reg |= (1 << 1);
    }
    ov2640_write_reg(0x12, reg);
}

/**
 * @bref        设置传感器输出窗口
 * @param       sx   : 传感器输出窗口的起始地址X
 * @param       sy   : 传感器输出窗口的起始地址Y
 * @param       width: 传感器输出窗口的宽度（对应horizontal）
 * @param       hight: 传感器输出窗口的高度（对应vertical）
 * @retval      无
 */
void ov2640_window_set(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    uint16_t endx;
    uint16_t endy;
    uint8_t temp;
    
    endx = sx + (width >> 1);
    endy = sy + (height >> 1);
    
    ov2640_write_reg(0xFF, 0x01);
    temp = ov2640_read_reg(0x03);               /* 读取Vref之前的值 */
    temp &= 0xF0;
    temp |= ((endy & 0x03) << 2) | (sy & 0x03);
    ov2640_write_reg(0x03, temp);               /* 设置Vref的start和end的最低2位 */ 
    ov2640_write_reg(0x19, sy >> 2);            /* 设置Vref的start高8位 */
    ov2640_write_reg(0x1A, endy >> 2);          /* 设置Vref的end的高8位 */
    
    temp = ov2640_read_reg(0x32);               /* 读取Href之前的值 */
    temp &= 0xC0;
    temp |= ((endx & 0x07) << 3) | (sx & 0x07);
    ov2640_write_reg(0x32, temp);               /* 设置Href的start和end的最低3位 */
    ov2640_write_reg(0x17, sx >> 3);            /* 设置Href的start高8位 */
    ov2640_write_reg(0x18, endx >> 3);          /* 设置Href的end的高8位 */
}

/** 
 * @bref        设置图像输出大小
 * @note        OV2640输出图像的大小（分辨率），完全由该函数确定
 *              width和height必须是4的倍数
 * @param       width : 输出输出的宽度（对应horizontal）
 * @param       height: 输出输出的高度（对应vertical）
 * @retval      设置结果
 *              0   : 成功
 *              其他: 失败
 */
uint8_t ov2640_outsize_set(uint16_t width, uint16_t height)
{
    uint16_t outh;
    uint16_t outw;
    uint8_t temp;
    
    if ((width & 3) != 0)
    {
        return 1;
    }
    
    if ((height & 3) != 0)
    {
        return 2;
    }
    
    outw = width >> 2;
    outh = height >> 2;
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0xE0, 0x04);
    ov2640_write_reg(0x5A, outw & 0xFF);    /* 设置OUTW的低八位 */
    ov2640_write_reg(0x5B, outh & 0xFF);    /* 设置OUTH的低八位 */
    
    temp = (outw >> 8) & 0x03;
    temp |= (outh >> 6) & 0x04;
    ov2640_write_reg(0x5C, temp);           /* 设置OUTH/OUTW的高位 */
    ov2640_write_reg(0xE0, 0x00);
    
    return 0;
}

/**
 * @brief       设置图像开窗大小
 *   @note      OV2640输出图像的大小（分辨率），完全由该函数确定
 *              由于开启了scale功能，用于输出的图像窗口为：xsize - 2 * offx, ysize - 2 * offy
 *              实际输出(width,height)，是在xsize - 2 * offx, ysize - 2 * offy的基础上进行缩放处理
 *              一般设置offx和offy的值为16和4，更小也是可以，不过默认是16和4
 * @param       offx : 输出图像在ov2640_image_window_set设定窗口X方向上的偏移
 * @param       offy: 输出图像在ov2640_image_window_set设定窗口Y方向上的偏移
 * @param       width : 输出输出的宽度（对应horizontal）
 * @param       height: 输出输出的高度（对应vertical）
 * @retval      设置结果
 *              0   : 成功
 *              其他: 失败
 */
uint8_t ov2640_image_win_set(uint16_t offx, uint16_t offy, uint16_t width, uint16_t height)
{
    uint16_t hsize;
    uint16_t vsize;
    uint8_t temp;
    
    if ((width & 3) != 0)
    {
        return 1;
    }
    
    if ((height & 3) != 0)
    {
        return 2;
    }
    
    hsize = width >> 2;
    vsize = height >> 2;
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0xE0, 0x04);
    ov2640_write_reg(0x51, hsize & 0xFF);           /* 设置H_SIZE的低八位 */
    ov2640_write_reg(0x52, vsize & 0xFF);           /* 设置V_SIZE的低八位 */
    ov2640_write_reg(0x53, offx & 0xFF);            /* 设置offx的低八位 */
    ov2640_write_reg(0x54, offy & 0xFF);            /* 设置offy的低八位 */
    temp = (vsize >> 1) & 0x80;
    temp |= (offy >> 4) & 0x70;
    temp |= (hsize>>5) & 0x08;
    temp |= (offx >> 8) & 0x07; 
    ov2640_write_reg(0x55, temp);                   /* 设置H_SIZE/V_SIZE/OFFX,OFFY的高位 */
    ov2640_write_reg(0x57, (hsize >> 2) & 0x80);    /* 设置H_SIZE/V_SIZE/OFFX,OFFY的高位 */
    ov2640_write_reg(0xE0, 0x00);
    
    return 0;
}

/**
 * @bref        设置图像尺寸大小
 * @note        UXGA: 1600*1200
 *              SVGA: 800*600
 *              CIF : 352*288
 * @param       width : 图像的宽度
 * @param       height: 图像的高度
 * @retval      设置结果
 *              0   : 成功
 *              其他: 失败
 */
uint8_t ov2640_imagesize_set(uint16_t width, uint16_t height)
{ 
    uint8_t temp;
    
    ov2640_write_reg(0xFF, 0x00);
    ov2640_write_reg(0xE0, 0x04);
    ov2640_write_reg(0xC0, (width) >> 3 & 0xFF);    /* 设置HSIZE的10:3位 */
    ov2640_write_reg(0xC1, (height) >> 3 & 0xFF);   /* 设置VSIZE的10:3位 */
    temp = (width & 0x07) << 3;
    temp |= height & 0x07;
    temp |= (width >> 4) & 0x80;
    ov2640_write_reg(0x8C, temp);
    ov2640_write_reg(0xE0, 0x00);
    
    return 0;
}

/**
 * @bref        控制外部闪光灯
 * @param       sw: 控制信号
 *              0: 关闭
 *              1: 打开
 * @retval      无
 */
void ov2640_flash_extctrl(uint8_t sw)
{
    if(sw != 0)
    {
        OV2640_FLASH(1);
    }
    else
    {
        OV2640_FLASH(0);
    }
}

/**
 * @bref        内部控制闪光灯
 * @note        控制信号从OV2640的STROBE引脚自动输出
 * @retval      无
 */
void ov2640_flash_intctrl(void)
{
    ov2640_write_reg(0xFF, 0x01);
    ov2640_write_reg(0x4B, 0x81);
    ov2640_write_reg(0x4B, 0x01);
}
