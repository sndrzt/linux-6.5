#!/usr/bin/env bash

sudo apt-get install -y flex bison libssl-dev build-essential libncurses5-dev libssl-dev libelf-dev

make menuconfig
#./scripts/config --disable CONFIG_SYSTEM_TRUSTED_KEYS

sudo sed -i 's/GRUB_DEFAULT=.*/GRUB_DEFAULT="1 > 2"/g' /etc/default/grub

date > a.txt
make bzImage modules -j 4
date > b.txt

sudo make modules_install install

