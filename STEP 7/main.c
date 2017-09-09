////////////////////////////////////////////////////////////////////////////////
// ECE 2534:        LAB 4
//
// File name:       HarounAnsari_Lab4 
//
// Description:     Drum Hero
//
// How to use:      
//Navigate through the menu via the buttons, a secret god mode is
//described in the word document. You then choose the difficulty and then head into
//the game. You can then play the game through the right and left twist. I did not 
//get the double tap working, so this action was supplanted through pressing button
//2. The arrows act as the notes and the white block acts as the score zone. Activate the
//appropriate action in order to score points. Score as many points as you can before
//the game ends, after a minute. Once the game ends you will be taken to a menu with your
//score. After that you are taken back to the difficulty menu.
//                  
//                  
//Further clarification is given in the word document.
//
//
// Written by:      Haroun Ansari
// Last modified:   5 December 2016

#include <stdio.h> 
#include <plib.h>
#include "PmodOLED.h"
#include "OledChar.h"
#include "OledGrph.h"
#include "delay.h"
#include "myDebug.h"
#include "myBoardConfigFall2016.h"

int y_prev = 0; // right twist
int y_prev_l = 0; // left twist

    int rightTwist(int y)
    {
        
        int current = y; //read y-axis
        if (current == y_prev) return 0; // no change
        DelayMs (1) ; //delays 1 ms is how debouncing works
        current = y; //reads y-axis again
        if (current == y_prev) return 0; // way to clarify debounce
        
        y_prev = current; // allows to loop
        
        if (current == 1) return 1; // rising edge from off to on
        return 0;
    }
    
        int leftTwist(int y2)
    {
        
        int current = y2; //read y-axis
        if (current == y_prev_l) return 0; // no change
        DelayMs (1) ; //delays 1 ms is how debouncing works
        current = y2; //reads y-axis again
        if (current == y_prev_l) return 0; // way to clarify debounce
        
        y_prev_l = current; // allows to loop
        
        if (current == -1) return 1; // rising edge from off to on
        return 0;
    }



void initSPI(SpiChannel chn)
{   
    unsigned int SOURCE_CLK_DIV = 10;
    
    SpiChnOpen(chn,
            SPI_OPEN_MSTEN
            | SPI_OPEN_MSSEN
            | SPI_OPEN_CKP_HIGH
            | SPI_OPEN_MODE8
            | SPI_OPEN_ENHBUF
            | SPI_OPEN_ON,
            SOURCE_CLK_DIV);
}

// Comment this define out to *not* use the OledDrawGlyph() function
#define USE_OLED_DRAW_GLYPH
#define BUTTON1 1<<6
#define BUTTON2 1<<7
#ifdef USE_OLED_DRAW_GLYPH
// forward declaration of OledDrawGlyph() to satisfy the compiler
void OledDrawGlyph(char ch);
#endif

// Global variable to count number of times in timer2 ISR
//volatile unsigned int timer2_ms_value = 0;

// Return value check macro
#define CHECK_RET_VALUE(a) { \
  if (a == 0) { \
    LATGSET = 0xF << 12; \
    return(EXIT_FAILURE) ; \
  } \
}

// Use preprocessor definitions for program constants
// The use of these definitions makes your code more readable!

#define NUMBER_OF_MILLISECONDS_PER_OLED_UPDATE 100
#define LED_MASK 0xf000

// Global variable to count number of times in timer2 ISR
volatile unsigned int timer2_ms_value = 0;


// The interrupt handler for timer2
// IPL4 medium interrupt priority
// SOFT|AUTO|SRS refers to the shadow register use
void __ISR(_TIMER_2_VECTOR, IPL4AUTO) _Timer2Handler(void) {
    DBG_ON(MASK_DBG0);
    timer2_ms_value++; // Increment the millisecond counter.
    DBG_OFF(MASK_DBG0);
    INTClearFlag(INT_T2); // Acknowledge the interrupt source by clearing its flag.
}

// Initialize timer2 and set up the interrupts

void initTimer2() {
    // Configure Timer 2 to request a real-time interrupt once per millisecond.
    // The period of Timer 2 is (16 * 625)/(10 MHz) = 1 s.
    OpenTimer2(T2_ON | T2_IDLE_CON | T2_SOURCE_INT | T2_PS_1_16 | T2_GATE_OFF, 624);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTClearFlag(INT_T2);
    INTEnable(INT_T2, INT_ENABLED);
}


 enum Drum_Game {DifficultyScreen1, DifficultyScreen2, DifficultyScreen3, GameScreen1, GameScreen2, GameScreen3, secretGame, secretMenu } Choices; // defining all states
int main() {
    char oledstring[17];
    unsigned int timer2_ms_value_save;
    unsigned int GameTimer = 0; unsigned int ProgTmr = 0;
    unsigned int last_oled_update = 0;
    unsigned int ms_since_last_oled_update;
    unsigned int glyph_pos_x = 3, glyph_pos_y = 1;
    unsigned int pix_x1 = 0, pix_y1 = 9;
    unsigned int pix_x2 = 0, pix_y2 = 19;
    unsigned int pix_x3 = 0, pix_y3 = 29;
    signed int velocity = 1; // 4 for hard, 1 for easy , reconfigure settings for 1
    signed int trajectory = 0; // y value never changes
    int retValue = 0;
    int game_start = 0;
    int i1 =0, i2 = 0, j1 =0, j2 = 0, k1 =0, k2 = 0;
    int StartMenClr = 0;
    unsigned int paddle_pos = 14;
    unsigned int y_change = 0;
    signed int y_sub = 0;
    signed int ball_change = 0;
    unsigned char button1Previous = 0x00; //Last eight samples of BTN1
    unsigned char button2Previous = 0x00; //Last eight samples of BTN2
    char buf[17]; 
    char buf2 [17];
    char OledScore[17];
    int ScoreBoard = 0;
    int streak_good = 0;
    int streak_bad = 0;
    int ID;
    int si = 0;
        //This is the SPI channel on JTAG E
    const SpiChannel chn = SPI_CHANNEL3;
    

    

    // Initialize GPIO for LEDs
    TRISGCLR = LED_MASK; // For LEDs: configure PortG pins for output
    ODCGCLR = LED_MASK; // For LEDs: configure as normal output (not open drain)
    LATGCLR = LED_MASK; // Initialize LEDs to 0000

    // Initialize Timer1 and OLED for display
    DelayInit();
    OledInit();
    initSPI(chn);
    
    // Initialize ACL
    // measure on
    SpiChnPutC(chn, 0x2D); 
    SpiChnPutC(chn, 0x08);
    SpiChnGetC(chn);
    SpiChnGetC(chn);
    
    // set range to +/- 4g
    // the rest of the settings stay at default
    SpiChnPutC(chn, 0x31);
    SpiChnPutC(chn, 0x01);
    SpiChnGetC(chn);
    SpiChnGetC(chn);
    
    // read the device ID
    SpiChnPutC(chn, 0x00|0x80); 
    SpiChnPutC(chn, 0xFF);
    SpiChnGetC(chn);
    ID = SpiChnGetC(chn); // receives ID number
    
        int button1Press() {
        int current = PORTG & BUTTON1; //read button
        if (current == button1Previous)
            
            return 0; // no change
        DelayMs (1) ; //delays 1 ms is how debouncing works
        current = PORTG & BUTTON1; //reads button again
        if (current == button1Previous) return 0; // way to clarify debounce
        
        button1Previous = current; // allows to loop
        
        if (current) return 1; // rising edge from off to on
        return 0;
    }
    int button2Press() { //for button2
        int current = PORTG & BUTTON2; //read button
        if (current == button2Previous) 
            return 0; // no change
        DelayMs (1) ; //delays 1 ms for debouncing
        current = PORTG & BUTTON2; //reads button again
        if (current == button2Previous) return 0; 
        
        button2Previous = current; // allows to loop
        
        if (current) return 1; // rising edge from off to on
        return 0;
    }
    // Initialize GPIO for debugging
    DBG_INIT();

    // Initial Timer2
    initTimer2();

    // Configure the system for vectored interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // Enable the interrupt controller
    INTEnableInterrupts();
    

   
    while (1) {
        ms_since_last_oled_update = timer2_ms_value - last_oled_update;
        if (ms_since_last_oled_update >= NUMBER_OF_MILLISECONDS_PER_OLED_UPDATE) {
            //DBG_ON(MASK_DBG1);
            timer2_ms_value_save = timer2_ms_value;
            last_oled_update = timer2_ms_value;
            //DBG_OFF(MASK_DBG1);
            //DBG_ON(MASK_DBG2);
            
            short x_Data[3];
        short final_x_Data;
        short x_axis = 0;
        short y_Data[3];
        short final_y_Data;
        short y_axis = 0;
        
        SpiChnPutC(chn, 0x32|0x80); 
        SpiChnPutC(chn, 0x00);
        SpiChnGetC(chn);
        x_Data[0] = SpiChnGetC(chn); // receives data
        
        SpiChnPutC(chn, 0x33|0x80); 
        SpiChnPutC(chn, 0x00);
        SpiChnGetC(chn);
        x_Data[1] = SpiChnGetC(chn); // receives data
        
        final_x_Data = (x_Data[1] << 8) | x_Data[0];
        
        x_axis = final_x_Data /100 ; // scaled by 100
        
        // y-axis
        SpiChnPutC(chn, 0x34|0x80); 
        SpiChnPutC(chn, 0x00);
        SpiChnGetC(chn);
        y_Data[0] = SpiChnGetC(chn); // receives data
        
        SpiChnPutC(chn, 0x35|0x80); 
        SpiChnPutC(chn, 0x00);
        SpiChnGetC(chn);
        y_Data[1] = SpiChnGetC(chn); // receives data
        
        final_y_Data = (y_Data[1] << 8) | y_Data[0];
        
        y_axis = final_y_Data /100 ; // scaled by 100
            
            
            ProgTmr++;
            
  if (ProgTmr < 50)
            {// Send a welcome message to the OLED display

            OledSetCursor(0, 0);          // upper-left corner of display
            OledPutString("Drum Hero");
            OledSetCursor(0, 1);          // column 0, row 1 of display
            OledPutString("Haroun Ansari");
            OledSetCursor(0, 2);          // column 0, row 2 of display
            OledPutString("ECE 2534 LAB 3");
            OledSetCursor(0,3);
            sprintf(buf, "%d", ProgTmr );
            OledPutString(buf);
            OledUpdate();
                  
            }
            else if (ProgTmr == 50)
            {
                OledClearBuffer();
            }
            else if (ProgTmr > 50 ){ // after 5s
            
                switch (Choices) { // switching between all states
                
                    Choices = DifficultyScreen1;
                
       // display after 5 sec
   case DifficultyScreen1: {
        
            
            if(StartMenClr == 0) // clears buffer once when program restarts
            {                    // only done once to stop flashing screens
                OledClearBuffer();
            }
            StartMenClr++;
    
            
    OledSetCursor(0, 0);          // upper-left corner of display
    OledPutString("Choose Level");
    OledSetCursor(0, 1);          // column 0, row 1 of display
    OledPutString( "   ->Easy  ");
    OledUpdate();
    OledSetCursor(0, 2);          // column 0, row 2 of display
    OledPutString("Medium  ");
    OledUpdate();
    OledSetCursor(0, 3);          // column 0, row 2 of display
    OledPutString("Hard  ");
    
            if(rightTwist(y_axis)){
                StartMenClr = 0;
                si++;
                if(si > 2){
                Choices = secretMenu;
                }
            }
            else if(button1Press()){// goes down
                
                StartMenClr = 0;
                Choices = DifficultyScreen2;
                DelayMs(10);
                } // move cursor down menu
    
            else if(button2Press()){
                Choices = GameScreen1;
            } 
           }
   break;
   
   case DifficultyScreen2: {
   
            if(StartMenClr == 0) // clears buffer once when program restarts
            {                    // only done once to stop flashing screens
                OledClearBuffer();
            }
            StartMenClr++;
            
    OledSetCursor(0, 0);          // upper-left corner of display
    OledPutString("Choose Level");
    OledSetCursor(0, 1);          // column 0, row 1 of display
    OledPutString( "Easy  ");
    OledUpdate();
    OledSetCursor(0, 2);          // column 0, row 2 of display
    OledPutString("   ->Medium  ");
    OledUpdate();
    OledSetCursor(0, 3);          // column 0, row 2 of display
    OledPutString("Hard  ");
            
            
            
            if(rightTwist(y_axis)){
                StartMenClr = 0;
                si++;
                if(si > 2){
                Choices = secretMenu;
                }
            }
            else if(button1Press()){// goes down
            Choices = DifficultyScreen3;
            StartMenClr = 0;
            DelayMs(10);
            } // move cursor down menu
    
            else if(button2Press()){
                Choices = GameScreen2;
            } 
           }
   break;
   
         case DifficultyScreen3: {
            
            if(StartMenClr == 0) // clears buffer once when program restarts
            {                    // only done once to stop flashing screens
                OledClearBuffer();
            }
            StartMenClr++;
            
    OledSetCursor(0, 0);          // upper-left corner of display
    OledPutString("Choose Level");
    OledSetCursor(0, 1);          // column 0, row 1 of display
    OledPutString( "Easy  ");
    OledUpdate();
    OledSetCursor(0, 2);          // column 0, row 2 of display
    OledPutString("Medium  ");
    OledUpdate();
    OledSetCursor(0, 3);          // column 0, row 2 of display
    OledPutString("   ->Hard  ");
    
            if(rightTwist(y_axis)){
                StartMenClr = 0;
                si++;
                if(si > 2){
                Choices = secretMenu;
                }
            }
            else if(button1Press()){// goes down
                StartMenClr = 0;
                Choices = DifficultyScreen1;
            DelayMs(10);} // move cursor down menu
            else if(button2Press()){
                Choices = GameScreen3;
            } 
           }
   break;
                  case GameScreen1: {
            
            //OledSetCursor(glyph_pos_x, glyph_pos_y);

            OledUpdate();   // cleans the screen       
            GameTimer++;    // used for starting and ending game
            velocity = 1;   // used for different difficulty
            
            if(GameTimer == 1){ // cleans screen
                OledClearBuffer();
            }
            if(GameTimer < 600) // game play actually starts
            {
                                       /* for loop execution */
                        int a;
               for( a = 0; a <= 108; a = a + 4 ) // Dotted lines at y pos = 15 and 27
               {                                 // used for dividing areas up
                  OledSetDrawColor(1);
                  OledMoveTo(a,15); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(a,24); // 2nd line
                  OledDrawPixel(); 

               }
                        int b;
            for( b = 7; b <= 32; b++ ) // score zone where if arrows reach we get points
               {
                  OledSetDrawColor(1);
                  OledMoveTo(108, b); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(109, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(110, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(111, b); // 2nd line
                  OledDrawPixel(); 

               }
                  OledSetCursor(15, 1); // distinguishes areas for twists
                  OledPutString("R");  
                  OledSetCursor(15, 2);
                  OledPutString("D"); 
                  OledSetCursor(15, 3);
                  OledPutString("L"); 
                  
                  
                   sprintf(OledScore, "%d", ScoreBoard ); // shows our score
                   OledSetCursor(0, 0);
                   OledPutString(OledScore);
                   
                   // audience feedback - done
                   if(streak_good >= -3 && streak_good <= 3 && streak_bad == 0){ // neutral reaction
                   sprintf(buf, "AFB :|");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good > 3 && streak_good < 7){ // happy reaction
                   sprintf(buf, "AFB :)");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good >= 7){ // very happy reaction
                   sprintf(buf, "AFB :D");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_bad > 3 && streak_bad < 7){ //sad reaction
                   sprintf(buf, "AFB ):");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   if(streak_bad >= 7){ // very sad reaction
                   sprintf(buf, "AFB D:");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   // arrows
            OledSetDrawColor(1);
            OledMoveTo(pix_x1,pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1,pix_y1+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1, pix_y1-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x1 - velocity, pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1-1);
            OledDrawPixel();
            pix_x1 = pix_x1+velocity; // moves arrow across screen
            
            if(GameTimer > 50){ // generates arrows for second row and puts it in later
            OledSetDrawColor(1);
            OledMoveTo(pix_x2,pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x2 - velocity, pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2-1);
            OledDrawPixel();
            pix_x2 = pix_x2+velocity; // moves arrow along screen
            
            }
            
            if(GameTimer > 25){
            OledSetDrawColor(1);
            OledMoveTo(pix_x3, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x3 - velocity, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3-1);
            OledDrawPixel();
            pix_x3 = pix_x3+velocity; // speed of ball
            
            }
        
          
            if(pix_x1 > 105) // this is the process of moving the top arrow
            { 
                if(rightTwist(y_axis)){
                    OledSetCursor(14,1);
                    OledPutString("*"); // outputs * if you score
                    ScoreBoard = ScoreBoard + 500; // increase score
                    streak_good++;
                    streak_bad = 0;
                    if (i1 < 10) // keeps the asterisk on the screen long enough
                    {
                        OledPutString("*");
                        i1 = 0;
                    }
                    i1++;
                    OledSetCursor(14,1);
                    OledPutString(" "); // clears asterisk
                    OledClearBuffer();
                    pix_x1 = 0;
                    
                }
                else if(pix_x1 > 111){
                    OledSetCursor(14,1);
                    OledPutString(">"); // outputs > as enlarged version of arrow
                    ScoreBoard = ScoreBoard - 100; // takes away points for a miss
                    streak_bad++;
                    streak_good = 0;
                    if (i2 < 100) // used for keeping it on screen
                    {
                        OledPutString(">"); //keeps the arrow on screen
                        i2 = 0;
                    }
                    i2++;
                    OledSetCursor(14,1);
                    OledPutString(" "); //removes arrow from screen
                    OledClearBuffer();
                    
                }
            if(pix_x1 > 111){ // restarts arrow  
                pix_x1 = 0; 
                OledClearBuffer;
                }
            }
            if(pix_x2 > 105) // this is the process of moving the middle arrow
            {
                if(button2Press()){ 
                    OledSetCursor(14,2);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    streak_bad = 0;
                    if (j1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        j1 = 0;
                    }
                    j1++;
                    OledSetCursor(14,2);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x2 = 0;
                    
                }
                else if(pix_x2 > 111){
                    OledSetCursor(14,2);
                    OledPutString(">");
                    ScoreBoard = ScoreBoard - 100;
                    streak_bad++;
                    streak_good = 0;
                    if (j2 < 10) // used for keeping it on screen
                    {
                        OledPutString(">");
                        j2 = 0;
                    }
                    j2++;                    
                    OledClearBuffer();
                }
                
              if(pix_x2 > 111){  
                pix_x2 = 0;
                OledClearBuffer; 
                }
           }
            if(pix_x3 > 105) // this is the process of moving the bottom arrow
            {
                if(leftTwist(y_axis)){ // put Left Twist here
                    OledSetCursor(14,3);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    streak_bad = 0;
                    if (k1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        k1 = 0;
                    }
                    k1++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x3 = 0;
                    
                }
                else if(pix_x3 > 111 ){
                    OledSetCursor(14,3);
                    OledPutString(">");
                    ScoreBoard = ScoreBoard - 100;
                    streak_bad++;
                    streak_good = 0;
                    if (k2 < 10) // used for keeping it on screen
                    {
                        OledPutString(">");
                        k2 = 0;
                    }
                    k2++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                }
                
              if(pix_x3 > 111){ //restarts arrow
                pix_x3 = 0;
                OledClearBuffer;
                }
                
            }
            }
            if(GameTimer > 600 && GameTimer < 700){
                OledClearBuffer();
            sprintf(buf, "YOUR SCORE: \n  %d", ScoreBoard );
            OledSetCursor(1, 1);
            OledPutString(buf);
            }
            if (GameTimer > 700){
                ScoreBoard = 0;
                GameTimer = 0;
                StartMenClr = 0;
                pix_x1 = 0;
                pix_x2 = 0;
                pix_x3 = 0;
                streak_good = 0;
                streak_bad = 0;
                Choices = DifficultyScreen1;
            }

    
            
           }
   break;
   
                     case GameScreen2: {
            
            //OledSetCursor(glyph_pos_x, glyph_pos_y);

            OledUpdate();   // cleans the screen       
            GameTimer++;    // used for starting and ending game
            velocity = 2;   // used for different difficulty - medium
            
            if(GameTimer == 1){ // cleans screen
                OledClearBuffer();
            }
            if(GameTimer < 600) // game play actually starts
            {
                                       /* for loop execution */
                        int a;
               for( a = 0; a <= 108; a = a + 4 ) // Dotted lines at y pos = 15 and 27
               {                                 // used for dividing areas up
                  OledSetDrawColor(1);
                  OledMoveTo(a,15); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(a,24); // 2nd line
                  OledDrawPixel(); 

               }
                        int b;
            for( b = 7; b <= 32; b++ ) // score zone where if arrows reach we get points
               {
                  OledSetDrawColor(1);
                  OledMoveTo(108, b); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(109, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(110, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(111, b); // 2nd line
                  OledDrawPixel(); 

               }
                  OledSetCursor(15, 1); // distinguishes areas for twists
                  OledPutString("R");  
                  OledSetCursor(15, 2);
                  OledPutString("D"); 
                  OledSetCursor(15, 3);
                  OledPutString("L"); 
                  
                  
                   sprintf(OledScore, "%d", ScoreBoard ); // shows our score
                   OledSetCursor(0, 0);
                   OledPutString(OledScore);
                   
                   // audience feedback done
                   
                   if(streak_good >= -3 && streak_good <= 3 && streak_bad == 0){ // neutral reaction
                   sprintf(buf, "AFB :|");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good > 3 && streak_good < 7){ // happy reaction
                   sprintf(buf, "AFB :)");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good >= 7){ // very happy reaction
                   sprintf(buf, "AFB :D");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_bad > 3 && streak_bad < 7){ //sad reaction
                   sprintf(buf, "AFB ):");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   if(streak_bad >= 7){ // very sad reaction
                   sprintf(buf, "AFB D:");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   // arrows
            OledSetDrawColor(1);
            OledMoveTo(pix_x1,pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1,pix_y1+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1, pix_y1-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x1 - velocity, pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1-1);
            OledDrawPixel();
            pix_x1 = pix_x1+velocity; // moves arrow across screen
            
            if(GameTimer > 50){ // generates arrows for second row and puts it in later
            OledSetDrawColor(1);
            OledMoveTo(pix_x2,pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x2 - velocity, pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2-1);
            OledDrawPixel();
            pix_x2 = pix_x2+velocity; // moves arrow along screen
            
            }
            
            if(GameTimer > 25){
            OledSetDrawColor(1);
            OledMoveTo(pix_x3, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x3 - velocity, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3-1);
            OledDrawPixel();
            pix_x3 = pix_x3+velocity; // speed of ball
            
            }
        
          
             if(pix_x1 > 105) // this is the process of moving the top arrow
            { 
                if(rightTwist(y_axis)){
                    OledSetCursor(14,1);
                    OledPutString("*"); // outputs * if you score
                    ScoreBoard = ScoreBoard + 500; // increase score
                    streak_good++;
                    streak_bad = 0;
                    if (i1 < 10) // keeps the asterisk on the screen long enough
                    {
                        OledPutString("*");
                        i1 = 0;
                    }
                    i1++;
                    OledSetCursor(14,1);
                    OledPutString(" "); // clears asterisk
                    OledClearBuffer();
                    pix_x1 = 0;
                    
                }
                else if(pix_x1 > 111){
                    OledSetCursor(14,1);
                    OledPutString(">"); // outputs > as enlarged version of arrow
                    ScoreBoard = ScoreBoard - 100; // takes away points for a miss
                    streak_bad++;
                    streak_good = 0;
                    if (i2 < 100) // used for keeping it on screen
                    {
                        OledPutString(">"); //keeps the arrow on screen
                        i2 = 0;
                    }
                    i2++;
                    OledSetCursor(14,1);
                    OledPutString(" "); //removes arrow from screen
                    OledClearBuffer();
                    
                }
            if(pix_x1 > 111){ // restarts arrow  
                pix_x1 = 0; 
                OledClearBuffer;
                }
            }
            if(pix_x2 > 105) // this is the process of moving the middle arrow
            {
                if(button2Press()){ 
                    OledSetCursor(14,2);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    streak_bad = 0;
                    if (j1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        j1 = 0;
                    }
                    j1++;
                    OledSetCursor(14,2);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x2 = 0;
                    
                }
                else if(pix_x2 > 111){
                    OledSetCursor(14,2);
                    OledPutString(">");
                    ScoreBoard = ScoreBoard - 100;
                    streak_bad++;
                    streak_good = 0;
                    if (j2 < 10) // used for keeping it on screen
                    {
                        OledPutString(">");
                        j2 = 0;
                    }
                    j2++;                    
                    OledClearBuffer();
                }
                
              if(pix_x2 > 111){  
                pix_x2 = 0;
                OledClearBuffer; 
                }
           }
            if(pix_x3 > 105) // this is the process of moving the bottom arrow
            {
                if(leftTwist(y_axis)){ // put Left Twist here
                    OledSetCursor(14,3);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    streak_bad = 0;
                    if (k1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        k1 = 0;
                    }
                    k1++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x3 = 0;
                    
                }
                else if(pix_x3 > 111 ){
                    OledSetCursor(14,3);
                    OledPutString(">");
                    ScoreBoard = ScoreBoard - 100;
                    streak_bad++;
                    streak_good = 0;
                    if (k2 < 10) // used for keeping it on screen
                    {
                        OledPutString(">");
                        k2 = 0;
                    }
                    k2++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                }
                
              if(pix_x3 > 111){ //restarts arrow
                pix_x3 = 0;
                OledClearBuffer;
                }
                
            }
            }
            if(GameTimer > 600 && GameTimer < 700){
                OledClearBuffer();
            sprintf(buf, "YOUR SCORE: \n  %d", ScoreBoard );
            OledSetCursor(1, 1);
            OledPutString(buf);
            }
            if (GameTimer > 700){
                ScoreBoard = 0;
                GameTimer = 0;
                StartMenClr = 0;
                pix_x1 = 0;
                pix_x2 = 0;
                pix_x3 = 0;
                streak_good = 0;
                streak_bad = 0;
                Choices = DifficultyScreen1;
            }

    
            
           }
   break;
   
                        case GameScreen3: {
            
            //OledSetCursor(glyph_pos_x, glyph_pos_y);

            OledUpdate();   // cleans the screen       
            GameTimer++;    // used for starting and ending game
            velocity = 3;   // used for different difficulty - medium
            
            if(GameTimer == 1){ // cleans screen
                OledClearBuffer();
            }
            if(GameTimer < 600) // game play actually starts
            {
                                       /* for loop execution */
                        int a;
               for( a = 0; a <= 108; a = a + 4 ) // Dotted lines at y pos = 15 and 27
               {                                 // used for dividing areas up
                  OledSetDrawColor(1);
                  OledMoveTo(a,15); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(a,24); // 2nd line
                  OledDrawPixel(); 

               }
                        int b;
            for( b = 7; b <= 32; b++ ) // score zone where if arrows reach we get points
               {
                  OledSetDrawColor(1);
                  OledMoveTo(108, b); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(109, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(110, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(111, b); // 2nd line
                  OledDrawPixel(); 

               }
                  OledSetCursor(15, 1); // distinguishes areas for twists
                  OledPutString("R");  
                  OledSetCursor(15, 2);
                  OledPutString("D"); 
                  OledSetCursor(15, 3);
                  OledPutString("L"); 
                  
                  
                   sprintf(OledScore, "%d", ScoreBoard ); // shows our score
                   OledSetCursor(0, 0);
                   OledPutString(OledScore);
                   
                   // audience feedback done
                   
                   if(streak_good >= -3 && streak_good <= 3 && streak_bad == 0){ // neutral reaction
                   sprintf(buf, "AFB :|");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good > 3 && streak_good < 7){ // happy reaction
                   sprintf(buf, "AFB :)");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good >= 7){ // very happy reaction
                   sprintf(buf, "AFB :D");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_bad > 3 && streak_bad < 7){ //sad reaction
                   sprintf(buf, "AFB ):");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   if(streak_bad >= 7){ // very sad reaction
                   sprintf(buf, "AFB D:");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   // arrows
            OledSetDrawColor(1);
            OledMoveTo(pix_x1,pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1,pix_y1+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1, pix_y1-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x1 - velocity, pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1-1);
            OledDrawPixel();
            pix_x1 = pix_x1+velocity; // moves arrow across screen
            
            if(GameTimer > 50){ // generates arrows for second row and puts it in later
            OledSetDrawColor(1);
            OledMoveTo(pix_x2,pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x2 - velocity, pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2-1);
            OledDrawPixel();
            pix_x2 = pix_x2+velocity; // moves arrow along screen
            
            }
            
            if(GameTimer > 25){
            OledSetDrawColor(1);
            OledMoveTo(pix_x3, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x3 - velocity, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3-1);
            OledDrawPixel();
            pix_x3 = pix_x3+velocity; // speed of ball
            
            }
        
          
             if(pix_x1 > 105) // this is the process of moving the top arrow
            { 
                if(rightTwist(y_axis)){
                    OledSetCursor(14,1);
                    OledPutString("*"); // outputs * if you score
                    ScoreBoard = ScoreBoard + 500; // increase score
                    streak_good++;
                    streak_bad = 0;
                    if (i1 < 10) // keeps the asterisk on the screen long enough
                    {
                        OledPutString("*");
                        i1 = 0;
                    }
                    i1++;
                    OledSetCursor(14,1);
                    OledPutString(" "); // clears asterisk
                    OledClearBuffer();
                    pix_x1 = 0;
                    
                }
                else if(pix_x1 > 111){
                    OledSetCursor(14,1);
                    OledPutString(">"); // outputs > as enlarged version of arrow
                    ScoreBoard = ScoreBoard - 100; // takes away points for a miss
                    streak_bad++;
                    streak_good = 0;
                    if (i2 < 100) // used for keeping it on screen
                    {
                        OledPutString(">"); //keeps the arrow on screen
                        i2 = 0;
                    }
                    i2++;
                    OledSetCursor(14,1);
                    OledPutString(" "); //removes arrow from screen
                    OledClearBuffer();
                    
                }
            if(pix_x1 > 111){ // restarts arrow  
                pix_x1 = 0; 
                OledClearBuffer;
                }
            }
            if(pix_x2 > 105) // this is the process of moving the middle arrow
            {
                if(button2Press()){ 
                    OledSetCursor(14,2);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    streak_bad = 0;
                    if (j1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        j1 = 0;
                    }
                    j1++;
                    OledSetCursor(14,2);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x2 = 0;
                    
                }
                else if(pix_x2 > 111){
                    OledSetCursor(14,2);
                    OledPutString(">");
                    ScoreBoard = ScoreBoard - 100;
                    streak_bad++;
                    streak_good = 0;
                    if (j2 < 10) // used for keeping it on screen
                    {
                        OledPutString(">");
                        j2 = 0;
                    }
                    j2++;                    
                    OledClearBuffer();
                }
                
              if(pix_x2 > 111){  
                pix_x2 = 0;
                OledClearBuffer; 
                }
           }
            if(pix_x3 > 105) // this is the process of moving the bottom arrow
            {
                if(leftTwist(y_axis)){ // put Left Twist here
                    OledSetCursor(14,3);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    streak_bad = 0;
                    if (k1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        k1 = 0;
                    }
                    k1++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x3 = 0;
                    
                }
                else if(pix_x3 > 111 ){
                    OledSetCursor(14,3);
                    OledPutString(">");
                    ScoreBoard = ScoreBoard - 100;
                    streak_bad++;
                    streak_good = 0;
                    if (k2 < 10) // used for keeping it on screen
                    {
                        OledPutString(">");
                        k2 = 0;
                    }
                    k2++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                }
                
              if(pix_x3 > 111){ //restarts arrow
                pix_x3 = 0;
                OledClearBuffer;
                }
                
            }
            }
            if(GameTimer > 600 && GameTimer < 700){
                OledClearBuffer();
            sprintf(buf, "YOUR SCORE: \n  %d", ScoreBoard );
            OledSetCursor(1, 1);
            OledPutString(buf);
            }
            if (GameTimer > 700){
                ScoreBoard = 0;
                GameTimer = 0;
                StartMenClr = 0;
                
                Choices = DifficultyScreen1;
            }

    
            
           }
   break;
   
   
   
   case secretGame: {
            
            //OledSetCursor(glyph_pos_x, glyph_pos_y);

            OledUpdate();   // cleans the screen       
            GameTimer++;    // used for starting and ending game
            velocity = 3;   // used for different difficulty - hard
            
            if(GameTimer == 1){ // cleans screen
                OledClearBuffer();
            }
            if(GameTimer < 600) // game play actually starts
            {
                                       /* for loop execution */
                        int a;
               for( a = 0; a <= 108; a = a + 4 ) // Dotted lines at y pos = 15 and 27
               {                                 // used for dividing areas up
                  OledSetDrawColor(1);
                  OledMoveTo(a,15); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(a,24); // 2nd line
                  OledDrawPixel(); 

               }
                        int b;
            for( b = 7; b <= 32; b++ ) // score zone where if arrows reach we get points
               {
                  OledSetDrawColor(1);
                  OledMoveTo(108, b); //Draw Top 1st line
                  OledDrawPixel();
                  OledMoveTo(109, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(110, b); // 2nd line
                  OledDrawPixel(); 
                  OledMoveTo(111, b); // 2nd line
                  OledDrawPixel(); 

               }
                  OledSetCursor(15, 1); // distinguishes areas for twists
                  OledPutString("R");  
                  OledSetCursor(15, 2);
                  OledPutString("D"); 
                  OledSetCursor(15, 3);
                  OledPutString("L"); 
                  
                  
                   sprintf(OledScore, "%d", ScoreBoard ); // shows our score
                   OledSetCursor(0, 0);
                   OledPutString(OledScore);
                   
                   // audience feedback
                   // audience feedback
                   if(streak_good >= -3 && streak_good <= 3 && streak_bad == 0){ // neutral reaction
                   sprintf(buf, "AFB :|");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good > 3 && streak_good < 7){ // happy reaction
                   sprintf(buf, "AFB :)");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_good >= 7){ // very happy reaction
                   sprintf(buf, "AFB :D");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   if(streak_bad > 3 && streak_bad < 7){ //sad reaction
                   sprintf(buf, "AFB ):");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   if(streak_bad >= 7){ // very sad reaction
                   sprintf(buf, "AFB D:");
                   OledSetCursor(6, 0);
                   OledPutString(buf); 
                   }
                   
                   // arrows
            OledSetDrawColor(1);
            OledMoveTo(pix_x1,pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1,pix_y1+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1, pix_y1-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x1 - velocity, pix_y1);
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x1-1 - velocity, pix_y1-1);
            OledDrawPixel();
            pix_x1 = pix_x1+velocity; // moves arrow across screen
            
            if(GameTimer > 50){ // generates arrows for second row and puts it in later
            OledSetDrawColor(1);
            OledMoveTo(pix_x2,pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1,pix_y2-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x2 - velocity, pix_y2);
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x2-1 - velocity, pix_y2-1);
            OledDrawPixel();
            pix_x2 = pix_x2+velocity; // moves arrow along screen
            
            }
            
            if(GameTimer > 25){
            OledSetDrawColor(1);
            OledMoveTo(pix_x3, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3+1); // used for drawing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1, pix_y3-1);
            OledDrawPixel();
            OledSetDrawColor(0);
            OledMoveTo(pix_x3 - velocity, pix_y3);
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3+1); // used for erasing arrow
            OledDrawPixel();
            OledMoveTo(pix_x3-1 - velocity, pix_y3-1);
            OledDrawPixel();
            pix_x3 = pix_x3+velocity; // speed of ball
            
            }
        
          
            if(pix_x1 > 105) // this is the process of moving the top arrow
            { 
                    OledSetCursor(14,1);
                    OledPutString("*"); // outputs * if you score
                    ScoreBoard = ScoreBoard + 500; // increase score
                    streak_good++;
                    OledSetCursor(13,1);
                    OledPutString("  ");
                    if (i1 < 10) // keeps the asterisk on the screen long enough
                    {
                        OledPutString("*");
                        i1 = 0;
                    }
                    i1++;
                    OledSetCursor(14,1);
                    OledPutString(" "); // clears asterisk
                    OledClearBuffer();
                    pix_x1 = 0;
                                      
                    
                }
            if(pix_x1 > 111){ // restarts arrow  
                pix_x1 = 0; 
                OledClearBuffer;
                }
            }
            if(pix_x2 > 105) // this is the process of moving the middle arrow
            {
                    OledSetCursor(14,2);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    OledSetCursor(13,2);
                    OledPutString("  ");
                    if (j1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        j1 = 0;
                    }
                    j1++;
                    OledSetCursor(14,2);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x2 = 0;
                    
                
              if(pix_x2 > 111){  
                pix_x2 = 0;
                OledClearBuffer; 
                }
           }
            if(pix_x3 > 105) // this is the process of moving the bottom arrow
            {
                
                    OledSetCursor(14,3);
                    OledPutString("*");
                    ScoreBoard = ScoreBoard + 500;
                    streak_good++;
                    OledSetCursor(13,3);
                    OledPutString("  ");
                    if (k1 < 10) // used for keeping it on screen
                    {
                        OledPutString("*");
                        k1 = 0;
                    }
                    k1++;
                    OledSetCursor(14,3);
                    OledPutString(" ");
                    OledClearBuffer();
                    pix_x3 = 0;
                    
                
              if(pix_x3 > 111){ //restarts arrow
                pix_x3 = 0;
                OledClearBuffer;
                }
                
            }
            
            if(GameTimer > 600 && GameTimer < 700){
                OledClearBuffer();
            sprintf(buf, "YOUR SCORE: \n  %d", ScoreBoard );
            OledSetCursor(1, 1);
            OledPutString(buf);
            }
            if (GameTimer > 700){
                ScoreBoard = 0;
                GameTimer = 0;
                StartMenClr = 0;
                pix_x1 = 0;
                pix_x2 = 0;
                pix_x3 = 0;
                streak_good = 0;
                streak_bad = 0;
                Choices = DifficultyScreen1;
            }
   }       
   break;
   
   case secretMenu: {
        
            si = 0;
            
            if(StartMenClr == 0) // clears buffer once when program restarts
            {                    // only done once to stop flashing screens
                OledClearBuffer();
            }
            StartMenClr++;
    
           
    OledSetCursor(0, 0);          // upper-left corner of display
    OledPutString("Secret Menu");
    OledSetCursor(0, 1);          // column 0, row 1 of display
    OledPutString( "   Press B1  ");
    OledUpdate();
    OledSetCursor(0, 2);          // column 0, row 2 of display
    OledPutString("   To Enter  ");
    OledUpdate();
    OledSetCursor(0, 3);          // column 0, row 2 of display
    OledPutString("   God Mode  ");
    
            if(button1Press()) {
                StartMenClr = 0;
                Choices = secretGame;

            }
                
            else if(button2Press()){
                Choices = DifficultyScreen1;
            } 
           }
   break;

            } // choices

            DBG_OFF(MASK_DBG2);
            LATGINV = LED_MASK; // Twiddle LEDs
            } // if timer>5
        } // if ms
    } // while
    return (EXIT_SUCCESS);
} //main


