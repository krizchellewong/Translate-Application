#include <stdio.h>
#include <string.h>
#include "GO_D_WONG_K_header.h"

/* LANGUAGE TRANSLATE FUNCTIONS */

/*
    getLanguage displays the menu 
    for Language Tools and asks
    the user for preferred
    language tool.

    @param *nOption is a pointer to store the 
    user's option among the Language Tools.
*/
void
getLanguage(int *nOption)
{
    char cTemp;
    printf("\n\t\tLANGUAGE TOOLS\n");
    printf("_________________________");
    printf ("______________________\n");
    printf("To select an option, enter");
    printf (" the key enclosed in brackets\n");
    printf(" to the left side of the choice\n");
    printf("\n[1] Identify Main Language");
    printf("\n[2] Simple Translation\n");
    printf("\n[0] Exit\n");
    printf("_________________________");
    printf ("______________________\n");

    /* Prompt user to select an option */
    printf("Select Option: ");
    scanf("%d", nOption);
    scanf("%c", &cTemp);
}

/*
    importDataTools imports a file with the 
    user's filename, and appends the entry
    list to the directory. 

    @param *directory is a pointer for the
    entire directory used for the program.
*/
void
importDataTools(directorytype *directory)
{
    char filename[40];
    entrytype temp; 
    int nEntryCount = directory->nEntryCount;
    int nPairCount, i;
    int nLanglength, nNewEntry = 0;
    str language, translation;
    str checkEntry, checkEntry2;
    str tempword, tempspace;
    FILE *existdata;


    /* open text file*/

    /* Prompt user to input 
    filename of txt file */

    printf("Input filename: ");
    getInput(filename);
    existdata = fopen(filename , "r");

    /* Append data if file is 
    successfully opened */

    if (existdata != NULL)
    {
    /* Continue reading the file 
    while End of File is not yet read */
      while (!feof(existdata))
      {
        if (!feof(existdata))
        {
            temp.nPairCount = 0;
            nPairCount = temp.nPairCount;
            nNewEntry = 0;
            strcpy(checkEntry, "");

            /* Append entry to current entry index
            until double enter is detected 
            for a new entry */
            do
            {
            /* Execute only for the first cycle 
            of appending a pair */

            if (nPairCount == 0)
            {
                fscanf (existdata, "%s", language);
                nLanglength = strlen(language);
                language[nLanglength - 1] = '\0';
                strcpy (temp.pair[nPairCount].language, language);
            
                /* store to an array*/
                fscanf (existdata, "%c", tempspace);
                fscanf (existdata, "%[^\n]s", translation);
                strcpy (temp.pair[nPairCount].translation, translation);
                
                nPairCount++;
                temp.nPairCount = nPairCount;
                
            }
            /* Reads newline character 
                from the txt file */
            fgets (checkEntry, 2, existdata);
            fgets (checkEntry2, 2, existdata);
                    
            /* A double enter or an EOF character 
            signals a new entry */
            if (strcmp(checkEntry2, "\n") == 0 || feof(existdata))
            {
                /* indicates a new entry*/
                nNewEntry = 1;
            }

            /* Append to the same entry */
            else 
            {
                        strcpy (language, checkEntry2);
                        fscanf (existdata, "%s", tempword);
                        strcat(language, tempword);
                        
                        nLanglength = strlen(language);
                        language[nLanglength - 1] = '\0';
                        strcpy (temp.pair[nPairCount].language, language);
                    
                        /* store to an array */
                        fscanf (existdata, "%c", tempspace);
                        fscanf (existdata, "%[^\n]s", translation);
                        strcpy (temp.pair[nPairCount].translation, translation);

                        nPairCount++;
                        temp.nPairCount = nPairCount;
            }
            } while (nNewEntry == 0);

            directory->entries[nEntryCount].nPairCount = nPairCount;

            /* Displaying directory per entry 
            and language-translation pair */
            for (i = 0; i < nPairCount; i++)
            {
                    strcpy(directory->entries[nEntryCount].pair[i].language, temp.pair[i].language);
                    strcpy(directory->entries[nEntryCount].pair[i].translation, temp.pair[i].translation);
            }
                (directory->nEntryCount)++;
                nEntryCount = directory->nEntryCount;
                
        } 
        fclose(existdata);  
      }
    }
    else printf("File cannot be opened\n");

}

/*
    split divides the source 
    text into words or tokens.

    @param *sentence is a string containing
    the user's source text.
    @param *pCount is a pointer to store
    the word count of the sentence. 
    @param words[MAXWORDS] is an array
    to store single words or tokens.

    Pre-condition: Sentence can contain at 
                   most 150 characters.

*/
void 
split(char *sentence, 
      int *pCount, 
      longStr words[MAXWORDS])
{
    int i, j = 0, nLength;
    *pCount = 0;
    
    nLength =  strlen(sentence);

    /*Include the index for '\0' 
    to include the last word */

    for (i = 0; i <= nLength; i++)
    {
        /* Any delimeter or space signals 
           that it is the next word */

        if (sentence[i] != ' ' && sentence[i] != '\0')
        {
            /* condition to exclude 
               any delimeters */
            if (!(sentence[i] == '.' 
                || sentence[i] == ',' 
                || sentence[i] == '!' 
                || sentence[i] == '?'))
            {
                words[*pCount][j] = sentence[i];
                j++;
            }
        }
        else 
        {
            words[*pCount][j] = '\0';
            j = 0;
            (*pCount)++;
        }   
    } 
}

/*
    checkLanguages checks if the language 
    exists in the list of languages identified
    in the sentence. 

    @param *language is a pointer to the 
    structure containing the list and 
    number of languages.
    @param languagecomp is the string 
    (language) that is being matched.  

    return i: index of where the language is found
          -1: if language is not found



    Pre-condition: languagecomp can 
    have at most 20 characters. 
*/
int 
checkLanguages(languagetype * language, 
               str languagecomp)
{
    int i;
    
    for (i = 0; i < MAXWORDS; i++)
    {
        if (strcmp(language->languages[i], languagecomp) == 0)
            return i;
    }
    return -1;
}

/*
    findWord matches the word in the sentence
    with the translations given in the entries
    and returns the number of languages present
    in a sentence.

    @param *language is a pointer to the 
    structure containing the list and 
    number of languages.
    @param *directory is a pointer for the
    entire directory used for the program.
    @param nCount contains how many
    words there are in the source text. 
    @param words[MAXWORDS] is an array
    to store single words or tokens.

    return nLangCount is number of languages 
    present in a sentence

    Pre-condition: A sentence can have at 
    most 120 characters or 75 words, words[]
    can only store at most 75 words.
*/

int 
findWord(languagetype * language, 
         directorytype * directory, 
         int nCount, 
         longStr words[MAXWORDS])
{
    int nEntry, nPair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int nIndex, nWord;
    int nLangCount = 0;

    /* Loops through each language-translation pair
    in each entry in the directory */

    for (nWord = 0; nWord < nCount; nWord++)
    {
      for (nEntry = 0; nEntry < nEntryCount; nEntry++)
      {
        nPairCount = directory->entries[nEntry].nPairCount;
        for (nPair = 0; nPair < nPairCount; nPair++)
        {
                /* Matches the words stored in the array 
                with every translation in the directory */

                if (strcmp(words[nWord], directory->entries[nEntry].pair[nPair].translation) == 0)
                {
                    /* Add another language to the list of 
                    languages in struct language if and only
                    if the language is not yet declared in the list. */

                    if (checkLanguages(language, directory->entries[nEntry].pair[nPair].language) == -1)
                    {
                        strcpy (language->languages[nLangCount], directory->entries[nEntry].pair[nPair].language);
                        language->languageCount[nLangCount] = 1;
                        nLangCount++;
                    }
                    else
                    {
                        /* If language is already in the list, 
                        append count of that language */
                        nIndex = checkLanguages(language, directory->entries[nEntry].pair[nPair].language);
                        language->languageCount[nIndex] += 1;
                    } 
                }
            }
        }
    }
    return nLangCount;
}

/*
    identifyLanguage determines what is the
    main language in the source text
    
    @param *language is a pointer to the 
    structure containing the list and 
    number of languages.
    @param *directory is a pointer for the
    entire directory used for the program.
*/

void
identifyLanguage (directorytype *directory, 
                  languagetype *language)
{
    longStr sentence;
    longStr words[MAXWORDS];
    int nCount = 0;
    int nLangCount = 0;
    int nWord, nTemp = 0;
    int nHighestIndex, nSecondHighIndex;

    /* Ask user to input source text */
    printf("Enter a phrase or sentence: ");
    getInput (sentence);

    /* Split source text into single words */
    split(sentence, &nCount, words);
    /* Number of Languages in the source text */
    nLangCount = findWord (language, directory, nCount, words);

    /* Identify the highest language count */
    for (nWord = 0; nWord < MAXWORDS; nWord++)
    {
        if (nTemp < language->languageCount[nWord])
        {
            nTemp = language->languageCount[nWord];
            nHighestIndex = nWord;
        }
    }
    nTemp = 0;

    /* Identify the second highest language count */
    for (nWord = 0; nWord < MAXWORDS; nWord++)
    {
        if (nTemp < language->languageCount[nWord] && nWord != nHighestIndex)
        {
            nTemp = language->languageCount[nWord];
            nSecondHighIndex = nWord;
            
        }
    }

    /* Displaying main language of source text */
    if (nLangCount == 0)
        printf("Cannot determine the language\n");
    else if (nLangCount > 1)
    {
        printf ("Main language: %s\n", language->languages[nHighestIndex]);
        printf ("Language with the second Highest Count: %s\n", language->languages[nSecondHighIndex]);
    }
    else if (nLangCount == 1)
    {
        printf ("Main language: %s\n", language->languages[nHighestIndex]);
    }
    
}

/*
    findOutput determines the corresponding 
    translation based on the language given.

    @param *directory is a pointer for the
    entire directory used for the program.
    @param language is a structure 
    containing the list and 
    number of languages.
    @param nPairCount is the pair count 
    of the chosen entry.
    @param output is a string containing 
    the translation of the word. 
    @param nEntryIndex is the index of 
    the entry in which we want to access.

    Pre-condition: nEntryIndex is between 
    0 to 149, inclusive.
*/

void
findOutput(directorytype * directory, 
           longStr language, 
           int nPairCount, 
           longStr output, 
           int nEntryIndex)
{
    int i;

    /* Loop through all language-transaltion 
       pairs for the chosen entry */

    for (i = 0; i < nPairCount; i++)
    {
        if (strcmp (language, directory->entries[nEntryIndex].pair[i].language) == 0)
        {
            strcpy (output, directory->entries[nEntryIndex].pair[i].translation);
        }    
    }
}

/*
    simpleTranslation provides the translation
    of a source text given the source language 
    and the language you want it 
    to be translated to.

    @param *directory is a pointer for the
    entire directory used for the program.
*/

void
simpleTranslation (directorytype *directory)
{
    longStr source, output;
    longStr words[MAXWORDS];
    str langoutput, langsource;
    str choice;
    int nCount = 0, nWord;
    int nEntry, nPair, nPairCount; 
    int nEntryCount = directory->nEntryCount;
    int nTranslated = 0;
    int nCycle = 0;

    /* Prompt user to input source text
    and source & translated language */
    printf ("Enter language of source text:");
    getInput(langsource);
    printf("Enter source text: ");
    getInput(source);
    printf("Enter language to be translated to: ");
    getInput(langoutput);
    
    /* Loop through the prompts and text conversion
    until user chooses to stop [NO]. */

    do
    {
        /* if user is already asked for source language
        and language to be translated to */

        if (nCycle > 0)
        {
            printf("Enter source text: ");
            getInput(source);
        }
        /* Split source text into single words */
        split (source, &nCount, words);

        /* Match each word with its corresponding translation
        in the directory */
        for (nWord = 0; nWord < nCount; nWord++)
        {
            nTranslated = 0;

            for (nEntry = 0; nEntry < nEntryCount; nEntry++)
            {
        
                nPairCount = directory->entries[nEntry].nPairCount;
                for (nPair = 0; nPair < nPairCount; nPair++)
                {
                
                    if (strcmp(words[nWord], directory->entries[nEntry].pair[nPair].translation) == 0)
                    {
                        if (strcmp (langsource, directory->entries[nEntry].pair[nPair].language) == 0)
                        {
                            findOutput (directory, langoutput, nPairCount, output, nEntry);
                            /* Printing translated test word per word */
                            printf("%s ", output);
                            nTranslated = 1;
                        }
                    }

                } 
            }
            if (nTranslated == 0)
                printf("%s ", words[nWord]);
        }   
        printf ("\n");

        /* Prompt user if he/she wants to translate another source text */
        printf("Do you want to translate another text in %s to %s? (Yes/No)", langsource, langoutput);
        getInput(choice);
        toUpper(choice);
        
        nCycle++;
        
    } while (strcmp(choice, "YES") == 0);

}
