#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
/*
   Notice all the samples are use for function logic, not exactly the grammar
*/

/*
    function: myStrlen
    @description: Calculate the length of the string
    @input: const string s
    @output: the length of the string
    @sample input: "abcde\0abcde"
    @sample output: 5
    @Notice:  Function myStrlen() show check whether the input array is NULL.
    If so, you show return 0. Note that strlen() in string.h does not check NULL arrays.
*/
unsigned int myStrlen(const char s[]);

/*
    function: myStrcpy
    @description: copy one string to another
    @input: const string source
    @output: string destination
    @sample input: "a" "abc"
    @sample output: "abc"
    @Notice: You can not assign the array directly which will cause a runtime error.
*/
char * myStrcpy(char destination[], const char source[]);

/*
    function: myStrcat
    @input: const string source
    @output: string destination
    @sample input: "abcde" "abc"
    @sample output: "abcdeabc"
    @Notice: You can not assign the array directly which will cause a runtime error.
*/
char * myStrcat(char destination[], const char source[]);

/*
    function: myStrcmp
    @input: const string1 and const string2
    @output: if string1 is euqal to string2, output 0
             if string1 is greater than string2 ouput an integer > 0
             if string2 is greater than string1 output an integer < 0
    @sample input: "abc" "abc"
    @sample output: 0
*/
int myStrcmp(const char str1[], const char str2[]);

/*
    function: Mystrfind
    @input: cosnt string1 and const string2
    @output: if str2 is a substring of str1, output the first index in str1
             otherwise, ouput -1 which indicates can not find
    @sample input: "abcde" "cde"
    @sample output: 2
*/
int MyStrfind(const char str1[], const char str2[]);

/*
    function: LeftRotateString
    @input: string buff, an integer n which indicates the first n
    @output: put the first n chars to the end of the string
    @sample input: "abcdefg" 4
    @sample output: "efgabcd"
*/
void LeftRotateString(char *buff, int n);

/*
    function: myParseInt
    @input: a const string
    @output: an integer parse from a string
    @sample input: "123"
    @sample output: 123
    @Notice: You should notice show extreme conditions such as:
   1 null array input: the input is an array, the program will crash in the access to the null array,
       so you need to judge whether the array is null before using the array.
   2 The sign: integer not only contain numbers, and may is the positive integer expressed
       starts with a '+' or '-', so if the first character is' - ',
       to get the integer value is converted to a negative integer.
   3 illegal characters: the input string may contain characters that are not numbers.
     Therefore, whenever you encounter these illegal characters, the program should stop converting.
   4 integer overflow: the number of input is the string of the form of input,
      so the input of a very long string will likely lead to overflow. You should set the return
      value to MAX_INT or MIN_INT in the situation.
*/
int myParseInt(const char str[]);

/*
    function: myStrcontain
    @input: const string1 and const string2
    @output: a boolean value. id all chars in str2 are in str1, output true
             else output flase
    @sample input1: "ABCD" "BAD"
    @sample output1: 1
    @sample input2: "ABCD" "BCE"
    @sample output2: 0
*/
int myStrcontain(const char str1[], const char str2[]);

#endif // STRING_H_INCLUDED
