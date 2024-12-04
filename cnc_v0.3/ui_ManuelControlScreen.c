// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: cnc-App-v1

#include "ui.h"

void ui_ManuelControlScreen_screen_init(void)
{
    ui_ManuelControlScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ManuelControlScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ControlScreenBackButton = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ControlScreenBackButton, 100);
    lv_obj_set_height(ui_ControlScreenBackButton, 50);
    lv_obj_set_x(ui_ControlScreenBackButton, -316);
    lv_obj_set_y(ui_ControlScreenBackButton, 142);
    lv_obj_set_align(ui_ControlScreenBackButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ControlScreenBackButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ControlScreenBackButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ControlScreenBackLabel = lv_label_create(ui_ControlScreenBackButton);
    lv_obj_set_width(ui_ControlScreenBackLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ControlScreenBackLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_ControlScreenBackLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ControlScreenBackLabel, "Back");

    ui_ButtonYplus = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ButtonYplus, 91);
    lv_obj_set_height(ui_ButtonYplus, 81);
    lv_obj_set_x(ui_ButtonYplus, -227);
    lv_obj_set_y(ui_ButtonYplus, -120);
    lv_obj_set_align(ui_ButtonYplus, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonYplus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonYplus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ButtonYplus, &ui_img_up_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonXminus = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ButtonXminus, 91);
    lv_obj_set_height(ui_ButtonXminus, 81);
    lv_obj_set_x(ui_ButtonXminus, -323);
    lv_obj_set_y(ui_ButtonXminus, -34);
    lv_obj_set_align(ui_ButtonXminus, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonXminus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonXminus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ButtonXminus, &ui_img_left_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonYminus = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ButtonYminus, 91);
    lv_obj_set_height(ui_ButtonYminus, 81);
    lv_obj_set_x(ui_ButtonYminus, -226);
    lv_obj_set_y(ui_ButtonYminus, 46);
    lv_obj_set_align(ui_ButtonYminus, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonYminus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonYminus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ButtonYminus, &ui_img_down_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonXplus = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ButtonXplus, 91);
    lv_obj_set_height(ui_ButtonXplus, 81);
    lv_obj_set_x(ui_ButtonXplus, -129);
    lv_obj_set_y(ui_ButtonXplus, -34);
    lv_obj_set_align(ui_ButtonXplus, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonXplus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonXplus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ButtonXplus, &ui_img_right_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonZplus = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ButtonZplus, 91);
    lv_obj_set_height(ui_ButtonZplus, 81);
    lv_obj_set_x(ui_ButtonZplus, 35);
    lv_obj_set_y(ui_ButtonZplus, -131);
    lv_obj_set_align(ui_ButtonZplus, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonZplus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonZplus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ButtonZplus, &ui_img_up_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonZminus = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_ButtonZminus, 91);
    lv_obj_set_height(ui_ButtonZminus, 81);
    lv_obj_set_x(ui_ButtonZminus, 35);
    lv_obj_set_y(ui_ButtonZminus, 5);
    lv_obj_set_align(ui_ButtonZminus, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonZminus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonZminus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ButtonZminus, &ui_img_down_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_FeedRateSlider = lv_slider_create(ui_ManuelControlScreen);
    lv_slider_set_value(ui_FeedRateSlider, 0, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_FeedRateSlider) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_FeedRateSlider, 0,
                                                                                                   LV_ANIM_OFF);
    lv_obj_set_width(ui_FeedRateSlider, 150);
    lv_obj_set_height(ui_FeedRateSlider, 10);
    lv_obj_set_x(ui_FeedRateSlider, 257);
    lv_obj_set_y(ui_FeedRateSlider, -60);
    lv_obj_set_align(ui_FeedRateSlider, LV_ALIGN_CENTER);


    ui_Label7 = lv_label_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label7, 220);
    lv_obj_set_y(ui_Label7, -102);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "feedrate:");

    ui_SetZeroButton = lv_btn_create(ui_ManuelControlScreen);
    lv_obj_set_width(ui_SetZeroButton, 100);
    lv_obj_set_height(ui_SetZeroButton, 50);
    lv_obj_set_x(ui_SetZeroButton, 284);
    lv_obj_set_y(ui_SetZeroButton, 86);
    lv_obj_set_align(ui_SetZeroButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SetZeroButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SetZeroButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label8 = lv_label_create(ui_SetZeroButton);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "Set Zero");

    lv_obj_add_event_cb(ui_ControlScreenBackButton, ui_event_ControlScreenBackButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonYplus, ui_event_ButtonYplus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonXminus, ui_event_ButtonXminus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonYminus, ui_event_ButtonYminus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonXplus, ui_event_ButtonXplus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonZplus, ui_event_ButtonZplus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonZminus, ui_event_ButtonZminus, LV_EVENT_ALL, NULL);

}