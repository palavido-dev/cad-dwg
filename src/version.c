/* SPDX-License-Identifier: MIT */
#include "caddwg/version.h"

#include <string.h>

typedef struct magic_map {
    const char magic[7];
    caddwg_version version;
    const char* name;
} magic_map;

/* Leading magic used by DWG files. The strings are the on-disk version
 * codes, not a decoder. */
static const magic_map k_magics[] = {
    {"AC1012", CADDWG_VERSION_R13, "R13"},
    {"AC1014", CADDWG_VERSION_R14, "R14"},
    {"AC1015", CADDWG_VERSION_R2000, "R2000"},
    {"AC1018", CADDWG_VERSION_R2004, "R2004"},
    {"AC1021", CADDWG_VERSION_R2007, "R2007"},
    {"AC1024", CADDWG_VERSION_R2010, "R2010"},
    {"AC1027", CADDWG_VERSION_R2013, "R2013"},
    {"AC1032", CADDWG_VERSION_R2018, "R2018"},
};

caddwg_probe caddwg_probe_version(const uint8_t* data, size_t size) {
    caddwg_probe unknown;
    unknown.version = CADDWG_VERSION_UNKNOWN;
    unknown.magic = NULL;
    unknown.name = "unknown";
    if (data == NULL || size < 6) {
        return unknown;
    }
    for (size_t i = 0; i < sizeof(k_magics) / sizeof(k_magics[0]); i++) {
        if (memcmp(data, k_magics[i].magic, 6) == 0) {
            caddwg_probe found;
            found.version = k_magics[i].version;
            found.magic = k_magics[i].magic;
            found.name = k_magics[i].name;
            return found;
        }
    }
    return unknown;
}
