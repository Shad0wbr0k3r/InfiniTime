#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>
#include "components/ble/BleController.h"

namespace Pinetime {
  namespace Controllers {
    class LightControlService;
    class Ble;
  }
  namespace Applications {
    namespace Screens {
      class LightControl : public Screen {
      public:
        LightControl(DisplayApp* app,
                  Controllers::LightControlService& lightControl,
                  Controllers::Ble& bleController);
        ~LightControl() override;
        void Refresh() override;
        void OnEvent(lv_obj_t* obj, lv_event_t event);

      private:

        lv_obj_t* slider_ww;
        lv_obj_t* label_ww;

        lv_obj_t* slider_cw;
        lv_obj_t* label_cw;

        lv_style_t style_slider_ww_knob;
        lv_style_t style_slider_ww_bg;
        lv_style_t style_slider_ww_indic;

        lv_style_t style_slider_cw_knob;
        lv_style_t style_slider_cw_bg;
        lv_style_t style_slider_cw_indic;


        Controllers::LightControlService& lightControlService;

        lv_task_t* taskRefresh;
        
        int16_t lightVal_ww = 0;
        int16_t lightVal_cw = 0;

      };
    }
  }
}