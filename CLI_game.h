#include "base_dependencies.h"
#include <string.h>
#include <iostream>

permutation inputPermutation() {
    permutation perm;
    char input[5];
    unsigned short current_digit;
    cin >> input;
    if (strlen(input) != 5) {
        throw "Input string is the wrong length.";
    }
    for (int i = 0; i < PERM_LEN; i++) {
        if (input[i] < '0' || input[i] > '9') {
            perm.isValid = false;
            throw "Input is not a set of digits.";
        }
        else {
            current_digit = (unsigned short)(input[i] - '0');
            if (perm.digit_used[current_digit] == true) {
                perm.isValid = false;
                throw "Input has repeated digits.";
            }
            else {
                perm.digit_used[current_digit] = true;
                perm.digit[i] = current_digit;
            }
        }
    }
    perm.isValid = true;
    return perm;
}

void displayPermutation(permutation perm) {
    if (perm.isValid == false)
        throw "Received invalid permutation, cannot display.";
    for (int i = 0; i < PERM_LEN; i++)
        cout << perm.digit[i];
    cout << endl;
}

void debugDisplayPermutation(permutation perm) {
    displayPermutation(perm);
    for (int i = 0; i <= 9; i++) {
        cout << perm.digit_used[i];
    }
    cout << "; " << perm.isValid << endl;

}

void gameLoop() {
    permutation base_perm;

    cout << "Please input the starting permutation. Don't let the player see it!" << endl;
    while (true) { // will keep trying to input a permutation until error is not thrown
        try {
            base_perm = inputPermutation();
        } catch (const char* msg) {
            cerr << "ERROR: " << msg << endl;
            cerr << "Try again." << endl;
            continue;
        } catch (exception &e) {
            cerr << "STD ERR: " << e.what() << endl;
            cerr << "Try again." << endl;
            continue;
        }
        break;
    }

    system("cls");

    cout << "Now, start inputting guesses. The game ends when you get it right!" << endl;
    permutation guess;
    result guess_result;

    do {
        while (true) { // ditto
            try {
                guess = inputPermutation();
            } catch (const char* msg) {
                cerr << "ERROR: " << msg << endl;
                cerr << "Try again." << endl;
                continue;
            } catch (exception &e) {
                cerr << "STD ERR: " << e.what() << endl;
                cerr << "Try again." << endl;
                continue;
            }
            break;
        }
        guess_result = comparePermutations(base_perm, guess);
        cout << "fixed: " << guess_result.fixed << "; ";
        cout << "moved: " << guess_result.moved << ". " << endl;
    } while (guess_result.fixed != 5);

    cout << "Congratulations, you got it!" << endl;
}