/**
  ******************************************************************************
  * @author  YOUR_NAME
  * @version V1.0
  * @date    2025-09-21
  * @brief   视觉通信中枢 - 适配LubanCat上位机
  ******************************************************************************
  * @attention
  * 基于PINK SAKURA的visual_identity模块改进，适配LubanCat平台
  ******************************************************************************
  */

#ifndef __VISUAL_COMM_H
#define __VISUAL_COMM_H

#include "main.h"
#include "usart.h"

/* 视觉数据接收结构体 */
typedef struct
{
    // 物料位置数据
    uint16_t r_block_x;      // 红色物料X坐标
    uint16_t r_block_y;      // 红色物料Y坐标
    uint16_t g_block_x;      // 绿色物料X坐标
    uint16_t g_block_y;      // 绿色物料Y坐标
    uint16_t b_block_x;      // 蓝色物料X坐标
    uint16_t b_block_y;      // 蓝色物料Y坐标
    
    // 凸台和凹槽位置数据
    uint16_t platform_x;     // 凸台X坐标
    uint16_t platform_y;     // 凸台Y坐标
    uint16_t slot_x;         // 凹槽X坐标
    uint16_t slot_y;         // 凹槽Y坐标
    
    // 控制指令
    uint8_t block_grab;      // 抓取指令
    uint8_t block_order;     // 决赛物料摆放顺序
    
    // 二维码数据
    uint8_t qr_data[6];      // 二维码6位数据
    uint8_t qr_valid;        // 二维码数据有效标志
    
} VisualRxData_t;

/* 任务码定义 */
typedef enum
{
    TASK_IDLE = 0x00,              // 空闲状态(保留用于初始化)
    TASK_IDENTIFY_MATERIAL = 0x02,  // 识别物料
    TASK_QR_CODE = 0x09,            // 二维码识别
    TASK_PLATFORM = 0x0A,           // 凸台识别
    TASK_SLOT = 0x0B                // 凹槽识别
} VisualTask_t;

/* 颜色识别目标定义 */
typedef enum
{
    COLOR_RED = 0x01,    // 红色
    COLOR_GREEN = 0x02,  // 绿色
    COLOR_BLUE = 0x03    // 蓝色
} ColorTarget_t;

/* 全局变量声明 */
extern VisualRxData_t VIS_RX;
extern uint8_t color_task[6];
extern uint8_t visual_rx_complete_flag;  // 串口接收完成标志

/* 函数声明 */

// 初始化函数
void Visual_Data_Init(void);
void Visual_UART_Start_Receive(void);

// 任务发送函数 (STM32 -> LubanCat)
void Visual_Send_Idle(void);
void Visual_Send_QRCode_Request(void);
void Visual_Send_Material_Request(uint8_t color);
void Visual_Send_Platform_Request(uint8_t color);
void Visual_Send_Slot_Request(uint8_t color);

// 数据接收解析函数 (LubanCat -> STM32)
void Visual_Data_Unpack(uint8_t *lubancat_data);
void Visual_UART_RxCallback(void);        // 串口接收回调
uint8_t* Visual_Get_RxBuffer(void);       // 获取接收缓冲区
void Visual_Clear_RxFlag(void);           // 清除接收标志

// 辅助函数
uint8_t Visual_Verify_Frame(uint8_t *data, uint8_t expected_tail_pos);
uint8_t Visual_Wait_Response(uint32_t timeout_ms);

#endif /* __VISUAL_COMM_H */
