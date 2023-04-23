#include <Arduino.h>
#include <EtherCard.h>

/**
 * Arduino Ethernet connection using EtherCard
 */

// ethernet interface mac address
static byte mymac[] = {0x74, 0x69, 0x69, 0x2D, 0x30, 0x31};
// ethernet interface ip address
static byte myip[] = {10, 0, 0, 222};
// ethernet interface ip netmask
static byte mask[] = {255, 255, 255, 0};
// gateway ip address
static byte gwip[] = {10, 0, 0, 254};
// dns ip address
static byte dnsip[] = {10, 0, 0, 254};

byte Ethernet::buffer[1024];

void udpSerialPrint(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len) {
    Serial.print("dest_port: ");
    Serial.println(dest_port);
    Serial.print("src_port: ");
    Serial.println(src_port);

    Serial.print("src_ip: ");
    ether.printIp(src_ip);
    Serial.println("\ndata: ");
    while (*data != NULL && *data != '\EOF' && *data != '\n') {
      Serial.print(*data++);
    }
    Serial.println();
}

void setup() {
  Serial.begin(9600);
  Serial.println("\n[Static IP]");

  if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0)
    Serial.println("Failed to access Ethernet controller");

  ether.staticSetup(myip, gwip, dnsip, mask);

  ether.printIp("My IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);

  ether.udpServerListenOnPort(&udpSerialPrint, 6666);
}

void loop() {
  ether.packetLoop(ether.packetReceive());
}
