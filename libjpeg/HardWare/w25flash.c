/**
 ****************************************************************************************************
 * @file        norflash.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-04-23
 * @brief       NOR Flash��������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
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

#include "w25flash.h"
#include "spi.h"

uint16_t g_norflash_type;
uint8_t spi1_read_write_byte(uint8_t txData) {
    uint8_t rxData;
    HAL_SPI_TransmitReceive(&hspi1, &txData, &rxData, 1, HAL_MAX_DELAY);
    return rxData;
}
/**
 * @brief   ��ʼ��NOR Flash
 * @param   ��
 * @retval  ��
 */
uint8_t norflash_init(void)
{
    uint8_t temp;
    /* ʱ��ʹ�� */
    NORFLASH_CS_GPIO_CLK_ENABLE();
    
    NORFLASH_CS(1);

    g_norflash_type = norflash_read_id();                   /* ��ȡNOR FlashоƬID */
    if (g_norflash_type == NM25Q128)                         /* W25Q256��ʹ��4�ֽڵ�ַģʽ */
    {
        temp = norflash_read_sr(3);                         /* ��״̬�Ĵ���3���жϵ�ַģʽ */
        if ((temp & 0x01) == 0)                             /* �������4�ֽڵ�ַģʽ�����������Ӧ���� */
        {
            norflash_write_enable();                        /* NOR Flashдʹ�� */
            temp |= (1 << 1);                               /* ADP=1�������ϵ�4�ֽڵ�ַģʽ */
            norflash_write_sr(3, temp);                     /* д״̬�Ĵ���3 */
            
            NORFLASH_CS(0);                                 /* ʹ��NOR FlashƬѡ */
            spi1_read_write_byte (NORFLASH_Enable4ByteAddr); /* ʹ��4�ֽڵ�ַģʽ */
            NORFLASH_CS(1);                                 /* ʧ��NOR FlashƬѡ */
        }
				return 0;
    }
		return 1;
}

/**
 * @brief   �ȴ�NOR Flash����
 * @param   ��
 * @retval  ��
 */
static void norflash_wait_busy(void)
{
    while ((norflash_read_sr(1) & 0x01) == 0x01);   /* �ȴ�BUSYλ���� */
}

/**
 * @brief   дʹ��NOR Flash
 * @note    ��S1�Ĵ�����WEL��λ
 * @param   ��
 * @retval  ��
 */
void norflash_write_enable(void)
{
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(NORFLASH_WriteEnable); /* ����дʹ������ */
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
}

/**
 * @brief   ��NOR Flash���͵�ַ
 * @note    ����оƬ�ͺŵĲ�ͬ������3�ֽڻ�4�ֽڵ�ַ
 * @param   address: �����͵ĵ�ַ
 * @retval  ��
 */
static void norflash_send_address(uint32_t address)
{
    if (g_norflash_type == W25Q256)                     /* ֻ��W25Q256֧��4�ֽڵ�ַģʽ */
    {
        spi1_read_write_byte((uint8_t)(address >> 24)); /* ����bit31~bit24��ַ */
    }
    spi1_read_write_byte((uint8_t)(address >> 16));     /* ����bit23~bit16��ַ */
    spi1_read_write_byte((uint8_t)(address >> 8));      /* ����bit15~ bit8��ַ */
    spi1_read_write_byte((uint8_t)address);             /* ���� bit7~ bit0��ַ */
}

/**
 * @brief   ��NOR Flash��״̬�Ĵ���
 * @note    NOR Flashһ����3��״̬�Ĵ���
 *          ״̬�Ĵ���1��
 *          BIT   7   6   5   4   3   2   1   0
 *               SPR  RV  TB BP2 BP1 BP0 WEL BUSY
 *          SPR��״̬�Ĵ�������λ�����WPʹ��
 *          TB��BP2��BP1��BP0��Flash����д��������
 *          WEL��дʹ������
 *          BUSY��æ���λ��1��æ��0�����У�
 *          Ĭ�ϣ�0x00
 *          ״̬�Ĵ���2��
 *          BIT   7   6   5   4   3   2   1   0
 *               SUS CMP LB3 LB2 LB1 (R)  QE SRP1
 *          ״̬�Ĵ���3��
 *          BIT   7       6    5    4   3   2   1   0
 *             HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 * @param   regno: ״̬�Ĵ��������ţ���Χ��1~3
 * @retval  ״̬�Ĵ�����ֵ
 */
uint8_t norflash_read_sr(uint8_t regno)
{
    uint8_t byte;
    uint8_t command;
    
    switch (regno)
    {
        case 1:
        {
            command = NORFLASH_ReadStatusReg1;  /* ��״̬�Ĵ���1ָ�� */
            break;
        }
        case 2:
        {
            command = NORFLASH_ReadStatusReg2;  /* ��״̬�Ĵ���2ָ�� */
            break;
        }
        case 3:
        {
            command = NORFLASH_ReadStatusReg3;  /* ��״̬�Ĵ���3ָ�� */
            break;
        }
        default:
        {
            command = NORFLASH_ReadStatusReg1;  /* Ĭ�϶�״̬�Ĵ���1ָ�� */
            break;
        }
    }
    
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(command);              /* ���Ͷ��Ĵ������� */
    byte = spi1_read_write_byte(0xFF);          /* ��ȡһ���ֽ� */
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
    
    return byte;
}

/**
 * @brief   дNOR Flash��״̬�Ĵ���
 * @note    ״̬�Ĵ���1��
 *          BIT   7   6   5   4   3   2   1   0
 *               SPR  RV  TB BP2 BP1 BP0 WEL BUSY
 *          SPR��״̬�Ĵ�������λ�����WPʹ��
 *          TB��BP2��BP1��BP0��Flash����д��������
 *          WEL��дʹ������
 *          BUSY��æ���λ��1��æ��0�����У�
 *          Ĭ�ϣ�0x00
 *          ״̬�Ĵ���2��
 *          BIT   7   6   5   4   3   2   1   0
 *               SUS CMP LB3 LB2 LB1 (R)  QE SRP1
 *          ״̬�Ĵ���3��
 *          BIT   7       6    5    4   3   2   1   0
 *             HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
 * @param   regno: ״̬�Ĵ��������ţ���Χ��1~3
 * @param   sr   : ��д��״̬�Ĵ�����ֵ
 * @retval  ��
 */
void norflash_write_sr(uint8_t regno, uint8_t sr)
{
    uint8_t command;
    
    switch (regno)
    {
        case 1:
        {
            command = NORFLASH_WriteStatusReg1; /* д״̬�Ĵ���1ָ�� */
            break;
        }
        case 2:
        {
            command = NORFLASH_WriteStatusReg2; /* д״̬�Ĵ���2ָ�� */
            break;
        }
        case 3:
        {
            command = NORFLASH_WriteStatusReg3; /* д״̬�Ĵ���3ָ�� */
            break;
        }
        default:
        {
            command = NORFLASH_WriteStatusReg1; /* Ĭ��д״̬�Ĵ���1ָ�� */
            break;
        }
    }
    
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(command);              /* ���Ͷ��Ĵ������� */
    spi1_read_write_byte(sr);                   /* д��һ���ֽ� */
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
}

/**
 * @brief   ��NOR FlashоƬID
 * @note    NOR FlashоƬID������ļ�norflash.h��NOR FlashоƬID���岿��
 * @param   ��
 * @retval  NOR FlashоƬID
 */
uint16_t norflash_read_id(void)
{
    uint16_t deviceid;
    
    NORFLASH_CS(0);                                     /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(NORFLASH_ManufactDeviceID);    /* ���Ͷ�ID���� */
    spi1_read_write_byte(0);                            /* д��һ���ֽ� */
    spi1_read_write_byte(0);
    spi1_read_write_byte(0);
    deviceid = spi1_read_write_byte(0xFF) << 8;         /* ��ȡ��8λ�ֽ� */
    deviceid |= spi1_read_write_byte(0xFF);             /* ��ȡ��8λ�ֽ� */
    NORFLASH_CS(1);                                     /* ʧ��NOR FlashƬѡ */
    
    return deviceid;
}

/**
 * @brief   ��NOR Flash
 * @note    ��ָ����ַ��ʼ��ȡָ�����ȵ�����
 * @param   pbuf   : ��ȡ�����ݱ���ĵ�ַ
 * @param   pbuf   : ָ����ʼ��ȡ�ĵ�ַ
 * @param   datalen: ָ����ȡ���ݵ��ֽ���
 * @retval  ��
 */
void norflash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;
    
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(NORFLASH_ReadData);    /* ���Ͷ�ȡ���� */
    norflash_send_address(addr);                /* ���͵�ַ */
    for (i=0; i<datalen; i++)                   /* ѭ����ȡ */
    {
        pbuf[i] = spi1_read_write_byte(0xFF);
    }
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
}

/**
 * @brief   ��NOR Flashָ����ַд��ָ�����ȵ�����
 * @note    д�����ݵĳ��Ȳ��ܳ���ָ����ַ����ҳ��ʣ���ֽ���
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ�������Χ��0~ָ����ַ����ҳʣ���ֽ���
 * @retval  ��
 */
static void norflash_write_page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;
    
    norflash_write_enable();                    /* NOR Flashдʹ�� */
    
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(NORFLASH_PageProgram); /* ����дҳ���� */
    norflash_send_address(addr);                /* ���͵�ַ */
    for (i = 0; i < datalen; i++)               /* ѭ��д�� */
    {
        spi1_read_write_byte(pbuf[i]);
    }
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
    
    norflash_wait_busy();                       /* �ȴ�д����� */
}

/**
 * @brief   �޼����NOR Flashָ����ַд��ָ�����ȵ�����
 * @note    ����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0xFF,�����ڷ�0xFF��д������ݽ�ʧ��
 *          �����Զ���ҳ����
 *          ��ָ����ַ��ʼд��ָ�����ȵ����ݣ�����Ҫȷ����ַ��Խ��
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ���
 * @retval  ��
 */
static void norflash_write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    
    pageremain = 256 - (addr % 256);                    /* ���㵱ǰҳʣ����ֽ��� */
    if (datalen <= pageremain)                          /* ������256���ֽ� */
    {
        pageremain = datalen;
    }
    
    /* ��д���ֽڱ�ҳ��ʣ���ַ���ٵ�ʱ��һ����д��
     * ��д��ֱ�ӱ�ҳ��ʣ���ַ�����ʱ����д������ҳ��ʣ���ַ��Ȼ�����ʣ�೤�Ƚ��в�ͬ����
     */
    while (1)
    {
        norflash_write_page(pbuf, addr, pageremain);    /* ��NOR Flashָ����ַд��ָ�����ȵ����� */
        
        if (datalen == pageremain)                      /* д����� */
        {
            break;
        }
        else                                            /* д��δ���� */
        {
            pbuf += pageremain;                         /* ƫ��pbufָ���ַpageremain����д����ֽ��� */
            addr += pageremain;                         /* ƫ��д���ַpageremain����д����ֽ��� */
            datalen -= pageremain;                      /* ����ʣ��д����ֽ��� */
            if (datalen > 256)                          /* ʣ������������256��ֻ����д��һҳ���� */
            {
                pageremain = 256;
            }
            else                                        /* ʣ��������������256����һ����д�� */
            {
                pageremain = datalen;
            }
        }
    }
}

/* �������� */
static uint8_t g_norflash_buf[4096];

/**
 * @brief   дNOR Flash
 * @note    ��ָ����ַ��ʼд��ָ�����ȵ����ݣ��ú�������������
 *          NOR Flashһ���ǣ�256���ֽ�Ϊһ��Page��4096���ֽ�Ϊһ��Sector��16��SectorΪ1��Block
 *          ��������С��λΪSector
 * @param   pbuf   : ��д�����ݵ���ʼ��ַ
 * @param   addr   : ָ����ʼд�����ݵĵ�ַ
 * @param   datalen: ָ��д�����ݵ��ֽ���
 * @retval  ��
 */
void norflash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *norflash_buf;
    
    norflash_buf = g_norflash_buf;                                      /* �������� */
    secpos = addr / 4096;                                               /* �������� */
    secoff = addr % 4096;                                               /* д����ʼ��ַ�ڵ�ǰ������ƫ���� */
    secremain = 4096 - secoff;                                          /* ���㵱����ʣ����ֽ��� */
    if (datalen <= secremain)                                           /* ������4096���ֽ� */
    {
        secremain = datalen;
    }
    
    while (1)
    {
        norflash_read(norflash_buf, secpos * 4096, 4096);               /* ������ǰ�������������ݣ����ڲ���������ָ���д����������� */
        
        for (i=0; i<secremain; i++)                                     /* У������ */
        {
            if (norflash_buf[secoff + i] != 0xFF)                       /* д���������з�0xFF�����ݣ�����Ҫ���� */
            {
                break;
            }
        }
        
        if (i < secremain)                                              /* ��Ҫ���� */
        {
            norflash_erase_sector(secpos);                              /* ������������ */
            
            for (i=0; i<secremain; i++)                                 /* ����д������ݣ���д���������� */
            {
                norflash_buf[i + secoff] = pbuf[i];
            }
            
            norflash_write_nocheck(norflash_buf, secpos * 4096, 4096);  /* д���������� */
        }
        else                                                            /* ����Ҫ����������ֱ��д�� */
        {
            norflash_write_nocheck(pbuf, addr, secremain);              /* ֱ��д����ʣ��Ŀռ� */
        }
        
        if (datalen == secremain)                                       /* д����� */
        {
            break;
        }
        else                                                            /* д��δ���� */
        {
            secpos++;                                                   /* ����������1 */
            secoff = 0;                                                 /* ����ƫ��λ��Ϊ0 */
            pbuf += secremain;                                          /* ƫ��pbufָ���ַsecremain����д����ֽ��� */
            addr += secremain;                                          /* ƫ��д���ַsecremain����д����ֽ��� */
            datalen -= secremain;                                       /* ����ʣ��д����ֽ��� */
            if (datalen > 4096)                                         /* ʣ������������4096��ֻ����д��һ���������� */
            {
                secremain = 4096;
            }
            else                                                        /* ʣ��������������4096����һ����д�� */
            {
                secremain = datalen;
            }
        }
    }
}

/**
 * @brief   ��������NOR FlashоƬ
 * @note    �ȴ�ʱ�䳬��
 * @param   ��
 * @retval  ��
 */
void norflash_erase_chip(void)
{
    norflash_write_enable();                    /* NOR Flashдʹ�� */
    norflash_wait_busy();                       /* �ȴ�NOR Flash���� */
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(NORFLASH_ChipErase);   /* ���Ͳ���оƬ���� */ 
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
    norflash_wait_busy();                       /* �ȴ�оƬ�������� */
}

/**
 * @brief   ����NOR Flashһ������
 * @note    ����һ������������ʱ��Ϊ150����
 * @param   saddr: ���������ţ����ֽڵ�ַ������Χ������ʵ��NOR Flash����ȷ��
 * @retval  ��
 */
void norflash_erase_sector(uint32_t saddr)
{
    saddr *= 4096;                              /* ��������������Ӧ���ֽڵ�ַ */
    norflash_write_enable();                    /* NOR Flashдʹ�� */
    norflash_wait_busy();                       /* �ȴ�NOR Flash���� */
    
    NORFLASH_CS(0);                             /* ʹ��NOR FlashƬѡ */
    spi1_read_write_byte(NORFLASH_SectorErase); /* ���Ͳ����������� */
    norflash_send_address(saddr);               /* ���͵�ַ */
    NORFLASH_CS(1);                             /* ʧ��NOR FlashƬѡ */
    norflash_wait_busy();                       /* �ȴ������������ */
}
