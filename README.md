# Ulam Spiral
The [Ulam spiral](https://en.wikipedia.org/wiki/Ulam_spiral) or prime spiral is a graphical depiction of the set of prime numbers, devised by mathematician Stanisław Ulam in 1963.

![image](https://github.com/nicholasbrar/Ulam/assets/153023837/8d6add2f-7742-4e68-a5b7-3bac546a3a2a)                       ![image](https://github.com/nicholasbrar/Ulam/assets/153023837/4e17ecd7-afda-41be-a9ac-675f55accd7c)

The image on the left shows the pattern in which numbers are spiraled. The image on the right outlines the prime numbers in the spiral.

This program was devised to visualize this spiral to whichever number is specified.

## Primes 

For determining whether an integer is prime, this program uses

[Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) 

for efficiency when computing the primality of larger numbers. I previously used trial division, but learned about Sieve through exploring number theory and algorithms. 

# Ongoing Efforts
It's my goal to implement an algorithm which computes the diagonal of max length containing only primes. I intend on using a sliding-window approach in the goal of computational efficiency. 

I'd like to attempt to define a function f: n -> d, where n is the width of the (n x n) matrix and d is the length of the max diagonal, and see if any interesting results follow.

Update from early 2025: 
Preliminary research questions that I've defined with the hopes to revisiting when my schedule allows.
![image](file:///C:/Users/14123/Downloads/Ulam_Research.pdf)


# Results
The interesting nature of the Ulam Spiral is rooted in the striking presence of diagonals that form. 

Below, are the results of spirals generated by the program, showcasing 3 spirals with increasing length that help illustrate the pattern.



(Note: Composite numbers are marked with "#", while primes are marked with "*".)


### Spiral with 100 numbers
![image](https://github.com/nicholasbrar/UlamSpiral/assets/153023837/a81dd794-71e8-424f-a2fc-70a93259358e)

### Spiral with 4900 numbers
![image](https://github.com/nicholasbrar/UlamSpiral/assets/153023837/9fd93d9f-9e53-4af6-abd5-b11a8f8becee)

### Spiral with 10000 numbers
![image](https://github.com/nicholasbrar/UlamSpiral/assets/153023837/38f356a9-d784-435d-a023-82821bddb7d0)

