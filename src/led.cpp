#include <Arduino.h>

#define RGB_BRIGHTNESS 255


void flash_blue(int count)
{
    for (int i = 0; i < count; i++)
    {
        digitalWrite(LED_BLUE, HIGH);
        delay(300);
        digitalWrite(LED_BLUE, LOW);
        delay(300);
    }
    digitalWrite(LED_BLUE, HIGH);
}

void flash_red(int count)
{
    for (int i = 0; i < count; i++)
    {
        digitalWrite(LED_RED, HIGH);
        delay(300);
        digitalWrite(LED_RED, LOW);
        delay(300);
    }
    digitalWrite(LED_RED, HIGH);
}


void flash_green(int count)
{
    for (int i = 0; i < count; i++)
    {
        digitalWrite(LED_GREEN, HIGH);
        delay(300);
        digitalWrite(LED_GREEN, LOW);
        delay(300);
    }
    digitalWrite(LED_GREEN, HIGH);
}
