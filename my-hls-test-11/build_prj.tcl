# To run: vivado_hls -f build_prj.tcl

set please_reset 1

# Create project
if {$please_reset} {
  open_project -reset myproject_prj
} else {
  open_project myproject_prj
}
set_top myproject
add_files firmware/myproject.cpp -cflags "-std=c++0x -fno-builtin" -csimflags "-Wall -Wno-unused-label"
add_files -tb myproject_test.cpp -cflags "-std=c++0x -fno-builtin" -csimflags "-Wall -Wno-unused-label"
add_files -tb firmware/weights
add_files -tb tb_data

# Configure as Virtex-7, 240 MHz
if {$please_reset} {
  open_solution -reset "solution1"
} else {
  open_solution "solution1"
}
set_part {xc7vx690tffg1927-2}
create_clock -period 4.16667 -name default

# Do stuff
puts "***** C SIMULATION *****"
csim_design

puts "***** C SYNTHESIS *****"
csynth_design
puts "See report: myproject_prj/solution1/syn/report/myproject_csynth.rpt"

#puts "***** C/RTL COSIMULATION *****"
#cosim_design -trace_level all
#puts "See report: myproject_prj/solution1/sim/report/myproject_cosim.rpt"

#puts "***** EXPORT RTL *****"
#export_design -format ip_catalog

exit
