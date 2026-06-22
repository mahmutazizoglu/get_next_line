*This project has been created as part of the 42 curriculum by <maazizog>.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor. The goal of the project is to understand file descriptors, static variables, dynamic memory allocation, and buffered reading while following the 42 Norm. The function must return the current line, including the newline character when present, and return `NULL` when there is nothing left to read or when an error occurs.

This project is useful because it introduces a reusable low-level function for reading text streams incrementally instead of loading a whole file into memory at once.

## Instructions

### Files
The mandatory part includes:
- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### Compilation

Compile with a chosen buffer size using `-D BUFFER_SIZE=n`.

Example:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

The project must also compile when `BUFFER_SIZE` is not explicitly provided, using a default value defined in the header.

### Usage

A simple example:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

### Notes
- The function reads from a file descriptor, not only from regular files.
- The returned string must be freed after each call.
- The behavior is undefined for binary files, according to the subject.
- The project must handle different buffer sizes correctly.

## Algorithm

The implementation is based on a static storage area, often called `stash` or `saved`, which keeps unread data between function calls.

### Step-by-step logic

1. A buffer is allocated with size `BUFFER_SIZE + 1`.
2. The function reads from the file descriptor into the buffer until either:
   - a newline character is found in the stored data, or
   - the end of file is reached.
3. Each new chunk is appended to the static storage.
4. Once enough data is available, the function extracts the next line from the storage.
5. After the line is returned, the remaining part after the newline is saved for the next call.
6. If there is no remaining content, the storage is cleared.

### Why this algorithm was chosen

This algorithm is appropriate because:
- it reads only as much as necessary,
- it preserves unread data between calls,
- it works for files, standard input, and other readable file descriptors,
- it avoids reading the full file at once,
- it fits the project requirement of returning one line per call.

The static variable is the key design choice because each call to `get_next_line` must continue where the previous one stopped.

## Technical choices

- A static pointer is used to store leftover data between calls.
- Helper functions are used to keep the code modular, for example:
  - finding a newline,
  - joining strings,
  - extracting the current line,
  - saving the remainder.
- Dynamic memory allocation is used for the buffer, returned line, and updated storage.
- Memory is freed carefully to avoid leaks.

## Resources

The following resources were useful for understanding the project:
- 42 subject PDF
- `read(2)` manual page
- `open(2)` manual page
- documentation about static variables in C
- documentation about file descriptors and dynamic memory allocation

Useful commands:
```bash
man 2 read
man 2 open
```

## AI usage

AI was used as a learning support tool to:
- clarify the project requirements,
- explain the behavior of `read`,
- discuss bugs and edge cases,
- help understand how to split the project into smaller helper functions,
- review README structure and documentation requirements.

AI was not used as a substitute for testing, debugging, or understanding the final implementation. All final code choices, structure decisions, and validations were reviewed manually.

## Possible tests

Examples of important tests:
- file with multiple lines
- file with one line only
- file ending without `\n`
- empty file
- very small `BUFFER_SIZE`, such as `1`
- very large `BUFFER_SIZE`
- reading from standard input
- invalid file descriptor