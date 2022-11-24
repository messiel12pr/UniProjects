#include <iostream>
#include <fstream>
#include <string>

#include <windows.h>

#include "LinkedStack.h"
#include "DynamicSet.h"

using namespace std;

void readFromTxt(DynamicSet<string> &, const string); // function that reads data from a txt file and inputs it into a set
void parsing(DynamicSet<string> const &, DynamicSet<string> const &, const string); // validates html file

int main()
{
    DynamicSet<string> tags, selfClosingTags;
    string fileName;

    // reading the text files into two sets
    fileName = "tags.txt";
    readFromTxt(tags, fileName);

    fileName = "self-closing.txt";
    readFromTxt(selfClosingTags, fileName);

    // validating html file
    parsing(tags, selfClosingTags, "index.html");

    return 0;
}

/**
 *  readFromTxt
 *
 *  Reads every line from a txt file and adds it to a set
 *
 *  Parameters:
 *      set - set of type string that holds all of the tags
 *      fileName - name of the txt file to open
 */
void readFromTxt(DynamicSet<string> &set, const string fileName)
{
    ifstream inFile;

    inFile.open(fileName, ios::in);

    if (inFile.is_open())
    {
        string s = "";
        while (!inFile.eof())
        {
            inFile >> s;
            set.add(s);
        }
    }

    else
    {
        cout << "ERROR: The file did not open correctly" << endl;
    }

    inFile.close();
}

/**
 *  parsing
 *
 *  Reads every line from an html file,
 *  ignores every space or text inside the tags and
 *  validates the html tags using a stack.
 *
 *  Parameters:
 *      tags - set that hold html tags
 *      selfClosingTags - set that holds the self closing tags
 *      fileName - name of the html file to read from
 *
 *  This function also tells the user what type of error the file has and
 *  where the error was found if it finds an error
 */
void parsing(DynamicSet<string> const &tags, DynamicSet<string> const &selfClosingTags, const string fileName)
{
    // this stack will check if we open and close the tags correctly
    LinkedStack<string> validateTags;
    int line = 0;
    ifstream inFile;
    inFile.open(fileName, ios::in);

    if (inFile.is_open())
    {
        string s = "";
        string currentTag = "";
        bool closing = false, open = false;

        while (!inFile.eof())
        {
            // getting a single line from the html file and storing it in a string
            getline(inFile, s);
            line++;

            // traversing the line looking for tags
            for(int i = 0; i<s.length(); i++)
            {
                if (s[i] == '<')
                {
                    open = true;
                    i++;
                }

                if (s[i] == '/')
                {
                    closing = true;
                    i++;
                }

                if (open == true && s[i] != ' ' && s[i] != '>')
                {
                    // add char to currentTag
                    currentTag += s[i];
                }

                // checking that the file contains <!DOCTYPE html>
                if(s[i] == '>' && line == 1)
                {
                    if(currentTag != "!DOCTYPEhtml")
                    {
                        cout<<"ERROR ON LINE 1: MISSING <!DOCTYPE html> OR TYPO"<<endl;
                        return;
                    }

                    open = false;
                    currentTag = "";
                }

                // if this if statement is executed it means we have a complete tag
                // ready to be validated
                if ((s[i] == '>' || s[i] == ' ') && (open == true && line != 1))
                {
                    // checking special cases

                    // checking if we have a valid self closing tag that is closing
                    if (closing == true && selfClosingTags.isElement(currentTag) == true)
                    {
                        cout << "ERROR ON LINE: " << line << " THE TAG " << currentTag << " IS SELF CLOSING" << endl;
                        return;
                    }

                    else if (selfClosingTags.isElement(currentTag) == true)
                    {
                        // The tag is self closing so we dont have to add it to the stack
                    }

                    // checking if we have a valid tag that is closing
                    else if (closing == true && tags.isElement(currentTag) == true)
                    {
                        if(validateTags.isEmpty())
                        {
                            cout<<"ERROR ON LINE "<<line<<" CLOSING TAG WITHOUT PREVIOUS OPENING TAG "<<currentTag<<endl;
                            return;
                        }

                        // check if its a valid closing tag by comparing it to the 
                        // top tag in our stack
                        if (validateTags.top() != currentTag)
                        {   
                            // error the last tag isn't equal to the current tag that is closing
                            cout << "ERROR ON LINE: " << line << " END TAG " << validateTags.top() << endl;
                            return;
                        }

                        // because we have a valid closing tag we can simply pop the opening tag
                        // at the top and continue traversing our file
                        validateTags.pop();
                    }

                    // checking if we have a valid opening tag
                    else if (tags.isElement(currentTag) == true)
                    {
                        // add the opening tag to the top of the stack
                        validateTags.push(currentTag);
                    }

                    else
                    {
                        // error unkown tag
                        cout << "ERROR ON LINE: " << line << " UNKOWN TAG " << currentTag << endl;
                        return;
                    }

                    // reset the variables
                    open = false;
                    closing = false;
                    currentTag = "";
                }
            }
        }
    }

    if (validateTags.isEmpty())
        cout<<"HTML IS VALID!"<<endl;

    else
        cout << "ERROR ON LINE: " << line << " END TAG " << validateTags.top() << endl;

    inFile.close();
}
