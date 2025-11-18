## Installation Arduino CLI

https://docs.arduino.cc/arduino-cli/installation/#download

```shell
arduino-cli version
arduino-cli config init
arduino-cli config add board_manager.additional_urls https://github.com/ambiot/ambd_arduino/raw/master/Arduino_package/package_realtek.com_amebad_index.json
arduino-cli config dump
arduino-cli core update-index
arduino-cli core search  # look for ID `realtek:AmebaD`
arduino-cli core install realtek:AmebaD
arduino-cli core list
```

## Code d'exemple

Fichier `bw16.ino`

```c
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin's from all 3 colors as an output.
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

// blink RED, GREEN, BLUE
void blink() {
  digitalWrite(LED_R, HIGH);  // turn the RED LED on (HIGH is the voltage level)
  delay(1000);                // wait for a second
  digitalWrite(LED_R, LOW);   // turn the RED LED off by making the voltage LOW
  delay(1000);                // wait for a second
  digitalWrite(LED_G, HIGH);  // turn the GREEN LED on (HIGH is the voltage level)
  delay(1000);                // wait for a second
  digitalWrite(LED_G, LOW);   // turn the GREEN LED off by making the voltage LOW
  delay(1000);                // wait for a second
  digitalWrite(LED_B, HIGH);  // turn the BLUE LED on (HIGH is the voltage level)
  delay(1000);                // wait for a second
  digitalWrite(LED_B, LOW);   // turn the BLUE LED off by making the voltage LOW
  delay(1000);                // wait for a second
}

// fade RED and BLUE
void fade() {
  // fade RED in from min to max in increments of 5 points:
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(LED_R, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade RED out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(LED_R, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade BLUE in from min to max in increments of 5 points:
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(LED_B, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade BLUE out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(LED_B, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

// the loop function runs over and over again forever
void loop() {
  blink();      // blink RED, GREEN, BLUE
  fade();       // fade RED, BLUE
  delay(1000);  // wait for a second
}
```

```shell
arduino-cli compile \
  --verbose \
  --fqbn realtek:AmebaD:Ai-Thinker_BW16 \
  --build-path build
```

Fichier binaire généré : `build/km0_km4_image2.bin`

## VSCodium extensions

- `clangd` (llvm-vs-code-extensions)
- `Cortex-Debug` (marus25)

## Liens

- https://www.amebaiot.com/en/amebad-bw16-arduino-getting-started/
- https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_d/bw16-typeb/Getting_Started/Getting%20Started%20with%20BW16.html
- https://docs.arduino.cc/arduino-cli/getting-started/
- https://elm-chan.org/fsw/ff/
