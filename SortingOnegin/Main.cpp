//! @file
//! \brief Программа сортирует в лексикографическом порядке письмо Онегина Татьяне
//! @mainpage
//-----------------------------------------------------------------------------------------------------------------
//! \author     TheCompiler
//! \version    alpha 1
//! \date       05.09.2019
//=================================================================================================================

#include <iostream>
#include "VectorOfString.h"

int main(int argc, char *argv[])
{
    if(argc != 3) {
		printf("# Please write inputFile, them outputFile\n");
		return 1;
	}

    printf("# Start\n\n");

    VectorOfStrings* vec = ReadVectorFromFile(argv[1]);

    insertionSorting(vec);

    WriteVectorToFile(argv[2], vec);

    printf("# Done\n");

    vec->~VectorOfStrings();

    return 0;
}