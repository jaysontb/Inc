#ifndef __MOTOR_H__
#define __MOTOR_H__
#pragma once//只编译一次
#include <stdint.h>
#include <stdbool.h>

bool Motor_readangle(uint8_t motor_adr , float *angle);

// 里程计数据结构（扩展版）
typedef struct {
    float x_mm;           // 世界坐标 X (mm)
    float y_mm;           // 世界坐标 Y (mm)
    float yaw_deg;        // 当前航向角(度) — 来自 IMU
    float last_deg[4];    // 上一次读取的四轮角度(度)
    bool  initialized;    // 是否已完成初始采样
} Odom2D_t;

// 里程计接口（首次调用 Update 会自动完成初始化基准）
// 更新：内部主动读取四轮角度与 IMU 航向；返回 true 成功，false 传感读取失败（保持旧值）
bool Motor_Odom_Update(Odom2D_t *odom);
// 获取当前位置（便捷封装，可直接读取结构体亦可不用）
void Motor_Odom_Get(const Odom2D_t *odom, float *x_mm, float *y_mm, float *yaw_deg);

bool Motor_readangle(uint8_t motor_adr , float *angle);

// 航向角稳定控制
typedef struct {
    float target_yaw_deg;       // 目标航向角(度)
    float current_yaw_deg;      // 当前航向角(度)
    float yaw_error_deg;        // 航向角误差(度)
    float kp_yaw;               // 航向角P控制器增益
    float max_correction_rpm;   // 最大修正转速
    bool enable_heading_hold;   // 是否启用航向保持
} HeadingController_t;

// 航向角稳定移动函数
void Motor_SetHeadingTarget(float target_yaw_deg);
void Motor_EnableHeadingHold(bool enable);
void Motor_Yaw_Corrected_Forward(float base_speed_rpm, float wheel_speeds[4]);
void Motor_Yaw_Corrected_Strafe(float base_speed_rpm, float wheel_speeds[4]);
bool Motor_UpdateHeadingController(float current_yaw_deg);
float calculate_yaw_correction_rpm(void);
bool Move_Forward_Distance_Stable(float d_mm, float target_yaw_deg);
bool Move_Lateral_Distance_Stable(float d_mm, float target_yaw_deg);
bool Move_Rotate_90_Degrees(bool clockwise);

#endif
