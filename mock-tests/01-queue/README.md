# Mock test 1 - Queue

**Time limit:** 90 minutes. No internet.

## Files

| File | What it is | Edit it? |
|---|---|---|
| `Queue.h` | Class declaration | Only the `private:` section |
| `Queue.cpp` | Stubs - every function throws "not implemented" | **Yes, this is your work** |
| `TestQueue.cpp` | Test cases | No |
| `build.sh` | Builds with AddressSanitizer and runs the tests | No |

```bash
./build.sh
```

**You pass when** the last line says `All tests passed - mock test PASSED` **and** AddressSanitizer
reports nothing (an ASan report = a memory bug = fail, even if every check printed PASS).

## Task

Implement a **FIFO queue of `int`** backed by a **dynamically allocated array** (`malloc`/`realloc`/`free`
or `new[]`/`delete[]`, your choice). A linked list is not allowed here.

### Part A - basic queue (30%)

| Function | Behaviour |
|---|---|
| `Queue()` | Empty queue. Allocates the initial array (any capacity >= 1). Throws `std::bad_alloc` if allocation fails. |
| `~Queue()` | Frees the memory. |
| `bool isEmpty() const` | `true` if there are no elements. |
| `int getCount() const` | Number of stored elements. |
| `void enqueue(int)` | Adds an element at the back. When the array is full it **grows** (e.g. doubles). Stored elements and their order must survive the resize. |
| `int dequeue()` | Removes and returns the **oldest** element. Throws `std::underflow_error` when empty. |
| `int peek() const` | Returns the oldest element without removing it. Throws `std::underflow_error` when empty. |

> Hint: a queue that does `enqueue` + `dequeue` 1000 times while never holding more than 4
> elements should **not** need to keep growing. Think about what `head` is for.

### Part B - copy semantics (35%)

| Function | Behaviour |
|---|---|
| `Queue(const Queue& other)` | **Deep** copy. Changing either queue afterwards must not affect the other. |
| `Queue& operator=(const Queue& other)` | Deep copy into an existing queue. Must handle: source bigger than target, source smaller than target, empty source, **self-assignment** (`q = q`), and chaining (`a = b = c` - return `*this`). No memory leaks: free what you replace. |

### Part C - operators (35%)

| Expression | Result |
|---|---|
| `a + b` | **New** queue: elements of `a` (front to back) followed by elements of `b`. `a` and `b` unchanged. |
| `q + x` (`int x`) | New queue: `q`'s elements, then `x` at the back. |
| `x + q` (`int x`) | New queue: `x` at the front, then `q`'s elements. *(free function - why can't it be a member?)* |
| `a += b` | Appends `b`'s elements to `a`. Returns `*this`. **`q += q` must double the queue.** |
| `q += x` | Same as `enqueue(x)`. Returns `*this`. |
| `a == b` | `true` if both hold the same elements in the same order. Capacity and internal positions don't matter. |
| `a != b` | Opposite of `==`. |

## Checklist before you hand in

- [ ] Every function that doesn't modify the object is `const`
- [ ] No `throwNotImplemented` calls left
- [ ] `./build.sh` → `All tests passed`, no ASan output
