 #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 80
#define MAX_ATTEMPTS 5

int ChooseCategory();
char* PicWordFromSelectedCategory(char table[MAX_WORDS][MAX_WORD_LENGTH]);
void InitializeRandomlySelectedWord(char selectedWord[], char hiddenWord[]);
int EvaluateGuess(char playerGuess, char selectedWord[], char hiddenWord[]);

void main()
{
    
    int SelectedCategoryIndex = -1;
    int WrongGuessesByPlayer = 0;
    char LetterGuessesByPlayer;

    char AsianCountries[MAX_WORDS][MAX_WORD_LENGTH] = {"INDIA", "SRILANKA", "BANGLADESH", "BHUTAN", "NEPAL",
                                                       "CHINA", "PAKISTAN", "KOREA", "IRAN", "USA"};
   
    char IndianCities[MAX_WORDS][MAX_WORD_LENGTH] = {"CHENNAI", "BENGALORE", "PUNE", "MUMBAI", "KOLKATA",
                                                     "KERALA", "ODISSA", "DELHI", "PATNA", "SRINAGAR"};
    
    char Animals[MAX_WORDS][MAX_WORD_LENGTH] = {"TIGER", "LION", "ELEPHANT", "CHEETAH", "SNAKE",
                                                "WOLF", "BEAR", "HORSE", "PARROT", "DEER"};
    
    char SelectedCategoryWords[MAX_WORDS][MAX_WORD_LENGTH] = {""};

    char* RandomlySelectedword;
    char HiddenWord[MAX_WORD_LENGTH];


    do
    {
        SelectedCategoryIndex = ChooseCategory();
    } while (SelectedCategoryIndex == -1);

    switch (SelectedCategoryIndex)
    {
    case 1:
        /*for (int index = 0; index < MAX_WORDS; index++)
        {
            strcpy(SelectedCategoryWords[index], AsianCountries[index]);
        }*/

        memcpy(SelectedCategoryWords, AsianCountries, sizeof(AsianCountries));
        printf("You have selected Asian Countries. Cool, let's play!!\n");
        break;
    case 2:
        memcpy(SelectedCategoryWords, IndianCities, sizeof(IndianCities));
        printf("You have selected Indian Cities. Cool, let's play!!\n");
        break;
    case 3:
        memcpy(SelectedCategoryWords, Animals, sizeof(Animals));
         printf("You have selected Animals. Cool, let's play!!\n");
        break;
    default:
        break;
    }
    
    // printf(SelectedCategoryWords[4]);

   // srand(time(NULL));
    //int wordtochooseIndex = rand() % MAX_WORDS;
    //strcpy(randomlySelectedword, SelectedCategoryWords[wordtochooseIndex]);

    // printf("%d", wordtochooseIndex);
    // printf("%s", randomSelectedword); 
    RandomlySelectedword = PicWordFromSelectedCategory(SelectedCategoryWords);
    //printf("/n%s", RandomlySelectedword);
    InitializeRandomlySelectedWord(RandomlySelectedword, HiddenWord);

   // printf("\n\n%s", HiddenWord);

   // Main  Game Loop
   while (WrongGuessesByPlayer < MAX_ATTEMPTS)
   {
    printf("\n\n%s", HiddenWord);
    printf("\nGuess a letter for the hidden word : ");

    scanf("%c", &LetterGuessesByPlayer);
    getc(stdin);
    LetterGuessesByPlayer = toupper(LetterGuessesByPlayer);
    fflush(stdin);

    if (EvaluateGuess(LetterGuessesByPlayer, RandomlySelectedword, HiddenWord) == 0)
    {
        printf("\nNope! %c isn't a part of the hidden word. Please try again! ", LetterGuessesByPlayer);
        WrongGuessesByPlayer++;
    }
    else
    {
        printf("\nVoila! You guessed the letter right! Great job!\n");
    }

    // Notify the player about the progress of the game to far...
    printf("You have %d ", MAX_ATTEMPTS -  WrongGuessesByPlayer);
    printf("attempts left!\n");

    if (strcmp(RandomlySelectedword, HiddenWord) == 0)
    {
       printf("Congratulations! You got the word right!\n");
       printf("The hidden word was : %s!\n", RandomlySelectedword);
       break;
    }
    
  }

  if (WrongGuessesByPlayer == MAX_ATTEMPTS)
  {
    printf("\nToo bad! You have been hanged!\n");
    printf("The hidden word was : %s!\n", RandomlySelectedword);
  }

   _getch();
}

int ChooseCategory()
{
    printf("Select a category of words to play with : \n");
    printf("Press '1' to select Asian Countries.\n");
    printf("Press '2' to select Indian Cities.\n");
    printf("Press '3' to select Animals.\n");

    int userInput;
    scanf("%d",&userInput);
    getc(stdin);
    fflush(stdin);

    if(userInput > 0 && userInput < 4)
    {
        return userInput;
    }
    else
    {
        printf("\nINVALID INPUT. Please try agian!\n\n");
        return -1;
    }
}

char* PicWordFromSelectedCategory(char table[MAX_WORDS][MAX_WORD_LENGTH])
{
    srand(time(NULL));
    int wordtochooseIndex = rand() % MAX_WORDS;
    wordtochooseIndex = 0; // HACK : REMOVE LATER
    return (char *)table[wordtochooseIndex];
}

void InitializeRandomlySelectedWord(char selectedWord[], char hiddenWord[])
{
    int index;
    int wordLength = strlen(selectedWord);

    if (wordLength > 3)
    {
        for (index = 0; index < wordLength; index++)
        {
            hiddenWord[index] = '-';
            
        }

        hiddenWord[index] = '\0';
    }
}

int EvaluateGuess(char playerGuess, char selectedWord[], char hiddenWord[])
{
    int index;
    int outcome = 0;

    for (index = 0; selectedWord[index]  != '\0'; index++)
    {
        // check whether the word has already been guessed.
        if (playerGuess == hiddenWord[index])
        {
            return 0;
        }
        
        // check whether the player's guess matches any character within the randomly selected  word.
        if (playerGuess == selectedWord[index])
        {
            hiddenWord[index] = playerGuess;
            outcome++;
        }
        
    }
    return outcome;
}