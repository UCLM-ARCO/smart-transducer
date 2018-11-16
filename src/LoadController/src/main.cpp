#include <Arduino.h>
#include <ESP8266WiFi.h> // force IDE to include this

#include <IceC-IoT-node.h>
#include <IceC/IceC.h>
#include <IceC/platforms/esp8266/TCPEndpoint.h>
#include <IceC/platforms/esp8266/debug.hpp>

#include <lifelike.h>

Ice_Communicator ic;
Ice_ObjectAdapter adapter;
LifeLike_LoadNode node;

void IoT_IDMAdminI_setIDMAddress(IoT_IDMAdminPtr self, Ice_String address)
{
  Serial.println("IDMAdmin::setIDMADDRESS()");
  char value[address.size + 1];
  strncpy(value, address.value, address.size);
  value[address.size] = 0;
  Serial.println( value);
}

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n------Booting------\n");

  // setup WiFi, Ice, Endpoints...
  IceC_Storage_begin();
  setup_wireless();
  setup_ota();

  Ice_initialize(&ic);
  TCPEndpoint_init(&ic);

  // create adapter and add its servants
  Ice_Communicator_createObjectAdapterWithEndpoints(
      &ic, "Adapter", "tcp -p 4455", &adapter);
  Ice_ObjectAdapter_activate(&adapter);
  LifeLike_LoadNode_init(&node);
  Ice_ObjectAdapter_add(&adapter, (Ice_ObjectPtr)&node, "Node");

  Serial.println("\n------Boot done!------\n");
}

void loop()
{
  handle_ota();
  check_buttons();
  Ice_Communicator_loopIteration(&ic);
}