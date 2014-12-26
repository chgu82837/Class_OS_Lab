#!/bin/sh
#
# Warning: this part havent been debug! I just write down my bash history!

echo "Warning: You need to find the device for your filesystem, please input your device locaiton (ex: /vda1):"
read device
mount $device /mnt
mount -o remount,mand $device /mnt
echo "cd into /mnt/$(pwd)"
echo "chmod g+s lock.txt"
echo "Exe the ex1 executable!"
