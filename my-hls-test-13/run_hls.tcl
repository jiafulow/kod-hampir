# To run: vivado_hls -f run_hls.tcl

set PROJ "myproject_prj"
set SOLN "solution1"
set XPART xc7vx690tffg1927-2
set CLKP 160MHz
set CFLAGS "-std=c++11"
set CSIMFLAGS "-Wall -Wextra -Wno-ignored-attributes -Wno-unused-parameter -Wno-unused-variable -Wno-unused-label"
set CSIM 1
set CSYNTH 1
set COSIM 0
set VIVADO_SYN 0
set VIVADO_IMPL 0


# ########################################################
# Create a project
open_project -reset $PROJ
add_files firmware/myproject.cpp -cflags $CFLAGS -csimflags $CSIMFLAGS
add_files -tb myproject_test.cpp -cflags $CFLAGS -csimflags $CSIMFLAGS
add_files -tb tb_data
set_top myproject

# ########################################################
# Create a solution
open_solution -reset $SOLN
set_part $XPART
create_clock -period $CLKP

# Set any optimization directives
config_compile -pipeline_loops 64
config_array_partition -auto_partition_threshold 32 -auto_promotion_threshold 64
config_array_partition -include_extern_globals
config_interface -trim_dangling_port
# End of directives

# ########################################################
# Execute
if {$CSIM == 1} {
  csim_design 
}

if {$CSYNTH == 1} {
  csynth_design
}

if {$COSIM == 1} {
  cosim_design 
}

if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}

if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog
}

exit
