
#include "cos.h"

char *explore(char *token, maciora *p, Dane *z)
{
    char *url = (char *)malloc(sizeof(char) * 1024);
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore");
    strcat(url, "/");
    strcat(url, token);
    uzupelnienie_explore(interpret_response(make_request(url), z), p);
    free(url);
}

char *info(char *token, maciora *p, Dane *z)
{
    char *url = (char *)malloc(sizeof(char) * 1024);
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info");
    strcat(url, "/");
    strcat(url, token);
    uzupelnienie_info(interpret_response(make_request(url), z), p);
    free(url);
}

char *move(char *token, maciora *p, Dane *z)
{
    char *url = (char *)malloc(sizeof(char) * 1024);
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move");
    strcat(url, "/");
    strcat(url, token);
    make_request(url);
    uzupelnienie_info(interpret_response(make_request(url), z), p);
    free(url);
}

char *rotate(char *token, char *direction, maciora *p, Dane *z)
{
    char *url = (char *)malloc(sizeof(char) * 1024);
    strcpy(url, "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate");
    strcat(url, "/");
    strcat(url, token);
    strcat(url, "/");
    strcat(url, direction);
    make_request(url);
    uzupelnienie_info(interpret_response(make_request(url), z), p);
    free(url);
}