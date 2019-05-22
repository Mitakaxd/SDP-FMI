# SDP-FMI
Projects for Data Structures and Algorithms course at FMI

#Inverted Index
Definition

An index data structure that maps content to 1 or more documents. The purpose is to optimize time needed for search queries at the cost of more time needed to process the documents.
For every word in all of the documents we will save a list of all the documents that contain it so the problem "Which documents contain the word X?" is reduced to searching among the much smaller and indexed set of used words rather than the entire text.
Problem
Implement a rudimentary inverted index, that can answer simple queries.

# Trie
Definition
Deterministic Finite State Automata (DFSA) usually used to store dictionaries. The name Trie (pronounced like "try") is short for retrieval.
The main selling point is recognizing if a given word is part of the dictionary by simply checking if the automata accepts it in O(m) time, m being the length of the word, regardless of the size of the entire dicitonary.


# Unrolled linked list
In computer programming, an unrolled linked list is a variation on the linked list which stores multiple elements in each node. It can dramatically increase cache performance, while decreasing the memory overhead associated with storing list metadata such as references. It is related to the B-tree. 

# Double-ended queue
Not to be confused with Double-ended priority queue.
In computer science, a double-ended queue (abbreviated to deque) is an abstract data type that generalizes a queue, for which elements can be added to or removed from either the front (head) or back (tail). It is also often called a head-tail linked list, though properly this refers to a specific data structure implementation of a deque.
