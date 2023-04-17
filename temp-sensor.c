#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)

#define LCD_ENABLE_PIN PIN_D2
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>

void main()
{
int EOC =0;
long int  hari=0;
float  VOLTAGE=0 , TEMPERATURE=0 ;

   setup_adc_ports(AN0_AN1_AN3);
setup_adc(ADC_CLOCK_INTERNAL);
   lcd_init();

   while(TRUE)
   {
      SET_ADC_CHANNEL(0);
      
      WHILE(!EOC)
      {
      EOC =adc_done();
      }
      hari = read_adc();
      VOLTAGE = hari*0.00488;
      TEMPERATURE = VOLTAGE * 100;
      
      printf(lcd_putc," VOLTage = %F  \n TEMp = %F  ",VOLTAGE,TEMPERATURE);
      delay_ms(200);
      
      if(TEMPERATURE>26)
      {
      output_high(pin_b0);
      output_low(pin_b1);
      }
      else if(TEMPERATURE<24)
      {
      output_low(pin_b0);
      output_high(pin_b1); }
      else 
      {
      output_low(pin_b0);
      output_low(pin_b1); }
      delay_ms(200);

   }

}
