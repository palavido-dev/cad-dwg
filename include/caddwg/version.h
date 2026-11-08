/* SPDX-License-Identifier: MIT */
#ifndef CADDWG_VERSION_H
#define CADDWG_VERSION_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DWG version ids used by the file's leading magic ("AC1015" and friends).
 * Geometry decoding is not implemented. R2000 is already read by GDAL's
 * in-tree CAD driver (libopencad). Later ids are recognized so a decoder
 * can refuse them clearly instead of pretending they are R2000. */
typedef enum caddwg_version {
    CADDWG_VERSION_UNKNOWN = 0,
    CADDWG_VERSION_R13,   /* AC1012 */
    CADDWG_VERSION_R14,   /* AC1014 */
    CADDWG_VERSION_R2000, /* AC1015 */
    CADDWG_VERSION_R2004, /* AC1018 */
    CADDWG_VERSION_R2007, /* AC1021 */
    CADDWG_VERSION_R2010, /* AC1024 */
    CADDWG_VERSION_R2013, /* AC1027 */
    CADDWG_VERSION_R2018  /* AC1032 */
} caddwg_version;

typedef struct caddwg_probe {
    caddwg_version version;
    /* Six-character magic when version != UNKNOWN, otherwise NULL.
     * Points at a static string, not into `data`. */
    const char* magic;
    /* Short stable name such as "R2004", or "unknown". Static string. */
    const char* name;
} caddwg_probe;

/* Inspect the leading bytes of a DWG. Does not allocate.
 * A buffer shorter than 6 bytes, or any other magic, is UNKNOWN.
 * This does not validate the rest of the file. */
caddwg_probe caddwg_probe_version(const uint8_t* data, size_t size);

#ifdef __cplusplus
}
#endif

#endif
