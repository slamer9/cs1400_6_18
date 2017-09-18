#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>    // std::sort
#include <unistd.h>     //sleep();

using namespace std;

#define minScore 0
#define maxScore 100

bool properInput = false;
string instructionString;


void getExamScore(int& exam) 
{
    char tempChar;
    while(properInput == false)
    {
        cout << instructionString;
        cout << endl << endl;
        if(cin >> exam)
        {
            if(exam >= minScore && exam <= maxScore)
            {
                properInput = true;
            } else {
                cout << "Sorry, your input must be between 0 and 100 Please try again." << endl;
            }
        } else {
            cin.clear();
            while(cin.get(tempChar) && !isspace(tempChar)) // Clear bad number
            {
                //Do nothing for now
            }
            //cin.ignore(numeric_limits<streamsize>::max(), '\n'); //(Code from C++.com, idk how it works, need to look up) NOT GOOD IN CORNER CASES, CIN.GET() BETTER WAY
            cout << "Sorry, your input must be an integer. Please try again." << endl;
        }
    }
    properInput = false;
    return;
}

void getHomeworkScores(vector<int>& homeworkVector)
{
    int temp;
    char tempChar;
    
    while(true)
    {
        cout << instructionString << endl << endl;
        cin >> temp;
        
        if(cin.eof())
        {
            return;
        }
        if(cin.good())
        {
            if(temp >= minScore && temp <= maxScore)
            {
                homeworkVector.push_back(temp);
            } else {
                cout << "Sorry, your input must be between 0 and 100 Please try again." << endl;
            }
        } else if (cin.fail())
        {
            cin.clear();
            while(cin.get(tempChar) && !isspace(tempChar)) // Clear bad number
            {
                //Do nothing for now
            }
            cout << "Sorry, your input must be an integer. Please try again." << endl;

        } else if (cin.bad())
        {
            cout << "Input stream set to bad, something went wrong." << endl;
            return;
        } else {
            cout << "***Unknown Error*****" << endl;
            return;
        }
    }

}

double getMedianScore(vector<int>& homeworkVector)
{
    int temp;
    sort(homeworkVector.begin(), homeworkVector.end()); 
    
    int size = homeworkVector.size();
    if((size % 2) == 0)    //Even
    {
        temp = size/2;
        return (homeworkVector.at(temp) + homeworkVector.at(temp-1))/2;
        
    } else {                                //Odd
        temp = (size - 1)/2;
        return homeworkVector.at(temp);
    }
}

void printLetterGrade(int& totalPoints)
{
    if(totalPoints>380)
    {
        cout << "The letter calculated letter grade is A";
    } else if(totalPoints>360)
    {
        cout << "The letter calculated letter grade is A-";
    } else if(totalPoints>340)
    {
        cout << "The letter calculated letter grade is B+";
    } else if (totalPoints>320)
    {
        cout << "The letter calculated letter grade is B";
    } else if (totalPoints>300)
    {
        cout << "The letter calculated letter grade is B-";
    } else if (totalPoints>280)
    {
        cout << "The letter calculated letter grade is C+";
    } else if (totalPoints>260)
    {
        cout << "The letter calculated letter grade is C";
    } else if(totalPoints>240)
    {
        cout << "The letter calculated letter grade is C-";
    } else if(totalPoints>220)
    {
        cout << "The letter calculated letter grade is D+";
    } else if (totalPoints>200)
    {
        cout << "The letter calculated letter grade is D";
    } else if (totalPoints>180)
    {
        cout << "The letter calculated letter grade is D-";
    } else {
        cout << "The letter calculated letter grade is fail";
    }
}

int main() 
{
    int exam1; //Main variable declarations
    int exam2;
    int exam3;
    double medianValue;
    int totalPoints;
    vector<int> recordVector;
    
    cout << "Dr. DoLittle's Grading Program ....." << endl << endl;
    
    instructionString.assign("Please enter in the score for the first exam: ");
    getExamScore(exam1);
    instructionString.assign("Please enter in the score for the second exam: ");
    getExamScore(exam2);
    instructionString.assign("Please enter in the score for the final exam: ");
    getExamScore(exam3);
    
    instructionString.assign("Enter the score for a homework assignment (signal EOF when done): ");
    getHomeworkScores(recordVector);
    
    medianValue = getMedianScore(recordVector);
    totalPoints = medianValue + exam1 + exam2 + exam3;
 
    cout << "The median homework score was " << medianValue << endl;
    cout << "The total points earned was " << totalPoints << endl;
    printLetterGrade(totalPoints);
}