 
#include "config.h"
#include "lcdWrite.h"
#include "byteLcd.h"
#include <stdio.h>
void move_ball(void)
{
  
  const  bool upper_pos[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xc0};    // up and down positions
  const  bool start_pos_up[8] = {0xe0,0x70,0x38,0x1c,0x0e,0x07,0x03,0x01};
  
  const bool start_pos_dwn[8] = {0x07,0x0e,0x1c,0x38,0x70,0xe0,0xc0,0x80};
  const bool lower_pos[8] =     {0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03};
  //    index                      0    1     2    3   4     5     6   7  
  if(col <76)
  {
      if(col >24)          // inc row so that start_pos_dwn data can be written to display ( 3 x 8 = 24 so next col address is 25 + 24 = 49 etc))
            {
                row = row + 1;
            }
      else if(col > 48)    // inc row so that start_pos_dwn data can be written to display ( 3 x 8 = 24 so next col address is 49 + 24 = 73 etc))
            {
                row = row + 2;
            }
      else if (col > 74)   // inc row so that start_pos_dwn data can be written to display ( max address is 84 -3 = 81, hence col max address at top of loop))
            {
                row = row + 3;
            }
  for(counter = 0; counter <8 ; counter++)
  {
      if(col >82) 
            {
                break;
            }
    for(j = 0; j <3; j++)
    {
            lcdWrite(SET_X|col, LOW);     // set X address to col = 1
            lcdWrite(SET_Y|row, LOW);     // set Y address to row = 0 (top row)  
            lcdWrite(start_pos_dwn[counter]|gameplay_area[row][col], HIGH);
        
            lcdWrite(SET_X|col, LOW);     // set X address to col = 1
            lcdWrite(SET_Y|row+1, LOW);     // set Y address to row = 1(row 1)
            lcdWrite(lower_pos[counter]|gameplay_area[row][col], HIGH);
            printf("col = %d\n", col);
            col++;        
    }   
            col = col - 6;              // move col back six columns to erase the first ball position
            for(k = 0; k < 3; k++) // move the row up one if col is between these values ( 22,23,24 or 46,47,48, or 70,71,72)
            {
                if (col > 21 && col < 25)
                {
                    row = row -1;
                }
                else if (col > 45 && col < 49)
                {
                    row = row -1;
                }
                else if (col > 69 && col < 73)
                {
                    row = row -1;
                }
                lcdWrite(SET_X|col, LOW);     // set X address to col = 1   //clear the top row of ball pattern
                lcdWrite(SET_Y|row, LOW);     // set Y address to row = 0 (top row)  
                lcdWrite(0x00|gameplay_area[row][col], HIGH);
    
                lcdWrite(SET_X|col, LOW);     // set X address to col = 1       // clear the lower row of ball pattern
                lcdWrite(SET_Y|row+1, LOW);     // set Y address to row = 0 (row 1)
                if(row > 0 && row < 6)
                {
                lcdWrite(0x00|gameplay_area[row][col], HIGH);
                }
                else
                {
                    lcdWrite(0x00, HIGH);
                }
                if (col > 21 && col < 25)   // restore row back down one row to it's original position position 
                {
                    row = row + 1;
                }
                else if (col > 45 && col < 49)
                {
                    row = row + 1;
                }
                 else if (col > 69 && col < 73)
                {
                    row = row + 1;
                }
                col++;      // col has increased by three using the for loop
            } 
            col = col+3;    // col increased by another three to get col back to where it was before the erase process started
    }
  }
}
            