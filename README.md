# LibraX — Intelligent Digital Library & Recommendation Engine

> An algorithm-driven digital library prototype built in C++ to demonstrate efficient document searching, recommendations, citation graph exploration, and reading optimization.

## Overview

**LibraX** is a command-line digital library system that applies fundamental Design and Analysis of Algorithms (DAA) techniques to organize, search, analyze, and explore a collection of documents.

The project combines multiple algorithms—including sorting, searching, string matching, graph traversal, greedy algorithms, and dynamic programming—to demonstrate how algorithmic concepts can solve practical problems in a digital library environment.

## Problem Statement

Traditional document collections can make it difficult to efficiently locate documents, discover related content, explore citation relationships, and organize reading activities.

LibraX addresses these challenges through a modular C++ system that integrates multiple algorithmic techniques for document management and exploration.

## Features

- **Document Catalog:** Load and display a collection of documents.
- **Binary Search:** Search for documents using their unique IDs.
- **Merge Sort:** Sort documents alphabetically by title.
- **Naive String Matching:** Search for text patterns using direct character comparisons.
- **Rabin–Karp:** Search text using hash-based pattern matching.
- **Knuth–Morris–Pratt (KMP):** Efficient pattern matching using the LPS array.
- **Jaccard Similarity:** Recommend documents based on keyword overlap.
- **BFS & DFS:** Explore document citation relationships.
- **0/1 Knapsack:** Optimize document selection within a reading-time constraint.
- **Activity Selection:** Select compatible, non-overlapping activities.
- **Longest Common Subsequence (LCS):** Compare text sequences using Dynamic Programming.
- **Kruskal's Algorithm:** Demonstrate Minimum Spanning Tree construction in a weighted graph.

## Algorithms & DAA Concepts

| Algorithm | DAA Concept | Application |
|---|---|---|
| Merge Sort | Divide and Conquer | Sort documents by title |
| Binary Search | Searching | Find documents by ID |
| Naive String Matching | String Matching | Search document text |
| Rabin–Karp | Hashing | Pattern matching |
| KMP | String Matching | Efficient pattern search |
| Jaccard Similarity | Set-based similarity | Document recommendations |
| BFS | Graph Traversal | Explore citation relationships |
| DFS | Graph Traversal | Explore citation relationships |
| 0/1 Knapsack | Dynamic Programming | Reading selection |
| Activity Selection | Greedy Algorithm | Activity scheduling |
| LCS | Dynamic Programming | Compare text sequences |
| Kruskal | Greedy Algorithm | Minimum Spanning Tree |

## System Architecture

The system follows a modular structure:

```text
CSV Dataset
    ↓
CSV Reader & Validation
    ↓
Document Data Model
    ↓
Algorithm Modules
    ↓
Command-Line Interface
    ↓
Results & Recommendations
```

## Technology Stack

- **Language:** C++
- **Standard:** C++17
- **Data Storage:** CSV
- **Algorithms:** Sorting, Searching, String Matching, Graph Algorithms, Greedy Algorithms, Dynamic Programming
- **Build:** g++

## Project Structure

```text
LibraX/
├── data/
│   └── documents.csv
├── include/
│   ├── algorithms/
│   ├── models/
│   └── utils/
├── src/
│   ├── algorithms/
│   ├── utils/
│   └── main.cpp
├── tests/
├── benchmarks/
├── docs/
└── README.md
```

## Getting Started

### Prerequisites

- C++ compiler supporting C++17
- g++ recommended
- Git

### Clone the Repository

```bash
git clone <YOUR_REPOSITORY_URL>
cd LibraX
```

### Compile

Compile the project by including the main source file, utility implementations, and algorithm source files.

Example:

```bash
g++ -std=c++17 src/main.cpp src/utils/CSVReader.cpp src/algorithms/*.cpp -Iinclude -o LibraX
```

> Adjust the compilation command if your project source files are organized differently.

### Run

On Linux/macOS:

```bash
./LibraX
```

On Windows:

```bash
LibraX.exe
```

## Dataset

LibraX uses a CSV dataset containing document information such as:

- Document ID
- Title
- Author
- Publication year
- Keywords
- Content
- Reading time
- Citation relationships

The CSV reader parses and validates the dataset before the documents are processed by the application.

## Limitations

- The application currently operates through a command-line interface.
- Recommendations are based on keyword overlap rather than semantic understanding.
- The system depends on the structure and quality of the CSV dataset.
- The project is an algorithm-focused prototype rather than a production digital library platform.

## Future Scope

- Develop a graphical user interface or web interface.
- Integrate semantic search using NLP techniques.
- Implement more advanced recommendation methods.
- Add database integration.
- Expand performance benchmarking on larger datasets.
- Visualize citation networks.

## Academic Context

This project was developed as an individual Project-Based Learning (PBL) project focused on applying Design and Analysis of Algorithms concepts to a practical software system.

---

**LibraX — Explore. Search. Connect. Optimize.**
