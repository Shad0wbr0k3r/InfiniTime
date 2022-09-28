#include "displayapp/screens/FitoTrack.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include <date/date.h>

using namespace Pinetime::Applications::Screens;

FitoTrack::FitoTrack(DisplayApp* app,
                     Controllers::DateTime& dateTimeController,
                     Controllers::Battery& batteryController,
                     Controllers::Ble& bleController)
  : Screen(app),
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
  lv_label_set_text_static(label_hrBleValue, "123");
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
  lv_label_set_text_static(label_speedValue, "32");
  lv_label_set_align(label_speedValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_speedValue, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 130, 65);
  lv_obj_set_style_local_text_font(label_speedValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);

  label_speedValueSmall = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_speedValueSmall, ".22");
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
  lv_label_set_text_static(label_distanceValue, "11");
  lv_label_set_align(label_distanceValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_distanceValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 10, -45);
  lv_obj_set_style_local_text_font(label_distanceValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);

  label_distanceValueSmall = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(label_distanceValueSmall, ".55");
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
  lv_label_set_text_static(label_durationValue, "00:15:42");
  lv_label_set_align(label_durationValue, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(label_durationValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 130, -45);
  lv_obj_set_style_local_text_font(label_durationValue, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_bold_20);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
  Refresh();
}

FitoTrack::~FitoTrack() {
  lv_obj_clean(lv_scr_act());
}

void FitoTrack::Refresh() {
  statusIcons.Update();

  currentDateTime = dateTimeController.CurrentDateTime();

  if (currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();
    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime - dp);
    auto yearMonthDay = date::year_month_day(dp);

    //auto year = static_cast<int>(yearMonthDay.year())%100;
    //auto month = static_cast<Pinetime::Controllers::DateTime::Months>(static_cast<unsigned>(yearMonthDay.month()));
    //auto day = static_cast<unsigned>(yearMonthDay.day());

    uint8_t hour = time.hours().count();
    uint8_t minute = time.minutes().count();
    uint8_t second = time.seconds().count();
    lv_label_set_text_fmt(label_dateTime, "%02d:%02d", hour, minute);

    lv_label_set_text_fmt(label_hrBleValue, "%03d", second*2);
    lv_label_set_text_fmt(label_distanceValue, "%02d", second);
    lv_label_set_text_fmt(label_distanceValueSmall, ".%02d", second+30);

    lv_label_set_text_fmt(label_speedValue, "%02d", second);
    lv_label_set_text_fmt(label_speedValueSmall, ".%02d", second+15);
  }
}