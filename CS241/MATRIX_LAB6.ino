/// These constants give the bit numbers for each row and column.
///  (Mostly to give nice names for row/column "rc" values.)
typedef enum {
 c0=0,c1,c2,c3,c4,c5,c6,c7,
 r0=8,r1,r2,r3,r4,r5,r6,r7,
} rc_t;


//  This table lets you look up the row/col bit numbers
//   that need to be fed into the shift register and hardwired pins:
const int nshift_bits=8;
const rc_t rc_for_shift[nshift_bits]={c7,c6,r1,c0,r3,c5,c3,r0}; // c7 == QA
const int nhardwire=8;
const rc_t rc_for_hardwire[nhardwire]={r4,r6,c1,c2,r7,c4,r5,r2};


// Shift register data and clock pins, wired to the 8x8's top pins:
const int data_pin=2, rclock_pin=3, sclock_pin=4;


/// These are Arduino digital pins wired directly to the 8x8's bottom pins:
const char pin_for_hardwire[nhardwire]={5,6,7,8,9,10,11,12};


/// Each bit of this 16-bit pattern datatype stores a value
/// for the rows (bits 15..8) and columns (bits 7..0)
/// for one fixed pattern on the LED matrix.
/// These are static patterns that can be shown without any row scanning.
typedef unsigned short LED_pattern_t;


const int npatterns=6+8+8;
LED_pattern_t patterns[npatterns]={
//    0=on    1=on
//     row   column
//  76543210 76543210
 0b1111111100000000, // all LEDs off
 0b0000000011111111, // all LEDs on
 0b0111111010000001, // corner LEDs on
 0b1011110101000010, // corner inset-1
 0b1101101100100100, // corner inset-2
 0b1110011100011000, // center 4
 
 0b0000000010000000, // right-to-left col scan (dark background)
 0b0000000001000000,
 0b0000000000100000,
 0b0000000000010000,
 0b0000000000001000,
 0b0000000000000100,
 0b0000000000000010,
 0b0000000000000001,
 
 0b0111111111111111, // bottom-to-top row scan (dark background)
 0b1011111111111111,
 0b1101111111111111,
 0b1110111111111111,
 0b1111011111111111,
 0b1111101111111111,
 0b1111110111111111,
 0b1111111011111111,

};


/// Extract one bit from an rc_bits pattern.
///    pattern: the pattern to display
///    bit: which row/column to extract from the pattern
inline bool get_pattern_bit(LED_pattern_t pattern,rc_t bit)
{
 return pattern & (1<<bit);
}


/// Show this row/col value out the LED matrix
///   Call like    LEDs_show(patterns[1]);
void LEDs_show(LED_pattern_t pattern)
{
 // Write to the shift register, high bit first:
 for (int i=nshift_bits-1;i>=0;i--) {
   digitalWrite(sclock_pin,0); // clock low prepares for data
   digitalWrite(data_pin,
     get_pattern_bit(pattern,rc_for_shift[i]));
   digitalWrite(sclock_pin,1); // rising clock accepts data
 }
 digitalWrite(rclock_pin,0); // clock cycle
 digitalWrite(rclock_pin,1); // show the output


 // Write to the Arduino hardwired pins
 for (int i=0;i<nhardwire;i++)
   digitalWrite(pin_for_hardwire[i],
     get_pattern_bit(pattern,rc_for_hardwire[i]));
}


/// Set up output pins (call from your setup())
void LEDs_begin()
{
 pinMode(data_pin,OUTPUT);
 pinMode(rclock_pin,OUTPUT); 
 pinMode(sclock_pin,OUTPUT);
 for (char pin:pin_for_hardwire) pinMode(pin,OUTPUT);
}

// CS241 LAB 06: LED MATRIX
// Group Room 3: Samuel && Jewel
// Below is our code :)


//                                 put your array, array size, delay
void iteratePatterns(LED_pattern_t patternArray [], int arrSize, int del){
  for (LED_pattern_t i = 0; i < arrSize;i++)
  {
    LEDs_show(patternArray[i]);
    delay(del);
  }
  
}

const LED_pattern_t SMILEY_FACE_PATTERN1 = 0b0000000011111111; // practice led pattern varr
const int smileLen=16; // size
LED_pattern_t SMILEY1[smileLen]= {
  0b1111001100000100, // left eye
  0b1111111100000000,
  0b1111001100100000, // right eye
  0b1111111100000000,
  0b1110111100000010, // upper left corner smile
  0b1111111100000000,
  0b1101111100000100, // left 
  0b1111111100000000, // off
  0b1011111100001000,
  0b1111111100000000, // off
  0b1011111100010000,
  0b1111111100000000, // off
  0b1101111100100000,
  0b1111111100000000, // off
  0b1110111101000000, // upper right corner
};
//practice SMILEY
LED_pattern_t SMILEY2[smileLen]= {
  0b1000010110000000,
  0b0010010001000000,
  0b0100110000100000,
  0b0100110000010000, 
  0b0100010000001000, 
  0b0100110000000100, 
  0b0010110000000010, 
  0b1000000100000001, 
};



void setup()
{
  LEDs_begin();
}

void loop()
{
  //iterate_patterns();
  //LEDs_show(SMILEY_FACE_PATTERN1);
  //delay(1000);
  iteratePatterns(SMILEY1,smileLen,1); // running patter for smiley with size
}