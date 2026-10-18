# MP3 Tag Reader and Editor in C

## Project Description

The MP3 Tag Reader and Editor is a C project that reads, displays, and modifies ID3 metadata stored in MP3 files.

ID3 tags store information such as song title, artist, album, year, genre, and comments.

## Features

- Read and display MP3 ID3 tag information.
- Edit the title of an MP3 file.
- Edit the artist and album information.
- Modify the year, track, comment, and genre tags where supported.
- Validate command-line arguments.
- Display help and version information where implemented.

## Technologies Used

- C Programming
- File Handling
- Structures
- Command-Line Arguments
- ID3v2 Metadata

## Installation

Download or clone this repository to your computer.

Make sure GCC is installed before compiling the project.

## How to Compile and Run

Compile the source files using GCC. 

    gcc main.c view.c edit.c -o mp3tag

### View MP3 Tags

    ./mp3tag -v song.mp3

### Edit the Year

    ./mp3tag -e -y 2026 song.mp3

### Edit the Title

    ./mp3tag -e -t "Pavan Kumar" song.mp3

Refer to `doc.txt` for more sample commands and output.

## Project Structure

- `main.c` - Main program and command-line argument handling.
- `view.c` - Reads and displays MP3 tag information.
- `view.h` - Declarations for viewing functions.
- `edit.c` - Modifies MP3 tag information.
- `edit.h` - Declarations for editing functions.
- `types.h` - Shared type definitions.
- `doc.txt` - Project documentation, sample inputs, outputs, and error handling.

## Learning Outcomes

- Understanding MP3 ID3 metadata.
- Reading and modifying file data using C.
- Working with command-line arguments.
- Using structures and file handling.
- Implementing validation and error handling.

## Author

K. Pavan Kumar
