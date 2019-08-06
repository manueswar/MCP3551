
#include<SPI.h>

int cs = 10;
int bitvalue[4];
long bytevalue;
int signBit = 1;
int overFlow = 0;

void setup() {

  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setBitOrder(MSBFIRST);
  Serial.begin(9600);
}

void loop() {
  signBit = 1;
  overFlow = 0;
  digitalWrite(cs, LOW);
  delay(100);
  for (int i = 0; i < 4; i++)
  {
    bitvalue[i] = 0;
    bitvalue[i] = SPI.transfer(0);
  }

  digitalWrite(cs, HIGH);
  bytevalue = 0;
  if (bitvalue[0] & 0x40 | bitvalue[0] & 0x80)
  {
    bitvalue[0] = 0x3F & bitvalue[0];
    overFlow = 1;
    Serial.println("Error");
  }
  else if (bitvalue[0] & 0x20)
  {
    bitvalue[0] = 0x1F & bitvalue[0];
    signBit = -1;
  }
  bytevalue = bitvalue[0];
  bytevalue = (bytevalue << 8) | bitvalue[1];
  bytevalue = (bytevalue << 8) | bitvalue[2];

  bytevalue = (signBit * bytevalue);

  Serial.print(bytevalue*1.192/1000000, 6);

  Serial.println(" Volts");

}
