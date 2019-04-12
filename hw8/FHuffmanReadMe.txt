{\rtf1\ansi\ansicpg1252\cocoartf1671\cocoasubrtf400
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww8900\viewh11420\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 The updated fast Huffman tree:\
\
We were not able to get a functional code or even an agreed upon pseudocode; however, we are now sure of what we must accomplish with the implementation. We worked on this concept for hours, even though our work might not reflect that to the greatest extent. Dylan also attempted to help us in lab but was unsure of how to go about helping us. Here is what we wanted to do: \
\
The Huffman code that we implement is very slow, even though it is correct. The problem with Huffman stems from the fact that each time we get a new letter and are forced to change the frequency, we have to update and change the entire tree to reflect the change of one frequency. Our first concept that we toyed around with was encoding a Huffman tree only when we got a character, meaning not initializing the entire tree to 256+EOF empty characters. However, a problem arises with the decoder, because the tree did not exist\'85. \
\
So we then settled on the side of swapping children. We created getter and setter functions within the FHTree class so that we would be able to get the parent of a node. \
\
We included scratch work file that shows some pseudocode that we created and ideas of trees that we tried to manipulate and get to work. We wanted the interior nodes to reflect the largest value below it and then to somehow only swap the children not entire trees. We thought of recursive solutions, but any solutions that we could agree upon were not faster than the solution of Huffman that we were required to implement for homework. \
\
We tried extensively for hours, it was hard because we ended up almost attempting to design a re max-heapify algorithm to get the code to work. However, Dylan said that was ineffective. }