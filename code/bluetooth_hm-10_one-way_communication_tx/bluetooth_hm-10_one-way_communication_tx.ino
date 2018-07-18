// Custom one-way communication with Bluetooth HM-10
// Transmitting data in the form of a struct to receiver
//
// Writes (hardcoded) data to the software UART 
//  and prints the transmitted packet


// Library to make a Software UART
#include <SoftwareSerial.h>

#define RX 3
#define TX 2
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

#define BAUDRATE 9600

// Struct to hold the data we want to transmit
struct Packet {
  byte a;
  int b;
  float c;
  int d;
  
  // signature to minimize errors
//  byte signature;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);  
}
 
void loop() {  
  // Transmit data via bluetooth
  bluetooth_transmit();

  // Print packet (debug)
  print_packet();

  // Necessary forced delay, if we transmit too fast
  //  the error rate will increase sharply
  delay(20);

//  pkt.signature = 0xDEAD;
}


// Function responsible for transmitting data over bluetooth
void bluetooth_transmit() {
  // Update data to be transmitted
  pkt.a = 0;
  pkt.b = 255;
  pkt.c = 888.888;
  pkt.d = -100;
  
  // Write packet data to the bluetooth - and transmit
  BTSerial.write((byte *) & pkt,sizeof(Packet));  
}

// Function to print packet data (debug)
void print_packet() {
  // Print the same string to the Serial Monitor for feedback
  Serial.print("TX: (a,b,c)=(");
  Serial.print(pkt.a); Serial.print(",");
  Serial.print(pkt.b); Serial.print(",");
  Serial.print(pkt.c); Serial.print(",");  
  Serial.print(pkt.d);
  Serial.println(")");
}
