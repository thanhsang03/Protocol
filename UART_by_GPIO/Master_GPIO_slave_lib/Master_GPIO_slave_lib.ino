// UARRT BAUD: 9600, 115200.... bits/s (f)

#define TX_PIN 4

#define TX_OUTPUT DDRD |= (1<<DDD4)      // pinMode(TX_PIN,OUTPUT);

// x=LOW=FALSE=0
// x=HIGH...
#define write_TX(x) PORTD = ( (x) ? (PORTD |= 1 << PD4) : (PORTD & (~(1 << PD4))) )      // digitalWrite(...)

unsigned int UART_Cycle = 0;   // T = 1/f


void setup() {
  UART_Begin(9600);
  delay(100);
  

}

char x ='a';
void loop() {
  UART_WriteByte(x);
  x++;
  delay(1000);
}

void UART_Begin(unsigned int baudrate)
{
  UART_Cycle = 1.0/baudrate * 1000 *1000;  // giay s chuyen sang us
  write_TX(HIGH);   // set IDLE state
  TX_OUTPUT;        // set IDLE state
}

// LSB first, No Parity, 1 bit Stop
// uint8_t = unsigned char
// shiftRight1bit
void UART_WriteByte(uint8_t byte_out)
{
  int i, b;
  // (1) Send START Bit
  write_TX(LOW);
  delayMicroseconds(UART_Cycle);

  // (2) Send 8bits data   LSB MSB
  for(i=0;i<8;i++)
  {
    b = byte_out & 0x01;
    write_TX(b);
    byte_out = byte_out >> 1;
    delayMicroseconds(UART_Cycle);
  }

  // (3) Send Stop bit
  write_TX(HIGH);
  delayMicroseconds(UART_Cycle);

  // (4) Comback to IDLE state
  write_TX(HIGH);   // redundant
}





