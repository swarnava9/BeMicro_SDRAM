/*
 * accelerometer_example.c
 * -> this program works (much) better using the Nios II Command Shell.
 *    Here are the commands to cut-and-paste:
 *    nios2-download -r -g accelerator_example.elf;nios2-terminal
 *
 *
 * int alt_avalon_spi_command(
 * 	alt_u32 base,
 * 	alt_u32 slave,
 * 	alt_u32 write_length,
 * 	const alt_u8* wdata,
 * 	alt_u32 read_length,
 * 	alt_u8* read_data,
 * 	alt_u32 flags)
 *
 *
 * NOTE:  By default slave_select[0] is enabled/selected so there is no code explicitly setting the CS number.
 * 			This is ok because there is only one SPI slave, located at location 0
 *
 * ADXL362 commands, pulled from datasheet:
 *   write command = 0x0A
 *   read command  = 0x0B
 *   FIFO command  = 0x0D
 *
 */

#include <stdio.h>
#include <altera_avalon_spi.h>
#include <altera_avalon_spi_regs.h>
#include <altera_avalon_pio_regs.h>
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include "system.h"

//GLOBAL variable
int alarm_rang=0;

//defines
#define WRITE_COMMAND 0x0A
#define READ_COMMAND 0x0B
#define FIFO_COMMAND 0x0D

alt_u32 my_alarm_callback (void* context)
{
	/* This function is called twice per second */
	alarm_rang=1;
	return alt_ticks_per_second()/2; // return value is the time when the next alarm will occur
}



//http://www.alterawiki.com/wiki/Spi_core
//This is the ISR that runs when the SPI Slave receives data
static void spi_rx_isr(void* isr_context){

	alt_printf("ISR :) %x \n" ,  IORD_ALTERA_AVALON_SPI_RXDATA(SPI_ACCELEROMETER_BASE));

        //This resets the IRQ flag. Otherwise the IRQ will continuously run.
	IOWR_ALTERA_AVALON_SPI_STATUS(SPI_ACCELEROMETER_BASE, 0x0);

}


typedef struct mystruct {
		alt_u8 x;
		alt_u8 y;
		alt_u8 z;
} ACCELEROMETER;

int main()
{
	ACCELEROMETER accel_data;

	static alt_alarm alarm;
	int return_code,ret;
	alt_u8 spi_command_tx[2] = {0x0B, 0x00}; //, 0x00, 0x00}; // read one register from address 0x00
	alt_u8 spi_command_rx[4] = {0xB,0,0,0};


  /******************************************************
   * Start the Accelerometer by writing to the'Go' bit  *
   ******************************************************/

	printf("Starting up the accelerometer...\n\n");

  spi_command_tx[0] = WRITE_COMMAND; // write command
  spi_command_tx[1] = 0x2D; // Address 0x2D (go bit location)
  spi_command_tx[2] = 0x02; // go bit value

  alt_avalon_spi_command( SPI_ACCELEROMETER_BASE, 0,
                          3, spi_command_tx,
                          0, spi_command_rx,
                          0);

  alt_alarm_start (&alarm,  alt_ticks_per_second()/2,  my_alarm_callback, NULL);

  printf("xx yy zz\n");
  while(1)
	  if(alarm_rang==1)
	  {
		  alarm_rang=0;

		  /******************************************************
		   * Read the Accelerometer data registers			    *
		   ******************************************************/
		  spi_command_tx[0] = READ_COMMAND; // read command
		  spi_command_tx[1] = 0x08; // Address of the data registers

		  alt_avalon_spi_command( SPI_ACCELEROMETER_BASE, 0,
								  2, spi_command_tx,
								  3, &accel_data,
								  0);


		  /* this print command works much better using the Nios II Command Shell
		   *  because the data will overwrite the previous sample.
		   *
		   *  The Eclipse console does not support backspace and therefore the data appends
		   *  which makes it more difficult to read
		   */

		  printf("\b\b\b\b\b\b\b\b%02X %02X %02X",accel_data.x, accel_data.y, accel_data.z);
		  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,accel_data.x); // update the LEDs with the x-axis


	  }

  return 0;

}
