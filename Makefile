#
# zipwriter
# a library for writing zipfiles
#
# copyright (c) 2006 Geo Carncross <geocar@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

bundle: bundle.o zipwriter.o -lz
bundle.o: bundle.c zipwriter.h
zipwriter.o: zipwriter.c zipwriter.h
clean:;rm -f *.o bundle
distclean: clean; rm -f zipwriter.zip
