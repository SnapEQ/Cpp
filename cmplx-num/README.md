# Complex numbers

`ComplexNumber` class with arithmetic, compound assignment, comparison, amplitude, phase and `<<` operators, plus a test program.

## Build and run

```sh
g++ -std=c++17 -Wall -Wextra Complex.cpp TestComplex.cpp -o test && ./test
```

## Expected results checked with Wolfram|Alpha

Each link opens the calculation in Wolfram|Alpha, so you can confirm the values the tests expect.

### Complex operators

| Test | Calculation | Result |
|---|---|---|
| addition | [`(2-3i)+(3+2i)`](https://www.wolframalpha.com/input?i=%282-3i%29%2B%283%2B2i%29) | 5 - i |
| subtraction | [`(2-3i)-(3+2i)`](https://www.wolframalpha.com/input?i=%282-3i%29-%283%2B2i%29) | -1 - 5i |
| multiplication | [`(2-3i)*(3+2i)`](https://www.wolframalpha.com/input?i=%282-3i%29%2A%283%2B2i%29) | 12 - 5i |
| i * i | [`i*i`](https://www.wolframalpha.com/input?i=i%2Ai) | -1 |
| division | [`(2-3i)/(3+2i)`](https://www.wolframalpha.com/input?i=%282-3i%29%2F%283%2B2i%29) | -i |
| result times divisor | [`(-i)*(3+2i)`](https://www.wolframalpha.com/input?i=%28-i%29%2A%283%2B2i%29) | 2 - 3i |
| number divided by itself | [`(3+2i)/(3+2i)`](https://www.wolframalpha.com/input?i=%283%2B2i%29%2F%283%2B2i%29) | 1 |

### Operators with a double

| Test | Calculation | Result |
|---|---|---|
| double addition | [`(2-3i)+2.5`](https://www.wolframalpha.com/input?i=%282-3i%29%2B2.5) | 4.5 - 3i |
| double subtraction | [`(2-3i)-2.5`](https://www.wolframalpha.com/input?i=%282-3i%29-2.5) | -0.5 - 3i |
| double multiplication | [`(2-3i)*2`](https://www.wolframalpha.com/input?i=%282-3i%29%2A2) | 4 - 6i |
| double division | [`(2-3i)/2`](https://www.wolframalpha.com/input?i=%282-3i%29%2F2) | 1 - 1.5i |
| reversed addition | [`1+(2+4i)`](https://www.wolframalpha.com/input?i=1%2B%282%2B4i%29) | 3 + 4i |
| reversed subtraction | [`1-(2+4i)`](https://www.wolframalpha.com/input?i=1-%282%2B4i%29) | -1 - 4i |
| reversed multiplication | [`1.5*(2+4i)`](https://www.wolframalpha.com/input?i=1.5%2A%282%2B4i%29) | 3 + 6i |
| reversed division | [`1/(2+4i)`](https://www.wolframalpha.com/input?i=1%2F%282%2B4i%29) | 0.1 - 0.2i |

### Compound and chained assignment

| Test | Calculation | Result |
|---|---|---|
| `+=` complex | [`(2-3i)+(3+2i)`](https://www.wolframalpha.com/input?i=%282-3i%29%2B%283%2B2i%29) | 5 - i |
| `-=` complex | [`(5-i)-(3+2i)`](https://www.wolframalpha.com/input?i=%285-i%29-%283%2B2i%29) | 2 - 3i |
| `*=` complex | [`(2-3i)*(3+2i)`](https://www.wolframalpha.com/input?i=%282-3i%29%2A%283%2B2i%29) | 12 - 5i |
| `/=` complex | [`(12-5i)/(3+2i)`](https://www.wolframalpha.com/input?i=%2812-5i%29%2F%283%2B2i%29) | 2 - 3i |
| `+=` double | [`(2-3i)+1.5`](https://www.wolframalpha.com/input?i=%282-3i%29%2B1.5) | 3.5 - 3i |
| `*=` double | [`(2-3i)*2`](https://www.wolframalpha.com/input?i=%282-3i%29%2A2) | 4 - 6i |
| `/=` double | [`(4-6i)/2`](https://www.wolframalpha.com/input?i=%284-6i%29%2F2) | 2 - 3i |
| chained `+=`, right side | [`(0.9+0.1i)+(0.8+0.1i)`](https://www.wolframalpha.com/input?i=%280.9%2B0.1i%29%2B%280.8%2B0.1i%29) | 1.7 + 0.2i |
| chained `+=`, left side | [`(1+0.3i)+(0.9+0.1i)+(0.8+0.1i)`](https://www.wolframalpha.com/input?i=%281%2B0.3i%29%2B%280.9%2B0.1i%29%2B%280.8%2B0.1i%29) | 2.7 + 0.5i |
| braced `*=` | [`(1+0.3i)*(0.9+0.1i)*(0.8+0.1i)`](https://www.wolframalpha.com/input?i=%281%2B0.3i%29%2A%280.9%2B0.1i%29%2A%280.8%2B0.1i%29) | 0.659 + 0.383i |

### Amplitude and phase

| Test | Calculation | Result |
|---|---|---|
| amplitude of 3+4i | [`abs(3+4i)`](https://www.wolframalpha.com/input?i=abs%283%2B4i%29) | 5 |
| amplitude of -3-4i | [`abs(-3-4i)`](https://www.wolframalpha.com/input?i=abs%28-3-4i%29) | 5 |
| amplitude of 2i | [`abs(2i)`](https://www.wolframalpha.com/input?i=abs%282i%29) | 2 |
| amplitude of 0 | [`abs(0)`](https://www.wolframalpha.com/input?i=abs%280%29) | 0 |
| phase of 1+i | [`arg(1+i)`](https://www.wolframalpha.com/input?i=arg%281%2Bi%29) | π/4 |
| phase of -1+i | [`arg(-1+i)`](https://www.wolframalpha.com/input?i=arg%28-1%2Bi%29) | 3π/4 |
| phase of -1-i | [`arg(-1-i)`](https://www.wolframalpha.com/input?i=arg%28-1-i%29) | -3π/4 |
| phase of 1-i | [`arg(1-i)`](https://www.wolframalpha.com/input?i=arg%281-i%29) | -π/4 |
| phase of 2i | [`arg(2i)`](https://www.wolframalpha.com/input?i=arg%282i%29) | π/2 |
| phase of 2 | [`arg(2)`](https://www.wolframalpha.com/input?i=arg%282%29) | 0 |

### Division by zero

| Test | Calculation | Result |
|---|---|---|
| complex / 0 | [`(2-3i)/0`](https://www.wolframalpha.com/input?i=%282-3i%29%2F0) | complex infinity, so the code throws `std::domain_error` |
| double / 0 | [`1/0`](https://www.wolframalpha.com/input?i=1%2F0) | complex infinity, so the code throws `std::domain_error` |
| zero divided by a number | [`0/(2-3i)`](https://www.wolframalpha.com/input?i=0%2F%282-3i%29) | 0 |
