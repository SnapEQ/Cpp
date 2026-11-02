# Mock test 3 - Stack of complex numbers

**Time limit:** 120 minutes. No internet.

This one combines both projects: first you write the `ComplexNumber` operators, then a dynamic
`ComplexStack` that stores `ComplexNumber` objects and uses those operators.

## Files

| File | What it is | Edit it? |
|---|---|---|
| `Complex.h` | `ComplexNumber` declaration | No |
| `Complex.cpp` | Constructor/getters/setters given, every operator is a stub | **Yes** |
| `ComplexStack.h` | `ComplexStack` declaration | Only the `private:` section |
| `ComplexStack.cpp` | Stubs - every function throws "not implemented" | **Yes** |
| `TestComplexStack.cpp` | Test cases, grouped into parts A-D | No |
| `build.sh` | Builds with AddressSanitizer and runs the tests | No |

```bash
./build.sh
```

**You pass when** the last line says `All tests passed - mock test PASSED` **and** AddressSanitizer
reports nothing.

## Part A - `ComplexNumber` (25%)

Implement every operator in `Complex.cpp`. For `z = a + bi`:

| Operator | Meaning |
|---|---|
| `+ - * /` with another `ComplexNumber` | Usual complex arithmetic. `(a+bi)/(c+di)` = multiply top and bottom by the conjugate `c-di`. |
| `+ - * /` with a `double` (number on the right) | The `double` is the complex number `x+0i`. |
| `double + - * / ComplexNumber` (number on the left) | Free functions. Watch out: `2 - z` is **not** `z - 2`, and `2 / z` is **not** `z / 2`. |
| `+= -= *= /=` (both versions) | Modify `*this`, return `*this` by reference. **`z *= z` must give z²** (careful if you update `realPart` before computing `imaginaryPart`). |
| `==` / `!=` with `ComplexNumber` | Both parts equal. |
| `==` / `!=` with `double` | Real part equals the number **and** the imaginary part is 0. |

Binary operators must not change their operands (they are `const`).

## Part B - basic `ComplexStack` (25%)

A LIFO stack of `ComplexNumber` backed by a **dynamic array** that grows when full
(`new ComplexNumber[n]` / `delete[]` is the easiest. That's why the constructor has default arguments).

| Function | Behaviour |
|---|---|
| `ComplexStack()` | Empty stack. |
| `~ComplexStack()` | Frees the array. |
| `bool isEmpty() const`, `int getCount() const` | Obvious. |
| `void push(const ComplexNumber&)` | Pushes a **copy** of the number. Grows the array when full. |
| `ComplexNumber pop()` | Removes and returns the top. `std::underflow_error` when empty. |
| `ComplexNumber peek() const` | Returns the top without removing it. `std::underflow_error` when empty. |
| `ComplexNumber sum() const` | Sum of all elements (`0+0i` for an empty stack). Doesn't change the stack. |

## Part C - copy semantics (25%)

| Function | Behaviour |
|---|---|
| `ComplexStack(const ComplexStack&)` | Deep copy. |
| `ComplexStack& operator=(const ComplexStack&)` | Deep copy into an existing stack. Bigger source, smaller source, empty source, **self-assignment**, chaining. No leaks. |

## Part D - `ComplexStack` operators (25%)

| Expression | Result |
|---|---|
| `a + b` | **New** stack: `b` is placed **on top of** `a`, keeping `b`'s order (so `b`'s top is the result's top). `a`, `b` unchanged. |
| `a += b` | Same, but modifies `a`; returns `*this`. **`s += s` must double the stack.** Think about what happens to a reference into your array when `push` reallocates it. |
| `s * x`, `x * s` (`double x`) | New stack with every element multiplied by `x`. |
| `s *= x` | Multiplies every element in place; returns `*this`. |
| `a == b` / `a != b` | Same count, and equal elements at every position. |

## Checklist before you hand in

- [ ] Every function that doesn't modify the object is `const`
- [ ] No `throwNotImplemented` calls left
- [ ] `./build.sh` → `All tests passed`, no ASan output
