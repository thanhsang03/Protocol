// slave by GPIO

#define RX_PIN 5
#define RX_INPUT  DDRD &= ~(1 << DDD5)   // pinmode(RX_PIN, INPUT):
#define read_RX()    ( (PIND & (1 << PIND5)) ? HIGH : LOW )  // digitalRead();

int UART_Cycle = 0;

void setup() {
  UART_Begin(9600);
  Serial.begin(9600);

}

char x;
void loop() {
  x = UART_ReadByte();
  Serial.println(x);       // CO CHUA KI TU KET THUC CHUOI XUONG DONG   '\n'...........
  // nen dung serial.print
}


void UART_Begin(int baud)
{
  UART_Cycle = 1.0/baud *1000 *1000;
  RX_INPUT;
}

// LSB first, no Parity, 1 Stop bit, 8bits data
uint8_t UART_ReadByte(void)
{
  uint8_t byte_in = 0;  // 0000.0000
  uint8_t i, res;
  // (1) waiting for start point
  while( read_RX() == HIGH);

  // (2) Read 8 bit data
  delayMicroseconds(1.5*UART_Cycle);
  for(i =0;i<8;i++)
  {
    res = read_RX(); // 1 hoac 0
    res = res << i;
    byte_in = byte_in | res;
    delayMicroseconds(UART_Cycle);
  }

  // (3) read stop bit
  res = read_RX();
  delayMicroseconds(UART_Cycle);  // delay stop bit 1 hoac 2 stop bit  
  if(res == 0)
    return 0;

  return byte_in;
}



