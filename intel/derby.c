/**********************************************************************/
/* file name: derby.c                                                 */
/**********************************************************************/

#include <reg51gb.h>  
#include <stdio.h>
#include "derby.h"  

/**********************************************************************/
/* main line portion of code                                          */
/**********************************************************************/
void main (void)
{
  unsigned char i, done;
  /* initialize system hardware */
  initHardware();
  
  printf("Welcome to the Pinewood Derby Electronic Judge\n");
 
  while (1)
  {   
    if (startLeverIsReleased() == TRUE)
    { /* start lever is still in the release position */
      printf("\nFix the start lever.\n");
      /* wait until operator starts the race */
      while (startLeverIsReleased() == TRUE);
    } /* if */
     
    /* set to a race not completed condition */
    raceStatus = 0;
   
    /* stop the programmer counter array */
    resetPca();
    
    printf("\nGet ready for the race!\n");

    /* wait until operator starts the race */
    while (startLeverIsReleased() == FALSE);

    /* start the programmable counter array */
    startPca();
    
    printf("Race is under way!\n\n");

    /* flush any key presses */
    i = keyPressed();
        
    /* set up for loop entry */
    done = FALSE;
        
    while (done == FALSE)
    {
      if (raceStatus == 0x0f)
      { /* race over */
        done = TRUE; /* bail out */
      } /* if */
      else
      { /* race is not over */
        if (keyPressed() == TRUE)
        { /* race aborted */
          printf("Race aborted.\n");
          done = TRUE; /* bail out */
        } /* if */
      } /* else */
    } /* while */
    
    /* set to a race not completed condition */
    raceStatus = 0;

    rankLanes();
    
    for (i = 1; i < 5; i++)
    {
      displayTime(i); /* display time in appropriate format */
    } /* for */
  } /* while */
   
} /* main */ 

/***********************************************************************

  Name: displayTime
    
  Purpose: The purpose of this function is to display the time for a
  particular lane in the Pinewood Derby system.  The units of time
  are in seconds with a resolution of 1 millisecond.
    
  Calling Sequence: displayTime(laneNumber)
    
  Inputs:
    
    laneNumber - The lane number for which to display the time.
    
  Outputs:
  
    None. 
      
***********************************************************************/
void displayTime(unsigned char laneNumber)
{
  unsigned short timeInMilliseconds, mantissa, fraction;

  switch (laneNumber)
  {
    case 1:
      timeInMilliseconds = captureHigh0;
      timeInMilliseconds = timeInMilliseconds << 8;
      timeInMilliseconds |= captureLow0;
      captureHigh0 = 0;
      captureLow0 = 0;
      break;
      
    case 2:
      timeInMilliseconds = captureHigh1;
      timeInMilliseconds = timeInMilliseconds << 8;
      timeInMilliseconds |= captureLow1;
      captureHigh1 = 0;
      captureLow1 = 0;
      break;
      
    case 3:
      timeInMilliseconds = captureHigh2;
      timeInMilliseconds = timeInMilliseconds << 8;
      timeInMilliseconds |= captureLow2;
      captureHigh2 = 0;
      captureLow2 = 0;
      break;
      
    case 4:
      timeInMilliseconds = captureHigh3;
      timeInMilliseconds = timeInMilliseconds << 8;
      timeInMilliseconds |= captureLow3;
      captureHigh3 = 0;
      captureLow3 = 0;
      break;
      
    default:
      break;
      
  } /* case */

  /* compute mantissa and fraction with millisecond resolution */    
  mantissa = timeInMilliseconds / 1000;
  fraction = timeInMilliseconds - (1000 * mantissa);

  /* output results */
  printf ("LANE %d ",laneNumber);
   
  switch (laneRank[laneNumber-1])
  {
    case 1:
      printf("[1st Place] ");
      break;
      
    case 2:
      printf("[2nd Place] ");
      break;
      
    case 3:
      printf("[3rd Place] ");
      break;
      
    case 4:
      printf("[4th Place] ");
      break;
  } /* case */
   
  printf("Time: %2u.%03u seconds\n",mantissa,fraction);

  return;
  
} /* displayTime */

/***********************************************************************

  Name: rankLanes
    
  Purpose: The purpose of this function is to rank the lanes in terms
  of first, second, third, and fourth place.
      
  Calling Sequence: rankLanes()
    
  Inputs:

    None.
        
  Outputs:
  
    None. 
      
***********************************************************************/
void rankLanes(void)
{
  unsigned short time[4], temp;
  unsigned char i, j, scrambledRank[4];
  
  time[0] = captureHigh0;
  time[0] = time[0] << 8;
  time[0] |= captureLow0;

  time[1] = captureHigh1;
  time[1] = time[1] << 8;
  time[1] |= captureLow1;

  time[2] = captureHigh2;
  time[2] = time[2] << 8;
  time[2] |= captureLow2;

  time[3] = captureHigh3;
  time[3] = time[3] << 8;
  time[3] |= captureLow3;

  for (i = 0; i < 4; i++)
  { /* initialize our ranking array */
    scrambledRank[i] = i + 1;
  } /* for */
  
  for (i = 0; i < 3; i++)
  {
    for (j = 1; j < 4; j++)
    {
      if (time[j-1] > time[j])
      {
        /* sort our time array */
        temp = time[j-1];
        time[j-1] = time[j];
        time[j] = temp;
        /* sort our ranking array */
        temp = scrambledRank[j-1];
        scrambledRank[j-1] = scrambledRank[j];
        scrambledRank[j] = temp;
      } /* if */
    } /* for */
  } /* for */
  
  for (i = 0; i < 4; i++)
  { /* unscramble our results */
    laneRank[scrambledRank[i]-1] = i + 1;
  } /* for */
  
  return;
  
} /* rankLanes */

