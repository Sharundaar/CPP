#include "converter.h"

/* The units in the french grammar */
char* units[] = {
    "zero",
	"un",
    "deux",
    "trois",
    "quatre",
    "cinq",
    "six",
    "sept",
    "huit",
    "neuf"
};

/* Some special number in the french grammar */
char* specials[] = {
	"onze",
	"douze",
	"treize",
	"quatorze",
	"quinze",
	"seize"
};

/* Global variable which represent the dizaine of the french grammar
 * each entry represent the 10*(i-1) dizaine
 */
char* dizaine[] = {
    "dix",
    "vingt",
    "trente",
    "quarante",
    "cinquante",
    "soixante",
    "soixante",
    "quatre vingt",
    "quatre vingt"
};


/* Global variable which represent 10^2, 10^3, 10^6, 10^9 */
char* puissancedix[] = {
    "cent",
	"mille",
    "million",
    "milliard"
};

int letter2intPacket(char* chaineNombre) {
    if(chaineNombre == NULL)
		return 0;

    char* ptr=chaineNombre;

    int result=0;

    /* Some variable to store the indexes */
    int i=0;
	int icent=0;
	int idiz=0;
	int iunit=0;

	/* Manage the hundred */

	/* First we get the index of the word "cent" in the string */
	icent = getFirstOccurenceInString(chaineNombre, "cent");
	if(icent > 0) {
		/* We collect everything before the word "cent" */
		char* temp = cutStringFromStart(chaineNombre, icent-1);
		char* trimed = temp;
		/* Trim it */
		trim(trimed);

		/* Collecting the hundred unit */
        int centaine = contains(units, 10, trimed);
		if(centaine > 0) {
            result+=100*centaine;
		} else {
            result+=100;
		}

		free(temp);

        /* We move the pointer beyond the hundred */
		ptr += icent+3;
	}

    /* Manage the dizaine */
    i=0;
    /* spec will indicate if we have a special dizaine as 90 or 70 */
    int spec=0;
    while(idiz == 0 && i < 9) {
        idiz = getFirstOccurenceInString(ptr, dizaine[i]);
        if(idiz > 5 && i!=1) {
            idiz=0;
            spec=1;
        }
        if(i == 1 && idiz > 5) {
            idiz = 0;
        }

        ++i;
    }
    if(idiz>0) {
        /* We move the cursor beyond the dizaine */
        ptr+=idiz + strlen(dizaine[i]) - 2;

        /* Special case : i = 6 (soixante) and i = 8 (quatre vingt) and we haven't detect any spec*/
        if(spec==0 && (i == 6 || i == 8)) {
            int j=0;
            iunit=0;
            while(iunit == 0 && j<6) {
                iunit = getFirstOccurenceInString(ptr, specials[j]);
                ++j;
            }

            if(iunit>0) {
                result += (i+1)*10 + j;
                int slength = strlen(specials[j]);
                ptr+=iunit+slength-1;
            } else {
                result += i*10;
            }
        } else {
            /* If spec = 1 we need to ass 10, we detect 8 for 90 */
            if(spec==1)
                result += (i+1)*10;
            else
                result += i*10;
        }
    }

    /* Manage units */
    i=0;
    iunit=0;
    while(iunit == 0 && i<10) {
        iunit = getFirstOccurenceInString(ptr, units[i]);
        ++i;
    }
    if(iunit>0) {
        /* We move the cursor beyond the unit */
        ptr+=iunit + strlen(units[i]) - 1;

        result += i-1;
    } else {
        i=0;
        while(iunit == 0 && i<6) {
            iunit = getFirstOccurenceInString(ptr, specials[i]);
            ++i;
        }
        if(iunit > 0) {
            int slength = strlen(specials[i]);
            ptr+=iunit+slength;
            result += 10 + i;
        }
    }

    ptr = NULL;
	return result;
}

unsigned int letter2int(char* chaineNombre) {
	unsigned int result=0;
	int i=0;
	int index=0;
	unsigned int tempresult=0;
	char* ptr = chaineNombre;

    do {
        i=4; /* We start from "milliard" */
        index=0;
        /* loop until we find a power of ten */
        while(index == 0 && i > 0) {
            --i;
            index = getFirstOccurenceInString(ptr, puissancedix[i]);
        }

        /* If we found a power of ten we must cut the string */
        if(i>0) {
            /* Temp will store the string we need */
            char* temp = (char*) malloc(sizeof(char) * index);
            memcpy(temp, ptr, index);
            temp[index-1] = '\0';
            tempresult = letter2intPacket(temp);
            if(tempresult == 0)
                tempresult=1;
            /* Here we check the multiplication necessary for the power */
            tempresult = tempresult * getPowerWithI(i);
            result += tempresult;

            /* Move beyond the power and free temp */
            ptr += index + strlen(puissancedix[i])-1;
            free(temp);
        }
    } while(i > 0);
    result += letter2intPacket(ptr);

	return result;
}

unsigned int getPowerWithI(int i) {
    switch(i) {
    case 0:
        return 100;

    case 1:
        return 1000;
    case 2:
        return 1000000;
    case 3:
        return 1000000000;
    default:
        return 1;
    }
}

char* int2letter(unsigned int value) {
    /* Setup a buffer */
    char* buff = (char*) malloc(BUFFER_SIZE * sizeof(char));
    if(buff == NULL)
        return NULL;
    buff[0]='\0';

    /* counter will store the power of ten */
    int counter=0;

    /* checking the zero */
	if(value == 0)
		return units[0];

    /* We loop until the value is null */
    while(value != 0) {
        /* check the counter for the power of ten, we don't want to check cent */
        if(counter > 0 && counter < 4) {
            insertAtStart(" ", buff);
            insertAtStart(puissancedix[counter], buff);
            if(value!=1) {
                insertAtStart(" ", buff);
            }
        }

        /* Here we collect a packet of 3 integers which correspond to the unit, thenth and hundred */
        int n1 = value % 10; /* unité */
        value /= 10;
        int n2 = value % 10; /* dizaine */
        value /= 10;
        int n3 = value % 10; /* centaine */
        value /= 10;

        /* Three specials cases, 1, 7 and 9 for dix, soixante dix and quatre vingt dix */
		if(n2 == 1 || n2 == 7 || n2 == 9) {
			if(n1 < 7 && n1 > 0) {
				insertAtStart(specials[n1-1], buff);
				/* must add et un if the unit is 1 and the dizaine != 1 and inferior to 8 */
                if(n1 == 1 && n2 != 1 && n2 < 8)
                        insertAtStart("et ", buff);
            } else if(n1 >= 7) {
				insertAtStart(units[n1], buff);
				insertAtStart(" ", buff);
				insertAtStart(dizaine[0], buff);
			}
        /* If we don't have a special unit we have to add the unit */
		} else if(n2 > 0) {
			if(n1 == 1 && n2 < 8) {
                insertAtStart(units[n1], buff);
                insertAtStart("et ", buff);
			} else if(n1 > 0) {
                insertAtStart(units[n1], buff);
			}
		} else if (counter > 0 && n1 > 1) {
            insertAtStart(units[n1], buff);
		} else if(counter == 0) {
            insertAtStart(units[n1], buff);
		}

		if(n2 > 1) {
            if(n1>0)
                insertAtStart(" ", buff);
			insertAtStart(dizaine[n2-1], buff);
		}

        /* The hundred is simple, if we have one we add it */
		if(n3 > 1) {
			insertAtStart(" ", buff);
			insertAtStart(puissancedix[0], buff);
			insertAtStart(" ", buff);
			insertAtStart(units[n3], buff);
		} else if(n3 > 0) {
			insertAtStart(" ", buff);
			insertAtStart(puissancedix[0], buff);
		}

		++counter;
	}

    /* We size a result to be exactly what we need */
	char* result = (char*) malloc(sizeof(char) * strlen(buff)+1);
	strcpy(result, buff);
	free(buff);

    return result;
}

char* cutStringFromStart(const char* str, int n) {
	int i;
	char* result = (char*) malloc(sizeof(char) * (n+1));
	if(result == NULL)
        return NULL;

	/* Simple copy from 0 to n-1*/
	for(i=0 ; i<n ; ++i) {
		result[i] = str[i];
	}
	result[n] = '\0';
	return result;
}

int getFirstOccurenceInString(const char* str1, const char* str2) {
	int index=0;
	int i=0;
	int j=0;
	int founded = 0;
	int lstr1 = strlen(str1);
	int lstr2 = strlen(str2);

    /* Some check for str1 and 2 to exists */
	if(str1 == NULL || str2 == NULL)
		return 0;

    /* We loop until we found str2 or we reach the end of str1 */
	while(i < lstr1 && founded == 0) {
        /* We begin the search when we find the first caracter of str2 */
		if(str1[i] == str2[0]) {
			index = i;
			j=0;
            /* we loop until we reach the end of str1, str2 or str1 is different from str2 */
			while(i < lstr1 && j < lstr2 && str2[j] == str1[i]) {
				j++;
				i++;
			}
			if(j == lstr2) {
				founded = 1;
			}
		}
		i++;
	}

    /* If we are here and haven't found str2 we return 0 */
	if(founded == 0)
		index = 0;
    else
        ++index; /* This put the index on the letter and not before */

	return index;
}

int contains(char* arr[], int arraySize, char* toCompare) {
    int i;

    /* We just compare every entry of arr until we find toCompare or we check all entries */
    for(i=0 ; i<arraySize ; ++i) {
        if(strcmp(arr[i], toCompare) == 0) {
            return i;
        }
    }

    return -1;
}

void trim(char* s) {
    /* ptr is our cursor */
	char *ptr;

	/* Some tests to check if s exist */
	if(!s)
		return;
	if(!*s)
		return;

	/* We loop from s[strlen]-1 to s until we reach s or we found a space */
	for(ptr = s+strlen(s)-1; (ptr>=s) && *ptr == ' '; --ptr);
	/* we put a EOF character were there were a space */
	ptr[1] = '\0';

    /* then we move s where their is no space */
	while(*s != ' ')
        ++s;

    /* Notice that this function loose the pointor s, so you need to store it for future free */
}

void insertAtStart(const char* source, char* dest) {
    /* Some check to see if source and dest exists */
    if(source != NULL && dest != NULL) {
        int sourceSize = strlen(source);
        int destSize = strlen(dest);

        int i;

        /* We shift dest to leave some space to source */
        for(i=destSize ; i>=0 ; --i) {
            dest[i+sourceSize] = dest[i];
        }

        /* inserting source at the begining of dest */
        for(i=0 ; i<sourceSize ; ++i) {
            dest[i] = source[i];
        }
    }

    /* Notice that this function need dest to have enought space */
}
