#include "displayapp/screens/FitoTrack.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"
#include "components/ble/FitoTrackService.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include <date/date.h>

using namespace Pinetime::Applications::Screens;

FitoTrack::FitoTrack(DisplayApp* app,
                     Controllers::FitoTrackService& fitoTrack,
                     Controllers::DateTime& dateTimeController,
                     Controllers::Battery& batteryController,
                     Controllers::Ble& bleController)
  : Screen(app),
    fitoTrackService(fitoTrack),
    currentDateTime {{}},
    dateTimeController {dateTimeController},
    statusIcons(batteryController, bleController)  {


  statusIcons.Create();

  label_dateTime = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_align(label_dateTime, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 0 , 0);



  label_hrBleIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_hrBleIcon, Symbols::heartBeat);
  lv_obj_set_style_local_text_color(label_hrBleIcon, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xCE1B1B));
  lv_obj_align(label_hrBleIcon, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 10 , 35);

  label_hrBleValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_hrBleValue, "-");
  lv_label_set_align(label_hrBleValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_hrBleValue, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 10, 65);
  lv_obj_set_style_local_text_color(label_hrBleValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xCE1B1B));
  lv_obj_set_style_local_text_font(label_hrBleValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  //lv_obj_set_size(label_hrBleValue, 5, 5);

  label_hrBleUnit = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_hrBleUnit, "bpm");
  lv_label_set_align(label_hrBleUnit, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_hrBleUnit, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 10, 100);
  lv_obj_set_style_local_text_color(label_hrBleUnit, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xCE1B1B));
  //lv_obj_set_style_local_text_font(label_hrBleValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_bold_20);



  label_speedTitle = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_speedTitle, Symbols::tachometer);
  lv_label_set_align(label_speedTitle, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_speedTitle, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 130, 35);

  label_speedValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_speedValue, "0");
  lv_label_set_align(label_speedValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_speedValue, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 130, 65);
  lv_obj_set_style_local_text_font(label_speedValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);

  label_speedValueSmall = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_speedValueSmall, ".00");
  lv_label_set_align(label_speedValueSmall, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_speedValueSmall, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 178, 77);


  label_speedUnit= lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_speedUnit, "km/h");
  lv_label_set_align(label_speedUnit, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_speedUnit, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 130, 100);




  label_distanceTitle = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_distanceTitle, Symbols::shoe);
  lv_label_set_align(label_distanceTitle, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_distanceTitle, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 10, -80);

  label_distanceValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_distanceValue, "0");
  lv_label_set_align(label_distanceValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_distanceValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 10, -45);
  lv_obj_set_style_local_text_font(label_distanceValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);

  label_distanceValueSmall = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_distanceValueSmall, ".000");
  lv_label_set_align(label_distanceValueSmall, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_distanceValueSmall, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 58, -33);

  label_distanceUnit = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_distanceUnit, "km");
  lv_label_set_align(label_distanceUnit, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_distanceUnit, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 10, -15);



  label_durationTitle = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_durationTitle, Symbols::stopWatch);
  lv_label_set_align(label_durationTitle, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_durationTitle, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 130, -80);

  label_durationValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_durationValue, "00:00:00");
  lv_label_set_align(label_durationValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_durationValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 130, -45);
  lv_obj_set_style_local_text_font(label_durationValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_bold_20);

  fitoTrackService.event(Controllers::FitoTrackService::EVENT_FITOTRACK_OPEN);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

FitoTrack::~FitoTrack() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void FitoTrack::Refresh() {
  statusIcons.Update();

  currentDateTime = dateTimeController.CurrentDateTime();

  if (currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();
    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime - dp);

    uint8_t hour = time.hours().count();
    uint8_t minute = time.minutes().count();
    //uint8_t second = time.seconds().count();
    lv_label_set_text_fmt(label_dateTime, "%02d:%02d", hour, minute);
  }

  if (heartRate != fitoTrackService.getHeartRate()) {
    heartRate = fitoTrackService.getHeartRate();
    lv_label_set_text(label_hrBleValue, heartRate.c_str());
  }

  if (speed != fitoTrackService.getSpeed()) {
    speed = fitoTrackService.getSpeed();
    int index = speed.find('.');

    if ((size_t) index != std::string::npos) {
      lv_label_set_text_fmt(label_speedValue, "%2s", speed.substr(0, index).c_str());
      lv_label_set_text(label_speedValueSmall, speed.substr(index).c_str());
    } else {
      lv_label_set_text(label_speedValue, speed.c_str());
    }
  }

  if (distance != fitoTrackService.getDistance()) {
    distance = fitoTrackService.getDistance();
    int index = distance.find('.');

    if ((size_t) index != std::string::npos) {
      lv_label_set_text_fmt(label_distanceValue, "%2s", distance.substr(0, index).c_str());
      lv_label_set_text(label_distanceValueSmall, distance.substr(index).c_str());
    } else {
      lv_label_set_text(label_distanceValue, distance.c_str());
    }
  }

  if (duration != fitoTrackService.getDuration()) {
    duration = fitoTrackService.getDuration();
    lv_label_set_text(label_durationValue, duration.c_str());
  }
}