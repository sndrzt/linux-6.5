#!/usr/bin/env bash

sudo apt-get install -y flex bison libssl-dev build-essential libncurses5-dev libssl-dev libelf-dev

make menuconfig
#./scripts/config --disable CONFIG_SYSTEM_TRUSTED_KEYS

sudo sed -i 's/GRUB_DEFAULT=.*/GRUB_DEFAULT="1 > 2"/g' /etc/default/grub

date > a.txt
make bzImage modules -j 4
date > b.txt

sudo make modules_install install

#./arch/x86/crypto/sha1-ssse3.ko
#./arch/x86/crypto/sha256-ssse3.ko
#./sound/hda/snd-intel-sdw-acpi.ko
#./sound/soc/snd-soc-acpi.ko
#./drivers/soundwire/soundwire-bus.ko
#./drivers/soundwire/soundwire-cadence.ko
#./drivers/soundwire/soundwire-generic-allocation.ko
#./drivers/soundwire/soundwire-intel.ko
#./sound/core/snd-pcm-dmaengine.ko
#./sound/core/snd-rawmidi.ko
#./sound/core/seq/snd-seq-midi.ko
#./sound/core/seq/snd-seq-midi-event.ko
#./sound/soc/intel/common/snd-soc-acpi-intel-match.ko
#./sound/soc/codecs/snd-soc-hdac-hda.ko
#./sound/soc/intel/skylake/snd-soc-skl.ko
#./sound/soc/intel/common/snd-soc-sst-dsp.ko
#./sound/soc/intel/common/snd-soc-sst-ipc.ko
#./sound/soc/sof/snd-sof.ko
#./sound/soc/sof/intel/snd-sof-intel-hda.ko
#./sound/soc/sof/intel/snd-sof-intel-hda-common.ko
#./sound/soc/sof/intel/snd-sof-intel-hda-mlink.ko
#./sound/soc/sof/snd-sof-pci.ko
#./sound/soc/sof/intel/snd-sof-pci-intel-apl.ko
#./sound/soc/sof/snd-sof-utils.ko
#./sound/soc/sof/xtensa/snd-sof-xtensa-dsp.ko

