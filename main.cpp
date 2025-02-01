#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

class Ulam {
public:
    std::vector<std::vector<int>> matrix; 
    std::vector<bool> primes; 

    Ulam(int num) {
        primes = sieve(num);
        int size = sqrt(num);
        matrix.resize(size, std::vector<int>(size, 0));

        generateSpiral(num);
    }

    // Sieve of Eratosthenes 
    std::vector<bool> sieve(int num) {
        std::vector<bool> prime(num + 1, true);
        for (int p = 2; p * p <= num; p++) {
            if (prime[p]) {
                for (int i = p * p; i <= num; i += p) {
                    prime[i] = false;
                }
            }
        }
        return prime;
    }

    // Generate the spiral matrix
    void generateSpiral(int num) {
        int size = sqrt(num);
        int x = size / 2, y = size / 2;

        if (num % 2 == 0) {
            x -= 1;
            y -= 1;
        }

        int dirs[4][2] = { {0,1}, {-1,0}, {0,-1}, {1,0} }; // Right, Up, Left, Down
        int dir = 0;  // Start direction is right
        int steps = 1; // Steps to take in current direction

        int val = 1; // Initial value to fill in spiral, Increments 
        while (val <= num) {
            for (int i = 0; i < steps; ++i) { // Move steps in current direction
                if (x >= 0 && x < size && y >= 0 && y < size) {
                    matrix[x][y] = val++;
                    if (val > num) break; // Stop if we've placed all numbers
                }
                x += dirs[dir][0];
                y += dirs[dir][1];
            }

            dir = (dir + 1) % 4; // Change direction

            // Increase step count every two direction changes (one full cycle: right-down-left-up)
            if (dir == 0 || dir == 2) steps++;
        }
    }

    void printSpiral(std::ofstream& output) {
        int size = matrix.size();
        for (int i = 0; i < size; i++) { 
            for (int j = 0; j < size; j++) {
                if (primes[matrix[i][j]]) {
                    output << "* ";
                }
                else {
                    output << "# ";
                }
            }
            output << std::endl;
        }
    }

    int maxDiagonalSequence() {
        
    }
};

bool isPerfectSquare(int num) {
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

int main() {
    int n;
    std::ofstream outputFile("spiral_output10000.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    std::cout << "Enter the number to spiral down from: ";
    std::cin >> n;

    int targetNum = isPerfectSquare(n) ? n : nearestPerfectSquare(n);
    Ulam spiral(targetNum);

    spiral.printSpiral(outputFile);

    outputFile.close();
    
    return 0;
}
