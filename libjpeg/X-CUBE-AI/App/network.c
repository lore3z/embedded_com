/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-07-17T23:05:46+0800
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0x111e80724e190b4ce1a44f139c2ee9ab"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2025-07-17T23:05:46+0800"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_input_10_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 4800, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  nl_0_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  nl_3_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_4_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 12800, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  nl_6_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_7_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  nl_9_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3200, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_12_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  nl_12_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_13_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_15_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  nl_15_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_16_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_22_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  nl_22_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_23_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_18_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  nl_18_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_19_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_21_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_25_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  nl_26_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_27_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_29_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  nl_29_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_30_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  pool_32_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  gemm_33_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  nl_34_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 3, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 864, AI_STATIC)

/* Array#37 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#38 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_1_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#39 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#40 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#41 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#42 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_4_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#43 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_4_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#44 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#45 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#46 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_7_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#47 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_7_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#48 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#49 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#50 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#51 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_10_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#52 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_12_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#53 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_12_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#54 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_13_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#55 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_13_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#56 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_15_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#57 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_15_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#58 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_16_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#59 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_16_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#60 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_22_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1024, AI_STATIC)

/* Array#61 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_22_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#62 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_23_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#63 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_23_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#64 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_18_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 25600, AI_STATIC)

/* Array#65 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_18_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#66 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_19_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#67 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_19_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#68 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#69 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#70 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_27_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#71 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_27_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#72 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_29_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 9216, AI_STATIC)

/* Array#73 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_29_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#74 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_30_scale_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#75 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_30_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#76 */
AI_ARRAY_OBJ_DECLARE(
  gemm_33_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 96, AI_STATIC)

/* Array#77 */
AI_ARRAY_OBJ_DECLARE(
  gemm_33_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)

/* Array#78 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 27, AI_STATIC)

/* Array#79 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#80 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#81 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_9_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#82 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_12_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#83 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_15_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#84 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_22_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#85 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_18_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 800, AI_STATIC)

/* Array#86 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#87 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_29_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_4_scale, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_4_scale_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_4_bias, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_4_bias_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_weights, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_6_weights_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_bias, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_6_bias_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_7_scale, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_7_scale_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_7_bias, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_7_bias_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_weights, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_9_weights_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_bias, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_9_bias_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_scale, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_10_scale_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_10_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_weights, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_12_weights_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_bias, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_12_bias_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_13_scale, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_13_scale_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_13_bias, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_13_bias_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_15_weights, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_15_weights_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_15_bias, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_15_bias_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_16_scale, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_16_scale_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_16_bias, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_16_bias_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_22_weights, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 32, 1, 1, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 4096),
  1, &conv2d_22_weights_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_22_bias, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_22_bias_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_23_scale, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_23_scale_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_23_bias, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_23_bias_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_18_weights, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 32, 5, 5, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 20480),
  1, &conv2d_18_weights_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_18_bias, AI_STATIC,
  23, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_18_bias_array, NULL)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_19_scale, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_19_scale_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_19_bias, AI_STATIC,
  25, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_19_bias_array, NULL)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_26_weights, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_26_weights_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_26_bias, AI_STATIC,
  27, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_26_bias_array, NULL)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_27_scale, AI_STATIC,
  28, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_27_scale_array, NULL)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_27_bias, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_27_bias_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_29_weights, AI_STATIC,
  30, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_29_weights_array, NULL)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_29_bias, AI_STATIC,
  31, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_29_bias_array, NULL)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_30_scale, AI_STATIC,
  32, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_30_scale_array, NULL)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_30_bias, AI_STATIC,
  33, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_30_bias_array, NULL)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  gemm_33_weights, AI_STATIC,
  34, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 1, 1), AI_STRIDE_INIT(4, 4, 128, 384, 384),
  1, &gemm_33_weights_array, NULL)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  gemm_33_bias, AI_STATIC,
  35, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &gemm_33_bias_array, NULL)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_scratch0, AI_STATIC,
  36, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 3), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &conv2d_0_scratch0_array, NULL)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  37, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_scratch0, AI_STATIC,
  38, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_6_scratch0_array, NULL)

/* Tensor #39 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_scratch0, AI_STATIC,
  39, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_9_scratch0_array, NULL)

/* Tensor #40 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_scratch0, AI_STATIC,
  40, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_12_scratch0_array, NULL)

/* Tensor #41 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_15_scratch0, AI_STATIC,
  41, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_15_scratch0_array, NULL)

/* Tensor #42 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_22_scratch0, AI_STATIC,
  42, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_22_scratch0_array, NULL)

/* Tensor #43 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_18_scratch0, AI_STATIC,
  43, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &conv2d_18_scratch0_array, NULL)

/* Tensor #44 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_26_scratch0, AI_STATIC,
  44, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_26_scratch0_array, NULL)

/* Tensor #45 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_29_scratch0, AI_STATIC,
  45, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_29_scratch0_array, NULL)

/* Tensor #46 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_10_output, AI_STATIC,
  46, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 40, 40), AI_STRIDE_INIT(4, 4, 4, 12, 480),
  1, &serving_default_input_10_output_array, NULL)

/* Tensor #47 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_output, AI_STATIC,
  47, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &conv2d_0_output_array, NULL)

/* Tensor #48 */
AI_TENSOR_OBJ_DECLARE(
  nl_0_nl_output, AI_STATIC,
  48, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &nl_0_nl_output_array, NULL)

/* Tensor #49 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_1_output, AI_STATIC,
  49, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &eltwise_1_output_array, NULL)

/* Tensor #50 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  50, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &conv2d_3_output_array, NULL)

/* Tensor #51 */
AI_TENSOR_OBJ_DECLARE(
  nl_3_nl_output, AI_STATIC,
  51, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &nl_3_nl_output_array, NULL)

/* Tensor #52 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_4_output, AI_STATIC,
  52, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 20, 20), AI_STRIDE_INIT(4, 4, 4, 128, 2560),
  1, &eltwise_4_output_array, NULL)

/* Tensor #53 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_output, AI_STATIC,
  53, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 10, 10), AI_STRIDE_INIT(4, 4, 4, 128, 1280),
  1, &conv2d_6_output_array, NULL)

/* Tensor #54 */
AI_TENSOR_OBJ_DECLARE(
  nl_6_nl_output, AI_STATIC,
  54, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 10, 10), AI_STRIDE_INIT(4, 4, 4, 128, 1280),
  1, &nl_6_nl_output_array, NULL)

/* Tensor #55 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_7_output, AI_STATIC,
  55, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 10, 10), AI_STRIDE_INIT(4, 4, 4, 128, 1280),
  1, &eltwise_7_output_array, NULL)

/* Tensor #56 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_9_output, AI_STATIC,
  56, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 10, 10), AI_STRIDE_INIT(4, 4, 4, 128, 1280),
  1, &conv2d_9_output_array, NULL)

/* Tensor #57 */
AI_TENSOR_OBJ_DECLARE(
  nl_9_nl_output, AI_STATIC,
  57, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 10, 10), AI_STRIDE_INIT(4, 4, 4, 128, 1280),
  1, &nl_9_nl_output_array, NULL)

/* Tensor #58 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_10_output, AI_STATIC,
  58, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 10, 10), AI_STRIDE_INIT(4, 4, 4, 128, 1280),
  1, &eltwise_10_output_array, NULL)

/* Tensor #59 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_12_output, AI_STATIC,
  59, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &conv2d_12_output_array, NULL)

/* Tensor #60 */
AI_TENSOR_OBJ_DECLARE(
  nl_12_nl_output, AI_STATIC,
  60, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &nl_12_nl_output_array, NULL)

/* Tensor #61 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_13_output, AI_STATIC,
  61, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &eltwise_13_output_array, NULL)

/* Tensor #62 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_15_output, AI_STATIC,
  62, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &conv2d_15_output_array, NULL)

/* Tensor #63 */
AI_TENSOR_OBJ_DECLARE(
  nl_15_nl_output, AI_STATIC,
  63, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &nl_15_nl_output_array, NULL)

/* Tensor #64 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_16_output, AI_STATIC,
  64, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &eltwise_16_output_array, NULL)

/* Tensor #65 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_22_output, AI_STATIC,
  65, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &conv2d_22_output_array, NULL)

/* Tensor #66 */
AI_TENSOR_OBJ_DECLARE(
  nl_22_nl_output, AI_STATIC,
  66, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &nl_22_nl_output_array, NULL)

/* Tensor #67 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_23_output, AI_STATIC,
  67, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &eltwise_23_output_array, NULL)

/* Tensor #68 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_18_output, AI_STATIC,
  68, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &conv2d_18_output_array, NULL)

/* Tensor #69 */
AI_TENSOR_OBJ_DECLARE(
  nl_18_nl_output, AI_STATIC,
  69, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &nl_18_nl_output_array, NULL)

/* Tensor #70 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_19_output, AI_STATIC,
  70, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &eltwise_19_output_array, NULL)

/* Tensor #71 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_21_output, AI_STATIC,
  71, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &eltwise_21_output_array, NULL)

/* Tensor #72 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_25_output, AI_STATIC,
  72, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 5, 5), AI_STRIDE_INIT(4, 4, 4, 128, 640),
  1, &eltwise_25_output_array, NULL)

/* Tensor #73 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_26_output, AI_STATIC,
  73, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_26_output_array, NULL)

/* Tensor #74 */
AI_TENSOR_OBJ_DECLARE(
  nl_26_nl_output, AI_STATIC,
  74, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &nl_26_nl_output_array, NULL)

/* Tensor #75 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_27_output, AI_STATIC,
  75, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &eltwise_27_output_array, NULL)

/* Tensor #76 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_29_output, AI_STATIC,
  76, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &conv2d_29_output_array, NULL)

/* Tensor #77 */
AI_TENSOR_OBJ_DECLARE(
  nl_29_nl_output, AI_STATIC,
  77, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &nl_29_nl_output_array, NULL)

/* Tensor #78 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_30_output, AI_STATIC,
  78, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 3, 3), AI_STRIDE_INIT(4, 4, 4, 128, 384),
  1, &eltwise_30_output_array, NULL)

/* Tensor #79 */
AI_TENSOR_OBJ_DECLARE(
  pool_32_output, AI_STATIC,
  79, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &pool_32_output_array, NULL)

/* Tensor #80 */
AI_TENSOR_OBJ_DECLARE(
  gemm_33_output, AI_STATIC,
  80, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &gemm_33_output_array, NULL)

/* Tensor #81 */
AI_TENSOR_OBJ_DECLARE(
  nl_34_output, AI_STATIC,
  81, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &nl_34_output_array, NULL)

/* Tensor #82 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_weights, AI_STATIC,
  82, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 32), AI_STRIDE_INIT(4, 4, 12, 384, 1152),
  1, &conv2d_0_weights_array, NULL)

/* Tensor #83 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_0_bias, AI_STATIC,
  83, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_0_bias_array, NULL)

/* Tensor #84 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_1_scale, AI_STATIC,
  84, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_1_scale_array, NULL)

/* Tensor #85 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_1_bias, AI_STATIC,
  85, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &eltwise_1_bias_array, NULL)

/* Tensor #86 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  86, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 32), AI_STRIDE_INIT(4, 4, 128, 4096, 12288),
  1, &conv2d_3_weights_array, NULL)

/* Tensor #87 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  87, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_3_bias_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_34_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_33_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_34_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_34_layer, 34,
  NL_TYPE, 0x0, NULL,
  nl, forward_sm,
  &nl_34_chain,
  NULL, &nl_34_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_33_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_32_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_33_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_33_weights, &gemm_33_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  gemm_33_layer, 33,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &gemm_33_chain,
  NULL, &nl_34_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_32_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_30_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_32_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_32_layer, 32,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap,
  &pool_32_chain,
  NULL, &gemm_33_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(3, 3), 
  .pool_stride = AI_SHAPE_2D_INIT(3, 3), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_30_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_29_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_30_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_30_scale, &eltwise_30_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_30_layer, 31,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_30_chain,
  NULL, &pool_32_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_29_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_29_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_29_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_29_nl_layer, 29,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_29_nl_chain,
  NULL, &eltwise_30_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_29_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_27_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_29_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_29_weights, &conv2d_29_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_29_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_29_layer, 29,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_29_chain,
  NULL, &nl_29_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_27_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_26_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_27_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_27_scale, &eltwise_27_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_27_layer, 28,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_27_chain,
  NULL, &conv2d_29_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_26_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_26_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_26_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_26_nl_layer, 26,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_26_nl_chain,
  NULL, &eltwise_27_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_26_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_25_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_26_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_26_weights, &conv2d_26_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_26_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_26_layer, 26,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_26_chain,
  NULL, &nl_26_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_25_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_21_output, &eltwise_23_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_25_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_25_layer, 25,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &eltwise_25_chain,
  NULL, &conv2d_26_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_21_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_16_output, &eltwise_19_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_21_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_21_layer, 21,
  ELTWISE_TYPE, 0x0, NULL,
  eltwise, forward_eltwise,
  &eltwise_21_chain,
  NULL, &eltwise_25_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_19_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_18_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_19_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_19_scale, &eltwise_19_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_19_layer, 20,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_19_chain,
  NULL, &eltwise_21_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_18_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_18_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_18_nl_layer, 18,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_18_nl_chain,
  NULL, &eltwise_19_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_18_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_18_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_18_weights, &conv2d_18_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_18_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_18_layer, 18,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_18_chain,
  NULL, &nl_18_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 2, 2, 2, 2), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_23_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_22_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_23_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_23_scale, &eltwise_23_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_23_layer, 24,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_23_chain,
  NULL, &conv2d_18_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_22_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_22_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_22_nl_layer, 22,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_22_nl_chain,
  NULL, &eltwise_23_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_22_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_22_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_22_weights, &conv2d_22_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_22_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_22_layer, 22,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_22_chain,
  NULL, &nl_22_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_16_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_15_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_16_scale, &eltwise_16_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_16_layer, 17,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_16_chain,
  NULL, &conv2d_22_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_15_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_15_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_15_nl_layer, 15,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_15_nl_chain,
  NULL, &eltwise_16_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_15_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_15_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_15_weights, &conv2d_15_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_15_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_15_layer, 15,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_15_chain,
  NULL, &nl_15_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_13_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_12_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_13_scale, &eltwise_13_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_13_layer, 14,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_13_chain,
  NULL, &conv2d_15_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_12_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_12_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_12_nl_layer, 12,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_12_nl_chain,
  NULL, &eltwise_13_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_12_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_12_weights, &conv2d_12_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_12_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_12_layer, 12,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_12_chain,
  NULL, &nl_12_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_10_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_9_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_10_scale, &eltwise_10_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_10_layer, 11,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_10_chain,
  NULL, &conv2d_12_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_9_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_9_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_9_nl_layer, 9,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_9_nl_chain,
  NULL, &eltwise_10_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_9_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_9_weights, &conv2d_9_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_9_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_9_layer, 9,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_9_chain,
  NULL, &nl_9_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_6_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_7_scale, &eltwise_7_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_7_layer, 8,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_7_chain,
  NULL, &conv2d_9_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_6_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_6_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_6_nl_layer, 6,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_6_nl_chain,
  NULL, &eltwise_7_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_6_weights, &conv2d_6_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_6_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_6_layer, 6,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_6_chain,
  NULL, &nl_6_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_4_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_3_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_4_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_4_scale, &eltwise_4_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_4_layer, 5,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_4_chain,
  NULL, &conv2d_6_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_3_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_3_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_3_nl_layer, 3,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_3_nl_chain,
  NULL, &eltwise_4_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_3_chain,
  NULL, &nl_3_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 1, 1, 1, 1), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_0_nl_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_1_scale, &eltwise_1_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_1_layer, 2,
  BN_TYPE, 0x0, NULL,
  bn, forward_bn,
  &eltwise_1_chain,
  NULL, &conv2d_3_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_0_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_0_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_0_nl_layer, 0,
  NL_TYPE, 0x0, NULL,
  nl, forward_relu,
  &nl_0_nl_chain,
  NULL, &eltwise_1_layer, AI_STATIC, 
  .nl_params = NULL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &serving_default_input_10_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_0_weights, &conv2d_0_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_0_scratch0, NULL)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_0_layer, 0,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_if32of32wf32,
  &conv2d_0_chain,
  NULL, &nl_0_nl_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 2, 2), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_SAME, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 372236, 1, 1),
    372236, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 62988, 1, 1),
    62988, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_34_output),
  &conv2d_0_layer, 0x5c857619, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 372236, 1, 1),
      372236, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 62988, 1, 1),
      62988, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_10_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_34_output),
  &conv2d_0_layer, 0x5c857619, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_input_10_output_array.data = AI_PTR(g_network_activations_map[0] + 43680);
    serving_default_input_10_output_array.data_start = AI_PTR(g_network_activations_map[0] + 43680);
    conv2d_0_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 62880);
    conv2d_0_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 62880);
    conv2d_0_output_array.data = AI_PTR(g_network_activations_map[0] + 6912);
    conv2d_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6912);
    nl_0_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 6912);
    nl_0_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6912);
    eltwise_1_output_array.data = AI_PTR(g_network_activations_map[0] + 6912);
    eltwise_1_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6912);
    conv2d_3_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 58112);
    conv2d_3_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 58112);
    conv2d_3_output_array.data = AI_PTR(g_network_activations_map[0] + 1408);
    conv2d_3_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1408);
    nl_3_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 1408);
    nl_3_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1408);
    eltwise_4_output_array.data = AI_PTR(g_network_activations_map[0] + 1408);
    eltwise_4_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1408);
    conv2d_6_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 52608);
    conv2d_6_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 52608);
    conv2d_6_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_6_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    nl_6_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 12800);
    nl_6_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 12800);
    eltwise_7_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_7_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_9_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 12800);
    conv2d_9_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 12800);
    conv2d_9_output_array.data = AI_PTR(g_network_activations_map[0] + 13952);
    conv2d_9_output_array.data_start = AI_PTR(g_network_activations_map[0] + 13952);
    nl_9_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_9_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_10_output_array.data = AI_PTR(g_network_activations_map[0] + 12800);
    eltwise_10_output_array.data_start = AI_PTR(g_network_activations_map[0] + 12800);
    conv2d_12_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_12_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_12_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    conv2d_12_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    nl_12_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 4352);
    nl_12_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4352);
    eltwise_13_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_13_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_15_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 3200);
    conv2d_15_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 3200);
    conv2d_15_output_array.data = AI_PTR(g_network_activations_map[0] + 4352);
    conv2d_15_output_array.data_start = AI_PTR(g_network_activations_map[0] + 4352);
    nl_15_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_15_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_16_output_array.data = AI_PTR(g_network_activations_map[0] + 3200);
    eltwise_16_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3200);
    conv2d_22_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_22_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_22_output_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    conv2d_22_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    nl_22_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_22_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_23_output_array.data = AI_PTR(g_network_activations_map[0] + 6400);
    eltwise_23_output_array.data_start = AI_PTR(g_network_activations_map[0] + 6400);
    conv2d_18_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_18_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_18_output_array.data = AI_PTR(g_network_activations_map[0] + 9600);
    conv2d_18_output_array.data_start = AI_PTR(g_network_activations_map[0] + 9600);
    nl_18_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_18_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_19_output_array.data = AI_PTR(g_network_activations_map[0] + 9600);
    eltwise_19_output_array.data_start = AI_PTR(g_network_activations_map[0] + 9600);
    eltwise_21_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_21_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_25_output_array.data = AI_PTR(g_network_activations_map[0] + 3200);
    eltwise_25_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3200);
    conv2d_26_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_26_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_26_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    conv2d_26_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    nl_26_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_26_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_27_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_27_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    conv2d_29_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_29_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_29_output_array.data = AI_PTR(g_network_activations_map[0] + 2304);
    conv2d_29_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2304);
    nl_29_nl_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_29_nl_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    eltwise_30_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_30_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    pool_32_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    pool_32_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    gemm_33_output_array.data = AI_PTR(g_network_activations_map[0] + 128);
    gemm_33_output_array.data_start = AI_PTR(g_network_activations_map[0] + 128);
    nl_34_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_34_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    conv2d_0_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_0_weights_array.data = AI_PTR(g_network_weights_map[0] + 0);
    conv2d_0_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    conv2d_0_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_0_bias_array.data = AI_PTR(g_network_weights_map[0] + 3456);
    conv2d_0_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 3456);
    eltwise_1_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_1_scale_array.data = AI_PTR(g_network_weights_map[0] + 3584);
    eltwise_1_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 3584);
    eltwise_1_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_1_bias_array.data = AI_PTR(g_network_weights_map[0] + 3712);
    eltwise_1_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 3712);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(g_network_weights_map[0] + 3840);
    conv2d_3_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 3840);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(g_network_weights_map[0] + 40704);
    conv2d_3_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 40704);
    eltwise_4_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_4_scale_array.data = AI_PTR(g_network_weights_map[0] + 40832);
    eltwise_4_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 40832);
    eltwise_4_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_4_bias_array.data = AI_PTR(g_network_weights_map[0] + 40960);
    eltwise_4_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 40960);
    conv2d_6_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_6_weights_array.data = AI_PTR(g_network_weights_map[0] + 41088);
    conv2d_6_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 41088);
    conv2d_6_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_6_bias_array.data = AI_PTR(g_network_weights_map[0] + 77952);
    conv2d_6_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 77952);
    eltwise_7_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_7_scale_array.data = AI_PTR(g_network_weights_map[0] + 78080);
    eltwise_7_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 78080);
    eltwise_7_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_7_bias_array.data = AI_PTR(g_network_weights_map[0] + 78208);
    eltwise_7_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 78208);
    conv2d_9_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_weights_array.data = AI_PTR(g_network_weights_map[0] + 78336);
    conv2d_9_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 78336);
    conv2d_9_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_9_bias_array.data = AI_PTR(g_network_weights_map[0] + 115200);
    conv2d_9_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 115200);
    eltwise_10_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_10_scale_array.data = AI_PTR(g_network_weights_map[0] + 115328);
    eltwise_10_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 115328);
    eltwise_10_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_10_bias_array.data = AI_PTR(g_network_weights_map[0] + 115456);
    eltwise_10_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 115456);
    conv2d_12_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_12_weights_array.data = AI_PTR(g_network_weights_map[0] + 115584);
    conv2d_12_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 115584);
    conv2d_12_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_12_bias_array.data = AI_PTR(g_network_weights_map[0] + 152448);
    conv2d_12_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 152448);
    eltwise_13_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_13_scale_array.data = AI_PTR(g_network_weights_map[0] + 152576);
    eltwise_13_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 152576);
    eltwise_13_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_13_bias_array.data = AI_PTR(g_network_weights_map[0] + 152704);
    eltwise_13_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 152704);
    conv2d_15_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_15_weights_array.data = AI_PTR(g_network_weights_map[0] + 152832);
    conv2d_15_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 152832);
    conv2d_15_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_15_bias_array.data = AI_PTR(g_network_weights_map[0] + 189696);
    conv2d_15_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 189696);
    eltwise_16_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_16_scale_array.data = AI_PTR(g_network_weights_map[0] + 189824);
    eltwise_16_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 189824);
    eltwise_16_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_16_bias_array.data = AI_PTR(g_network_weights_map[0] + 189952);
    eltwise_16_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 189952);
    conv2d_22_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_22_weights_array.data = AI_PTR(g_network_weights_map[0] + 190080);
    conv2d_22_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 190080);
    conv2d_22_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_22_bias_array.data = AI_PTR(g_network_weights_map[0] + 194176);
    conv2d_22_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 194176);
    eltwise_23_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_23_scale_array.data = AI_PTR(g_network_weights_map[0] + 194304);
    eltwise_23_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 194304);
    eltwise_23_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_23_bias_array.data = AI_PTR(g_network_weights_map[0] + 194432);
    eltwise_23_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 194432);
    conv2d_18_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_18_weights_array.data = AI_PTR(g_network_weights_map[0] + 194560);
    conv2d_18_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 194560);
    conv2d_18_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_18_bias_array.data = AI_PTR(g_network_weights_map[0] + 296960);
    conv2d_18_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 296960);
    eltwise_19_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_19_scale_array.data = AI_PTR(g_network_weights_map[0] + 297088);
    eltwise_19_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 297088);
    eltwise_19_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_19_bias_array.data = AI_PTR(g_network_weights_map[0] + 297216);
    eltwise_19_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 297216);
    conv2d_26_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_26_weights_array.data = AI_PTR(g_network_weights_map[0] + 297344);
    conv2d_26_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 297344);
    conv2d_26_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_26_bias_array.data = AI_PTR(g_network_weights_map[0] + 334208);
    conv2d_26_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 334208);
    eltwise_27_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_27_scale_array.data = AI_PTR(g_network_weights_map[0] + 334336);
    eltwise_27_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 334336);
    eltwise_27_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_27_bias_array.data = AI_PTR(g_network_weights_map[0] + 334464);
    eltwise_27_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 334464);
    conv2d_29_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_29_weights_array.data = AI_PTR(g_network_weights_map[0] + 334592);
    conv2d_29_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 334592);
    conv2d_29_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_29_bias_array.data = AI_PTR(g_network_weights_map[0] + 371456);
    conv2d_29_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 371456);
    eltwise_30_scale_array.format |= AI_FMT_FLAG_CONST;
    eltwise_30_scale_array.data = AI_PTR(g_network_weights_map[0] + 371584);
    eltwise_30_scale_array.data_start = AI_PTR(g_network_weights_map[0] + 371584);
    eltwise_30_bias_array.format |= AI_FMT_FLAG_CONST;
    eltwise_30_bias_array.data = AI_PTR(g_network_weights_map[0] + 371712);
    eltwise_30_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 371712);
    gemm_33_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_33_weights_array.data = AI_PTR(g_network_weights_map[0] + 371840);
    gemm_33_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 371840);
    gemm_33_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_33_bias_array.data = AI_PTR(g_network_weights_map[0] + 372224);
    gemm_33_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 372224);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 7277168,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x5c857619,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 7277168,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x5c857619,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_data_params_get(&params) != true) {
    err = ai_network_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_init(*network, &params) != true) {
    err = ai_network_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

