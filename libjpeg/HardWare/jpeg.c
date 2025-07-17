#include "jpeg.h"
#include "stdio.h"
#include "string.h"
#include "ov2640.h"
#include "math.h"
#include "jpeg.h"
#include "stm32f4xx_it.h"
#include <setjmp.h>
#include "network.h"
#include "network_data.h"


extern int frame;
uint8_t ov2640_mode = 0;        //����ģʽ:0,RGB565ģʽ;1,JPEGģʽ
#define jpeg_buf_size 4*1024            //����JPEG���ݻ���jpeg_buf�Ĵ�С(*4�ֽ�)
__ALIGNED(4) uint32_t jpeg_buf[jpeg_buf_size];    //JPEG���ݻ���buf
volatile uint32_t jpeg_data_len = 0;            //buf�е�JPEG��Ч���ݳ���
volatile uint8_t jpeg_data_ok = 0;                //JPEG���ݲɼ���ɱ��?
const char *EFFECTS_TBL[7] = {"Normal", "Negative", "B&W", "Redish", "Greenish", "Bluish", "Antique"};     /* 7����Ч */
const char *JPEG_SIZE_TBL[13] = {"QQVGA", "QCIF", "QVGA", "WGVGA", "CIF", "VGA", "SVGA", "XGA", "WXGA", "SVGA", "WXGA+","SXGA", "UXGA"}; /* JPEGͼƬ 13�ֳߴ� */
uint8_t rgb888[3][Width_raw*Height_raw] __attribute__((at(0x68531800)))={0};                               
extern ai_float in_data[AI_NETWORK_IN_1_SIZE];
static uint8_t in_data_temp[AI_NETWORK_IN_1_SIZE] ;															 
//#define BANK1_SRAM3_ADDR ((uint32_t)(0x68000000))

//uint8_t SramArray[1024 * 1024] __attribute__((at(0X68000000))); // ����������

//																 
const uint16_t jpeg_img_size_tbl[][2] =
        {
                160, 120,       /* QQVGA */
                176, 144,       /* QCIF */
                320, 240,       /* QVGA */
                400, 240,        /* WGVGA */
                352, 288,        /* CIF */
                640, 480,       /* VGA */
                800, 600,       /* SVGA */
                1024, 768,      /* XGA */
                1280, 800,      /* WXGA */
                1280, 960,      /* XVGA */
                1440, 900,      /* WXGA+ */
                1280, 1024,     /* SXGA */
                1600, 1200,     /* UXGA */
        };


void delay_us(uint16_t us)
{
	uint16_t differ=0xffff-us-5; 
	HAL_TIM_Base_Start(&htim6);
	__HAL_TIM_SetCounter(&htim6,differ); 
	while(differ < 0xffff-5) 
	{ 
		differ = __HAL_TIM_GetCounter(&htim6); 
	} 
	HAL_TIM_Base_Stop(&htim6);
 
}
void delay_ms(uint16_t ms)
{
	delay_us(1000*ms);
}


void jpeg_data_process(void) {
    if (ov2640_mode)//ֻ����JPEG��ʽ��,����Ҫ������.
    {
        if (jpeg_data_ok == 0)    //jpeg���ݻ�δ�ɼ���?
        {
            __HAL_DMA_DISABLE(&hdma_dcmi);//�ر�DMA
            while (DMA2_Stream1->CR & 0X01);    //�ȴ�DMA2_Stream1������
            jpeg_data_len = jpeg_buf_size - __HAL_DMA_GET_COUNTER(&hdma_dcmi);//�õ�ʣ�����ݳ���
            jpeg_data_ok = 1;                //���JPEG���ݲɼ��갴��,�ȴ�������������
        }
        if (jpeg_data_ok == 2)    //��һ�ε�jpeg�����Ѿ���������
        {
            __HAL_DMA_SET_COUNTER(&hdma_dcmi, jpeg_buf_size);//���䳤��Ϊjpeg_buf_size*4�ֽ�
            __HAL_DMA_ENABLE(&hdma_dcmi); //��DMA
            jpeg_data_ok = 0;                        //�������δ�ɼ�????
        }
    }

}

extern void dcmi_start(void);

void send_rgb_data(uint8_t *rgb_data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        while ((USART1->SR & 0X40) == 0);  // 等待发�?�缓冲区�?
        USART1->DR = rgb_data[i];          // 发�?�数�?
    }
}


void jpeg_init(void) {

    uint8_t effect = 0, saturation = 2, contrast = 2;
	   uint8_t size = 2;        // 默认QVGA 320*240大小
    while (ov2640_init());       /* 初始化OV2640 */

    ov2640_jpeg_mode(); /* JPEG模式 */
    ov2640_contrast(contrast); //对比�??
    ov2640_color_saturation(saturation); //颜色饱和�??
    ov2640_special_effects(effect); //特殊效果
    ov2640_outsize_set(jpeg_img_size_tbl[size][0], jpeg_img_size_tbl[size][1]); //设置输出大小
    HAL_DMA_Start(&hdma_dcmi, (uint32_t) &DCMI->DR, (uint32_t) &jpeg_buf, jpeg_buf_size);
    dcmi_start();

}
void jpeg_test(){
	    uint32_t i;
    uint8_t *p;


    uint32_t jpeglen;
    uint8_t headok;
    uint32_t jpegstart;
    ov2640_mode = 1;
	        if (jpeg_data_ok == 1) { /* JPEG数据采集完成 */
            p = (uint8_t *)jpeg_buf;
            jpeglen = 0;
            headok = 0;
            for (i = 0; i < ((jpeg_data_len << 2) - 1); i++) { /* 查找JPEG数据，找到JPEG文件�??0xFF�??0xD8以及JPEG文件�??0xFF�??0xD9 */
                if ((p[i] == 0xFF) && (p[i + 1] == 0xD8)) { /* 找到JPEG文件�?? */
                    jpegstart = i;
                    headok = 1;
                }

                if (headok != 0) { /* 找到JPEG文件头后�??始找JPEG文件�?? */
                    if ((p[i] == 0xFF) && (p[i + 1] == 0xD9)) { /* 找到JPEG文件�?? */
                        jpeglen = i - jpegstart + 2;
                        break;
                    }
                }
            }

            if (jpeglen != 0) { /* JPEG文件有效 */
                p += jpegstart; /* 偏移到JPEG文件头位�?? */
//                jpeg_to_rgb(p, jpeglen, (uint8_t *)rgb888); /* 解码JPEG到RGB */
                for (i=0; i<jpeglen; i++)                                           /* ����������Ч��JPEG���ݣ�JPEG����ͷ��JPEG����β�� */
                {
                    USART1->DR = p[i];
                    while ((USART1->SR & 0X40) == 0);
                }
            }

            jpeg_data_ok = 2; /* 处理完JPEG数据，可以开始采集下�??�?? */
        }
}
/* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ���������??? */
int fputc(int ch, FILE *f)
{
	  while ((USART1->SR & 0X40) == 0);               /* �ȴ���һ���ַ��������??? */
    USART1->DR = (uint8_t)ch;                       /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */

    return ch;
	  

}

void rgb565_to_rgb888(uint8_t *rgb565, uint8_t rgb888[3][Width_raw * Height_raw], int src_width, int src_height, int dst_width, int dst_height) {
    memset(rgb888, 0, 3 * dst_width * dst_height);

    float x_ratio = (float)(src_width - 1) / dst_width;
    float y_ratio = (float)(src_height - 1) / dst_height;
    float x_diff, y_diff;
    int x, y, index;
    uint8_t r, g, b;
    uint16_t pixel;
    for (int i = 0; i < dst_height; i++) {
        for (int j = 0; j < dst_width; j++) {
            x = (int)(x_ratio * j);
            y = (int)(y_ratio * i);
            x_diff = (x_ratio * j) - x;
            y_diff = (y_ratio * i) - y;
            index = (y * src_width + x);
					
            uint8_t high_byte = rgb565[index * 2 + 1];
            uint8_t low_byte = rgb565[index * 2];
            pixel = (high_byte << 8) | low_byte;

            uint8_t r1 = (pixel >> 11) & 0x1F;
            uint8_t g1 = (pixel >> 5) & 0x3F;
            uint8_t b1 = pixel & 0x1F;

            r1 = (r1 << 3) | (r1 >> 2);
            g1 = (g1 << 2) | (g1 >> 4);
            b1 = (b1 << 3) | (b1 >> 2);

            uint8_t r2, g2, b2;
            if (x + 1 < src_width) {
                high_byte = rgb565[(index + 1) * 2 + 1];
                low_byte = rgb565[(index + 1) * 2];
                pixel = (high_byte << 8) | low_byte;

                r2 = (pixel >> 11) & 0x1F;
                g2 = (pixel >> 5) & 0x3F;
                b2 = pixel & 0x1F;

                r2 = (r2 << 3) | (r2 >> 2);
                g2 = (g2 << 2) | (g2 >> 4);
                b2 = (b2 << 3) | (b2 >> 2);
            } else {
                r2 = r1;
                g2 = g1;
                b2 = b1;
            }

            uint8_t r3, g3, b3;
            if (y + 1 < src_height) {
                high_byte = rgb565[(index + src_width) * 2 + 1];
                low_byte = rgb565[(index + src_width) * 2];
                pixel = (high_byte << 8) | low_byte;

                r3 = (pixel >> 11) & 0x1F;
                g3 = (pixel >> 5) & 0x3F;
                b3 = pixel & 0x1F;

                r3 = (r3 << 3) | (r3 >> 2);
                g3 = (g3 << 2) | (g3 >> 4);
                b3 = (b3 << 3) | (b3 >> 2);
            } else {
                r3 = r1;
                g3 = g1;
                b3 = b1;
            }

            uint8_t r4, g4, b4;
            if (x + 1 < src_width && y + 1 < src_height) {
                high_byte = rgb565[(index + src_width + 1) * 2 + 1];
                low_byte = rgb565[(index + src_width + 1) * 2];
                pixel = (high_byte << 8) | low_byte;

                r4 = (pixel >> 11) & 0x1F;
                g4 = (pixel >> 5) & 0x3F;
                b4 = pixel & 0x1F;

                r4 = (r4 << 3) | (r4 >> 2);
                g4 = (g4 << 2) | (g4 >> 4);
                b4 = (b4 << 3) | (b4 >> 2);
            } else {
                r4 = r1;
                g4 = g1;
                b4 = b1;
            }

            r = (uint8_t)(
                r1 * (1 - x_diff) * (1 - y_diff) +
                r2 * x_diff * (1 - y_diff) +
                r3 * y_diff * (1 - x_diff) +
                r4 * x_diff * y_diff
            );

            g = (uint8_t)(
                g1 * (1 - x_diff) * (1 - y_diff) +
                g2 * x_diff * (1 - y_diff) +
                g3 * y_diff * (1 - x_diff) +
                g4 * x_diff * y_diff
            );

            b = (uint8_t)(
                b1 * (1 - x_diff) * (1 - y_diff) +
                b2 * x_diff * (1 - y_diff) +
                b3 * y_diff * (1 - x_diff) +
                b4 * x_diff * y_diff
            );

            rgb888[0][i * dst_width + j] = r;
            rgb888[1][i * dst_width + j] = g;
            rgb888[2][i * dst_width + j] = b;


						in_data_temp[(i * dst_width + j)*3]  =rgb888[0][i * dst_width + j];
						in_data_temp[(i * dst_width + j)*3+1]=rgb888[1][i * dst_width + j];
						in_data_temp[(i * dst_width + j)*3+2]=rgb888[2][i * dst_width + j];

//						in_data_temp[i]=rgb888[0][i * dst_width + j]*0.299+rgb888[1][i * dst_width + j]*0.587+rgb888[2][i * dst_width + j]*0.114;


        }
    }
}



void rgb_init(void) {
    uint8_t effect = 0, saturation = 2, contrast = 2;
    while (ov2640_init());       /* 初始化OV2640 */
    ov2640_mode = 0;
    ov2640_rgb565_mode(); /* RGB565模式 */
    ov2640_contrast(contrast); // 对比度
    ov2640_color_saturation(saturation); // 饱和度
    ov2640_special_effects(effect); // 特殊效果
    ov2640_outsize_set(nWidth_raw, nHeight_raw); // 设置输出大小

    __HAL_DCMI_DISABLE_IT(&hdcmi, DCMI_IT_FRAME);
    HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)SRAM_ADDR, DEF_DcmiDmaRxBuff_Size);

}
void rgb_test(void){
		if (frame) {
            HAL_DCMI_Stop(&hdcmi);
            uint8_t *p = (uint8_t *)SRAM_ADDR;
            rgb565_to_rgb888(p, rgb888, nWidth_raw, nHeight_raw, Width_raw, Height_raw);
//
			      for (int i = 0; i < 3*Width_raw * Height_raw; i++) {
							in_data[i]=((float)in_data_temp[i]);
						}
//            // 发�?? RGB888 数据
            for (int i = 0; i < Width_raw * Height_raw; i++) {
                USART1->DR = rgb888[0][i]; // 发�?�红色�?�道数据
                while ((USART1->SR & 0X40) == 0);
                USART1->DR = rgb888[1][i]; // 发�?�绿色�?�道数据
                while ((USART1->SR & 0X40) == 0);
                USART1->DR = rgb888[2][i]; // 发�?�蓝色�?�道数据
                while ((USART1->SR & 0X40) == 0);
            }
//          for (int i = 0; i < 3*Width_raw * Height_raw; i++) {

//						printf("[%d]%d,%f\r\n",i,in_data_temp[i],in_data[i]);
//                USART1->DR =in_data_temp[i];
//                while ((USART1->SR & 0X40) == 0);
//					}
            HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS, (uint32_t)SRAM_ADDR, DEF_DcmiDmaRxBuff_Size);
        }
}

