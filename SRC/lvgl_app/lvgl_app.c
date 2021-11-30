#include "lvgl_app.h"
#include "lvgl.h"
#include "lv_port_indev.h"
#include "user_hal.h"

void lvgl_test1(void)
{
	lv_obj_clean(lv_scr_act()); 					// 确保屏幕无残留
	lv_obj_t * scr = lv_obj_create(NULL, NULL);
	lv_scr_load(scr);
	
	/* 电池*/
  lv_obj_t * label_state = lv_label_create(scr, NULL);
	lv_obj_set_style_local_text_color(label_state, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);    		// 设置颜色
  lv_label_set_text(label_state, LV_SYMBOL_BATTERY_FULL);
  lv_obj_align_origo(label_state, NULL, LV_ALIGN_IN_TOP_RIGHT, -(15*1), 10);
  lv_obj_fade_in(label_state, 0, 1000);
}

void lv_ex_obj_1(void)
{
		lv_obj_t * obj1;
		obj1 = lv_obj_create(lv_scr_act(), NULL);
		lv_obj_set_size(obj1, 50, 25);
		lv_obj_align(obj1, NULL, LV_ALIGN_CENTER, -60, -30);
		/*Copy the previous object and enable drag*/
		lv_obj_t * obj2;
		obj2 = lv_obj_create(lv_scr_act(), obj1);
		lv_obj_align(obj2, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_obj_set_drag(obj2, true);
		static lv_style_t style_shadow;
		lv_style_init(&style_shadow);
		lv_style_set_shadow_width(&style_shadow, LV_STATE_DEFAULT, 10);
		lv_style_set_shadow_spread(&style_shadow, LV_STATE_DEFAULT, 5);
		lv_style_set_shadow_color(&style_shadow, LV_STATE_DEFAULT, LV_COLOR_BLUE);

		/*Copy the previous object (drag is already enabled)*/
		lv_obj_t * obj3;
		obj3 = lv_obj_create(lv_scr_act(), obj2);
		lv_obj_add_style(obj3, LV_OBJ_PART_MAIN, &style_shadow);
		lv_obj_align(obj3, NULL, LV_ALIGN_CENTER, 60, 30);
}

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	if(event == LV_EVENT_CLICKED) {

		HAL_GPIO_TogglePin(GPIOB,GPIO_Pin_10);
//		printf("Clicked\n");
	}
	else if(event == LV_EVENT_VALUE_CHANGED) {
//		printf("Toggled\n");
	}
}

void lv_ex_btn_1(void)
{
	lv_group_t * group = lv_group_create();
	
		lv_obj_t * label;

		lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_set_event_cb(btn1, event_handler);
//		lv_btn_set_checkyable(btn1, true);
		lv_btn_toggle(btn1);
		lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -50);
		lv_btn_set_fit2(btn1, LV_FIT_NONE, LV_FIT_TIGHT);


		label = lv_label_create(btn1, NULL);
		lv_label_set_text(label, "Start");

		lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_set_event_cb(btn2, event_handler);
		lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 0);
//		lv_btn_set_checkable(btn2, true);
		lv_btn_toggle(btn2);
		lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

		label = lv_label_create(btn2, NULL);
		lv_label_set_text(label, "Setup");
		
		lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_set_event_cb(btn3, event_handler);
		lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, 0, 50);
//		lv_btn_set_checkable(btn3, true);
		lv_btn_toggle(btn3);
		lv_btn_set_fit2(btn3, LV_FIT_NONE, LV_FIT_TIGHT);

		label = lv_label_create(btn3, NULL);
		lv_label_set_text(label, "Exit");
		
		lv_group_add_obj(group, btn1);
		lv_group_add_obj(group, btn2);
		lv_group_add_obj(group, btn3);
		
		lv_indev_set_group(indev_encoder, group);
		
}

void lv_ex_calendar_1(void)
{
	lv_obj_t  * calendar = lv_calendar_create(lv_scr_act(), NULL);
	lv_obj_set_size(calendar, 132, 162);
	lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_event_cb(calendar, event_handler);

	/*Make the date number smaller to be sure they fit into their area*/
	lv_obj_set_style_local_text_font(calendar, LV_CALENDAR_PART_DATE, LV_STATE_DEFAULT, lv_theme_get_font_small());

	/*Set today's date*/
	lv_calendar_date_t today;
	today.year = 2018;
	today.month = 10;
	today.day = 23;

	lv_calendar_set_today_date(calendar, &today);
	lv_calendar_set_showed_date(calendar, &today);

	/*Highlight a few days*/
	static lv_calendar_date_t highlighted_days[3];       /*Only its pointer will be saved so should be static*/
	highlighted_days[0].year = 2018;
	highlighted_days[0].month = 10;
	highlighted_days[0].day = 6;

	highlighted_days[1].year = 2018;
	highlighted_days[1].month = 10;
	highlighted_days[1].day = 11;

	highlighted_days[2].year = 2018;
	highlighted_days[2].month = 11;
	highlighted_days[2].day = 22;

	lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);
}

void lv_ex_spinner_1(void)
{
	/*Create a Preloader object*/
	lv_obj_t * preload = lv_spinner_create(lv_scr_act(), NULL);
	lv_obj_set_size(preload, 50, 50);
	lv_obj_align(preload, NULL, LV_ALIGN_CENTER, 0, 20);
	
	lv_obj_t * label;

	lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn1, event_handler);
	lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -40);

	label = lv_label_create(btn1, NULL);
	lv_label_set_text(label, "Button");
	
}

void lv_scr_load_1(void)
{
	lv_obj_t* one = lv_obj_create(lv_scr_act(), NULL);  //在默认屏上创建obj对象
	lv_obj_t* label = lv_label_create(one, NULL);        // 创建label  
	lv_obj_set_size(one, LV_HOR_RES, LV_VER_RES);       // 设置到屏幕大小
	lv_obj_align(label, one, LV_ALIGN_CENTER, 0, 0);    // label居屏幕中心对齐
	lv_obj_set_style_local_bg_color(one, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);       // obj背景色设成黄色
	lv_label_set_text(label, "ONE");    // label显示ONE
	
	
	lv_obj_t* two = lv_obj_create(NULL, NULL);   // 创建新屏幕但未加载到显示
	label = lv_label_create(two, NULL);         // 创建label
	lv_obj_set_size(two, LV_HOR_RES, LV_VER_RES);  //设置到屏幕大小
	lv_obj_align(label, two, LV_ALIGN_CENTER, 0, 0);  // 居中对齐
	lv_obj_set_style_local_bg_color(two, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);    // 背影色设成蓝色
	lv_label_set_text(label, "TWO");  // label上显示TWO
	
	lv_scr_load_anim(two, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 1000, true); // 加载屏幕TWO,动画效果为LV_SCR_LOAD_ANIM_FADE_ON,切换时间为500ms,延迟5000ms后从第一屏开始切换，切换完成后删除屏幕一
}

void lv_scr_load_2(void)
{
	lv_obj_t* one = lv_obj_create(lv_scr_act(), NULL);  //在默认屏上创建obj对象
	lv_obj_t * label;

		lv_obj_t * btn1 = lv_btn_create(one, NULL);
		lv_obj_set_event_cb(btn1, event_handler);
		lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, -50);

		label = lv_label_create(btn1, NULL);
		lv_label_set_text(label, "Button");

		lv_obj_t * btn2 = lv_btn_create(one, NULL);
		lv_obj_set_event_cb(btn2, event_handler);
		lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 0, 50);
		lv_btn_set_checkable(btn2, true);
		lv_btn_toggle(btn2);
		lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_NONE);

		label = lv_label_create(btn2, NULL);
		lv_label_set_text(label, "Toggled");
	
		lv_obj_t * btn3 = lv_btn_create(one, NULL);
		lv_obj_align(btn3, NULL, LV_ALIGN_CENTER, 0, 0);
		label = lv_label_create(btn3, NULL);
		lv_label_set_text(label, "Clock");
		lv_btn_set_fit2(btn3, LV_FIT_NONE, LV_FIT_NONE);
		
	lv_obj_set_style_local_bg_color(one, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);       // obj背景色设成白色


	lv_obj_t* two = lv_obj_create(NULL, NULL);   // 创建新屏幕但未加载到显示
	
	lv_obj_set_style_local_bg_color(two, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);    // 背影色设成蓝色
	lv_obj_t * preload = lv_spinner_create(two, NULL);
	lv_obj_set_size(preload, 50, 50);
	lv_obj_align(preload, NULL, LV_ALIGN_CENTER, 0, 0);
	
	lv_scr_load_anim(two, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 1000, true); // 加载屏幕TWO,动画效果为LV_SCR_LOAD_ANIM_FADE_ON,切换时间为500ms,延迟5000ms后从第一屏开始切换，切换完成后删除屏幕一
}

lv_group_t *test_group;
lv_obj_t *test_mbox;
extern lv_indev_t *indev_encoder;
void msgbox_create(void)
{

//    test_group = lv_group_create();

//    lv_indev_set_group(indev_encoder, test_group);
//    lv_group_focus_obj(test_group);          //分组聚焦到对象
//    lv_group_set_editing(test_group, true);   //编辑模式
//    static const char *test_btns[] = {"Ok", "Cancel", ""};
//    test_mbox = lv_msgbox_create(lv_layer_top(), "WX17777697205", "Welcome to the  encoder demo", test_btns, true);

//    lv_obj_align(test_mbox, LV_ALIGN_CENTER, 0, 0);
//    lv_group_focus_obj(lv_msgbox_get_btns(test_mbox));
//    lv_obj_add_state(lv_msgbox_get_btns(test_mbox), LV_STATE_FOCUS_KEY);

//    lv_obj_t * bg = lv_obj_get_parent(test_mbox);
//    lv_obj_set_style_bg_opa(bg, LV_OPA_70, 0);
//    lv_obj_set_style_bg_color(bg, lv_palette_main(LV_PALETTE_GREY), 0);

}
