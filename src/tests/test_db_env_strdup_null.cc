/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:
#ident "$Id$"
#ident "Copyright (c) 2007 Tokutek Inc.  All rights reserved."
#include "test.h"

/* Do I return EINVAL when passing in NULL for something that would otherwise be strdup'd? */

#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <db.h>


// ENVDIR is defined in the Makefile

DB_ENV *env;
DB *db;

int
test_main (int UU(argc), char UU(*const argv[])) {
    int r;
    r=system("rm -rf " ENVDIR);                    assert(r==0);
    r=toku_os_mkdir(ENVDIR, S_IRWXU+S_IRWXG+S_IRWXO);                         assert(r==0);
    r=db_env_create(&env, 0);                   assert(r==0);
// None of this stuff works with BDB.  TDB does more error checking.
#ifdef USE_TDB
    r=env->set_data_dir(env, NULL);             assert(r==EINVAL);
    r=env->open(env, ENVDIR, DB_CREATE|DB_PRIVATE, S_IRWXU+S_IRWXG+S_IRWXO);    assert(r==0);
    env->set_errpfx(env, NULL);                 assert(1); //Did not crash.
    r=env->set_tmp_dir(env, NULL);              assert(r==EINVAL);
#endif
    r=env->close(env, 0);                       assert(r==0);
    return 0;
}
