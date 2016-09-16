/*
 * used to test the timer to ensure it works
 *
 * Note: a system timer is required for this design; ensure the bsp-editor has one defined
 */

#include <stdio.h>
#include "system.h"
//#include "sys/alt_timestamp.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

alt_u8 alarm_rang=0;

alt_u32 my_alarm_callback (void* context)
{
	/* This function is called once per second */
	alarm_rang = 1;
	return alt_ticks_per_second(); // return value is the time when the next alarm will occur
}


int main()
{
	static alt_alarm alarm;
	int seconds_passed=0;
  printf("Timer Example code\n");

  // start the alarm to go off once per second
  if (alt_alarm_start (&alarm,  alt_ticks_per_second(),  my_alarm_callback, NULL) < 0)
  {
	  printf ("No system clock available\n");
  }

  while(1)
	  if(alarm_rang==1)
	  {
		  printf("%d ",++seconds_passed);
		  alarm_rang=0;
	  }

  return 0;
}
