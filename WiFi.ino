void connectToWebsocket() {
  wsclient.onEvent(onEventsCallback);
  wsclient.onMessage(onMessageCallback);
  wsclient.connect(websocket_server);
}

void onEventsCallback(WebsocketsEvent event, String data) {
  if (event == WebsocketsEvent::ConnectionOpened) {
    //Serial.println("Connnection to WebSocket server established");
  } else if (event == WebsocketsEvent::ConnectionClosed) {
    //Serial.println("Connection to WebSocket server closed");
  } else if (event == WebsocketsEvent::GotPing) {
    // Handle pings if necessary
  } else if (event == WebsocketsEvent::GotPong) {
    // Handle pongs if necessary
  }
}

void onMessageCallback(WebsocketsMessage message) {
  writeBytesToLEDs(message.c_str(), NUM_LEDS*3);
  FastLED.show();
}

void callback(char* topic, byte* payload, unsigned int length) {
  error = deserializeJson(doc, (const byte*)payload);
  if (!error) newDataReady = true;
  //TODO: else flash red
}

void wifi_setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.persistent(false);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  //WiFi.setNoDelay(false);

  while (WiFi.status() != WL_CONNECTED){
    blinkStatusLed(CRGB::Red);
    delay(100); //wait connected
  }

  //try to update
  //t_httpUpdate_return ret = ESPhttpUpdate.update(UPDATE_SERVER, UPDATE_PORT, "/update.bin");
}

void reconnect() {
  //TODO: disable leds
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect(MQTT_NAME)) {
      // ... and resubscribe
      client.subscribe(MQTT_TOPIC);
    } else {
      // Wait 5 seconds before retrying
      blinkStatusLed(CRGB::Green);
      delay(2500);
    }
  }
}

void resetDevice()
{
  ESP.restart();
}
