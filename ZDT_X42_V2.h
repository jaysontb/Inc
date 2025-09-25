#ifndef __ZDT_X42_V2_H
#define __ZDT_X42_V2_H

#include "main.h" // HAL库主头文件
#include <stdbool.h>

// 宏定义，用于简化代码
#define ABS(x) ((x) > 0 ? (x) : -(x))

// 系统参数类型枚举
typedef enum {
    S_VER,  // 读取固件版本和对应的硬件版本
    S_RL,   // 读取相电阻和相电感
    S_PID,  // 读取PID参数
    S_ORG,  // 读取回零参数
    S_VBUS, // 读取总线电压
    S_CBUS, // 读取总线电流
    S_CPHA, // 读取相电流
    S_ENC,  // 读取编码器原始值
    S_CPUL, // 读取实时脉冲数
    S_ENCL, // 读取经过线性化校准后的编码器值
    S_TPUL, // 读取输入脉冲数
    S_TPOS, // 读取电机目标位置
    S_OPOS, // 读取电机实时设定的目标位置
    S_VEL,  // 读取电机实时转速
    S_CPOS, // 读取电机实时位置
    S_PERR, // 读取电机位置误差
    S_TEMP, // 读取电机实时温度
    S_SFLAG,// 读取状态标志位
    S_OFLAG,// 读取回零状态标志位
    S_Conf, // 读取驱动参数
    S_State // 读取系统状态参数
} SysParams_t;


// 外部变量声明
extern UART_HandleTypeDef huart1;
extern volatile uint8_t rxFrameFlag1;
extern uint8_t rxBuffer[256];
extern uint16_t rxFrameCount;


// 函数声明
void ZDT_X42_V2_Reset_CurPos_To_Zero(uint8_t addr);
void ZDT_X42_V2_Reset_Clog_Pro(uint8_t addr);
void ZDT_X42_V2_Read_Sys_Params(uint8_t addr, SysParams_t s);
void ZDT_X42_V2_Modify_Ctrl_Mode(uint8_t addr, bool svF, uint8_t ctrl_mode);
void ZDT_X42_V2_En_Control(uint8_t addr, bool state, uint8_t snF);
void ZDT_X42_V2_Torque_Control(uint8_t addr, uint8_t sign, uint16_t t_ramp, uint16_t torque, uint8_t snF);
void ZDT_X42_V2_Velocity_Control(uint8_t addr, uint8_t dir, uint16_t v_ramp, float velocity, uint8_t snF);
void ZDT_X42_V2_Bypass_Position_LV_Control(uint8_t addr, uint8_t dir, float velocity, float position, uint8_t raf, uint8_t snF);
void ZDT_X42_V2_Traj_Position_Control(uint8_t addr, uint8_t dir, uint16_t acc, uint16_t dec, float velocity, float position, uint8_t raf, uint8_t snF);
void ZDT_X42_V2_Stop_Now(uint8_t addr, uint8_t snF);
void ZDT_X42_V2_Synchronous_motion(uint8_t addr);
void ZDT_X42_V2_Origin_Set_O(uint8_t addr, bool svF);
void ZDT_X42_V2_Origin_Modify_Params(uint8_t addr, bool svF, uint8_t o_mode, uint8_t o_dir, uint16_t o_vel, uint32_t o_tm, uint16_t sl_vel, uint16_t sl_ma, uint16_t sl_ms, bool potF);
void ZDT_X42_V2_Origin_Trigger_Return(uint8_t addr, uint8_t o_mode, bool snF);
void ZDT_X42_V2_Origin_Interrupt(uint8_t addr);

void ZDT_X42_V2_Receive_Data(uint8_t *rxCmd, uint8_t *rxCount);

#endif
