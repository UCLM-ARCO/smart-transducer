#include <Arduino.h>
#include <ESP8266WiFi.h> // force IDE to include this

#include <IceC-IoT-node.h>
#include <IceC/IceC.h>
#include <IceC/platforms/esp8266/TCPEndpoint.h>
#include <IceC/platforms/esp8266/debug.hpp>

#include "lifelike.h"

#ifndef PIN_RELAY
#define PIN_RELAY 12
#endif

#define MAX_PROXY_SIZE 64
#define MAX_IDM_ADD_SIZE 16
#define DBINDEX_IDM_ADDR DBINDEX_LAST
#define DBINDEX_IDM_ROUTER DBINDEX_IDM_ADDR + MAX_IDM_ADD_SIZE
#define DBINDEX_OBSERVER DBINDEX_IDM_ROUTER + MAX_PROXY_SIZE

Ice_Communicator ic;
Ice_ObjectAdapter adapter;
LifeLike_LoadNode node;

void IoT_NodeAdminI_restart(IoT_NodeAdminPtr self)
{
  async_restart_node();
}

void IoT_NodeAdminI_factoryReset(IoT_NodeAdminPtr self)
{
  async_factory_reset();
}

void IoT_IDMAdminI_setIDMRouter(IoT_IDMAdminPtr self,
                                Ice_String proxy)
{
  const char zero = 0;
  IceC_Storage_put(DBINDEX_IDM_ROUTER, proxy.value, proxy.size);
  IceC_Storage_put(DBINDEX_IDM_ROUTER + proxy.size, &zero, 1);

  char prx[proxy.size + 1];
  strncpy(prx, proxy.value, proxy.size);
  prx[proxy.size] = 0;

  Serial.printf("IDM: set router to '%s'\n", prx);
}

void IoT_IDMAdminI_setIDMAddress(IoT_IDMAdminPtr self,
                                 Ice_String address)
{
  const char zero = 0;
  IceC_Storage_put(DBINDEX_IDM_ADDR, address.value, address.size);
  IceC_Storage_put(DBINDEX_IDM_ADDR + address.size, &zero, 1);

  char addr[address.size + 1];
  strncpy(addr, address.value, address.size);
  addr[address.size] = 0;

  Serial.printf("IDM: set address to '%s'\n", addr);
}

void IoT_WiFiAdminI_setupWiFi(IoT_WiFiAdminPtr self,
                              Ice_String ssid,
                              Ice_String key)
{
  store_wifi_settings(ssid, key);
}

void st_IBoolI_set(st_IBoolPtr self,
                   Ice_Bool v,
                   Ice_String sourceAddr)
{
  digitalWrite(PIN_RELAY, v ? HIGH : LOW);
  digitalWrite(LED_BUILTIN, v ? HIGH : LOW);

  // FIXME: use observer and router proxy to notify changes
}

void st_LinkableI_linkto(st_LinkablePtr self,
                         Ice_String observerAddr)
{
  const char zero = 0;
  IceC_Storage_put(DBINDEX_OBSERVER, observerAddr.value, observerAddr.size);
  IceC_Storage_put(DBINDEX_OBSERVER + observerAddr.size, &zero, 1);

  char addr[observerAddr.size + 1];
  strncpy(addr, observerAddr.value, observerAddr.size);
  addr[observerAddr.size] = 0;

  Serial.printf("ST: link to IDM addr '%s'\n", addr);
}

void check_button()
{
  if (digitalRead(PIN_BUTTON) == 1)
    return;

  bool erase = false;
  bool led_state = false;
  long start = millis();
  while (digitalRead(PIN_BUTTON) == 0)
  {
    delay(100);

    if (millis() - start > 3000)
    {
      erase = true;
      digitalWrite(STATUS_LED, led_state);
      led_state = !led_state;
    }
  }

  if (erase)
    factory_reset();
  reset_node();
}

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
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

  // get node address from stored settings
  char addr[MAX_IDM_ADD_SIZE] = {0};
  IceC_Storage_get(DBINDEX_IDM_ADDR, addr, MAX_IDM_ADD_SIZE);
  if (addr[0] == 0)
    strcpy(addr, "Node");

  Ice_ObjectAdapter_add(&adapter, (Ice_ObjectPtr)&node, addr);
  Serial.printf("IDM: node address '%s'\n", addr);

  Serial.println("\n------Boot done!------\n");
}

void loop()
{
  handle_ota();
  check_button();
  Ice_Communicator_loopIteration(&ic);
}