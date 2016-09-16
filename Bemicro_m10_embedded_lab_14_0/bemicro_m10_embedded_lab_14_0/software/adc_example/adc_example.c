/*
 * adc_example.c
 *
 */

#include <stdio.h>
#include "alt_types.h"
#include "system.h"
//#include "altera_adc.h"
#include "altera_modular_adc.h"
#include "altera_modular_adc_sample_store_regs.h"
#include "altera_modular_adc_sequencer_regs.h"
#include <altera_avalon_pio_regs.h>



#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

//GLOBAL variable
int alarm_rang=0;
static int alarm_counter = 0;

alt_u32 my_alarm_callback (void* context)
{
	// set the alarm_rang flag every 3 seconds
	if((alarm_counter++)%3==0)
		alarm_rang=1;
	return alt_ticks_per_second(); // return value is the time when the next alarm will occur
}



int main()
{
  printf("adc_example.c\n\n");

  static alt_alarm alarm;
  int i;
  int loop_count;

  alt_u32 *adc_data;
  alt_u32 *adc_sequencer;

  adc_sequencer = (alt_u32 *)MODULAR_ADC_SEQUENCER_CSR_BASE;
  adc_data = (alt_u32 *)MODULAR_ADC_SAMPLE_STORE_CSR_BASE;

  printf("MODULAR_ADC_SAMPLE_STORE_CSR_BASE: 0x%08X\n",MODULAR_ADC_SAMPLE_STORE_CSR_BASE);
  printf("MODULAR_ADC_SEQUENCER_CSR_BASE: 0x%08X\n",MODULAR_ADC_SEQUENCER_CSR_BASE);

  adc_sequencer[0] = 0x01;
  printf("Set the GO-bit (adc_sequencer[0]): 0x%04X\n",adc_sequencer[0]);
  printf("***********************\n\n");


  alt_alarm_start (&alarm,  alt_ticks_per_second(),  my_alarm_callback, NULL);


  printf("ADC Data\n");
  for(loop_count=1;loop_count<9; loop_count++)
	  {
	  while(alarm_rang==0); // wait until the timeout occurs

	  alarm_rang = 0;
	  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,loop_count);
	  printf("\nSample %02d\n",loop_count);
	  for (i=0; i<18; i++)
		  printf("CH%02d : 0x%04X\n", i+1, (adc_data[i])&0x0FFF);
	  }



  printf("Done\n");

  return 0;
  //*/
}


