#include "My_gui.h"  // 引用头文件
#include "lvgl/lvgl.h"
#include "stdio.h"

#define LCD_WIDTH  320   // 这个命名实际代表“高度”
#define LCD_LENGTH 480   // 这个命名实际代表“宽度”（横屏）

lv_obj_t * backgroundScreen = NULL;
lv_obj_t * top_status_bar = NULL;
lv_obj_t * bottom_status_bar = NULL;

uint16_t mainmenukeyboardNavPointer = 1;
uint8_t shutdownDevice = 0;

static void mainMenuButtonChonice_event_cb(lv_event_t * e){
    lv_obj_t * btn = lv_event_get_target(e);
    mainmenukeyboardNavPointer = (uint16_t)(uintptr_t)lv_obj_get_user_data(btn) + 1;
    printf("%d",mainmenukeyboardNavPointer);
}

void createMainInterface(void){

    backgroundScreen = lv_obj_create(NULL);
    lv_obj_set_size(backgroundScreen, LCD_LENGTH, LCD_WIDTH);
    lv_obj_set_style_bg_color(backgroundScreen, lv_color_hex(0x000000), 0);
    lv_scr_load(backgroundScreen);

    top_status_bar = lv_obj_create(backgroundScreen);
    // lv_obj_set_style_radius(top_status_bar, 0, LV_STATE_DEFAULT);    // 设置圆角
    // lv_obj_set_style_pad_all(top_status_bar, 0, LV_STATE_DEFAULT);  // 清除所有内边距
    // lv_obj_set_style_border_width(top_status_bar, 0, LV_STATE_DEFAULT);// 清除边框宽度
    lv_obj_set_size(top_status_bar, LCD_LENGTH, 40);
    lv_obj_align(top_status_bar, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(top_status_bar, lv_color_hex(0x5E8B6F), LV_STATE_DEFAULT);

    lv_obj_set_flex_flow(top_status_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(top_status_bar, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * name_label = lv_label_create(top_status_bar);
    lv_label_set_text(name_label, "EAU");
    lv_obj_set_style_text_color(name_label, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
    lv_obj_t * battery_label = lv_label_create(top_status_bar);
    lv_label_set_text(battery_label, "2026.5");
    lv_obj_set_style_text_color(battery_label, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);
    lv_obj_t * icon_label = lv_label_create(top_status_bar);
    lv_obj_set_style_text_color(icon_label, lv_color_hex(0xFFFFFF), LV_STATE_DEFAULT);

    bottom_status_bar = lv_obj_create(backgroundScreen);
    lv_obj_set_size(bottom_status_bar,LCD_LENGTH,280);
    lv_obj_align(bottom_status_bar,LV_ALIGN_BOTTOM_MID,0,0);
    // lv_obj_set_style_radius(bottom_status_bar,0,LV_STATE_DEFAULT);// 设置圆角为0（直角）
    // lv_obj_set_style_border_width(bottom_status_bar,0,LV_STATE_DEFAULT);// 清除边框
    lv_obj_set_style_bg_color(bottom_status_bar,lv_color_hex(0x1E2B24),LV_STATE_DEFAULT);// 设置底部栏背景色
    
}

void mainMenuButtonChoice(void){

    lv_obj_clean(bottom_status_bar);

    lv_obj_set_style_pad_hor(bottom_status_bar,30,LV_STATE_DEFAULT);// 设置水平内边距
    lv_obj_set_style_pad_ver(bottom_status_bar,65,LV_STATE_DEFAULT);// 设置垂直内边距

    lv_obj_set_layout(bottom_status_bar,LV_LAYOUT_GRID);
    static uint8_t btn_count = 9;
    static uint8_t col_num = 5;
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1),LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {50, 50, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(bottom_status_bar, col_dsc, row_dsc);
    lv_obj_set_style_pad_row(bottom_status_bar,30, LV_STATE_DEFAULT);// 设置网格行间距
    lv_obj_set_style_pad_column(bottom_status_bar,30,LV_STATE_DEFAULT);// 设置网格列间距
    for (uint8_t i = 0; i < btn_count; i++) {

        lv_obj_t * btn = lv_btn_create(bottom_status_bar);
        lv_obj_set_user_data(btn, (void*)(intptr_t)i);
        // lv_obj_set_style_shadow_width(btn, 0, 0);//设置阴影
        lv_obj_set_style_radius(btn, 10, LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xD2E0CF), LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(btn, 4, LV_STATE_FOCUSED);
        lv_obj_set_style_border_color(btn, lv_color_hex(0x3A6B47), LV_STATE_FOCUSED);
        lv_obj_set_style_outline_width(btn, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
        lv_obj_set_style_outline_width(btn, 5, LV_STATE_PRESSED);
        lv_obj_set_style_outline_color(btn, lv_color_hex(0x3A6B47), LV_STATE_FOCUSED);
        lv_obj_add_event_cb(btn,mainMenuButtonChonice_event_cb,LV_EVENT_CLICKED,NULL);

        lv_obj_t * label = lv_label_create(btn);
        char text[10];
        sprintf(text,"%d",i);
        lv_label_set_text(label,text);
        lv_obj_center(label);
        lv_obj_set_style_text_font(label,&lv_font_montserrat_14,LV_STATE_DEFAULT);

        lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, i % col_num, 1,LV_GRID_ALIGN_STRETCH, i / col_num, 1);

    }

}

void settingsModeInterface(void){

    lv_obj_clean(bottom_status_bar);
    lv_obj_set_style_pad_hor(bottom_status_bar,0,LV_STATE_DEFAULT);// 设置水平内边距
    lv_obj_set_style_pad_ver(bottom_status_bar,0,LV_STATE_DEFAULT);// 设置垂直内边距

    // lv_obj_set_layout(bottom_status_bar,LV_LAYOUT_GRID);

    // static lv_coord_t col_dsc[] = {LV_GRID_FR(1),LV_GRID_FR(3),LV_GRID_TEMPLATE_LAST};
    // static lv_coord_t row_dsc[] = {LV_GRID_FR(1),LV_GRID_TEMPLATE_LAST};
    // lv_obj_set_grid_dsc_array(bottom_status_bar,col_dsc,row_dsc);
    // lv_obj_set_style_pad_row(bottom_status_bar,0,LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_column(bottom_status_bar,0,LV_STATE_DEFAULT);

    // lv_obj_t * left_panel = lv_obj_create(bottom_status_bar);
    // lv_obj_set_grid_cell(left_panel,LV_GRID_ALIGN_STRETCH,0,1,LV_GRID_ALIGN_STRETCH,0,1);

    // lv_obj_set_layout(left_panel,LV_LAYOUT_GRID);
    // static lv_coord_t left_col_dsc[] = {LV_GRID_FR(1),LV_GRID_TEMPLATE_LAST};
    // static lv_coord_t left_row_dsc[] = {LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_FR(1),LV_GRID_TEMPLATE_LAST};
    // lv_obj_set_grid_dsc_array(left_panel,left_col_dsc,left_row_dsc);
    // for (uint8_t i = 0; i < 4; i++)
    // {
    //     lv_obj_t * btn = lv_btn_create(left_panel);

    //     lv_obj_t * label = lv_label_create(btn);
    //     char text[10];
    //     sprintf(text,"%d",i);
    //     lv_label_set_text(label,text);
    //     lv_obj_center(label);

    //     lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, i % 1, 1,LV_GRID_ALIGN_STRETCH, i / 1, 1);

    // }
    
    // lv_obj_t * right_panel = lv_obj_create(bottom_status_bar);
    // lv_obj_set_grid_cell(right_panel,LV_GRID_ALIGN_STRETCH,1,1,LV_GRID_ALIGN_STRETCH,0,1);

    lv_obj_t * settingMode_TabView = lv_tabview_create(bottom_status_bar,LV_DIR_LEFT,96);

    lv_obj_t * settingMode_TabView_TabBtn = lv_tabview_get_tab_btns(settingMode_TabView);
    lv_obj_set_style_bg_color(settingMode_TabView_TabBtn, lv_color_hex(0xD2E0CF), 0);
    lv_obj_set_style_bg_color(settingMode_TabView_TabBtn, lv_color_hex(0xD2E0CF), LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_side(settingMode_TabView_TabBtn, LV_BORDER_SIDE_BOTTOM, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(settingMode_TabView_TabBtn, 3, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(settingMode_TabView_TabBtn, lv_color_hex(0x2E8B57), LV_PART_ITEMS | LV_STATE_CHECKED);

    lv_obj_t * About_tab = lv_tabview_add_tab(settingMode_TabView,"About");
    lv_obj_t * Status_tab = lv_tabview_add_tab(settingMode_TabView,"Status");
    lv_obj_t * Update_tab = lv_tabview_add_tab(settingMode_TabView,"Update");
    lv_obj_t * Screen_tab = lv_tabview_add_tab(settingMode_TabView,"Screen");

}


void my_gui(void) {

    
    
    switch (mainmenukeyboardNavPointer)
    {
        case 0:
            mainMenuButtonChoice();
            mainmenukeyboardNavPointer = 0xf0;
            break;
        case 1:
            settingsModeInterface();
            mainmenukeyboardNavPointer = 0xf0;
            break;
        default:
            break;
    }

}


