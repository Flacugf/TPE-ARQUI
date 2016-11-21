
all:  bootloader kernel userland music video image 

bootloader:
	cd Bootloader; make all

kernel:
	cd Kernel; make all

userland:
	cd Userland; make all

image: kernel bootloader userland
	cd Image; make all

music: 
	cd Music; make all

video:
	cd Video; make all

clean:
	cd Bootloader; make clean
	cd Image; make clean
	cd Kernel; make clean
	cd Userland; make clean
	cd Music; make clean
	cd Video; make clean

.PHONY: bootloader image collections kernel userland all clean
