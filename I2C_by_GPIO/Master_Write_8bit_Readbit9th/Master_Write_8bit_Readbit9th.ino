// Master  Write 8bit

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
  SDA_HIGH;
  SCL_HIGH;
  SCL_OUTPUT;
  SDA_OUTPUT;
  delay(1000);
  begin_I2C(0);

}

void loop() {
  // PORTD |= (1<<PD3);
  // delayMicroseconds(10);
  // PORTD &= ~(1<<PD3);
  // delayMicroseconds(10);

  delay(100);

}

void begin_I2C(byte address)
{
  // address = 0x55;
  SDA_LOW; delayMicroseconds(5); // START
  SCL_LOW; delayMicroseconds(5);

  SCL_LOW;  SDA_HIGH; delayMicroseconds(5); // CLOCK 1
  SCL_HIGH; delayMicroseconds(5); 

  SCL_LOW;  SDA_LOW; delayMicroseconds(5);  // CLOCK 2
  SCL_HIGH; delayMicroseconds(5); 



  // CLOCK 9 - kiem tra truyen nhan du lieu   // ACK(0)/ NACK(1)
  SCL_LOW;
  SDA_INPUT;  // PULLUP RES WILL BRIGH SDA LINE TO HIGH -> cau hinh input de doc bit phan hoi ACK/NACK
  // SDA_HIGH;   // FORCE HIGH(NACK)
  delayMicroseconds(5); 
  SCL_HIGH;
  uint8_t ACK = (PIND & (1 << PIND4)) >> PIND4; // tra ve 0 hoac 1 (bit LSB)
  delayMicroseconds(5); 

  // stop (P)
  SCL_LOW;  delayMicroseconds(10); 
  SDA_OUTPUT;  // tra ve trang thai output
  SDA_LOW;  delayMicroseconds(5); 
  SCL_HIGH;  delayMicroseconds(5); 
  SDA_HIGH;

}



