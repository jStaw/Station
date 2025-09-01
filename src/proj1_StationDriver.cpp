/**
* 
* File Name: assign proj1_StationDriver.cpp
*
* Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating 
* this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is
* a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure 
* and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another 
* individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic 
* Dishonesty Board. See Academic Integrity Procedural Guidelines Links to an external site. at:  
* https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines
*
* Your Name: John Stawski 
*
* Your PSU user ID: jrs7535
*
* Course Title: CMPSC 465 WC Sections 1 & 2
*
* Due Time: 11:59pm, Sunday, September 7, 2025 
*
* Time of Last Modification: 7:34am, Monday, September 1, 2025
*
* Description: This is the driver file for Project 1 - Station. It will read the input file (lab1in.txt), which gives the size of 
* train block as the first line which will be N. The data stream for each block of coaches will be stored according to the file
* ordering in an array.
* This array will be passed to canMarshallCoaches(). In this function the coaches 1 ... N will be utilize a stack to check if the 
* permutation can be marshalled onto track B. It will return true or false.
*/

#include <iostream>
#include <fstream>
#include <stack>

bool canMarshallCoaches(const int *array, int size) {
  std::stack<int> stationStack;
  int cnt = 0;

  for(int i = 0; i < size; i++) {
    stationStack.push(i + 1); 
    // check if the stack is not empty and if the top element matches the current position 
    // of the permutaiton array passed in. Cnt will keep track of the index of that array.
    // It will pop the top element if both conditions are met and the cnt counter will be incremented.
    while(!stationStack.empty() && stationStack.top() == *(array + cnt)) {
      stationStack.pop();
      cnt++;
    }
  }
  // empty stack means the coaches can be marshalled.
  return stationStack.empty();
}

int main() {

  std::string filePathIn = "tests/lab1in.txt";
  std::string filePathOut = "tests/lab1out.txt";
  std::ifstream fileIn(filePathIn);
  std::ofstream fileOut(filePathOut);

  if (!fileIn.is_open()) {
    std::cerr << "Error: Could not open the file at " << filePathIn << std::endl;
    return 1;
  }

  int N;  // size of each coach.
  fileIn >> N;
  int nextInt;


  while(fileIn) {
    
    int coachArragnement[N];
    std::streampos currentPosition = fileIn.tellg(); // stores current position in file. Allows to peek to the next string.
    fileIn >> nextInt; // move to the next string i.e. peeking.

    // Will break the loop if a 0 is located.
    if(N == 0 || nextInt == 0) {
      fileOut << '\n';
      break;
    } else {
      fileIn.seekg(currentPosition); // Restoring the pointer to the position of currentPosition.
    }  
    
    // load content of file into an array that keeps the order of the permutation of the coaches.
    for(int i = 0; i < N; i++) {
      fileIn >> coachArragnement[i];
    }

    // This will update the output of each train viability
    if (canMarshallCoaches(coachArragnement, N)) {
      fileOut << "yes\n";
    } else {
      fileOut << "No\n";
    }
  }

  fileIn.close();
  fileOut.close();

  return 0;
}
