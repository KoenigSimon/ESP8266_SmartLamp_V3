void WriteLEDs(){
  if (lampMode == 0){
    writeCurrentPalette(startOffset);
  }
  if (ledShowTimer + refreshRate < millis()){
    ledShowTimer = millis();
    startOffset += cycleSpeed;
    FastLED.show();
  }
}

void writeCurrentPalette(uint8_t offset) {
  uint8_t colorIndex;
  for (int i = 0; i < NUM_LEDS; i++) {
    // Calculate the color index with offset and wrap around if needed
    colorIndex = (offset + (i * 256) / NUM_LEDS);// % 256;
    leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);
  }
}

void blinkStatusLed(CRGB color){
  leds[0] = (statusLed == true ? color : CRGB::Black);
  statusLed = !statusLed;
  FastLED.show();
  FastLED.delay(50);
}

void writeBytesToLEDs(const char* data, int length) {
  int numColors = length / 3; // 3 bytes per color
  for(int i = 0; i < numColors && i < NUM_LEDS; i++) {
    leds[i] = CRGB(data[i*3], data[i*3+1], data[i*3+2]);
  }
}
