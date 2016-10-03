#include "global.h"
#include "uart.h"
#include <string.h>

char* name = "ARIEL";

int parse_message(char* message);
int parse_motor(char* message, int i);
int parse_pwm(char* message, int i);
int parse_dir(char* message, int i);
int parse_steps(char* message, int i);
int parse_rate(char* message, int i);
char* concat(char *s1, char *s2);

/*Motor Mode:
00 = 0x00 0x30 =  FULL SWING
01 = 0x00 0x31 =  HALF SWING
02 = 0x00 0x32 =  STEPPER
03 = 0x00 0x33 =  SERVER

PWM:
11 = 0x31 0x31 = 1 PWM
12 = 0x31 0x32 = 2 PWM
13 = 0x31 0x33 = 3 PWM
14 = 0x31 0x34  = 4 PWM

Dir:
20 = 0x32 0x00 = BACK
21 = 0x32 0x01 = FORWARD

NUM (For the Stepper):
0-65536 = 0xxx...0xFFFF = Steps  

RATE:
41 = 0x34 0x31 = 1
42 = 0x34 0x32 = 2
43 = 0x34 0x33 = 3
44 = 0x34 0x34 = 4

Example message recieved with opcodes: ~ARIEL*00*11*21*0*41* */

int parse_message(char* message){
    int i = 0;
    char m = message[i];

    if(m!='~'){         //checks the starting delimiter  
        USART_putstring("FAIL");
        return -1;
    }

    i++;
    while(message[i]!='*'){ 
        m = message[i];
        if(name[i-1]!= m){
            _delay_ms(100);
            return -1;
        }
        i++;
    }   
    i++;    //passes the * names delimeter

    if(parse_motor(message,i)==0){
        char* success = "Successfully updated ";
        concat(success,name);
        USART_putstring(success);
    }
    
    return 0;
}

int parse_motor(char* message, int i){
    
    char op_code[2];
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    i++;
  
    if(strcmp(op_code,"00")==0){
        //FULL SWING           
    }
    else if(strcmp(op_code,"01")==0){
        //HALF SWING        
    }
    else if(strcmp(op_code,"02")==0){
        //STEPPER        
    }
    else if(strcmp(op_code,"03")==0){
        //SERVER       
    }    
    else{
        USART_putstring("Fail to parse Motor");
        return -1;
    }

    return parse_pwm(message, i);         
}

int parse_pwm(char* message, int i){
    
    char op_code[2];
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    i++;
  
    if(strcmp(op_code,"11")==0){
        //1 PWM
    }
    else if(strcmp(op_code,"12")==0){
        //2 PWM
    }
    else if(strcmp(op_code,"13")==0){
        //3 PWM
    }
    else if(strcmp(op_code,"14")==0){
        //4 PWM
    }    
    else{
        USART_putstring("Fail to parse PWM");
        return -1;
    }

    return parse_dir(message, i);            
}

int parse_dir(char* message, int i){
    
    char op_code[2];
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    i++;
  
    if(strcmp(op_code,"20")==0){
        //BACK
    }
    else if(strcmp(op_code,"21")==0){
        //FORWARD
    }
    else{
        USART_putstring("Fail to parse direction");
        return -1;
    }

    return parse_steps(message, i);          
}

int parse_steps(char* message, int i){
    
    char op_code[5];
    int num_steps = 0;
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    i++;
    
    j = 0;

    for(j=0; j<6; i++){
        num_steps = num_steps * 10 + ( op_code[i] - '0' );
    }

    if(num_steps<0||num_steps>65536){
        USART_putstring("Fail to parse Steps");
        return -1;
    }

    return parse_rate(message, i);   
}

int parse_rate(char* message, int i){
    
    char op_code[2];
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    i++;
  
    if(strcmp(op_code,"41")==0){
        //RATE 1
    }
    else if(strcmp(op_code,"42")==0){
        //RATE 2
    }
    else if(strcmp(op_code,"43")==0){
        //RATE 3
    }
    else if(strcmp(op_code,"44")==0){
        //RATE 4
    }    
    else{
        USART_putstring("Fail to parse rate");
        return -1;
    }

    return 0;       
}

char* concat(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *result = malloc(len1+len2+1);//+1 for the zero-terminator    
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator
    return result;
}


