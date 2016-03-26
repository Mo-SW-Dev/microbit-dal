#ifndef MICROBIT_LED_SERVICE_H
#define MICROBIT_LED_SERVICE_H

#include "MicroBitConfig.h"
#include "ble/BLE.h"
#include "MicroBitDisplay.h"

// Defines the buffer size for scrolling text over BLE, hence also defines
// the maximum string length that can be scrolled via the BLE service.
#define MICROBIT_BLE_MAXIMUM_SCROLLTEXT         20

// UUIDs for our service and characteristics
extern const uint8_t  MicroBitLEDServiceUUID[];
extern const uint8_t  MicroBitLEDServiceMatrixUUID[];
extern const uint8_t  MicroBitLEDServiceTextUUID[];
extern const uint8_t  MicroBitLEDServiceScrollingSpeedUUID[];


/**
  * Class definition for a MicroBit BLE Event Service.
  * Provides a _ble gateway onto the MicroBit Message Bus.
  */
class MicroBitLEDService
{
    public:

    /**
      * Constructor.
      * Create a representation of the LEDService
      * @param BLE The instance of a BLE device that we're running on.
      * @param display The instance of a MicroBitDisplay to interface with.
      */
    MicroBitLEDService(BLEDevice &_ble, MicroBitDisplay &_display);

    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten(const GattWriteCallbackParams *params);

    /**
      * Callback. Invoked when any of our attributes are read via BLE.
      */
    void onDataRead(GattReadAuthCallbackParams *params);

    private:

    // Bluetooth stack we're running on.
    BLEDevice           &ble;
    MicroBitDisplay     &display;

    // memory for our 8 bit control characteristics.
    uint8_t             matrixCharacteristicBuffer[5];
    uint16_t            scrollingSpeedCharacteristicBuffer;
    uint8_t             textCharacteristicBuffer[MICROBIT_BLE_MAXIMUM_SCROLLTEXT];

    // Handles to access each characteristic when they are held by Soft Device.
    GattAttribute::Handle_t matrixCharacteristicHandle;
    GattAttribute::Handle_t textCharacteristicHandle;
    GattAttribute::Handle_t scrollingSpeedCharacteristicHandle;

    // We hold a copy of the GattCharacteristic, as mbed's BLE API requires this to provide read callbacks (pity!).
    GattCharacteristic  matrixCharacteristic;
};


#endif