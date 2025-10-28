// This header has all the (extern) declarations of the globals.
// "extern" means "this is instantiated somewhere, but here's what the name
// means.
#include "globals.h"

#include "hardware.h"

// We need to actually instantiate all of the globals (i.e. declare them once
// without the extern keyword). That's what this file does!

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11);             // LCD Screen (tx, rx, reset)
//SDFileSystem sd(p5, p6, p7, p8, "sd");  // SD Card(mosi, miso, sck, cs)
Nav_Switch myNav(p12, p15, p14, p16, p13); // initialize nav switch
DigitalIn button1(p21);                 // Pushbuttons (pin)
DigitalIn button2(p22);
DigitalIn button3(p23);
DigitalIn button4(p24);

AnalogOut DACout(p18);                  // Speaker (pin)
PwmOut speaker(p25); 
wave_player waver(&DACout);


int hardware_init()
{    
    
    button1.mode(PullUp); 
    button2.mode(PullUp);
    button3.mode(PullUp);
    button4.mode(PullUp);
    
    return ERROR_NONE;
}

GameInputs read_inputs() 
{
    GameInputs in;
    /*
    YOUR CODE HERE
    1) Read push buttons (recall that the push buttons are active-low)
    2) Read the nav switch
    */
    in.b1 = !button1; 
    in.b2 = !button2;
    in.b3 = !button3;
    in.b4 = !button4;

    in.up = myNav.up();       
    in.down = myNav.down();   
    in.left = myNav.left();   
    in.right = myNav.right(); 
    in.center = myNav.center(); 
    
    return in;
}
