/**
  ******************************************************************************
  * @file    task.h
  * @brief   比赛任务流程模块头文件
  * @details 包含智能物流搬运比赛的完整任务流程实现
  *          根据浙江省大学生工程实践与创新能力竞赛规则设计
  ******************************************************************************
  */

#ifndef __TASK_H
#define __TASK_H

#include "main.h"
#include <stdint.h>

/* ==================== 任务状态定义 ==================== */
typedef enum {
    TASK_SUCCESS = 0,      /**< 任务成功完成 */
    TASK_FAILED  = 1,      /**< 任务失败 */
    TASK_TIMEOUT = 2,      /**< 任务超时 */
    TASK_VISION_ERROR = 3  /**< 视觉定位失败 */
} TaskStatus_t;

/* ==================== 物料颜色定义 ==================== */
// 使用visual_comm.h中的COLOR_RED, COLOR_GREEN, COLOR_BLUE定义

/* ==================== 公开函数声明 ==================== */

/**
 * @brief 物料台抓取流程 (阶段1)
 * @details 完成以下步骤:
 *          1. 从启停区驶出到物料台区域
 *          2. 依次定位并抓取蓝色、绿色、红色物块
 *          3. 每个物块抓取后放置到对应物料盘
 * @return TaskStatus_t 任务执行状态
 * @note 对应比赛流程步骤1-7: 出发 -> 读码 -> 物料台取料 -> 装配区第一批放置
 */
TaskStatus_t Task_Material_Pickup(void);

/**
 * @brief 测试区放置所有物料(按红→绿→蓝顺序)
 * @details 完成以下步骤:
 *          1. 从物料盘按红→绿→蓝顺序抓取并放置到测试凸台
 *          2. 每个物料测试后重新抓取,准备放回
 * @return TaskStatus_t 任务执行状态
 * @note 对应比赛流程步骤4-5: 运送至测试区 -> 按颜色放置测试
 */
TaskStatus_t Task_Test_Zone_Place_All(void);

/**
 * @brief 将测试通过的物料按蓝→绿→红顺序放回物料盘
 * @details 从测试凸台取回物料并放回到对应物料盘位置
 * @return TaskStatus_t 任务执行状态
 */
TaskStatus_t Task_Return_To_Plate(void);

/**
 * @brief 测试区放置流程 (阶段2) - 旧版本保留
 * @details 完成以下步骤:
 *          1. 从物料盘抓取物料
 *          2. 行驶到测试区
 *          3. 按颜色对应关系放置到测试凸台
 *          4. 测试合格后再次抓取物料
 * @param color 物料颜色 (COLOR_RED/GREEN/BLUE)
 * @return TaskStatus_t 任务执行状态
 * @note 对应比赛流程步骤4-5: 运送至测试区 -> 按颜色放置测试
 */
TaskStatus_t Task_Test_Zone_Place(uint8_t color);

/**
 * @brief 装配码垛流程 (阶段3)
 * @details 完成以下步骤:
 *          1. 从测试区抓取合格物料
 *          2. 行驶到装配码垛区
 *          3. 按二维码指令装配(同色/异色)
 *          4. 码垛第二层物料
 * @param assembly_mode 装配模式: 0=同色装配, 1=异色错配
 * @return TaskStatus_t 任务执行状态
 * @note 对应比赛流程步骤6-8: 装配区装配和码垛
 */
TaskStatus_t Task_Assembly_Stacking(uint8_t assembly_mode);

/**
 * @brief 障碍穿越与回归流程 (阶段4)
 * @details 完成以下步骤:
 *          1. 从装配区抓取一组装配体
 *          2. 穿越障碍区
 *          3. 回到启停区
 *          4. 关闭任务码显示
 * @return TaskStatus_t 任务执行状态
 * @note 对应比赛流程步骤9-10: 穿越障碍 -> 回归启停区
 */
TaskStatus_t Task_Obstacle_Return(void);

/**
 * @brief 二维码识别并显示任务码
 * @details 完成以下步骤:
 *          1. 向视觉模块发送二维码扫描指令(unit=9)
 *          2. 接收二维码数据(装配模式: 1=同色, 2=异色)
 *          3. 在OLED显示屏上显示任务信息
 *          4. 全局保存装配模式供后续使用
 * @param assembly_mode 输出参数: 装配模式(0=同色, 1=异色)
 * @return TaskStatus_t 任务执行状态
 * @note 对应比赛流程步骤2: 读取二维码并显示任务码
 *       比赛规则: 任务码显示字体高度不小于8mm,持续显示至比赛结束
 */
TaskStatus_t Task_QRCode_Read(uint8_t *assembly_mode);

/**
 * @brief 任务码显示控制
 * @param mode 显示模式: 0=关闭显示, 1=显示"同色装配", 2=显示"异色错配"
 * @note OLED 0.96寸屏幕显示策略:
 *       - 使用大号字体显示编号("MODE 1"或"MODE 2")
 *       - 小号字体补充说明("SAME"或"DIFF")
 *       - 满足8mm字高要求(16×16点阵约5.3mm,需放大显示)
 */
void Task_Display_Mode(uint8_t mode);

#endif /* __TASK_H */
