/**********************************************************************/
/* file name: derby.h                                                 */
/**********************************************************************/
/******************************************************************/
/* defines                                                        */
/******************************************************************/
#define TRUE 1
#define FALSE 0

/******************************************************************/
/* function prototypes                                            */
/******************************************************************/
extern void initHardware(void);
extern void initParallelPorts(void);
extern void initPca(void);
extern void resetPca(void);
extern void startPca(void);
extern void initTimer0(void);
extern void initTimer1(void);
extern void initTimer2(void);
extern void initUart(void);
extern void initInterruptController(void);
extern void pcaIsr(void) interrupt 6 using 2;
extern void timer0Isr(void) interrupt 1 using 3;

extern void displayTime(unsigned char laneNumber);
extern void rankLanes(void);
extern unsigned char keyPressed(void);
extern unsigned char startLeverIsReleased(void);

/******************************************************************/
/* data structures                                                */
/******************************************************************/
/* status variables */
extern unsigned char raceStatus;

/* capture register values */
extern unsigned char captureLow0;
extern unsigned char captureHigh0;
extern unsigned char captureLow1;
extern unsigned char captureHigh1;
extern unsigned char captureLow2;
extern unsigned char captureHigh2;
extern unsigned char captureLow3;
extern unsigned char captureHigh3;

/* lane ranking array */
extern unsigned char laneRank[];

