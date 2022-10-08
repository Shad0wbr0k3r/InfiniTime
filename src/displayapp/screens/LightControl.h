#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>
#include "components/ble/BleController.h"

namespace Pinetime {
  namespace Controllers {
    //class FitoTrackService;
    class Ble;
  }
  namespace Applications {
    namespace Screens {
      class LightControl : public Screen {
      public:
        LightControl(DisplayApp* app,
                  //Controllers::FitoTrackService& fitoTrack,
                  Controllers::Ble& bleController);
        ~LightControl() override;

        void Refresh() override;

      private:

        lv_obj_t* slider_ww;
        lv_obj_t* label_ww;

        //Controllers::FitoTrackService& fitoTrackService;

        lv_task_t* taskRefresh;
        
        int lightVal_ww;

      };
    }
  }
}