/**
  ******************************************************************************
  * @file    task_vision_gripper.h
  * @brief   视觉引导的机械爪任务流程头文件
  ******************************************************************************
  */

#ifndef __TASK_VISION_GRIPPER_H
#define __TASK_VISION_GRIPPER_H

#include "main.h"
#include "visual_comm.h"

/* ==================== 公开函数声明 ==================== */

/**
 * @brief 视觉引导抓取任务
 * @param color 目标物料颜色(COLOR_RED/GREEN/BLUE)
 * @return true=成功, false=失败
 */
bool Task_Vision_Pickup(ColorTarget_t color);

/**
 * @brief 视觉引导放置任务
 * @param color 物料颜色(决定放入哪个物料盘)
 * @return true=成功, false=失败
 */
bool Task_Vision_Place(ColorTarget_t color);

/**
 * @brief 完整的视觉引导抓取-放置流程
 * @param color 目标物料颜色
 * @return true=成功, false=失败
 */
bool Task_Vision_PickAndPlace(ColorTarget_t color);

/**
 * @brief 二维码识别任务
 * @param qr_result[out] 输出6位二维码数据
 * @return true=成功, false=失败
 */
bool Task_Vision_ReadQRCode(uint8_t qr_result[6]);

/**
 * @brief 三色物料自动分拣任务
 * @details 按红→绿→蓝顺序依次抓取并放入对应物料盘
 * @return true=成功, false=失败
 */
bool Task_Auto_Sorting(void);

#endif /* __TASK_VISION_GRIPPER_H */
