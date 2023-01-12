#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */
void Clean_Whitespace(char str[]) {
    int i = 0;
    int j;
    int whitespaceCounter = 0;

    // Remove leading whitespace
    while(str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'){
        j = i;
        // Shift array by one
        while(str[j] != '\0'){
          str[j] = str[j+1];
          j++;
        }
    }

    while(str[i] != '\0'){

      // Count if a space, newline, or tab is detected in a string
      if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'){
        whitespaceCounter++;
      } else{
        // reset the counter if a whitespace is no longer detected
        whitespaceCounter = 0;
      }

      // If there is more than one space in a row, shift array by one.
      if(whitespaceCounter > 1){
        j = i;
        
        // Shift array by one
        while(str[j] != '\0'){
          str[j] = str[j+1];
          j++;
        }
        i--;
      }

      // Increment by one 
      i++;
    }

    // Remove trailing whitespace
    if(whitespaceCounter > 0){
      while(str[i] < 'A' || str[i] > 'z'){
      i--;
      }
      i++;
      str[i] = '\0';
    }
    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {
  int i = 0;
  Clean_Whitespace(str);
  
  // Make the first letter of the next word uppercase 
  if(str[i] >= 'a' && str[i] <='z'){
    str[i] = str[i]-32;
  }
  i++;

  // Do this until end of string character is detected
  while(str[i] != '\0'){

    // If there is space in a string, increment i by one and make the first letter of the next word uppercase 
    if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'){ 
    i++;
      if(str[i] >= 'a' && str[i] <='z'){
        str[i] = str[i]-32;
      }
    i++;
    }

    // Make all upper case letters inside of words lower case
    if(str[i] >= 'A' && str[i] <= 'Z'){
      str[i] = str[i]+32;
    }
    i++;
  }
  return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    int year = atoi(str);
    return year;
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {
  int i = 0;
  char lastName[100];
  int spaceCounter = 0;

  while(str[i] != '\0'){
    if(str[i] == ' '){
      spaceCounter++;
    }
    i++;
  }
  if(spaceCounter == 0){
    return;
  }
  i = 0;

  // Increment through string until a space is found
  for(int k = 0; k < spaceCounter; k++){
    while(str[i] != ' '){
      i++;
    }

    // Increment by one to get to start of last name
    i++;
  }

  // Until end character is reached, continue to add characters to lastName variable
  int j = 0;
  while(str[i] != '\0'){
    lastName[j] = str[i];
    i++;
    j++;
  }
  lastName[j] = '\0';

  // Most janky roundabout way of copying an array bc im too lazy to go back and change this whole method
  i = 0;
  while (str[i+1] != '\0'){
    str[i] = '\0';
    i++;
  }
  str[i] = '\0';
  i = 0;
  while (lastName[i] != '\0'){
    str[i] = lastName[i];
    i++;
  }

  return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
    float rating = atof(str);
    return rating;
}

/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
  int i = 0;

  // Increment through string until a suffix is found
  do{
    i++;
  } while(str[i] < 'A' || str[i] > 'z' || str[i] == '\0');

  // Change to millions if m or M is found in the string
  if(str[i] == 'M' || str[i] == 'm'){
    for(int j = 0; j < 6; j++){
      str[i] = '0';
      i++;
    }
    str[i] = '\0';
  }

  // Change to thousands if k or K is found in the string
  if(str[i] == 'K' || str[i] == 'k'){
    for(int j = 0; j < 3; j++){
      str[i] = '0';
      i++;
    }
    str[i] = '\0';
  }

  // Convert dollars string to long to represent revenue
  return atol(str);
}

/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {

  int i; //source
  int j; //destination
  int row;
  char str[1024];

  // Repeat this process for each movie stored in the CSV file
  for (row = 0; row < num_movies; row++){
    
    // Copy the csv row into the str buffer
    i = 0;
    while (csv[row][i] != '\0'){
      str[i] = csv[row][i];
      i++;
    }
    csv[row][i] = '\0';

    // Start of row, so set the i (character counter) to 0
    i = 0;

    // Title: set the title, clean whitespace, and fix case
    j = 0;
    while (str[i] != ',') {
      titles[row][j] = str[i];
      i++;
      j++;
    }
    j++;
    titles[row][j] = '\0';
    Clean_Whitespace(titles[row]);
    Fix_Case(titles[row]);
    i++;

    // Year: clean whitespace and convert the string to an int
    char y[1024];
    j = 0;
    while (str[i] != ','){
      y[j] = str[i];
      i++;
      j++;
    }
    j++;
    y[j] = '\0';
    Clean_Whitespace(y);
    years[row] = String_To_Year(y);
    i++;

    // Ignore the runtime field since it isn't necessary
    while (str[i] != ','){
      i++;
    }
    i++;

    // Director: set the director last name, clean whitespace, and fix case
    j = 0;
    while (str[i] != ','){
      directors[row][j] = str[i];
      i++;
      j++;
    }
    directors[row][j] = '\0';
    Clean_Whitespace(directors[row]);
    Director_Last_Name(directors[row]);
    i++;

    // Year: clean whitespace and convert the string to a float
    char r[1024];
    j = 0;
    while (str[i] != ','){
      r[j] = str[i];
      i++;
      j++;
    }
    r[j] = '\0';
    Clean_Whitespace(r);
    ratings[row] = String_To_Rating(r);
    i++;

    // Set the value for revenue properly
    char d[1024];
    j = 0;
    while (str[i] != '\0'){
      d[j] = str[i];
      i++;
      j++;
    }
    d[j] = '\0';
    Clean_Whitespace(d);
    dollars[row] = String_To_Dollars(d);
    

  }

  return;
}

/* This function finds the longest movie/director length and adds two to it.
*/
int longest(int num_movies, char str[10][1024]){
  int mostChars = 0;
  int currChars = 0;
  int j;
  for(int i = 0; i < num_movies; i++){
    j = 0;
    currChars = 0;
    while(str[i][j] != '\0'){
      currChars++;
      j++;
    }
    if(currChars > mostChars){
      mostChars = currChars;
    }
  }
  return mostChars + 2;
}

/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 5, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    int longestTitle;
    int longestDirector;
    int id = 0;

    if(longest(num_movies, titles) > 7){
      longestTitle = longest(num_movies, titles);
    } else {
      longestTitle = 7;
    }

    if(longest(num_movies, directors) > 10){
      longestDirector = longest(num_movies, directors);
    } else {
      longestDirector = 10;
    }

    // Header
    printf("%-3s","Id");
    printf("%-*s", longestTitle, "Title");
    printf("%-6s", "Year");
    printf("%-*s", longestDirector, "Director");
    printf("%5s", "Rating");
    printf("%11s", "Revenue");

    for(int i = 0; i < num_movies; i++){
      printf("\n");
      id++;
      printf("%-3d",id);
      printf("%-*s", longestTitle, titles[i]);
      printf("%-6d", years[i]);
      printf("%-*s", longestDirector, directors[i]);
      printf("%6.1f", ratings[i]);
      printf("%11lld", dollars[i]);
    }
    printf("\n");
    return;
}
//This was a tester method that is now unused
int main() {
  char whitespaceTester[100] = "   this   is  the \ttext   \r \nbeing fixed    ";
  printf("\nBefore:%s", whitespaceTester);
  Clean_Whitespace(whitespaceTester);
  printf("\nAfter:%s", whitespaceTester);

  char caseFixTexter[100] = "i aM fIXinG tHe CaSE of ThIS teXT";
  printf("\nBefore:%s", caseFixTexter);
  Fix_Case(caseFixTexter);
  printf("\nAfter:%s", caseFixTexter);

  char yearTest[4] = "2016";
  printf("\nBefore:%s", yearTest);
  int yearAsInt = String_To_Year(yearTest);
  printf("\nAfter:%d", yearAsInt);

  char lastNameTester[100] = "Quentin Holle";
  printf("\nBefore:%s", lastNameTester);
  Director_Last_Name(lastNameTester);
  printf("\nAfter:%s", lastNameTester);

  char lastNameTester2[100] = "Quentin W. Holle";
  printf("\nBefore:%s", lastNameTester2);
  Director_Last_Name(lastNameTester2);
  printf("\nAfter:%s", lastNameTester2);

  char lastNameTester3[100] = "Holle";
  printf("\nBefore:%s", lastNameTester3);
  Director_Last_Name(lastNameTester3);
  printf("\nAfter:%s", lastNameTester3);

  char ratingTest[4] = "4.12";
  printf("\nBefore:%s", ratingTest);
  float ratingTester = String_To_Rating(ratingTest);
  printf("\nAfter:%f", ratingTester);

  char dollarTest[100] = "9k";
  printf("\nBefore:%s", dollarTest);
  long dollarTestOutput = String_To_Dollars(dollarTest);
  printf("\nAfter:%ld", dollarTestOutput);

  char dollarTest2[100] = "12K";
  printf("\nBefore:%s", dollarTest2);
  long dollarTestOutput2 = String_To_Dollars(dollarTest2);
  printf("\nAfter:%ld", dollarTestOutput2);

  char dollarTest3[100] = "982m";
  printf("\nBefore:%s", dollarTest3);
  long dollarTestOutput3 = String_To_Dollars(dollarTest3);
  printf("\nAfter:%ld", dollarTestOutput3);

  char dollarTest4[100] = "74M";
  printf("\nBefore:%s", dollarTest4);
  long dollarTestOutput4 = String_To_Dollars(dollarTest4);
  printf("\nAfter:%ld", dollarTestOutput4);

  char dollarTest5[100] = "74129378192837";
  printf("\nBefore:%s", dollarTest5);
  long dollarTestOutput5 = String_To_Dollars(dollarTest5);
  printf("\nAfter:%ld", dollarTestOutput5);
  printf("\n\n");


    char csv[10][1024] = {"The American, 2010, 105 minutes, Anton Corbijn, 6.3, 67800K", "Black Swan, 2010, 103 minutes, Darren Aronofsky, 8, 329M","How to Train Your Dragon, 2010, 90 minutes, Chris Sanders, 8.1, 495M", "Inception, 2010, 148 minutes, Christopher Nolan, 8.8, 836836967"}; // data structure for the entire movie csv file
    int num_movies = 4;
    char titles[10][1024];
    int years[10];
    char directors[10][1024];
    float ratings[10];
    long long dollars[10];

    char csv2[10][1024] = {"        The      American,     \n\t2010, 105 min       utes, \t\nAnton         Corbijn, 6.3,      \n\n10123123", "Black         Swan, 2010, 103 minutes,\n\nDarren Aronofsky, 8, 1091823","How to Train Your Dragon, 2010, 90 minutes, Chris Sanders, 8.1, 495M", "Inception, 2010, 148 minutes, Christopher Nolan, 8.8, 836836967"}; // data structure for the entire movie csv file
    int num_movies2 = 4;
    char titles2[10][1024];
    int years2[10];
    char directors2[10][1024];
    float ratings2[10];
    long long dollars2[10];

    Split(csv,num_movies,titles,years,directors,ratings,dollars);
    Print_Table(num_movies,titles,years,directors,ratings,dollars);


    Split(csv2,num_movies2,titles2,years2,directors2,ratings2,dollars2);
    Print_Table(num_movies2,titles2,years2,directors2,ratings2,dollars2);
}

