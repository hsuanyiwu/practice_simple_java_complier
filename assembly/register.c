#include <string.h>
#include "register.h"


Register R_fp = NULL;
Register R_sp = NULL;
Register R_result = NULL;
Register R_acc = NULL;
Register R_return = NULL;
Register R_tmp1 = NULL;
Register R_tmp2 = NULL;
Register R_tmp3 = NULL;




Register FP(void) {
  if (R_fp == NULL) {
    R_fp = (char *) malloc(sizeof(char)*3);
    strcpy(R_fp,"FP");
  } 
  return R_fp;
}
Register SP(void){
  if (R_sp == NULL) {
    R_sp = (char *) malloc(sizeof(char)*3);
    strcpy(R_sp,"SP");
  }
  return R_sp;
}
Register Result(void) {
  if (R_result == NULL) {
    R_result = (char *) malloc(sizeof(char)*7);
    strcpy(R_result,"RESULT");
  } 
  return R_result;
  
}

Register Acc(void){
  if (R_acc == NULL) {
    R_acc = (char *) malloc(sizeof(char)*4);
    strcpy(R_acc,"ACC");
  } 
  return R_acc;
}

Register ReturnAddr(void){
  if (R_return == NULL) {
    R_return = (char *) malloc(sizeof(char)*7);
    strcpy(R_return,"RETURN");
  } 
  return R_return;
}

Register Tmp1(void){
  if (R_tmp1 == NULL) {
    R_tmp1 = (char *) malloc(sizeof(char)*5);
    strcpy(R_tmp1,"TMP1");
  } 
  return R_tmp1;
}
Register Tmp2(void) {
  if (R_tmp2 == NULL) {
    R_tmp2 = (char *) malloc(sizeof(char)*5);
    strcpy(R_tmp2,"TMP2");
  }
  return R_tmp2;
}
Register Tmp3(void) {
  if (R_tmp3 == NULL) {
    R_tmp3 = (char *) malloc(sizeof(char)*5);
    strcpy(R_tmp3,"TMP3");
  }
  return R_tmp3;
}
