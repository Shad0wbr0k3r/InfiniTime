#include "components/ble/FitoTrackService.h"
#include "systemtask/SystemTask.h"
#include <cstring>

namespace {
  // 0005yyxx-78fc-48fe-8e23-433b3a1942d0
  constexpr ble_uuid128_t CharUuid(uint8_t x, uint8_t y) {
    return ble_uuid128_t {.u = {.type = BLE_UUID_TYPE_128},
                          .value = {0xd0, 0x42, 0x19, 0x3a, 0x3b, 0x43, 0x23, 0x8e, 0xfe, 0x48, 0xfc, 0x78, x, y, 0x05, 0x00}};
  }

  // 00000000-78fc-48fe-8e23-433b3a1942d0
  constexpr ble_uuid128_t BaseUuid() {
    return CharUuid(0x00, 0x00);
  }

  constexpr ble_uuid128_t msUuid {BaseUuid()};

  constexpr ble_uuid128_t msHeartRateCharUuid {CharUuid(0x01, 0x00)};
  constexpr ble_uuid128_t msDistanceCharUuid {CharUuid(0x02, 0x00)};
  constexpr ble_uuid128_t msSpeedCharUuid {CharUuid(0x03, 0x00)};
  constexpr ble_uuid128_t msDurationCharUuid {CharUuid(0x04, 0x00)};

  constexpr uint8_t MaxStringSize {40};

  int FitoTrackCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt, void* arg) {
    return static_cast<Pinetime::Controllers::FitoTrackService*>(arg)->OnCommand(conn_handle, attr_handle, ctxt);
  }
}

Pinetime::Controllers::FitoTrackService::FitoTrackService(Pinetime::System::SystemTask& system) : m_system(system) {
  characteristicDefinition[0] = {.uuid = &msHeartRateCharUuid.u,
                                 .access_cb = FitoTrackCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE};
  characteristicDefinition[1] = {.uuid = &msSpeedCharUuid.u,
                                 .access_cb = FitoTrackCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE};
  characteristicDefinition[2] = {.uuid = &msDistanceCharUuid.u,
                                 .access_cb = FitoTrackCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE};
  characteristicDefinition[3] = {.uuid = &msDurationCharUuid.u,
                                 .access_cb = FitoTrackCallback,
                                 .arg = this,
                                 .flags = BLE_GATT_CHR_F_WRITE};

  characteristicDefinition[4] = {0};

  serviceDefinition[0] = {.type = BLE_GATT_SVC_TYPE_PRIMARY, .uuid = &msUuid.u, .characteristics = characteristicDefinition};
  serviceDefinition[1] = {0};
}

void Pinetime::Controllers::FitoTrackService::Init() {
  uint8_t res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}

int Pinetime::Controllers::FitoTrackService::OnCommand(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt) {
  if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
    size_t notifSize = OS_MBUF_PKTLEN(ctxt->om);
    size_t bufferSize = notifSize;
    if (notifSize > MaxStringSize) {
      bufferSize = MaxStringSize;
    }

    char data[bufferSize + 1];
    os_mbuf_copydata(ctxt->om, 0, bufferSize, data);

    if (notifSize > bufferSize) {
      data[bufferSize - 1] = '.';
      data[bufferSize - 2] = '.';
      data[bufferSize - 3] = '.';
    }
    data[bufferSize] = '\0';

    //char* s = &data[0];
    if (ble_uuid_cmp(ctxt->chr->uuid, &msHeartRateCharUuid.u) == 0) {
      heartRate = data;
    } else if (ble_uuid_cmp(ctxt->chr->uuid, &msSpeedCharUuid.u) == 0) {
      speed = data;
    } else if (ble_uuid_cmp(ctxt->chr->uuid, &msDistanceCharUuid.u) == 0) {
      distance = data;
    } else if (ble_uuid_cmp(ctxt->chr->uuid, &msDurationCharUuid.u) == 0) {
      duration = data;
    }
  }
  return 0;
}

std::string Pinetime::Controllers::FitoTrackService::getHeartRate() const {
  return heartRate;
}

std::string Pinetime::Controllers::FitoTrackService::getSpeed() const {
  return speed;
}

std::string Pinetime::Controllers::FitoTrackService::getDistance() const {
  return distance;
}

std::string Pinetime::Controllers::FitoTrackService::getDuration() const {
  return duration;
}

void Pinetime::Controllers::FitoTrackService::event(char event) {
  auto* om = ble_hs_mbuf_from_flat(&event, 1);

  uint16_t connectionHandle = m_system.nimble().connHandle();

  if (connectionHandle == 0 || connectionHandle == BLE_HS_CONN_HANDLE_NONE) {
    return;
  }

  ble_gattc_notify_custom(connectionHandle, eventHandle, om);
}