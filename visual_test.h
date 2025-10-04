/**
  ******************************************************************************
  * @file    visual_test.h
  * @brief   视觉系统测试函数声明
  ******************************************************************************
  */

#ifndef __VISUAL_TEST_H
#define __VISUAL_TEST_H

#include "main.h"

/* 测试函数声明 */
uint8_t Visual_Wait_Response(uint32_t timeout_ms);
void Visual_Show_Coord_OLED(uint16_t x, uint16_t y, uint8_t line);  // 在OLED上显示坐标
void Visual_Test_Basic(void);
void Visual_Test_Loop(void);
void Visual_Test_FullTask(void);
void Visual_Display_All_Info(void);  // 显示完整视觉信息
uint8_t Visual_Quick_Test(uint8_t color, uint8_t line);  // 单次快速测试

#endif /* __VISUAL_TEST_H */
