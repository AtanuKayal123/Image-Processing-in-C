#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//t
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX_COLOR 255
#define BRIGHTNESS_FACTOR 25
#define MAX_VALUE 255
void rotate()
{
    FILE *fIn = fopen("lena512.bmp", "r");       // Input File name
    FILE *fOut = fopen("lena_rotate.bmp", "w+"); // Output File name

    int i, j, choice;
    unsigned char byte[54], colorTable[1024];

    if (fIn == NULL) // check if the input file has not been opened succesfully.
    {
        printf("File does not exist.\n");
    }

    for (i = 0; i < 54; i++) // read the 54 byte header from fIn
    {
        byte[i] = getc(fIn);
    }

    fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

    // extract image height, width and bitDepth from imageHeader
    int height = *(int *)&byte[18];
    int width = *(int *)&byte[22];
    int bitDepth = *(int *)&byte[28];

    printf("width: %d\n", width);
    printf("height: %d\n", height);

    int size = height * width; // calculate image size

    if (bitDepth <= 8) // if ColorTable present, extract it.
    {
        fread(colorTable, sizeof(unsigned char), 1024, fIn);
        fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
    }

    unsigned char buffer[width][height]; // to store the image data
    unsigned char out_buffer[width][height];

    fread(buffer, sizeof(unsigned char), size, fIn); // read the image data

    printf("Enter your choice :\n");
    printf("1. Rotate right\n");
    printf("2. Rotate left\n");
    printf("3. Rotate 180\n");

    scanf("%d", &choice);

    switch (choice) // to rotate image in 3 direction
    {
    case 1:
        for (i = 0; i < width; i++) // to rotate right
        {
            for (j = 0; j < height; j++)
            {
                out_buffer[j][height - 1 - i] = buffer[i][j];
            }
        }
        break;
    case 2:
        for (i = 0; i < width; i++) // to rotate left
        {
            for (j = 0; j < height; j++)
            {
                out_buffer[j][i] = buffer[i][j];
            }
        }
        break;
    case 3:
        for (i = 0; i < width; i++) // to rotate 180 degree
        {
            for (j = 0; j < height; j++)
            {
                out_buffer[width - i][j] = buffer[i][j];
            }
        }
        break;
    default:
        break;
    }

    fwrite(out_buffer, sizeof(unsigned char), size, fOut); // write back to the output image

    fclose(fIn);
    fclose(fOut);
}
int main()
{
    int choice, i, j, k, size;

    do
    {
        printf("Select the filter for Image.\n");
        printf("1. Black to White.\n");
        printf("2. RGB to gray.\n");
        printf("3. Increase brightness.\n");
        printf("4. Blur the Image.\n");
        printf("5. Blur to Gray.\n");
        printf("6. Colours to Sepia.\n");
        printf("7. Copy Image.\n");
        printf("8. Darken Image.\n");
        printf("9. Rotate Image.\n");
        printf("10. Negative Image.\n");
        printf("11. Exit.\n");

        scanf("%d", &choice);

        if (choice == 1)
        {                                          // Black to White
                                                   // Implement your code here
            FILE *fIn = fopen("lena512.bmp", "r"); // Input File name
            FILE *fOut = fopen("b_2w.bmp", "w+");  // Output File name

            int i;
            unsigned char byte[54];         // to get the image header
            unsigned char colorTable[1024]; // to get the colortable

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            if (bitDepth <= 8) // if ColorTable present, extract it.
            {
                fread(colorTable, sizeof(unsigned char), 1024, fIn);
                fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
            }

            unsigned char buffer[size]; // to store the image data

            fread(buffer, sizeof(unsigned char), size, fIn); // read image data

            for (i = 0; i < size; i++) // store 0(black) and 255(white) values to buffer
            {
                buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
            }

            fwrite(buffer, sizeof(unsigned char), size, fOut); // write back to the output image

            fclose(fIn);
            fclose(fOut);

            break;
        }

        else if (choice == 2)
        { // RGB to Gray
            // Implement your code here
            clock_t start, stop;

            start = clock(); // Note the start time for profiling purposes.

            FILE *fIn = fopen("lena_color.bmp", "r");  // Input File name
            FILE *fOut = fopen("lena_gray.bmp", "w+"); // Output File name

            int i, j, y;
            unsigned char byte[54];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            unsigned char buffe[size][3]; // to store the image data

            for (i = 0; i < size; i++) // RGB to gray
            {
                y = 0;
                buffe[i][2] = getc(fIn); // blue
                buffe[i][1] = getc(fIn); // green
                buffe[i][0] = getc(fIn); // red

                y = (buffe[i][0] * 0.3) + (buffe[i][1] * 0.59) + (buffe[i][2] * 0.11); // conversion formula of rgb to gray

                putc(y, fOut);
                putc(y, fOut);
                putc(y, fOut);
            }

            fclose(fOut);
            fclose(fIn);

            stop = clock();
            printf("\nCLOCKS_PER_SEC = %ld\n", stop - start);
            printf("%lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }

        else if (choice == 3)
        { // Increase brightness
            // Implement your code here
            FILE *fIn = fopen("lena512.bmp", "r");       // Input File name
            FILE *fOut = fopen("lena_bright.bmp", "w+"); // Output File name

            int i;
            unsigned char byte[54], colorTable[1024];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
                exit(1);
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            if (bitDepth <= 8) // if ColorTable present, extract it.
            {
                fread(colorTable, sizeof(unsigned char), 1024, fIn);
                fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
            }

            unsigned char buffer[size]; // to store the image data
            int temp;

            fread(buffer, sizeof(unsigned char), size, fIn); // read image data

            for (i = 0; i < size; i++) // increasing pixel values to get image bright
            {
                temp = buffer[i] + BRIGHTNESS_FACTOR;
                buffer[i] = (temp > MAX_COLOR) ? MAX_COLOR : temp;
            }

            fwrite(buffer, sizeof(unsigned char), size, fOut); // write back to the output image

            fclose(fIn);
            fclose(fOut);

            break;
        }

        else if (choice == 4)
        { // Blur the Image
            // Implement your code here
            clock_t start, stop;

            start = clock(); // Note the start time for profiling purposes.

            FILE *fIn = fopen("images/lena_color.bmp", "r"); // Input File name
            FILE *fOut = fopen("lena_blur_color.bmp", "w+"); // Output File name

            int i, j, y, x;
            unsigned char byte[54];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate the image size

            unsigned char buffe[size][3]; // store the input image data
            unsigned char out[size][3];   // store the output image data

            for (i = 0; i < size; i++) // read image data character by character
            {
                buffe[i][2] = getc(fIn); // blue
                buffe[i][1] = getc(fIn); // green
                buffe[i][0] = getc(fIn); // red
            }

            float v = 1.0 / 9.0; // initialize the blurrring kernel
            float kernel[3][3] = {{v, v, v},
                                  {v, v, v},
                                  {v, v, v}};

            for (x = 1; x < height - 1; x++)
            {
                for (y = 1; y < width - 1; y++)
                {
                    float sum0 = 0.0;
                    float sum1 = 0.0;
                    float sum2 = 0.0;
                    for (i = -1; i <= 1; ++i)
                    {
                        for (j = -1; j <= 1; ++j)
                        {
                            // matrix multiplication with kernel with every color plane
                            sum0 = sum0 + (float)kernel[i + 1][j + 1] * buffe[(x + i) * width + (y + j)][0];
                            sum1 = sum1 + (float)kernel[i + 1][j + 1] * buffe[(x + i) * width + (y + j)][1];
                            sum2 = sum2 + (float)kernel[i + 1][j + 1] * buffe[(x + i) * width + (y + j)][2];
                        }
                    }
                    out[(x)*width + (y)][0] = sum0;
                    out[(x)*width + (y)][1] = sum1;
                    out[(x)*width + (y)][2] = sum2;
                }
            }

            for (i = 0; i < size; i++) // write image data back to the file
            {
                putc(out[i][2], fOut);
                putc(out[i][1], fOut);
                putc(out[i][0], fOut);
            }

            fclose(fOut);
            fclose(fIn);

            stop = clock();
            printf("\nCLOCKS_PER_SEC = %ld\n", stop - start); // 1000000
            printf("%lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }

        else if (choice == 5)
        { // Blur to Gray
            // Implement your code here
            clock_t start, stop;

            start = clock(); // Note the start time for profiling purposes.

            FILE *fIn = fopen("Images/lena_color.bmp", "r"); // Input File name
            FILE *fOut = fopen("lena_gray.bmp", "w+");       // Output File name

            int i, j, y;
            unsigned char byte[54];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            unsigned char buffer[size], outline[size]; // to store the image data

            float v = 1.0 / 9.0;
            float kernel[3][3] = {{v, v, v}, // initialize the blurrring kernel
                                  {v, v, v},
                                  {v, v, v}};

            fread(buffer, sizeof(unsigned char), size, fIn); // read the image data into buffer

            for (i = 0; i < size; i++)
            {
                outline[i] = buffer[i]; // copy image data to out bufer
            }

            for (int x = 1; x < height - 1; x++)
            {
                for (y = 1; y < width - 1; y++)
                {
                    float sum = 0.0;
                    for (i = -1; i <= 1; ++i)
                    {
                        for (j = -1; j <= 1; ++j)
                        {
                            sum = sum + (float)kernel[i + 1][j + 1] * buffer[(x + i) * width + (y + j)]; // matrix multiplication with kernel
                        }
                    }
                    outline[(x)*width + (y)] = sum;
                }
            }

            fwrite(outline, sizeof(unsigned char), size, fOut); // write image data back to the file

            fclose(fIn);
            fclose(fOut);
            break;
        }

        else if (choice == 6)
        { // Colours to Sepia
            // Implement your code here
            clock_t start, stop;

            start = clock(); // Note the start time for profiling purposes.

            FILE *fIn = fopen("lena_color.bmp", "r");   // Input File name
            FILE *fOut = fopen("lena_sepia.bmp", "w+"); // Output File name

            int i, r, g, b;
            unsigned char byte[54];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            unsigned char buffe[size][3]; // to store the image data

            for (i = 0; i < size; i++)
            {
                r = 0;
                g = 0;
                b = 0;
                buffe[i][2] = getc(fIn); // blue
                buffe[i][1] = getc(fIn); // green
                buffe[i][0] = getc(fIn); // red

                // conversion formula of rgb to sepia
                r = (buffe[i][0] * 0.393) + (buffe[i][1] * 0.769) + (buffe[i][2] * 0.189);
                g = (buffe[i][0] * 0.349) + (buffe[i][1] * 0.686) + (buffe[i][2] * 0.168);
                b = (buffe[i][0] * 0.272) + (buffe[i][1] * 0.534) + (buffe[i][2] * 0.131);

                if (r > MAX_VALUE)
                { // if value exceeds
                    r = MAX_VALUE;
                }
                if (g > MAX_VALUE)
                {
                    g = MAX_VALUE;
                }
                if (b > MAX_VALUE)
                {
                    b = MAX_VALUE;
                }
                putc(b, fOut);
                putc(g, fOut);
                putc(r, fOut);
            }

            fclose(fOut);
            fclose(fIn);

            stop = clock();
            printf("\nCLOCKS_PER_SEC = %ld\n", stop - start);
            printf("%lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }

        else if (choice == 7)
        { // Copy Image
            // Implement your code here
            clock_t start, stop;

            start = clock(); // Note the start time for profiling purposes.

            FILE *fo = fopen("images/lena_copy.bmp", "wb"); // Output File name

            int i;

            FILE *streamIn;
            streamIn = fopen("images/lena512.bmp", "r"); // Input file name

            if (streamIn == (FILE *)0) // check if the input file has not been opened succesfully.
            {
                printf("File opening error ocurred. Exiting program.\n");
                exit(0);
            }

            unsigned char header[54];       // to store the image header
            unsigned char colorTable[1024]; // to store the colorTable, if it exists.

            int count = 0;
            for (i = 0; i < 54; i++)
            {
                header[i] = getc(streamIn); // strip out BMP header
            }
            int width = *(int *)&header[18];    // read the width from the image header
            int height = *(int *)&header[22];   // read the height from the image header
            int bitDepth = *(int *)&header[28]; // read the bitDepth from the image header

            if (bitDepth <= 8)
                fread(colorTable, sizeof(unsigned char), 1024, streamIn);

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            fwrite(header, sizeof(unsigned char), 54, fo); // write the image header to output file

            unsigned char buf[height * width]; // to store the image data

            fread(buf, sizeof(unsigned char), (height * width), streamIn);

            if (bitDepth <= 8)
                fwrite(colorTable, sizeof(unsigned char), 1024, fo);

            fwrite(buf, sizeof(unsigned char), (height * width), fo);

            fclose(fo);
            fclose(streamIn);

            stop = clock();

            printf("Time: %lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }

        else if (choice == 8)
        { // Darken Image
            // Implement your code here
            FILE *fIn = fopen("lena512.bmp", "r");     // Input File name
            FILE *fOut = fopen("lena_dark.bmp", "w+"); // Output File name

            int i;
            unsigned char byte[54], colorTable[1024];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            if (bitDepth <= 8) // if ColorTable present, extract it.
            {
                fread(colorTable, sizeof(unsigned char), 1024, fIn);
                fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
            }

            unsigned char buffer[size]; // to store the image data

            fread(buffer, sizeof(unsigned char), size, fIn); // read image data

            for (i = 0; i < size; i++) // decreasing pixel values to get image bright
            {
                if (buffer[i] > THRESHOLD)
                    buffer[i] = buffer[i] - THRESHOLD;
            }

            fwrite(buffer, sizeof(unsigned char), size, fOut); // write back to the output image

            fclose(fIn);
            fclose(fOut);
            break;
        }

        else if (choice == 9)
        {
            rotate(); // Rotate Image
            break;
        }

        else if (choice == 10)
        { // Negative Image
            clock_t start, stop;
            start = clock();
            FILE *fp = fopen("bb.bmp", "rb"); // read the file//

            unsigned char *imageData;       // to store the image information
            unsigned char *newimageData;    // to store the new image information, i.e. the negative image
            unsigned char imageHeader[54];  // to get the image header
            unsigned char colorTable[1024]; // to get the colortable

            int i, j; // loop counter variables

            fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

            // extract image height and width from imageHeader
            int width = *(int *)&imageHeader[18];
            int height = *(int *)&imageHeader[22];
            int bitDepth = *(int *)&imageHeader[28];

            int imgDataSize = width * height; // calculate image size

            imageData = (unsigned char *)malloc(imgDataSize * sizeof(unsigned char)); // allocate the block of memory as big as the image size
            newimageData = (unsigned char *)malloc(imgDataSize * sizeof(unsigned char));

            if (bitDepth <= 8)                                      // COLOR TABLE Present
                fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

            fread(imageData, sizeof(unsigned char), imgDataSize, fp);

            // Calculate the mean of the image
            for (i = 0; i < height; i++)
            {
                for (j = 0; j < width; j++)
                {
                    newimageData[i * width + j] = 255 - imageData[i * width + j];
                }
            }

            FILE *fo = fopen("images/lena_negative.bmp", "wb");

            fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back.

            if (bitDepth <= 8)                                       // COLOR TABLE Present
                fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

            fwrite(newimageData, sizeof(unsigned char), imgDataSize, fo); // write the values of the negative image.

            fclose(fo);
            fclose(fp);
            stop = clock();
            double d = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
            printf("%lf\n", d);
            // Implement your code here
            break;
        }

        else
        {
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 10);

    return 0;
}
