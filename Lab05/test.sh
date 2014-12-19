#!/bin/bash

if [ "$1" != "clean_only" ]; then
    make clean
    make
    insmod hello_module.ko
    insmod module_a.ko
    insmod module_b.ko
    insmod module_c.ko v_new=50
    rmmod module_c
    insmod module_c.ko v_new=100
    rmmod module_c
    insmod module_c.ko v_new=120
    echo "Next step will enter less mode, input 'G' to directly scroll to bottom. [Press enter to continue]"
    read whatever
    dmesg | less
fi

# clean up...

rmmod module_c
rmmod module_b
rmmod module_a
rmmod hello_module
rm *.o
rm *.mod.c
rm *.ko
rm .*.cmd
rm -Rvf .tmp_versions
rm modules.order Module.symvers 

echo "Done!"
