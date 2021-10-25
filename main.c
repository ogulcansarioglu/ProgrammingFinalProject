/*This program is intented to enable bank users to use ATM via written menu displayed on the screen. Via this menu, user can
1. enter and verify his/her pin,
2. change his/her pin, 
3. counts his/her right and wrong attempts and shows it if desired so,
4. end the program.

Program runs until the user decides to end it.

Program also perfoms data validation and checks for the invalid inputs and asks user to provide a valid
one instead.

Oğulcan Sarıoğlu, 18.11.2020, written in C, using Visual Studio Code*/

#include <stdio.h>
#include <stdlib.h> // for malloc use in count feature
#include <stdbool.h> // for the use of boolean variables

/*Below not hard-coded should the need arise for the change, for example
more menu options are needed. They are used in input validation.*/

#define digit_high_limit 10 /* Higher limit for pin*/
#define digit_low_limit 0 /* lower limit for pin*/
#define menu_high_limit 5 /* Higher limit for menu selection*/
#define menu_low_limit 0 /* lower limit for menu selection*/
#define ARRAYSIZE 4 /*input would be four digit and defined here to used in many arrays*/

int compareTwoArrays(int *); /*compares the entered code to the access code*/
int menu(int *, int *); /* shows the menu and takes the user input */
void codeInput(int *, int *, int *); /* takes the code input using valid function and saved them into an array */
void encryptAndVerified(int *, int *); /* encrypt the code and verify if it's the access-code with the help ofcompareTwoArrays function */
int valid(int *, int *, int *); /*checks if the input is valid, meaning an integer, in a given maximum-minimum. */
int * count(int *); /*counts the attempts, wrong and right and feed them into countyDisplay function */
void countDisplay(void); /* displays the count */
void decyrpt(int *, int *); /* decyrpt the code if it's encrypted */

const int access_code[ARRAYSIZE] = {4,5,2,3}; /*global, constant variable by design choice since it would never change in the program, and the functions would need an access while would not need to change it in anyway */


int main(void) 

{

  int code_entered[ARRAYSIZE]; 
  int codeArrayInput[ARRAYSIZE];
  int userCode[ARRAYSIZE];
  int selected; /* user's menu option selection */
  int oneInteger;  
  int wrongAttempts;
  int rightAttempts;
  int isEnabled = 0;
   /*variable to check if the code is entered and thus, the other functionalities are enabled*/

/*Do-while loop that generates the loop the program lies in. Do-While is selected so that program always runs one time for menu to display
and terminated by user if desired so.*/

/*displays the menu*/

   do 
  {
    selected = menu(&selected, &oneInteger); //Recalls the menu function 
    
    switch(selected) 
    /*Switch statement takes the user selection (selected) and triggers the right case and function. Switch loop is selected for it's efficiency.*/
    {
	  case 1:
	    codeInput(code_entered, &oneInteger, &isEnabled); // takes users input and validate, and display it
	    break; /*to ensure that other cases will not run, same for other breaks in the switch*/
	  case 2:
	  encryptAndVerified(code_entered, &isEnabled);   // encrypt and verify the code
     
      break;
	  case 3:
	    decyrpt(code_entered, &isEnabled); // decrypt and verify the code
      break;
    case 4: 
      countDisplay(); //Displays the number of correct and incorrect pin entries
      break;
    case 5:
      printf("Program has ended");
      break;
	default: /*If user provides a different input, default warns user to choose a valid one - Informing, therefore preventing her/him from making the same mistakes*/
		printf("Please Choose a Valid Option\n");
    }
  }
/*Breaks the loop if 5 is selected*/
while(selected!=5);
  
    return 0;
}


int valid(int *limit1, int *limit2, int *oneInteger)

{

  char pin[150];  // Array with a high size to counter as many user mistakes
  bool control = true; // True/False (boolean) emulation
  char error; // for invalid inputs from the user

  while (control) 
  { // Loop continues until user gives a valid input
    fgets(pin, sizeof(pin), stdin); // Read from the stream into pin array,

    int n = sscanf(pin, "%d %c", oneInteger, &error); 
    
    /* sscanf reads from pin and returns the number of parameters assigned. 
    It would return 1 if a valid input (integer) is entered only. 
    It would return 1 only when it reads integer with no char. If char comes after, it would return '2'
    and, it would return 0 if char is first, since it's coded to read an integer firstly. 
    Thus I look for n to be not equal to 1 (valid)*/

    if (n != 1) 
        {
           printf("Please Enter a Valid Integer: ");
           
        }
    else if (!(*limit1 <= *oneInteger && *oneInteger < *limit2)) /* control
            if the input is four digit*/
        { 
           printf("Please enter a Valid Integer: ");
        }
    else //if two tests were passed, pin is valid, loop breaks
        {
          control = false;
        }
  }

  return *oneInteger; // the function returns the valid input from the user

}

void codeInput(int *codeInputArray, int *inputInteger, int *isEnabled) 
{

  int high = 10;
  int low = 0;
  *isEnabled = 0; 
 

  printf("\nPlease Enter Your Code In Form Of Four Integers One Line At A Time In Between 0-10\n");

  for (int i = 0; i < ARRAYSIZE; i++) 
  {
  *(codeInputArray + i) = valid(&low, &high, inputInteger); // records to array only the valid integers
  }

  /*prints it out entirely to the user*/

  for (int i = 0; i < ARRAYSIZE; i++) 
  {
  printf("%d", *(codeInputArray + i));
  }
 
}

/* Function that displays the menu options to the user and store the user's option selection, using the valid function.*/

int menu(int *selection, int *oneInteger) 
{
  /*two integer, limits for the validation of menu input*/
  int low = 0; 
  int high = 5;

  /*prints out the menu*/
   
  printf("\n1. Enter any code\n"); 
   
  printf("2. Encrypt code entered and verify if correct\n");

  printf("3. Decrypt code\n");
    
  printf("4. Display the number of times the encrypted code entered matches the authorised code (i) Successfully (ii) Incorrectly\n");

  printf("5. Exit\n");
   
  printf("Please Choose an Option (1-4)\n");
  
  *selection = valid(&low, &high, oneInteger);
 //function returns the user's selection, and it's stored in selected

  return *selection;
} 


/*The function that determines if the pin is correct and stores the right and wrong attempts in i, and j.*/
/*This function allows user to reset his/her password, and employs 2-step verification for valid inputs */

void encryptAndVerified(int *code_entered, int *isEnabled)
{
    
    int placeholder; /*temporarly stores the value of one of the two integers that would be switched*/

    int isCorrect = 2; /*by default, is correct is 2, so even if it's passed by bug to the count function, it would not be affected */
   
    if (*isEnabled == 0)  /* checks if the code is encrypted before */
  
    {

    /*checks if there is 10 in the numbers, and if so, change it to zero */

        

    //encrypts the code with the given instructions

        for (int i = 0; i< ARRAYSIZE/2; i++) 
    
        {
            

            placeholder = *(code_entered + i); //stores first integer to a placeholder temporarly;
            *(code_entered + i) = *(code_entered + (i+2)) + 1; //change first value to third and add one to the value
            *(code_entered + (i+2)) = placeholder + 1; //add one to the placeholder and change third to the placeholder, switch is completed

            /* Checks for any integer that would increase to 10 and change them to */

            if (*(code_entered + (i + 2)) == 10) 
      
            {

             *(code_entered + (i+2)) = 0;
      
            }

            if (*(code_entered + i) == 10) 
            {

            *(code_entered + i) = 0;

            }

  

        }

        /* prints the code encrypted to the user */

        for (int i = 0; i < ARRAYSIZE; i++) 
        {

            printf("%d", *(code_entered +i));

        }

    /*verifies if the code is the acces code by using returns from compareTwoArrays and pass the information into count function*/

        if (compareTwoArrays(code_entered) == 0)  /*it passes user code to the compareTwoArrays function and if the result zero, states that it's not correct, otherwise
    says that it's correct*/
        {

            printf("\nUnfortanetly, the code that you entered is not correct");
            isCorrect = 0;
            count(&isCorrect);
      
        } 
        else 
        {
            printf("\nThe Code that you entered is correct, now you can Decrypt it. ");
            isCorrect = 1;
            count(&isCorrect);
        }
    }


    else /* if the code is already encrypted, it gives the error, and information on what can be done to the user*/
    {

            printf("\nUnfortunately, the action that you required is not possibe, and has not been done. The Code is already encryptied. Please enter a new code by selecting 1 in menu options to enable this functionality.");

    }
    
    *isEnabled += 1; /*adds one to isEnabled, by doing so, changes information to encrypted */
   
}

/*this function decyrpts the code if it's encyripted and not already decyrpted. It functions just like encruption function, but reverse the code back into it's first status*/

void decyrpt(int *code_entered, int *isEnabled)
{
    
    int placeholder; /*to temporarly hold the value*/

    if (*isEnabled == 1)  /*if encyripted and not already decyrpted*/
    {


        for (int i = 1; i >= 0; i--) /*starts at 1 and decrase i one by one until it's less than zero.*/
    
        {

        /*checks and corrects and 0 to 10, since the 10's turned into 0 in encryption*/
             
            if (*(code_entered + (i + 2)) == 0) 
      
            {

             *(code_entered + (i+2)) = 10;
      
            }

            if (*(code_entered + i) == 0) 
            {

            *(code_entered + i) = 10;
            }

          /*reverse the numbers and decrase them by one to reverse the encyription*/

            placeholder = *(code_entered + i); /* stores the value at placeholder before switch */
            *(code_entered + i) = *(code_entered + (i+2)) -1; /*changes the second digit to fourth one and decrease by one to reverse the encryption formula*/
            *(code_entered + (i+2)) = placeholder -1;  /*switches fourth to second */

            
        
        }

            printf("\nThe decyrpted code is: ");

            /* prints out the decyrpted code */

    
            for (int i = 0; i < ARRAYSIZE; i++) 
     
        {

            printf("%d", *(code_entered+i));
     

        }

    /*changes isEnabled to 2, information that the code is both encyrpted and decyrpted */

        *isEnabled += 2;
     
    } 
    
    else if (*isEnabled == 0) /*if the code is not encyrpited*/
    {

        printf("\nTo enable the decyrpt the code functionality, you should first encrypt the code."); 

    }
     
    else 
    
    { /*if the code is already decyrpted*/

        printf("\nThe actions cannot be done, the code is already decyrpted. Please enter a new code by selecting 1 in menu options to enable this functionality."); 
    
    }
     
}

/*this function compares the user's input to the access code and returns one if it's the access code, returns 0 otherwise. It takes firstArray pointer as a perimeter and 
the user input passed by reference by that*/

int compareTwoArrays(int *firstArray) 

{

    int result; //The value that would pass the information regarding the array entered by user is the acces code. If the arrays are equal, the value will be 1, otherwise 0, and then would be returned.

    //for loop navigates through both arrays's values

    for (int i = 0; i < ARRAYSIZE; i++) 
    {

    /*Checks if the array passes is the acces code, using pointer notation*/

    if (*(firstArray + i) == (*(access_code + i)))
    {

        result = 1; //if it's the access code

    } //if ends
    else 
    
    {

        result = 0; //if it's not the access code

    } //else ends

  } //for ends
  
  
  return result; //returns the result

}

/*the function counts the number of right and wrong attempts of entering pin. isCorrect is value based bool emulation that comes from verifying function, based on if the code is acces-coe is not. */

/*It creates an array to pass these to countDisplay which would display them. Array is used by design to pass two variables at once.*/

int *count(int *isCorrect) 
{

 //static type is selected so that the values would not be resetted to zero every time the function called. The values would be stored after the function call ends. 


    static int correctAttempts = 0; 
    static int incorrectAttempts = 0;

    int *temp = (int*) malloc(sizeof(int) * 2); //creates an array to store wrong and right attempts


  //if isCorrect is one, this means the code is access code and the corretAttempts increase by one, otherwise incorrectAttempts is increased.

    if (*isCorrect == 1) 

    { //if begins

    correctAttempts += 1;
     
    } //if ends

    else if (*isCorrect == 0)

    { //if begins

    incorrectAttempts += 1;

    } //if ends

  /*passing values to array*/

    *temp = correctAttempts; 
    *(temp + 1) = incorrectAttempts;


    return temp;

} //function ends

/*this function displays the wrong and right attempts. Do so by first take the values from count's returned array and then display them with printf*/

void countDisplay() 

{
    int donothing = 2; /*to call the count function just to get values and prevent it from counting*/
    int wrong, right; 
    int *displayArray = count(&donothing); /*stores returned array*/

    right = displayArray[0]; 
    wrong = displayArray[1];
  

    printf("\nYou have entered your code %d right, and %d wrong.\n", right, wrong);

} //function ends








