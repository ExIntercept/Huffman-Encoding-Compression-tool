# Huffman Encoding Compression tool in C

This project implements a lossless text compression and decompression tool using the Huffman coding algorithm in C. The program reads input text, compresses it using Huffman encoding based on character frequencies, and can decode the compressed data back to the original text.

## Features

- Constructs a Huffman tree using a min-heap for frequency sorting
- Encodes input strings to binary strings representing compressed data
- Decodes binary strings back to original text using the Huffman tree
- Handles ASCII characters (0-127)
- Simple command-line interface

## How It Works

1. **Frequency Counting:** Counts the occurrences of each ASCII character in the input.
2. **Min-Heap Construction:** Builds a min-heap of nodes ordered by character frequency.
3. **Huffman Tree Building:** Combines nodes with smallest frequencies iteratively into a binary tree.
4. **Encoding:** Generates binary codes by traversing the tree; more frequent characters get shorter codes.
5. **Decoding:** Reads the encoded binary string and walks the Huffman tree to reconstruct the original message.

## Usage

1. Compile the program:

   ```bash
   gcc -o huffman huffman.c
