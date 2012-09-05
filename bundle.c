/*
 * zipwriter
 * a library for writing zipfiles
 *
 * copyright (c) 2006 Geo Carncross <geocar@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include "zipwriter.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void copytest(int in, zipwriter_file *out)
{
	char buffer[65536];
	int r, j;

	(void)lseek(in,0,SEEK_SET);
	for (;;) {
		do {
			r = read(in, buffer,sizeof(buffer));
		} while (r == -1 && errno == EINTR);
		if (!r) break;
		zipwriter_write(out, buffer, r);
	}
}

int main(int argc, char *argv[])
{
	zipwriter *z;
	zipwriter_file *f;

	z = zipwriter_start(open("zipwriter.zip", O_RDWR|O_CREAT|O_TRUNC, 0666));
#define M "a library for writing zipfiles\n\n" \
"Copyright \302\251 2006 Geo Carncross <geocar@gmail.com>\n\n" \
"This program is free software; you can redistribute it and/or modify\n" \
"it under the terms of the GNU General Public License as published by\n" \
"the Free Software Foundation; either version 2 of the License, or\n" \
"(at your option) any later version.\n\n" \
"This program is distributed in the hope that it will be useful,\n" \
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" \
"GNU General Public License for more details.\n\n" \
"You should have received a copy of the GNU General Public License\n" \
"along with this program; if not, write to the Free Software\n" \
"Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\n\n"
	zipwriter_comment(z, M,sizeof(M)-1);

#define ZF(a,b,c)  copytest(open(a,O_RDONLY),zipwriter_addfile(z,b,c))
	ZF("Makefile", "zipwriter/Makefile", ZIPWRITER_DEFLATE9);
	ZF("zipwriter.c", "zipwriter/zipwriter.c", ZIPWRITER_DEFLATE9);
	ZF("zipwriter.h", "zipwriter/zipwriter.h", ZIPWRITER_DEFLATE9);
	ZF("testzip.c", "zipwriter/testzip.c", ZIPWRITER_DEFLATE9);
	ZF("bundle.c", "zipwriter/bundle.c", ZIPWRITER_DEFLATE9);
	ZF("COPYING", "zipwriter/COPYING", ZIPWRITER_DEFLATE9);
	if (!zipwriter_finish(z)) {
		puts("err");
		exit(1);
	}
	exit(0);
}
	


