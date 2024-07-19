// Master  Write 8bit
// try: 20Khz ~ T = 50us

#include <Wire.h>

#define tFULL 10
#define tHALF tFULL/2
#define SCL_PIN 3
#define SDA_PIN 4

#define SDA_OUTPUT DDRD |= (1<<DDB4);
#define SCL_OUTPUT DDRD |= (1<<DDB3);

#define SDA_INPUT DDRD &= ~(1<<DDB4);
#define SCL_INPUT DDRD &= ~(1<<DDB3);

#define SDA_HIGH PORTD |= (1<<PD4);  // SDA = 1
#define SCL_HIGH PORTD |= (1<<PD3);  // SLC = 1
#define SDA_LOW PORTD &= ~(1<<PD4);  
#define SCL_LOW PORTD &= ~(1<<PD3);


// tan so xung mac dinh i2c la 100.000 hz
void setup() {
  // Wire.begin();
  // delay(100);
  // Wire.beginTransmission(0x55);
  // Wire.write('a');
  // Wire.endTransmission();
  // delay(100);

  // cau hinh master tao xung clock output
  // IDLE state--------------- cho len muc cao truoc sau do moi cau hunh output de tranh bi loi
  delay(100);
}

void loop() {
  // PORTD |= (1<<PD3);
  // delayMicroseconds(10);
  // PORTD &= ~(1<<PD3);
  // delayMicroseconds(10);
  uint8_t ack;
  ack = I2C_WriteByte(0x55);    // 0x55 +0 (write) = 1010.1010
  delay(100);


}

uint8_t I2C_WriteByte(byte data)
{
  int i;
  // IDLE Condition      // address = 0x55;
  SDA_HIGH;     // dam bao trang thai IDLE de begin mot write I2C
  SCL_HIGH;     // dam bao trang thai IDLE de begin mot write I2C
  SCL_OUTPUT;   // dam bao trang thai IDLE de begin mot write I2C
  SDA_OUTPUT;   // dam bao trang thai IDLE de begin mot write I2C
  delayMicroseconds(tFULL); 
  // START
  SDA_LOW; delayMicroseconds(tHALF); 
  SCL_LOW; delayMicroseconds(tHALF);

  // CLOCK X-------------------X: 1 - 8
  for( i =0; i<8; i++)
  {
    if( (data & 0x80) != 0)
      {SDA_HIGH;}
    else
      SDA_LOW;
    data = data << 1;
    delayMicroseconds(tHALF); 
    SCL_HIGH;
    delayMicroseconds(tHALF); 
    SCL_LOW;
  }

  // -----CLOCK 9 ------ kiem tra truyen nhan du lieu   // ACK(0)/ NACK(1)
  // READ ACK/NACK
  SDA_INPUT;  // PULLUP RES WILL BRIGH SDA LINE TO HIGH -> cau hinh input de doc bit phan hoi ACK/NACK
  // SDA_HIGH;   // FORCE HIGH(NACK)
  delayMicroseconds(tHALF); 
  SCL_HIGH;
  delayMicroseconds(tHALF); 
  uint8_t ACK = (PIND & (1 << PIND4)) >> PIND4; // tra ve 0 hoac 1 (bit LSB)
  SCL_LOW;  

  // stop (P)
  //delayMicroseconds(tFULL); 
  SDA_OUTPUT;  // tra ve trang thai output
  SDA_LOW;  delayMicroseconds(tHALF); 
  SCL_HIGH;  delayMicroseconds(tHALF); 
  SDA_HIGH;

  return ACK;
}



