/*************************************************************************
 * AUTHOR           :  David Shin
 * Project          :  Hangman
 ************************************************************************/
#include <iostream>
#include <cctype>
#include <string>

using namespace std;
/*************************************************************************
* Project - Hangman
* _________________________________________________________________________
* This program executes a game of hangman.  The user has seven tries to
* guess the word and if they fail they lose, else they win.
* _________________________________________________________________________
* INPUT:
*    phrase         :  Asks for the hidden word
*    guess          :  Asks for a letter used to guess the hidden word
* OUTPUT:
*    nPhrase        :  Outputs the word inputted as a hidden word (shows
*                      dashes)
*    guesslist      :  Stores guessed letters and outputs them
*__________________________________________________________________________
*************************************************************************/
//  setupUnsolved Prototype
string setupUnsolved(string phrase);
//  udateUnsolved Prototype
string updateUnsolved(string phrase, string unsolved, char guess);
//  getGuess Prototype
char getGuess(string prevGuesses);

int main()
{
    string phrase;          //  INPUT - Grabs the word(s) for hangman
    string nPhrase;         //  OUTPUT - Outputs the hidden word(s)
    string uPhrase;         //  Used to update the updateUnsolved parameter
    string guesslist = "";  //  Used to store the guessed letters
    char letter;            //  Used to input getGuess return
    int attempts = 7;       //  Counts the attempts left

    cout << "Enter phrase: \n";
    getline(cin, phrase);

    nPhrase = setupUnsolved(phrase);
  
    cout << "Phrase: " << nPhrase << endl;

    uPhrase = updateUnsolved(phrase, nPhrase, letter);
    
    //  Game Start
    while(attempts > 0)
    {
        letter = getGuess(guesslist);
        //  Adds guessed letter to guesslist
        guesslist += letter;
        //  Redefinites uPhrase so it can used to update
        uPhrase = updateUnsolved(phrase, uPhrase, letter);
        //  Checks to see if the guess was correct
        if(phrase.find(letter) == string::npos
                && phrase.find(toupper(letter)) == string::npos
                && phrase.find(tolower(letter)) == string::npos)
        {
            cout << --attempts << " incorrect guesses left\n";
        }
        cout << updateUnsolved(phrase, uPhrase, letter);
        cout << endl;

        //  OUTPUT - Outputs guesslist
        cout << "Guessed so far: " << guesslist << endl;

        //  Checks if the user guessed the word(s) properly
        if(uPhrase == phrase)
        {
            cout << "Congratualations!! You won!" << endl;
            break;
        }

    }
    //	Game Over - Out of attempts
    if(attempts == 0)
    {
        cout << "You lost!" << endl;
    }
}

/// @brief Puts dashes in place of alphabetic characters in the phrase.
/// @param phrase the phrase to be solved
/// @return the phrase with all alphabetic characters converted to dashes
string setupUnsolved(string phrase)
{
    int i;
    for(i = 0; i < phrase.size(); i++)
    {
        if(isalpha(phrase[i]))
        {
            phrase[i] = '-';
        }
        else
        {
            phrase[i] = phrase[i];
        }
    }
    return phrase;
}

/// @brief Replaces the dashes with the guessed character.
/// @param phrase the phrase to be solved
/// @param unsolved the phrase with dashes for all unsolved characters
/// @param guess the char containing the current guessed character
/// @return the new unsolved string with dashes replaced by new guess
string updateUnsolved(string phrase, string unsolved, char guess)
{
    int i;  //  Used as a counter
    for(i = 0; i < unsolved.size(); i++)
    {
        if (islower(guess) && phrase[i] == guess){

            unsolved[i] = guess;
        }
        else if (islower(guess) && phrase[i] == toupper(guess)){
            unsolved[i] = toupper(guess);

        }
    }
    return unsolved;
}

/// @brief Gets valid guess as input
///    A guess is taken as input as a character. It is valid if
///    1) it is an alphabetic character; and
///    2) the character has not already been guessed
/// @param prevGuesses the string containing all characters guessed so far
/// @return a valid guess and only a valid guess as a character
char getGuess(string prevGuesses)
{
    char guess;

    cout << "Enter a guess: \n";
    cin >> guess;

    while(!(isalpha(guess)) || prevGuesses.find(guess) != string::npos
          || isupper(guess))
    {
        cout << "Enter a guess: \n";
        cin >> guess;
    }
    return guess;
}
