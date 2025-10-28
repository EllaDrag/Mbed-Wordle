//=================================================================
// The main program file.
//
// Copyright 2024 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"
#include "speech.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

void set_random_seed(Timer);


/*
* This function handles the main logic of the game. You should
* initialize the hardware in this function, make calls to 
* functions that update the keyboard and your guess of 
* the word. 
*/
int main()
{
    printf("Program Starting\n");
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, -1);
    printf("start\n");
    
    //led1 hardware initialization
    myled1=1;  
    
    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time
    
    /* Put code here to initialize the game state:
    1) you will need to use a psuedo random number generator such as
        rand() to randomly select a goal word from the dictionary.
        The random function needs to be seeded before you call rand(),
        otherwise, rand() will always generate the same series of numbers.
        Call the function set_random_seed -- you need to complete its
        definition below.*/
    printf("Set random seed\n");

    set_random_seed(t);
    printf("Go to keyboard.cpp to initalize keyboard\n");
    //init_keyboard();
    //draw_sprite();
    
    /*
    2) call init_keyboard() and show start screen
    
    3) initialize any other game state that you add.
    */

    while(1)
    {
        t.start();
        myled2 =!myled2; 
        
        /*
        CORE GAME LOOP
        1) Call draw_lower_status() 
            - will draw a line to separate the keyboard from the guesses
        2) Read user inputs
            - will read the user buttons / navswitch input
            - The output of this function should be stored in the variable 'inputs' 
        3) Update game based on user inputs
            a) if navswitch left, call moveleft() (Feature 1)
            b) if navswitch right, call moveright() (Feature 1)
                - will make the next available letter in the keyboard appear in the bottom of the screen
            c) if navswitch pressed, call select_letter() (Feature 2)
                - will handle letter selection and cases where a guess is completed
                - this is the bulk of P2-2
            d) if button2 pressed, call remove_letter() (Feature 3)
                - will handle letter removal and return to main loop
        */
        draw_lower_status();
        inputs = read_inputs();
        update_timer(); 

        if (inputs.left) {
            printf("left\n");
            moveleft();
        }

        if (inputs.right) {
            printf("right\n");
            moveright();
        }
        if (inputs.up) {
            printf("up\n");
            moveleft();
            
        }

        if (inputs.down) {
            printf("down\n");
            moveright();
        }

        if (inputs.center) {
            select_letter();
            printf("center\n");
        }

        if (inputs.b2) {
            remove_letter();
            printf("b2 pressed\n");
        }

        if (inputs.b3) {
            reset_game();
            printf("b3 pressed\n");
        }
        
        t.stop();
        dt = t.read_ms();

        if (dt < 100) wait_us((100 - dt)*1000);
    }
    return 0;
}

void set_random_seed(Timer t) {
    GameInputs inputs; 
    t.start();

    uLCD.printf("Select Mode: \n\n\n");
    uLCD.printf("-> Standard Mode\n\n");
    uLCD.printf("   Custom Word\n\n");
    uLCD.printf("   1 min Challenge\n\n");

    //Crown Sprite
    int crown_center_x = 64;
    int crown_center_y = 95;

    uLCD.filled_rectangle(crown_center_x - 10, crown_center_y + 2, crown_center_x + 10, crown_center_y + 5, 0xFFD700);
    uLCD.triangle(crown_center_x - 10, crown_center_y + 2, crown_center_x - 6, crown_center_y - 5, crown_center_x - 2, crown_center_y + 2, 0xFFD700);
    uLCD.triangle(crown_center_x - 3, crown_center_y + 2, crown_center_x, crown_center_y - 8, crown_center_x + 3, crown_center_y + 2, 0xFFD700);
    uLCD.triangle(crown_center_x + 2, crown_center_y + 2, crown_center_x + 6, crown_center_y - 5, crown_center_x + 10, crown_center_y + 2, 0xFFD700);
    uLCD.circle(crown_center_x - 7, crown_center_y, 1, 0xFF0000);
    uLCD.circle(crown_center_x, crown_center_y - 5, 1, 0x0000FF);
    uLCD.circle(crown_center_x + 7, crown_center_y, 1, 0x00FF00);
    
    int mode = 1;
    bool mode_selected = false;

    while(!mode_selected){
      inputs = read_inputs();
      if (inputs.b1) {
          mode = 1;

          uLCD.locate(0, 3);
          uLCD.printf("-> Standard Mode\n\n");
          uLCD.printf("   Custom Word\n\n");
          uLCD.printf("   1 min Challenge\n\n");
          uLCD.filled_rectangle(0, 64, 127, 127, 0x000000);


        //Crown Sprite
          int crown_center_x = 64;
          int crown_center_y = 95;

          uLCD.filled_rectangle(crown_center_x - 10, crown_center_y + 2, crown_center_x + 10, crown_center_y + 5, 0xFFD700);
          uLCD.triangle(crown_center_x - 10, crown_center_y + 2, crown_center_x - 6, crown_center_y - 5, crown_center_x - 2, crown_center_y + 2, 0xFFD700);
          uLCD.triangle(crown_center_x - 3, crown_center_y + 2, crown_center_x, crown_center_y - 8, crown_center_x + 3, crown_center_y + 2, 0xFFD700);
          uLCD.triangle(crown_center_x + 2, crown_center_y + 2, crown_center_x + 6, crown_center_y - 5, crown_center_x + 10, crown_center_y + 2, 0xFFD700);
          uLCD.circle(crown_center_x - 7, crown_center_y, 1, 0xFF0000);
          uLCD.circle(crown_center_x, crown_center_y - 5, 1, 0x0000FF);
          uLCD.circle(crown_center_x + 7, crown_center_y, 1, 0x00FF00);

      } else if (inputs.b2) {
          mode = 2;

          uLCD.locate(0, 3);
          uLCD.printf("   Standard Mode\n\n");
          uLCD.printf("-> Custom Word\n\n");
          uLCD.printf("   1 min Challenge\n\n");
          uLCD.filled_rectangle(0, 64, 127, 127, 0x000000);

         //Pencil Sprite
          int pencil_center_x = 64;  
          int pencil_center_y = 95; 

          uLCD.filled_rectangle(pencil_center_x - 5, pencil_center_y - 3, pencil_center_x + 5, pencil_center_y + 3, 0xFFFF00);  
          uLCD.triangle(pencil_center_x + 5, pencil_center_y - 3, pencil_center_x + 5, pencil_center_y + 3, pencil_center_x + 10, pencil_center_y, 0xFFFFFF);  
          uLCD.filled_rectangle(pencil_center_x - 10, pencil_center_y - 3, pencil_center_x - 5, pencil_center_y + 3, 0xFF00FF);  
          uLCD.filled_rectangle(pencil_center_x - 6, pencil_center_y - 2, pencil_center_x - 5, pencil_center_y + 2, 0xFFFFFF);  

      } else if (inputs.b3) {
          mode = 3;

          uLCD.locate(0, 3);
          uLCD.printf("   Standard Mode\n\n");
          uLCD.printf("   Custom Word\n\n");
          uLCD.printf("-> 1 min Challenge\n\n");
          uLCD.filled_rectangle(0, 64, 127, 127, 0x000000);

         // Clock Sprite
          int clock_center_x = 64;  //horizontal
          int clock_center_y = 95;  //vertical

          uLCD.circle(clock_center_x, clock_center_y, 10, 0xFFFFFF);
          uLCD.pixel(clock_center_x, clock_center_y - 8, 0xFFFFFF);  
          uLCD.pixel(clock_center_x + 8, clock_center_y, 0xFFFFFF);  
          uLCD.pixel(clock_center_x, clock_center_y + 8, 0xFFFFFF);  
          uLCD.pixel(clock_center_x - 8, clock_center_y, 0xFFFFFF);  
          uLCD.line(clock_center_x, clock_center_y, clock_center_x, clock_center_y - 5, 0xFFFFFF); 
          uLCD.line(clock_center_x, clock_center_y, clock_center_x + 3, clock_center_y + 3, 0xFFFFFF);  

         } else if (inputs.b4) {
             mode_selected = true;
         }

        wait_us(200000);
    }
    
    uLCD.cls();
    
    t.stop();
    int seed = t.read_ms();    
    srand(seed);

    if (mode == 1) {
        init_keyboard();
    } else if (mode == 2) {
        set_custom_word();
    } else if (mode == 3) {
        set_timer();
    }
}