include Makefile.inc


all: song 

song:
	cat Song >> song.bin && dd if=/dev/zero bs=1 count=1 >> song.bin

clean:
	rm -rf *.bin

