#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include "tree.h"
#include "reader.h"

void FileInput(struct Reader* read);
void ReplaceSymbol(struct Reader* read);
int StrCounter(struct Reader* read);
unsigned int MyFstat(struct Reader* read);

void Input(struct Reader* read)
{
    FileInput(read);

    read->count_lines = StrCounter(read);

    ReplaceSymbol(read);

}

void FileInput(struct Reader* read)
{
    read->file = fopen(read->input_file, "rb");
$$$ assert(read->file);

    read->count_elements = MyFstat(read);

    read->text = (char*) calloc(read->count_elements + 1, sizeof(char));
$$$ assert(read->text);

    size_t fread_check = fread(read->text, sizeof(char), read->count_elements, read->file);
$$$ assert(read->count_elements == fread_check);

    read->text[read->count_elements] = '\0';

    int errclose = !fclose(read->file);
$$$ assert(errclose); //!NDEBUG! !change to if!
}

int StrCounter(struct Reader* read)
{
    int count_of_lines = 1;

    for(size_t i = 0; i < read->count_elements; i++)
    {
        if(read->text[i] == '\r')
        {
            count_of_lines += 1;
        }
    }

    return count_of_lines;
}

void ReplaceSymbol(struct Reader* read)
{
    for(size_t i = 0; i < read->count_elements; i++)
    {
        if(read->text[i] == '\r')
        {
            read->text[i] = '\0';
            read->text[i+1] = '\0';
        }
    }

}

unsigned int MyFstat(struct Reader* read)
{
    int fseek_proof = fseek(read->file, 0, SEEK_END);
$$$ assert(fseek_proof + 1);

    unsigned int count_symb_in_file = ftell(read->file);

$$$ if(read->count_elements == (size_t)(-1L))
        printf("!File Size is 0!");

    rewind(read->file);

    return count_symb_in_file;
}