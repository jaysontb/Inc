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
void Visual_Print_Coord(uint16_t x, uint16_t y);
void Visual_Test_Basic(void);
void Visual_Test_Loop(void);
void Visual_Test_FullTask(void);

#endif /* __VISUAL_TEST_H */
