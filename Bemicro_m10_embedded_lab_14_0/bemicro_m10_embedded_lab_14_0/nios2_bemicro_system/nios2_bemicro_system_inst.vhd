	component nios2_bemicro_system is
		port (
			adc_pll_areset_conduit_export   : in    std_logic                     := 'X';             -- export
			button_pio_external_export      : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			clk_clk                         : in    std_logic                     := 'X';             -- clk
			i2c_temp_sense_scl_pad_io       : inout std_logic                     := 'X';             -- scl_pad_io
			i2c_temp_sense_sda_pad_io       : inout std_logic                     := 'X';             -- sda_pad_io
			led_pio_external_export         : out   std_logic_vector(7 downto 0);                     -- export
			reset_reset_n                   : in    std_logic                     := 'X';             -- reset_n
			sdram_addr                      : out   std_logic_vector(11 downto 0);                    -- addr
			sdram_ba                        : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_cas_n                     : out   std_logic;                                        -- cas_n
			sdram_cke                       : out   std_logic;                                        -- cke
			sdram_cs_n                      : out   std_logic;                                        -- cs_n
			sdram_dq                        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_dqm                       : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_ras_n                     : out   std_logic;                                        -- ras_n
			sdram_we_n                      : out   std_logic;                                        -- we_n
			sdram_pll_80shift_clk           : out   std_logic;                                        -- clk
			sdram_pll_areset_conduit_export : in    std_logic                     := 'X';             -- export
			sdram_pll_locked_conduit_export : out   std_logic;                                        -- export
			spi_accelerometer_MISO          : in    std_logic                     := 'X';             -- MISO
			spi_accelerometer_MOSI          : out   std_logic;                                        -- MOSI
			spi_accelerometer_SCLK          : out   std_logic;                                        -- SCLK
			spi_accelerometer_SS_n          : out   std_logic;                                        -- SS_n
			spi_dac_MISO                    : in    std_logic                     := 'X';             -- MISO
			spi_dac_MOSI                    : out   std_logic;                                        -- MOSI
			spi_dac_SCLK                    : out   std_logic;                                        -- SCLK
			spi_dac_SS_n                    : out   std_logic                                         -- SS_n
		);
	end component nios2_bemicro_system;

	u0 : component nios2_bemicro_system
		port map (
			adc_pll_areset_conduit_export   => CONNECTED_TO_adc_pll_areset_conduit_export,   --   adc_pll_areset_conduit.export
			button_pio_external_export      => CONNECTED_TO_button_pio_external_export,      --      button_pio_external.export
			clk_clk                         => CONNECTED_TO_clk_clk,                         --                      clk.clk
			i2c_temp_sense_scl_pad_io       => CONNECTED_TO_i2c_temp_sense_scl_pad_io,       --           i2c_temp_sense.scl_pad_io
			i2c_temp_sense_sda_pad_io       => CONNECTED_TO_i2c_temp_sense_sda_pad_io,       --                         .sda_pad_io
			led_pio_external_export         => CONNECTED_TO_led_pio_external_export,         --         led_pio_external.export
			reset_reset_n                   => CONNECTED_TO_reset_reset_n,                   --                    reset.reset_n
			sdram_addr                      => CONNECTED_TO_sdram_addr,                      --                    sdram.addr
			sdram_ba                        => CONNECTED_TO_sdram_ba,                        --                         .ba
			sdram_cas_n                     => CONNECTED_TO_sdram_cas_n,                     --                         .cas_n
			sdram_cke                       => CONNECTED_TO_sdram_cke,                       --                         .cke
			sdram_cs_n                      => CONNECTED_TO_sdram_cs_n,                      --                         .cs_n
			sdram_dq                        => CONNECTED_TO_sdram_dq,                        --                         .dq
			sdram_dqm                       => CONNECTED_TO_sdram_dqm,                       --                         .dqm
			sdram_ras_n                     => CONNECTED_TO_sdram_ras_n,                     --                         .ras_n
			sdram_we_n                      => CONNECTED_TO_sdram_we_n,                      --                         .we_n
			sdram_pll_80shift_clk           => CONNECTED_TO_sdram_pll_80shift_clk,           --        sdram_pll_80shift.clk
			sdram_pll_areset_conduit_export => CONNECTED_TO_sdram_pll_areset_conduit_export, -- sdram_pll_areset_conduit.export
			sdram_pll_locked_conduit_export => CONNECTED_TO_sdram_pll_locked_conduit_export, -- sdram_pll_locked_conduit.export
			spi_accelerometer_MISO          => CONNECTED_TO_spi_accelerometer_MISO,          --        spi_accelerometer.MISO
			spi_accelerometer_MOSI          => CONNECTED_TO_spi_accelerometer_MOSI,          --                         .MOSI
			spi_accelerometer_SCLK          => CONNECTED_TO_spi_accelerometer_SCLK,          --                         .SCLK
			spi_accelerometer_SS_n          => CONNECTED_TO_spi_accelerometer_SS_n,          --                         .SS_n
			spi_dac_MISO                    => CONNECTED_TO_spi_dac_MISO,                    --                  spi_dac.MISO
			spi_dac_MOSI                    => CONNECTED_TO_spi_dac_MOSI,                    --                         .MOSI
			spi_dac_SCLK                    => CONNECTED_TO_spi_dac_SCLK,                    --                         .SCLK
			spi_dac_SS_n                    => CONNECTED_TO_spi_dac_SS_n                     --                         .SS_n
		);

