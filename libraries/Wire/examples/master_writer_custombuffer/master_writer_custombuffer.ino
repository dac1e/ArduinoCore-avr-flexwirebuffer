// Wire Master Writer Custom Buffer

// Demonstrates use of the Wire library with customized buffers
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver Custom Buffer" example for use with this

// Created 31 Dec 2024

// This example code is in the public domain.


#include <Wire.h>
#include <TwoWireBuffers.h>
#include "Arduino.h"

// The following text will not fit into the default buffer of 32 bytes.
static const char text[] = "You really won't believe it, but x is ";

constexpr size_t RECEIVE_BUFFER_SIZE  = 0;  // There is no receive in this sketch.
constexpr size_t TRANSMIT_BUFFER_SIZE = 42; // Enhance the buffer to 42 characters.

SET_Wire_BUFFERS(RECEIVE_BUFFER_SIZE, TRANSMIT_BUFFER_SIZE,
    true /* master buffers needed */, false /* no slave buffers needed */ );

void setup() {
  Wire.begin(); // join I2C bus (address optional for master)

  // This is just for curiosity and could be removed
  Serial.begin(9600);   // start serial for output
  printWireBuffersCapacity(Serial);
}

static byte x = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(text);          // sends multiple bytes
  Wire.write(x);             // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}

void printWireBuffersCapacity(Stream& stream) {
  const auto& buffers = GET_Wire_BUFFERS();

  stream.print("Wire transmit buffer size is ");
  stream.println(buffers.txWireBufferCapacity());

  stream.print("Wire receive buffer size is ");
  stream.println(buffers.rxWireBufferCapacity());

  stream.print("twi_masterBuffer size is ");
  stream.println(buffers.twi_masterBufferCapacity());

  stream.print("twi_rxBuffer size is ");
  stream.println(buffers.twi_rxBufferCapacity());

  stream.print("twi_txBuffer size is ");
  stream.println(buffers.twi_txBufferCapacity());
}
