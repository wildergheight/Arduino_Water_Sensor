#include <ArduinoJson.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiClient.h>
#include <Pushsafer.h>

// Initialize Wifi connection to the router
char ssid[] = "Scarlet&Gray";     // your network SSID (name)
char password[] = "letsgoBucks"; // your network key
int status = WL_IDLE_STATUS;
int Liquid_level=0;

// Pushsafer private or alias key
#define PushsaferKey "8Q6JBAV3AARS5RNFHd0m"

/*WiFiClientSecure client;*/
WiFiClient client;
Pushsafer pushsafer(PushsaferKey, client);

void setup() {
  Serial.begin(115200);
  pinMode(5,INPUT);
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, password);

    // wait 10 seconds for connection:
    delay(4000);

  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pushsafer.debug = true;

  // Take a look at the Pushsafer.com API at
  // https://www.pushsafer.com/en/pushapi
  
  struct PushSaferInput input;
  input.message = "This is a test message";
  input.title = "Hello!";
  input.sound = "1";
  input.vibration = "1";
  input.icon = "1";
  input.iconcolor = "#FFCCCC";
  input.priority = "1";
  input.device = "a";
  input.url = "https://www.pushsafer.com";
  input.urlTitle = "Open Pushsafer.com";
  input.picture = "";
  input.picture2 = "";
  input.picture3 = "";
  input.time2live = "";
  input.retry = "";
  input.expire = "";
  input.answer = "";

  Serial.println(pushsafer.sendEvent(input));
  Serial.println("Sent");
  
  // client.stop();
}

void loop() {
Liquid_level=digitalRead(5);
Serial.print("Liquid_level= ");
Serial.println(Liquid_level,DEC);
delay(500);
}
