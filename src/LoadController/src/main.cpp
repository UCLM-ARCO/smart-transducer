#include <Arduino.h>
#include <IceC-IoT-node.h>

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n------Booting------\n");

  // setup WiFi, Ice, Endpoints...
  IceC_Storage_begin();

  setup_wireless();
  setup_ota();

  Serial.println("\n------Boot done!------\n");
}

void loop()
{
  handle_ota();
  check_buttons();
}