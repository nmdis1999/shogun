#include <string.h>
#include <assert.h>

#include "lib/File.h"
#include "lib/SimpleFile.h"

CFile::CFile(char* fname, char rw, EType typ, char fourcc[4])
{
	status=false;
	task=rw;
	expected_type=typ;
	this->fname=strdup(fname);
	char mode[2];
	mode[0]=rw;
	mode[1]='\0';


	if (rw=='r' || rw == 'w')
	{
		if ( fname)
		{
			if ((file=fopen((const char*) fname, (const char*) mode)))
				status=true;
		}
	}

	if (fourcc)
	{
		if (rw=='r')
			status=read_header();
		else if (rw=='w')
			status=read_header();

		if (!status)
			fclose(file);

		file=NULL;
	}
}

CFile::~CFile()
{
	fclose(file);
	file=NULL;
}

INT* CFile::load_int_data(INT* target, long& num)
{
	assert(expected_type==F_INT);
	CSimpleFile<INT> f(fname, file);
	target=f.load(target, num);
	status=(target!=NULL);
	return target;
}

bool CFile::save_int_data(INT* src, long num)
{
	assert(expected_type==F_INT);
	CSimpleFile<INT> f(fname, file);
	status=f.save(src, num);
	return status;
}

REAL* CFile::load_real_data(REAL* target, long& num)
{
	assert(expected_type==F_REAL);
	CSimpleFile<REAL> f(fname, file);
	target=f.load(target, num);
	status=(target!=NULL);
	return target;
}

bool CFile::save_real_data(REAL* src, long num)
{
	assert(expected_type==F_REAL);
	CSimpleFile<REAL> f(fname, file);
	status=f.save(src, num);
	return status;
}

CHAR* CFile::load_char_data(CHAR* target, long& num)
{
	assert(expected_type==F_CHAR);
	CSimpleFile<CHAR> f(fname, file);
	target=f.load(target, num);
	status=(target!=NULL);
	return target;
}

BYTE* CFile::load_byte_data(BYTE* target, long& num)
{
	assert(expected_type==F_BYTE);
	CSimpleFile<BYTE> f(fname, file);
	target=f.load(target, num);
	status=(target!=NULL);
	return target;
}

WORD* CFile::load_word_data(WORD* target, long& num)
{
	assert(expected_type==F_WORD);
	CSimpleFile<WORD> f(fname, file);
	target=f.load(target, num);
	status=(target!=NULL);
	return target;
}

SHORT* CFile::load_short_data(SHORT* target, long& num)
{
	assert(expected_type==F_SHORT);
	CSimpleFile<SHORT> f(fname, file);
	target=f.load(target, num);
	status=(target!=NULL);
	return target;
}

int parse_first_header(EType &type)
{
	return -1;
}

int parse_next_header(EType &type)
{
	return -1;
}


bool CFile::read_header()
{
    assert(file!=NULL);
    unsigned int intlen=0;
    unsigned int endian=0;
    unsigned int fourcc=0;
    unsigned int doublelen=0;

    assert(fread(&intlen, sizeof(unsigned char), 1, file)==1);
    assert(fread(&doublelen, sizeof(unsigned char), 1, file)==1);
    assert(fread(&endian, (unsigned int) intlen, 1, file)== 1);
    assert(fread(&fourcc, (unsigned int) intlen, 1, file)==1);
	return false;
}

bool CFile::write_header()
{
    unsigned char intlen=sizeof(unsigned int);
    unsigned char doublelen=sizeof(double);
    unsigned int endian=0x12345678;

    assert(fwrite(&intlen, sizeof(unsigned char), 1, file)==1);
    assert(fwrite(&doublelen, sizeof(unsigned char), 1, file)==1);
    assert(fwrite(&endian, sizeof(unsigned int), 1, file)==1);
    assert(fwrite(&fourcc, 4*sizeof(char), 1, file)==1);

	return false;
}
