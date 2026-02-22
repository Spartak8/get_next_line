*This project has been created as part of the 42 curriculum by skhachat.*

# get_next_line

## Description

**get_next_line** is a C function that reads a file descriptor line by line. Each call to the function returns the next line from the file, including the terminating `\n` character (except at the end of the file if no `\n` is present). When there is nothing left to read or an error occurs, the function returns `NULL`.

The goal of this project is to understand and implement:
- Static variables in C
- Memory management (malloc/free)
- File I/O with the `read()` system call
- Buffer management across multiple function calls

The bonus part extends the function to handle multiple file descriptors simultaneously.

---

## Instructions

### Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Main function |
| `get_next_line_utils.c` | Helper functions |
| `get_next_line.h` | Header file |
| `get_next_line_bonus.c` | Bonus — multiple fd support |
| `get_next_line_utils_bonus.c` | Bonus helper functions |
| `get_next_line_bonus.h` | Bonus header file |

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

You can change `BUFFER_SIZE` to any value:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o gnl
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c -o gnl
```

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char  *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Check for memory leaks

```bash
valgrind --leak-check=full ./gnl
```

---

## Algorithm

The function works in three steps on each call:

**1. Fill the remainder**

A `static` variable called `remainder` persists between calls. It stores any data that was read but not yet returned. On each call, we read from the file descriptor in chunks of `BUFFER_SIZE` bytes using `read()`, appending each chunk to `remainder` via `ft_strjoin`, until we find a `\n` character or reach the end of the file.

```
remainder = ""
read() → "Hello"    → remainder = "Hello"
read() → "\nWorld"  → remainder = "Hello\nWorld"
'\n' found → stop reading
```

**2. Extract the line**

Once `\n` is found (or EOF is reached), we extract everything from the start of `remainder` up to and including `\n` using `ft_substr`. This is the string returned to the caller.

```
remainder = "Hello\nWorld"
line      = "Hello\n"       ← returned to caller
```

**3. Update remainder**

Everything after the `\n` is saved back into `remainder` for the next call, so we don't lose data that was already read.

```
remainder = "World"  ← saved for next call
```

**Why this algorithm?**

This approach reads as little as possible — we stop as soon as we find `\n`. The `static` variable is the key: it bridges calls, so data read in one call but not yet needed is not lost. The `BUFFER_SIZE` can be any value (1, 42, 9999...) because the loop handles accumulation regardless of chunk size.

---

## Resources

- [read() man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static variables in C — GeeksForGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Memory management in C — Valgrind docs](https://valgrind.org/docs/manual/quick-start.html)

### AI Usage

Claude (Anthropic) was used throughout this project in the following ways:
- **Concept explanation** — understanding static variables, buffer management, and the role of each helper function
- **Code review** — checking for memory leaks, norminette compliance, and edge cases
- **Debugging guidance** — identifying issues such as uninitialized variables, missing NULL checks, and incorrect casts
- **README writing** — structuring and writing this document

All code was written by the student; AI was used as a learning and review tool, not to generate final solutions.
