#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>
#include "components/datetime/DateTimeController.h"
#include "components/ble/BleController.h"
#include "displayapp/widgets/StatusIcons.h"

namespace Pinetime {
  namespace Controllers {
    class FitoTrackService;
    class Battery;
    class Ble;
  }
  namespace Applications {
    namespace Screens {
      class FitoTrack : public Screen {
      public:
        FitoTrack(DisplayApp* app,
                  Controllers::FitoTrackService& fitoTrack,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController);
        ~FitoTrack() override;

        void Refresh() override;

      private:
        DirtyValue<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime {};

        lv_obj_t* label_dateTime;
        lv_obj_t* label_hrBleIcon;
        lv_obj_t* label_hrBleValue;
        lv_obj_t* label_hrBleUnit;
        lv_obj_t* label_speedTitle;
        lv_obj_t* label_speedValue;
        lv_obj_t* label_speedValueSmall;
        lv_obj_t* label_speedUnit;
        lv_obj_t* label_distanceTitle;
        lv_obj_t* label_distanceValue;
        lv_obj_t* label_distanceValueSmall;
        lv_obj_t* label_distanceUnit;
        lv_obj_t* label_durationTitle;
        lv_obj_t* label_durationValue;

        Controllers::FitoTrackService& fitoTrackService;
        Controllers::DateTime& dateTimeController;

        lv_task_t* taskRefresh;
        Widgets::StatusIcons statusIcons;

        std::string heartRate;
        std::string speed;
        std::string distance;
        std::string duration;
      };
    }
  }
}