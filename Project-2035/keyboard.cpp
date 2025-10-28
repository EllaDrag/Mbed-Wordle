#include "keyboard.h"
#include "dictionary.h"
#include "speech.h"
#include <string>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



DLinkedList* keyboard;
LLNode* curr;
char currTest;

char* goal_word;
char guess[6];
int idx_2 = 0;
int row = 0;
char* currData;
char* hint1;
char* hint2;
int mode;
char custom_word[6];
bool has_custom_word;
int countdown_duration = 60;
bool timer_mode;
bool has_won;
Timer game_timer;

/*
* Function to implement comparisons of data in the DLL.
* This function allows the comparisons of chars if you input
* chars into the doubly_linked_list. If you want you can make 
* additional functions to compare different types of data.
*
* This function should be passed into the create_dLinkedList()
* call.
*
*/
int compareChar(void* input1, void* input2){
    if(*(char*)input1 == *(char*)input2){
        return 1;
    }
    else{
        return 0;
    }
}

void reset_game() {
    if (mode == 1) {
        
        idx_2 = 0;
        row = 0;
        has_won = false;
        timer_mode = false;

        game_timer.stop();
        game_timer.reset();
        countdown_duration = 60;
        uLCD.cls();

        init_keyboard();
    }
}

void set_timer() {
    game_timer.reset();
    game_timer.start();
    countdown_duration = 60;
    timer_mode = true;
    init_keyboard();
    //set timer mode to false later
}
void update_timer() {
    if (timer_mode && has_won == false) {
        int elapsed_time = game_timer.read();  
        int remaining_time = countdown_duration - elapsed_time;

        if (remaining_time <= 0) {
            timer_mode = false;
            game_timer.stop();

            uLCD.cls();
            uLCD.locate(4, 1);
            uLCD.printf("You Lose :(");

            //frowny face
            uLCD.circle(64, 64, 30, 0xFFC0CB);
            uLCD.circle(54, 54, 3, 0xFFC0CB);
            uLCD.circle(74, 54, 3, 0xFFC0CB);
            for (int i = -18; i <= 18; i++) {
                int x1 = 64 + i;                    
                int y1 = 80 - (int)(sqrt(81 - i * i));
                uLCD.pixel(x1, y1, 0xFFC0CB);
            }

            //heart sprite
          int center_x = 115;
            int center_y = 105;

            uLCD.filled_circle(center_x - 4, center_y - 5, 5, 0xFFC0CB);
            uLCD.filled_circle(center_x + 4, center_y - 5, 5, 0xFFC0CB);

            for (int y = 0; y <= 10; y++) {
                int start_x = center_x - (9 - y);
                int end_x = center_x + (9 - y);
                uLCD.line(start_x, center_y + y - 3, end_x + 1, center_y + y - 3, 0xFFC0CB);
            }

            while (1); 

        } else {
            uLCD.locate(1, 13);
            uLCD.printf("Time Left: %d  ", remaining_time);  

            //hourglass sprite
            int center_x = 115;
            int center_y = 107;

            uLCD.line(center_x - 4, center_y - 6, center_x + 4, center_y - 6, 0xA52A2A);
            uLCD.line(center_x - 4, center_y - 6, center_x, center_y, 0xA52A2A);
            uLCD.line(center_x + 4, center_y - 6, center_x, center_y, 0xA52A2A);
            uLCD.line(center_x, center_y, center_x - 4, center_y + 6, 0xA52A2A);
            uLCD.line(center_x, center_y, center_x + 4, center_y + 6, 0xA52A2A);
            uLCD.line(center_x - 4, center_y + 6, center_x + 4, center_y + 6, 0xA52A2A);
            for (int i = center_x - 2; i <= center_x + 2; i++) {
            uLCD.pixel(i, center_y + 5, 0xFFFFFF);
            }
        }
    }
}


void set_custom_word() {
    has_won = false;
    mode = 2;
    has_custom_word = false;
    idx_2 = 0;

    uLCD.printf("Pick a 5 letter\nword:\n");
    uLCD.locate(5, 5); 
    uLCD.printf("_ _ _ _ _");

    //Star Sprite
    int center_x = 64;
    int center_y = 85;

    uLCD.line(center_x, center_y - 12, center_x + 6, center_y + 8, 0xFFFF00);
    uLCD.line(center_x, center_y - 12, center_x - 6, center_y + 8, 0xFFFF00);
    uLCD.line(center_x - 6, center_y + 8, center_x + 12, center_y - 4, 0xFFFF00);
    uLCD.line(center_x + 12, center_y - 4, center_x - 12, center_y - 4, 0xFFFF00);
    uLCD.line(center_x - 12, center_y - 4, center_x + 6, center_y + 8, 0xFFFF00);


    // Instantiate alphabet keyboard
    keyboard = create_dlinkedlist();
    char initial_char = 'a';
    char* curr1 = (char*)malloc(sizeof(char));
    *curr1 = initial_char;
    insertHead(keyboard, (void*)curr1);

    /*
    YOUR CODE HERE
    Populate the 'keyboard' linked list with the rest of the letters of the alphabet (b-z)
     */
    printf("Start Keyboard Initialization\n");
    for (char c = 'b'; c <= 'z'; c++) {
        char* new_char = (char*)malloc(sizeof(char));
        *new_char = c;
        insertTail(keyboard, (void*)new_char);
        printf("letters: %c\n", c);
    }
    printf("Finished Keyboard Initialization\n");

    curr = getHead(keyboard);
    uLCD.locate(8,15);
    uLCD.puts(curr1);
}

void init_keyboard()
{
    has_won = false;
    printf("we are starting init keyboard\n");
    if (has_custom_word == true) {
        goal_word = custom_word;
        printf("Goal word is %s\n\r", goal_word);
        mode = 1;
    } else {
        mode = 1;
        // Select random word from dictionary
        int random_word_ind = rand() % 30; // change with size of dictionary
        Word random_selection = dictionary[random_word_ind];

        goal_word = random_selection.letters;
        hint1 = random_selection.hint1;
        hint2 = random_selection.hint2;
        printf("Goal word is %s\n\r", goal_word);
    }
    
    // Instantiate alphabet keyboard
    keyboard = create_dlinkedlist();
    char initial_char = 'a';
    char* curr1 = (char*)malloc(sizeof(char));
    *curr1 = initial_char;
    insertHead(keyboard, (void*)curr1);

    /*
    YOUR CODE HERE
    Populate the 'keyboard' linked list with the rest of the letters of the alphabet (b-z)
     */
    printf("Start Keyboard Initialization\n");
    for (char c = 'b'; c <= 'z'; c++) {
        char* new_char = (char*)malloc(sizeof(char));
        *new_char = c;
        insertTail(keyboard, (void*)new_char);
        printf("letters: %c\n", c);
    }
    printf("Finished Keyboard Initialization\n");

    curr = getHead(keyboard);
    uLCD.locate(8,15);
    uLCD.puts(curr1);

}

void moveleft()
{
    /*
    YOUR CODE HERE (Feature 1)
    1) Update the global 'curr' to the left (previous letter) and display
    */
    
    if (curr != NULL) {
        if (curr -> prev != NULL) {
            curr = curr -> prev;
        } else {
            curr = getTail(keyboard);
        }
    }
    currTest = *(char*)(curr->data);

    uLCD.locate(9,15);
    uLCD.puts("     ");
    uLCD.locate(8, 15);
    uLCD.puts(&currTest);
    uLCD.locate(9,15);
    uLCD.puts("     ");
    wait_us(300000);
}
void moveright()
{
    /*
    YOUR CODE HERE (Feature 1)
    1) Update the global 'curr' to the right (next letter) and display
    */
    
    if (curr != NULL) {
        if (curr -> next != NULL) {
            curr = curr -> next;
        } else {
            curr = getHead(keyboard);
        }
    }
    currTest = *(char*)(curr->data);

    uLCD.locate(9,15);
    uLCD.puts("     "); 
    uLCD.locate(8, 15);
    uLCD.puts(&currTest);

    uLCD.locate(9,15);
    uLCD.puts("     ");
    wait_us(300000);
}

void select_letter()
{   
    /*
    YOUR CODE HERE (Feature 2)
    1) Update the next letter of your guess with the current 
        letter from the keyboard
        a) use globals guess and idx_2
    2) Display the letter on the uLCD screen in the correct location (Feature 4)
        a) see uLCD.locate() and uLCD.puts()
    3) Increment idx_2
    4) If the guess is completed, call check_word() to check the guess
    */
    if (mode == 1) {
        guess[idx_2] = currTest;

        uLCD.locate(idx_2, row);
        uLCD.puts(&guess[idx_2]);

        idx_2++;
        printf("we are in mode 1 select\n");
        if (idx_2 == 5) {
            guess[5] = '\0';
            check_word();
            idx_2 = 0;
            row++;
        }
        wait_us(200000);
    } else if (mode == 2) {
        custom_word[idx_2] = currTest;

        uLCD.locate((idx_2 * 2) + 5, 5);
        uLCD.puts(&custom_word[idx_2]);

        idx_2++;
        if (idx_2 == 5) {
            custom_word[5] = '\0';
            idx_2 = 0;
            row = 0;
            has_custom_word = true;

            uLCD.color(0x00FF00);
            uLCD.printf("\n\nYour word is:%s", custom_word);
            uLCD.color(0xFFFFFF);
            wait_us(3000000);

            uLCD.cls();
            init_keyboard();
        }
        wait_us(200000);
    }
    
    /*
    guess[idx_2] = currTest;

    uLCD.locate(idx_2, row);
    uLCD.puts(&guess[idx_2]);

    idx_2++;

    if (idx_2 == 5) {
        guess[5] = '\0';
        check_word();
        idx_2 = 0;
        row++;
    }
    wait_us(200000);
    */
}

void remove_letter()
{   
    /*
    YOUR CODE HERE (Feature 3)
    1) Remove the current letter of your guess
    2) Remove the letter from the uLCD screen 
        (this can be done in multiple ways)
    3) Decrement idx_2
        a) Hint: prevent decrement in certain edge case
    */
    if (idx_2 > 0) {
        idx_2--;

        uLCD.locate(idx_2, row);
        const char* message = " ";  
            uLCD.puts((char*)message);

        guess[idx_2] = '\0';

    }
    wait_us(200000);
}

char right_word[6] = "     "; 
int displayed_top[26] = {0}; 
int top_right_index = 0;    

void check_word() 
{
    int correct_count = 0; 
    int letter_checked[26] = {0}; 

    for (int i = 0; i < 5; i++) {
        char guessed_letter = guess[i];
        int found_in_goal = 0; 

        for (int j = 0; j < 5; j++) {
            if (goal_word[j] == guessed_letter) {
                found_in_goal = 1; 
                break;
            }
        }

        if (goal_word[i] == guessed_letter) {

            uLCD.color(0x00FF00);
            uLCD.locate(i, row);
            uLCD.puts(&guessed_letter); 
            uLCD.color(0xFFFFFF);

            guess[i] = ' ';
            if (!displayed_top[guessed_letter - 'a']) { 
                uLCD.locate(top_right_index + 13, 0); 
                uLCD.puts(&guessed_letter); 
                displayed_top[guessed_letter - 'a'] = 1; 
                top_right_index++; 
            }

            right_word[i] = guessed_letter; 
            correct_count++; 

        } else if (found_in_goal) {
            
            if (!letter_checked[guessed_letter - 'a']) {
                letter_checked[guessed_letter - 'a'] = 1;

                if (!displayed_top[guessed_letter - 'a']) { 
                    uLCD.locate(top_right_index + 13, 0);
                    uLCD.puts(&guessed_letter); 
                    displayed_top[guessed_letter - 'a'] = 1; 
                    top_right_index++; 
                }
            }

            uLCD.color(0xFFFF00);
            uLCD.locate(i, row);
            uLCD.puts(&guessed_letter); 
            uLCD.color(0xFFFFFF);

            guess[i] = ' ';
        } else {
            
            uLCD.locate(i, row);
            uLCD.puts(&guessed_letter);
            
            guess[i] = ' ';

            
            LLNode* temp = getHead(keyboard);
            while (temp) {
                if (*(char*)(temp->data) == guessed_letter) {
                    deleteNode(keyboard, temp);
                    break;
                }
                temp = temp->next;
            }
        }
    }

    
    if (correct_count == 5) {
        has_won = true;
        uLCD.cls();
        stickman_animation();
        return;
    } else if (row == 4) {
        
        speech(hint1, hint2);
    } else if (row == 5) {
    
        uLCD.cls();
        uLCD.locate(4, 1);
        const char* message = "You Lose :(";  
        uLCD.puts((char*)message);

        //frowny face
        uLCD.circle(64, 64, 30, 0xFFC0CB);
        uLCD.circle(54, 54, 3, 0xFFC0CB);
        uLCD.circle(74, 54, 3, 0xFFC0CB);
        for (int i = -20; i <= 20; i++) {
            int x1 = 64 + i;                    
            int y1 = 74 - (int)(sqrt(100 - i * i) / 2);
            uLCD.pixel(x1, y1, 0xFFC0CB);
        }

        //heart sprite
          int center_x = 115;
            int center_y = 105;

            uLCD.filled_circle(center_x - 4, center_y - 5, 5, 0xFFC0CB);
            uLCD.filled_circle(center_x + 4, center_y - 5, 5, 0xFFC0CB);

            for (int y = 0; y <= 10; y++) {
                int start_x = center_x - (9 - y);
                int end_x = center_x + (9 - y);
                uLCD.line(start_x, center_y + y - 3, end_x + 1, center_y + y - 3, 0xFFC0CB);
            }

    }
}

void stickman_animation() {
    uLCD.locate(3, 5);
    uLCD.printf("You Win!!! :)");

    //Sun Sprite
    int center_x = 64;
    int center_y = 80;

    uLCD.circle(center_x, center_y, 6, 0xFFFF00); 
    uLCD.line(center_x, center_y - 10, center_x, center_y - 6, 0xFFFF00); 
    uLCD.line(center_x, center_y + 10, center_x, center_y + 6, 0xFFFF00); 
    uLCD.line(center_x - 10, center_y, center_x - 6, center_y, 0xFFFF00); 
    uLCD.line(center_x + 10, center_y, center_x + 6, center_y, 0xFFFF00); 
    uLCD.line(center_x - 7, center_y - 7, center_x - 4, center_y - 4, 0xFFFF00); 
    uLCD.line(center_x + 7, center_y - 7, center_x + 4, center_y - 4, 0xFFFF00); 
    uLCD.line(center_x - 7, center_y + 7, center_x - 4, center_y + 4, 0xFFFF00); 
    uLCD.line(center_x + 7, center_y + 7, center_x + 4, center_y + 4, 0xFFFF00); 
    wait_us(3000000);

    for (int i = 0; i < 6; i++) { 
        uLCD.cls();

        uLCD.circle(64, 40, 5, 0xFFFFFF);  
        uLCD.line(64, 45, 64, 70, 0xFFFFFF);  
        uLCD.line(64, 70, 50, 80, 0xFFFFFF);  
        uLCD.line(64, 70, 78, 80, 0xFFFFFF);  

        // Frame 1: diagonal left
        if (i % 3 == 0) {
            uLCD.line(64, 50, 50, 40, 0xFFFFFF);  
            uLCD.line(64, 50, 78, 60, 0xFFFFFF);  
        }
        // Frame 2: arms flat
        else if (i % 3 == 1) {
            uLCD.line(64, 50, 50, 50, 0xFFFFFF);  
            uLCD.line(64, 50, 78, 50, 0xFFFFFF);  
        }
        // Frame 3: diagonal right
        else if (i % 3 == 2) {
            uLCD.line(64, 50, 50, 60, 0xFFFFFF);  
            uLCD.line(64, 50, 78, 40, 0xFFFFFF);  
        }

        wait_us(150000);  
    }

    uLCD.cls();
    uLCD.locate(4, 1);
    uLCD.printf("You Win! :)");

    //smiley face
    uLCD.circle(64, 64, 30, 0xFFC0CB); 
    uLCD.circle(54, 54, 3, 0xFFC0CB); 
    uLCD.circle(74, 54, 3, 0xFFC0CB); 
    for (int i = -20; i <= 20; i++) {
        int x1 = 64 + i;                    
        int y1 = 74 + (int)(sqrt(100 - i*i) / 2);
        uLCD.pixel(x1, y1, 0xFFC0CB); 
    }
}















