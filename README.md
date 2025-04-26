# DBMS

A simple **Database Management System** built from scratch in C++.  
This project simulates core concepts found in real DBMS engines, including **file storage**, **buffer management**, and **indexing using B+ Trees**.

## Features

- **Page Management**: Data is stored in fixed-size pages.
- **Buffer Pool with Clock Replacement**: Pages are cached in memory and evicted using the Clock algorithm when space is needed.
- **File Storage**: Persistent disk storage for pages and tuples.
- **Tuple Abstraction**: Data is organized as rows (tuples) inside pages.
- **B+ Tree Indexing**: Efficient search and insert operations using a B+ Tree structure.
- **Minimal Design**: Focused on clarity and modularity over completeness.

## Data Flow

1. **Client** requests to insert/search data.
2. **Storage Layer** determines which page holds the data.
3. **BufferPool** loads the page into memory if it's not already cached.
4. **Page** structure manages the actual tuple inside memory.
5. If BufferPool is full, uses **Clock Algorithm** to evict pages.
6. **Disk Files** are the permanent backup for all pages.
7. **B+ Tree** helps in quickly locating the required page for a given key.

## Requirements

- C++17
- CMake
- Basic understanding of operating systems and database internals is a plus!

## How to Build and Run

```bash
mkdir build
cd build
cmake ..
make
./DBMS
