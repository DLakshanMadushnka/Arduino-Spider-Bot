#include <SpiderBot.h>

SpiderBot bot(9, 10);  // Trig, Echo pins

void setup() {
  Serial.begin(9600);
  bot.initServos();
}

void loop() {
  if (!bot.detectObstacle()) {
    bot.tripodGait(1.0);  // Forward gait
  } else {
    bot.tripodGait(-1.0);  // Backward
  }
  bot.gestureControl();
  delay(50);
}
