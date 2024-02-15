#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "led.hpp"
#include "auth.hpp"


BLEServer* pServer = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
bool deviceConnected = false;

// UUIDs can be randomly generated or specific to your application
#define SERVICE_UUID        "a4122eb1-921d-472d-90f0-d59b54c60804"
#define CHARACTERISTIC_UUID "6f5176cd-d06f-4dd4-a845-bfd0952b760c"

class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      flash_blue(3);
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      flash_red(3);
      deviceConnected = false;
      pServer->getAdvertising()->start();
    }
};

class AuthCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String value = pCharacteristic->getValue().c_str();

      if (value.length() > 0) {
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        String user = getUser(value);
        Serial.println(user);
        if (user != "") {
          flash_green(5);
        } else {
          flash_red(5);
        }
        Serial.println();
      }
    }
};

void initBluetooth() {
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("ESP32_AC");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pCharacteristic->setCallbacks(new AuthCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting for a client connection to notify...");
}
