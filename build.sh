#!/usr/bin/env bash

sudo apt-get install -y flex bison libssl-dev build-essential libncurses5-dev libssl-dev libelf-dev

make menuconfig
#./scripts/config --disable CONFIG_SYSTEM_TRUSTED_KEYS

make bzImage modules -j 8

sed -i 's/GRUB_DEFAULT=.*/GRUB_DEFAULT="1 > 4"/g' grub

sudo make module_install install

