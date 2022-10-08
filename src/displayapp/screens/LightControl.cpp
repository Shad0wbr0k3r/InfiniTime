#include "displayapp/screens/LightControl.h"
#include "displayapp/DisplayApp.h"
//#include "components/ble/FitoTrackService.h"
#include "components/ble/BleController.h"

using namespace Pinetime::Applications::Screens;

LightControl::LightControl(DisplayApp* app,
                     //Controllers::FitoTrackService& fitoTrack,
                     Controllers::Ble& bleController)
  : Screen(app)
    //fitoTrackService(fitoTrack),
      {




  slider_ww = lv_slider_create(lv_scr_act(), NULL);
  lv_obj_align(slider_ww, NULL, LV_ALIGN_OUT_TOP_LEFT, 20, 20);
  lv_obj_set_size(slider_ww, 10, 200);

  lv_slider_set_range(slider_ww, 0, 1023);
  
  /*
lv_arc_set_value(bpmArc, bpm);
lv_arc_set_adjustable(bpmArc, true);
   */


  //fitoTrackService.event(Controllers::FitoTrackService::EVENT_FITOTRACK_OPEN);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

LightControl::~LightControl() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void LightControl::Refresh() {
}