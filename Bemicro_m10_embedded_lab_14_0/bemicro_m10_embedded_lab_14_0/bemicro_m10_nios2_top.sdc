## Generated SDC file "top.out.sdc"

## Copyright (C) 1991-2014 Altera Corporation. All rights reserved.
## Your use of Altera Corporation's design tools, logic functions 
## and other software and tools, and its AMPP partner logic 
## functions, and any output files from any of the foregoing 
## (including device programming or simulation files), and any 
## associated documentation or information are expressly subject 
## to the terms and conditions of the Altera Program License 
## Subscription Agreement, the Altera Quartus II License Agreement,
## the Altera MegaCore Function License Agreement, or other 
## applicable license agreement, including, without limitation, 
## that your use is for the sole purpose of programming logic 
## devices manufactured by Altera and sold by Altera or its 
## authorized distributors.  Please refer to the applicable 
## agreement for further details.


## VENDOR  "Altera"
## PROGRAM "Quartus II"
## VERSION "Version 14.0.1 Build 205 08/13/2014 Patches 1.01 SJ Full Version"

## DATE    "Wed Sep 03 16:24:01 2014"

##
## DEVICE  "10M08DAF484C8GES"
##


#**************************************************************
# Time Information
#**************************************************************

set_time_format -unit ns -decimal_places 3



#**************************************************************
# Create Clock
#**************************************************************

create_clock -name {altera_reserved_tck} -period 100.000 -waveform { 0.000 50.000 } [get_ports {altera_reserved_tck}]
create_clock -name altera_internal_jtag~TCKUTAP -period 100.000 altera_internal_jtag~TCKUTAP
create_clock -name {SYS_CLK} -period 20.000 -waveform { 0.000 10.000 } [get_ports {SYS_CLK}]
create_clock -name {USER_CLK} -period 41.667 -waveform { 0.000 20.803 } [get_ports {USER_CLK}]


#**************************************************************
# Create Generated Clock
#**************************************************************

create_generated_clock -name {u0|sdram_pll|sd1|pll7|clk[0]} -source [get_pins {u0|sdram_pll|sd1|pll7|inclk[0]}] -duty_cycle 50.000 -multiply_by 1 -master_clock {SYS_CLK} [get_pins {u0|sdram_pll|sd1|pll7|clk[0]}] 
create_generated_clock -name {u0|sdram_pll|sd1|pll7|clk[1]} -source [get_pins {u0|sdram_pll|sd1|pll7|inclk[0]}] -duty_cycle 50.000 -multiply_by 1 -phase -90.000 -master_clock {SYS_CLK} [get_pins {u0|sdram_pll|sd1|pll7|clk[1]}] 
create_generated_clock -name {u0|adc_pll|sd1|pll7|clk[0]} -source [get_pins {u0|adc_pll|sd1|pll7|inclk[0]}] -duty_cycle 50.000 -multiply_by 1 -divide_by 5 -master_clock {SYS_CLK} [get_pins {u0|adc_pll|sd1|pll7|clk[0]}] 


#**************************************************************
# Set Clock Latency
#**************************************************************



#**************************************************************
# Set Clock Uncertainty
#**************************************************************



#**************************************************************
# Set Input Delay
#**************************************************************



#**************************************************************
# Set Output Delay
#**************************************************************



#**************************************************************
# Set Clock Groups
#**************************************************************

set_clock_groups -asynchronous -group [get_clocks {altera_reserved_tck}] 


#**************************************************************
# Set False Path
#**************************************************************

set_false_path -from [get_registers {*|alt_jtag_atlantic:*|jupdate}] -to [get_registers {*|alt_jtag_atlantic:*|jupdate1*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|rdata[*]}] -to [get_registers {*|alt_jtag_atlantic*|td_shift[*]}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|read}] -to [get_registers {*|alt_jtag_atlantic:*|read1*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|read_req}] 
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|rvalid}] -to [get_registers {*|alt_jtag_atlantic*|td_shift[*]}]
set_false_path -from [get_registers {*|t_dav}] -to [get_registers {*|alt_jtag_atlantic:*|tck_t_dav}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|user_saw_rvalid}] -to [get_registers {*|alt_jtag_atlantic:*|rvalid0*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|wdata[*]}] -to [get_registers *]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write}] -to [get_registers {*|alt_jtag_atlantic:*|write1*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write_stalled}] -to [get_registers {*|alt_jtag_atlantic:*|t_ena*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write_stalled}] -to [get_registers {*|alt_jtag_atlantic:*|t_pause*}]
set_false_path -from [get_registers {*|alt_jtag_atlantic:*|write_valid}] 
set_false_path -from [get_registers {*altera_avalon_st_clock_crosser:*|in_data_buffer*}] -to [get_registers {*altera_avalon_st_clock_crosser:*|out_data_buffer*}]
set_false_path -to [get_keepers {*altera_std_synchronizer:*|din_s1}]
set_false_path -to [get_pins -nocase -compatibility_mode {*|alt_rst_sync_uq1|altera_reset_synchronizer_int_chain*|clrn}]
set_false_path -from [get_registers {*altera_jtag_src_crosser:*|sink_data_buffer*}] -to [get_registers {*altera_jtag_src_crosser:*|src_data*}]
set_false_path -from [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_nios2_oci_break:the_nios_system_cpu_nios2_oci_break|break_readreg*}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_tck:the_nios_system_cpu_jtag_debug_slave_tck|*sr*}]
set_false_path -from [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_nios2_oci_debug:the_nios_system_cpu_nios2_oci_debug|*resetlatch}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_tck:the_nios_system_cpu_jtag_debug_slave_tck|*sr[33]}]
set_false_path -from [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_nios2_oci_debug:the_nios_system_cpu_nios2_oci_debug|monitor_ready}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_tck:the_nios_system_cpu_jtag_debug_slave_tck|*sr[0]}]
set_false_path -from [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_nios2_oci_debug:the_nios_system_cpu_nios2_oci_debug|monitor_error}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_tck:the_nios_system_cpu_jtag_debug_slave_tck|*sr[34]}]
set_false_path -from [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_nios2_ocimem:the_nios_system_cpu_nios2_ocimem|*MonDReg*}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_tck:the_nios_system_cpu_jtag_debug_slave_tck|*sr*}]
set_false_path -from [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_tck:the_nios_system_cpu_jtag_debug_slave_tck|*sr*}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_sysclk:the_nios_system_cpu_jtag_debug_slave_sysclk|*jdo*}]
set_false_path -from [get_keepers {sld_hub:*|irf_reg*}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_jtag_debug_slave_wrapper:the_nios_system_cpu_jtag_debug_slave_wrapper|nios_system_cpu_jtag_debug_slave_sysclk:the_nios_system_cpu_jtag_debug_slave_sysclk|ir*}]
set_false_path -from [get_keepers {sld_hub:*|sld_shadow_jsm:shadow_jsm|state[1]}] -to [get_keepers {*nios_system_cpu:*|nios_system_cpu_nios2_oci:the_nios_system_cpu_nios2_oci|nios_system_cpu_nios2_oci_debug:the_nios_system_cpu_nios2_oci_debug|monitor_go}]


#**************************************************************
# Set Multicycle Path
#**************************************************************



#**************************************************************
# Set Maximum Delay
#**************************************************************



#**************************************************************
# Set Minimum Delay
#**************************************************************



#**************************************************************
# Set Input Transition
#**************************************************************

