# Get Next Line

## Overview

The **Get Next Line** project aims to implement a function `get_next_line()` that reads a file line by line. This function is a crucial tool for handling file inputs efficiently, especially for programs that need to process text files incrementally.

## Features

- Reads a single line from a file descriptor (fd) at a time.
- Handles multiple file descriptors simultaneously.
- Efficiently manages memory and handles large files.
- Compatible with any buffer size defined by `BUFFER_SIZE`.

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters:

- `fd`: The file descriptor to read from.

### Return Value:

- The next line read from the file descriptor, including the newline character (`\n`) if one exists.
- `NULL` if there are no more lines to read or an error occurs.

## Implementation Details

- **Static Variables**: Used to store remaining data from previous reads for each file descriptor.
- **Buffer Management**: Reads chunks of data from the file descriptor using a buffer of size `BUFFER_SIZE`.
- **Dynamic Memory Allocation**: Ensures the function can handle lines of any length.
- **Error Handling**: Manages cases such as invalid file descriptors, memory allocation failures, or read errors.

## Requirements

- Implement the function in a single `.c` file.
- Ensure your code adheres to the coding style and guidelines of your project (e.g., Norminette for 42 projects).
- Do not use standard library functions like `malloc()` unless explicitly allowed.

## Usage

1. **Include the Header File**: Ensure `get_next_line.h` is included in your project.

2. **Compile with **``: Define `BUFFER_SIZE` during compilation. For example:

   ```bash
   gcc -D BUFFER_SIZE=32 -o get_next_line get_next_line.c
   ```

3. **Link the Function**: Integrate `get_next_line()` into your project to read files line by line.

### Example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file");
        return (1);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

## Testing

- Test with files of various sizes and contents.
- Ensure compatibility with edge cases:
  - Empty files.
  - Files without newline characters.
  - Files with very long lines.
  - Multiple file descriptors.

## Common Issues

- **Memory Leaks**: Always free dynamically allocated memory.
- **Buffer Size Dependency**: Ensure the function works for any `BUFFER_SIZE`.
- **Static Variables**: Properly handle them to avoid data corruption between file descriptors.

