#ifndef MY_GUI_H
#define MY_GUI_H

#include "lvgl/lvgl.h"  // 包含LVGL头文件，避免编译报错

// 声明my_gui函数（必须和实现的签名一致：void my_gui(void)）
void my_gui(void);
void createMainInterface(void);
void settingsModeInterface(void);
void mainMenuButtonChoice(void);
extern uint16_t mainmenukeyboardNavPointer;
#endif  // MY_GUI_H