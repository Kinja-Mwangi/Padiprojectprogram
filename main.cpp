#include "mbed.h"
#include "displayFuncs.h"

int main()
{    
    DigitalIn fNButton(D13, PullDown); // first name button
    DigitalIn lNButton(D14, PullDown); // last name button
    DigitalIn resetButton(D15, PullDown);

    Thread ADThread; // thread to allow display adjustment to run in the background
    ADThread.start(AdjustDisplay);

    while (true)
    {
        Thread Idle; // thread to display idle animation while user is entering names
        Idle.start(IdleAnimation);

        char fN[6]; // first name string
        char lN[6]; // last name string
        
        printf("Enter the First 5 Letters of Your First Name: ");
        scanf("%5s", fN); // get user first name
        printf("%s\n\n", fN); // print user first name

        printf("Enter the First 5 Letters of Your Last Name: ");
        scanf("%5s", lN); // get user last name
        printf("%s\n\n", lN); // print user last name

        // stop idle animation and clear display when names have been entered
        Idle.terminate();
        DisplayClear();

        while (true)
        {
            // display first name
            if (fNButton)
            {
                DisplayString(fN, sizeof(fN)/sizeof(fN[0])); 
            }

            // display last name
            else if (lNButton)
            {
                DisplayString(lN, sizeof(lN)/sizeof(lN[0]));
            }

            // reset display
            else if (resetButton)
            {
                break;
            }
        }
    }
}
