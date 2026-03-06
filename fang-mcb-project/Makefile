pierce-run-debug:
	scons run robot=TARGET_PIERCE profile=debug -j 64
pierce-debug:
	openocd -f interface/stlink.cfg -f openocd.cfg 2> /dev/null &
	gdb build/hardware/scons-debug/fang-mcb-project.elf -ex "target ext localhost:3333" -ex "breakpoint main()" -tui
	pkill openocd
