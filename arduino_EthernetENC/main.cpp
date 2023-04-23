#include <Arduino.h>
#include <EthernetENC.h>

/**
 * Ethernet Shield using EthernetENC lib
 */

// Ethernet Configuration
EthernetClient etherClient;
static byte mac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};
IPAddress ip(10, 0, 0, 222);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(10, 0, 0, 254);
IPAddress dns_ip(9, 9, 9, 9);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dns_ip, gateway, subnet);
  delay(500);
  Serial.print("Connected, IP: ");
  Serial.println(Ethernet.localIP());
  Serial.println(Ethernet.gatewayIP());
  Serial.println();
  delay(1000);  // wait for network connection
}

void loop() {}
