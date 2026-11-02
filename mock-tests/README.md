# Mock tests

Three practice exams covering the material from `stack-implementation*` and `cmplx-num`:
dynamic memory, destructor, copy constructor, `operator=`, exceptions, `const` members,
pass-by-value vs. pass-by-reference, and operator overloading (member and free `double op X` forms).

| Folder | Topic | Time |
|---|---|---|
| [`01-queue`](01-queue/README.md) | FIFO queue on a dynamic array | 90 min |
| [`02-linked-list`](02-linked-list/README.md) | Singly linked list with head + tail | 90 min |
| [`03-stack`](03-stack/README.md) | `ComplexNumber` + a stack of complex numbers | 120 min |

## How each one works

1. Read the folder's `README.md`. It's the task description.
2. The `.cpp` next to the header is the unfinished program. Every function throws
   `"... is not implemented"`, so the tests compile and run from minute one.
3. Run `./build.sh` as often as you like. It builds with **AddressSanitizer**, so shallow copies,
   double frees and use-after-free crash with a report instead of silently "working".
4. You pass when the output ends with `All tests passed - mock test PASSED` and ASan printed nothing.

Don't edit the `Test*.cpp` files or the public part of the headers.
