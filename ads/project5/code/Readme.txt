
code
|--1.exe
|--2.exe
|--run.bat
|--Readme.txt
|--data
|--|--random.cpp
|--|--random.exe
|--|--test0
|--|--|--data.in
|--|--|--ans.out
|--|--|--Readme.txt
|--|--|
|--|--test1
|--|--test2
|--|--test3
|--|--test4
|--|--test5
|--|--test6
|--|--test7
|--|--test_correction0
|--|--test_correction1
|--|--test_correction2
|--|
|--source
|--|--1.py
|--|--2.py
|--|--3.py



To generate an executable file from a python script file,you should install pyinstaller.
Our Python script files import the `matplotlib` , if you want to run our python file directly, you need to install it using command `pip install matplotlib` in advance.
We recommend that you use run.bat and executable files to run our program.

`1.py` and `2.py` in the folder `source` are script files of programs with time complexity of O(N*logN) and O(N^2) respectively.

`1.exe` and `2.exe` are executable files of programs with time complexity of O(N*logN) and O(N^2) respectively.

To execute our program, you need to create a `data.in` file in the folder where the two executable files and bat files are located. The bat file will run the two executable files in sequence and output the answers into the 'ans.out' file.

`Random.cpp` is the program to generate those testing folders. After running the `random.exe`, these folders will be created with a `data.in` file in them which is a testing file generated randomly.

We have get the answers and results of all the testing files. `ans.out` file will carry the time and ans of two programs, while `result1.png` and `result2.png` are the pictures the programs draw.
Notice that, when N is large, the pictures can not be drawn successfully.