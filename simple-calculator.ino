#include <LiquidCrystal.h>
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5,  1,  0}; //connect to the column  pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 
ROWS, COLS );

String text="";
int ctr=1;
int num1,num2,answer;

bool reset=false;
bool allowOperation = false;
int seconds = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16, 2); // Set up the number of columns and rows on the LCD.
  lcd.print("Enter 1st No.");  
  lcd.blink();
  lcd.setCursor(0,1);
}

void loop()
{
 char key = keypad.getKey();
  
 if (key != NO_KEY)
 {
       //allow 0 to 9 only
    if (key<='9' && key>='0' && reset==false)
    {
       text=text+key;
       lcd.print(key);
    } 
    
    if (key=='#')//Enter Key
    {

      switch(ctr)
      {
        case 1: 
          num1=text.toFloat(); 
          ctr++;
          text="";
          lcd.clear();
          lcd.print("Enter 2nd No.");
          lcd.setCursor(0,1);
          lcd.blink(); 
          break;

        case 2: 
          num2=text.toFloat();
          ctr++;
          text="";
        
          lcd.clear();
          lcd.print("Operation:");
          lcd.noBlink();
          lcd.setCursor(0,1);
          lcd.print("A=+,B=-,C=*,D=/"); 
          allowOperation = true;
          break;
      } 
    } 
   
   if (allowOperation == true) // For operations
   {
     switch(key)
     {
       case 'A':
         answer=num1+num2;
       	 text="";
         text=text+num1+"+"+num2+"="; 
         reset=true;
       	 displayAnswer(text, answer);
       	 break;
       
       case 'B':
         answer=num1-num2;
       	 text="";
         text=text+num1+"-"+num2+"="; 
         reset=true;
       	 displayAnswer(text, answer);
       	 break;
       
       case 'C':
         answer=num1*num2;
       	 text="";
         text=text+num1+"*"+num2+"="; 
         reset=true;
       	 displayAnswer(text, answer);
       	 break;
       
       case 'D':
         answer=num1/num2;
       	 text="";
         text=text+num1+"/"+num2+"="; 
         reset=true;
         if (num2==0)
         {
		   lcd.clear();
           lcd.print(text);
           lcd.print("Error"); 
           lcd.noBlink();
           lcd.setCursor(0,1);
           lcd.print("Press * to reset");
         }
         else
         {
           displayAnswer(text, answer);
         }
       	 break;
     }
     
   }

  if (key=='*') //Reset Key
  {

    text="";
    ctr=1;
    num1=0;
    num2=0;
    answer=0;
    reset=false;
    allowOperation = false;
    lcd.clear();
    lcd.print("Enter 1st No.");
    lcd.blink();
    lcd.setCursor(0,1);
  }
    
  }
}

// Function for displaying the answer
void displayAnswer(String text, float answer){
     lcd.clear();
     lcd.print(text);
     lcd.print(answer,2); 
     lcd.noBlink();
     lcd.setCursor(0,1);
     lcd.print("Press * to reset");
}
