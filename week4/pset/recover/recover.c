#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Some needed defines
#define byte uint8_t
#define string char *
#define buffer_size 512

// Functions prototype
bool is_jpg(byte *buffer);

int main(int argc, string argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open the card file
    FILE *card = fopen(argv[1], "r");

    // Check if file exists
    if (card == NULL)
    {
        printf("Could not open the card.\n");
        return 1;
    }

    // Make a buffer
    byte buffer[buffer_size];

    // Create a picture count
    int pic_count = 0;

    // Make a file to write into
    FILE *picture = NULL;

    while (fread(buffer, buffer_size, 1, card))
    {
        // Check if it's a start of a jpg
        if (is_jpg(buffer))
        {
            // Close the previous picture if found
            if (picture != NULL)
            {
                fclose(picture);
            }

            // Create a name for the new file
            char filename[8];
            sprintf(filename, "%03i.jpg", pic_count);

            // Open a new picture
            picture = fopen(filename, "a");

            // Check if something went wrong
            if (picture == NULL)
            {
                printf("Could not open a picture.\n");
                return 1;
            }

            pic_count++;
        }

        // If there is a file already opened -> Write the buffer size chunks to it
        if (picture != NULL)
        {
            fwrite(buffer, buffer_size, 1, picture);
        }
    }

    // Clear the memory
    fclose(card);
    fclose(picture);
    return 0;
}

// Check if it's a start of a jpg
bool is_jpg(byte *buffer)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}