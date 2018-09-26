#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//! Creation pointers on massiv
//! @param [in] mem  mem - pointer on massiv
//! @param [in] file_in file_in - pointer on file
//! @param [in] kol_strings kol_strings - ammount of strings
//! @return array of pointers to the beginning of lines
char** Create_pointers (char *mem, FILE *file_in, int unsigned kol_strings);



//! reads a file and writes it to dynamic memory
//! @param [in] file_in file in - the file which we want to record
//! @return array where the read file is located
char *Read_file(FILE *file_in);



//! recorde information to a file
//! @param [in] arr_pointers arr_pointers - pointer to the array to be written
//! @param [in] kol_strings kol_strings - ammount of strings
void Write_file(char **arr_pointers, int unsigned kol_strings);



//! determines the number of characters in the file
//! @param [in] file_in file in - file number of elements we are looking for
//! @return  number of characters in file
unsigned int def_Len_file(FILE *file_in);



//! determines the number of lines in the file
//! @param [in] mem mem - a pointer to a file to determine the number of lines
//! @return number of strings in the file
unsigned int def_kol_strings(char *mem);



//! reads the file and creates an array of pointers to the beginning of the lines
//! @return array of pointers to the beginning of lines
char **read_file_create_arr_pointers ();



//! sets the sort condition
//! @param [in] s1 s1 - first element of comparison
//! @param [in] s2 s2 - second element of comparison
//! @return 1 if s1 > s2, 0 if s1 < s2
int comp(const void* s1, const void* s2);




int main ()
{
    char **arr_pointers = read_file_create_arr_pointers();

    int unsigned kol_strings = def_kol_strings(arr_pointers[0]);

    qsort(arr_pointers, kol_strings, sizeof(*arr_pointers), comp);

    Write_file(arr_pointers, kol_strings);

    return 0;

}

char **Create_pointers (char *mem, FILE *file_in, int unsigned kol_strings)
{
    assert(mem != NULL);
    assert(file_in);
    assert(kol_strings);

    char **arr_pointers = (char **)calloc( kol_strings + 1, sizeof(*arr_pointers));

    arr_pointers[0] = &mem[0];

    char simvol = 0;
    int i = 0, position = 0;

    simvol = mem[i];

    while (mem[i] != EOF)
    {
        if (simvol == '\n')
        {
            simvol = '\0';
            mem[i] = simvol;
            arr_pointers[++position] = &mem[i + 1];
        }
        else
            mem[i] = simvol;

        i++;
    }
    arr_pointers[position] = NULL;
    fclose(file_in);
    return arr_pointers;
}

char *Read_file(FILE *file_in)
{
    assert(file_in);

    unsigned int len_file = def_Len_file(file_in);

    char *mem = (char *)calloc( len_file + 1 , sizeof(*mem));
    fread(mem, len_file + 1, sizeof(*mem), file_in);

    return mem;
}

void Write_file(char **arr_pointers, int unsigned kol_strings)
{
    assert(arr_pointers != NULL);
    assert(kol_strings);

    int index = 0;
    FILE *file_out = fopen("Rezultat.txt", "w");

    for (index = 0; index < kol_strings; index++ )
    {
        fputs( arr_pointers[index], file_out);
        fputc('\n', file_out);
    }
    fclose(file_out);
}

unsigned int def_Len_file(FILE *file_in)
{
    assert(file_in);

    unsigned int kol_simvols = 0;

    fseek(file_in, 0, SEEK_END);
    kol_simvols = ftell(file_in);
    fseek(file_in, 0, SEEK_SET);

    return kol_simvols;
}

unsigned int def_kol_strings(char *mem)
{
    assert(mem != NULL);

    unsigned int number_string = 0;
    int i = 0;

    while (mem[i] != EOF)
    {
        if (mem[i] == '\n')
            number_string++;

        i++;
    }
    return number_string;
}

char **read_file_create_arr_pointers ()
{
    FILE *file_in = fopen("E_Onegin.txt", "r");
    if (file_in == NULL) {
        return 0;
    }
    char *mem = Read_file(file_in);
    int unsigned kol_strings = def_kol_strings(mem);
    char **arr_pointers = Create_pointers(mem, file_in, kol_strings);

    assert(file_in);
    assert(mem != NULL);
    assert(kol_strings);
    assert(arr_pointers != NULL);

    return arr_pointers;
}

int comp(const void* s1, const void* s2)
{
    return strcmp(*(char* const*) s1, *(char* const*) s2);
}