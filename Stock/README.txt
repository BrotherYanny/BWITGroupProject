TASK: STOCK FUNCTION
NAME: Iulia Corici

A little help in understanding what I have done:

-> to compile the task, you only need to run "make" in the terminal;
(this way all the files will be compiled using the build rule from the Makefile)
-> to clear the object and executables files, please run "make clean" in the terminal.

-> in order to test any method from the STOCK task, you will need these guidelines:

    - for "addBasicSecurityInfo(securityID, industry, description, listOfBoardMemebers)"
        just type "addInfo" and the fields for the parameters will be nicely displayed
        Here is an example: 

        COMMAND: addInfo
        INSERT securityID = 1
        INSERT industry = economy
        INSERT description = general economy
        INSERT (with commas) the board members' list = Alex Petrescu,Ana Barbieru,Gica Petrescu

-------------------------------------------------------------------------------------------------
    - for "addTick(securityID, price, timestamp)"
        just type "addTick" and the fields for the parameters will be nicely displayed
        Here is an example: 

        COMMAND: addTick
        INSERT securityID = 1
        INSERT timestamp = 34
        INSERT price = 12
---------------------------------------------------------------------------------------------------
    - for "allTimeHigh(securityID)"
        just type "highest" and the fields for the parameters will be nicely displayed
        Here is an example: 

        COMMAND: highest
        INSERT securityID = 1
        95
---------------------------------------------------------------------------------------------------
    - for "allTimeLow(securityID)"
        just type "lowest" and the fields for the parameters will be nicely displayed
        Here is an example: 

        COMMAND: lowest
        INSERT securityID = 1
        12
---------------------------------------------------------------------------------------------------
    - for "getAllPriceHistory(securityID, startTime, endTime)"
        just type "history" and the fields for the parameters will be nicely displayed
        Here is an example:

        COMMAND: history
        INSERT securityID = 1
        INSERT startTime = 3
        INSERT endTime = 678

        SECURITY DETAILS
        ID: 1
        INDUSTRY: economy
        DESCRIPTION: general economy
        BOARD MEMBERS:
                Alex Petrescu
                Ana Barbieru
                Gica Petrescu

        Stock prices between these timestamps: 3.000000 and 678.000000:
        TIME: 31 with STOCK PRICE: 98
        TIME: 34 with STOCK PRICE: 12
        TIME: 67 with STOCK PRICE: 2

--------------------------------------------------------------------------------------------------------