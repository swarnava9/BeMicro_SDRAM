/*
 * ADT7420 temperature sensor reference code.
 *
 */



#include <stdio.h>
#include "../temp_sense_example_bsp/system.h"
#include <alt_types.h>
#include "sys/alt_alarm.h"

#define ADT7420_ADDR 0x48

int alarm_counter=0;
int alarm_rang=0;

alt_u32 one_shot_alarm_callback (void* context)
{
	/* This function is called once */
	alarm_rang=1;
	return alt_ticks_per_second(); // return value is the time when the next alarm will occur
}


alt_u32 read_adc_temp(alt_u32 base);  // a separate function was written to do a two byte read and concat them together.

int main()
{
  static alt_alarm alarm;

  alt_u32 data = 0;
  alt_u32 msb = 0;
  alt_u32 lsb = 0;
  alt_u8 write_return_value;



  printf("Testing the ADT7420 via I2C...\n\n");

//http://www.alteraforum.com/forum/showthread.php?t=38962
  //Initialize I2C master controller at 100kHz, 50MHz Cpu clock.
  I2C_init(I2C_ADT7420_BASE,ALT_CPU_CPU_FREQ,100000);

 /***************************************
  * read the Device ID at offset 0x0B   *
  ***************************************/

  //*
  // Write address that is to be read from
  I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
  I2C_write(I2C_ADT7420_BASE,0x0B,0);		// where 0x0B is the offset to the device id

  // Set the start bit for a read command
  I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,1);
  printf("Device ID: 0x%02X \n",I2C_read(I2C_ADT7420_BASE,1));


  /*****************************************************************
   * reset the ADT7420 by writing to the register at offset 0x2F   *
   *****************************************************************/


   //* Write address that is to be read from
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
   I2C_write(I2C_ADT7420_BASE,0x2F,0);		// where 0x2F is the offset to the reset register
   I2C_write(I2C_ADT7420_BASE, 0x00,1);


   printf("Reseting...");
   //need to wait for 200us for reset to complete (10000 clocks)
    alt_alarm_start (&alarm,  alt_ticks_per_second(),  one_shot_alarm_callback, NULL);

    // this will wait for 5 seconds before moving on
    while(alarm_counter<5)
    	if(alarm_rang == 1)
    	{
    		alarm_counter++;
    		printf(".");
    	}
    printf("\n");


  /****************************************************
   * write the Configuration Register at offset 0x03   *
   ****************************************************/

   //* Write address that is to be read from
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
   I2C_write(I2C_ADT7420_BASE,0x03,0);		// where 0x03 is the offset to the Configuration register
   I2C_write(I2C_ADT7420_BASE, 0x80,1); 	// Set the temp resolution to 16-bits by writing 0x80


  /****************************************************
   * read the Configuration Register at offset 0x03   *
   ****************************************************/

   //* Write address that is to be read from
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
   I2C_write(I2C_ADT7420_BASE,0x03,0);		// where 0x03 is the offset to the Configuration register

   // Set the start bit for a read command
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,1);
   printf("Config Reg: 0x%02X \n",I2C_read(I2C_ADT7420_BASE,1));

  /****************************************************
   * read the Thigh setpoint Register at offset 0x04  *
   ****************************************************/


   /* Write address that is to be read from
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
   I2C_write(I2C_ADT7420_BASE,0x04,0);		// where 0x04 is the offset to the Thigh setpoint register

   // Set the start bit for a read command
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,1);
   printf("Thigh Setpoint Register: 0x%02X \n",I2C_read(I2C_ADT7420_BASE,1));

  /****************************************************
   * write the Thigh Setpoint Register at offset 0x04 *
   ****************************************************/


   /* Write address that is to be read from
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
   I2C_write(I2C_ADT7420_BASE,0x04,0);		// where 0x04 is the offset to the Thigh setpoint register

   // Set the start bit for a read command
   //I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);	// trailing zero indicates a write is occuring
   write_return_value = I2C_write(I2C_ADT7420_BASE, 0x3F,1);
   printf("Thigh Write Return Value = %d\n",write_return_value);




  /****************************************************
   * read the Thigh setpoint Register at offset 0x04  *
   ****************************************************/


   /* Write address that is to be read from
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,0);
   I2C_write(I2C_ADT7420_BASE,0x04,0);		// where 0x04 is the offset to the Thigh setpoint register

   // Set the start bit for a read command
   I2C_start(I2C_ADT7420_BASE,ADT7420_ADDR,1);
   printf("Thigh Setpoint Register: 0x%02X \n",I2C_read(I2C_ADT7420_BASE,1));


  /***************************************
   * read the temperature data		     *
   ***************************************/

  data=read_adc_temp(I2C_ADT7420_BASE);
  printf("\nTemperature Register: 0x%04X\n",data);
  printf("Temperature Value: %d degC\n",data/128);  // divide by 128 because the resolution is set to 16-bits


  return 0;
}

/*
 *  this function reads the two temperature bytes, concatenates them together, and returns them via one 32-bit value
 */
alt_u32 read_adc_temp(alt_u32 base)
{
	alt_u32 msb = 0;
	alt_u32 lsb = 0;

	// Write address that is to be read from
	  I2C_start(base,ADT7420_ADDR,0);
	  I2C_write(base,0x00,0);		// where 0x00 is the offset to the temperature data

	  // Set the start bit for a read command
	  I2C_start(base,ADT7420_ADDR,1);

	  //block reads supported on the temperature data bytes (msb & lsb) where the address auto increments.
	  msb = I2C_read(base,0)<<8;
	  lsb = I2C_read(base,1);// & 0x00FF;


	  return (msb|lsb);
}

