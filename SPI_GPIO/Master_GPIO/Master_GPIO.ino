#define  SCK_PIN  4
#define  MOSI_PIN 5
#define  MISO_PIN 6
#define  SS_PIN   7

#define SCK_OUTPUT      DDRD |= (1<<DDD4)
#define MOSI_OUTPUT     DDRD |= (1<<DDD5)
#define MISO_INPUT      DDRD &= ~(1<<DDD6)
#define SS_OUTPUT       DDRD |= (1<<DDD7)

#define MOSI_HIGH PORTD |= (1<<PD5)
#define MOSI_LOW  PORTD &= ~(1<<PD5)

#define write_MOSI(x)  PORTD = ( (x) ? (PORTD | 1<<PD5) : (PORTD & (~(1<<PD5))) )
#define write_SS(x)    PORTD = ( (x) ? (PORTD | 1<<PD7) : (PORTD & (~(1<<PD7))) )
#define write_SCK(x)   PORTD = ( (x) ? (PORTD | 1<<PD4) : (PORTD & (~(1<<PD4))) )

#define read_MISO()    ( (PIND & (1<<PD6)) ? HIGH : LOW )

// SPI speed
// Slow_01: f = 20Khz -> T = 50us
#define tFULL  50
#define tHALF tFULL/2

void setup() {
  

}

void loop() {
  

}

// CPOL = 0   CPHA = 0
void SPI_setup(void)
{
  MOSI_OUTPUT;
  MISO_INPUT;
  write_SCK(LOW);
  SCK_OUTPUT;
  write_SS(HIGH);
  SS_OUTPUT;
  delay(1);
}

void SPI_begin(void)
{
  write_SS(LOW);   // change when using mode: 1 master many slave for choosing another SLAVE----
}

void SPI_end(void)
{
  write_SCK(LOW);
  write_SS(HIGH);
}

// MODE 0
// bit Order = MSB
uint8_t SPI_trnsfer(uint8_t byte_out)
{
  uint8_t byte_in = 0;
  uint8_t ibit;
  uint8_t res;

  for(ibit=0x80; ibit >0; ibit = ibit >> 1)
  {
    // day data ngay lap tuc khi SS xuong muc thap
    res = byte_out & ibit;   // tra ve 1 (hoac khac o) or 0  => xuat tung bit trong byte
    write_MOSI(res);

    delayMicroseconds(tHALF);
    write_SCK(HIGH);

    // doc data MISO tai thoi diem on dinh nhat
    if(read_MISO() == HIGH)
    {
      byte_in = byte_in | ibit;
    } // truong hop muc thap da la 0 do da khoi tao ban dau

    delayMicroseconds(tHALF);
    write_SCK(LOW); // end CLOCK

  }

  return byte_in;

}



