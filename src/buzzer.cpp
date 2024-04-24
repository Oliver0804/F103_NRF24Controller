
#include <Arduino.h>
#include "buzzer.h"
#include "gpio.h"
// Define the GPIO pin where the buzzer is connected

Buzzer::Buzzer()
{
    // Initialize the GPIO pin as an output
    pinMode(BUZZER_PIN, OUTPUT);
    // Make sure the buzzer is off initially
    digitalWrite(BUZZER_PIN, LOW);
}

void Buzzer::play(int duration)
{
    // Set the buzzer pin high to start the sound
    digitalWrite(BUZZER_PIN, HIGH);
    // Keep the buzzer on for the specified duration
    delay(duration);
    // After the duration, turn the buzzer off
    digitalWrite(BUZZER_PIN, LOW);
}

void Buzzer::stop()
{
    // Ensure the buzzer is off
    digitalWrite(BUZZER_PIN, LOW);
}