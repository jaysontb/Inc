/**
  ******************************************************************************
  * @file    gripper.h
  * @brief   机械爪控制模块头文件
  * @details 包含云台旋转、爪子开合、升降控制功能
  *          本模块用于比赛中的物料抓取、测试、装配等任务
  ******************************************************************************
  */

#ifndef __GRIPPER_H
#define __GRIPPER_H

#include "main.h"
#include <stdbool.h>

/* ==================== 硬件配置参数 ==================== */

// 升降电机(丝杆步进电机)配置
#define GRIPPER_LIFT_MOTOR_ADDR     6       // 升降电机地址
#define GRIPPER_CLK_PER_MM          1143    // 脉冲数/mm (实测: 16000clk=14mm)
#define GRIPPER_DEFAULT_SPEED       80      // 默认速度 (RPM)
#define GRIPPER_DEFAULT_ACC         100     // 默认加速度
#define GRIPPER_MAX_HEIGHT          28.0f   // 最大升降高度 (mm) - 离地20.8cm
#define GRIPPER_MIN_HEIGHT          0.0f    // 最小升降高度 (mm) - 离地18cm(零点)

// 云台舵机配置 (TIM1_CH1)
#define GRIPPER_PAN_MIN_ANGLE       0.0f    // 云台最小角度(抓取位置)
#define GRIPPER_PAN_MAX_ANGLE       270.0f  // 云台最大角度

// 爪子舵机配置 (TIM1_CH2)
#define GRIPPER_CLAW_MIN_ANGLE      5.0f    // 爪子抓紧角度
#define GRIPPER_CLAW_MAX_ANGLE      45.0f   // 爪子松开角度

/* ==================== 预设位置参数 ==================== */

// 升降高度预设值 (根据比赛场地实测调整)
// 注意: 0mm = 离地18cm, 22mm = 离地20.2cm
#define HEIGHT_HOME                 0.0f    // 归零位置 (离地18cm)
#define HEIGHT_PICKUP_LOWER         0.0f    // 下层物料台抓取高度 (离地18cm)
#define HEIGHT_PICKUP_UPPER         15.0f   // 上层物料台抓取高度 (离地19.5cm)
#define HEIGHT_TEST_PLATFORM        8.0f    // 测试台放置高度 (离地18.8cm)
#define HEIGHT_ASSEMBLY_L1          5.0f    // 装配台第一层高度 (离地18.5cm)
#define HEIGHT_ASSEMBLY_L2          12.0f   // 装配台第二层高度 (离地19.2cm)
#define HEIGHT_TRANSPORT            28.0f   // 搬运过程中的安全高度 (最高点,离地20.8cm)

// 云台角度预设值 (根据实测数据)
#define PAN_ANGLE_GRAB              0.0f    // 抓取位置 (机械臂前方)
#define PAN_ANGLE_PLATE1            182.0f  // 第一个物料盘位置
#define PAN_ANGLE_PLATE2            208.0f  // 第二个物料盘位置
#define PAN_ANGLE_PLATE3            228.0f  // 第三个物料盘位置

/* ==================== 公开函数声明 ==================== */

/**
 * @brief 控制机械爪升降到指定高度
 * @param height_mm 目标高度 (mm), 范围[0, 22]
 * @note 自动使用默认速度80RPM, 会阻塞等待运动完成
 */
void Gripper_Lift(float height_mm);

/**
 * @brief 获取当前机械爪高度
 * @retval 当前高度 (mm)
 */
float Gripper_Get_Height(void);

/**
 * @brief 控制云台旋转到指定角度
 * @param angle_deg 目标角度 (度), 范围[0, 270]
 * @note 使用舵机控制,无需等待,立即返回
 */
void Gripper_Pan_Rotate(float angle_deg);

/**
 * @brief 控制爪子张开
 * @note 张开到最大角度45°,用于释放物料
 */
void Gripper_Claw_Open(void);

/**
 * @brief 控制爪子闭合
 * @note 闭合到最小角度9°,用于抓取物料
 */
void Gripper_Claw_Close(void);

#endif /* __GRIPPER_H */
