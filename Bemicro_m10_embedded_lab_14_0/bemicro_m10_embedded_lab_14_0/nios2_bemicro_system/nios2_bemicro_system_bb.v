
module nios2_bemicro_system (
	adc_pll_areset_conduit_export,
	button_pio_external_export,
	clk_clk,
	i2c_temp_sense_scl_pad_io,
	i2c_temp_sense_sda_pad_io,
	led_pio_external_export,
	reset_reset_n,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_pll_80shift_clk,
	sdram_pll_areset_conduit_export,
	sdram_pll_locked_conduit_export,
	spi_accelerometer_MISO,
	spi_accelerometer_MOSI,
	spi_accelerometer_SCLK,
	spi_accelerometer_SS_n,
	spi_dac_MISO,
	spi_dac_MOSI,
	spi_dac_SCLK,
	spi_dac_SS_n);	

	input		adc_pll_areset_conduit_export;
	input	[3:0]	button_pio_external_export;
	input		clk_clk;
	inout		i2c_temp_sense_scl_pad_io;
	inout		i2c_temp_sense_sda_pad_io;
	output	[7:0]	led_pio_external_export;
	input		reset_reset_n;
	output	[11:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[15:0]	sdram_dq;
	output	[1:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_pll_80shift_clk;
	input		sdram_pll_areset_conduit_export;
	output		sdram_pll_locked_conduit_export;
	input		spi_accelerometer_MISO;
	output		spi_accelerometer_MOSI;
	output		spi_accelerometer_SCLK;
	output		spi_accelerometer_SS_n;
	input		spi_dac_MISO;
	output		spi_dac_MOSI;
	output		spi_dac_SCLK;
	output		spi_dac_SS_n;
endmodule
