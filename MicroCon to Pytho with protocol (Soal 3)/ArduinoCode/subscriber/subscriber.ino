#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "RobotikID";
const char *password = "123456789";

// MQTT Broker
const char *mqtt_broker = "free.mqtt.iyoti.id";
const char *topic_pub = "robotikid/pub";
const char *topic_sub = "robotikid/sub";
//const char *mqtt_username = "RobotikID";
//const char *mqtt_password = "1234567";
const int mqtt_port = 1883;
String client_id = "RobotikID";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
   Serial.begin(115200);
  
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.println("Menghubungkan ke WiFi..");
   }
   Serial.println("Terhubung ke WiFi");

   //Menghubungkan ke mqtt broker
   client.setServer(mqtt_broker, mqtt_port);
   client.setCallback(callback);
   while (!client.connected()) {
       if (client.connect(client_id.c_str())) {
           Serial.println("Terhubung ke mqtt broker");
       } else {
           Serial.print("Gagal Terhubung ");
           Serial.print(client.state());
           delay(2000);
       }
   }
   
   // publish and subscribe
   client.publish(topic_pub, "Hi, ESP32");
   client.subscribe(topic_sub);   
}

void callback(char *topic, byte *payload, unsigned int length) {
   Serial.print("Dari Topik: ");
   Serial.println(topic);
   Serial.print("Pesannya:");
   for (int i = 0; i < length; i++) {
       Serial.print((char) payload[i]);
   }
   Serial.println();
}

void loop() {
 client.loop();
}