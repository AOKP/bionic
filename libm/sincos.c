/*-
 * Copyright (c) 2010 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */
#define _GNU_SOURCE 1
#include <math.h>
#define INLINE_KERNEL_COSDF
#define INLINE_KERNEL_SINDF
#include "upstream-freebsd/lib/msun/src/math_private.h"
#include "upstream-freebsd/lib/msun/src/k_cosf.c"
#include "upstream-freebsd/lib/msun/src/k_sinf.c"

/* Small multiples of pi/2 rounded to double precision. */
static const double
	s1pio2 = 1*M_PI_2,		/* 0x3FF921FB, 0x54442D18 */
	s2pio2 = 2*M_PI_2,		/* 0x400921FB, 0x54442D18 */
	s3pio2 = 3*M_PI_2,		/* 0x4012D97C, 0x7F3321D2 */
	s4pio2 = 4*M_PI_2;		/* 0x401921FB, 0x54442D18 */

// Disable sincos optimization for all functions in this file,
// otherwise gcc would generate infinite calls.
// Refer to gcc PR46926.
// -fno-builtin-sin or -fno-builtin-cos can disable sincos optimization,
// but these two options do not work inside optimize pragma in-file.
// Thus we just enforce -O0 when compiling this file.
#pragma GCC optimize ("O0")

void sincos(double x, double* p_sin, double* p_cos) {
  *p_sin = sin(x);
  *p_cos = cos(x);
}

void sincosf(float x, float* p_sinf, float* p_cosf) {
  *p_sinf = sinf(x);
  *p_cosf = cosf(x);
}

void sincosl(long double x, long double* p_sinl, long double* p_cosl) {
  *p_sinl = sinl(x);
  *p_cosl = cosl(x);
}
