# Password-Hashtable

To Compile the Program run the command
make

- Test Insert Password:                 
``checkpass <password>``
- Generate Passwords:                   
``checkpass -g password.txt <count> <seed>``
- Test Insert Password with hash size: 
``checkpass -h <count> <password>``
- Test Collisions with hash size:      
``checkpass -t 1000 password.txt``

To run the autotester type the command
``sh autotester.sh``
The test output will appear in the log file
