//
//  log.h
//  LogUtility
//  debug, info, error, warning, critical. più inclusione di un printf-like. Connessa a macro programming. Chiedi a me che ho un esempio
//  Created by Andrea Rossi on 22/07/2017.
//  Copyright © 2017 Andrea Rossi. All rights reserved.
//

#ifndef log_h

#include <time.h>

/*################################################ start commons ################################################*/
/* Timestamp NOW fixed dim*/

void timestamp(){
    time_t _now=clock();
#if ClOCKS_PER_SEC == 1000000000
    printf("%02d,%010lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 100000000
    printf("%02d,%09lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 10000000
    printf("%02d,%08lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 1000000
    printf("%02d,%07lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 100000
    printf("%02d,%06lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 10000
    printf("%02d,%05lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 1000
    printf("%02d,%04lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 100
    printf("%02d,%03lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 10
    printf("%02d,%02lu",localtime(&_now)->tm_sec,clock());
#elif CLOCKS_PER_SEC == 1
    printf("%02d,%01lu",localtime(&_now)->tm_sec,clock());
#else
    printf("Your CLOCKS_PER_SEC size is %d: check logutility to fix it",CLOCKS_PER_SEC);
#endif
}

void __message(char *m){
    printf("%s\n",m);
}

#ifdef DEBUG
#ifndef DEBUG_LABEL
#define DEBUG_LABEL "DEBUG"
#endif
#endif

#ifdef INFO
#ifndef INFO_LABEL
#define INFO_LABEL "INFO"
#endif
#endif
#ifdef ERROR
#ifndef ERROR_LABEL
#define ERROR_LABEL "ERROR"
#endif
#endif
#ifdef WARNING
#ifndef WARNING_LABEL
#define WARNING_LABEL "WARNING"
#endif
#endif
#ifdef CRITICAL
#ifndef CRITICAL_LABEL
#define CRITICAL_LABEL "CRITICAL"
#endif
#endif


/*################################################ end commons ################################################*/



/*################################################ DEBUG ################################################*/
#ifdef DEBUG
#ifndef DEBUG_LABEL
#define DEBUG_LABEL "DEBUG"
#endif
void log_d(char *s){
    timestamp();
    printf(" -- %s -- %s\n",DEBUG_LABEL,s);
    
}

#endif
/*################################################ INFO ################################################*/
#ifdef INFO
#ifndef INFO_LABEL
#define INFO_LABEL "INFO"
#endif
void log_i(char *s){
    timestamp();
    printf(" -- %s -- %s\n", INFO_LABEL,s);
    
}


#endif
/*################################################ ERROR ################################################*/
#ifdef ERROR
#ifndef ERROR_LABEL
#define ERROR_LABEL "ERROR"
#endif
void log_e(char *s){
    timestamp();
    printf(" -- %s -- %s\n",ERROR_LABEL,s);
    
}

#endif
/*################################################ WARNING ################################################*/
#ifdef WARNING
#ifndef WARNING_LABEL
#define WARNING_LABEL "WARNING"
#endif
void log_w(char *s){
    timestamp();
    printf(" -- %s -- %s\n",WARNING_LABEL,s);
    
}

#endif
/*################################################ CRITICAL ################################################*/
#ifdef CRITICAL
#ifndef CRITICAL_LABEL
#define CRITICAL_LABEL "CRITICAL"
#endif
void log_c(char *s){
    timestamp();
    printf(" -- %s -- %s\n",CRITICAL_LABEL,s);
    
}

#endif

/*################################################ start interface ################################################*/

#define log_h

void _log(char *m){
#ifdef DEBUG
    log_d(m);
#endif
#ifdef INFO
    log_i(m);
#endif
#ifdef ERROR
    log_e(m);
#endif
#ifdef WARNING
    log_w(m);
#endif
#ifdef CRITICAL
    log_c(m);
#endif
}



/*################################################ end interface ################################################*/

#endif /* log_h */
