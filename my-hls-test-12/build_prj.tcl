# To run: vivado_hls -f build_prj.tcl

set please_reset 1

set_param general.maxThreads 8

# Create a project and add files
if {$please_reset} {
  open_project -reset myproject_prj
} else {
  open_project myproject_prj
}
set_top myproject
add_files firmware/myproject.cpp -cflags "-std=c++0x" -csimflags "-Wall -Wno-unused-label"
add_files -tb myproject_test.cpp -cflags "-std=c++0x" -csimflags "-Wall -Wno-unused-label"
#add_files -tb firmware/weights
add_files -tb tb_data

# Create a solution. Configured as Virtex-7 690T, 240 MHz
if {$please_reset} {
  open_solution -reset "solution1"
} else {
  open_solution "solution1"
}
set_part {xc7vx690tffg1927-2}
create_clock -period 4.16667 -name default

# ##############################################################
# Set optimization directives
config_array_partition -auto_partition_threshold 8 -auto_promotion_threshold 64 -include_extern_globals
config_interface -trim_dangling_port

# ##############################################################
# Do stuff
puts "@@@ C SIMULATION"
csim_design

puts "@@@ C SYNTHESIS"
csynth_design

#puts "@@@ C/RTL COSIMULATION"
#cosim_design -trace_level all

#puts "@@@ EXPORT RTL"
#export_design -format ip_catalog

exit
