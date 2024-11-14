// Program to make alphabetical keypad similar to the one in mobiles
#include<reg51.h>
sbit col1=P1^4;
sbit col2=P1^5;
sbit col3=P1^6;
sbit row1=P1^0;
sbit row2=P1^1;		   //Define Pins For Keypad
sbit row3=P1^2;
sbit row4=P1^3;
sfr ldata =0xA0;	   //Data port for LCD
sbit rs = P3^5;
sbit rw = P3^6;
sbit en = P3^7;
unsigned char chk_agn[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char pos = 128, c = 0;
sbit clearScreenButton = P3^2;
sbit backspaceButton = P3^3;
unsigned char currentLine = 1;


void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void delay(unsigned int itime);
void display(unsigned char a, unsigned char b);
void clearScreenISR(void);
void backspaceISR(void);
void setupInterrupts(void);
void clearScreen(void);



void clearScreenISR(void) interrupt 0 {
    // Clear screen and move cursor to the beginning of the first line
    lcdcmd(0x01);
    delay(10);
	  pos=128;
	  c=0;
    lcdcmd(pos);
}

void backspaceISR(void) interrupt 2 {
    // Handle backspace (clear last previous character)
    if (c > 0) {
        c--;
        lcdcmd(pos + c);
        lcddata(' ');
        delay(10);
        lcdcmd(pos + c);
    } else if (pos + c == pos) {
        // Cursor is at the start of the second line
        c = 16;  // Move to the last character of the first line
			lcdcmd(0x80);
			pos=128;
      lcdcmd(pos + c);
			currentLine=1;
    }
}


void setupInterrupts(void) {
    // Enable the internal pull-up resistor for INT0 (pin 3.2)
    PCON |= 0x80;

    // Configure INT0 (clear screen button) and INT1 (backspace button) interrupts
    IT0 = IT1 = EX0 = EX1 = 1;  // Falling edge triggered
    EA = 1;  // Enable global interrupts
}

void main() {
    unsigned char j, d;

    lcdcmd(0x38);
    delay(10);
    lcdcmd(0x0F);
    delay(10);
    lcdcmd(pos);

    col1 = col2 = col3 = 1;
	
	//setupInternalPullUps();
	setupInterrupts();

    while (1) {
        do {
            row1 = row2 = row3 = row4 = 0;
        } while (col1 == 0 || col2 == 0 || col3 == 0);

        while (1) {
            row2 = row3 = row4 = 1;
            row1 = 0;

            if (col1 == 0 || col2 == 0 || col3 == 0) {
                j = 0;
                if (col1 == 0) {
                    chk_agn[1]++;
                    display(1, chk_agn[1]);
                } else if (col2 == 0) {
                    chk_agn[2]++;
                    display(2, chk_agn[2]);
                } else if (col3 == 0) {
                    chk_agn[3]++;
                    display(3, chk_agn[3]);
                }
                break;
            }

            row1 = row3 = row4 = 1;
            row2 = 0;

            if (col1 == 0 || col2 == 0 || col3 == 0) {
                j = 1;
                if (col1 == 0) {
                    chk_agn[4]++;
                    display(4, chk_agn[4]);
                } else if (col2 == 0) {
                    chk_agn[5]++;
                    display(5, chk_agn[5]);
                } else if (col3 == 0) {
                    chk_agn[6]++;
                    display(6, chk_agn[6]);
                }
                break;
            }

            row1 = row2 = row4 = 1;
            row3 = 0;

            if (col1 == 0 || col2 == 0 || col3 == 0) {
                j = 2;
                if (col1 == 0) {
                    chk_agn[7]++;
                    display(7, chk_agn[7]);
                } else if (col2 == 0) {
                    chk_agn[8]++;
                    display(8, chk_agn[8]);
                } else if (col3 == 0) {
                    chk_agn[9]++;
                    display(9, chk_agn[9]);
                }
                break;
            }

            row1 = row2 = row3 = 1;
            row4 = 0;

            if (col1 == 0 || col2 == 0 || col3 == 0) {
                j = 3;
                if (col1 == 0) {
                    pos++;
                    lcdcmd(pos + c);
                } else if (col2 == 0) {
                    chk_agn[0]++;
                    display(0, chk_agn[0]);
                } else if (col3 == 0) {
									pos=0xC0;
									lcdcmd(0xC0);
									currentLine=2;
									c=0;
                }
                break;
            }
        }
				// Check if the current line is filled and move to the next line
		if (c >= 16) {
				if (currentLine == 1) {
						currentLine = 2;
						pos = 0xC0;  // Set position to the start of the second line
						lcdcmd(pos);
				} else {
						// If both lines are filled, clear the display
						clearScreen();
						currentLine = 1;
						pos = 128;  // Set position to the start of the first line
						lcdcmd(pos);
				}
				c = 0;  // Reset the character count for the new line
		}
    }
}

void num_check(unsigned char a) {
    unsigned char j;
    c++; // Increment cursor position here

    for (j = 0; j < 10; j++) {
        if (j != a)
            chk_agn[j] = 0;
    }
    if (chk_agn[a] == 4) {
        c--;
        chk_agn[a] = 0;
    }
}


void repeat(unsigned char a) {
    if (chk_agn[a] > 1)
        c--;
    lcdcmd(pos + c);
}
void display(unsigned char a ,unsigned char b) 	 // Display function
{
switch(b)
{
  case 1:
   {
    switch(a)
    {
     case 1:{
       repeat(1);
       lcddata('a');
       delay(4);
       num_check(1);
       break;
       }
     case 2:{
       repeat(2);
	   lcddata('d');
       delay(4);
       num_check(2);
       break;
       }
     case 3: {
       repeat(3);
       lcddata('g');
       delay(4);
       num_check(3);
       break;
       }
     case 4:{
       repeat(4);
       lcddata('j');
       delay(4);
       num_check(4);
       break;
       }
     case 5:{
       repeat(5);
       lcddata('m');
       delay(4);
       num_check(5);
       break;
       }
     case 6:{
       repeat(6);
       lcddata('p');
       delay(4);
       num_check(6);
       break;
       }
     case 7:{
       repeat(7);
       lcddata('s');
       delay(4);
       num_check(7);
       break;
       }
     case 8:{
       repeat(8);
       lcddata('v');
       delay(4);
       num_check(8);
       break;
       }
     case 9:{
       repeat(9); 
       lcddata('y');
       delay(4);
       num_check(9);
       break;
       }
     case 0:{ 
       repeat(0);
       lcddata(' ');
       delay(4);
       num_check(0);
       break;
       }
    }
   break;
   }
  case 2:
   {
    switch(a)
     {
     case 1:{
       repeat(1);
       lcddata('b');
       delay(4);
       num_check(1);
       break;
       }
     case 2:{
       repeat(2);
       lcddata('e');
       delay(4);
       num_check(2);
       break;
       }
     case 3: {
       repeat(3);
       lcddata('h');
       delay(4);
       num_check(3);
       break;
       }
     case 4:{
       repeat(4);
       lcddata('k');
       delay(4);
       num_check(4);
       break;
       }
     case 5:{
       repeat(5);
       lcddata('n');
       delay(4);
       num_check(5);
       break;
       }
     case 6:{
       repeat(6);
       lcddata('q');
       delay(4);
       num_check(6);
       break;
       }
     case 7:{
       repeat(7);
       lcddata('t');
       delay(4);
       num_check(7);
       break;
       }
     case 8:{
       repeat(8);
       lcddata('w');
       delay(4);
       num_check(8);
       break;
       }
     case 9:{
       repeat(9); 
       lcddata('z');
       delay(4);
       num_check(9);
       break;
       }
     case 0:{
	   repeat(0);
       lcddata('0');
       delay(4);
	   num_check(0);
       break;
       }
     }
    break;
   }
  case 3:
   {
    switch(a)
     {
     case 1:{
       repeat(1);
       lcddata('c');
       delay(4);
       num_check(1);
       break;
       }
     case 2:{
       repeat(2);
       lcddata('f');
       delay(4);
       num_check(2);
       break;
       }
     case 3: {
       repeat(3);
       lcddata('i');
       delay(4);
       num_check(3);
       break;
       }
     case 4:{
       repeat(4);
       lcddata('l');
       delay(4);
       num_check(4);
       break;
       }
     case 5:{
       repeat(5);
       lcddata('o');
       delay(4);
       num_check(5);
       break;
       }
     case 6:{
       repeat(6);
       lcddata('r');
       delay(4);
       num_check(6);
       break;
       }
     case 7:{
       repeat(7);
       lcddata('u');
       delay(4);
       num_check(7);
       break;
       }
     case 8:{
       repeat(8);
       lcddata('x');
       delay(4);
       num_check(8);
       break;
       }
     case 9:{
       repeat(9); 
       lcddata('9');
       delay(4);
       num_check(9);
       break;
       }
     case 0:{
	   repeat(0);
       lcddata(' ');
			 delay(4);
       num_check(0);
       break;
       }
	  }
	break;
     }
  case 4:
   {
    switch(a)
     {
     case 1:{
       repeat(1);
       lcddata('1');
       delay(4);
       num_check(1);
       break;
       }
     case 2:{
       repeat(2);
       lcddata('2');
       delay(4);
       num_check(2);
       break;
       }
     case 3: {
       repeat(3);
       lcddata('3');
       delay(4);
       num_check(3);
       break;
       }
     case 4:{
       repeat(4);
       lcddata('4');
       delay(4);
       num_check(4);
       break;
       }
     case 5:{
       repeat(5);
       lcddata('5');
       delay(4);
       num_check(5);
       break;
       }
     case 6:{
       repeat(6);
       lcddata('6');
       delay(4);
       num_check(6);
       break;
       }
     case 7:{
       repeat(7);
       lcddata('7');
       delay(4);
       num_check(7);
       break;
       }
     case 8:{
       repeat(8);
       lcddata('8');
       delay(4);
       num_check(8);
       break;
       }
		      case 9:{
       repeat(9); 
       lcddata('9');
       delay(4);
       num_check(9);
       break;
       }
     case 0:{
	   repeat(0);
       lcddata('0');
			 delay(4);
       num_check(0);
       break;
       }
     }          
   break;
   }
}}

void lcdcmd (unsigned char value)	//Function to send command to LCD
{
ldata =value;
rs=0;
rw=0;
en=1;
delay (1);
en=0;
}

void lcddata (unsigned char value)	//Funtion to send data on LCD
{
ldata =value;
rs=1;
rw=0;
en=1;
delay(1);
en=0;
}

void delay (unsigned char itime)	//Time delay function
{
unsigned int i,j;
    for(i=0;i<itime;i++)
	for(j=0;j<1275;j++);
}

void clearScreen(void) {
    // Clear screen and move cursor to the beginning of the first line
    lcdcmd(0x01);
    delay(10);
	  pos=128;
	  c=0;
    lcdcmd(pos);
}