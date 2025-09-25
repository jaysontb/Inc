#ifndef __GRIPPER_H__
#define __GRIPPER_H__

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

// 舵机控制参数
#define SERVO_FREQUENCY_HZ      50      // 舵机PWM频率50Hz
#define SERVO_PERIOD_US         20000   // 周期20ms
#define SERVO_MIN_PULSE_US      500     // 最小脉宽0.5ms
#define SERVO_MAX_PULSE_US      2500    // 最大脉宽2.5ms

// 机械爪位置定义 (PWM占空比，0-1000对应0.5ms-2.5ms)
typedef enum {
    // 伸缩舵机位置
    EXTEND_RETRACT      = 100,  // 完全收回位置（安全位置）
    EXTEND_HALF         = 300,  // 半伸出位置
    EXTEND_GRAB         = 500,  // 抓取位置
    EXTEND_PLACE        = 600,  // 放置位置
    EXTEND_STACK        = 700,  // 码垛位置
    
    // 抓取舵机位置
    GRIP_OPEN           = 150,  // 完全张开
    GRIP_LIGHT          = 350,  // 轻抓（适合轻物料）
    GRIP_NORMAL         = 500,  // 正常抓取
    GRIP_FIRM           = 650,  // 牢固抓取
    GRIP_STACK          = 400   // 码垛专用抓取力度
} GripperPosition_t;

// 机械爪状态
typedef enum {
    GRIPPER_IDLE = 0,           // 空闲状态
    GRIPPER_EXTENDING,          // 正在伸出
    GRIPPER_RETRACTING,         // 正在收回
    GRIPPER_GRIPPING,           // 正在抓取
    GRIPPER_RELEASING,          // 正在松开
    GRIPPER_ERROR               // 错误状态
} GripperState_t;

// 物料类型（影响抓取策略）
typedef enum {
    MATERIAL_UNKNOWN = 0,       // 未知物料
    MATERIAL_A_LIGHT,           // 物料A（轻型）
    MATERIAL_A_HEAVY,           // 物料A（重型）
    MATERIAL_B_LIGHT,           // 物料B（轻型）
    MATERIAL_B_HEAVY,           // 物料B（重型）
    MATERIAL_ASSEMBLY           // 装配体
} MaterialType_t;

// 机械爪控制结构体
typedef struct {
    uint16_t extend_position;   // 当前伸缩位置
    uint16_t grip_position;     // 当前抓取位置
    GripperState_t state;       // 当前状态
    MaterialType_t material;    // 当前物料类型
    bool has_material;          // 是否抓有物料
    uint32_t last_action_time; // 上次动作时间
} GripperControl_t;

// 机械爪初始化
void Gripper_Init(void);

// 基础控制函数
bool Gripper_SetExtendPosition(uint16_t position, uint16_t timeout_ms);
bool Gripper_SetGripPosition(uint16_t position, uint16_t timeout_ms);

// 复合动作函数
bool Gripper_GrabMaterial(MaterialType_t material_type);
bool Gripper_PlaceMaterial(void);
bool Gripper_PlaceMaterialOnPlatform(void);
bool Gripper_PlaceMaterialInSlot(void);
bool Gripper_StackMaterial(void);
bool Gripper_RetractToSafe(void);

// 状态查询函数
GripperState_t Gripper_GetState(void);
bool Gripper_HasMaterial(void);
bool Gripper_IsReady(void);

// 精确控制函数
bool Gripper_AdjustPosition(int16_t extend_delta, int16_t grip_delta);
bool Gripper_SlowPlace(void);  // 缓慢精确放置

// 紧急停止
void Gripper_EmergencyStop(void);

#endif // __GRIPPER_H__
