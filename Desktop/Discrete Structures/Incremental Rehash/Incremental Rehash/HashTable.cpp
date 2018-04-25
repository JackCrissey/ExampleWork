//
//  HashTable.cpp
//  Incremental Rehash
//
//  Created by Jack Crissey on 5/3/17.
//  Copyright © 2017 Jack Crissey. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdexcept>
#include "HashTable.h"
#include "primes.h"
using namespace std;

char * const HashTable::DELETED  = (char *) 1 ;

/*This is the constructor for the hash table it creates Hash Table A which is the original table and 
 sets the other 2 tables that used for rehashing to NULL just to make it easier to identify which tables
 are currently being used. It also initializes all of the table information and sets the capacity of
 table A. It also checks to make sure that someone or the program isnt trying to create a table larger
 that 200,000 slots, because it should never reach a size of 200,000 unless something really messed up
 happens. It also makes sure that the table size isnt less than 101 and if it is then it automatically
 sets the value to 101.*/
HashTable::HashTable(int n)
{
    //Makes sure table isnt greater that 200,000
    if(n < 200000)
    {
        //Makes sure table isnt less than 101.
        if(n < 101)
        {
            n = 101;
        }
        //This is the value that primeNumSearch is storing it's answer in. Set to -1 for precausion.
        answer = -1;
        //Finds the nearest prime number to the value n.
        primeNumSearch(n, 0, numPrimes-1);
        n = answer;
        //Creates table A
        A = new char*[n]();
        B = NULL;
        C = NULL;
        //Initailizes values
        Rehashing = false;
        isRehashingToA = true;
        isRehashingToB = false;
        isRehashingToC = false;
        ACapacity = n;
        BCapacity = 0;
        CCapacity = 0;
        ASize = 0;
        BSize = 0;
        CSize = 0;
        AInserts = 0;
        BInserts = 0;
        CInserts = 0;
    }
    else
    {
        //Throws and out of range if the array size tries to exceed 200,000
        throw out_of_range("Size of the Hash Table is to large. It is greater that 200,000.");
    }
}

/*This is the insert it checks what table is currently being hashed to and will try and insert the item.
 If the item is already in the array it will just ignore the insert and move on and not insert the item.
 It will also wrap around to the other end of the array if needed to insert a new item if the linear 
 probe requires it.*/

void HashTable::insert(const char *str)
{
    /*The couple of lines are used to copy the const char string
     into a char string that using a malloc command.*/
    int temp = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        temp++;
    }
    temp++;
    char * newStr = (char*) malloc(temp*sizeof(char)+1);
    strcpy ((char*)newStr,str);
    
    //Determines that hash value of the string
    unsigned int hash = hashCode(str);
    
    //Using the find program to determine if the string is already in the table
    bool inTable = false;
    if(find(newStr))
    {
        inTable = true;
    }
    
    /*If the values are hashing to A and the word isnt already in the table*/
    if(isRehashingToA && !inTable)
    {
        //Adds one to the size of the able and the number of inserts into the table
        ASize++;
        AInserts++;
        //Figures out the Hash Value used for that specific array
        int arraySlot = hash % ACapacity;
        
        //If the slot hashed to has a value in it already
        if(A[arraySlot] != NULL && A[arraySlot] != DELETED)
        {
            int newSlot = 0;
            //Iterates until it finds an empty slot or it reaches the end of the array
            for(int i = arraySlot; A[i] != NULL && A[i] != DELETED; i++)
            {
                newSlot = i+1;
                if(i == ACapacity-1)
                {
                    i = 0;
                }
            }
            /*If it reaches the end of the array then it will wrap around to the
             front of the array and keep checking until it reaches an empty slot*/
            if(newSlot == ACapacity)
            {
                newSlot = 0;
                
                for(int i = 0; A[i] != NULL && A[i] != DELETED; i++)
                {
                    newSlot = i+1;
                }
            }
            //Stores the value in the new slot
            A[newSlot] = newStr;
            //Checks to make sure that the insert didnt probe more than 9 slots
            if((newSlot - arraySlot) >= 9 )
            {
                //If it did and their are still 2 hash tables then the program will do a resort rehash where it will dump everything from those last 2 arrays into a new array.
                if(C != NULL)
                {
                    resortRehash('B');
                }
                //If their is just 1 hash table then it will call to start hashing to another hashtable with just the rehash function.
                else
                {
                    startRehashingToB();
                    reHash(arraySlot, newSlot);
                }
            }
        }
        //If their is nothing in the slot the program is trying to hash to it will just insert into that arrayslot.
        else
        {
            A[arraySlot] = newStr;
        }
        //The program now checks to make sure that the array size doesnt have a greater magnatude than .5. If it does then it will start rehashing.
        if(ASize > ACapacity/2)
        {
            //If 2 tables already exist
            if(C != NULL)
            {
                resortRehash('B');
            }
            //If 1 table exists
            else
            {
                startRehashingToB();
            }
        }
    }
    
    /*If the values are hashing to B and the word isnt already in the table*/
    else if(isRehashingToB && !inTable)
    {
        //Adds one to the size of the able and the number of inserts into the table
        BSize++;
        BInserts++;
        //Figures out the Hash Value used for that specific array
        int arraySlot = hash % BCapacity;
        //If the slot hashed to has a value in it already
        if(B[arraySlot] != NULL && B[arraySlot] != DELETED)
        {
            int newSlot = 0;
            //Iterates until it finds an empty slot or it reaches the end of the array
            for(int i = arraySlot; B[i] != NULL && B[i] != DELETED; i++)
            {
                newSlot = i+1;
                if(i == BCapacity-1)
                {
                    i = 0;
                }
            }
            /*If it reaches the end of the array then it will wrap around to the
             front of the array and keep checking until it reaches an empty slot*/
            if(newSlot == BCapacity)
            {
                newSlot = 0;
                
                for(int i = 0; B[i] != NULL && B[i] != DELETED; i++)
                {
                    newSlot = i+1;
                }
            }
            //Stores the value in the new slot
            B[newSlot] = newStr;
            //Checks to make sure that the insert didnt probe more than 9 slots
            if((newSlot - arraySlot) >= 9)
            {
                //If it did and their are still 2 hash tables then the program will do a resort rehash where it will dump everything from those last 2 arrays into a new array.
                if(A != NULL)
                {
                    resortRehash('C');
                }
                //If their is just 1 hash table then it will call to start hashing to another hashtable with just the rehash function.
                else
                {
                    startRehashingToC();
                    reHash(arraySlot, newSlot);
                }
            }
        }
        //If their is nothing in the slot the program is trying to hash to it will just insert into that arrayslot.
        else
        {
            B[arraySlot] = newStr;
        }
        //The program now checks to make sure that the array size doesnt have a greater magnatude than .5. If it does then it will start rehashing.
        if(BSize > BCapacity/2)
        {
            //If 2 tables already exist
            if(A != NULL)
            {
                resortRehash('C');
            }
            //If 1 table exists
            else
            {
                startRehashingToC();
            }
        }
    }
    
    /*If the values are hashing to C and the word isnt already in the table*/
    else if(isRehashingToC && !inTable)
    {
        //Adds one to the size of the able and the number of inserts into the table
        CSize++;
        CInserts++;
        //Figures out the Hash Value used for that specific array
        int arraySlot = hash % CCapacity;
        //If the slot hashed to has a value in it already
        if(C[arraySlot] != NULL && C[arraySlot] != DELETED)
        {
            int newSlot = 0;
            //Iterates until it finds an empty slot or it reaches the end of the array
            for(int i = arraySlot; C[i] != NULL && C[i] != DELETED; i++)
            {
                newSlot = i+1;
                if(i == CCapacity-1)
                {
                    i = 0;
                }
            }
            /*If it reaches the end of the array then it will wrap around to the
             front of the array and keep checking until it reaches an empty slot*/
            if(newSlot == CCapacity)
            {
                newSlot = 0;
                
                for(int i = 0; C[i] != NULL && C[i] != DELETED; i++)
                {
                    newSlot = i+1;
                }
            }
            //Stores the value in the new slot
            C[newSlot] = newStr;
            //Checks to make sure that the insert didnt probe more than 9 slots
            if((newSlot - arraySlot) >= 9)
            {
                //If it did and their are still 2 hash tables then the program will do a resort rehash where it will dump everything from those last 2 arrays into a new array.
                if(B != NULL)
                {
                    resortRehash('A');
                }
                //If their is just 1 hash table then it will call to start hashing to another hashtable with just the rehash function.
                else
                {
                    startRehashingToA();
                    reHash(arraySlot, newSlot);
                }
            }
        }
        //If their is nothing in the slot the program is trying to hash to it will just insert into that arrayslot.
        else
        {
            C[arraySlot] = newStr;
        }
        //The program now checks to make sure that the array size doesnt have a greater magnatude than .5. If it does then it will start rehashing.
        if(CSize > CCapacity/2)
        {
            //If 2 tables already exist
            if(B != NULL)
            {
                resortRehash('A');
            }
            //If 1 table exists
            else
            {
                startRehashingToA();
            }
        }
    }
}

/*This is the remove function of the hash table. If the item exists in the table it will delete that
 item from the table by first replacing the item with a DELETED const char statement and then returning
 the char value back to the driver where it can be read and subsequently be freed by the driver. If a 
 value is not found it will return NULL*/
char * HashTable::remove(const char *str)
{
    /*If the table is already rehashing and the size of the original array has dropped below
     3% of the total array capacity of the array then it will move the rest of the items over
     to the table being rehashed to.*/
    if(A != NULL && B != NULL)
    {
        float capacity = ACapacity;
        float dev = ASize/capacity;
        if(dev < .03 && AInserts/capacity > .03)
        {
            resortRehash('B');
        }
    }
    if(B != NULL && C != NULL)
    {
        float capacity = BCapacity;
        float dev = BSize/capacity;
        if(dev < .03 && BInserts/capacity > .03)
        {
            resortRehash('C');
        }
    }
    if(C != NULL && A != NULL)
    {
        float capacity = CCapacity;
        float dev = CSize/capacity;
        if(dev < .03 && CInserts/capacity > .03)
        {
            resortRehash('A');
        }
    }
    
    /*The couple of lines are used to copy the const char string
     into a char string that using a malloc command.*/
    int temp = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        temp++;
    }
    char * newStr = (char *) malloc(temp*sizeof(char)+1);
    strcpy (newStr,str);
    
    //Determines that hash value of the string
    unsigned int hash = hashCode(str);
    
    //If table A exists then it will search this table to remove the item from
    if(A != NULL)
    {
        //Determines the hash slot it wants to insert the data item into
        int arraySlot = hash % ACapacity;
        
        //If the array slot has a value in it
        if(A[arraySlot] != NULL)
        {
            //If the value in the array slot is not deleted
            if(A[arraySlot] != DELETED)
            {
                //If the string equals the value in the array slot it will remove that value
                if(strcmp(A[arraySlot], newStr) == 0)
                {
                    free(A[arraySlot]);
                    A[arraySlot] = DELETED;
                    ASize--;
                    if(isRehashingToB)
                    {
                        reHash(arraySlot, arraySlot);
                    }
                    return newStr;
                }
                //The program will iterate through the array until it finds the value of hits a NULL space.
                else
                {
                    //Increase the arrayslot size by 1 to move to the next array slot value
                    arraySlot++;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < ACapacity && A[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(A[arraySlot] != DELETED)
                        {
                            //Compares the item in the current array slot with the string value to see if they are the same
                            if(strcmp(A[arraySlot], newStr) == 0)
                            {
                                free(A[arraySlot]);
                                //Deletes the value in the array slot
                                A[arraySlot] = DELETED;
                                //Reduces the size of the array by one
                                ASize--;
                                //If the array is rehashing that it will also move the items in the deleted items group
                                //over to the new array
                                if(isRehashingToB)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                //return the string value
                                return newStr;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                    //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                    if(arraySlot == ACapacity)
                    {
                        //resets arraySlot
                        arraySlot = 0;
                        //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                        while(arraySlot < ACapacity && A[arraySlot] != NULL)
                        {
                            //If the array slot isnt deleted
                            if(A[arraySlot] != DELETED)
                            {
                                //Compares the item in the current array slot with the string value to see if they are the same
                                if(strcmp(A[arraySlot], newStr) == 0)
                                {
                                    free(A[arraySlot]);
                                    //Deletes the value in the array slot
                                    A[arraySlot] = DELETED;
                                    //Reduces the size of the array by one
                                    ASize--;
                                    //If the array is rehashing that it will also move the items in the deleted items group
                                    //over to the new array
                                    if(isRehashingToB)
                                    {
                                        reHash(arraySlot, arraySlot);
                                    }
                                    //return the string value
                                    return newStr;
                                }
                            }
                            //advance through the array
                            arraySlot++;
                        }
                    }
                    //If it isnt found then the program will still move that group of data from the old table to the new table.
                    if(isRehashingToB)
                    {
                        reHash(arraySlot-1, arraySlot-1);
                    }
                }
            }
            //The program will iterate through the array until it finds the value of hits a NULL space.
            else
            {
                //Increase the arrayslot size by 1 to move to the next array slot value
                arraySlot++;
                //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                while(arraySlot < ACapacity && A[arraySlot] != NULL)
                {
                    //If the array slot isnt deleted
                    if(A[arraySlot] != DELETED)
                    {
                        //Compares the item in the current array slot with the string value to see if they are the same
                        if(strcmp(A[arraySlot], newStr) == 0)
                        {
                            free(A[arraySlot]);
                            //Deletes the value in the array slot
                            A[arraySlot] = DELETED;
                            //Reduces the size of the array by one
                            ASize--;
                            //If the array is rehashing that it will also move the items in the deleted items group
                            //over to the new array
                            if(isRehashingToB)
                            {
                                reHash(arraySlot, arraySlot);
                            }
                            //return the string value
                            return newStr;
                        }
                    }
                    //advance through the array
                    arraySlot++;
                }
                //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                if(arraySlot == ACapacity)
                {
                    //resets arraySlot
                    arraySlot = 0;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < ACapacity && A[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(A[arraySlot] != DELETED)
                        {
                            //Compares the item in the current array slot with the string value to see if they are the same
                            if(strcmp(A[arraySlot], newStr) == 0)
                            {
                                free(A[arraySlot]);
                                //Deletes the value in the array slot
                                A[arraySlot] = DELETED;
                                //Reduces the size of the array by one
                                ASize--;
                                //If the array is rehashing that it will also move the items in the deleted items group
                                //over to the new array
                                if(isRehashingToB)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                //return the string value
                                return newStr;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                }
                //If it isnt found then the program will still move that group of data from the old table to the new table.
                if(isRehashingToB)
                {
                    reHash(arraySlot-1, arraySlot-1);
                }
            }
        }
    }
    
    //If table B exists then it will search this table to remove the item from
    if(B != NULL)
    {
        //Determines the hash slot it wants to insert the data item into
        int arraySlot = hash % BCapacity;
        //If the array slot has a value in it
        if(B[arraySlot] != NULL)
        {
            //If the value in the array slot is not deleted
            if(B[arraySlot] != DELETED)
            {
                //If the string equals the value in the array slot it will remove that value
                if(strcmp(B[arraySlot], newStr) == 0)
                {
                    free(B[arraySlot]);
                    B[arraySlot] = DELETED;
                    BSize--;
                    if(isRehashingToC)
                    {
                        reHash(arraySlot, arraySlot);
                    }
                    return newStr;
                }
                //The program will iterate through the array until it finds the value of hits a NULL space.
                else
                {
                    //Increase the arrayslot size by 1 to move to the next array slot value
                    arraySlot++;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < BCapacity && B[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(B[arraySlot] != DELETED)
                        {
                            //Compares the item in the current array slot with the string value to see if they are the same
                            if(strcmp(B[arraySlot], newStr) == 0)
                            {
                                free(B[arraySlot]);
                                //Deletes the value in the array slot
                                B[arraySlot] = DELETED;
                                //Reduces the size of the array by one
                                BSize--;
                                //If the array is rehashing that it will also move the items in the deleted items group
                                //over to the new array
                                if(isRehashingToC)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                //return the string value
                                return newStr;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                    //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                    if(arraySlot == BCapacity)
                    {
                        //resets arraySlot
                        arraySlot = 0;
                        //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                        while(arraySlot < BCapacity && B[arraySlot] != NULL)
                        {
                            //If the array slot isnt deleted
                            if(B[arraySlot] != DELETED)
                            {
                                //Compares the item in the current array slot with the string value to see if they are the same
                                if(strcmp(B[arraySlot], newStr) == 0)
                                {
                                    free(B[arraySlot]);
                                    //Deletes the value in the array slot
                                    B[arraySlot] = DELETED;
                                    //Reduces the size of the array by one
                                    BSize--;
                                    //If the array is rehashing that it will also move the items in the deleted items group
                                    //over to the new array
                                    if(isRehashingToC)
                                    {
                                        reHash(arraySlot, arraySlot);
                                    }
                                    //return the string value
                                    return newStr;
                                }
                            }
                            //advance through the array
                            arraySlot++;
                        }
                    }
                    //If it isnt found then the program will still move that group of data from the old table to the new table.
                    if(isRehashingToC)
                    {
                        reHash(arraySlot-1, arraySlot-1);
                    }
                }
            }
            //The program will iterate through the array until it finds the value of hits a NULL space.
            else
            {
                //Increase the arrayslot size by 1 to move to the next array slot value
                arraySlot++;
                //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                while(arraySlot < BCapacity && B[arraySlot] != NULL)
                {
                    //If the array slot isnt deleted
                    if(B[arraySlot] != DELETED)
                    {
                        //Compares the item in the current array slot with the string value to see if they are the same
                        if(strcmp(B[arraySlot], newStr) == 0)
                        {
                            free(B[arraySlot]);
                            //Deletes the value in the array slot
                            B[arraySlot] = DELETED;
                            //Reduces the size of the array by one
                            BSize--;
                            //If the array is rehashing that it will also move the items in the deleted items group
                            //over to the new array
                            if(isRehashingToC)
                            {
                                reHash(arraySlot, arraySlot);
                            }
                            //return the string value
                            return newStr;
                        }
                    }
                    //advance through the array
                    arraySlot++;
                }
                //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                if(arraySlot == BCapacity)
                {
                    //resets arraySlot
                    arraySlot = 0;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < BCapacity && B[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(B[arraySlot] != DELETED)
                        {
                            //Compares the item in the current array slot with the string value to see if they are the same
                            if(strcmp(B[arraySlot], newStr) == 0)
                            {
                                free(B[arraySlot]);
                                //Deletes the value in the array slot
                                B[arraySlot] = DELETED;
                                //Reduces the size of the array by one
                                BSize--;
                                //If the array is rehashing that it will also move the items in the deleted items group
                                //over to the new array
                                if(isRehashingToC)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                //return the string value
                                return newStr;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                }
                //If it isnt found then the program will still move that group of data from the old table to the new table.
                if(isRehashingToC)
                {
                    reHash(arraySlot-1, arraySlot-1);
                }
            }
        }
    }
    
    //If table C exists then it will search this table to remove the item from
    if(C != NULL)
    {
        //Determines the hash slot it wants to insert the data item into
        int arraySlot = hash % CCapacity;
        //If the array slot has a value in it
        if(C[arraySlot] != NULL)
        {
            //If the value in the array slot is not deleted
            if(C[arraySlot] != DELETED)
            {
                //If the string equals the value in the array slot it will remove that value
                if(strcmp(C[arraySlot], newStr) == 0)
                {
                    free(C[arraySlot]);
                    C[arraySlot] = DELETED;
                    CSize--;
                    if(isRehashingToA)
                    {
                        reHash(arraySlot, arraySlot);
                    }
                    return newStr;
                }
                //The program will iterate through the array until it finds the value of hits a NULL space.
                else
                {
                    //Increase the arrayslot size by 1 to move to the next array slot value
                    arraySlot++;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < CCapacity && C[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(C[arraySlot] != DELETED)
                        {
                            //Compares the item in the current array slot with the string value to see if they are the same
                            if(strcmp(C[arraySlot], newStr) == 0)
                            {
                                free(C[arraySlot]);
                                //Deletes the value in the array slot
                                C[arraySlot] = DELETED;
                                //Reduces the size of the array by one
                                CSize--;
                                //If the array is rehashing that it will also move the items in the deleted items group
                                //over to the new array
                                if(isRehashingToA)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                //return the string value
                                return newStr;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                    //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                    if(arraySlot == CCapacity)
                    {
                        //resets arraySlot
                        arraySlot = 0;
                        //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                        while(arraySlot < CCapacity && C[arraySlot] != NULL)
                        {
                            //If the array slot isnt deleted
                            if(C[arraySlot] != DELETED)
                            {
                                //Compares the item in the current array slot with the string value to see if they are the same
                                if(strcmp(C[arraySlot], newStr) == 0)
                                {
                                    free(C[arraySlot]);
                                    //Deletes the value in the array slot
                                    C[arraySlot] = DELETED;
                                    //Reduces the size of the array by one
                                    CSize--;
                                    //If the array is rehashing that it will also move the items in the deleted items group
                                    //over to the new array
                                    if(isRehashingToA)
                                    {
                                        reHash(arraySlot, arraySlot);
                                    }
                                    //return the string value
                                    return newStr;
                                }
                            }
                            //advance through the array
                            arraySlot++;
                        }
                    }
                    //If it isnt found then the program will still move that group of data from the old table to the new table.
                    if(isRehashingToA)
                    {
                        reHash(arraySlot-1, arraySlot-1);
                    }
                }
            }
            //The program will iterate through the array until it finds the value of hits a NULL space.
            else
            {
                //Increase the arrayslot size by 1 to move to the next array slot value
                arraySlot++;
                //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                while(arraySlot < CCapacity && C[arraySlot] != NULL)
                {
                    //If the array slot isnt deleted
                    if(C[arraySlot] != DELETED && arraySlot < CCapacity)
                    {
                        //Compares the item in the current array slot with the string value to see if they are the same
                        if(strcmp(C[arraySlot], newStr) == 0)
                        {
                            free(C[arraySlot]);
                            //Deletes the value in the array slot
                            C[arraySlot] = DELETED;
                            //Reduces the size of the array by one
                            CSize--;
                            //If the array is rehashing that it will also move the items in the deleted items group
                            //over to the new array
                            if(isRehashingToA)
                            {
                                reHash(arraySlot, arraySlot);
                            }
                            //return the string value
                            return newStr;
                        }
                    }
                    //advance through the array
                    arraySlot++;
                }
                //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                if(arraySlot == CCapacity)
                {
                    //resets arraySlot
                    arraySlot = 0;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < CCapacity && C[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(C[arraySlot] != DELETED)
                        {
                            //Compares the item in the current array slot with the string value to see if they are the same
                            if(strcmp(C[arraySlot], newStr) == 0)
                            {
                                //Deletes the value in the array slot
                                free(C[arraySlot]);
                                C[arraySlot] = DELETED;
                                //Reduces the size of the array by one
                                CSize--;
                                //If the array is rehashing that it will also move the items in the deleted items group
                                //over to the new array
                                if(isRehashingToA)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                //return the string value
                                return newStr;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                }
                //If it isnt found then the program will still move that group of data from the old table to the new table.
                if(isRehashingToA)
                {
                    reHash(arraySlot-1, arraySlot-1);
                }
            }
        }
    }
    
    //If it doesnt find the value in any of the tables than it will free the string and return NULL
    free(newStr);
    return NULL;
}

/*This is the find fuction. It searches the hash table to see if it can find the
 item that was passed to it. If it finds the item it will return true else it will
 return false.*/
bool HashTable::find(const char *str)
{
    /*The couple of lines are used to copy the const char string
     into a char string that using a malloc command.*/
    int temp = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        temp++;
    }
    char * newStr = (char *) malloc((temp+1)*sizeof(char));
    strcpy (newStr,str);
    //Determines that hash value of the string
    unsigned int hash = hashCode(newStr);
    /*If the table is already rehashing and the size of the original array has dropped below
     3% of the total array capacity of the array then it will move the rest of the items over
     to the table being rehashed to.*/
    if(A != NULL && B != NULL)
    {
        float capacity = ACapacity;
        float dev = ASize/capacity;
        if(dev < .03 && AInserts/capacity > .03)
        {
            resortRehash('B');
        }
    }
    //If table A exists then it will search this table to find the item from
    if(A != NULL)
    {
        //Determines the hash slot it wants to insert the data item into
        int arraySlot = hash % ACapacity;
        
        //If the array slot has a value in it
        if(A[arraySlot] != NULL)
        {
            //If the value in the array slot is not deleted
            if(A[arraySlot] != DELETED)
            {
                //If the string equals the value in the array slot it return true and free the copied string
                if(strcmp(A[arraySlot], newStr) == 0)
                {
                    free(newStr);
                    if(isRehashingToB)
                    {
                        reHash(arraySlot, arraySlot);
                    }
                    return true;
                }
                //The program will iterate through the array until it finds the value of hits a NULL space.
                else
                {
                    //Increase the arrayslot size by 1 to move to the next array slot value
                    arraySlot++;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < ACapacity && A[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(A[arraySlot] != DELETED)
                        {
                            //If the string equals the value in the array slot it return true and free the copied string
                            if(strcmp(A[arraySlot], newStr) == 0)
                            {
                                free(newStr);
                                if(isRehashingToB)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                return true;
                            }
                        }
                        //advance through the array
                        arraySlot++;
                    }
                    //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                    if(arraySlot == ACapacity)
                    {
                        //resets arraySlot
                        arraySlot = 0;
                        //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                        while(arraySlot < ACapacity && A[arraySlot] != NULL)
                        {
                            //If the array slot isnt deleted
                            if(A[arraySlot] != DELETED)
                            {
                                //If the string equals the value in the array slot it return true and free the copied string
                                if(strcmp(A[arraySlot], newStr) == 0)
                                {
                                    free(newStr);
                                    if(isRehashingToB)
                                    {
                                        reHash(arraySlot, arraySlot);
                                    }
                                    return true;
                                }
                            }
                            arraySlot++;
                        }
                    }
                    //If it isnt found then the program will still move that group of data from the old table to the new table.
                    if(isRehashingToB)
                    {
                        reHash(arraySlot-1, arraySlot-1);
                    }
                }
            }
            //The program will iterate through the array until it finds the value of hits a NULL space.
            else
            {
                //Increase the arrayslot size by 1 to move to the next array slot value
                arraySlot++;
                //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                while(arraySlot < ACapacity && A[arraySlot] != NULL)
                {
                    //If the array slot isnt deleted
                    if(A[arraySlot] != DELETED)
                    {
                        //If the string equals the value in the array slot it return true and free the copied string
                        if(strcmp(A[arraySlot], newStr) == 0)
                        {
                            free(newStr);
                            if(isRehashingToB)
                            {
                                reHash(arraySlot, arraySlot);
                            }
                            return true;
                        }
                    }
                    arraySlot++;
                }
                //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                if(arraySlot == ACapacity)
                {
                    //resets arraySlot
                    arraySlot = 0;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < ACapacity && A[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(A[arraySlot] != DELETED)
                        {
                            //If the string equals the value in the array slot it return true and free the copied string
                            if(strcmp(A[arraySlot], newStr) == 0)
                            {
                                free(newStr);
                                if(isRehashingToB)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                return true;
                            }
                        }
                        arraySlot++;
                    }
                }
                //If it isnt found then the program will still move that group of data from the old table to the new table.
                if(isRehashingToB)
                {
                    reHash(arraySlot-1, arraySlot-1);
                }
            }
        }
    }
    /*If the table is already rehashing and the size of the original array has dropped below
     3% of the total array capacity of the array then it will move the rest of the items over
     to the table being rehashed to.*/
    if(B != NULL && C != NULL)
    {
        float capacity = BCapacity;
        float dev = BSize/capacity;
        if(dev < .03 && BInserts/capacity > .03)
        {
            resortRehash('C');
        }
    }
    //If table B exists then it will search this table to find the item from
    if(B != NULL)
    {
        //Determines the hash slot it wants to insert the data item into
        int arraySlot = hash % BCapacity;
        //If the array slot has a value in it
        if(B[arraySlot] != NULL)
        {
            //If the value in the array slot is not deleted
            if(B[arraySlot] != DELETED)
            {
                //If the string equals the value in the array slot it return true and free the copied string
                if(strcmp(B[arraySlot], newStr) == 0)
                {
                    free(newStr);
                    if(isRehashingToC)
                    {
                        reHash(arraySlot, arraySlot);
                    }
                    return true;
                }
                //The program will iterate through the array until it finds the value of hits a NULL space.
                else
                {
                    //Increase the arrayslot size by 1 to move to the next array slot value
                    arraySlot++;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < BCapacity && B[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(B[arraySlot] != DELETED)
                        {
                            //If the string equals the value in the array slot it return true and free the copied string
                            if(strcmp(B[arraySlot], newStr) == 0)
                            {
                                free(newStr);
                                if(isRehashingToC)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                return true;
                            }
                        }
                        arraySlot++;
                    }
                    //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                    if(arraySlot == BCapacity)
                    {
                        //resets arraySlot
                        arraySlot = 0;
                        //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                        while(arraySlot < BCapacity && B[arraySlot] != NULL)
                        {
                            //If the array slot isnt deleted
                            if(B[arraySlot] != DELETED)
                            {
                                //If the string equals the value in the array slot it return true and free the copied string
                                if(strcmp(B[arraySlot], newStr) == 0)
                                {
                                    free(newStr);
                                    if(isRehashingToC)
                                    {
                                        reHash(arraySlot, arraySlot);
                                    }
                                    return true;
                                }
                            }
                            arraySlot++;
                        }
                    }
                    //If it isnt found then the program will still move that group of data from the old table to the new table.
                    if(isRehashingToC)
                    {
                        reHash(arraySlot-1, arraySlot-1);
                    }
                }
            }
            //The program will iterate through the array until it finds the value of hits a NULL space.
            else
            {
                //Increase the arrayslot size by 1 to move to the next array slot value
                arraySlot++;
                //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                while(arraySlot < BCapacity && B[arraySlot] != NULL)
                {
                    //If the array slot isnt deleted
                    if(B[arraySlot] != DELETED)
                    {
                        //If the string equals the value in the array slot it return true and free the copied string
                        if(strcmp(B[arraySlot], newStr) == 0)
                        {
                            free(newStr);
                            if(isRehashingToC)
                            {
                                reHash(arraySlot, arraySlot);
                            }
                            return true;
                        }
                    }
                    arraySlot++;
                }
                //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                if(arraySlot == BCapacity)
                {
                    //resets arraySlot
                    arraySlot = 0;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < BCapacity && B[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(B[arraySlot] != DELETED)
                        {
                            //If the string equals the value in the array slot it return true and free the copied string
                            if(strcmp(B[arraySlot], newStr) == 0)
                            {
                                free(newStr);
                                if(isRehashingToC)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                return true;
                            }
                        }
                        arraySlot++;
                    }
                }
                //If it isnt found then the program will still move that group of data from the old table to the new table.
                if(isRehashingToC)
                {
                    reHash(arraySlot-1, arraySlot-1);
                }
            }
        }
    }
    /*If the table is already rehashing and the size of the original array has dropped below
     3% of the total array capacity of the array then it will move the rest of the items over
     to the table being rehashed to.*/
    if(C != NULL && A != NULL)
    {
        float capacity = CCapacity;
        float dev = CSize/capacity;
        if(dev < .03 && CInserts/capacity > .03)
        {
            resortRehash('A');
        }
    }
    //If table C exists then it will search this table to find the item from
    if(C != NULL)
    {
        //Determines the hash slot it wants to insert the data item into
        int arraySlot = hash % CCapacity;
        //If the array slot has a value in it
        if(C[arraySlot] != NULL)
        {
            //If the value in the array slot is not deleted
            if(C[arraySlot] != DELETED)
            {
                //If the string equals the value in the array slot it return true and free the copied string
                if(strcmp(C[arraySlot], newStr) == 0)
                {
                    free(newStr);
                    if(isRehashingToA)
                    {
                        reHash(arraySlot, arraySlot);
                    }
                    return true;
                }
                //The program will iterate through the array until it finds the value of hits a NULL space.
                else
                {
                    //Increase the arrayslot size by 1 to move to the next array slot value
                    arraySlot++;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < CCapacity && C[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(C[arraySlot] != DELETED)
                        {
                            //If the string equals the value in the array slot it return true and free the copied string
                            if(strcmp(C[arraySlot], newStr) == 0)
                            {
                                free(newStr);
                                if(isRehashingToA)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                return true;
                            }
                        }
                        arraySlot++;
                    }
                    //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                    if(arraySlot == CCapacity)
                    {
                        //resets arraySlot
                        arraySlot = 0;
                        //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                        while(arraySlot < CCapacity && C[arraySlot] != NULL)
                        {
                            //If the array slot isnt deleted
                            if(C[arraySlot] != DELETED)
                            {
                                //If the string equals the value in the array slot it return true and free the copied string
                                if(strcmp(C[arraySlot], newStr) == 0)
                                {
                                    free(newStr);
                                    if(isRehashingToA)
                                    {
                                        reHash(arraySlot, arraySlot);
                                    }
                                    return true;
                                }
                            }
                            arraySlot++;
                        }
                    }
                    //If it isnt found then the program will still move that group of data from the old table to the new table.
                    if(isRehashingToA)
                    {
                        reHash(arraySlot-1, arraySlot-1);
                    }
                }
            }
            //The program will iterate through the array until it finds the value of hits a NULL space.
            else
            {
                //Increase the arrayslot size by 1 to move to the next array slot value
                arraySlot++;
                //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                while(arraySlot < CCapacity && C[arraySlot] != NULL)
                {
                    //If the array slot isnt deleted
                    if(C[arraySlot] != DELETED)
                    {
                        //If the string equals the value in the array slot it return true and free the copied string
                        if(strcmp(C[arraySlot], newStr) == 0)
                        {
                            free(newStr);
                            if(isRehashingToA)
                            {
                                reHash(arraySlot, arraySlot);
                            }
                            return true;
                        }
                    }
                    arraySlot++;
                }
                //If the end of the array is reached and still hasnt reached NULL it will loop to the front of the array to keep looking
                if(arraySlot == CCapacity)
                {
                    //resets arraySlot
                    arraySlot = 0;
                    //This while loop will go until it either reaches the end of the array or it reaches a NULL value
                    while(arraySlot < CCapacity && C[arraySlot] != NULL)
                    {
                        //If the array slot isnt deleted
                        if(C[arraySlot] != DELETED)
                        {
                            //If the string equals the value in the array slot it return true and free the copied string
                            if(strcmp(C[arraySlot], newStr) == 0)
                            {
                                free(newStr);
                                if(isRehashingToA)
                                {
                                    reHash(arraySlot, arraySlot);
                                }
                                return true;
                            }
                        }
                        arraySlot++;
                    }
                }
                //If it isnt found then the program will still move that group of data from the old table to the new table.

                if(isRehashingToA)
                {
                    reHash(arraySlot-1, arraySlot-1);
                }
            }
        }
    }
    //if nothing is found it will just free the string and return false
    free(newStr);
    return false;
}

/*This program returns the value item that is in the array slot and table that was
 passed in by the user. */
const char * HashTable::at(int index, int table)
{
    //Makes sure that the indez entered is greater that or equal to zero
    if(index >= 0)
    {
        if(table == 0)
        {
            //Checks to see if the table is rehashing if it is then it returns
            //items from the original table instead of the table it is hashing
            //to
            if(Rehashing)
            {
                //If it is rehashing to A
                if(isRehashingToA)
                {
                    //Makes sure that index inputed is less than CCapacity
                    if(index < CCapacity)
                    {
                        const char * temp = C[index];
                        return temp;
                    }
                    else{
                        throw out_of_range("Trying to call an array space greater than the array size");
                    }
                }
                //If it is rehashing to B
                else if(isRehashingToB)
                {
                    //Makes sure that index inputed is less than CCapacity
                    if(index <= ACapacity)
                    {
                        const char * temp = A[index];
                        return temp;
                    }
                    else{
                        throw out_of_range("Trying to call an array space greater than the array size");
                    }
                }
                //If it is rehashing to C
                else if(isRehashingToC)
                {
                    //Makes sure that index inputed is less than CCapacity
                    if(index <= BCapacity)
                    {
                        const char * temp = B[index];
                        return temp;
                    }
                    else{
                        throw out_of_range("Trying to call an array space greater than the array size");
                    }
                }
            }
            else
            {
                //If it is rehashing to A
                if(isRehashingToA)
                {
                    //Makes sure that index inputed is less than CCapacity
                    if(index <= ACapacity)
                    {
                        const char * temp = A[index];
                        return temp;
                    }
                    else{
                        throw out_of_range("Trying to call an array space greater than the array size");
                    }
                }
                //If it is rehashing to B
                else if(isRehashingToB)
                {
                    //Makes sure that index inputed is less than CCapacity
                    if(index <= BCapacity)
                    {
                        const char * temp = B[index];
                        return temp;
                    }
                    else{
                        throw out_of_range("Trying to call an array space greater than the array size");
                    }
                }
                //If it is rehashing to C
                else if(isRehashingToC)
                {
                    //Makes sure that index inputed is less than CCapacity
                    if(index <= CCapacity)
                    {
                        const char * temp = C[index];
                        return temp;
                    }
                    else{
                        throw out_of_range("Trying to call an array space greater than the array size");
                    }
                }
            }
        }
        if(table == 1)
        {
            //If it is rehashing to A
            if(isRehashingToA)
            {
                //Makes sure that index inputed is less than CCapacity
                if(index <= ACapacity)
                {
                    const char * temp = A[index];
                    return temp;
                }
                else{
                    throw out_of_range("Trying to call an array space greater than the array size");
                }
            }
            //If it is rehashing to B
            else if(isRehashingToB)
            {
                //Makes sure that index inputed is less than CCapacity
                if(index <= BCapacity)
                {
                    const char * temp = B[index];
                    return temp;
                }
                else{
                    throw out_of_range("Trying to call an array space greater than the array size");
                }
            }
            //If it is rehashing to C
            else if(isRehashingToC)
            {
                //Makes sure that index inputed is less than CCapacity
                if(index <= CCapacity)
                {
                    const char * temp = C[index];
                    return temp;
                }
                else{
                    throw out_of_range("Trying to call an array space greater than the array size");
                }
            }
        }
        //Else it returns NULL
        return NULL;
    }
    else{
        throw out_of_range("Trying to call an array space less than 0");
    }
}

//Returns whether or not the table is rehashing
bool HashTable::isRehashing()
{
    return Rehashing;
}

//Returns the size of the table that was passed in
int HashTable::tableSize(int table)
{
    //If table zero was passed in
    if(table == 0)
    {
        //If the table is rehashing
        if(Rehashing)
        {
            //If rehashing to A returns the capacity of C.
            if(isRehashingToA)
            {
                return CCapacity;
            }
            //If rehashing to B returns the capacity of A.
            else if(isRehashingToB)
            {
                return ACapacity;
            }
            //If rehashing to C returns the capacity of B.
            else if(isRehashingToC)
            {
                return BCapacity;
            }
        }
        else{
            //If it is hashing to A returns A's capacity
            if(isRehashingToA)
            {
                return ACapacity;
            }
            //If it is hashing to B returns B's capacity
            else if(isRehashingToB)
            {
                return BCapacity;
            }
            //If it is hashing to C returns C's capacity
            else if(isRehashingToC)
            {
                return CCapacity;
            }
        }
    }
    if(table == 1)
    {
        //If it is hashing to A returns A's capacity
        if(isRehashingToA)
        {
            return ACapacity;
        }
        //If it is hashing to B returns B's capacity
        else if(isRehashingToB)
        {
            return BCapacity;
        }
        //If it is hashing to C returns C's capacity
        else if(isRehashingToC)
        {
            return CCapacity;
        }
    }
    //If none of the tables exist or a value other that 0 or 1 is entered
    return NULL;
}

//Returns the size of the table passed in
int HashTable::size(int table)
{
    if(table == 0)
    {
        if(Rehashing)
        {
            //If rehashing to A returns the size of C.
            if(isRehashingToA)
            {
                return CSize;
            }
            //If rehashing to B returns the size of A.
            else if(isRehashingToB)
            {
                return ASize;
            }
            //If rehashing to C returns the size of B.
            else if(isRehashingToC)
            {
                return BSize;
            }
        }
        else{
            //If rehashing to A returns the size of A.
            if(isRehashingToA)
            {
                return ASize;
            }
            //If rehashing to B returns the size of B.
            else if(isRehashingToB)
            {
                return BSize;
            }
            //If rehashing to C returns the size of C.
            else if(isRehashingToC)
            {
                return CSize;
            }
        }
    }
    if(table == 1)
    {
        //If rehashing to A returns the size of A.
        if(isRehashingToA)
        {
            return ASize;
        }
        //If rehashing to B returns the size of B.
        else if(isRehashingToB)
        {
            return BSize;
        }
        //If rehashing to C returns the size of C.
        else if(isRehashingToC)
        {
            return CSize;
        }
    }
    //If none of the tables exist or a value other that 0 or 1 is entered
    return NULL;
}

/*This is my prime number search function that searchs the primes table for a prime value that is or is the closest
 value to the one that was passed into the search. It does a binary search of the array until it finds the number 
 entered or the number that is the next largest prime number to it.*/
void HashTable::primeNumSearch(int num, int lower_bound, int upper_bound)
{
    //This checks to see if the value at the half way is equal to the number entered
    if(primes[upper_bound - ((upper_bound - lower_bound)/2)] == num)
    {
        answer = num;
    }
    //This checks to see if the value at the half way is greater than to the number entered
    else if(primes[upper_bound - ((upper_bound - lower_bound)/2)] > num)
    {
        //makes sure the binary search will be valid
        if((upper_bound - lower_bound)/2 < 1)
        {
            //If the value is less than num
            if(primes[upper_bound] < num)
            {
                answer = primes[upper_bound+1];
            }
            //If num equal the value in the array
            else if(num == primes[lower_bound])
            {
                answer = primes[lower_bound];
            }
            else
            {
                answer = primes[upper_bound];
            }
        }
        //continues to iterate
        else
        {
            primeNumSearch(num, lower_bound, upper_bound - ((upper_bound - lower_bound)/2)-1);
        }
    }
    //This checks to see if the value at the half way is less than to the number entered
    else if(primes[upper_bound - ((upper_bound - lower_bound)/2)] < num)
    {
        //makes sure the binary search will be valid
        if((upper_bound - lower_bound)/2 < 1)
        {
            //If the value is less than num
            if(primes[upper_bound] < num)
            {
                answer = primes[upper_bound+1];
            }
            //If num equal the value in the array
            else if(num == primes[lower_bound])
            {
                answer = primes[lower_bound];
            }
            else{
                answer = primes[upper_bound];
            }
        }
        //continues to iterate
        else
        {
            primeNumSearch(num, lower_bound + ((upper_bound - lower_bound)/2), upper_bound);
        }
    }
}

/*This function is called before a rehash is initiated it sets all of the isRehashing values, 
 tells the program that the table is rehashing, creates the new table with the correct size 
 and capacity*/
void HashTable::startRehashingToA()
{
    Rehashing = true;
    isRehashingToA = true;
    isRehashingToB = false;
    isRehashingToC = false;
    answer = -1;
    primeNumSearch(4*CSize, 0, numPrimes-1);
    ACapacity = answer;
    A = new char*[ACapacity]();
    ASize = 0;
}

/*This function is called before a rehash is initiated it sets all of the isRehashing values,
 tells the program that the table is rehashing, creates the new table with the correct size
 and capacity*/
void HashTable::startRehashingToB()
{
    Rehashing = true;
    isRehashingToA = false;
    isRehashingToB = true;
    isRehashingToC = false;
    answer = -1;
    primeNumSearch(4*ASize, 0, numPrimes-1);
    BCapacity = answer;
    B = new char*[BCapacity]();
    BSize = 0;
}

/*This function is called before a rehash is initiated it sets all of the isRehashing values,
 tells the program that the table is rehashing, creates the new table with the correct size
 and capacity*/
void HashTable::startRehashingToC()
{
    Rehashing = true;
    isRehashingToA = false;
    isRehashingToB = false;
    isRehashingToC = true;
    answer = -1;
    primeNumSearch(4*BSize, 0, numPrimes-1);
    CCapacity = answer;
    C = new char*[CCapacity]();
    CSize = 0;
}

//This is professor Chang's hash code program.
unsigned int HashTable::hashCode(const char *str) {
    
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook
    
    int i = 0 ;
    while (str[i] != '\0') {
        val = val * thirtyThree + str[i] ;
        i++ ;
    }
    return val ;
}

//This is an overlead version professor Chang's hash code program to take standard char values.
unsigned int HashTable::hashCode(char *str) {
    
    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook
    int i = 0 ;
    while (str[i] != '\0') {
        val = val * thirtyThree + str[i] ;
        i++ ;
    }
    return val ;
}

/*This is my rehash function, it takes the upperboud and lowerbound of the probe and will continue to probe
 the array to find the ends of the bunch. It then proceeds to rehash those items over to the new table.*/
void HashTable::reHash(int lowerBound, int upperBound)
{
    //If it is rehashing to A
    if(isRehashingToA)
    {
        //Finds the upperbound of the cluster
        while(upperBound < CCapacity-1 && C[upperBound+1] != NULL)
        {
            upperBound++;
        }
        if(upperBound == CCapacity -2 && C[CCapacity-1] != NULL)
        {
            upperBound++;
        }
        //Loops to the bottom of the array if needed
        if((upperBound == CCapacity || upperBound == CCapacity-1) && C[0] != NULL)
        {
            upperBound = 0;
            while(C[upperBound+1] != NULL && C[0] != NULL)
            {
                upperBound++;
            }
        }
        //Finds the lower bound of the cluster
        while(C[lowerBound-1] != NULL && lowerBound >= 1)
        {
            lowerBound--;
        }
        if(lowerBound == 1 && C[0] != NULL)
        {
            lowerBound--;
        }
        //Loops to the top of the array if needed
        if((lowerBound == -1 || lowerBound == 0) && C[CCapacity-1] != NULL)
        {
            lowerBound = CCapacity -1;
            while(C[lowerBound-1] != NULL)
            {
                lowerBound--;
            }
        }
        //If the upperbound is less than the lower bound aka. If the program
        //loops around.
        if(upperBound < lowerBound)
        {
            //Until the Lowerbound reaches the capacity
            for(int i = lowerBound; i < CCapacity; i++)
            {
                if(C[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(C[i]);
                    int arraySlot = hash % ACapacity;
                    
                    //If the array slot it is inserting into is NULL or DELETED
                    if(A[arraySlot] == NULL || A[arraySlot] == DELETED)
                    {
                        A[arraySlot] = C[i];
                    }
                    else
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; A[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == ACapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == ACapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; A[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        A[newSlot] = C[i];
                    }
                    //Update the array sizes
                    CSize--;
                    ASize++;
                }
                //Set the value of C[i] to NULL
                C[i] = NULL;
            }
            //Until i reaches the upperBound of the cluster
            for(int i = 0; i <= upperBound; i++)
            {
                if(C[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(C[i]);
                    int arraySlot = hash % ACapacity;
                    
                    //If the array slot it is inserting into is NULL or DELETED
                    if(A[arraySlot] == NULL || A[arraySlot] == DELETED)
                    {
                        A[arraySlot] = C[i];
                    }
                    else
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; A[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == ACapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == ACapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; A[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        A[newSlot] = C[i];
                    }
                    //Update the array sizes
                    CSize--;
                    ASize++;
                }
                //Set the value of C[i] to NULL
                C[i] = NULL;
            }
        }
        //If the cluster doesnt wrap arround
        else
        {
            //Iterate through the cluster from bottom to top
            for(int i = lowerBound; i <= upperBound; i++)
            {
                if(C[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(C[i]);
                    int arraySlot = hash % ACapacity;
                    
                    //If the array slot it is inserting into is NULL or DELETED
                    if(A[arraySlot] == NULL || A[arraySlot] == DELETED)
                    {
                        A[arraySlot] = C[i];
                    }
                    else
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; A[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == ACapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == ACapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; A[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        A[newSlot] = C[i];
                    }
                    //Update the array sizes
                    CSize--;
                    ASize++;
                }
                //Set the value of C[i] to NULL
                C[i] = NULL;
            }
        }
    }
    //If it is rehashing to B
    else if(isRehashingToB)
    {
        //Finds the upperbound of the cluster
        while(upperBound < ACapacity-1 && A[upperBound+1] != NULL)
        {
            upperBound++;
        }
        if(upperBound == ACapacity -2 && A[ACapacity-1] != NULL)
        {
            upperBound++;
        }
        //Loops to the bottom of the array if needed
        if((upperBound == ACapacity || upperBound == ACapacity-1) && A[0] != NULL)
        {
            upperBound = 0;
            //Finds the upperbound of the cluster
            while(A[upperBound+1] != NULL)
            {
                upperBound++;
            }
        }
        //Finds the lower bound of the cluster
        while(lowerBound >= 1 && A[lowerBound-1] != NULL)
        {
            lowerBound--;
        }
        if(lowerBound == 1 && A[0] != NULL)
        {
            lowerBound--;
        }
        //Loops to the top of the array if needed
        if((lowerBound == -1 || lowerBound == 0) && A[ACapacity-1] != NULL)
        {
            lowerBound = ACapacity -1;
            //Finds the lower bound of the cluster
            while(A[lowerBound-1] != NULL)
            {
                lowerBound--;
            }
        }
        //If the upperbound is less than the lower bound aka. If the program
        //loops around.
        if(upperBound < lowerBound)
        {
            //Until the Lowerbound reaches the capacity
            for(int i = lowerBound; i < ACapacity; i++)
            {
                if(A[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(A[i]);
                    int arraySlot = hash % BCapacity;
                    
                    //If the value in the array slot isn't null or deleted
                    if(B[arraySlot] != NULL && B[arraySlot] != DELETED)
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; B[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == BCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == BCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; B[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        B[newSlot] = A[i];
                    }
                    //If the array slot it is inserting into is NULL or DELETED
                    else
                    {
                        B[arraySlot] = A[i];
                    }
                    //Update the array sizes
                    ASize--;
                    BSize++;
                }
                //Set the value of C[i] to NULL
                A[i] = NULL;
            }
            //Until i reaches the upperBound of the cluster
            for(int i = 0; i <= upperBound; i++)
            {
                if(A[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(A[i]);
                    int arraySlot = hash % BCapacity;
                    
                    //If the value in the array slot isn't null or deleted
                    if(B[arraySlot] != NULL && B[arraySlot] != DELETED)
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; B[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == BCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == BCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; B[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        B[newSlot] = A[i];
                    }
                    //If the array slot it is inserting into is NULL or DELETED
                    else
                    {
                        B[arraySlot] = A[i];
                    }
                    //Update the array sizes
                    ASize--;
                    BSize++;
                }
                //Set the value of C[i] to NULL
                A[i] = NULL;
            }
        }
        //If the cluster doesnt wrap arround
        else
        {
            //Iterate through the cluster from bottom to top
            for(int i = lowerBound; i <= upperBound; i++)
            {
                if(A[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(A[i]);
                    int arraySlot = hash % BCapacity;
                    
                    //If the value in the array slot isn't null or deleted
                    if(B[arraySlot] != NULL && B[arraySlot] != DELETED)
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; B[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == BCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == BCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; B[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        B[newSlot] = A[i];
                    }
                    //If the array slot it is inserting into is NULL or DELETED
                    else
                    {
                        B[arraySlot] = A[i];
                    }
                    //Update the array sizes
                    ASize--;
                    BSize++;
                }
                //Set the value of C[i] to NULL
                A[i] = NULL;
            }
        }
    }
    //If it is rehashing to B
    else if(isRehashingToC)
    {
        //Finds the upperbound of the cluster
        while(upperBound < BCapacity-1 && B[upperBound+1] != NULL)
        {
            upperBound++;
        }
        if(upperBound == BCapacity -2 && B[BCapacity-1] != NULL)
        {
            upperBound++;
        }
        //Loops to the bottom of the array if needed
        if((upperBound == BCapacity || upperBound == BCapacity-1) && B[0] != NULL)
        {
            upperBound = 0;
            //Finds the upperbound of the cluster
            while(B[upperBound+1] != NULL && B[0] != NULL)
            {
                upperBound++;
            }
        }
        //Finds the lower bound of the cluster
        while(B[lowerBound-1] != NULL && lowerBound >= 1)
        {
            lowerBound--;
        }
        if(lowerBound == 1 && B[0] != NULL)
        {
            lowerBound--;
        }
        //Loops to the top of the array if needed
        if((lowerBound == -1 || lowerBound == 0) && B[BCapacity-1] != NULL)
        {
            lowerBound = ACapacity -1;
            //Finds the lower bound of the cluster
            while(A[lowerBound-1] != NULL)
            {
                lowerBound--;
            }
        }
        //If the upperbound is less than the lower bound aka. If the program
        //loops around.
        if(upperBound < lowerBound)
        {
            //Until the Lowerbound reaches the capacity
            for(int i = lowerBound; i < BCapacity; i++)
            {
                if(B[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(B[i]);
                    int arraySlot = hash % CCapacity;
                    
                    //If the value in the array slot isn't null or deleted
                    if(C[arraySlot] != NULL && C[arraySlot] != DELETED)
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; C[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == CCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == CCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; C[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        C[newSlot] = B[i];
                    }
                    //If the array slot it is inserting into is NULL or DELETED
                    else
                    {
                        C[arraySlot] = B[i];
                    }
                    //Update the array sizes
                    BSize--;
                    CSize++;
                }
                //Set the value of C[i] to NULL
                B[i] = NULL;
            }
            //Until i reaches the upperBound of the cluster
            for(int i = 0; i <= upperBound; i++)
            {
                if(B[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(B[i]);
                    int arraySlot = hash % CCapacity;
                    
                    //If the value in the array slot isn't null or deleted
                    if(C[arraySlot] != NULL && C[arraySlot] != DELETED)
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; C[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == CCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == CCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; C[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        C[newSlot] = B[i];
                    }
                    //If the array slot it is inserting into is NULL or DELETED
                    else
                    {
                        C[arraySlot] = B[i];
                    }
                    //Update the array sizes
                    BSize--;
                    CSize++;
                }
                //Set the value of C[i] to NULL
                B[i] = NULL;
            }
        }
        //If the cluster doesnt wrap arround
        else
        {
            //Iterate through the cluster from bottom to top
            for(int i = lowerBound; i <= upperBound; i++)
            {
                if(B[i] != DELETED)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(B[i]);
                    int arraySlot = hash % CCapacity;
                    
                    //If the value in the array slot isn't null or deleted
                    if(C[arraySlot] != NULL && C[arraySlot] != DELETED)
                    {
                        int newSlot = 0;
                        //Iterate through the array until it finds a NULL slot
                        for(int i = arraySlot; C[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == CCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //If it reaches the capacity it will loop around to the bottom of the array
                        if(newSlot == CCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; C[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //insert the item into the array
                        C[newSlot] = B[i];
                    }
                    //If the array slot it is inserting into is NULL or DELETED
                    else
                    {
                        C[arraySlot] = B[i];
                    }
                    //Update the array sizes
                    BSize--;
                    CSize++;
                }
                //Set the value of C[i] to NULL
                B[i] = NULL;
            }
        }
    }
}

void HashTable::resortRehash(char table)
{
    //If the table passed in is C
    if(table == 'C')
    {
        //Sets is rehashing to false
        Rehashing = false;
        isRehashingToA = false;
        isRehashingToB = false;
        isRehashingToC = true;
        answer = -1;
        //Is doing a double table resort and not just moving the rest of the
        //items from one table to another
        if(C == NULL)
        {
            //Creates a new Table to rehash all of the items too
            primeNumSearch(4*(BSize+ASize), 0, numPrimes-1);
            CCapacity = answer;
            C = new char*[CCapacity]();
            CSize = 0;
        }
        //If A is not null
        if(A != NULL)
        {
            //Iterate throught the entire array
            for(int i = 0; i < ACapacity; i++)
            {
                //if the value is not null or deleted
                if(A[i] != DELETED && A[i] != NULL)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(A[i]);
                    int arraySlot = hash % CCapacity;
                    //If the arraySlot is not null
                    if(C[arraySlot] != NULL)
                    {
                        int newSlot = 0;
                        //Probe until a null non null slot is found
                        for(int i = arraySlot; C[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == CCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //wraps around to the bottom of the array if during probing it reaches the end of the array
                        if(newSlot == CCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; C[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //inserts the item into the array
                        C[newSlot] = A[i];
                    }
                    //if the array slot it originally hashes to is null
                    else
                    {
                        C[arraySlot] = A[i];
                    }
                }
            }
            //Deletes the old empty array
            delete [] A;
            //Sets the number of inserts to null
            AInserts = 0;
            //sets it to null
            A = NULL;
        }
        //If B is not null
        if(B != NULL)
        {
            //Iterate throught the entire array
            for(int i = 0; i < BCapacity; i++)
            {
                //if the value is not null or deleted
                if(B[i] != DELETED && B[i] != NULL)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(B[i]);
                    int arraySlot = hash % CCapacity;
                    //If the arraySlot is not null
                    if(C[arraySlot] != NULL)
                    {
                        int newSlot = 0;
                        //Probe until a null non null slot is found
                        for(int i = arraySlot; C[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == CCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //wraps around to the bottom of the array if during probing it reaches the end of the array
                        if(newSlot == CCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; C[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //inserts the item into the array
                        C[newSlot] = B[i];
                    }
                    //if the array slot it originally hashes to is null
                    else
                    {
                        C[arraySlot] = B[i];
                    }
                }
            }
            //Deletes the old empty array
            delete [] B;
            //Sets the number of inserts to null
            BInserts = 0;
            //sets it to null
            B = NULL;
        }
        //Sets the size of C
        CSize = ASize + BSize + CSize;
        //Rests all of the counters
        ASize = 0;
        ACapacity = 0;
        BSize = 0;
        BCapacity = 0;
    }
    //If the table passed in is B
    else if(table == 'B')
    {
        //Sets is rehashing to false
        Rehashing = false;
        isRehashingToA = false;
        isRehashingToB = true;
        isRehashingToC = false;
        answer = -1;
        //Is doing a double table resort and not just moving the rest of the
        //items from one table to another
        if(B == NULL)
        {
            //Creates a new Table to rehash all of the items too
            primeNumSearch(4*(ASize+CSize), 0, numPrimes-1);
            BCapacity = answer;
            B = new char*[BCapacity]();
            BSize = 0;
        }
        //If A is not null
        if(A != NULL)
        {
            //Iterate throught the entire array
            for(int i = 0; i < ACapacity; i++)
            {
                //if the value is not null or deleted
                if(A[i] != DELETED && A[i] != NULL)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(A[i]);
                    int arraySlot = hash % BCapacity;
                    //If the arraySlot is not null
                    if(B[arraySlot] != NULL)
                    {
                        int newSlot = 0;
                        //Probe until a null non null slot is found
                        for(int i = arraySlot; B[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == BCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //wraps around to the bottom of the array if during probing it reaches the end of the array
                        if(newSlot == BCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; B[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //inserts the item into the array
                        B[newSlot] = A[i];
                    }
                    //if the array slot it originally hashes to is null
                    else
                    {
                        B[arraySlot] = A[i];
                    }
                }
            }
            //Deletes the old empty array
            delete [] A;
            //Sets the number of inserts to null
            AInserts= 0;
            //sets it to null
            A = NULL;
        }
        //If C is not null
        if(C != NULL)
        {
            //Iterate throught the entire array
            for(int i = 0; i < CCapacity; i++)
            {
                //if the value is not null or deleted
                if(C[i] != DELETED && C[i] != NULL)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(C[i]);
                    int arraySlot = hash % BCapacity;
                    //If the arraySlot is not null
                    if(B[arraySlot] != NULL)
                    {
                        int newSlot = 0;
                        //Probe until a null non null slot is found
                        for(int i = arraySlot; B[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == BCapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //wraps around to the bottom of the array if during probing it reaches the end of the array
                        if(newSlot == BCapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; B[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //inserts the item into the array
                        B[newSlot] = C[i];
                    }
                    //if the array slot it originally hashes to is null
                    else
                    {
                        B[arraySlot] = C[i];
                    }
                }
            }
            //Deletes the old empty array
            delete [] C;
            //Sets the number of inserts to null
            CInserts= 0;
            //sets it to null
            C = NULL;
        }
        //Sets the size of C
        BSize = ASize + BSize + CSize;
        //Rests all of the counters
        ASize = 0;
        ACapacity = 0;
        CSize = 0;
        CCapacity = 0;
    }
    //If the table passed in is A
    else if(table == 'A')
    {
        //Sets is rehashing to false
        Rehashing = false;
        isRehashingToA = true;
        isRehashingToB = false;
        isRehashingToC = false;
        answer = -1;
        //Is doing a double table resort and not just moving the rest of the
        //items from one table to another
        if(A == NULL)
        {
            //Creates a new Table to rehash all of the items too
            primeNumSearch(4*(CSize+BSize), 0, numPrimes-1);
            ACapacity = answer;
            A = new char*[ACapacity]();
            ASize = 0;
        }
        //If B is not null
        if(B != NULL)
        {
            //Iterate throught the entire array
            for(int i = 0; i < BCapacity; i++)
            {
                //if the value is not null or deleted
                if(B[i] != DELETED && B[i] != NULL)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(B[i]);
                    int arraySlot = hash % ACapacity;
                    //If the arraySlot is not null
                    if(A[arraySlot] != NULL)
                    {
                        int newSlot = 0;
                        //Probe until a null non null slot is found
                        for(int i = arraySlot; A[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == ACapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //wraps around to the bottom of the array if during probing it reaches the end of the array
                        if(newSlot == ACapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; A[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //inserts the item into the array
                        A[newSlot] = B[i];
                    }
                    //if the array slot it originally hashes to is null
                    else
                    {
                        A[arraySlot] = B[i];
                    }
                }
            }
            //Deletes the old empty array
            delete [] B;
            //Sets the number of inserts to null
            BInserts= 0;
            //sets it to null
            B = NULL;
        }
        //If C is not null
        if(C != NULL)
        {
            //Iterate throught the entire array
            for(int i = 0; i < CCapacity; i++)
            {
                //if the value is not null or deleted
                if(C[i] != DELETED && C[i] != NULL)
                {
                    //Calculates the hashcode of the value
                    unsigned int hash = hashCode(C[i]);
                    int arraySlot = hash % ACapacity;
                    //If the arraySlot is not null
                    if(A[arraySlot] != NULL)
                    {
                        int newSlot = 0;
                        //Probe until a null non null slot is found
                        for(int i = arraySlot; A[i] != NULL; i++)
                        {
                            newSlot = i+1;
                            if(i == ACapacity-1)
                            {
                                i = 0;
                            }
                        }
                        //wraps around to the bottom of the array if during probing it reaches the end of the array
                        if(newSlot == ACapacity)
                        {
                            newSlot = 0;
                            
                            for(int i = 0; A[i] != NULL; i++)
                            {
                                newSlot = i+1;
                            }
                        }
                        //inserts the item into the array
                        A[newSlot] = C[i];
                    }
                    //if the array slot it originally hashes to is null
                    else
                    {
                        A[arraySlot] = C[i];
                    }
                }
            }
            //Deletes the old empty array
            delete [] C;
            //Sets the number of inserts to null
            CInserts= 0;
            //sets it to null
            C = NULL;
        }
        //Sets the size of C
        ASize = ASize + BSize + CSize;
        //Rests all of the counters
        CSize = 0;
        CCapacity = 0;
        BSize = 0;
        BCapacity = 0;
    }
    Rehashing = false;
}

/*Is is the dump fuction it's job is to dump the tables that are currently being used and in the order that they are being used. H1 is the original table H2 is the table that is being rehashed to is their is a table that is being rehashed to.*/
void HashTable::dump()
{
    //Checks if 2 Tables need to be dumped
    if(Rehashing)
    {
        /*If it is rehashing to B that means that tables A and B are being used so it dumps those tables*/
        if(isRehashingToB)
        {
            cout<<"--------Printing Out Table H1--------"<<endl;
            cout<<"Size = "<<ASize<<endl;
            cout<<"Capacity = "<<ACapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < ACapacity; i++)
            {
                int arraySlot = NULL;
                if(A[i] != NULL && A[i] != DELETED)
                {
                    unsigned int hash = hashCode(A[i]);
                    arraySlot = hash % ACapacity;
                    cout<<"H1["<<i<<"] = "<<A[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(A[i] == DELETED)
                {
                    cout<<"H1["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H1["<<i<<"]"<<endl;
                }
            }
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            cout<<endl;
            cout<<"--------Printing Out Table H2--------"<<endl;
            cout<<"Size = "<<BSize<<endl;
            cout<<"Capacity = "<<BCapacity<<endl;
            for(int i = 0; i < BCapacity; i++)
            {
                int arraySlot = NULL;
                if(B[i] != NULL && B[i] != DELETED)
                {
                    unsigned int hash = hashCode(B[i]);
                    arraySlot = hash % BCapacity;
                    cout<<"H2["<<i<<"] = "<<B[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(B[i] == DELETED)
                {
                    cout<<"H2["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H2["<<i<<"]"<<endl;
                }
            }
        }
        /*If it is rehashing to C that means that tables B and C are being used so it dumps those tables*/
        if(isRehashingToC)
        {
            cout<<"--------Printing Out Table H1--------"<<endl;
            cout<<"Size = "<<BSize<<endl;
            cout<<"Capacity = "<<BCapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < BCapacity; i++)
            {
                int arraySlot = NULL;
                if(B[i] != NULL && B[i] != DELETED)
                {
                    unsigned int hash = hashCode(B[i]);
                    arraySlot = hash % BCapacity;
                    cout<<"H1["<<i<<"] = "<<B[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(B[i] == DELETED)
                {
                    cout<<"H1["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H1["<<i<<"]"<<endl;
                }
            }
            cout<<endl;
            cout<<"--------Printing Out Table H2--------"<<endl;
            cout<<"Size = "<<CSize<<endl;
            cout<<"Capacity = "<<CCapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < CCapacity; i++)
            {
                int arraySlot = NULL;
                if(C[i] != NULL && C[i] != DELETED)
                {
                    unsigned int hash = hashCode(C[i]);
                    arraySlot = hash % CCapacity;
                    cout<<"H2["<<i<<"] = "<<C[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(C[i] == DELETED)
                {
                    cout<<"H2["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H2["<<i<<"]"<<endl;
                }
            }
        }
        /*If it is rehashing to A that means that tables C and A are being used so it dumps those tables*/
        if(isRehashingToA)
        {
            cout<<"--------Printing Out Table H1--------"<<endl;
            cout<<"Size = "<<CSize<<endl;
            cout<<"Capacity = "<<CCapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < CCapacity; i++)
            {
                int arraySlot = NULL;
                if(C[i] != NULL && C[i] != DELETED)
                {
                    unsigned int hash = hashCode(C[i]);
                    arraySlot = hash % CCapacity;
                    cout<<"H1["<<i<<"] = "<<C[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(C[i] == DELETED)
                {
                    cout<<"H1["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H1["<<i<<"]"<<endl;
                }
            }
            cout<<"--------Printing Out Table H2--------"<<endl;
            cout<<"Size = "<<ASize<<endl;
            cout<<"Capacity = "<<ACapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < ACapacity; i++)
            {
                int arraySlot = NULL;
                if(A[i] != NULL && A[i] != DELETED)
                {
                    unsigned int hash = hashCode(A[i]);
                    arraySlot = hash % ACapacity;
                    cout<<"H2["<<i<<"] = "<<A[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(A[i] == DELETED)
                {
                    cout<<"H2["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H2["<<i<<"]"<<endl;
                }
            }
        }
    }
    /*If only one table is being used then it will dump just the table being used*/
    else
    {
        //A is being used
        if(A != NULL)
        {
            cout<<"--------Printing Out Table H1--------"<<endl;
            cout<<"Size = "<<ASize<<endl;
            cout<<"Capacity = "<<ACapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < ACapacity; i++)
            {
                int arraySlot = NULL;
                if(A[i] != NULL && A[i] != DELETED)
                {
                    unsigned int hash = hashCode(A[i]);
                    arraySlot = hash % ACapacity;
                    cout<<"H1["<<i<<"] = "<<A[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(A[i] == DELETED)
                {
                    cout<<"H1["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H1["<<i<<"]"<<endl;
                }
            }
        }
        //B is being used
        if(B != NULL)
        {
            cout<<"--------Printing Out Table H1--------"<<endl;
            cout<<"Size = "<<BSize<<endl;
            cout<<"Capacity = "<<BCapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < BCapacity; i++)
            {
                int arraySlot = NULL;
                if(B[i] != NULL && B[i] != DELETED)
                {
                    unsigned int hash = hashCode(B[i]);
                    arraySlot = hash % BCapacity;
                    cout<<"H1["<<i<<"] = "<<B[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(B[i] == DELETED)
                {
                    cout<<"H1["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H1["<<i<<"]"<<endl;
                }
            }
        }
        //C is being used
        if(C != NULL)
        {
            cout<<"--------Printing Out Table H1--------"<<endl;
            cout<<"Size = "<<CSize<<endl;
            cout<<"Capacity = "<<CCapacity<<endl;
            //This iterates through the table and dumps all of the associated items into those tables along with the slot they are supposed to be hashing to.
            for(int i = 0; i < CCapacity; i++)
            {
                int arraySlot = NULL;
                if(C[i] != NULL && C[i] != DELETED)
                {
                    unsigned int hash = hashCode(C[i]);
                    arraySlot = hash % CCapacity;
                    cout<<"H1["<<i<<"] = "<<C[i]<<" ("<<arraySlot<<")"<<endl;
                }
                else if(C[i] == DELETED)
                {
                    cout<<"H1["<<i<<"] = DELETED"<<endl;
                }
                else
                {
                    cout<<"H1["<<i<<"]"<<endl;
                }
            }
        }
    }
}

/*This is the destructor for the function. Finds any arrays that still exits
 in the HashTable object and frees all of the char* in the array an then deletes
 the array.*/
HashTable::~HashTable()
{
    if(A != NULL)
    {
        for(int i = 0; i < ACapacity; i++)
        {
            if(A[i] != NULL && A[i] != DELETED)
            {
                    free(A[i]);
            }
        }
        delete [] A;
    }
    if(B != NULL)
    {
        for(int i = 0; i < BCapacity; i++)
        {
            if(B[i] != NULL && B[i] != DELETED)
            {
                
                    free(B[i]);
            }
        }
        delete [] B;
    }
    if(C != NULL)
    {
        for(int i = 0; i < CCapacity; i++)
        {
            if(C[i] != NULL && C[i] != DELETED)
            {
                    free(C[i]);
            }
        }
        delete [] C;
    }
}

/*This is the copy constructior for the HashTable it does a hard copy of an object to another object. */
HashTable::HashTable(HashTable& other)
{
    //If other object has table A
    if(other.A != NULL)
    {
        isRehashingToA = true;
        isRehashingToB = false;
        isRehashingToC = false;
        //Checks to see if it is rehashing to A
        if(other.C != NULL)
        {
            Rehashing = true;
        }
        //checks to see if A is the table rehashing
        if(other.B != NULL)
        {
            isRehashingToA = false;
            isRehashingToB = true;
            isRehashingToC = false;
        }
        //Sets the Attributes of table A
        ACapacity = other.ACapacity;
        ASize = 0;
        AInserts = 0;
        //Creates table A
        A = new char*[ACapacity]();
        //Inserts the objects into table A
        for(int i = 0; i < ACapacity; i++)
        {
            if(other.A[i] != NULL)
            {
                if(other.A[i] == DELETED)
                {
                    A[i] = DELETED;
                }
                else
                {
                    int temp = 0;
                    char * tempChar = other.A[i];
                    for(int k = 0; tempChar[k] != '\0'; k++)
                    {
                        temp++;
                    }
                    temp++;
                    char * newStr = (char*) malloc(temp*sizeof(char)+1);
                    strcpy ((char*)newStr,tempChar);
                    newStr[temp] = '\0';
                    A[i] = newStr;
                    ASize++;
                }
                AInserts++;
            }
        }
    }
    else{
        A = NULL;
    }
    //If other object has table B
    if(other.B != NULL)
    {
        isRehashingToA = false;
        isRehashingToB = true;
        isRehashingToC = false;
        //Checks to see if it is rehashing to B
        if(other.A != NULL)
        {
            Rehashing = true;
        }
        //checks to see if B is the table rehashing
        if(other.C != NULL)
        {
            isRehashingToA = false;
            isRehashingToB = false;
            isRehashingToC = true;
        }
        //Sets the Attributes of table B
        BCapacity = other.BCapacity;
        BSize = 0;
        BInserts = 0;
        //Creates table B
        B = new char*[BCapacity]();
         //Inserts the objects into table B
        for(int i = 0; i < BCapacity; i++)
        {
            if(other.B[i] != NULL)
            {
                if(other.B[i] == DELETED)
                {
                    B[i] = DELETED;
                }
                else
                {
                    int temp = 0;
                    char * tempChar = other.B[i];
                    for(int k = 0; tempChar[k] != '\0'; k++)
                    {
                        temp++;
                    }
                    temp++;
                    char * newStr = (char*) malloc(temp*sizeof(char)+1);
                    strcpy ((char*)newStr,tempChar);
                    newStr[temp] = '\0';
                    B[i] = newStr;
                    BSize++;
                }
                BInserts++;
            }
        }
    }
    else{
        B = NULL;
    }
    //If other object has table C
    if(other.C != NULL)
    {
        isRehashingToA = false;
        isRehashingToB = false;
        isRehashingToC = true;
        //Checks to see if it is rehashing to C
        if(other.B != NULL)
        {
            Rehashing = true;
        }
        //checks to see if C is the table rehashing
        if(other.A != NULL)
        {
            isRehashingToA = true;
            isRehashingToB = false;
            isRehashingToC = false;
        }
        //Sets the Attributes of table C
        CCapacity = other.CCapacity;
        CSize = 0;
        CInserts = 0;
        //Creates table C
        C = new char*[CCapacity]();
        //Inserts the objects into table C
        for(int i = 0; i < CCapacity; i++)
        {
            if(other.C[i] != NULL)
            {
                if(other.C[i] == DELETED)
                {
                    C[i] = DELETED;
                }
                else
                {
                    int temp = 0;
                    char * tempChar = other.C[i];
                    for(int k = 0; tempChar[k] != '\0'; k++)
                    {
                        temp++;
                    }
                    temp++;
                    char * newStr = (char*) malloc(temp*sizeof(char)+1);
                    strcpy ((char*)newStr,tempChar);
                    newStr[temp] = '\0';
                    C[i] = newStr;
                    CSize++;
                }
                CInserts++;
            }
        }
    }
    else{
        C = NULL;
    }
}

const HashTable& HashTable::operator= (HashTable& rhs)
{
    //All of this is just like the destructor
    if(A != NULL)
    {
        for(int i = 0; i < ACapacity; i++)
        {
            if(A[i] != NULL && A[i] != DELETED)
            {
                free(A[i]);
            }
        }
        delete [] A;
    }
    if(B != NULL)
    {
        for(int i = 0; i < BCapacity; i++)
        {
            if(B[i] != NULL && B[i] != DELETED)
            {
                
                free(B[i]);
            }
        }
        delete [] B;
    }
    if(C != NULL)
    {
        for(int i = 0; i < CCapacity; i++)
        {
            if(C[i] != NULL && C[i] != DELETED)
            {
                free(C[i]);
            }
        }
        delete [] C;
    }
    
    //Works the same as the copy constructor
    //If other object has table A
    if(rhs.A != NULL)
    {
        isRehashingToA = true;
        isRehashingToB = false;
        isRehashingToC = false;
        //Checks to see if it is rehashing to A
        if(rhs.C != NULL)
        {
            Rehashing = true;
        }
        //checks to see if A is the table rehashing
        if(rhs.B != NULL)
        {
            isRehashingToA = false;
            isRehashingToB = true;
            isRehashingToC = false;
        }
        //Sets the Attributes of table A
        ACapacity = rhs.ACapacity;
        ASize = 0;
        AInserts = 0;
        //Creates table A
        A = new char*[ACapacity]();
        //Inserts the objects into table A
        for(int i = 0; i < ACapacity; i++)
        {
            if(rhs.A[i] != NULL)
            {
                if(rhs.A[i] == DELETED)
                {
                    A[i] = DELETED;
                }
                else
                {
                    int temp = 0;
                    char * tempChar = rhs.A[i];
                    for(int i = 0; tempChar[i] != '\0'; i++)
                    {
                        temp++;
                    }
                    temp++;
                    char * newStr = (char*) malloc(temp*sizeof(char)+1);
                    strcpy ((char*)newStr,tempChar);
                    newStr[temp] = '\0';
                    A[i] = newStr;
                    ASize++;
                }
                AInserts++;
            }
        }
    }
    //If other object has table B
    if(rhs.B != NULL)
    {
        isRehashingToA = false;
        isRehashingToB = true;
        isRehashingToC = false;
        //Checks to see if it is rehashing to B
        if(rhs.A != NULL)
        {
            Rehashing = true;
        }
        //checks to see if B is the table rehashing
        if(rhs.C != NULL)
        {
            isRehashingToA = false;
            isRehashingToB = false;
            isRehashingToC = true;
        }
        //Sets the Attributes of table B
        BCapacity = rhs.BCapacity;
        BSize = 0;
        BInserts = 0;
        //Creates table B
        B = new char*[BCapacity]();
        //Inserts the objects into table B
        for(int i = 0; i < BCapacity; i++)
        {
            if(rhs.B[i] != NULL)
            {
                if(rhs.B[i] == DELETED)
                {
                    B[i] = DELETED;
                }
                else
                {
                    int temp = 0;
                    char * tempChar = rhs.B[i];
                    for(int i = 0; tempChar[i] != '\0'; i++)
                    {
                        temp++;
                    }
                    temp++;
                    char * newStr = (char*) malloc(temp*sizeof(char)+1);
                    strcpy ((char*)newStr,tempChar);
                    newStr[temp] = '\0';
                    B[i] = newStr;
                    BSize++;
                }
                BInserts++;
            }
        }
    }
    //If other object has table C
    if(rhs.C != NULL)
    {
        isRehashingToA = false;
        isRehashingToB = false;
        isRehashingToC = true;
        //Checks to see if it is rehashing to C
        if(rhs.B != NULL)
        {
            Rehashing = true;
        }
        //checks to see if C is the table rehashing
        if(rhs.A != NULL)
        {
            isRehashingToA = true;
            isRehashingToB = false;
            isRehashingToC = false;
        }
        //Sets the Attributes of table C
        CCapacity = rhs.CCapacity;
        CSize = 0;
        CInserts = 0;
        //Creates table C
        C = new char*[CCapacity]();
        //Inserts the objects into table C
        for(int i = 0; i < CCapacity; i++)
        {
            if(rhs.C[i] != NULL)
            {
                if(rhs.C[i] == DELETED)
                {
                    C[i] = DELETED;
                }
                else
                {
                    int temp = 0;
                    char * tempChar = rhs.C[i];
                    for(int i = 0; tempChar[i] != '\0'; i++)
                    {
                        temp++;
                    }
                    temp++;
                    char * newStr = (char*) malloc(temp*sizeof(char)+1);
                    strcpy ((char*)newStr,tempChar);
                    newStr[temp] = '\0';
                    C[i] = newStr;
                    CSize++;
                }
                CInserts++;
            }
        }
    }
    return *this;
}





