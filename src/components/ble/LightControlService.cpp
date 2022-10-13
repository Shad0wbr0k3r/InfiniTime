#include "components/ble/LightControlService.h"
#include "systemtask/SystemTask.h"

using namespace Pinetime::Controllers;

constexpr ble_uuid128_t LightControlService::lightControlServiceUuid;
constexpr ble_uuid128_t LightControlService::lightControlCharacteristicUuid;

namespace {
  int LightControlServiceCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt, void* arg) {
    auto* lightControlService = static_cast<LightControlService*>(arg);
    return lightControlService->OnLightValRequested(conn_handle, attr_handle, ctxt);
  }
}

LightControlService::LightControlService(Pinetime::System::SystemTask& system)
  : system {system},
    characteristicDefinition {{.uuid = &lightControlCharacteristicUuid.u,
                               .access_cb = LightControlServiceCallback,
                               .arg = this,
                               .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
                               .val_handle = &eventHandle},
                              {0}},
    serviceDefinition {
      {/* Device Information Service */
       .type = BLE_GATT_SVC_TYPE_PRIMARY,
       .uuid = &lightControlServiceUuid.u,
       .characteristics = characteristicDefinition},
      {0},
    } {
}

void LightControlService::Init() {
  uint8_t res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}



int LightControlService::OnLightValRequested(uint16_t connectionHandle, uint16_t attributeHandle, ble_gatt_access_ctxt* context) {
  if (attributeHandle == eventHandle) {
    uint8_t buffer[3] = {this->lightType, this->lightVal>>8, this->lightVal&0xFF};

    int res = os_mbuf_append(context->om, buffer, 3);
    return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
  }
  return 0;
}

void LightControlService::OnNewLightVal(uint8_t type, int16_t lightValue) {
  this->lightType = type;
  this->lightVal = lightValue;
  if (!lightControlNotificationEnable)
    return;

  uint8_t buffer[3] = {this->lightType, this->lightVal>>8, this->lightVal&0xFF};
  auto* om = ble_hs_mbuf_from_flat(buffer, 3);

  uint16_t connectionHandle = system.nimble().connHandle();

  if (connectionHandle == 0 || connectionHandle == BLE_HS_CONN_HANDLE_NONE) {
    return;
  }

  ble_gattc_notify_custom(connectionHandle, eventHandle, om);
}

void LightControlService::SubscribeNotification(uint16_t connectionHandle, uint16_t attributeHandle) {
  if (attributeHandle == eventHandle)
    lightControlNotificationEnable = true;
}

void LightControlService::UnsubscribeNotification(uint16_t connectionHandle, uint16_t attributeHandle) {
  if (attributeHandle == eventHandle)
    lightControlNotificationEnable = false;
}