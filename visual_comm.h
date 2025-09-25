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
    
    // 色环和物料盘数据
    uint16_t rgb_circle_x;   // 色环中心X坐标
    uint16_t rgb_circle_y;   // 色环中心Y坐标
    int16_t rgb_circle_z;    // 左环减右环的Y差值
    uint16_t tray_center_x;  // 物料盘中心X坐标
    uint16_t tray_center_y;  // 物料盘中心Y坐标
    
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
    TASK_IDLE = 0x00,              // 空闲状态
    TASK_IDENTIFY_TRAY = 0x01,     // 识别物料盘
    TASK_IDENTIFY_MATERIAL = 0x02,  // 识别物料
    TASK_IDENTIFY_RINGS = 0x03,     // 识别色环
    TASK_STACKING_POS = 0x04,       // 码垛定位
    TASK_FINAL_TRAY = 0x05,         // 决赛物料盘识别
    TASK_PLACE_MATERIAL = 0x06,     // 决赛请求放置物料
    TASK_GRAB_MATERIAL = 0x07,      // 请求抓取物料
    TASK_FINAL_STACKING = 0x08,     // 决赛抓取校准
    TASK_QR_CODE = 0x09,            // 二维码识别
    TASK_PLATFORM = 0x0A,           // 凸台识别 (新增)
    TASK_SLOT = 0x0B,               // 凹槽识别 (新增)
    TASK_DEBUG = 0xAA               // 调试模式
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

/* 函数声明 */

// 初始化函数
void Visual_Data_Init(void);

// 任务发送函数 (STM32 -> LubanCat)
void Visual_Send_Idle(void);
void Visual_Send_QRCode_Request(void);
void Visual_Send_Tray_Request(void);
void Visual_Send_Material_Request(uint8_t color);
void Visual_Send_Platform_Request(uint8_t color);
void Visual_Send_Slot_Request(uint8_t color);
void Visual_Send_Rings_Request(void);
void Visual_Send_Stacking_Request(void);
void Visual_Send_Debug_Request(uint8_t debug_cmd);

// 数据接收解析函数 (LubanCat -> STM32)
void Visual_Data_Unpack(uint8_t *lubancat_data);

// 辅助函数
uint8_t Visual_Calculate_Checksum(uint8_t *data, uint8_t len);
uint8_t Visual_Verify_Frame(uint8_t *data, uint8_t expected_tail_pos);

#endif /* __VISUAL_COMM_H */
