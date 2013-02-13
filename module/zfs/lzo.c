/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2013 Cyril Plisko.  All rights reserved.
 */



#include <sys/debug.h>
#include <sys/types.h>

#ifdef _KERNEL

#include <sys/systm.h>
#include <sys/lzo.h>

/*ARGSUSED*/
size_t
lzo_compress(void *s_start, void *d_start, size_t s_len, size_t d_len, int n)
{
	size_t	dstlen = d_len;

	ASSERT(d_len <= s_len);

	if (spl_lzo_compress(d_start, &dstlen, s_start, s_len) != LZO_E_OK) {
		if (d_len != s_len)
			return (s_len);

		bcopy(s_start, d_start, s_len);
		return (s_len);
	}

	return (dstlen);
}

/*ARGSUSED*/
int
lzo_decompress(void *s_start, void *d_start, size_t s_len, size_t d_len, int n)
{
	size_t dstlen = d_len;

	ASSERT(d_len >= s_len);

	if (spl_lzo_decompress(d_start, &dstlen, s_start, s_len) != LZO_E_OK)
		return (-1);

	return (0);
}

void
lzo_init(void)
{
	(void) spl_lzo_init();
}

void
lzo_fini(void)
{
	spl_lzo_fini();
}

#else /* _KERNEL */

size_t
lzo_compress(void *s_start, void *d_start, size_t s_len, size_t d_len, int n)
{
	size_t dstlen = d_len;

	ASSERT(d_len <= s_len);

	bcopy(s_start, d_start, s_len);
	return (s_len);
}

/*ARGSUSED*/
int
lzo_decompress(void *s_start, void *d_start, size_t s_len, size_t d_len, int n)
{
	size_t dstlen = d_len;

	ASSERT(d_len >= s_len);

	bcopy(s_start, d_start, s_len);

	return (0);
}

void
lzo_init(void)
{
}

void
lzo_fini(void)
{
}

#endif /* _KERNEL */
