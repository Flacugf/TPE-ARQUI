include Makefile.inc


all: video 

video:
	cat Video >> video.bin && dd if=/dev/zero bs=1 count=1 >> video.bin

clean:
	rm -rf *.bin

