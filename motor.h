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
 * @brief 兼容旧接口: 前后移动 (忽略航向参数)
 * @return 始终返回 true
 */
bool Move_Forward_Distance_Stable(float d_mm, float target_yaw_deg);

/**
 * @brief 兼容旧接口: 左右平移 (忽略航向参数)
 * @return 始终返回 true
 */
bool Move_Lateral_Distance_Stable(float d_mm, float target_yaw_deg);

/**
 * @brief 兼容旧接口: 原地旋转 90°
 * @param clockwise true 顺时针, false 逆时针
 * @return 始终返回 true
 */
bool Move_Rotate_90_Degrees(bool clockwise);

#endif /* __MOTOR_H__ */
