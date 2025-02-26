# CS300
What was the problem you were solving in the projects for this course?
ABCU wanted the ability to import a CSV file contating couse information. This includes course number, course name, and prerequisites. After importing the CSV, they wanted the ability to view all courses in alphanumeric order and search for specific courses.

How did you approach the problem? Consider why data structures are important to understand.
There where a couple of things to consider. What functions are going to be used most often and what is the size of their data. The provided material only had 8 courses and I didn't see it growing to a very large size. Becuase of this, I decided to use a vector. Binary Search Trees will process large sets of data faster, but I thought the code for a vector would be better for review/changes/added functions/etc.
Using a vector is very easy to code, and the purpose of this exercise was to demonstrate our understanding of data structures and algorithms, so, so even though I chose an vector for easy and clean coding, I came up with an insertion algorithm that works similar to a binary search, but finds the right location to insert the data to keep the vector sorted.

How did you overcome any roadblocks you encountered while going through the activities or project?
I really enjoyed the logic needed for this class, so I wanted to build something using my own logic instead of copying code out of the book, using previous exercises, or too many existing libraries/functions. That being said, I did need to reference stackoverflow and cppreference a couple of times to understand why my code wasn't working. The biggest issue I had was trying to convert the course number, ie MATH200, into a number for sorting. STOI and ATOI weren't working and I decided to convert each character to ASCII. Stepping through this made me realize the value needed to be a double instead of an integer and it solved everything.

How has your work on this project expanded your approach to designing software and developing programs?
I'm considering, and actually understanding, how to make them faster. I essentially had the caveman thinking of "use less lines of code", but understanding how big O scales and the algorithms to minimize that scale is where the real time is saved.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
One of the things I never thought of was recursive functions. It still takes me a little to process how they work/how to write one, but I really enjoyed the cleaverness of them. My job has an "in house" programming language (along with C# and Python), and I started asking more senior devs if we've ever created a recursive program using the in house language. The need for it has come up once and it wasn't possible back then, but if I ever find the need for it, I'm going to try to make it work.
