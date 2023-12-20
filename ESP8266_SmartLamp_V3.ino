//Requirements:
//Mode switch to Websocket connection -> JSON send websocket connection
// -> stream RT color data

//OTA CI/CD
//modular system loading

#include <FastLED.h>
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

//FASTLED CONFIG
//#define FASTLED_ALLOW_INTERRUPTS 0 //might not be needed
#define LED_PIN     D3
#define NUM_LEDS    50
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//MQTT Setup
#define WIFI_SSID "ssid"
#define WIFI_PASS "pass"
#define MQTT_SERV "192.168.0.32"
#define MQTT_TOPIC "lamp/TestDevice"
#define MQTT_NAME "ESP8266_V3_TestDevice"
WiFiClient espClient;
PubSubClient client(espClient);

//JSON Setup
static StaticJsonDocument<2048> doc; //TODO: 4kb too much
DeserializationError error;

//Dynamic vars
bool newDataReady = false;
int8_t cycleSpeed = 0;
uint8_t lampMode = 0; //0-palette, 1-websocket, 2-gradient
float refreshRate = 30;

//const char* websocket_server = "ws://192.168.0.32:1880/ws/lamp/test";
String websocket_server = "ws://192.168.0.72:1880/";
using namespace websockets;
WebsocketsClient wsclient;

bool statusLed = false;
uint8_t startOffset = 0;
unsigned long connectionTimer = 0;
unsigned long mqTimer = 0;
unsigned long ledShowTimer = 0;
////////////////////////////////////////////////////////////



void setup() {  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  fill_solid( currentPalette, NUM_LEDS, CRGB::Black);

  Serial.begin(115200);
  
  wifi_setup();
  OTA_setup();
  client.setServer(MQTT_SERV, 1883);
  client.setCallback(callback);
  client.setBufferSize(2048);

  blinkStatusLed(CRGB::Black);
}

void loop() {
  
  if (millis() > connectionTimer + 5000) {
    connectionTimer = millis();
    ArduinoOTA.handle();
    if (!client.connected())
      reconnect();    
  }

  if (millis() - mqTimer > 100) {
    mqTimer = millis();
    client.loop();

    if (newDataReady) {
      newDataReady = false;
      ReadData();
    }
  }

  //websocket mode
  if(lampMode == 1){
    wsclient.poll();
  }

  WriteLEDs();
}
