## Burrows-Wheeler Transform (BWT) and Pattern Matching

This C++ program implements the Burrows-Wheeler Transform (BWT) on a given input string and allows pattern matching against the transformed string. The program takes command-line arguments for text and an optional pattern and produces the BWT-transformed string or the number of occurrences of the pattern in the transformed string.

### Usage

To run the program, use the following command in the terminal:

```
./bwt_transform <text> [pattern]
```

- `<text>`: The input text to perform the Burrows-Wheeler Transform on.
- `[pattern]`: (Optional) The pattern to search for in the transformed string. If not provided, the program will output the transformed string.

### Example

1. Transform the input text "banana":
   ```
   ./bwt_transform panamabananas
   Output: (u003)smnpbnnaaaaa(u002)a
   ```

2. Search for the pattern "ana" in the transformed string "annb$aa":
   ```
   ./bwt_transform panamabananas ana
   Output: 3
   ```

### Note

- The transformed string is enclosed in special markers (ASCII 2 and ASCII 3) during the transformation process. These markers are not part of the original input text.
