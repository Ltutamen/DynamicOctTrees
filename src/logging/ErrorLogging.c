//
// Created by axiom on 5/22/19.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <time.h>
#include "ErrorLogging.h"

FILE *ef;

void initLogging(char* filepath){
    ef = fopen(filepath, "rt+");
    fprintf(ef, "%ld ; Logging initialization\n", time(NULL));

}


void enshureInfoMsg(char* infoLine){
    fprintf(ef, "%ld : %s", time(NULL), infoLine);
}


void enshureErrorMsg(char* errorLine){
    fprintf(ef, "%ld ERROR: %s", time(NULL), errorLine);
}