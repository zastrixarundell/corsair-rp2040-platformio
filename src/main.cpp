/*
   Copyright 2021 Leon Kiefer

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <CorsairLightingProtocol.h>
#include <FastLED.h>

#define DATA_PIN_CHANNEL 16
#define LED_LENGTH 18

CRGB ledsChannel[18];

// Most ARM devices do not contain an EEPROM; we will use static storage for the Device ID
DeviceID deviceID = {0x9A, 0xDA, 0xA7, 0x8E};
CorsairLightingFirmwareStorageStatic firmwareStorage(deviceID);
CorsairLightingFirmware firmware(CORSAIR_LIGHTING_NODE_PRO, &firmwareStorage);
FastLEDController ledController(nullptr);
CorsairLightingProtocolController cLP(&ledController, &firmware);
CorsairLightingProtocolTinyUSBHID cHID(&cLP);

void setup() {
	cHID.setup();

	FastLED.addLeds<WS2812B, DATA_PIN_CHANNEL, GRB>(ledsChannel, LED_LENGTH);
	ledController.addLEDs(0, ledsChannel, 18);
}

void loop() {
	cHID.update();

	if (ledController.updateLEDs()) {
		FastLED.show();
	}
}
