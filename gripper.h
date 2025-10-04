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
#define GRIPPER_MAX_HEIGHT          22.0f   // 最大升降高度 (mm) - 离地20.2cm
#define GRIPPER_MIN_HEIGHT          0.0f    // 最小升降高度 (mm) - 离地18cm(零点)

// 云台旋转电机配置 (后续添加)
// #define GRIPPER_PAN_MOTOR_ADDR      7       // 云台电机地址 (待定)

// 爪子开合舵机配置 (后续添加)
// #define GRIPPER_CLAW_SERVO_CHANNEL  1       // 舵机通道 (待定)

/* ==================== 预设位置参数 ==================== */

// 根据比赛场地实测调整以下高度值
// 注意: 0mm = 离地18cm, 22mm = 离地20.2cm
#define HEIGHT_HOME                 0.0f    // 归零位置 (离地18cm)
#define HEIGHT_PICKUP_LOWER         0.0f    // 下层物料台抓取高度 (离地18cm)
#define HEIGHT_PICKUP_UPPER         15.0f   // 上层物料台抓取高度 (离地19.5cm)
#define HEIGHT_TEST_PLATFORM        8.0f    // 测试台放置高度 (离地18.8cm)
#define HEIGHT_ASSEMBLY_L1          5.0f    // 装配台第一层高度 (离地18.5cm)
#define HEIGHT_ASSEMBLY_L2          12.0f   // 装配台第二层高度 (离地19.2cm)
#define HEIGHT_TRANSPORT            22.0f   // 搬运过程中的安全高度 (最高点,离地20.2cm)

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

// ========== 云台旋转控制 (后续实现) ==========

// void Gripper_Pan_Rotate(float angle_deg);
// void Gripper_Pan_Home(void);

// ========== 爪子开合控制 (后续实现) ==========

// void Gripper_Claw_Open(void);
// void Gripper_Claw_Close(void);
// void Gripper_Claw_Set_Width(float width_mm);

#endif /* __GRIPPER_H */
