#define lcd 0xff00
  #define rs 1<<16 
  #define E 1<<17   
  void lcd_init(void);
  void lcd_cmd(unsigned char);
  void lcd_data(unsigned char);
  void delay_ms(unsigned int);
  void lcd_string(unsigned char*);
  void lcd_init(void)
  {
  IODIR0|=lcd|rs|E;
  lcd_cmd(0x01);
  lcd_cmd(0x02);
  lcd_cmd(0x0c);
  lcd_cmd(0x38);
  }
  void lcd_cmd(unsigned char cmd)
  {
  IOCLR0=lcd;
  IOSET0=(cmd<<8);
  IOCLR0=rs;
  IOSET0=E;
  delay_ms(2);
  IOCLR0=E;
  }
  void lcd_data(unsigned char d)
  {
  IOCLR0=lcd;
  IOSET0=(d<<8);
  IOSET0=rs;
  IOSET0=E;
  delay_ms(2);
  IOCLR0=E;
  }
  void delay_ms(unsigned int ms)
  {
  T0PR=15000-1;
  T0TCR=0x01;
  while(T0TC<ms);
  T0TCR=0x03;
  T0TCR=0X00;
  }  
  void lcd_string(unsigned char *s)
  {
   while(*s)
   lcd_data(*s++);
  }
