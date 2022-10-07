#pragma once

#include <cstdint>
#include <string>
#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#include <host/ble_uuid.h>
#undef max
#undef min

namespace Pinetime {
  namespace System {
    class SystemTask;
  }
  namespace Controllers {
    class FitoTrackService {
    public:
      explicit FitoTrackService(Pinetime::System::SystemTask& system);

      void Init();

      int OnCommand(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt* ctxt);

      void event(char event);

      std::string getHeartRate() const;

      std::string getSpeed() const;

      std::string getDistance() const;

      std::string getDuration() const;

      static const char EVENT_FITOTRACK_OPEN = 0xe0;

    private:
      struct ble_gatt_chr_def characteristicDefinition[14];
      struct ble_gatt_svc_def serviceDefinition[2];

      uint16_t eventHandle {};

      std::string heartRate {"-"};
      std::string speed {"0.00"};
      std::string distance {"0.000"};
      std::string duration {"00:00:00"};

      Pinetime::System::SystemTask& m_system;
    };
  }
}
