
Required Files to run:
    CustomLinkedList.c
    CustomLinkedList.h
    wordsearch.c
Compile Commands:
    gcc .\wordsearch.c .\CustomLinkedList.c -o test1
            ^^              ^^                  ^    
        Must Compile Both Scripts               |
     (Tells Compiler To Link Files)             |
                                                |
                                Applicable For windows use to pipe output
                                I am Unaware if this works for mac or linux

Run with args:
    .\test1.exe puzzle3.txt
        ^^          ^
    run exe         |
                WithOverflow args
                Works with any txt file with thats the same format
                as given in assignment directions.


Computer will promt User and Run attempts

