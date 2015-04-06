/*
 * getopt - POSIX like getopt for Windows console Application
 *
 * win-c - Windows Console Library
 * Copyright (c) 2015 Koji Takami
 * Released under the MIT license
 * https://github.com/takamin/win-c/blob/master/LICENSE
 */
#include <stdio.h>
#include <string.h>
#include "getopt.h"

char* optarg = 0;
int optind = 1;
int opterr = 1;
int optopt = 0;

int getopt(int argc, char* const argv[],
            const char* optstring)
{
    static int nextchar = 0;
    while(1) {
		int c;
		const char* optptr = 0;
        if(optind >= argc) {
            nextchar = 0;
            return -1;
        }
        c = *(argv[optind] + nextchar);
        if(c == '\0') {
            nextchar = 0;
            ++optind;
            continue;
        }
        if(nextchar == 0) {
            if(c != '-') {
                nextchar = 0;
                return -1;
            } else {
                ++nextchar;
                continue;
            }
        }
        optptr = strchr(optstring, c);
        if(optptr == NULL) {
            optopt = c;
            if(opterr) {
                fprintf(stderr,
                        "%s : unknown option '%c'.\n",
                        argv[0], c);
            }
            ++nextchar;
            return '?';
        }
        if(*(optptr+1) != ':') {
            nextchar++;
            if(*(argv[optind] + nextchar) == '\0') {
                ++optind;
                nextchar = 0;
            }
        } else {
            nextchar++;
            if(*(argv[optind] + nextchar) != '\0') {
                optarg = argv[optind] + nextchar;
            } else {
                ++optind;
                if(optind < argc) {
                    optarg = argv[optind];
                } else {
                    optopt = c;
                    if(opterr) {
                        fprintf(stderr,
                                "%s : argument required for option '%c'.\n",
                                argv[0], c);
                    }
                    if(optstring[0] == ':') {
                        c = ':';
                    } else {
                        c = '?';
                    }
                }
            }
            ++optind;
            nextchar = 0;
        }
        return c;
    }
    return -1;
}

/********************************************************
int getopt_long(int argc, char* const argv[],
        const char* optstring,
        const struct option* longopts, int* longindex)
{
    return -1;
}
int getopt_long_only(int argc, char* const argv[],
        const char* optstring,
        const struct option* longopts, int* longindex)
{
    return -1;
}
********************************************************/
