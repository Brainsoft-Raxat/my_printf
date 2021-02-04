#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

void swap(char* s, int i1, int i2){
  char temp = s[i1];
  s[i1] = s[i2];
  s[i2] = temp;
}

void reverse(char* s){
  int l = strlen(s);
  for(int i=0; i < l/2; i++){
    swap(s, i, l-i-1);
  }
}

char* converter(int value, char* result, int base){
  int rem, i=0;
  _Bool negative = 0;
  
  if(value == 0){
    result[i++]='0';
    result[i]='\0';
  }
  else if(value<0){
    negative = 1;
    value = -value;
  }
  
  for(; value>0; i++){
    rem = value%base;
    if(rem>9){
      result[i] = 'a' + rem - 10;
    } 
    else{
      result[i] = '0' + rem;
    }
    value=value/base;
  }
  if(negative){
    result[i++]='-';
  }
  result[i] = '\0';
  reverse(result);
  return result;
}

char* converter_u(unsigned int value, char* result, int base){
    int rem, i=0;
  
  _Bool negative = 0;
  
  if(value == 0){
    result[i++]='0';
    result[i]='\0';
  }
  else if(value<0){
    negative = 1;
    value = -value;
  }
  
  for(; value>0; i++){
    rem = value%base;
    if(rem>9){
      result[i] = 'a' + rem - 10;
    } 
    else{
      result[i] = '0' + rem;
    }
    value=value/base;
  }
  if(negative){
    result[i++]='-';
  }
  result[i] = '\0';
  reverse(result);
  return result;
}

char* converter_lu(unsigned long value, char* result, int base){
    int rem, i=0;
  
  _Bool negative = 0;
  
  if(value == 0){
    result[i++]='0';
    result[i]='\0';
  }
  else if(value<0){
    negative = 1;
    value = -value;
  }
  
  for(; value>0; i++){
    rem = value%base;
    if(rem>9){
      result[i] = 'a' + rem - 10;
    } 
    else{
      result[i] = '0' + rem;
    }
    value=value/base;
  }
  if(negative){
    result[i++]='-';
  }
  result[i] = '\0';
  reverse(result);
  return result;
}

int my_printf(char* restrict format, ...){
    va_list argptr;
    va_start(argptr, format);
    int total = 0;
    int i = 0;
    while(*(format + i) != '\0'){
        if(*(format + i) == '%'){
            i++;
            char buffer[100];
            int dec;
            void* p;
            switch(*(format + i)){
                case 'd':{
                    dec = va_arg(argptr, int);
                    converter(dec, buffer, 10);
                    total+=write(1, buffer, strlen(buffer));
                    i++;
                    break;
                    }
                case 'o':{
                    dec = va_arg(argptr, unsigned int);
                    converter_u(dec, buffer, 8);
                    total+=write(1, buffer, strlen(buffer));
                    i++;
                    break;
                    }
                case 'u':{
                    dec = va_arg(argptr, unsigned int);
                    converter_u(dec, buffer, 10);
                    total+=write(1, buffer, strlen(buffer));
                    i++;
                    break;
                    }
                case 'x':{
                    dec = va_arg(argptr, unsigned int);
                    converter_u(dec, buffer, 16);
                    total+=write(1, buffer, strlen(buffer));
                    i++;
                    break;
                    }
                case 's':{
                    //total+=my_printf(va_arg(argptr, char*));
                    char* s = va_arg(argptr, char*);
                    total+=write(1, s, strlen(s));
                    i++;
                    break;
                }
                case 'c':{
                    char c = (char)va_arg(argptr, int);
                    write(1, &c, 1);
                    total++;
                    i++;
                    break;
                }
                case 'p':{
                    p = va_arg(argptr, void*);
                    unsigned long lp = (unsigned long)p;
                    converter_lu(lp, buffer, 16);
                    total+=write(1, "0x", 2);
                    total+=write(1, buffer, strlen(buffer));
                    i++;
                    break;
                }
                default:{
                    i++;
                    break;
                }
                                
            }
        } else {
            write(1,(format + i),1);

            total++;
            i++;
        }
        
    }
    return total;
}

int main(){ 
    unsigned int a = -1234;
    int l1 = my_printf("Hello %d %o %u %x %s %c %p %p %x\n", -1234, -1234, -1234, -1234, "cool%d", 'h', printf, main, a);
    int l2 = printf("Hello %d %o %u %x %s %c %p %p %x\n", -1234, -1234, -1234, -1234, "cool%d", 'h', printf, main, a);

    printf("%d %d\n", l1, l2);
    return 0;
}