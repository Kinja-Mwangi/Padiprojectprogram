#include "mbed.h"
#include <ctype.h> // included in order to use the toupper() function
#include "displayFuncs.h"

// array of pin numbers for displaying full alphaneumeric set
const int A[] = {6, 7, 9};
const int B[] = {2, 4, 9, 10};
const int C[] = {7, 9, 10};
const int D[] = {1, 2, 6, 10};
const int E[] = {2, 7, 10};
const int F[] = {1, 7, 10};
const int G[] = {2, 4, 5, 10};
const int H[] = {1, 4, 9, 10};
const int I[] = {1, 5};
const int J[] = {2, 4, 5};
const int K[] = {1, 5, 9, 10};
const int L[] = {1, 2};
const int M[] = {1, 4, 7};
const int N[] = {4, 10};
const int O[] = {6, 7, 9, 10};
const int P[] = {1, 6, 7, 10};
const int Q[] = {4, 7, 9, 10};
const int R[] = {1, 10};
const int S[] = {2, 4, 7, 10};
const int T[] = {1, 7, 9};
const int U[] = {1, 2, 4};
const int V[] = {1, 2, 4, 5};
const int W[] = {5, 6, 9, 10};
const int X[] = {1, 4, 6, 9};
const int Y[] = {4, 5, 9, 10};
const int Z[] = {2, 5, 6, 7, 10};

const int ZERO[] = {1, 2, 4, 6, 7, 9};
const int ONE[] = {4, 6};
const int TWO[] = {1, 2, 6, 7, 10};
const int THREE[] = {2, 4, 6, 7, 10};
const int FOUR[] = {4, 6, 9, 10};
const int FIVE[] = {2, 4, 7, 9, 10};
const int SIX[] = {1, 2, 4, 7, 9, 10};
const int SEVEN[] = {4, 6, 7};
const int EIGHT[] = {1, 2, 4, 6, 7, 9, 10};
const int NINE[] = {2, 4, 6, 7, 9, 10};

// array of pins for each segment of the display (D14 and D15 are placeholders for the GND pins)
DigitalOut pins[] = {D0, D1, D2, D3, D4, D8, D9, D10, D11, D12};
PwmOut brightness = D7; //determines the display brightness
int scrollSpeed = 1000; // determines number of miliseconds a character is displayed for

void IdleAnimation()
{
    // array of pin numbers to display an animation cycle
    const int animation[] = {7, 6, 4, 2, 1, 9};

    // infinite while so idle animation can run indefinitely until the display is ready
    while (true)
    {
        for (int i = 0; i < sizeof(animation)/sizeof(animation[0]); i++)
        {
            pins[animation[i] - 1] = true; // display frame of animation
            thread_sleep_for(scrollSpeed);
            pins[animation[i] - 1] = false; // clear frame after the duration of scrollSpeed (up to 2s)
        }
    }
}

void AdjustDisplay()
{
    DigitalIn ADToggle(BUTTON1, PullDown); // button to toggle between adjusting brightness and scroll-speed
    AnalogIn ADPot = A0; // potentiometer to adjust the display and scroll-speed

    bool q = false; // bool to store the output of the toggle button
    bool d = true; // bool to latch toggle by storing if the button is up

    // infinite while loop so display adjustment runs continuously in the background
    while (true)
    {
        if (ADToggle)
        {
            // flip toggle and set latch to false when button is down and was previously up
            if (d)
            {
                q = !q;
                d = false;
            }
        }

        // set latch to true when button is up
        else
        {
            d = true;
        }
        
        // adjust brightness when toggle output is true
        if (q)
        {
            brightness = ADPot.read();
        }
            
        // adjust scrollspeed when toggle output is false
        else
        {
            scrollSpeed = 2000 * ADPot.read();
        }
    }
}

void DisplayClear()
{
    // for loop cycles through the pins array setting all DigitalOut pins to false 
    for (int i = 0; i < 10; i++)
    {
        pins[i] = false;
    }
}

void DisplayChar(const int c[], const int n)
{
    // for loop cycles through the pin number int array and sets corresponding DigitalOut pins to true
    for (int i = 0; i < n; i++)
    {
        pins[c[i] - 1] = true;
    }
}

void DisplayString(const char s[], const int n)
{
    for (int i = 0; i < n - 1; i++) // for loop stops at n - 1 to exclude the string null character from being displayed
    {
        const char c = toupper(s[i]); // chars from the string are made uppercase so they can be recognised even when entered lowercase

        switch (c)
        {
            case 'A':
                DisplayChar(A, sizeof(A)/sizeof(A[0]));
                break;
            case 'B':
                DisplayChar(B, sizeof(B)/sizeof(B[0]));
                break;
            case 'C':
                DisplayChar(C, sizeof(C)/sizeof(C[0]));
                break;
            case 'D':
                DisplayChar(D, sizeof(D)/sizeof(D[0]));
                break;
            case 'E':
                DisplayChar(E, sizeof(E)/sizeof(E[0]));
                break;
            case 'F':
                DisplayChar(F, sizeof(F)/sizeof(F[0]));
                break;
            case 'G':
                DisplayChar(G, sizeof(G)/sizeof(G[0]));
                break;
            case 'H':
                DisplayChar(H, sizeof(H)/sizeof(H[0]));
                break;
            case 'I':
                DisplayChar(I, sizeof(I)/sizeof(I[0]));
                break;
            case 'J':
                DisplayChar(J, sizeof(J)/sizeof(J[0]));
                break;
            case 'K':
                DisplayChar(K, sizeof(K)/sizeof(K[0]));
                break;
            case 'L':
                DisplayChar(L, sizeof(L)/sizeof(L[0]));
                break;
            case 'M':
                DisplayChar(M, sizeof(M)/sizeof(M[0]));
                break;
            case 'N':
                DisplayChar(N, sizeof(N)/sizeof(N[0]));
                break;
            case 'O':
                DisplayChar(O, sizeof(O)/sizeof(O[0]));
                break;
            case 'P':
                DisplayChar(P, sizeof(P)/sizeof(P[0]));
                break;
            case 'Q':
                DisplayChar(Q, sizeof(Q)/sizeof(Q[0]));
                break;
            case 'R':
                DisplayChar(R, sizeof(R)/sizeof(R[0]));
                break;
            case 'S':
                DisplayChar(S, sizeof(S)/sizeof(S[0]));
                break;
            case 'T':
                DisplayChar(T, sizeof(T)/sizeof(T[0]));
                break;
            case 'U':
                DisplayChar(U, sizeof(U)/sizeof(U[0]));
                break;
            case 'V':
                DisplayChar(V, sizeof(V)/sizeof(V[0]));
                break;
            case 'W':
                DisplayChar(W, sizeof(W)/sizeof(W[0]));
                break;
            case 'X':
                DisplayChar(X, sizeof(X)/sizeof(X[0]));
                break;
            case 'Y':
                DisplayChar(Y, sizeof(Y)/sizeof(Y[0]));
                break;
            case 'Z':
                DisplayChar(Z, sizeof(Z)/sizeof(Z[0]));
                break;
            case '0':
                DisplayChar(ZERO, sizeof(ZERO)/sizeof(ZERO[0]));
                break;
            case '1':
                DisplayChar(ONE, sizeof(ONE)/sizeof(ONE[0]));
                break;
            case '2':
                DisplayChar(TWO, sizeof(TWO)/sizeof(TWO[0]));
                break;
            case '3':
                DisplayChar(THREE, sizeof(THREE)/sizeof(THREE[0]));
                break;
            case '4':
                DisplayChar(FOUR, sizeof(FOUR)/sizeof(FOUR[0]));
                break;
            case '5':
                DisplayChar(FIVE, sizeof(FIVE)/sizeof(FIVE[0]));
                break;
            case '6':
                DisplayChar(SIX, sizeof(SIX)/sizeof(SIX[0]));
                break;
            case '7':
                DisplayChar(SEVEN, sizeof(SEVEN)/sizeof(SEVEN[0]));
                break;
            case '8':
                DisplayChar(EIGHT, sizeof(EIGHT)/sizeof(EIGHT[0]));
                break;
            case '9':
                DisplayChar(NINE, sizeof(NINE)/sizeof(NINE[0]));
                break;
            default:
                break;
        }
        thread_sleep_for(scrollSpeed); // display character for the duration of scrollSpeed (up to 2 seconds)
        DisplayClear(); // clear display
        thread_sleep_for(100); // hold display clear for 0.1 seconds to better indicate a display change
    }
}