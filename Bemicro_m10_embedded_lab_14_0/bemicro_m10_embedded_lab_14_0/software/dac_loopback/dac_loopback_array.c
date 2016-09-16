/*
 * dac_loopback.c
 * -limitations:  The SPI master can only send 8-bits.  when the peripheral is set to 24-bits, three transactions occur,
 * 				  each transferring 8-bits but note 24 clocks long.  Changing the SPI to an 8-bit slave and using the
 * 				  flag: ALT_AVALON_SPI_COMMAND_MERGE, allows us to concat three 8-bit transactions together
 *
 */

#include <stdio.h>
#include "alt_types.h"
#include "system.h"
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
	// set the alarm_rang flag every 1 second
	if((alarm_counter++)%1==0)
		alarm_rang=1;
	return alt_ticks_per_second(); // return value is the time when the next alarm will occur
}



int main()
{
  printf("dac_loopback.c\n\n");

  static alt_alarm alarm;
  int i;
  int loop_count;

  alt_u32 *adc_data = (alt_u32 *)MODULAR_ADC_SAMPLE_STORE_CSR_BASE;
  alt_u32 *adc_sequencer = (alt_u32 *)MODULAR_ADC_SEQUENCER_CSR_BASE;

  alt_u8 spi_command_tx[3] = {0x00, 0x00, 0x00};

  alt_u8 output_array[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F};

  printf("Start the ADC by setting the run flag\n");
  adc_sequencer[0] = 0x01;

  /***************************************************************************************
   * Setup the DAC registers 															 *
   ***************************************************************************************/

  // write the control register, address: 0x4
  //  value: 0x00000 (20-bits wide) [DB19:DB0]
  // (this action is redundant because the part is reset to these values)

	spi_command_tx[0] = 0x40; // [CMD3:CMD0] [DB19:DB16] write control register address (first four bits are command)
	spi_command_tx[1] = 0x00; // [DB15:DB8]
	spi_command_tx[2] = 0x00; // [DB7:DB0] // this byte is ignored on the AD5681


	printf("Setting up the DAC control register...");


	alt_avalon_spi_command( SPI_AD5681_BASE, 0,
							3, spi_command_tx,		// write 3 bytes from the data buffer pointed to by spi_command_tx
							//0, spi_command_rx,
							0, NULL,
							0);


	printf("...Done!\n\n");


  /***************************************************************************************
   * Start the alarm callback to capture the adc registers after a one-second timeout  *
   ***************************************************************************************/

  alt_alarm_start (&alarm,  alt_ticks_per_second(),  my_alarm_callback, NULL);

  /***************************************************************************************
   * Print out the samples of the ADC Data												 *
   ***************************************************************************************/

  for(loop_count=1;loop_count<=16; loop_count++)
	  {
	  while(alarm_rang==0); // wait until the timeout occurs

	// setup the DAC output values by going through an array of output values.
		spi_command_tx[0] = output_array[loop_count-1]; // [CMD3:CMD0] [DB19:DB16]; write control register address (first four bits are command)
		spi_command_tx[1] = 0x00; // [DB15:DB8]
		spi_command_tx[2] = 0x00; // [DB7:DB0] this byte is ignored on the AD5681

	// update the DAC output
		alt_avalon_spi_command( SPI_AD5681_BASE, 0,
								2, spi_command_tx,		// short write of 16-bits
								0, NULL,
								0);

	/* Consider adding a delay to allow the ADC to settle after the DAC changes its value */
	  alarm_rang = 0;
	  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,loop_count);
	  printf("\nDAC output: 0x%01X%02X\n",0x0F&spi_command_tx[0],spi_command_tx[1]); // strip off the upper nibble when printing

	  printf("AIN1 : 0x%03X\n", (adc_data[0])&0x0FFF);
	  printf("AIN2 : 0x%03X\n", (adc_data[8])&0x0FFF);

	  }



  printf("\nDone sampling ADC data\n");

  return 0;
}


