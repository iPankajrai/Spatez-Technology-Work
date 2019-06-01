
#include "config.h"
#define LED_PIN D1

// this int will hold the current count for our sketch
int count = 0;

// set up the 'digital' feed
AdafruitIO_Feed *LED = io.feed("LED");
// set up the 'counter' feed
AdafruitIO_Feed *Temperature = io.feed("Temperature");

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  LED->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  LED->get();
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // save count to the 'counter' feed on Adafruit IO
  Serial.print("sending -> ");
  
   int x=analogRead(A0);
   int temp1= (x*330)/ 1024;   //330 because the lm35 is connected to 3.3 V pin
   Temperature->save(temp1);
   
   //Serial.println(count);
   //counter->save(count);
   // increment the count by 1
   //count++;

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);

}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");


  digitalWrite(LED_PIN, data->toPinLevel());
}
