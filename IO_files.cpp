#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string>
#include <string.h>
#include "Supporting_functions.h"
#include "IO_files.h"

/*=======================================================================================================================*/
int actualLength(const char* string) {
    //  return the actual lenght of a string (trailling spaces are not counted)
    while (isspace((unsigned char)string[0]))
        string++;
    char* final = (char*)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(final, string);
    int length = strlen(final);
    while (length > 0 && isspace((unsigned char)final[length - 1]))
        length--;
    final[length - 1] = '\0';
    return (strlen(final) + 1);
}
/*====================================================================================================================*/
char* readline(int lineNumber, const char* txtFile) {
    /* return a string of a complete line #lineNumber in the file #txtFile
    with actual length (no spaces character at the end) */
    char* buf = (char*)malloc(50 * sizeof(char));
    int count = 1;
    FILE* fileName;
    fileName = fopen(txtFile, "r");//open file #txtFile
    while (fgets(buf, 50, fileName) != NULL) {
        //get the wanted line by fgets all lines respectively from line #1 to lie #lineNumber
        if (count == lineNumber) {
            break;
        }
        else {
            count++;
        }
    }

    char* line = (char*)malloc(actualLength(buf) * sizeof(char));
    strcpy(line, buf);
    //so this make 'line' contains a whole line with minimum size
    free(buf);
    fclose(fileName);
    strtok(line, "\n");
    return line;
    // delete line;
}
/*===================================================================================================================*/
int* getpos(int line, const char* filename) {
    //return the ordinate (int x and int y) which has the form [x;y] in a specific line
    static int pos[2] = { NULL,NULL };
    int j;
    char* buf = (char*)malloc((strlen(readline(line, filename)) + 1) * sizeof(char));

    strcpy(buf, readline(line, filename));
    for (j = strlen(buf); j > 0; j--) {
        // find the ';' character in a line then before ';' is x and after ';' is y 
        if (buf[j] == ';') {
            pos[0] = buf[j - 1] - '0';
            pos[1] = buf[j + 1] - '0';
            break;
        }
    }
    free(buf);
    return pos;
}
/*===================================================================================================================*/
int count(const char* obj) {
    // return number of object (driver or customer) in the input text file
    FILE* fp;
    int count = 0;
    char c;
    fp = fopen(obj, "r");

    if (fp == NULL) {
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '=')
            // increment count if this character is '=' 
            //(because I separate the object in text file by '=') 
            count = count + 1;
    }
    fclose(fp);
    return count;
}
/*====================================================================================================================*/
customer* constructC(int num, customer* c) {
    //construct all the customer c[i]
    int i;
    for (i = 0; i < num; i++) {
        // in this session, the term k+5*i is the information in the 
        //line number #linenum congruence with k modulo 5
        //each driver's or customer's information store in 5 lines
        // so all #linenum in the same congruence group containing the same field
        // example for customer: names are in line {1,6,11}, phones are in line {2,7,12}, etc..
        c[i].name = readline((1 + 5 * i), "customer_data.txt");
        c[i].phone = readline((2 + 5 * i), "customer_data.txt");
        c[i].cip[0] = *getpos((3 + 5 * i), "customer_data.txt");
        c[i].cip[1] = *(getpos((3 + 5 * i), "customer_data.txt") + 1);
        c[i].cfp[0] = *getpos((4 + 5 * i), "customer_data.txt");
        c[i].cfp[1] = *(getpos((4 + 5 * i), "customer_data.txt") + 1);
    }
    return c;
}
/*==================================================================================================================*/
driver* constructD(int num, driver* d) {
    //construct all the driver d[i]
    int i;
    for (i = 0; i < num; i++) {
        d[i].name = readline((1 + 5 * i), "driver_data.txt");
        d[i].phone = readline((2 + 5 * i), "driver_data.txt");
        d[i].numberPlt = readline((3 + 5 * i), "driver_data.txt");
        d[i].dp[0] = *getpos((4 + 5 * i), "driver_data.txt");
        d[i].dp[1] = *(getpos((4 + 5 * i), "driver_data.txt") + 1);
    }
    return d;
}
/*====================================================================================================================*/
void getCusCip(int** CusCipMat, customer* c, int numOfCus) {
    //put customers's initial position to CusCipMat which is allocated in main function
    for (int i = 0; i < numOfCus; i++) {
        CusCipMat[i][0] = c[i].cip[0];
        CusCipMat[i][1] = c[i].cip[1];
    }
}
void getCusCfp(int** cusCipMat, customer* c, int numOfCus) {
    //put customers's final position to CusCfpMat which is allocated in main function
    for (int i = 0; i < numOfCus; i++) {
        cusCipMat[i][0] = c[i].cfp[0];
        cusCipMat[i][1] = c[i].cfp[1];
    }
}
void getDrvDp(int** DrvDpMat, driver* d, int numOfDrv) {
    //put drivers's present position to DrvDpMat which is allocated in main function
    for (int i = 0; i < numOfDrv; i++) {
        DrvDpMat[i][0] = d[i].dp[0];
        DrvDpMat[i][1] = d[i].dp[1];
    }
}
/*===========================================================================================*/
//update information part
void updateDrvData(int numOfDrv, customer* c, driver* d, int** result_2) {
    FILE* fp;
    char* buf;
    int i;
    fp = fopen("driver_data.txt", "w+");
    for (i = 0; i < numOfDrv; i++) {
        buf = (char*)malloc(500 * sizeof(char));
        sprintf(buf, "%s\n%s\n%s\nposition [%d;%d]\n=\n", d[i].name, d[i].phone, d[i].numberPlt, c[result_2[i][1]].cfp[0], c[result_2[i][1]].cfp[1]);
        fputs(buf, fp);
        free(buf);
    }
    fclose(fp);
}
void updateCusData(int numOfcus, customer* c) {
    FILE* fp;
    char* buf;
    int i;
    fp = fopen("customer_data.txt", "w+");
    for (i = 0; i < numOfcus; ++i) {
        buf = (char*)malloc(500 * sizeof(char));
        sprintf(buf, "%s%sDeparting point: [%d;%d]\nArriving point: [%d;%d]\n=\n", c[i].name, c[i].phone, c[i].cip[0], c[i].cip[1], c[i].cfp[0], c[i].cfp[1]);
        fputs(buf, fp);
        free(buf);
    }
    fclose(fp);
}
/*===============================================================================================*/
billForCus* constructBill(int num, billForCus* bill, int** timeCashMat, customer* c, driver* d) {
    int i;
    for (i = 0; i < num; i++) {
        int cus = timeCashMat[i][1];
        //
        bill[i].cusName = c[cus].name;
        bill[i].phone = d[i].phone;
        bill[i].drvName = d[i].name;
        bill[i].pltNum = d[i].numberPlt;
        bill[i].cash = timeCashMat[i][4];
        bill[i].time1 = timeCashMat[i][2];
        bill[i].time2 = timeCashMat[i][3];
    }
    return bill;
}
void printBill(int numOfBill, billForCus* bill) {
    FILE* fp;
    char* buf;
    char* filename;
    int i;
    for (i = 0; i < numOfBill; i++) {
        filename = (char*)malloc((strlen(bill[i].cusName) + 7) * sizeof(char));
        buf = (char*)malloc(500 * sizeof(char));
        sprintf(filename, "%s.txt", bill[i].cusName);
        fp = fopen(filename, "w+");
        sprintf(buf, "/==========Your Bills==========/\n\
Your driver information:\n\
Name: %s\n\
Phone number: %s\t plate number: [%s]\n\n\
>Estimate departure time: %d minutes\n\
>Estimate arrival time: %d minutes\n\
>>Please prepare total cash: %d,000 VND\n\
******THANKS FOR USING OUR SERVICE******", bill[i].drvName, bill[i].phone, bill[i].pltNum, bill[i].time1, bill[i].time2, bill[i].cash);
        fputs(buf, fp);
        free(buf);
        free(filename);
        fclose(fp);
    }
}