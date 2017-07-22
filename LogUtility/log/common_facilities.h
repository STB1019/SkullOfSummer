//
//  common_facilities.h
//  LogUtility
//
//  Created by Andrea Rossi on 22/07/2017.
//  Copyright © 2017 Andrea Rossi. All rights reserved.
//

#ifndef common_facilities_h
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
#define common_facilities_h


#endif /* common_facilities_h */
