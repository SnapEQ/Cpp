# Mock test 2 - Singly linked list

**Time limit:** 90 minutes. No internet.

## Files

| File | What it is | Edit it? |
|---|---|---|
| `LinkedList.h` | Class declaration | Only the `private:` section |
| `LinkedList.cpp` | Stubs - every function throws "not implemented" | **Yes, this is your work** |
| `TestLinkedList.cpp` | Test cases | No |
| `build.sh` | Builds with AddressSanitizer and runs the tests | No |

```bash
./build.sh
```

**You pass when** the last line says `All tests passed - mock test PASSED` **and** AddressSanitizer
reports nothing (an ASan report = a memory bug = fail, even if every check printed PASS).

## Task

Implement a **singly linked list of `int`**. Every element lives in its own heap-allocated `Node`
(`new`/`delete`, or `malloc`/`free`). The header keeps a `head` **and** a `tail` pointer, so
`pushBack` is O(1). Keeping `tail` correct is the hard part.

### Part A - basic list (30%)

| Function | Behaviour |
|---|---|
| `LinkedList()` | Empty list. |
| `~LinkedList()` | Frees **every** node. |
| `bool isEmpty() const` | `true` if there are no elements. |
| `int getCount() const` | Number of elements. |
| `void pushFront(int)` / `void pushBack(int)` | Adds an element at the front / back. |
| `int popFront()` / `int popBack()` | Removes and returns the front / back element. Throw `std::underflow_error` when empty. |
| `int getFront() const` / `int getBack() const` | Returns the front / back element without removing it. Throw `std::underflow_error` when empty. |

### Part B - copy semantics (35%)

| Function | Behaviour |
|---|---|
| `LinkedList(const LinkedList& other)` | **Deep** copy: new nodes, same values, same order. Changing either list afterwards must not affect the other. |
| `LinkedList& operator=(const LinkedList& other)` | Deep copy into an existing list. Must handle: longer source, shorter source, empty source, **self-assignment**, chaining (`a = b = c`). The old nodes of the target must be freed. |

### Part C - operators (35%)

| Expression | Result |
|---|---|
| `a + b` | **New** list: `a`'s elements then `b`'s. `a`, `b` unchanged. |
| `l + x` (`int x`) | New list with `x` appended at the back. |
| `x + l` (`int x`) | New list with `x` at the front. *(free function)* |
| `a += b` | Appends **copies** of `b`'s elements to `a`. Returns `*this`. **`l += l` must double the list (and must terminate!).** |
| `l += x` | Same as `pushBack(x)`. Returns `*this`. |
| `l -= x` | Removes **every** occurrence of `x`. Returns `*this`. Removing nothing is fine. |
| `l - x` | New list with every `x` removed. `l` unchanged. |
| `a == b` | Same count and same values in the same order. |
| `a != b` | Opposite of `==`. |

## Checklist before you hand in

- [ ] `tail` is correct after **every** operation: pop to empty, pop to one element, `-=` removing the last node, copy, assignment
- [ ] No `throwNotImplemented` calls left
- [ ] `./build.sh` → `All tests passed`, no ASan output
