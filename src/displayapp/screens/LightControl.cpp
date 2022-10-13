#include "displayapp/screens/LightControl.h"
#include "displayapp/DisplayApp.h"
#include "components/ble/LightControlService.h"
#include "components/ble/BleController.h"

using namespace Pinetime::Applications::Screens;

namespace {
  void eventHandler(lv_obj_t* obj, lv_event_t event) {
    auto* screen = static_cast<LightControl*>(obj->user_data);
    screen->OnEvent(obj, event);
  }
}

LightControl::LightControl(DisplayApp* app,
                     Controllers::LightControlService& lightControl,
                     Controllers::Ble& bleController)
  : Screen(app),
    lightControlService(lightControl) {




  lv_style_init(&style_slider_ww_knob);
  lv_style_set_bg_color(&style_slider_ww_knob, LV_STATE_DEFAULT, lv_color_hex(0xFFFFAA));
  //lv_style_set_bg_opa(&style_slider_knob, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  lv_style_set_border_width(&style_slider_ww_knob, LV_STATE_DEFAULT, 8);
  //lv_style_set_border_color(&style_slider_knob, LV_STATE_DEFAULT, lv_color_hex(0xFF00FF));
  lv_style_set_border_opa(&style_slider_ww_knob, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  //lv_style_set_transform_height(&style_slider_knob, LV_STATE_DEFAULT, 0);

  lv_style_init(&style_slider_ww_bg);
  //lv_style_set_bg_color(&style_slider_bg, LV_STATE_DEFAULT, lv_color_hex(0x00FF00));
  lv_style_set_bg_opa(&style_slider_ww_bg, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  lv_style_set_border_width(&style_slider_ww_bg, LV_STATE_DEFAULT, 2);
  lv_style_set_border_color(&style_slider_ww_bg, LV_STATE_DEFAULT, lv_color_hex(0xFFFFAA));
  //lv_style_set_transform_height(&style_slider_bg, LV_STATE_DEFAULT, 0);

  lv_style_init(&style_slider_ww_indic);
  lv_style_set_bg_color(&style_slider_ww_indic, LV_STATE_DEFAULT, lv_color_hex(0x0000FF));
  //lv_style_set_bg_opa(&style_slider_indic, LV_STATE_DEFAULT, LV_OPA_TRANSP);
  //lv_style_set_border_width(&style_slider_indic, LV_STATE_DEFAULT, 2);
  //lv_style_set_transform_height(&style_slider_indic, LV_STATE_DEFAULT, 0);


  slider_ww = lv_slider_create(lv_scr_act(), nullptr);
  slider_ww->user_data = this;
  lv_obj_add_style(slider_ww, LV_SLIDER_PART_KNOB, &style_slider_ww_knob);
  lv_obj_add_style(slider_ww, LV_SLIDER_PART_BG, &style_slider_ww_bg);
  lv_obj_add_style(slider_ww, LV_SLIDER_PART_INDIC, &style_slider_ww_indic);

  //lv_obj_set_style_bg_opa(slider_ww, LV_OPA_100, LV_PART_MAIN);
  //lv_obj_set_style_opa(slider_ww, LV_OPA_100, LV_PART_MAIN);
  lv_obj_align(slider_ww, NULL, LV_ALIGN_OUT_TOP_LEFT, 55, 30);
  lv_obj_set_size(slider_ww, 20, 160);
  lv_arc_set_adjustable(slider_ww, true);
  //lv_slider_set_style(slider_ww, LV_SLIDER_STYLE_KNOB, NULL);
  lv_slider_set_range(slider_ww, 0, 1023);
  //lv_slider_set_value(slider_ww, lightVal_ww, false);
  lv_obj_set_event_cb(slider_ww, eventHandler);


  lv_style_init(&style_slider_cw_knob);
  lv_style_set_bg_color(&style_slider_cw_knob, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
  lv_style_init(&style_slider_cw_bg);
  lv_style_set_border_color(&style_slider_cw_bg, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
  lv_style_init(&style_slider_cw_indic);
  lv_style_set_border_color(&style_slider_cw_indic, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));



  slider_cw = lv_slider_create(lv_scr_act(), nullptr);
  slider_cw->user_data = this;
  lv_obj_add_style(slider_cw, LV_SLIDER_PART_KNOB, &style_slider_ww_knob);
  lv_obj_add_style(slider_cw, LV_SLIDER_PART_BG, &style_slider_ww_bg);
  lv_obj_add_style(slider_cw, LV_SLIDER_PART_INDIC, &style_slider_ww_indic);
  lv_obj_add_style(slider_cw, LV_SLIDER_PART_KNOB, &style_slider_cw_knob);
  lv_obj_add_style(slider_cw, LV_SLIDER_PART_BG, &style_slider_cw_bg);
  lv_obj_add_style(slider_cw, LV_SLIDER_PART_INDIC, &style_slider_cw_indic);
  lv_obj_align(slider_cw, NULL, LV_ALIGN_OUT_TOP_LEFT, 165, 30);
  lv_obj_set_size(slider_cw, 20, 160);
  lv_arc_set_adjustable(slider_cw, true);
  lv_slider_set_range(slider_cw, 0, 1023);
  //lv_slider_set_value(slider_cw, lightVal_cw, false);
  lv_obj_set_event_cb(slider_cw, eventHandler);

  label_ww = lv_label_create(lv_scr_act(), nullptr);
  label_ww->user_data = this;
  lv_label_set_text_fmt(label_ww, "%d", lightVal_ww);
  lv_obj_set_style_local_text_color(label_ww, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFFFAA));
  //lv_obj_align(label_ww, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 45 , 210);
  lv_obj_set_auto_realign(label_ww, true);
  lv_obj_align(label_ww, slider_ww, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

  label_cw = lv_label_create(lv_scr_act(), nullptr);
  label_cw->user_data = this;
  lv_label_set_text_fmt(label_cw, "%d", lightVal_cw);
  lv_obj_set_style_local_text_color(label_cw, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
  //lv_obj_align(label_cw, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 150 , 210);
  lv_obj_set_auto_realign(label_cw, true);
  lv_obj_align(label_cw, slider_cw, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

  //lightControlService.event(Controllers::LightControlService::EVENT_LIGHTCONTROL_OPEN);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

LightControl::~LightControl() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void LightControl::Refresh() {
}

void LightControl::OnEvent(lv_obj_t* obj, lv_event_t event) {
  if (event == LV_EVENT_VALUE_CHANGED) {
    if (obj == slider_ww) {
      lightVal_ww = lv_slider_get_value(slider_ww);
      lv_label_set_text_fmt(label_ww, "%d", lightVal_ww);
      lightControlService.OnNewLightVal(0, lightVal_ww);
    } else if (obj == slider_cw) {
      lightVal_cw = lv_slider_get_value(slider_cw);
      lv_label_set_text_fmt(label_cw, "%d", lightVal_cw);
      lightControlService.OnNewLightVal(1, lightVal_cw);
    }
  }
}
