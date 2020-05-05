#include <Arduino.h>

const gpio_num_t switchPin = GPIO_NUM_34;
const gpio_num_t ledPinR = GPIO_NUM_27;
const gpio_num_t ledPinY = GPIO_NUM_26;
const gpio_num_t ledPinG = GPIO_NUM_25;

void setup()
{
  Serial.begin(115200);

  pinMode(switchPin, INPUT);

  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);

  randomSeed(analogRead(0));
}

void light_off()
{
  digitalWrite(ledPinR, 0);
  digitalWrite(ledPinY, 0);
  digitalWrite(ledPinG, 0);
}

void light(int num)
{
  switch (num % 3)
  {
  case 0:
    digitalWrite(ledPinR, 0);
    digitalWrite(ledPinY, 0);
    digitalWrite(ledPinG, 1);
    break;
  case 1:
    digitalWrite(ledPinR, 0);
    digitalWrite(ledPinY, 1);
    digitalWrite(ledPinG, 0);
    break;
  case 2:
    digitalWrite(ledPinR, 1);
    digitalWrite(ledPinY, 0);
    digitalWrite(ledPinG, 0);
    break;
  }
}

void loop()
{
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0)
  {
    int count = random(30, 36);
    Serial.print("count:");
    Serial.println(count);

    for (int i = 0; i < count; i++)
    {
      light(i);
      delay(10 * i);
    }

    for (int i = 0; i < 5; i++)
    {
      delay(100);
      light_off();
      delay(100);
      light(count);
    }

    delay(3000);
  }

  esp_sleep_enable_ext0_wakeup(switchPin, 1);
  esp_deep_sleep_start();
}