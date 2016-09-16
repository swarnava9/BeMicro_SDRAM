	nios2_bemicro_system u0 (
		.adc_pll_areset_conduit_export   (<connected-to-adc_pll_areset_conduit_export>),   //   adc_pll_areset_conduit.export
		.button_pio_external_export      (<connected-to-button_pio_external_export>),      //      button_pio_external.export
		.clk_clk                         (<connected-to-clk_clk>),                         //                      clk.clk
		.i2c_temp_sense_scl_pad_io       (<connected-to-i2c_temp_sense_scl_pad_io>),       //           i2c_temp_sense.scl_pad_io
		.i2c_temp_sense_sda_pad_io       (<connected-to-i2c_temp_sense_sda_pad_io>),       //                         .sda_pad_io
		.led_pio_external_export         (<connected-to-led_pio_external_export>),         //         led_pio_external.export
		.reset_reset_n                   (<connected-to-reset_reset_n>),                   //                    reset.reset_n
		.sdram_addr                      (<connected-to-sdram_addr>),                      //                    sdram.addr
		.sdram_ba                        (<connected-to-sdram_ba>),                        //                         .ba
		.sdram_cas_n                     (<connected-to-sdram_cas_n>),                     //                         .cas_n
		.sdram_cke                       (<connected-to-sdram_cke>),                       //                         .cke
		.sdram_cs_n                      (<connected-to-sdram_cs_n>),                      //                         .cs_n
		.sdram_dq                        (<connected-to-sdram_dq>),                        //                         .dq
		.sdram_dqm                       (<connected-to-sdram_dqm>),                       //                         .dqm
		.sdram_ras_n                     (<connected-to-sdram_ras_n>),                     //                         .ras_n
		.sdram_we_n                      (<connected-to-sdram_we_n>),                      //                         .we_n
		.sdram_pll_80shift_clk           (<connected-to-sdram_pll_80shift_clk>),           //        sdram_pll_80shift.clk
		.sdram_pll_areset_conduit_export (<connected-to-sdram_pll_areset_conduit_export>), // sdram_pll_areset_conduit.export
		.sdram_pll_locked_conduit_export (<connected-to-sdram_pll_locked_conduit_export>), // sdram_pll_locked_conduit.export
		.spi_accelerometer_MISO          (<connected-to-spi_accelerometer_MISO>),          //        spi_accelerometer.MISO
		.spi_accelerometer_MOSI          (<connected-to-spi_accelerometer_MOSI>),          //                         .MOSI
		.spi_accelerometer_SCLK          (<connected-to-spi_accelerometer_SCLK>),          //                         .SCLK
		.spi_accelerometer_SS_n          (<connected-to-spi_accelerometer_SS_n>),          //                         .SS_n
		.spi_dac_MISO                    (<connected-to-spi_dac_MISO>),                    //                  spi_dac.MISO
		.spi_dac_MOSI                    (<connected-to-spi_dac_MOSI>),                    //                         .MOSI
		.spi_dac_SCLK                    (<connected-to-spi_dac_SCLK>),                    //                         .SCLK
		.spi_dac_SS_n                    (<connected-to-spi_dac_SS_n>)                     //                         .SS_n
	);

