#ifndef _DAO_H
#define _DAO_H

#include "../inc/bank.h"

int genid (void);
int save (const ACCOUNT* acc);
int get (int id, ACCOUNT* acc);
int update (const ACCOUNT* acc);
int delete (int id);

#endif // _DAO_H
