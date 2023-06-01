#include <stdio.h>
#include <string.h>
#include "GO_D_WONG_K_header.h"

/*  getInput gets a string input from the user and 
    can get input with spaces between strings
    @param string - the array that the string's 
           characters will be stored in
*/
void
getInput(char * string) 
{
  int i;
  char c;
  
  i = 0;
  do 
  {
    scanf("%c", &c);
    if (c != '\n') 
	{
      string[i] = c;
      i++;
    }
  } while (c != '\n');
  string[i] = '\0';
}

/*  getMenu displays the menu options and asks 
    the user to choose one
    @param *nMenu - the menu option selected
*/
void 
getMenu(int *nMenu)
{
    char cTemp;
    printf("\n\t\tMAIN MENU\n");
    printf("_______________________________________________\n");
    printf("\'Manage Data\' allows you to create entries \n");
    printf("and create and edit language-translation pairs \n");
    printf("within these entries. \n");
    printf("\'Language Tools\' allows you to import a file\n");
    printf("of language-translation pairs to be used to either\n");
    printf("translate a text or identify its main language\n\n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Manage Data\n");
    printf("\n[2] Language Tools\n");
    printf("\n[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nMenu);
    scanf("%c", &cTemp);
}

/*  getData displays the Manage Data options and asks 
    the user to choose one
    @param *nData is the Manage Data option selected
*/
void
getData(int *nData)
{
    char cTemp;
    printf("\n\t\tMANAGE DATA\n");
    printf("_______________________________________________\n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("[1] Add Entry\n");
    printf("[2] Add Translations\n");
    printf("[3] Modify Entry\n");
    printf("[4] Delete Entry\n");
    printf("[5] Delete Translation\n");
    printf("[6] Display All Entries\n");
    printf("[7] Search Word\n");
    printf("[8] Search Translations\n");
    printf("[9] Export\n");
    printf("[10] Import\n");
    printf("[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nData);
    scanf("%c", &cTemp);
}

/*  toUpper capitalizes all lowercase alphabetical letters
    @param string - the string to be capitalized
*/
void 
toUpper(char * string)
{
    int i;
    int nLength = strlen(string);

    for (i = 0; i < nLength; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
            string[i] -= 32;
    }
}


/*  displayEntry displays a single entry from the directory 
    @param directory - the structure that contains the list
                       of entries
    @param nEntryIndex - the index of the entry in directory 
                         to be displayed
    @param nPairCount - the number of language-translation 
                        pairs in an entry

    Pre-conditions: index is between 0 to the number of entries
                    in directory minus 1, inclusive
                    nPairCount is between 0 to 10, inclusive
*/
void 
displayEntry (directorytype directory, 
              int nEntryIndex, 
              int nPairCount)
{
    int pair;
    printf ("%-25s", "    |LANGUAGE");
    printf ("%-20s", "|TRANSLATION");
    printf ("%2s\n", "|");
    for (pair = 0; pair < nPairCount; pair++)
       printf ("(%d) |%-20s|%-20s|\n", pair + 1, directory.entries[nEntryIndex].pair[pair].language, directory.entries[nEntryIndex].pair[pair].translation);
}

/*  getNewPair asks the user for a language-translation 
    pair and appends it to an entry in the directory 
    structure
    @param directory - the structure that contains the 
                       list of entries
    @param nEntryIndex - the index of the entry in directory 
                         that will be appended to

    Pre-condition: nEntryIndex is between 0 to 149, inclusive
 */
void
getNewPair(directorytype * directory, 
           int nEntryIndex)
{
    str language, translation;
    int nPairCount; 

    /* Enter new pair */
    printf ("Enter Language: ");
    getInput(language);

    printf ("Enter Translation: ");
    getInput(translation);

    /* Incremend pair count */
    directory->entries[nEntryIndex].nPairCount += 1; 
    nPairCount = directory->entries[nEntryIndex].nPairCount;

    /* Append pair to the entry */
    strcpy (directory->entries[nEntryIndex].pair[nPairCount - 1].language, language);
    strcpy (directory->entries[nEntryIndex].pair[nPairCount - 1].translation, translation);
}

/*  addEntry asks the user for a language-translation 
    pair and creates a new entry if the pair does not 
    exist or if it exists and the user still wants to 
    create a new entry
    @param directory - the structure that contains the list
                       of entries
*/
void 
addEntry (directorytype * directory)
{
    str language, translation;
    int nEntry, nPair;
    int nFound = 0; 
    int nEntryCount, nPairCount; 
    str newEntry, newPair;

    /* Enter new pair */
    printf ("Enter Language: ");
    getInput(language);

    printf ("Enter translation: ");
    getInput(translation);

    /* Check if pair exists*/
    for (nEntry = 0; nEntry < MAXENTRY; nEntry++)
    {
        for  (nPair = 0; nPair < MAXPAIR; nPair++)
        {
            if ((strcmp(translation, directory->entries[nEntry].pair[nPair].translation) == 0) 
            && (strcmp (language, directory->entries[nEntry].pair[nPair].language) == 0))
                nFound = 1; 
        }
    }

    /* If pair found, display entries where pair has been found */
    if (nFound == 1)
    {
        /* Display first entries with the same info*/
        nEntryCount = directory->nEntryCount;
        for (nEntry = 0; nEntry < nEntryCount; nEntry++)
        {
            nPairCount = directory->entries[nEntry].nPairCount;
            for (nPair = 0; nPair < nPairCount; nPair++)
            {
                if ((strcmp(translation, directory->entries[nEntry].pair[nPair].translation) == 0) 
                && (strcmp (language, directory->entries[nEntry].pair[nPair].language) == 0))
                {
                    displayEntry(*directory, nEntry, nPairCount);
                    nPair = nPairCount;
                }
            }
            printf ("\n");
        }

        /* Ask user if they still want to add the pair as a new entry */
        printf ("Is this a new entry (Yes/No)? ");
        getInput(newEntry);

        toUpper(newEntry);

        /* Add pair as a new entry */
        if (strcmp (newEntry, "YES") == 0)
        {
            /* Increment entry count */
            directory->nEntryCount += 1;
            nEntryCount = directory->nEntryCount;

            /* Increment pair count in new entry */
            directory->entries[nEntryCount -1].nPairCount += 1; 
            nPairCount = directory->entries[nEntryCount -1].nPairCount;

            /* Append pair to new entry */
            strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);

            /* Exit loop when user does not want to 
               add another pair to the entry */
            do
            {
                /* Ask the user if they want to encode another pair in the entry */
                printf ("Do you want to encode another pair (Yes/No)? ");
                getInput(newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    /* Ask user for new pair and append to 
                       the current entry */
                    getNewPair(directory, nEntryCount - 1);
                }

            } while (strcmp (newPair, "YES") == 0);
        }
        
    }

    else if (nFound == 0)
    {
        directory->nEntryCount += 1;
        nEntryCount = directory->nEntryCount;
        directory->entries[nEntryCount -1].nPairCount += 1; 
        nPairCount = directory->entries[nEntryCount -1].nPairCount;

        strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
        strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);

        /* Exit loop when user does not want to 
           add another pair to the entry */
        do
        {
            /* Ask the user if they want to encode another pair in the entry */
            printf ("Do you want to add another pair to this entry (Yes/No)? ");
            getInput(newPair);
            toUpper(newPair);

            if (strcmp (newPair, "YES") == 0)
            {
                /* Ask user for new pair and append to 
                   the current entry */
                getNewPair(directory, nEntryCount - 1);
            }

        } while (strcmp (newPair, "YES") == 0);
        
    }
}

/*  addTranslation asks the user for a language-translation
    pair. If the pair exists in an entry, the user may add
    another pair for that entry. Otherwise, the user must
    go back and select the Add Entry option first. 
    @param directory - the structure that contains the list
                       of entries  
*/
void
addTranslation(directorytype * directory)
{
    str language, translation;
    int entry, pair, nCount = 0; 
    int tempentry [MAXENTRY];
    int i, index;
    int newentry, nPairCount;
    str newPair;
    char temp;
    
    /* Enter new pair */
    printf ("Enter Language:");
    getInput (language);

    printf ("Enter Translation:");
    getInput (translation);

    /* Check if entry with that pair exists*/
    for (entry = 0; entry < MAXENTRY; entry++)
    {
        for  (pair = 0; pair < MAXPAIR; pair++)
        {
            if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
            && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
            {
                tempentry[nCount] = entry; 
                nCount++;
            }
        }
    }
    /* If nCount is 0, entry does not exist */
    if (nCount == 0)
    {
        printf ("Entry does not exist.\n");
        printf ("Please select the Add Entry Option\n");
    }   
    /* If nCount is greater than 0, entry exists */
    else if (nCount > 0)
    {
        for (i = 0; i < nCount; i++)
        {
            index = tempentry[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf ("\n");
        }

        /* If the pair only exists in one entry
           new pair is asked and added to the same entry */
        if (nCount == 1 && directory->entries[tempentry[0]].nPairCount < 10)
        {
            /* Enter new pair*/
            printf ("Enter New Language: ");
            getInput (language);

            printf ("Enter New Translation: ");
            getInput (translation);

            /* Increment pair count */
            directory->entries[tempentry[0]].nPairCount += 1; 
            nPairCount = directory->entries[tempentry[0]].nPairCount;

            /* Append pair to the entry */
            strcpy (directory->entries[tempentry[0]].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[tempentry[0]].pair[nPairCount - 1].translation, translation);

            /* Exit loop when user does not want to 
               add another pair to the entry */
            do
            {
                printf ("Do you want to encode another pair (Yes/No)? ");
                getInput(newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    /* Ask user for new pair and append to 
                       the current entry */
                    getNewPair(directory, tempentry[0]);
                }

            } while (strcmp (newPair, "YES") == 0 && directory->entries[tempentry[0]].nPairCount <= 10);
        }
        /* If the pair appears in multiple entries, user will choose an entry */
        else if (nCount > 1 && directory->entries[tempentry[0]].nPairCount < 10)
        {
            printf ("Choose Entry to add a language-translation pair to: ");
            scanf ("%d", &newentry);
            scanf("%c", &temp);

            /* Enter new pair*/
            printf ("Enter Language:");
            getInput (language);

            printf ("Enter translation:");
            getInput (translation);

            /* Add pair count */
            directory->entries[tempentry[newentry -1]].nPairCount += 1; 
            nPairCount = directory->entries[tempentry[newentry -1]].nPairCount;

            /* Append pair to the entry */
            strcpy (directory->entries[tempentry[newentry -1]].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[tempentry[newentry -1]].pair[nPairCount - 1].translation, translation);
        
            /* Exit loop when user does not want to 
               add another pair to the entry */
            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                getInput (newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    /* Ask user for new pair and append to 
                       the current entry */
                    getNewPair(directory, tempentry[newentry -1]);
                }
            } while (strcmp (newPair, "YES") == 0 && directory->entries[tempentry[newentry -1]].nPairCount <= 10);
        }
    }
}

/*  sortAlphabetical sorts the language-translation pairs
    in a single entry in alphabetical order
    @param directory - the structure that contains the list
                       of entries  
    @param nEntryIndex - the index of the entry in directory 
                         that will be appended to
    Pre-condition: nEntryIndex is between 0 to 149, inclusive
*/
void 
sortAlphabetical(directorytype * directory, int nEntryIndex)
{
    int nPairCount; 
    int i, j, position;
    str temp[2];

    nPairCount = directory->entries[nEntryIndex].nPairCount;
    /* Arrange all pairs in ascending order*/
    for(i = 0; i < nPairCount - 1; i++)
	{
        /* set your position cursor at index i */
		position = i;
        /* compare each language (ASCII Value) 
        of that in index i*/
		for(j = i + 1; j < nPairCount; j++)
		{
			if(strcmp (directory->entries[nEntryIndex].pair[position].language, directory->entries[nEntryIndex].pair[j].language) > 0)
            {
                /* if ASCII VALUE in index j is less than that in index i, 
                place position cursor at index j*/
                position = j;
            }
		}
        /*If the language in index i is not equal to position, swap pairs */
		if(position != i)
		{
            /* switch the language-pair located in index i to index position and vice versa */
			strcpy(temp[0], directory->entries[nEntryIndex].pair[i].language); 
            strcpy(temp[1], directory->entries[nEntryIndex].pair[i].translation);
			strcpy (directory->entries[nEntryIndex].pair[i].language, directory->entries[nEntryIndex].pair[position].language);
            strcpy (directory->entries[nEntryIndex].pair[i].translation, directory->entries[nEntryIndex].pair[position].translation);
			strcpy (directory->entries[nEntryIndex].pair[position].language, temp[0]);
            strcpy (directory->entries[nEntryIndex].pair[position].translation, temp[1]);
		}
	}
}

/*  displayAll displays all of the entries in directory 
    one by one with each individual entry sorted 
    alphabetically
    @param directory - the structure that contains the list
                       of entries
    Pre-condition: nEntryIndex is between 0 to 149, inclusive
*/
void
displayAll (directorytype * directory)
{ 
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int i = 0;
    char cOption;
    char cTemp;

    /* When no entries exist, this message is displayed */
    if (nEntryCount == 0)
        printf("There are no entries to be displayed.\n");

    while (i < nEntryCount)
    {
        /* Sort entry pairs alphabetically */
        sortAlphabetical(directory, i);

        nPairCount = directory->entries[i].nPairCount;

        printf("Entry #%d\n", i+1);

        /* Display one entry */
        displayEntry(*directory, i, nPairCount);

        printf("_______________________________________________\n");
        printf("[N] Next Entry\n");
        printf("[P] Previous Entry\n");
        printf("[X] End Display\n");
        printf("_______________________________________________\n");
        printf("Enter option: ");
        scanf("%c", &cOption);
        scanf("%c", &cTemp);

        toUpper(&cOption);

        /* Next entry increments the entry index i by 1 */
        if (cOption == 'N')
            i++;

        /* Previous entry decrements the entry index i by 1 */
        else if (cOption == 'P')
            i--;
        
        /* End display sets i to nEntryCount to exit the 
           while loop */
        else if (cOption == 'X')
            i = nEntryCount;
        
        else
            printf("Invalid option.\n");
            
    }
 
}

/*  modifyEntry allows the user to modify an entry pair by
    changing either the language or translation of a given
    pair 
    @param directory - the structure that contains the list
                       of entries
*/
void
modifyEntry(directorytype * directory)
{
    int nEntry, nPair;
    char temp;
    str choice, input, modify;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;

    /* Display all directories */
    displayAll(directory);

    /* Ask user for entry number to modify */
    printf("Which entry do you want to modify? ");
    scanf("%d", &nEntry);
    scanf("%c", &temp);

    if (!(nEntry >= 1 && nEntry <= nEntryCount))
        printf("Invalid input. Entry does not exist.\n");
    
    else
    {
        nPairCount = directory->entries[nEntry-1].nPairCount;

        /* Loop until user inputs NO when asked if they would like
           to make more modifications */
        do 
        {
            /* Loop until valid pair number is given */
            do
            {
                printf("Which pair do you want to modify? ");
                scanf("%d", &nPair);
                scanf("%c", &temp);
                if (!(nPair >= 1 && nPair <= nPairCount))
                    printf("Invalid input. Pair does not exist\n");

            } while (!(nPair >= 1 && nPair <= nPairCount));

            /* Loop until valid choice (either language or translation)
               is given */
            do
            {
                
                printf ("Modify language or translation: ");
                getInput(choice);
                toUpper (choice);

                if (strcmp (choice, "LANGUAGE") == 0)
                {
                    printf ("Input language: ");
                    getInput (input);
                    strcpy (directory->entries[nEntry -1].pair[nPair -1].language, input);
                }
                else if (strcmp(choice, "TRANSLATION") == 0)
                {
                    printf ("Input translation: ");
                    getInput (input);

                    strcpy(directory->entries[nEntry-1].pair[nPair -1].translation, input);
                }
                else
                    printf("Invalid input.\n");
                
            } while (!(strcmp(choice, "TRANSLATION") == 0 || strcmp (choice, "LANGUAGE") == 0));
            
            printf ("Would you like to make more modifications for this entry (Yes/No)? ");
            getInput (modify);
            toUpper(modify);

        } while (strcmp(modify, "YES") == 0);
    
    }
}

/*  deleteEntry allows the user to delete an entire entry
    from the directory
    @param directory - the structure that contains the list
                       of entries
*/
void
deleteEntry (directorytype *directory)
{
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int deleteEntry;
    char temp;
    int i, j;

    displayAll (directory);
    printf("Which entry do you want to delete? ");
    scanf("%d", &deleteEntry);
    scanf("%c", &temp);

    if (deleteEntry >= 1 && deleteEntry <= nEntryCount)
    {
        for (i = deleteEntry - 1; i < nEntryCount - 1; i++)
        {
            nPairCount = directory->entries[i].nPairCount;
            /* Set all pairs in the deleted entry to null to delete */
            for (j = 0; j < nPairCount; j++)
            {
                strcpy(directory->entries[i].pair[j].translation,"\0");
                strcpy(directory->entries[i].pair[j].language,"\0");
            }

            nPairCount = directory->entries[i + 1].nPairCount;
            /* Move all pairs from an entry to the location of the 
               deleted entry then all succeeding pairs are moved
               by one index less than its original */
            for (j = 0; j < nPairCount; j++)
            {
                strcpy(directory->entries[i].pair[j].translation, directory->entries[i + 1].pair[j].translation);
                strcpy(directory->entries[i].pair[j].language, directory->entries[i + 1].pair[j].language);
            }
        }

        /* Last entry is also set to null since all entries have
           already been moved */
        for (j = 0; j < nPairCount; j++)
        {
            strcpy(directory->entries[nEntryCount-1].pair[j].translation,"\0");
            strcpy(directory->entries[nEntryCount-1].pair[j].language,"\0");
        }
        directory->nEntryCount -= 1;
        nEntryCount = directory->nEntryCount;
        
    }
    else printf("Invalid input. Entry does not exist.\n");

}

/*  deleteTranslation allows the user to delete a specific
    language-translation pair in an entry of their choice
    @param directory - the structure that contains the list
                       of entries
*/
void
deleteTranslation(directorytype *directory)
{
    int deletePair, nPairCount, entry;
    int nEntryCount = directory->nEntryCount; 
    char temp;
    int i, j;
    str choice; 
    strcpy(choice, "YES");
    displayAll(directory);
    
    printf("Which entry do you want to delete from? ");
    scanf("%d", &entry);

    if (entry >= 1 && entry <= nEntryCount)
    {
        do
        {
            nPairCount = directory->entries[entry - 1].nPairCount;
            /* If there's only one pair left in the entry, delete
               the entire entry */
            if (nPairCount == 1)
            {
                for (i = entry - 1; i < nEntryCount - 1; i++)
                {
                    nPairCount = directory->entries[i].nPairCount;
                    /* Set all pairs in the deleted entry to null to delete */
                    for (j = 0; j < nPairCount; j++)
                    {
                        strcpy(directory->entries[i].pair[j].translation,"\0");
                        strcpy(directory->entries[i].pair[j].language,"\0");
                    }

                    nPairCount = directory->entries[i + 1].nPairCount;
                    /* Move all pairs from an entry to the location of the 
                    deleted entry then all succeeding pairs are moved
                    by one index less than its original */
                    for (j = 0; j < nPairCount; j++)
                    {
                        strcpy(directory->entries[i].pair[j].translation, directory->entries[i + 1].pair[j].translation);
                        strcpy(directory->entries[i].pair[j].language, directory->entries[i + 1].pair[j].language);
                    }
                }

                /* Last entry is also set to null since all entries have
                already been moved */
                for (j = 0; j < nPairCount; j++)
                {
                    strcpy(directory->entries[nEntryCount-1].pair[j].translation,"\0");
                    strcpy(directory->entries[nEntryCount-1].pair[j].language,"\0");
                }
                directory->nEntryCount -= 1;
                nEntryCount = directory->nEntryCount;
                strcpy (choice, "NO");
            }
            else
            {
                do
                {
                    printf("Which language-translation pair do you want to delete? ");
                    scanf("%d", &deletePair);
                    scanf("%c", &temp);

                    if (!(deletePair >= 1 && deletePair <= nPairCount))
                    {
                        printf("Invalid Input.\n");
                        printf("Do you still want to delete a pair (Yes/No)? ");
                        getInput (choice);
                        toUpper (choice);
                    }

                } while (!(!(deletePair >= 1 && deletePair <= nPairCount) || strcmp(choice, "YES") == 0));

            
                if (strcmp(choice, "YES") == 0)
                {
                    /* Move all pairs to the location of the deleted 
                       pair then all succeeding pairs are moved by 
                       one index less than its original */
                    for (i = deletePair - 1; i < nPairCount - 1; i++)
                    {
                        strcpy (directory->entries[entry-1].pair[i].language, directory->entries[entry-1].pair[i+1].language);
                        strcpy (directory->entries[entry-1].pair[i].translation, directory->entries[entry-1].pair[i+1].translation);
                    } 

                    /* Last pair is also set to null since all pairs have
                       already been moved */
                    strcpy(directory->entries[entry-1].pair[nPairCount-1].translation,"\0");
                    strcpy(directory->entries[entry-1].pair[nPairCount-1].language,"\0");

                    directory->entries[entry - 1].nPairCount -= 1;
    
                    printf("Do you want to delete another entry(Yes/No)? ");
                    getInput(choice);
                    toUpper(choice);
                }
            }
        } while (strcmp(choice, "YES") == 0);
    }
    else printf ("Invalid Input.\n");
}

/*  searchWord shows a list of all the entries where a
    given translation appears in
    @param directory - the structure that contains the list
                       of entries
*/
void
searchWord (directorytype *directory)
{
    str word;
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount, nCount = 0;
    int tempMatch[MAXENTRY];
    int index, i;
    char cOption, cTemp;

    printf ("Input word: ");
    getInput(word);

    for (entry = 0; entry < nEntryCount; entry++)
    {
        nPairCount = directory->entries[entry].nPairCount;
        for  (pair = 0; pair < nPairCount; pair++)
        {
            if (strcmp(word, directory->entries[entry].pair[pair].translation) == 0)
            {
                tempMatch[nCount] = entry; 
                nCount++; 
            }
        }
    }

    /* If nCount is greater than 0, word was found in one or more entries */
    if (nCount > 0)
    {
        /* Display all entries word was found in */
        for (i = 0; i < nCount; i++)
        {
            index = tempMatch[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf("_______________________________________________\n");
            printf("[N] Next Entry\n");
            printf("[P] Previous Entry\n");
            printf("[X] End Display\n");
            printf("_______________________________________________\n");
            printf("Enter option: ");
            scanf("%c", &cOption);
            scanf("%c", &cTemp);

            toUpper(&cOption);

            /* Next entry increments the entry index i by 1 */
            if (cOption == 'N')
                i++;

            /* Previous entry decrements the entry index i by 1 */
            else if (cOption == 'P')
                i--;
            
            /* End display sets i to nEntryCount to exit the 
            while loop */
            else if (cOption == 'X')
                i = nEntryCount;
            
            else
                printf("Invalid option.\n");
            printf ("\n");
        }   
    }
    else printf ("No entry match.\n");
}

/*  searchTranslation shows a list of all the entries
    where a specific language-translation pair appears in 
    @param directory - the structure that contains the list
                       of entries
*/
void 
searchTranslation(directorytype * directory)
{
    str language, translation;
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount, nCount = 0;
    int tempMatch[MAXENTRY];
    int index, i;

    /* Ask user to input the pair to search */
    printf ("Enter language: ");
    getInput(language);
    printf("Enter translation: ");
    getInput(translation);

    for (entry = 0; entry < nEntryCount; entry++)
    {
        nPairCount = directory->entries[entry].nPairCount;
        for  (pair = 0; pair < nPairCount; pair++)
        {
            if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
            && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
            {
                tempMatch[nCount] = entry; 
                nCount++; 
            }
        }
    }

    /* If nCount is greater than 0, word was found in one or more entries */
    if (nCount > 0)
    {
        /* Display all entries word was found in */
        for (i = 0; i < nCount; i++)
        {
            index = tempMatch[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf ("\n");
        }   
    }
    else printf ("No Entry Match\n");
    
}

/*  exportData saves all the stored data in directory
    into a text file, wherein the filename is given by the 
    user
    @param directory - the structure that contains the list
                       of entries
*/
void
exportData (directorytype directory)
{
    char filename [40];
    int i;
    int nEntryCount = directory.nEntryCount;
    int nPairCount;
    int pair;
    FILE *savedata;

    printf("Input filename: ");
    getInput (filename);

    /* Open file to write to and overwrite any previously 
       existing data in the file */
    savedata = fopen(filename, "w");

    /* If file opened successfully */
    if (savedata != NULL)
    {
        /* Write all contents of directory to file */
        for (i = 0; i < nEntryCount; i++)
        {
            nPairCount = directory.entries[i].nPairCount;
            for (pair = 0; pair < nPairCount; pair++)
                fprintf (savedata, "%s: %s\n", directory.entries[i].pair[pair].language, directory.entries[i].pair[pair].translation);
            if (i != nEntryCount - 1)
                fprintf(savedata, "\n");
        }
	    fclose(savedata);
    }
    else
    {
        printf("File cannot be opened.\n");
    }

}

/*  importData reads data from a file and stores it in the
    directory structure, differentiating between the
    languages and translations as well as different entries
    separeted by a newline
    @param directory - the structure that contains the list
                       of entries
*/
void
importData (directorytype * directory)
{
    char filename[40];
    FILE *existdata;
    entrytype temp; 
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    str language;
    str translation;
    int langlength;
    str checkEntry, checkEntry2;
    int newEntry = 0;
    str tempword, choice, tempspace;
    int i;


    /* Ask user to input name of file to be opened */
    printf("Input filename: ");
    getInput(filename);
    existdata = fopen(filename , "r");

    if (existdata != NULL)
    {
        /* While program has not reached the end of the file */
        while (!feof(existdata))
        {
            if (!feof(existdata))
            {

                temp.nPairCount = 0;
                nPairCount = temp.nPairCount;
                newEntry = 0;
                strcpy(checkEntry, "");

                /* Loop while it is not yet a new entry */
                do
                {
                    /* For the first pair of an entry */
                    if (nPairCount == 0)
                    {
                        /* Read the language of the first pair */
                        fscanf (existdata, "%s", language);

                        langlength = strlen(language);

                        /* Set semicolon to nullbyte */
                        language[langlength - 1] = '\0';

                        /* Store language in temporary entry structure */
                        strcpy (temp.pair[nPairCount].language, language);
            
                        /* Read the translation of the first pair */
                        fscanf (existdata, "%c", tempspace);

                        fscanf (existdata, "%[^\n]s", translation);

                        /* Store translation in a temporary entry structure */
                        strcpy (temp.pair[nPairCount].translation, translation);
                        
                        /* Increment pair count of the temporary array */
                        nPairCount++;
                        temp.nPairCount = nPairCount;
                
                    }
                    /* Scan for the newline */
                    fgets (checkEntry, 2, existdata);
                    
                    /* Scan for the first character of the next line in the file */
                    fgets (checkEntry2, 2, existdata);
        
                    /* If the next line is ONLY a newline or the end of the file */
                    if (strcmp(checkEntry2, "\n") == 0 || feof(existdata))
                    {
                        /* Indicate that the next pair/s are part of a new entry*/
                        newEntry = 1;
                    }
                    else 
                    {
                        /* If the next line is a character, copy it to index
                        0 of the language array */
                        strcpy (language, checkEntry2);

                        /* Concatenate the lest of the line until the semicolon */
                        fscanf (existdata, "%s", tempword);
                        strcat(language, tempword);
                    
                        langlength = strlen(language);

                        /* Set semicolon to nullbyte */
                        language[langlength - 1] = '\0';

                        /* Store language to the temporary entry structure */
                        strcpy (temp.pair[nPairCount].language, language);
                    
                        /* Scan the rest of the line for the translation */
                        fscanf (existdata, "%c", tempspace);
                        fscanf (existdata, "%[^\n]s", translation);

                        /* Store translation to the temporary entry structure */
                        strcpy (temp.pair[nPairCount].translation, translation);

                        nPairCount++;
                        temp.nPairCount = nPairCount;

                    }
                } while (newEntry == 0);

                /* If previous entries already exist in the directory, 
                ask if the read entry should be appended */
                if (nEntryCount > 0)
                {
                    for (i = 0; i < nPairCount; i++)
                    {
                        printf("%s: %s\n", temp.pair[i].language, temp.pair[i].translation);
                    }
                    printf ("Do you want to append this to your current list of entries? ");
                    getInput (choice);
                    toUpper (choice);
                }
                /* If previous entries do not exist in the directory,
                the read entry will immediately be added */
                else
                {
                    strcpy(choice, "YES");
                }

                /* Append entry to directory */
                if (strcmp (choice, "YES") == 0)
                {
                    directory->entries[nEntryCount].nPairCount = nPairCount;
                    for (i = 0; i < nPairCount; i++)
                    {
                        strcpy(directory->entries[nEntryCount].pair[i].language, temp.pair[i].language);
                        strcpy(directory->entries[nEntryCount].pair[i].translation, temp.pair[i].translation);
                    }
                    (directory->nEntryCount)++;
                    nEntryCount = directory->nEntryCount;
                }
            }

        } 
        fclose(existdata);
    }
    else printf("File cannot be opened\n");
}
