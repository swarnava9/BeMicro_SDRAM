/*
 *	serial_flash_example.c
 *
 *	the following define statement is required for the hello_world_small template because the small c library
 *	does not include drivers for the serial flash by default
 *
 *	#define ALT_USE_EPCS_FLASH
 *
 *
 */



#include <stdio.h>
//#include <altera_avalon_epcs_flash_controller.h>
#include <BeMicro_Max10_serial_flash_controller.h>
#include "sys/alt_stdio.h"
#include "system.h"
#include "alt_types.h"
#include "sys/alt_flash.h"


// Definitions
#define WRITE_FLASH 1
#define ERASE_FLASH 0
#define BLOCK_READ 1

#define READ_SIZE 32
#define WRITE_SIZE 512

int main()
{
  alt_flash_fd *fd_sflash;

  flash_region* regions;
  int number_of_regions;

  alt_u8 block_read[READ_SIZE];
  alt_u16 n, block_num;

  alt_putstr("serial_flash_example.c\n\n");

  //fd_sflash = alt_flash_open_dev(EPCS_FLASH_CONTROLLER_NAME);
  fd_sflash = alt_flash_open_dev(BEMICRO_MAX10_SERIAL_FLASH_CONTROLLER_0_NAME);
  if(fd_sflash == 0)
  {
    printf("\n\nError opening Flash Device\nError Code: %d\n",fd_sflash);
    return 0;
  }

	/*****************************************
	* Display some useful information about  *
	* the spi_flash connected to the system  *
	******************************************/
	alt_get_flash_info(fd_sflash, &regions, &number_of_regions);
	printf("Flash Info for Serial Flash:\n");
	printf("Number of regions:  %d\n",number_of_regions);
	printf("regions->offset: %d\n",regions->offset);
	printf("regions->region_size: %d MB\n",regions->region_size/1024/1024);
	printf("regions->number_of_blocks: %d\n",regions->number_of_blocks);
	printf("regions->block_size: %d KB\n\n\n",(regions->block_size/1024));


	/*****************************************
	* This section of code erases the entire *
	* spi_flash connected to the system      *
	******************************************/
	#if ERASE_FLASH
		for(n=0;n<regions->number_of_blocks;n++)
		{

			printf("Erasing Block %d...\n);
			if(alt_erase_flash_block(fd_sflash,regions->block_size*n,regions->block_size)==0)
				printf("Block #%d successfully erased\n",n);
			else
				printf("Erase FAILED at block #%d\n",n);
		}
	#endif


	/*****************************************
	* This section of code writes to a page  *
	* within the spi_flash                   *
	******************************************/

	#if WRITE_FLASH
		alt_u8 source_a[WRITE_SIZE];

		// fill a write buffer with some values we recognize
		for(n=0;n<WRITE_SIZE;n++)
			if(n%8==0)
				source_a[n] = 0xBE;
			else
				source_a[n] = 0xAA;

		alt_putstr("\nNow Writing to the serial flash device...");
		if(alt_write_flash(fd_sflash,0,source_a,WRITE_SIZE)==0) // write to the flash
			alt_putstr("Page 0 written!\n");
		else
			alt_putstr("\nError writing to address 0!\n");

	#endif


	/*****************************************
	* This section of code reads every page  *
	* within the spi_flash                   *
	******************************************/

	#if BLOCK_READ
		printf("\n\n\nNow reading %d bytes from each page of the serial flash:\n",READ_SIZE);

		for(block_num=0;block_num<regions->number_of_blocks;block_num++)
		{
		if(alt_read_flash(fd_sflash,65536*block_num,block_read,READ_SIZE)==0)  // read buf_size bytes
			for(n=0;n<READ_SIZE;n++)
				{
				if(n%16==0)
					printf("\n%08X: ",n+block_num*0x10000);

				printf("%02X ",block_read[n]);
				}
		}

	#endif

	alt_flash_close_dev(fd_sflash);  // close flash device

	printf("\nDone\n");

  return 0;
}
