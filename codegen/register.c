#include <string.h>
#include "register.h"


Register R_fp = NULL;
Register R_sp = NULL;
Register R_result = NULL;
Register R_return = NULL;
Register R_acc = NULL;
Register R_accSP = NULL;
Register R_zero = NULL;
Register R_tmp1 = NULL;
Register R_tmp2 = NULL;
Register R_tmp3 = NULL;




Register FP(void) {
  if (R_fp == NULL) {
    R_fp = (char *) malloc(sizeof(char)*4);
    strcpy(R_fp,"$fp");
  } 
  return R_fp;
}


Register SP(void){
  if (R_sp == NULL) {
    R_sp = (char *) malloc(sizeof(char)*4);
    strcpy(R_sp,"$sp");
  }
  return R_sp;
}


Register Zero(void) {
  if (R_zero == NULL) {
    R_zero = (char *) malloc(sizeof(char)*6);
    strcpy(R_zero,"$zero");
  } 
  return R_zero;
}


Register Result(void) {
  if (R_result == NULL) {
    R_result = (char *) malloc(sizeof(char)*4);
    strcpy(R_result,"$v0");
  } 
  return R_result;
  
}

Register Acc(void){
  if (R_acc == NULL) {
    R_acc = (char *) malloc(sizeof(char)*4);
    strcpy(R_acc,"$t0");
  } 
  return R_acc;
}

Register ReturnAddr(void){
  if (R_return == NULL) {
    R_return = (char *) malloc(sizeof(char)*4);
    strcpy(R_return,"$ra");
  } 
  return R_return;
}

Register Tmp1(void){
  if (R_tmp1 == NULL) {
    R_tmp1 = (char *) malloc(sizeof(char)*4);
    strcpy(R_tmp1,"$t1");
  } 
  return R_tmp1;
}
Register Tmp2(void) {
  if (R_tmp2 == NULL) {
    R_tmp2 = (char *) malloc(sizeof(char)*4);
    strcpy(R_tmp2,"$t2");
  }
  return R_tmp2;
}
Register Tmp3(void) {
  if (R_tmp3 == NULL) {
    R_tmp3 = (char *) malloc(sizeof(char)*4);
    strcpy(R_tmp3,"$t3");
  }
  return R_tmp3;
}

Register AccSP(void) {
  if (R_accSP == NULL) {
    R_accSP = (Register) malloc(sizeof(*R_accSP));
    R_accSP = (char *) malloc(sizeof(char)*4);
    strcpy(R_accSP,"$t4");
  }
  return R_accSP;
}

   
