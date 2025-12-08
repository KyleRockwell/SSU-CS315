## Student Information
Name: Kyle Rockwell
ID: 008657669

## Collaboration and sources
    cplusplus.com
        - ifstream
        - ostream
        - std::io
        - and several more
       cppreference.com 
## implementation Detals
    currently the program runs on input sizes of 4096 and 65536 with both single and double probing
    the program outputs a .csv file into the csvs/ folder with the headers and data in the format as expected
    as well as outputting two .csv files in the histograms/ folder for each table size respectively
    
    I have not implemented a trace generator. 
## Testing and Status
    I tested the program a few times running through each table size with 7 trials each, sigle and double probing
    each with and without compaction. As expected this took a long time, and most of it worked fine.
    however with no compaction at the largest table size I ran into what seemed to me like an infinite loop
    with two days of running on my computer which has a decent CPU, there was absolutely no output on that large table size
    I am unsure as to what the actual bug is since it seems like the smaller table sizes worked fine, so scaling to larger
    number seems like it would just work. There is a possibility the computations were just that much that my computer 
    didn't see any change within that timespan and the program was actually running as expected, but more testing would
    need to be done to be sure. 

## How to compile and run my solution
    to compile my code you can just type "make" in the project directory
    
    if you want to compile and run it, you can type "make run" 
    
    
