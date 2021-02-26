import random
f = open('strings.txt', 'w') #file for strings
f2 = open('superstrings.txt','w') #file for superstrings
f3 = open('output.txt','w') #file for expected output of assignment
words = ["Afnan", "Texas", "pHone","softWAre", "hello", "random", "unique","boston","words","dIscOrd","queStion","TextBook"] #target words. Put in manually
asciis = [i for i in range(65,91)] #contains list of all ascii codes for letters
asciis.extend([i for i in range(97,123)])
spaces = ['\n','\t',' ',' '] #contains character for all ignored characters in string. One more space put to make it more common
#print([chr(i) for i in asciis])
superstring = ""
"""
Function that inserts a word into a randomized string so that the string will now be a superstring of the word

Args:
    - string: the randomized string you want to put the word into
    - word: the word you want to insert

Return:
    - the new string with the word inserted randomly into the string
"""
def insertString(string, word):
    wordIndex = [] #will contain the indices of where each character of the word will go.
    prevIndex = 0 #contains the index of the previous letter so that the next letter does not go before it
    newWord = ""
    stringIndex = 0 #will be used to insert characters into new string
    sIndex = 0 #index of the original string. Pointer for string.
    for i in range(len(word)):
        wordIndex.append(random.randrange(prevIndex+1,len(string))) #picks a random location inside the string for the character in the word to go into. Must be after the previous character of the word
        # print(wordIndex[i])
        if(wordIndex[i]>len(string) - (len(word)-i)): #checks to see if the character is too far to the end of the string. If there aren't enough characters in the string after where the current character was placed to finish the word, then we will just append the rest of the word to the end of the string
            # print(word)
            # print(string)
            string += word[i+1:] #appends the rest of the word to the end of the string.
            #print(string)
            break #ends the loop for the word.
        prevIndex = wordIndex[i]
    #print(wordIndex)
    while(stringIndex < len(wordIndex)+len(string)): #add characters to the new string. Length of new string should be len(word) + len(string)
        if(stringIndex in wordIndex): #if you reach the index in the string where a character in word is supposed to go, insert that character. Otherwise, keep inserting characters from the string.
            # print(word[wordIndex.index(stringIndex)])
            newWord+= word[wordIndex.index(stringIndex)]
        else:
            # print(sIndex)
            newWord+= string[sIndex]
            sIndex+=1 #if character from string was added, point to the next character
        stringIndex+=1
    # print(newWord)
    return newWord

superstrings = [] #contains all the super strings.
wordsInSuperStrings = [] #This will be a list of lists. For each superstring, there will be a corresponding list that contains all the words that are contained in that superstring.    

for i in range(40): #creating 10 random superstrings
    superstring = ""
    length = random.randrange(2,18) 
    for j in range(length):#add some random letters
        superstring += chr(random.choice(asciis))
    superstrings.append(superstring)
    wordsInSuperStrings.append([])
    for k in words:
        r = random.random()
        if(r > 0.70 and len(superstrings[i]) + len(k) <=19): #for each word, there is a 30% chance that it will be inserted into the superstring
            superstrings[i] = insertString(superstrings[i], k) #creates the new superstring with the word inserted
            wordsInSuperStrings[i].append(k) #adds the current word to the list of words for the current superstring
            #print(superstrings[i])

print(superstrings)
print(wordsInSuperStrings)
    # for i in range(5):
    #     superstring += random.choice(spaces)
candidates = ""
for i in superstrings: #create the candidates string
    candidates += i
    r = random.randrange(1,4)
    for i in range(r): #adds a random amount of spaces, new lines, and tabs.
        candidates+= random.choice(spaces)
f2.write(candidates)
f2.close()
targets = ""
for i in words: #create targets string.
    targets+= i
    r = random.randrange(1,4)
    for i in range(r): #adds a random amount of spaces, new lines, and tabs
        targets+= random.choice(spaces)
f.write(targets)
f.close()
print(candidates)
print('\n')
for i in words: #goes through each word and sees if it is contained in each superstring. If it is, the superstring will be printed.
    print("WORD: "+ i)
    for j in range(len(superstrings)):
        if(i in wordsInSuperStrings[j]):
            print(superstrings[j])
            f3.write(superstrings[j] + '\n')
f3.close()


