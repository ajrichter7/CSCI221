Huffman Encoding
by Nicole Niesen and Alex Richter

DESIGN:
We designed the Huffman class with a constructor that initializes the frequencies of every ASCII character to 0 and the EOF to 1, then creates a forest with 257 trees that it then merges into one Huffman tree and sets that tree as a starting point for decoding.

When encoding a symbol Huffman finds a path to the node representing that symbol as the key and converts that path to a vector of 1's and 0's. Then the frequency of that character is increased and the Huffman tree is updated to reflect the new frequency. The path boolean to the symbol (the encoding) is then returned.

The decode function takes the corresponding child of the current node (initially the root of the Huffman tree) and sets the child to the current node. If the key of that node is negative, then that node is not a leaf and therefore does not represent an ASCII character or EOF. In that case, when decode is called again it will start at that internal node and check its children and so on. If the node has a nonnegative key, then it is a leaf, and we have decoded a character, so we update the frequency of that symbol, create a new Huffman tree that we set as the new starting point for decoding, and return the key of the leaf node decoded.

The BitIO class's constructor initializes a char buffer of zeros, an initial position set to 7, and a flag needed in the input_bit function so long as either an input stream or and output stream is given and not both.

The output_bit function takes bits and puts them in the buffer (using a mask)until it is full (marked by the position variable), then the buffer is outputed to the output stream. If an uneven (not a multiple of 8) number of bits is passed through the function before the object goes out of scope, the destructor will pass the buffer through to the ostream, with trailing zeros in the unfilled spots.

The input_bit function will get a byte from the istream if it is the first time it is called (marked with the flag) or when the current byte has been totally read. This function returns a single bit of the byte at a time (using a mask).

To encode a file, we first check the file given to encode, then create an output file that will be written to. Then, by reading one character at a time we encode that character using Huffman, then use the output_bit function on each bit in the encoded vector to write bytes to the output file. Finally we encode the EOF character once there are no more characters in the input file.

The decoder will check the file given to decode and create a new file output of the decompressed text. When opening the input file we read the bytes not converted into characters, and run input_bit for every bit in the input file, passing those bits through the huffman decoder as we read them. When the Huffman decoder returns a positive value, that is a character that we convert from the bytes and send to the output file. Finally, when we reach the EOF file, the output file will be the decompressed input file, so we close the files and return.


COMPRESSION TESTS:

    file name      raw file size   compressed size  decompressed match
    													raw file?
+----------------+---------------+-----------------+-------------------+
| nickelback.txt |  3015 bytes   |   2277 bytes    |         Yes       |
+----------------+---------------+-----------------+-------------------+
| trumanshow.txt | 136153 bytes  |   84440 bytes   |         Yes       |
+----------------+---------------+-----------------+-------------------+
|    haiku.txt   |  3516 bytes   |   2794 bytes    |         Yes       |
+----------------+---------------+-----------------+-------------------+
| act3scene1.txt |  9411 bytes   |   6739 bytes    |         Yes       |
+----------------+---------------+-----------------+-------------------+
|   mmmbop.txt   |  2704 bytes   |   2106 bytes    |         Yes       |
+----------------+---------------+-----------------+-------------------+
