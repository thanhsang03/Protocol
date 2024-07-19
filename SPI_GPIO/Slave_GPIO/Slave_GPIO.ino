#define  SCK_PIN  4
#define  MOSI_PIN 5
#define  MISO_PIN 6
#define  SS_PIN   7

#define SCK_INPUT       DDRD &= ~(1<<DDD4)
#define MOSI_INPUT      DDRD &= ~(1<<DDD5)
#define MISO_OUTPUT     DDRD |= (1<<DDD6)
#define SS_INPUT  DDRD &= ~(1<<DDD7)

#define read_SCK()      ( (PIND & (1<<PD4)) ? HIGH : LOW )
#define read_MOSI()   ( (PIND & (1<<PD5)) ? HIGH : LOW )
#define read_SS()     ( (PIND & (1<<PD7)) ? HIGH : LOW )

#define write_MISO(x)  PORTD = ( (x) ? (PORTD | 1<<PD6) : (PORTD & (~(1<<PD6))) )

void setup() {
  

}

void loop() {
  

}

void SPI_setup(void)
{
  SCK_INPUT;
  MOSI_INPUT;
  MISO_OUTPUT;
  SS_INPUT;
}

uint8_t SPI_transfer(uint8_t byte_out)
{
  uint8_t byte_in = 0; // 0000.0000
  uint8_t ibit, res;

  while( read_SCK() == HIGH);   // start condition
  for(ibit=0x80; ibit>0; ibit=ibit>>1)
  {
    res = (byte_out & ibit);
    write_MISO(res);

    while( read_SCK() == LOW);
    if( read_MOSI() == HIGH)
      byte_in = byte_in | ibit;
    // else
    //   byte_in = byte_in & (~ibit);
    while( read_SCK() == HIGH);   // waiting until SCK get LOW
    // until here. this is the end of the cycle
  }

  return byte_in;
}






