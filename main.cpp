#include <iostream> 
#include <vector>
#include <cmath>
#include <stdlib.h> 
#include <windows.h>
#include <fstream>

bool isPrime(int num){ // Checks if number is prime  
  if(num <= 1) return false;
  if(num <= 3) return true; 
  if(num % 2 == 0 || num % 3 == 0) return false;
  for (int i = 5; i * i <= num; i += 6)  
      if (num % i == 0 || num % (i + 2) == 0)
          return false;
  return true;
}

void printSpiral(int num, std::ofstream& output){
  int size = sqrt(num);
  std::vector<std::vector<int>> spiral(size, std::vector<int>(size, 0));

  int x = size / 2, y = size / 2; 

  if(num % 2 == 0){ 
    x -= 1;
    y -= 1;
  }

  int dirs[4][2] = {{0,1}, {-1,0}, {0,-1}, {1,0}}; // Right, Up, Left, Down
  int dir = 0;  // Start direction is right
  int steps = 1; // Steps to take in current direction

  int val = 1; // Initial value to fill in spiral, Increments 
  while (val <= num) {
      for (int i = 0; i < steps; ++i) { // Move steps in current direction
          if (x >= 0 && x < size && y >= 0 && y < size) {
              spiral[x][y] = val++;
              if (val > num) break; // Stop if we've placed all numbers
          }
          x += dirs[dir][0];
          y += dirs[dir][1];
      }

      dir = (dir + 1) % 4; // Change direction

      // Increase step count every two direction changes (one full cycle: right-down-left-up)
      if (dir == 0 || dir == 2) steps++;
  }



  for (int i = 0; i < size; i++) { // Output visualization
      for (int j = 0; j < size; j++) {
          if(isPrime(spiral[i][j])){
              output << "* ";
          }
          else{
              output << "# ";
          }
      }
      output << std::endl;
  }
}

bool isPerfectSquare(int num){
    int root = sqrt(num);
    return (root * root == num);
}

int nearestPerfectSquare(int num) {
    int numCopy = num; 
    while (!isPerfectSquare(numCopy)) {
        numCopy++;
    }
    return numCopy;
}

int main(){
  int n;
  std::ofstream outputFile("spiral_output1000000.txt");

  if (!outputFile.is_open()) {
      std::cerr << "Failed to open output file." << std::endl;
      return 1;
  }

  std::cout << "Enter the number to spiral down from: ";
  std::cin >> n; 

  if(isPerfectSquare(n)){
    printSpiral(n, outputFile);
  }
  else{
    printSpiral(nearestPerfectSquare(n), outputFile);
  }

  outputFile.close();
  
  return 0;
}