// Programmer: Sadeem Khan
// Programmer's ID: 1549921

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <cstring>

#include "DynamicArray.h"

int main()
{
  // Identification
  cout << "Programmer: Sadeem Khan\n";
  cout << "Programmer's ID: 1549921\n";
  cout << "File: " << __FILE__ << endl;

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";  

  DynamicArray<string> alreadySeen;
  DynamicArray<string> courses;

  int duplicates = 0;
  int count = 0;
  int x = 0;

  // read the input file
  while (fin.good())
  {
    count++;

    // Progress bar
    if (count % 1000 == 0) cout << '.';
    cout.flush();

    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    string key = term + section;
    bool found = false;
    for (int i = 0; i < alreadySeen.capacity(); i++) // go through already seen array of strings. If found make bool true and add number to duplica
      if (alreadySeen[i] == key) found = true;

    if (found) 
    {
      duplicates++;
      continue;
    }

    else 
    {
      alreadySeen[x] = key;
      courses[x] = subjectCode;
      x++;
    }
  }
  fin.close();

  for (int i = 0; i < x; i++)
    for (int j = i + 1; j < x; j++)
      if (courses[i] != string() && courses[j] != string() && courses[j] < courses[i]) 
        swap (courses[j],courses[i]);

  cout << endl;
  int a = 0;
  int b = 0;
  while (courses[a] != "") // If its not empty
  {
    for (a = b; courses[a] == courses[b] && b < x; b++) {}

    // prints all subjects and how many sections there have been
    if ((b - a) != 0) cout << courses[a] << ", " << b - a << " sections." << endl;
  }
  cout << "Total number of duplicates: " << duplicates << endl;
}