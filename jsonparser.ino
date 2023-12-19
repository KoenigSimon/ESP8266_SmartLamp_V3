void ReadData()
{
  if (doc["reset"]) resetDevice();

  if (doc.containsKey("webSocketConnection"))
    websocket_server = doc["webSocketConnection"].as<String>();
  if (doc.containsKey("webSocketMode")){
    lampMode = doc["webSocketMode"];
    if (lampMode == 1){
      connectToWebsocket();
    } else {
      wsclient.close();
    }
  }

  if (doc.containsKey("brightness"))
    FastLED.setBrightness( doc["brightness"] );
  if (doc.containsKey("cycleSpeed"))
    cycleSpeed = doc["cycleSpeed"];
  if (doc.containsKey("blendingMode"))
    currentBlending = doc["blendingMode"] == 0 ? NOBLEND : LINEARBLEND;
  if (doc.containsKey("refreshRate"))
    refreshRate = 1000.0 / (doc["refreshRate"] == 0.0 ? 1.0 : doc["refreshRate"]);

  if (doc.containsKey("palette")){
    lampMode = 0;
    JsonArray palette = doc["palette"];
    currentPalette = CRGBPalette16(
      CRGB(palette[0][0], palette[0][1], palette[0][2]),
      CRGB(palette[1][0], palette[1][1], palette[1][2]),
      CRGB(palette[2][0], palette[2][1], palette[2][2]),
      CRGB(palette[3][0], palette[3][1], palette[3][2]),
      CRGB(palette[4][0], palette[4][1], palette[4][2]),
      CRGB(palette[5][0], palette[5][1], palette[5][2]),
      CRGB(palette[6][0], palette[6][1], palette[6][2]),
      CRGB(palette[7][0], palette[7][1], palette[7][2]),
      CRGB(palette[8][0], palette[8][1], palette[8][2]),
      CRGB(palette[9][0], palette[9][1], palette[9][2]),
      CRGB(palette[10][0], palette[10][1], palette[10][2]),
      CRGB(palette[11][0], palette[11][1], palette[11][2]),
      CRGB(palette[12][0], palette[12][1], palette[12][2]),
      CRGB(palette[13][0], palette[13][1], palette[13][2]),
      CRGB(palette[14][0], palette[14][1], palette[14][2]),
      CRGB(palette[15][0], palette[15][1], palette[15][2])
    );
  }

  if (doc.containsKey("gradient2")){
    lampMode = 2;
    JsonArray palette = doc["gradient2"];
    fill_gradient_RGB(leds, NUM_LEDS, 
    CRGB(palette[0][0], palette[0][1], palette[0][2]),
    CRGB(palette[1][0], palette[1][1], palette[1][2]));
  }

  if (doc.containsKey("gradient3")){
    lampMode = 2;
    JsonArray palette = doc["gradient3"];
    fill_gradient_RGB(leds, NUM_LEDS, 
    CRGB(palette[0][0], palette[0][1], palette[0][2]),
    CRGB(palette[1][0], palette[1][1], palette[1][2]),
    CRGB(palette[2][0], palette[2][1], palette[2][2]));
  }

  if (doc.containsKey("gradient4")){
    lampMode = 2;
    JsonArray palette = doc["gradient4"];
    fill_gradient_RGB(leds, NUM_LEDS, 
    CRGB(palette[0][0], palette[0][1], palette[0][2]),
    CRGB(palette[1][0], palette[1][1], palette[1][2]),
    CRGB(palette[2][0], palette[2][1], palette[2][2]),
    CRGB(palette[3][0], palette[3][1], palette[3][2]));
  }
}
