############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project new_project
set_top main
add_files tb.cpp
add_files main.cpp
add_files -tb tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xczu7ev-ffvf1517-3-e}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog -vivado_clock 10
set_clock_uncertainty 0
source "./new_project/solution1/directives.tcl"
csim_design -clean -setup
csynth_design
cosim_design
export_design -flow impl -rtl verilog -format ip_catalog
