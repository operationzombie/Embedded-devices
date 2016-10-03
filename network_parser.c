#include "global.h"
#include "uart.h"
#include "network_parser.h"
#include <string.h>

char* name = "BELLE";

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

Example message recieved with opcodes: ~BELLE*02*13*21*44* ~BELLE*03*12*20*32*42* */


int parse_message(char* message){
    int i = 0;
    char m = message[i];

    if(m!='~'){         //checks the starting delimiter  
        char* fail = "Failed to update ";
        concat(fail,name);
        USART_putstring(fail);
        _delay_ms(30);
        return -1;
    }

    i++;
    while(message[i]!='*'){ 
        m = message[i];
        if(name[i-1]!= m){
            _delay_ms(30);
            return -1;
        }
        i++;
    }   
    i++;    //passes the * names delimeter

    if(parse_motor(message,i)==0){
        char* success = "Successfully updated ";
        concat(success,name);
        USART_putstring(success);
        _delay_ms(30);
    }
    else{
        char* fail = "Failed to update ";
        concat(fail,name);
        USART_putstring(fail);
        _delay_ms(30);
        return -1;
    }

    return 0;
 
}

int parse_motor(char* message, int i){
    
    char* op_code = malloc(sizeof(char)*3);
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    op_code[j]='\0';
    i++;

    char* fs = "00", *hs = "01", *st = "02", *se = "03";
  
    if(strcmp(op_code,fs)==0){
        USART_putstring("Full Swing");  
        _delay_ms(30);  
    }
    else if (strcmp(op_code,hs)==0){
        USART_putstring("Half Swing");  
        _delay_ms(30); 
    }
    else if (strcmp(op_code,st)==0){
        USART_putstring("Stepper");     
        _delay_ms(30);
    }
    else if(strcmp(op_code,se)==0){
        USART_putstring("Servo");   
        _delay_ms(30);
    }    
    else{
        USART_putstring("Fail to parse Motor ");
        _delay_ms(30);          
        return -1;
    }

    return parse_pwm(message, i);         
}

int parse_pwm(char* message, int i){
    
    char* op_code = malloc(sizeof(char)*3);
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    } 
    op_code[j]='\0';  
    i++;
    
    char* p1 = "11", *p2 = "12", *p3 = "13", *p4 = "14";
  
    if(strcmp(op_code,p1)==0){
        USART_putstring("PWM1");   
        _delay_ms(30);
    }
    else if(strcmp(op_code,p2)==0){
        USART_putstring("PWM2");   
        _delay_ms(30);
    }
    else if(strcmp(op_code,p3)==0){
        USART_putstring("PWM3");   
        _delay_ms(30);
    }
    else if(strcmp(op_code,p4)==0){
        USART_putstring("PWM4");   
        _delay_ms(30);
    }    
    else{
        USART_putstring("Fail to parse PWM");
        _delay_ms(30);
        return -1;
    }

    return parse_dir(message, i);            
}

int parse_dir(char* message, int i){
    
    char* op_code = malloc(sizeof(char)*3);
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    op_code[j]='\0';
    i++;

    char *fwd = "21", *bwd = "20";
  
    if(strcmp(op_code,bwd)==0){
        USART_putstring("BACK");
        _delay_ms(30);
    }
    else if(strcmp(op_code,fwd)==0){
        USART_putstring("FORWARD");
        _delay_ms(30);
    }
    else{
        USART_putstring("Fail to parse direction");
        _delay_ms(30);
        return -1;
    }

    return parse_steps(message, i);          
}

int parse_steps(char* message, int i){
    
    char* op_code = malloc(sizeof(char)*7);
    int num_steps = 0;
    int j = 0;

    while(message[i]!='*'){ 
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   
    op_code[j] = '\0';
    i++;
    
    int k = 0;

    for(k=0; k<j; k++){
        num_steps = num_steps * 10 + ( op_code[k] - '0' );
    }

    if(num_steps<0||num_steps>65536){
        USART_putstring("Fail to parse Steps");
        _delay_ms(30);
        return -1;
    }
    
    USART_putstring("Steps success");
    _delay_ms(30);
    
    
    return parse_rate(message, i);   
}

int parse_rate(char* message, int i){
    
    
    _delay_ms(30);
    char* op_code = malloc(sizeof(char)*3);
    int j = 0;

    while(message[i]!='*'){         
        op_code[j] = message[i] ;       
        i++;
        j++;
    }   

    USART_putstring("GOT TO HERE");
    op_code[j]='\0';
    i++;

    char* r1 = "41", *r2 = "42", *r3 = "43", *r4 = "44";
  
    if(strcmp(op_code,r1)==0){
         USART_putstring("Rate 1");
        _delay_ms(30);        
    }
    else if(strcmp(op_code,r2)==0){
         USART_putstring("Rate 2");
        _delay_ms(30);
    }
    else if(strcmp(op_code,r3)==0){
         USART_putstring("Rate 3");
        _delay_ms(30);
    }
    else if(strcmp(op_code,r4)==0){
         USART_putstring("Rate 4");
        _delay_ms(30);
    }    
    else{
        USART_putstring("Fail to parse rate");
        _delay_ms(30);
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

