#pragma once
#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#include <atomic>
#undef max
#undef min

namespace Pinetime {
  namespace System {
    class SystemTask;
  }
  namespace Controllers {
    class LightControlService {
    public:
      LightControlService(Pinetime::System::SystemTask& system);
      void Init();
      int OnLightValRequested(uint16_t connectionHandle, uint16_t attributeHandle, ble_gatt_access_ctxt* context);
      void OnNewLightVal(uint8_t type, int16_t lightValue);

      void SubscribeNotification(uint16_t connectionHandle, uint16_t attributeHandle);
      void UnsubscribeNotification(uint16_t connectionHandle, uint16_t attributeHandle);

      int16_t lightVal = 0;
      uint8_t lightType = 0;

    private:
      Pinetime::System::SystemTask& system;

      static constexpr ble_uuid128_t lightControlServiceUuid {.u = {.type = BLE_UUID_TYPE_128},
                                                              .value = {0xd0, 0x42, 0x19, 0x3a, 0x3b, 0x43, 0x23, 0x8e, 0xfe, 0x48, 0xfc, 0x78, 0, 0, 0x06, 0x00}};
      static constexpr ble_uuid128_t lightControlCharacteristicUuid {.u = {.type = BLE_UUID_TYPE_128},
                                                                     .value = {0xd0, 0x42, 0x19, 0x3a, 0x3b, 0x43, 0x23, 0x8e, 0xfe, 0x48, 0xfc, 0x78, 0x01, 0x00, 0x06, 0x00}};

      struct ble_gatt_chr_def characteristicDefinition[2];
      struct ble_gatt_svc_def serviceDefinition[2];

      uint16_t eventHandle;

      std::atomic_bool lightControlNotificationEnable {false};
    };
  }
}
