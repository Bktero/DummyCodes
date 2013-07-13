/*
bindump

bindump prints the content of a file, byte per byte.
Each byte prints to a new line, both in hexa and binary formats.


//----------------------------------------------------------------------------------
Simplified BSD License

Copyright (c) 2012-2013, Pierre GRADOT
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
//----------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef unsigned char byte_t;

void
print_octet_as_bin(byte_t number)
{
    int i;
    for(i=0; i<8; i++)
    {
        printf("%d ", (number >> (7-i)) & 1 );
    }
}

int
binary_dump(const char *file_name)
{
    byte_t buffer = 0;
    FILE* fh = fopen(file_name, "rb");
    int return_code = 0;

    errno = 0;

    if( fh == NULL)
    {
        printf("Cannot open file (%s)\n"
               "ERRNO = %d = %s\n", file_name, errno, strerror(errno));
        return_code = 1;
    }
    else
    {
        puts("Hexa\tBinary");

         // Read the entire file
        while( fread(&buffer, sizeof(byte_t), 1, fh) == 1)
        {
            printf("%.2X \t", buffer);
            print_octet_as_bin(buffer);
            printf("\n");
        }

        // See why fread() failed
        if(feof(fh) != 0)
        {
            // EOF reached, OK
            return_code = 0;
        }

        if(ferror(fh) != 0)
        {
            printf("\nError while reading file (%s)\n"
                   "ERRNO = %d = %s\n", file_name, errno, strerror(errno));
            return_code = 2;
        }
    }
    return return_code;
}

int
main(int argc, char *argv[])
{
    if(argc != 2)
    {
        puts("bindump takes a file name as parameter\n");
        return EXIT_FAILURE;
    }
    else
    {
        return binary_dump(argv[1]);
    }
}
