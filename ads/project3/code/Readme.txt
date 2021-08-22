--code
----data
------test0
--------data.in
--------ans.out
--------Readme.txt
------test1
------test2
------test3
------test4
------test5
------test6
----source
------1.py
------2.py
------3.py
----Readme.txt
----1.exe
----2.exe
----3.exe
----run.bat

To generate an executable file from a python script file,you should install pyinstaller 

1.py,2.py,3.py in the folder source are script files of programs with time complexity of O(N^2), O(N*M) and O(N*logN) respectively.

1.exe 2.exe 3.exe are executable files of programs with time complexity of O(N^2), O(N*M) and O(N*logN) respectively.

To execute our program, you need to create a 'data.in' file in the folder where the three executable files and bat files are located. The bat file will run the three executable files in sequence and output the answers into the 'ans.out' file.