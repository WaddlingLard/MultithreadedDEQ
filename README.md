# Project: MultithreadedDEQ

* Author: Brian Wu
* Class: CS452 Section #002
* Semester: Spring 2025

## Overview

A multithreaded deq with several thread safe operations.

## Reflection

This was a pleasantly simple homework, but it taught me how multithreading works and how to implement functions that are thread-safe, ensuring you can slap all sorts of power and get efficient results. Understanding the importance of multithreading really shows how fast tasks can be accomplished if you just put in some work to actually implement thread safe operations.

## Compiling and Using

To compile the code, first cd into the `hw4` directory.
Then, run this command 

```make```

and then...

```./wam```

Just make sure the file structure is not disturbed and all should be good!

Note: If you run into issues with the building and the shared object is 'missing' run ``` export LD_LIBRARY_PATH=/path/to/libs:$LD_LIBRARY_PATH ```

## Results 

Here is the mtq in operation, as you can see there are plenty of operations that are happening concurrently.
![multithreaded queue in operation](/mtqoperation.png);

## Valgrind
- brian@SLEEK:/mnt/c/Users/Datha/OneDrive/Desktop/CodingFolder/CS-452/HW4/MultithreadedDEQ/hw4$ valgrind ./wam
- ==33418== Memcheck, a memory error detector
- ==33418== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
- ==33418== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
- ==33418== Command: ./wam
- ==33418== 
- ==33418== 
- ==33418== HEAP SUMMARY:
- ==33418==     in use at exit: 718,487 bytes in 1,087 blocks
- ==33418==   total heap usage: 13,681 allocs, 12,594 frees, 2,719,104 bytes allocated
- ==33418== 
- ==33418== LEAK SUMMARY:
- ==33418==    definitely lost: 0 bytes in 0 blocks
- ==33418==    indirectly lost: 0 bytes in 0 blocks
- ==33418==      possibly lost: 0 bytes in 0 blocks
- ==33418==    still reachable: 718,487 bytes in 1,087 blocks
- ==33418==         suppressed: 0 bytes in 0 blocks
- ==33418== Rerun with --leak-check=full to see details of leaked memory
- ==33418== 
- ==33418== For lists of detected and suppressed errors, rerun with: -s
- ==33418== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

## Sources used

None
----------

## Notes

* This README template is using Markdown. Here is some help on using Markdown: 
[markdown cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)


* Markdown can be edited and viewed natively in most IDEs such as Eclipse and VS Code. Just toggle
between the Markdown source and preview tabs.

* To preview your README.md output online, you can copy your file contents to a Markdown editor/previewer
such as [https://stackedit.io/editor](https://stackedit.io/editor).
