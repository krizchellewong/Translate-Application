#include <stdio.h>
#include <string.h>

#define MAXPAIR 10
#define MAXCHAR 20
#define MAXENTRY 150
#define MAXWORDS 75

typedef char str [21];
typedef char longStr[150];

typedef struct pairtag
{
    str language;
    str translation; 
}pairtype; 

typedef struct entrytag
{
    pairtype pair [MAXPAIR];
    int nPairCount;
}entrytype;

typedef struct directorytag
{
    entrytype entries [MAXENTRY];
    int nEntryCount; 
}directorytype;

typedef struct languagetag
{
    int languageCount[MAXWORDS];
    str languages[MAXWORDS];
} languagetype;

void getInput (char *string);
void getMenu (int *nMenu);
void getData (int *nData);
void toUpper (char *string);
void displayEntry (directorytype directory, int index, int nPairCount);
void getNewPair(directorytype * directory, int entryIndex);
void addEntry (directorytype *directory);
void addTranslation(directorytype * directory);
void sortAlphabetical(directorytype * directory, int entryIndex);
void displayAll (directorytype * directory);
void modifyEntry(directorytype * directory);
void deleteEntry (directorytype *directory);
void deleteTranslation(directorytype *directory);
void searchWord (directorytype *directory);
void searchTranslation(directorytype * directory);
void getLanguage (int *nOption);
void exportData (directorytype directory);
void importData (directorytype * directory);
void importDataTools(directorytype *directory);
void split(char *sentence, int *pCount, longStr words[MAXWORDS]);
int checkLanguages(languagetype * language, longStr lang);
int findWord(languagetype * language, directorytype * directory, int nCount, longStr words[]);
void identifyLanguage (directorytype *directory, languagetype *language);
void findOutput(directorytype * directory, longStr language, int nPairCount, longStr output, int entryIndex);
void simpleTranslation (directorytype *directory);


int 
main ()
{
    int entry, pair;
    int nMenu, nOption = 0;
    directorytype directory;
    languagetype language;
    int languagecount;
    directory.nEntryCount = 0;

    for (entry = 0; entry < MAXENTRY; entry++)
    {
        directory.entries[entry].nPairCount = 0;
        for (pair = 0; pair < MAXPAIR; pair++)
        {
            strcpy(directory.entries[entry].pair[pair].translation,"\0");
            strcpy(directory.entries[entry].pair[pair].language,"\0");
        }
    }

    for (languagecount = 0; languagecount < MAXWORDS; languagecount++)
        language.languageCount[languagecount] = 0;

    do
    {
        /* Display and get menu input */
        getMenu(&nMenu);

        if (nMenu == 1)
        {
            /* display manage data */
    
            do
            {
                getData(&nOption);
                switch (nOption)
                {
                    case 1: addEntry(&directory);
                            break;
                    case 2: addTranslation (&directory);
                            break;
                    case 3: modifyEntry(&directory);
                            break;
                    case 4: deleteEntry(&directory);
                            break;
                    case 5: deleteTranslation(&directory);
                            break;
                    case 6: displayAll(&directory);
                            break;
                    case 7: searchWord(&directory);
                            break;
                    case 8: searchTranslation(&directory);
                            break;
                    case 9: exportData(directory);
                            break;
                    case 10: importData(&directory);
                             break;
                }

            }
            while (nOption != 0);

            /* clear all entries*/
            directory.nEntryCount = 0;

            for (entry = 0; entry < MAXENTRY; entry++)
            {
                directory.entries[entry].nPairCount = 0;
                for (pair = 0; pair < MAXPAIR; pair++)
                {
                    strcpy(directory.entries[entry].pair[pair].translation,"\0");
                    strcpy(directory.entries[entry].pair[pair].language,"\0");
                }
            }
        }

        if (nMenu == 2)
        {
            importDataTools (&directory);
            do
            {
                getLanguage(&nOption);
                switch (nOption)
                {
                    case 1: identifyLanguage (&directory, &language);
                            break;
                    case 2: simpleTranslation (&directory);   
                            break; 
                }
                    
            } while (nOption != 0);
        }


    } while (nMenu != 0);


    return 0;
}


/* 
*
*
*
MANAGE DATA FUNCTIONS 
*
*
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

void 
getMenu(int *nMenu)
{
    char temp;
    printf("\n\t\tMAIN MENU\n");
    printf("_______________________________________________\n");
    printf("\'Manage Data\' allows you to  \n");
    printf("\'Language Tools\' allows you to \n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Manage Data\n");
    printf("\n[2] Language Tools\n");
    printf("\n[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nMenu);
    scanf("%c", &temp);
}

void
getData(int *nData)
{
    char temp;
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
    scanf("%c", &temp);
}

void 
toUpper(char * string)
{
    int i;
    int length = strlen(string);

    for (i = 0; i < length; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
            string[i] -= 32;
    }
}

void 
displayEntry (directorytype directory, int index, int nPairCount)
{
    int pair;
    printf ("\tLanguage\tTranslation\n");
    for (pair = 0; pair < nPairCount; pair++)
       printf ("(%d) %s\t%s\n", pair + 1, directory.entries[index].pair[pair].language, directory.entries[index].pair[pair].translation);
}

void
getNewPair(directorytype * directory, int entryIndex)
{
    str language, translation;
    int nPairCount; 

    printf ("Enter Language:");
    
    getInput(language);

    printf ("Enter translation:");
    getInput(translation);

    // Add pair count and Append to current entry
    directory->entries[entryIndex].nPairCount += 1; 
    nPairCount = directory->entries[entryIndex].nPairCount;

    strcpy (directory->entries[entryIndex].pair[nPairCount - 1].language, language);
    strcpy (directory->entries[entryIndex].pair[nPairCount - 1].translation, translation);
}

void 
addEntry (directorytype * directory)
{
    str language; 
    str translation;
    int entry, pair;
    int nFound = 0; 
    int nEntryCount, nPairCount; 
    str newEntry, newPair;

    // Ask for Input
    printf ("Enter Language:");
    getInput(language);

    printf ("Enter translation:");
    getInput(translation);

    // Check if pair exists
    for (entry = 0; entry < MAXENTRY; entry++)
    {
        for  (pair = 0; pair < MAXPAIR; pair++)
        {
            if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
            && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
                nFound = 1; 
        }
    }

    // if nFound == 1, show entries with the same information as the one entered first
    if (nFound == 1)
    {
        // Display first entries with the same info
        nEntryCount = directory->nEntryCount;
        for (entry = 0; entry < nEntryCount; entry++)
        {
            nPairCount = directory->entries[entry].nPairCount;
            for (pair = 0; pair < nPairCount; pair++)
            {
                if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
                && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
                {
                    displayEntry(*directory, entry, nPairCount);
                    pair = nPairCount;
                }
            }
            printf ("\n");
        }
            

        /*Then display all other entries
        for (entry = 0; entry < nEntryCount; entry++)
        {
            nPairCount = directory->entries[entry].nPairCount;
            for (pair = 0; pair < nPairCount; pair++)
            {
                if ((strcmp (language, directory->entries[entry].pair[pair].language) != 0)
                || (strcmp(translation, directory->entries[entry].pair[pair].translation) != 0))
                {
                    displayEntry(*directory, entry, nPairCount);
                    pair = nPairCount;
                }  
            }
            printf ("\n");
        }*/

        printf ("Is this a new entry (Yes or No)?");
        getInput(newEntry);

        toUpper(newEntry);


        if (strcmp (newEntry, "YES") == 0)
        {
            directory->nEntryCount += 1;
            nEntryCount = directory->nEntryCount;
            directory->entries[nEntryCount -1].nPairCount += 1; 
            nPairCount = directory->entries[nEntryCount -1].nPairCount;

            strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);

            // do while user does not choose NO
            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                getInput(newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
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

        // do while user does not choose NO
        do
        {
            printf ("Do you want to encode another pair(Yes/No)?");
            getInput(newPair);
            toUpper(newPair);

            if (strcmp (newPair, "YES") == 0)
            {
                // Enter new pair
                getNewPair(directory, nEntryCount - 1);
            }

        } while (strcmp (newPair, "YES") == 0);
        
    }
}

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
    
    // Enter new pair
    printf ("Enter Language:");
    getInput (language);

    printf ("Enter translation:");
    getInput (translation);

    // Check if entry exists
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
    // entry does not exist, when count is equal to 0
    if (nCount == 0)
    {
        printf ("Entry does not exist.\n");
        printf ("Please press the Add Entry Option");
    }   
    // entry exist, count is > 0
    else if (nCount > 0)
    {
        for (i = 0; i < nCount; i++)
        {
            index = tempentry[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf ("\n");
        }

        // if count == 1, language translation pair is asked and added to the same entry
        if (nCount == 1 && directory->entries[tempentry[0]].nPairCount < 10)
        {
            // Enter new pair
            printf ("Enter Language:");
            getInput (language);

            printf ("Enter translation:");
            getInput (translation);

            // Add pair count and Append to current entry
            directory->entries[tempentry[0]].nPairCount += 1; 
            nPairCount = directory->entries[tempentry[0]].nPairCount;

            strcpy (directory->entries[tempentry[0]].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[tempentry[0]].pair[nPairCount - 1].translation, translation);

            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                getInput(newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    //Enter new pair
                    getNewPair(directory, tempentry[0]);
                }

            } while (strcmp (newPair, "YES") == 0 && directory->entries[tempentry[0]].nPairCount <= 10);
        }
        /* if count > 1, user chooses what entry he chooses and  
        langauge translation pair is added to the entry he chooses*/
        else if (nCount > 1 && directory->entries[tempentry[0]].nPairCount < 10)
        {
            printf ("Choose Entry to add a language-translation pair:");
            scanf ("%d", &newentry);
            scanf("%c", &temp);

            // Enter new pair
            printf ("Enter Language:");
            getInput (language);

            printf ("Enter translation:");
            getInput (translation);

            // Add pair count and Append to chosen entry
            directory->entries[tempentry[newentry -1]].nPairCount += 1; 
            nPairCount = directory->entries[tempentry[newentry -1]].nPairCount;

            strcpy (directory->entries[tempentry[newentry -1]].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[tempentry[newentry -1]].pair[nPairCount - 1].translation, translation);
            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                getInput (newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    // Enter new pair
                    getNewPair(directory, tempentry[newentry -1]);
                }
            } while (strcmp (newPair, "YES") == 0 && directory->entries[tempentry[newentry -1]].nPairCount <= 10);
        }
    }
}


void 
sortAlphabetical(directorytype * directory, int entryIndex)
{
    int nPairCount; 
    int i, j, position;
    str temp[2];

    nPairCount = directory->entries[entryIndex].nPairCount;

    for(i = 0; i < nPairCount - 1; i++)
	{
		position = i;
		for(j = i + 1; j < nPairCount; j++)
		{
			if(strcmp (directory->entries[entryIndex].pair[position].language, directory->entries[entryIndex].pair[j].language) > 0)
                position = j;
		}
		if(position != i)
		{
			strcpy(temp[0], directory->entries[entryIndex].pair[i].language); 
            strcpy(temp[1], directory->entries[entryIndex].pair[i].translation);
			strcpy (directory->entries[entryIndex].pair[i].language, directory->entries[entryIndex].pair[position].language);
            strcpy (directory->entries[entryIndex].pair[i].translation, directory->entries[entryIndex].pair[position].translation);
			strcpy (directory->entries[entryIndex].pair[position].language, temp[0]);
            strcpy (directory->entries[entryIndex].pair[position].translation, temp[1]);
		}
	}
}

void
displayAll (directorytype * directory)
{ 
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int i = 0;
    char cOption;
    char cTemp;

    if (nEntryCount == 0)
        printf("There are no entries to be displayed\n");

    while (i < nEntryCount)
    {
        sortAlphabetical(directory, i);
        nPairCount = directory->entries[i].nPairCount;
        printf("Entry #%d\n", i+1);
        displayEntry(*directory, i, nPairCount);
        printf("_______________________________________________\n");
        printf("[N] Next Entry\n");
        printf("[P] Previous Entry\n");
        printf("[X] End Display\n");
        printf("_______________________________________________\n");
        printf("Enter option: ");
        scanf("%c", &cOption);
        scanf("%c", &cTemp);

        if (cOption == 'N')
            i++;
        else if (cOption == 'P')
            i--;
        else if (cOption == 'X')
            i = nEntryCount;
        else
            printf("Invalid Option");
            
    }
 
}

void
modifyEntry(directorytype * directory)
{
    int nEntry, nPair;
    char temp;
    str choice, input, modify;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    displayAll(directory);

    printf("Which entry do you want to modify? ");
    scanf("%d", &nEntry);
    scanf("%c", &temp);
    if (!(nEntry >= 1 && nEntry <= nEntryCount))
    {
        printf("Invalid Input\n");
    }
    else
    {
        nPairCount = directory->entries[nEntry-1].nPairCount;

        do 
        {
            
            do
            {
                printf("Which pair do you want to modify? ");
                scanf("%d", &nPair);
                scanf("%c", &temp);
                if (!(nPair >= 1 && nPair <= nPairCount))
                    printf("Invalid Input\n");

            } while (!(nPair >= 1 && nPair <= nPairCount));

            do
            {
                
                printf ("Modify language or translation: ");
                getInput(choice);
                toUpper (choice);

                if (strcmp (choice, "LANGUAGE") == 0)
                {
                    printf ("Input language:");
                    getInput (input);
                    strcpy (directory->entries[nEntry -1].pair[nPair -1].language, input);
                }
                else if (strcmp(choice, "TRANSLATION") == 0)
                {
                    printf ("Input translation:");
                    getInput (input);

                    strcpy(directory->entries[nEntry-1].pair[nPair -1].translation, input);
    
                }
                else
                    printf("Invalid Input\n");
                
            } while (!(strcmp(choice, "TRANSLATION") == 0 || strcmp (choice, "LANGUAGE") == 0));
            
            printf ("More modifications for the entry (Yes/No)?");
            getInput (modify);
            toUpper(modify);

        } while (strcmp(modify, "YES") == 0);
    
    }
}

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
            for (j = 0; j < nPairCount; j++)
            {
                strcpy(directory->entries[i].pair[j].translation,"\0");
                strcpy(directory->entries[i].pair[j].language,"\0");
            }

            nPairCount = directory->entries[i + 1].nPairCount;
            for (j = 0; j < nPairCount; j++)
            {
                strcpy(directory->entries[i].pair[j].translation, directory->entries[i + 1].pair[j].translation);
                strcpy(directory->entries[i].pair[j].language, directory->entries[i + 1].pair[j].language);
            }
        }

        for (j = 0; j < nPairCount; j++)
        {
            strcpy(directory->entries[nEntryCount-1].pair[j].translation,"\0");
            strcpy(directory->entries[nEntryCount-1].pair[j].language,"\0");
        }
        directory->nEntryCount -= 1;
        nEntryCount = directory->nEntryCount;
        
    }
    else printf("Invalid Input\n");

}
void
deleteTranslation(directorytype *directory)
{
    int deletePair, nPairCount, entry;
    int nEntryCount = directory->nEntryCount; 
    char temp;
    int i;
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
            if (nPairCount == 1)
                deleteEntry(directory);
            else
            {
                do
                {
                    printf("Which language-translation pair do you want to delete? ");
                    scanf("%d", &deletePair);
                    scanf("%c", &temp);
                    if (!(deletePair >= 1 && deletePair <= nPairCount))
                    {
                        printf("Invalid Input\n");
                        printf("Do you still want to delete a pair (Yes/No)? ");
                        getInput (choice);
                        toUpper (choice);
                    }

                } while (!(!(deletePair >= 1 && deletePair <= nPairCount) || strcmp(choice, "YES") == 0));

            
                if (strcmp(choice, "YES") == 0)
                {
                    for (i = deletePair - 1; i < nPairCount - 1; i++)
                    {
                        strcpy (directory->entries[entry-1].pair[i].language, directory->entries[entry-1].pair[i+1].language);
                        strcpy (directory->entries[entry-1].pair[i].translation, directory->entries[entry-1].pair[i+1].translation);
                    } 
                    
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
    else printf ("Invalid Input\n");
}

void
searchWord (directorytype *directory)
{
    str word;
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount, nCount = 0;
    int tempMatch[MAXENTRY];
    int index, i;

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
    if (nCount > 0)
    {
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

void 
searchTranslation(directorytype * directory)
{
    str language, translation;
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount, nCount = 0;
    int tempMatch[MAXENTRY];
    int index, i;

    printf ("Input language: ");
    getInput(language);
    printf("Input translation: ");
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

    if (nCount > 0)
    {
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

void
exportData (directorytype directory)
{
    char filename [40];
    int i;
    int nEntryCount = directory.nEntryCount;
    int nPairCount;
    int pair;
    FILE *savedata;

    
    // save all data into a text file 

    printf("Input filename: ");
    getInput (filename);
    savedata = fopen(filename, "w");

    if (savedata != NULL)
    {
        for (i = 0; i < nEntryCount; i++)
        {
            nPairCount = directory.entries[i].nPairCount;
            for (pair = 0; pair < nPairCount; pair++)
                fprintf (savedata, "%s: %s\n", directory.entries[i].pair[pair].language, directory.entries[i].pair[pair].translation);
            if (i != nEntryCount - 1)
                fprintf(savedata, "\n");
        }
    }
    else
    {
        printf("File cannot be opened\n");
    }
     
    fclose(savedata);

}


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


    // open text file
    printf("Input filename: ");
    getInput(filename);
    existdata = fopen(filename , "r");

    if (existdata != NULL)
    {
        // until it encounters a double enter, that's the time that it is considered another entry
        while (!feof(existdata))
        {
            temp.nPairCount = 0;
            nPairCount = temp.nPairCount;
            newEntry = 0;
            strcpy(checkEntry, "");
            do
            {
                if (nPairCount == 0)
                {
                    fscanf (existdata, "%s", language);
                    langlength = strlen(language);
                    language[langlength - 1] = '\0';
                    strcpy (temp.pair[nPairCount].language, language);
          
                    // store to an array
                    fscanf (existdata, "%c", tempspace);
                    fscanf (existdata, "%[^\n]s", translation);
                    strcpy (temp.pair[nPairCount].translation, translation);
                    //fgets(translation, MAXCHAR, existdata);
                    nPairCount++;
                    temp.nPairCount = nPairCount;
             
                }
                fgets (checkEntry, 2, existdata);
                fgets (checkEntry2, 2, existdata);
                
      
                if (strcmp(checkEntry2, "\n") == 0 || feof(existdata))
                {
                    // indicates a new entry
                    newEntry = 1;
                }
                else 
                {
                    strcpy (language, checkEntry2);
                    fscanf (existdata, "%s", tempword);
                    strcat(language, tempword);
                    
                    langlength = strlen(language);
                    language[langlength - 1] = '\0';
                    strcpy (temp.pair[nPairCount].language, language);
                
                    // store to an array
                    fscanf (existdata, "%c", tempspace);
                    fscanf (existdata, "%[^\n]s", translation);
                    strcpy (temp.pair[nPairCount].translation, translation);

                    nPairCount++;
                    temp.nPairCount = nPairCount;

                }
            } while (newEntry == 0);

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
            else
            {
                strcpy(choice, "YES");
            }

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
    else printf("File cannot be opened\n");

    // read data stored in text file 
    // user inputs filename to load 
    // retrieves entry by entry 
    // checks if entry is already present in the list of entries

    fclose(existdata);
}


/* 
*
*
* 
LANGUAGE TRANSLATE FUNCTIONS 
*
*
*/
void
getLanguage(int *nOption)
{
    char temp;
    printf("\n\t\tLANGUAGE TOOLS\n");
    printf("_______________________________________________\n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Identify Main Language");
    printf("\n[2] Simple Translation\n");
    printf("\n[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nOption);
    scanf("%c", &temp);
}

void
importDataTools(directorytype *directory)
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
    str tempword, tempspace;
    int i;


    // open text file
    printf("Input filename: ");
    getInput(filename);
    existdata = fopen(filename , "r");

    if (existdata != NULL)
    {
        // until it encounters a double enter, that's the time that it is considered another entry
        while (!feof(existdata))
        {
            temp.nPairCount = 0;
            nPairCount = temp.nPairCount;
            newEntry = 0;
            strcpy(checkEntry, "");
            do
            {
                if (nPairCount == 0)
                {
                    fscanf (existdata, "%s", language);
                    langlength = strlen(language);
                    language[langlength - 1] = '\0';
                    strcpy (temp.pair[nPairCount].language, language);
          
                    // store to an array
                    fscanf (existdata, "%c", tempspace);
                    fscanf (existdata, "%[^\n]s", translation);
                    strcpy (temp.pair[nPairCount].translation, translation);
                    //fgets(translation, MAXCHAR, existdata);
                    nPairCount++;
                    temp.nPairCount = nPairCount;
             
                }
                fgets (checkEntry, 2, existdata);
                fgets (checkEntry2, 2, existdata);
                
      
                if (strcmp(checkEntry2, "\n") == 0 || feof(existdata))
                {
                    // indicates a new entry
                    newEntry = 1;
                }
                else 
                {
                    strcpy (language, checkEntry2);
                    fscanf (existdata, "%s", tempword);
                    strcat(language, tempword);
                    
                    langlength = strlen(language);
                    language[langlength - 1] = '\0';
                    strcpy (temp.pair[nPairCount].language, language);
                
                    // store to an array
                    fscanf (existdata, "%c", tempspace);
                    fscanf (existdata, "%[^\n]s", translation);
                    strcpy (temp.pair[nPairCount].translation, translation);


                    nPairCount++;
                    temp.nPairCount = nPairCount;
                }
            } while (newEntry == 0);

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
    else printf("File cannot be opened\n");

    fclose(existdata);
    
}

void 
split(char *sentence, int *pCount, longStr words[MAXWORDS])
{
    int i, j = 0, length;
    *pCount = 0;
    //included the index where the '\0' is to include the last word
    length =  strlen(sentence);
    for (i = 0; i <= length; i++)
    {
        if (sentence[i] != ' ' && sentence[i] != '\0')
        {
            if (!(sentence[i] == '.' || sentence[i] == ',' || sentence[i] == '!' || sentence[i] == '?'))
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

int 
checkLanguages(languagetype * language, longStr lang)
{
    int i;
    
    for (i = 0; i < MAXWORDS; i++)
    {
        if (strcmp(language->languages[i], lang) == 0)
            return i;
    }
    return 0;
}

int 
findWord(languagetype * language, directorytype * directory, int nCount, longStr words[])
{
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int index;
    int word;
    int i;
    int nLangCount = 0;


    for (word = 0; word < nCount; word++)
    {
        for (entry = 0; entry < nEntryCount; entry++)
        {
            nPairCount = directory->entries[entry].nPairCount;
            for  (pair = 0; pair < nPairCount; pair++)
            {
                if (strcmp(words[word], directory->entries[entry].pair[pair].translation) == 0)
                {
                    if (checkLanguages(language, directory->entries[entry].pair[pair].language) == 0)
                    {
                        i = nLangCount;
                        strcpy (language->languages[i], directory->entries[entry].pair[pair].language);
                        nLangCount++;
                    }
                    else
                    {
                        index = checkLanguages(language, directory->entries[entry].pair[pair].language);
                        language->languageCount[index] += 1;
                    }
                    
                }
            }
        }
    }
    return nLangCount;
}


void
identifyLanguage (directorytype *directory, languagetype *language)
{
    longStr sentence;
    longStr words[MAXWORDS];
    int nCount = 0;
    int nLangCount = 0;
    int word;
    int temp = 0;
    int nHighestIndex;
    printf("Enter a phrase or sentence: ");
    getInput (sentence);

    
    split(sentence, &nCount, words);
    nLangCount = findWord (language, directory, nCount, words);

    for (word = 0; word < MAXWORDS; word++)
    {
        if (temp < language->languageCount[word])
        {
            temp = language->languageCount[word];
            nHighestIndex = word;
        }
    }

    if (nLangCount == 0)
        printf("Cannot determine the language\n");
    else 
        printf ("Main language: %s\n", language->languages[nHighestIndex]);
    
}

void
findOutput(directorytype * directory, longStr language, int nPairCount, longStr output, int entryIndex)
{
    int i;
    
    for (i = 0; i < nPairCount; i++)
    {
        if (strcmp (language, directory->entries[entryIndex].pair[i].language) == 0)
        {
           
                strcpy (output, directory->entries[entryIndex].pair[i].translation);
          
        }
            
    }
}

void
simpleTranslation (directorytype *directory)
{
    longStr source, output;
    longStr words[MAXWORDS];
    int nCount = 0, word;
    str langoutput, langsource;
    str choice;
    int entry, pair, nPairCount; 
    int nEntryCount = directory->nEntryCount;
    int translated = 0;
    int nCycle = 0;
    
    printf ("Enter language of source text:");
    getInput(langsource);
    printf("Enter source text: ");
    getInput(source);
    printf("Enter language to be translated to: ");
    getInput(langoutput);
    
    do
    {
        if (nCycle > 0)
        {
            printf("Enter source text: ");
            getInput(source);
        }

        split (source, &nCount, words);


        for (word = 0; word < nCount; word++)
        {
            translated = 0;

            for (entry = 0; entry < nEntryCount; entry++)
            {
        
                nPairCount = directory->entries[entry].nPairCount;
                for (pair = 0; pair < nPairCount; pair++)
                {
                
                    if (strcmp(words[word], directory->entries[entry].pair[pair].translation) == 0)
                    {
                        if (strcmp (langsource, directory->entries[entry].pair[pair].language) == 0)
                        {
                            findOutput (directory, langoutput, nPairCount, output, entry);
                            printf("%s ", output);
                            translated = 1;
                        }
                    }

                } 
            }
            if (translated == 0)
                printf("%s ", words[word]);
        }   
        printf ("\n");
        printf("Do you want to translate another text in %s to %s? (Yes/No)", langsource, langoutput);
        getInput(choice);
        toUpper(choice);
        
        nCycle++;
        
    } while (strcmp(choice, "YES") == 0);

}
