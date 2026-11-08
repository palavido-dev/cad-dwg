/* SPDX-License-Identifier: MIT */
#include "caddwg/version.h"

#include <stdio.h>
#include <string.h>

static int g_failed = 0;

static void expect_version(const char* label, const void* bytes, size_t size, caddwg_version want, const char* want_name) {
    const caddwg_probe got = caddwg_probe_version((const uint8_t*)bytes, size);
    if (got.version != want || strcmp(got.name, want_name) != 0) {
        fprintf(stderr, "FAIL %s: got %s (%d), want %s\n", label, got.name, (int)got.version, want_name);
        g_failed++;
        return;
    }
    if (want == CADDWG_VERSION_UNKNOWN) {
        if (got.magic != NULL) {
            fprintf(stderr, "FAIL %s: unknown probe kept a magic\n", label);
            g_failed++;
        }
        return;
    }
    if (got.magic == NULL || memcmp(got.magic, bytes, 6) != 0) {
        fprintf(stderr, "FAIL %s: magic mismatch\n", label);
        g_failed++;
    }
}

int main(void) {
    expect_version("empty", "", 0, CADDWG_VERSION_UNKNOWN, "unknown");
    expect_version("short", "AC101", 5, CADDWG_VERSION_UNKNOWN, "unknown");
    expect_version("null", NULL, 6, CADDWG_VERSION_UNKNOWN, "unknown");
    expect_version("dxf", "  0\nSECTION", 11, CADDWG_VERSION_UNKNOWN, "unknown");
    expect_version("lower", "ac1018xxxx", 10, CADDWG_VERSION_UNKNOWN, "unknown");
    expect_version("not-a-version", "AC9999rest", 10, CADDWG_VERSION_UNKNOWN, "unknown");
    expect_version("embedded", "xxAC1018", 8, CADDWG_VERSION_UNKNOWN, "unknown");

    expect_version("r13", "AC1012rest-of-file", 16, CADDWG_VERSION_R13, "R13");
    expect_version("r14", "AC1014rest-of-file", 16, CADDWG_VERSION_R14, "R14");
    expect_version("r2000", "AC1015rest-of-file", 16, CADDWG_VERSION_R2000, "R2000");
    expect_version("r2004", "AC1018rest-of-file", 16, CADDWG_VERSION_R2004, "R2004");
    expect_version("r2007", "AC1021rest-of-file", 16, CADDWG_VERSION_R2007, "R2007");
    expect_version("r2010", "AC1024rest-of-file", 16, CADDWG_VERSION_R2010, "R2010");
    expect_version("r2013", "AC1027rest-of-file", 16, CADDWG_VERSION_R2013, "R2013");
    expect_version("r2018", "AC1032rest-of-file", 16, CADDWG_VERSION_R2018, "R2018");
    expect_version("exact-6", "AC1018", 6, CADDWG_VERSION_R2004, "R2004");

    if (g_failed != 0) {
        fprintf(stderr, "%d failure(s)\n", g_failed);
        return 1;
    }
    printf("ok\n");
    return 0;
}
