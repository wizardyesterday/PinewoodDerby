#include <stdio.h>
#include <stdlib.h>

struct scoreEntry
{
  unsigned short carNumber;
  unsigned short score;
};

struct scoreEntry scoreList[100];

void sort(int l, int r);

/**************************************************************************

  Name: main

  Purpose: The purpose of this function is to provide the mainline portion
  of code required for accumulating and sorting scores.

  Invocation: score <infile >outfile

  Inputs:

    infile - The input data defaulted to standard input.  The format of the
    data is described below.

    count
    carNumber score
    carNumber score
      .
      .
      .
    carNumber score

    carNumber - A car number.
    score - The score associated with the car number.

  Outputs:

    outfile - The sorted output data defaulted to standard input.  The format
    of the data is described below.

    carNumber score
    carNumber score
      .
      .
      .
    carNumber score

    carNumber - A car number.
    score - The score associated with the car number.


**************************************************************************/
main()
{
  char *consoleStatus, consoleBuffer[100];
  unsigned int i, n, score;
  float dscore;
 
  for (i = 0; i < 100; i++)
  {
    scoreList[i].carNumber = i;
    scoreList[i].score = 0;
  } /* for */

  /* get parameters */
  consoleStatus = gets(consoleBuffer); /* get data from standard input */
  sscanf(consoleBuffer,"%d",&n);

  do
  {
    consoleStatus = gets(consoleBuffer); /* get data from standard input */
    if (consoleStatus != NULL)
    {
      sscanf(consoleBuffer,"%d %d",&i,&score);
      scoreList[i].score += score;
    } /* if */
  } while (consoleStatus != NULL);

  /* sort our scores */
  sort(1,n);

  printf("**************************\n");
  printf("| Car Number | Time (s)  |\n");
  printf("**************************\n");

  for (i = 1; i <= n; i++)
  {
    dscore = (float)scoreList[i].score;
    dscore /= 1000;
    printf("|     %2u     |  %6.3f   |\n",
            scoreList[i].carNumber,dscore);
    printf("++++++++++++++++++++++++++\n");
  } /* for */

} /* main */

/**************************************************************************

  Name: sort

  Purpose: The purpose of this function is to sort all channels in
  the channel attribute list in ascending order of score.
  
  Calling Sequence: sort(l,r)

  Inputs:

    l - The left partition of the array to be sorted.

    r - The right partition of the array to be sorted.

  Outputs:

    None.

**************************************************************************/

void sort(int l, int r)
{
  volatile int i, j;
  volatile struct scoreEntry x, w;

  i = l;
  j = r;
  x = scoreList[(l + r) / 2];

  do
  {
    while (scoreList[i].score < x.score)
    {
      i = i + 1;
    } /* while */
    while (x.score < scoreList[j].score)
    {
      j = j - 1;
    } /* while */
    if (i <= j)
    {
      w = scoreList[i];
      scoreList[i] = scoreList[j];
      scoreList[j] = w;
      i = i + 1;
      j = j - 1;
    } /* if */
  } while (i <= j);
  if (l < j)
  {
    sort(l,j);
  } /* if */
  if (i < r)
  {
    sort(i,r);
  } /* if */

  return;

} /* sort */
