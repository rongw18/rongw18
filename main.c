//
//  main.c
//  oth2
//
//  Created by Aurora on 2018/9/6.
//  Copyright © 2018年 Aurora. All rights reserved.
//
#include <stdio.h>
#include <string.h>
/**
 * Parses pattern for next character and sets
 * necessary parameters that are referenced inside/outside
 * of this function.
 *
 * Add any additional inputs to function signature if necessary.
 */
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */



int matches_leading(char *partial_line, char *pattern, char *ori) {
    if (*partial_line != '\0') {
        if (*pattern != '\0') {
            // backslash
            if (*pattern == '\\' && *(pattern-1) != '\\') {
                //Back slash will skip a spot in pattern如果第二个\前面还有一个\，第二个\会被略过
                pattern++;
                return matches_leading(partial_line,pattern, ori);
            }  // \ends
            // ?
            if (*(pattern+1) == '?' && *(pattern-1) != '\\') {
                if(*pattern == '.'){
                    if (*(partial_line) == *(pattern+2)){
                        if(*(pattern+2) == *(partial_line+1)){ //youdianwenti
                            pattern++;
                            pattern++;
                            partial_line++;
                            return matches_leading(partial_line,pattern,ori);
                        }
                        else{   //meiwenti
                            pattern++;
                            pattern++;
                            return matches_leading(partial_line,pattern,ori);
                        }
                    }
                    else{    // *(partial_line) != *(pattern+2) //youwenti
                        pattern++;
                        pattern++;
                        partial_line++;
                        return matches_leading(partial_line,pattern,ori);
                    }
                }
                else{   //?qianmianmeiyou.
                    if(*pattern != *partial_line){
                        pattern++;
                        pattern++;
                        return matches_leading(partial_line,pattern,ori);
                    }
                    else{
                        pattern++;
                        partial_line++;
                        return matches_leading(partial_line,pattern,ori);
                    }
                    }
                    //Check if code reaches the end of hthe sentence, where character is '0'
                while(matches_leading(partial_line,pattern,ori)){//if
                    return 1;
                }
                while(!matches_leading(partial_line,pattern,ori)){
                    return 0;
                }
            }  //? ends
        
              /*  if (*pattern == '.'){//如果两个if都满足呢？
                    if( matches_leading(partial_line,pattern+2)) // if the current letter fits in如果和+2位相同的话，即？前省略.代表的字符
                        return 1;
                    if( matches_leading(partial_line+1,pattern+2))// or if the next letter fits in j即？前没省略.
                        return 1;
                    else
                        return 0;
                } */
            
            
            // +
            /*
             if (*pattern == '+'){
             char prev = *(pattern - 1);
             if (prev == '.'){
             if(*(pattern + 1) == '\0'){
             return 1;
             }
             return matches_leading(partial_line+1, pattern) || matches_leading(partial_line, pattern+2);
             }
             
             return matches_leading(partial_line + 1, pattern) || matches_leading(partial_line+1, pattern+1);
             
             }
             */
            
            if (*(pattern+1) == '+' && *(pattern-1) != '\\') { //The character before this index will appear one or more times in a row
                if (*pattern == '.'){
                     if(*partial_line== *(partial_line+1)){
                         char temp=*partial_line;
                         while(*partial_line ==*(partial_line+1)){
                             partial_line++;
                         }
                         pattern++;
                         pattern++;
                         while(*pattern == temp){
                             pattern++;
                         }
                          return matches_leading(partial_line,pattern,ori);
                     }
                     else{
                         pattern++;
                         pattern++;
                         partial_line++;
                         return matches_leading(partial_line,pattern,ori);
                     }
                 }
                else{  // actually they are the same
                    if(*partial_line== *(partial_line+1)){
                        char tempp=*partial_line;
                        while(*partial_line ==*(partial_line+1)){
                            partial_line++;
                        }
                        pattern++;
                        pattern++;
                        while(*pattern == tempp){
                            pattern++;
                        }
                        return matches_leading(partial_line,pattern,ori);
                    }
                    else{
                        pattern++;
                        pattern++;
                        partial_line++;
                        return matches_leading(partial_line,pattern,ori);
                    }
                }
            }
                     
      
            // CHARACTER MATCH
            if (*pattern == *partial_line) {
                return matches_leading(partial_line+1,pattern+1,ori); //increment both pattern and partial line if they have the same character, ie they match
            }
            // .
            if (*pattern == '.' && *(pattern-1) != '\\') {
                return matches_leading(partial_line+1,pattern+1,ori); //go on to the next two
            }
            // NO MATCH NO SPECIAL CHARACTER
            else {
                *pattern = *ori;
                 return matches_leading(partial_line+1,pattern,ori);
            }
             return 1;
        }
        else{
        return 1;
        }
    }
    else if(*partial_line == '\0' && *pattern == '\0'){
    return 1;
    }
    else return 0;
    
}

/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
    
    //
    // Implement me
    //
    if ((*pattern == '.') && (*(pattern+1) =='+') && (*(pattern+2) == '\0'))
        return 1;
    int k = 0;
    while (line[k] != '\0') {
        if (matches_leading(line+k, pattern,pattern))
            return 1;
        k++;
    }
    
    if (*pattern == '\0')
        return 1;
    return 0;
}



int main() {
    char a[100],b[100];
    printf("Enter string you want to search:\n");
    gets(a);
    printf("THEN enter the pattern you search for:\n");
    gets(b);
    switch (rgrep_matches(a, b)) {
        case 0:
            printf("No such a pattern\n");
            break;
        case 1:
            printf("Yes! We got it!\n");
            break;
            
        default:
            break;
    }
    return 0;
}
