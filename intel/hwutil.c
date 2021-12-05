/**********************************************************************/
/* file name: hwutil.c                                                */
/**********************************************************************/
#include <reg51gb.h>
#include <stdio.h>
#include "derby.h"

/***********************************************************************

  Name: initHardware
  
  Purpose: The purpose of this function is to initialize all hardware
  in the Pinewood Derby system.
    
  Calling Sequence: initHardware()
    
  Inputs:
    
    None.
    
  Outputs:
    
    None. 
      
***********************************************************************/
void initHardware(void)
{

  /* initialize parallel ports */
  initParallelPorts();
   
  /* initialize UART */
  initUart();
  
  /* initialize timer 0 */
  initTimer0();
  
  /* initialize timer 1 */
  initTimer1();
  
  /* initialize timer2 */
  initTimer2();
  
  /* initialize programmable counter array */
  initPca();
  
  /* initialize the interrupt controller */
  initInterruptController();
  
  return;
  
} /* initHardware */

/***********************************************************************

  Name: initParallelPorts
    
  Purpose: The purpose of this function is to initialize the parallel
  ports in the Pinewood Derby system.
    
  Calling Sequence: initParallelPorts()
    
  Inputs:
  
    None.
    
  Outputs:
    
    None. 
      
***********************************************************************/
void initParallelPorts(void)
{

  /* set our ports so that their registers are all 1s */
  P1 = 0xff;
  P3 = 0xff;
  P4 = 0xff;
  P5 = 0xff;
 
  return;
  
} /* initParallelPorts */

/***********************************************************************

  Name: initUart
    
  Purpose: The purpose of this function is to initialize the serial
  interface in the Pinewood Derby system.
    
  Calling Sequence: initUart()
    
  Inputs:
  
    None.
    
  Outputs:
    
    None. 
      
***********************************************************************/
void initUart(void)
{

  /* SCON: mode 1, 8-bit UART, enable receiver */
  SCON  = 0x50;
  
  /* set TI to send first character of UART */
  TI = 1;
  
  /* clear receiver interrupt flag */
  RI = 0;

  return;
  
} /* initUart */

/***********************************************************************

  Name: initTimer0
    
  Purpose: The purpose of this function is to initialize timer 0
  in the Pinewood Derby system.
    
  Calling Sequence: initTimer0()
    
  Inputs:
    
    None.
    
  Outputs:
    
    None. 
      
***********************************************************************/
void initTimer0(void)
{
  /* Disable Timer */
  TR0 = 0;
  
  /* Set Timer Mode */
  TMOD |= 0x02;
  
  /* Set Reload Value */
  TL0 = 0x00;
  TH0 = 0x00;
  
  /* Enable Timer */
  TR0 = 1;
  
  return;
  
} /* initTimer0 */

/***********************************************************************

  Name: initTimer1
    
  Purpose: The purpose of this function is to initialize timer 1
  in the Pinewood Derby system.  This timer is used as the baud
  rate generator for the serial interface.
    
  Calling Sequence: initTimer1()
    
  Inputs:
    
    None.
    
  Outputs:
    
    None. 
      
***********************************************************************/
void initTimer1(void)
{

  TMOD |= 0x20;  /* TMOD: timer 1, mode 2, 8-bit reload */
  TH1 = 0xfD;  /* TH1:  reload value for 9600 baud */
  TR1 = 1;  /* TR1:  timer 1 run */

  return;
  
} /* initTimer1 */

/***********************************************************************

  Name: initTimer2
    
  Purpose: The purpose of this function is to initialize timer 2
  in the Pinewood Derby system.
    
  Calling Sequence: initTimer2()
    
  Inputs:
    
    None.
    
  Outputs:
    
    None. 
      
***********************************************************************/
void initTimer2(void)
{

  /* set up as a 16-bit up counter with auto reload   */
  /* since RCLK,TCLK = 0, timer 1 is used as the baud */
  /* rate generator for the serial interface          */
  T2CON = 0x00;
  T2MOD = 0x02;
  
  /* set up value to reload upon overflow - 1ms tick */
  RCAP2H = 0xf5;
  RCAP2L = 0x33;
  
  /* set up initial value - 1ms tick */
  TH2 = 0xf5;
  TL2 = 0x33;
  
  /* enable timer */
  TR2 = 1;
  
  return;
  
} /* initTimer2 */

/***********************************************************************

  Name: initPca
    
  Purpose: The purpose of this function is to initialize the 
  programmable counter array in the Pinewood Derby system.
    
  Calling Sequence: initPca()
    
  Inputs:
    
    None.
    
  Outputs:
  
    None. 
    
***********************************************************************/
void initPca(void)
{

  /* Set Up Clocking Source */
  CMOD = 0x06;
  
  /* Set Up PCA inputs 0 thru 3 for Capture on rising edge w/ Interrupt */
  CCAPM0 = 0x21;
  CCAPM1 = 0x21;
  CCAPM2 = 0x21;
  CCAPM3 = 0x21;
  
  return;
  
} /* initPca */

/***********************************************************************

  Name: initInterruptController
    
  Purpose: The purpose of this function is to initialize the 
  interrupt controller in the Pinewood Derby system.
    
  Calling Sequence: initInterruptController()
    
  Inputs:
    
    None.
    
  Outputs:
  
    None. 
    
***********************************************************************/
void initInterruptController(void)
{

  /* give PCA interrupts high priority */
  PPC = 1;
  
  /* enable interrupts by seting the global enable bit */
  EA = 1;
  
  /* enable PCA interrupts */
  EC = 1;
  
  /* enable timer 0 interrupts */
  ET0 = 1;

  return;
  
} /* initInterruptController */

/***********************************************************************

  Name: resetPca
    
  Purpose: The purpose of this function is to reset the 
  programmable counter array in the Pinewood Derby system.
    
  Calling Sequence: resetPca()
    
  Inputs:
    
    None.
  
  Outputs:
  
    None. 
      
***********************************************************************/
void resetPca(void)
{

  /* Turn off PCA Timer */
  CR = 0;

  /* Set Count to 0x00 */
  CL = 0x0;
  CH = 0x0;
   
  return;
   
} /* resetPca */

/***********************************************************************

  Name: startPca
  
  Purpose: The purpose of this function is to start the 
  programmable counter array in the Pinewood Derby system.
  
  Calling Sequence: startPca()
  
  Inputs:
  
    None.
  
  Outputs:
  
    None. 
      
***********************************************************************/
void startPca(void)
{

  /* Set Up PCA inputs 0 thru 3 for Capture on rising edge w/ Interrupt */
  CCAPM0 = 0x21;
  CCAPM1 = 0x21;
  CCAPM2 = 0x21;
  CCAPM3 = 0x21;
  
  /* enable counter */
  CR = 1;
  
  return;
  
} /* startPca */

/***********************************************************************

  Name: pcaIsr
  
  Purpose: The purpose of this function is handle capture interrupts
  from the programmable counter array in the Pinewood Derby system.
    
  Calling Sequence: pcaIsr()
  
  Inputs:
  
    None.
  
  Outputs:
  
    None. 
      
***********************************************************************/
void pcaIsr(void) interrupt 6 using 2
{
  
  if ((CCON & 0x01) != 0)
  { /* lane 1 */
    /* disable capture register */
    CCAPM0 = 0x00;
    /* save counter value */
    captureLow0 = CCAP0L;
    captureHigh0 = CCAP0H;
    /* update status to indicate that lane 1 is finished */
    raceStatus |= 1;
    /* clear interrupt flag */
    CCF0 = 0;
  } /* if */
      
  if ((CCON & 0x02) != 0)
  { /* lane 2 */
    /* save counter value */
    captureLow1 = CCAP1L;
    captureHigh1 = CCAP1H;
    /* disable capture register */
    CCAPM1 = 0x00;
    /* update status to indicate that lane 2 is finished */
    raceStatus |= 2;
    /* clear interrupt flag */
    CCF1 = 0;
  } /* if */
      
  if ((CCON & 0x04) != 0)
  { /* lane 3 */
    /* save counter value */
    captureLow2 = CCAP2L;
    captureHigh2 = CCAP2H;
    /* disable capture register */
    CCAPM2 = 0x00;
    /* update status to indicate that lane 3 is finished */
    raceStatus |= 4;
    /* clear interrupt flag */
    CCF2 = 0;
  } /* if */
      
  if ((CCON & 0x08) != 0)
  { /* lane 4 */
    /* save counter value */
    captureLow3 = CCAP3L;
    captureHigh3 = CCAP3H;
    /* disable capture register */
    CCAPM3 = 0x00;
    /* update status to indicate that lane 4 is finished */
    raceStatus |= 8;
    /* clear interrupt flag */
    CCF3 = 0;
  } /* if */

  return;

} /* pcaIsr */

/***********************************************************************

  Name: timer0Isr
  
  Purpose: The purpose of this function is handle timer 2 interrupts
  in the Pinewood Derby system.
    
  Calling Sequence: timer0Isr()
  
  Inputs:
  
    None.
  
  Outputs:
  
    None. 
      
***********************************************************************/
void timer0Isr(void) interrupt 1 using 3
{

  /* strobe watchdog */
  WDTCON = 0x1e;
  WDTCON = 0xe1;
   
  return;

} /* timer0Isr */

/***********************************************************************

  Name: keyPressed
  
  Purpose: The purpose of this function is to determine if a key is
  pressed in the Pinewood Derby system.
  
  Calling Sequence: status = keyPressed()
  
  Inputs:
    
    None.
  
  Outputs:
  
    status - The result.  Valid values are,
      TRUE - A key was pressed.
      FALSE - A key was not pressed. 
      
***********************************************************************/
unsigned char keyPressed(void)
{
  unsigned char status;
  
  if (RI == 1)
  { /* a key was pressed */
    status = TRUE;
    RI = 0; /* clear the flag */
  } /* if */
  else
  { /* a key was not pressed */
    status = FALSE;
  } /* else */
  
  return (status);
 
} /* keyPressed */

/***********************************************************************

  Name: startLeverIsReleased
  
  Purpose: The purpose of this function is to determine if the
  start lever has been released in the Pinewood Derby system.
  
  Calling Sequence: status = startLeverIsReleased()
  
  Inputs:
  
    None.
  
  Outputs:
  
    status - The result.  Valid values are,
      TRUE - The start lever was released.
      FALSE - The start lever was not released.
      
***********************************************************************/
unsigned char startLeverIsReleased(void)
{
  unsigned char status;
  
  if ((P3 & 0x04) == 4)
  { /* a key was pressed */
    status = TRUE;
  } /* if */
  else
  { /* a key was not pressed */
    status = FALSE;
  } /* else */
  
  return (status);
 
} /* startLeverIsReleased */
