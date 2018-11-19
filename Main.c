#include <16F887.h>
#device adc=10
#include <stdio.h>
#include <string.h>
#fuses HS,nowdt,noprotect
#use delay(clock=8MHz)
#use RS232 (baud=19200, xmit=PIN_C6, rcv=PIN_C7, PARITY=N, BITS=8 )
//#include <flex_lcd.c>
#include <KeyPad.c>
#include <math.h>
#define sample_time 50
#define wait_time  400

char escape;
#INT_RB
void rb_isr(void) { 
   disable_interrupts(INT_RB);
   escape= !input(PIN_B7);
   char c = input_b();
   clear_interrupt(INT_RB);
   enable_interrupts(INT_RB);
}
void clearLCD(void){
   putc(254);
   putc(88);
}
void gotoxy(int row, int col){
   putc(254);
   putc(71);
   putc(row);
   putc(col);
}
void horBar_init(){
   putc(254);
   putc(104);
}
void initVertBar(){
   putc(254);
   putc(115);}

void drawVertBar(int col, int height){
   putc(254);
   putc(61);
   putc(col);
   putc(height);}

void main_menu()
{
   clearLCD();
   printf("Please select");
   printf("\nan option:");
   delay_ms(wait_time) ;
   printf("\n1 - Translate");
   printf("\n2 - Debug ");
   delay_ms(wait_time) ;
}
void boot_screen(){ // Bootscreen animation
   int col, height;
   clearLCD();
   for (int i=0; i<=1; i++){
      gotoxy(2,1);
      for (col=1; col<=20; col++){
         delay_ms(5);
         for (height=1; height<=50; height++){
            drawVertBar(col,height);
            delay_ms(15);
            clearLCD();}
            }}
      clearLCD();
   for (int i=0; i<=5; i++){
      gotoxy(2,1);
      printf("ASL Translator Demo");
      delay_ms(500);
      clearLCD();
      gotoxy(1,3);
      printf("ASL Translator Demo");
      delay_ms(500);
      clearLCD();         
      gotoxy(1,5);
      printf("ASL Translator Demo");
      delay_ms(500);
      clearLCD();
      }
   for (int i=0; i<=1; i++){        
      for (col=1; col<=20; col++){
         delay_ms(5);
         for (height=1; height<=50; height++){
            drawVertBar(col,height);
            delay_ms(15);
            clearLCD();}
      }
   }
}
VOID main()
{
   CHAR k;
   INT16 adc0, adc1, adc2, adc3, adc4;
   port_b_pullups(true);
   delay_us(50);
   char c = input_b();
   clear_interrupt(INT_RB);
   enable_interrupts(INT_RB7);
   enable_interrupts(GLOBAL);
   delay_ms (wait_time);
   setup_adc(adc_clock_internal);
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3|sAN4, VSS_VDD);
   boot_screen();
   WHILE (true)
   {  
      main_menu();
      k = keypad_wait();
      IF (k == '1')
      {
         do {
            clearLCD();
            printf("Translating  B7:Quit");
            delay_ms (wait_time);
            set_adc_channel (0); // Setup AN0 / RA0 //pinky
            delay_us(sample_time);
            adc0 = read_adc();
            set_adc_channel(1); // Setup AN1 / RA1 //ring
            delay_us(sample_time);
            adc1 = read_adc();
            set_adc_channel(2); // Setup AN2 / RA2 //middle
            delay_us(sample_time);
            adc2 = read_adc();
            set_adc_channel(3); // Setup AN3 / RA3 //index
            delay_us(sample_time);
            adc3 = read_adc();
            set_adc_channel(4); // Setup AN4 / RA5 //thumb
            delay_us(sample_time);
            adc4 = read_adc();
            delay_us(sample_time);
            gotoxy(1,2);
            // -------- Hello ------------
            IF (((adc1 >= 470 ) && (adc1 <= 490)) && ( (adc2 >= 540 ) && (adc2 <= 560)) && ((adc3>= 550)&& (adc3 <= 570)) && ((adc4 >= 540 ) && (adc4 <= 550)))
            {
               printf ("Hello");
               delay_ms (wait_time) ;
            }
            // -------- Letter A ----------
            IF ((adc1>=1010) && (adc2>=1010)&& (adc3 >= 680 && adc3<=710) && (adc4>=550 && adc4 <= 580))
            {
               printf("A ");
               delay_ms(wait_time);
            }
            IF ((adc1 >= 470 && adc1 <= 485) && (adc2>=540 && adc2 <= 560) && (adc3 >= 560 && adc3 <= 585) && (adc4>=600 && adc4 <= 620) )
            {
               printf("B ");
               delay_ms(wait_time);
            }
             
            // -------- Letter C ----------
            IF ((adc1>=570 && adc1 <= 600) && (adc2>=640 && adc2 <= 680) && (adc3>=620 && adc3 <= 650) && (adc4>=560 && adc4 <= 58) )
            {
               printf("C ");
               delay_ms(wait_time);
            }   
               
            // -------- Letter D ----------
            IF ((adc1>=1010) && (adc2>=1010) && (adc3>=570 && adc3 <= 590) && (adc4>=537 && adc4 <= 548))
            {
               printf("D ") ;
               delay_ms(wait_time) ;
            }
         }while(!escape);
      }

      IF (k == '2')
      {
         do {
            clearLCD();
            printf("Debugging  B7:Quit");
            delay_ms(wait_time) ;
            //ADXL_data (xLSB, xMSB, yLSB, yMSB, zLSB, zMSB);
            set_adc_channel(0); // Setup AN0 / RA0 // pinky
            delay_us(sample_time);
            adc0 = read_adc();
            gotoxy(1,2);
            printf("A0: %04ld", adc0); //pinky
            delay_ms(wait_time) ;
            set_adc_channel(1); // Setup AN1 / RA1 //ring
            delay_us(sample_time);
            adc1 = read_adc();
            gotoxy (11, 2) ;
            printf("A1: %04ld", adc1); // ring
            delay_ms(wait_time);
            set_adc_channel(2); // Setup AN2 / RA2
            delay_us(sample_time);
            adc2 = read_adc();
            gotoxy(1, 3) ;
            printf("A2: %04ld", adc2); // middle
            delay_ms(wait_time) ;
            set_adc_channel(3); // Setup AN3 / RA3
            delay_us(sample_time);
            adc3 = read_adc();
            gotoxy(11, 3) ;
            printf("A3: %04ld", adc3); // index
            delay_ms(wait_time) ;
            set_adc_channel (4); // Setup AN4 / RA5
            delay_us(sample_time);
            adc4 = read_adc();
            gotoxy(1,4);
            printf("A4: %04ld", adc4); //thumb
            delay_ms(2*wait_time);
         }while(!escape);
      }
   }
}

