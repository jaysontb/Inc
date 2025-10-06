#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief 初始化电机驱动模块 (位置模式)
 */
void Motor_Init(void);

/**
 * @brief 前后移动
 * @param distance_mm 正值前进, 负值后退 (mm)
 * @param speed_rpm   速度 (RPM), 0 表示使用默认值
 */
void Motor_Move_Forward(float distance_mm, uint16_t speed_rpm);

/**
 * @brief 左右平移
 * @param distance_mm 正值向右, 负值向左 (mm)
 * @param speed_rpm   速度 (RPM), 0 表示使用默认值
 */
void Motor_Move_Lateral(float distance_mm, uint16_t speed_rpm);

/**
 * @brief 原地旋转
 * @param angle_deg 正值逆时针, 负值顺时针 (度)
 * @param speed_rpm 速度 (RPM), 0 表示使用默认值
 */
void Motor_Move_Rotate(float angle_deg, uint16_t speed_rpm);

/**
 * @brief 停止所有电机
 */
void Motor_Stop_All(void);

/**
 * @brief 急停
 */
void Motor_Emergency_Stop(void);

/**
 * @brief 设置速度配置
 * @param profile 0=精确(30RPM), 1=正常(50RPM), 2=快速(80RPM)
 */
void Motor_Set_Speed_Profile(uint8_t profile);

/**
 * @brief 根据DMP的yaw读数计算小车实际转角
 * @param yaw_start_deg 旋转前的yaw角(度)
 * @param yaw_now_deg   旋转后的yaw角(度)
 *
 * @return 实际转角(度), 与Motor_Move_Rotate保持一致: 正值逆时针, 负值顺时针
 */
float Motor_Get_Rotation_From_Yaw(float yaw_start_deg, float yaw_now_deg);

/**
 * @brief 带航向保持的前进运动 (Level 2)
 * @param distance_mm 移动距离(mm), 正值前进, 负值后退
 * @param target_yaw_deg 目标航向角(度), 通常是起始yaw角
 * @param tolerance_deg 允许偏差(度), 建议±2°
 * @param speed_rpm 速度(RPM), 0表示使用默认值
 * @note 自动分段移动并修正航向偏差,适用于长距离直线移动
 */
void Motor_Move_Forward_WithYawHold(float distance_mm, float target_yaw_deg, 
                                     float tolerance_deg, uint16_t speed_rpm);

/**
 * @brief 带航向保持的平移运动 (Level 2)
 * @param distance_mm 移动距离(mm), 正值右移, 负值左移
 * @param target_yaw_deg 目标航向角(度), 通常是起始yaw角
 * @param tolerance_deg 允许偏差(度), 建议±2°
 * @param speed_rpm 速度(RPM), 0表示使用默认值
 * @note 自动分段移动并修正航向偏差,防止平移时车体旋转
 */
void Motor_Move_Lateral_WithYawHold(float distance_mm, float target_yaw_deg,
                                     float tolerance_deg, uint16_t speed_rpm);

#endif /* __MOTOR_H__ */
