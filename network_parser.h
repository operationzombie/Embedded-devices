#ifndef PARSER_H
#define PARSER_H

#include "global.h"
#include "uart.h"


int parse_message(char* message);
int parse_name(char* message, int i);
int parse_motor(char* message, int i);
int parse_pwm(char* message, int i);
int parse_dir(char* message, int i);
int parse_steps(char* message, int i);
int parse_rate(char* message, int i);
char* concat(char *s1, char *s2);

#endif