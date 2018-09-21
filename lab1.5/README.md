### Instructions

Create a script to find all Linux kernel related .c and .h source code files. Below you can see the requirements.

* Identify those paths where Linux kernel source code is located
* Generate a script that searchs for .c and .h files in those Linux Kernel source directories.
* Once files are found, categorize files on their first and second level directories. Also, separate them in .c and .h files on each category.
* That categorization data will be saved in a plain text called "linux_source_structure.txt"
* Below is an example of the final output file.

*Upload your code to your github repository os-labs and place it in a new directory called lab1.5, don't forget to include the README.md file with details about the lab.

```
/first/path/to/linux/source/code
- .c source code files
    - sample1.c
    - sample2.c
 - .h header files
    - header1.c
    - header2.c
- Second level directories
- /second_level_directory_1/
 - .c source code files
        - sublib1.c
 - .h header files
        - subhead.c 

/second/linux/source/code/dir
.
.
.
```

### Compile and run

`chmod +x script_lab`

`./script_lab`

