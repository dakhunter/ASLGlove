//4x4 Keypad
#define Col1     PIN_D0      // Colomn 1
#define Col2     PIN_D1      // Colomn 2
#define Col3     PIN_D2      // Colomn 3
#define Col4     PIN_D3      // Colomn 4

#define Row1     PIN_D4      // Row 1
#define Row2     PIN_D5      // Row 2
#define Row3     PIN_D6      // Row 3
#define Row4     PIN_D7      // Row 4


//**************************************************************************/

char keypad_read(void) {

   //start the scanning process

   output_high(Row1);      // scan keypress on 1st row: 1, 2, 3, A
   output_low(Row2);
   output_low(Row3);
   output_low(Row4);

   delay_ms(20);

   if (input(Col1) == 1)
      return '1';      // Key '1' is pressed

   else if (input(Col2) == 1)
      return '2';      // Key '2' is pressed

   else if (input(Col3) == 1)
      return '3';      // Key '3' is pressed

   else if (input(Col4) == 1) 
      return 'A';      // Key 'A' is pressed, we will store as 10

   output_low(Row1);      // scan keypress on 2nd row: 4, 5, 6, B
   output_high(Row2);
   output_low(Row3);
   output_low(Row4);

   delay_ms(20);

   if (input(Col1) == 1)   
      return '4';      // Key '4' is pressed

   else if (input(Col2) == 1) 
      return '5';      // Key '5' is pressed

   else if (input(Col3) == 1) 
      return '6';      // Key '6' is pressed

   else if (input(Col4) == 1)
      return 'B';      // Key 'B' is pressed, we will store as 11



   output_low(Row1);      // scan keypress on 3rd row: 7, 8, 9, C
   output_low(Row2);
   output_high(Row3);
   output_low(Row4);

   delay_ms(20);

   if (input(Col1) == 1)   
      return '7';      // Key '7' is pressed

   else if (input(Col2) == 1) 
      return '8';      // Key '8' is pressed

   else if (input(Col3) == 1) 
      return '9';      // Key '9' is pressed

   else if (input(Col4) == 1) 
      return 'C';      // Key 'C' is pressed, we will store as 12



   output_low(Row1);      // scan keypress on 4th row: *, 0, #, D
   output_low(Row2);
   output_low(Row3);
   output_high(Row4); //

   delay_ms(20);

   if (input(Col1) == 1)
      return '*';      // Key '*' is pressed, we will store as 14

   else if (input(Col2) == 1) 
      return '0';      // Key '0' is pressed

   else if (input(Col3) == 1) 
      return '#';      // Key '#' is pressed, we will store as 15

   else if (input(Col4) == 1) 
      return 'D';      // Key 'D' is pressed, we will store as 13



   return 0xFF;               // if no key press, the register is 0xFF

}

char keypad_wait(void) {

   // The pressed key.
   char c_pressed_key = 0xFF;   
   
   // Wait until the key is pressed.
   do {
      c_pressed_key = keypad_read();
   }   
   while (c_pressed_key == 0xFF);
   return c_pressed_key;
   delay_ms(50);
   
   // Wait until the key is released.
   while (keypad_read() != 0xFF){}
   
   return c_pressed_key;
}   









