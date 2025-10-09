#ifndef __TEST_H__
#define __TEST_H__

#include "visual_comm.h"  // 引入ColorTarget_t和TargetType_t定义
#include <stdbool.h>

void Test_1(void);
void Test_2(void);
void Test_3(void);

// Gripper综合测试函数
void Test_Gripper_PickAndPlace(void);

// ==================== 视觉集成测试函数 ====================
void Test_Vision_Communication(void);       // 视觉通信基础测试
void Test_Vision_Pickup_Red(void);          // 单个物料抓取测试
void Test_Vision_PickAndPlace_Red(void);    // 完整抓取-放置测试
void Test_Vision_Auto_Sorting(void);        // 三色自动分拣测试
void Test_Vision_QRCode(void);              // 二维码识别测试
void Test_Vision_Positioning(void);         // 视觉引导定位测试 (基础版)

// 高精度迭代定位 (统一接口,支持物块/凸台/凹槽)
bool Test_Vision_Positioning_Advanced(ColorTarget_t color);  // 旧版物块定位(保留兼容)
bool Vision_Align_Target(TargetType_t target_type, ColorTarget_t color);  // 新版统一接口

#endif