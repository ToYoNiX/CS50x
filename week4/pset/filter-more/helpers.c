#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating average
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Changing the values
            image[i][j].rgbtRed = avg, image[i][j].rgbtGreen = avg, image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculating middle point
    int middle = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            // Replacing pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }
    }

    double avg_red = 0, avg_green = 0, avg_blue = 0;
    int counter = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int line = i - 1; line <= i + 1; line++)
            {
                for (int index = j - 1; index <= j + 1; index++)
                {
                    if (line < 0 || index < 0 || line >= height || index >= width)
                    {
                        continue;
                    }

                    avg_red += tmp_image[line][index].rgbtRed;
                    avg_green += tmp_image[line][index].rgbtGreen;
                    avg_blue += tmp_image[line][index].rgbtBlue;

                    counter++;
                }
            }

            // Calculating the average
            avg_red = round(avg_red / counter);
            avg_green = round(avg_green / counter);
            avg_blue = round(avg_blue / counter);

            // Changing the values
            image[i][j].rgbtRed = avg_red;
            image[i][j].rgbtGreen = avg_green;
            image[i][j].rgbtBlue = avg_blue;

            // Cleaning the garbage
            avg_red = 0, avg_green = 0, avg_blue = 0, counter = 0;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}, gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int total_gx[3] = {0, 0, 0}, total_gy[3] = {0, 0, 0}, final[3] = {0, 0, 0}; // 0 -> red, 1 -> green, 2 -> blue

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pos_x = 0; // line index for gx and gy
            for (int line = i - 1; line <= i + 1; line++)
            {
                int pos_y = 0; // Colume index for gx and gy
                for (int index = j - 1; index <= j + 1; index++)
                {
                    if (line < 0 || index < 0 || line >= height || index >= width)
                    {
                        pos_y++;
                        continue;
                    }

                    total_gx[0] += (gx[pos_x][pos_y] * tmp_image[line][index].rgbtRed);
                    total_gx[1] += (gx[pos_x][pos_y] * tmp_image[line][index].rgbtGreen);
                    total_gx[2] += (gx[pos_x][pos_y] * tmp_image[line][index].rgbtBlue);

                    total_gy[0] += (gy[pos_x][pos_y] * tmp_image[line][index].rgbtRed);
                    total_gy[1] += (gy[pos_x][pos_y] * tmp_image[line][index].rgbtGreen);
                    total_gy[2] += (gy[pos_x][pos_y] * tmp_image[line][index].rgbtBlue);

                    pos_y++;
                }
                pos_x++;
            }

            // Final calculations
            for (int k = 0; k < 3; k++)
            {
                final[k] = round(sqrt(total_gx[k] * total_gx[k] + total_gy[k] * total_gy[k]));

                // Capping the value at 255
                if (final[k] > 255)
                {
                    final[k] = 255;
                }
            }

            // Changing the values
            image[i][j].rgbtRed = final[0];
            image[i][j].rgbtGreen = final[1];
            image[i][j].rgbtBlue = final[2];

            // Cleaning the garbage
            for (int k = 0; k < 3; k++)
            {
                total_gx[k] = 0;
                total_gy[k] = 0;
                final[k] = 0;
            }
        }
    }
    return;
}