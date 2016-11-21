    #include <stdint.h>
    #include <naiveConsole.h>

    #define VBE_DISPI_INDEX_ID 0
    #define VBE_DISPI_INDEX_XRES 1
    #define VBE_DISPI_INDEX_YRES 2
    #define VBE_DISPI_INDEX_BPP 3
    #define VBE_DISPI_INDEX_ENABLE 4
    #define VBE_DISPI_INDEX_BANK 5
    #define VBE_DISPI_BANK_ADDRESS 0xA0000
    #define VBE_DISPI_LFB_PHYSICAL_ADDRESS 0xE0000000
    #define VBE_DISPI_INDEX_VIRT_WIDTH 6
    #define VBE_DISPI_INDEX_VIRT_HEIGHT 7
    #define VBE_DISPI_INDEX_X_OFFSET 8
    #define VBE_DISPI_INDEX_Y_OFFSET 9
    #define VBE_DISPI_BPP_4 0x04
    #define VBE_DISPI_BPP_8 0x08
    #define VBE_DISPI_BPP_15 0x0F
    #define VBE_DISPI_BPP_16 0x10
    #define VBE_DISPI_BPP_24 0x18
    #define VBE_DISPI_BPP_32 0x20
    #define VBE_DISPI_LFB_ENABLED 0x40
    #define VBE_DISPI_NOCLEARMEM 0x80
    #define VBE_DISPI_IOPORT_INDEX 0x01CE
    #define VBE_DISPI_IOPORT_DATA 0x01CF
    #define VBE_DISPI_DISABLED 0x00
    #define VBE_DISPI_ENABLED 0x01
    #define VBE_DISPI_ID4 0xB0C4
    #define VIDEO_ADDRESS_START ((char *)0xFD000000)
    #define RESOLUTION 2359296
    #define VIDEO_RESOLUTION 786432
    #define END_OF_SCREEN ((char*)0xFD000000) + 2359296
    #define WIDTH 1024
    #define HEIGHT 768
    #define BPP_32_FACTOR 4
    #define DATA_MODULE_ADDRESS 0x500000

void outpw(uint16_t port, uint16_t value);
uint16_t inpw(uint16_t port);

void BgaWriteRegister(unsigned short IndexValue, unsigned short DataValue)
{
    outpw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    outpw(VBE_DISPI_IOPORT_DATA, DataValue);
}

unsigned short BgaReadRegister(unsigned short IndexValue)
{
    outpw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    return inpw(VBE_DISPI_IOPORT_DATA);
}

int BgaIsAvailable(void)
{
    return (BgaReadRegister(VBE_DISPI_INDEX_ID) == VBE_DISPI_ID4);
}

void BgaSetVideoMode(unsigned int Width, unsigned int Height, unsigned int BitDepth, int UseLinearFrameBuffer, int ClearVideoMemory)
{


    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    BgaWriteRegister(VBE_DISPI_INDEX_XRES, Width);
    BgaWriteRegister(VBE_DISPI_INDEX_YRES, Height);
    BgaWriteRegister(VBE_DISPI_INDEX_BPP, BitDepth);
    BgaWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED |
        (UseLinearFrameBuffer ? VBE_DISPI_LFB_ENABLED : 0) |
        (ClearVideoMemory ? 0 : VBE_DISPI_NOCLEARMEM));

}

void BgaSetBank(unsigned short BankNumber)
{
    BgaWriteRegister(VBE_DISPI_INDEX_BANK, BankNumber);
}


void paintPixel(int x, int y, char blue, char green, char red){
    char *videoPointer = (char*) VIDEO_ADDRESS_START;
    int offset = ((y*WIDTH + x))*BPP_32_FACTOR;
    videoPointer = videoPointer + offset;
    *videoPointer = blue;
    videoPointer++;
    *videoPointer = green;
    videoPointer++;
    *videoPointer = red;



}

//http://lodev.org/cgtutor/juliamandelbrot.html
void juliaFractal(int iterations){
      //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
      double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
      double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
      double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position
      //ColorRGB color; //the RGB color value for the pixel
      int maxIterations = iterations; //after how much iterations the function should stop
      int h=HEIGHT;
      int w=WIDTH;

      //pick some values for the constant c, this determines the shape of the Julia Set
      cRe = -0.7;
      cIm = 0.27015;

      //loop through every pixel
      for(int y = 0; y < h; y++)
          for(int x = 0; x < w; x++)
          {
        //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
            newRe = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
            newIm = (y - h / 2) / (0.5 * zoom * h) + moveY;
        //i will represent the number of iterations
            int i;
        //start the iteration process
            for(i = 0; i < maxIterations; i++)
            {
          //remember value of previous iteration
              oldRe = newRe;
              oldIm = newIm;
          //the actual iteration, the real and imaginary part are calculated
              newRe = oldRe * oldRe - oldIm * oldIm + cRe;
              newIm = 2 * oldRe * oldIm + cIm;
          //if the point is outside the circle with radius 2: stop
              if((newRe * newRe + newIm * newIm) > 4) break;
          }
        //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
          //color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
        //draw the pixel
          paintPixel(x, y, 255,i%256,255 * (i < maxIterations));
      }
      //make the Julia Set visible and wait to exit
      return 0;
  }


void SetVideoMode(void){
   BgaSetVideoMode(WIDTH, HEIGHT, VBE_DISPI_BPP_32, 1,1);
    int iterations = 0;
    char* data = DATA_MODULE_ADDRESS;
    while(*data != '\0'){
      iterations *= 10;
      iterations += *data - '0';
      data++;
    }
    juliaFractal(iterations);

}


