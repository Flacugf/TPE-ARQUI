#!/bin/bash
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -soundhw pcspk -vga std -no-kvm-irqchip -device rtl8139,netdev=net0,mac=52:54:11:11:11:11 -netdev tap,id=net0,ifname=tap0,script=no,downscript=no
