//
//  main.c
//  oth2
//
//  Created by Aurora on 2018/9/6.
//  Copyright © 2018年 Aurora. All rights reserved.
//
#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */



int matches_leading(char *partial_line, char *pattern) {
    // Implement if desire
    //
    if (*partial_line != '\0') {
        if (*pattern != '\0') {
            // backslash
            if (*pattern == '\\' && *(pattern-1) != '\\') {
                //Back slash will skip a spot in pattern如果第二个\前面还有一个\，第二个\会被略过
                pattern++;
                return matches_leading(partial_line,pattern);
            }
            // ?
            if (*(pattern+1) == '?' && *(pattern-1) != '\\') {
                if(*pattern == '.'){
                    if (*(partial_line) == *(pattern+2)){
                        if(*(pattern+2) == *(partial_line+1)){
                            pattern++;
                            partial_line++;
                        }
                        else{
                            pattern++;
                            pattern++;
                        }
                    }
                else{
                        pattern++;
                        pattern++;
                        partial_line++;
                    }
                
                    //Check if code reaches the end of hthe sentence, where character is '0'
                    if(matches_leading(partial_line,pattern))//if
                        return 1;
                    else
                        return 0;
                }
            
                if (*pattern == '.'){//如果两个if都满足呢？
                    if( matches_leading(partial_line,pattern+2)) // if the current letter fits in如果和+2位相同的话，即？前省略.代表的字符
                        return 1;
                    if( matches_leading(partial_line+1,pattern+2))// or if the next letter fits in j即？前没省略.
                        return 1;
                    else
                        return 0;
                }
                if (*pattern == *(pattern+2)){ //If hi?h?hi, then it will be equivalent to hhi, hihhi, etc.这个是不是应该删掉
                    pattern+=2;
                    return matches_leading(partial_line,pattern);
                }
                if (*pattern == *partial_line){
                    return matches_leading(partial_line+1,pattern+2);
                }
            }
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
                int i = 0;
                int j = 1;
                if (*pattern == '.'){
                    while(*(pattern+2) != *partial_line) {//每次都加到头，再从不一样的地方开始接着比较
                        partial_line++;
                    }
                    partial_line--;
                    pattern++;
                    pattern++;
                    while(*pattern == *partial_line){
                        pattern++;
                    }
                    pattern--;
                    if(*partial_line == '\0'){
                            return 0;
                    }
                    return matches_leading(partial_line,pattern);
                }
                while (partial_line[i] == *pattern) { //While the partial lin
                    i++;
                }
                while (j <= i) {
                    j++;
                    if (pattern+j == NULL)
                        return matches_leading(partial_line+i,pattern+j);
                    if(pattern[j] != *pattern)
                        break;
                }
                return matches_leading(partial_line+i,pattern+j);
            }
            
            // CHARACTER MATCH
            if (*pattern == *partial_line) {
                return matches_leading(partial_line+1,pattern+1); //increment both pattern and partial line if they have the same character, ie they match
            }
            // .
            if (*pattern == '.' && *(pattern-1) != '\\') {
                return matches_leading(partial_line+1,pattern+1); //go on to the next two
            }
            // NO MATCH NO SPECIAL CHARACTER
            else {
                return 0;
            }
        }
        return 1;
    }
    return 0;
    
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
        if (matches_leading(line+k, pattern))
            return 1;
        k++;
    }
    
    if (*pattern == '\0')
        return 1;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }
    
    /* we're not going to worry about long lines */
    char buf[MAXSIZE];
    
    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }
    
    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }
    
    return 0;
}


