#include <stdio.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

// mask function
void mask_image(unsigned char *background, unsigned char *foreground, unsigned char *forecast, int width, int height, int channel)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int diff = 0;
            for(int k = 0; k < channel; k++)
            {
                diff += abs(foreground[i*width*channel + j*channel + k]-background[i*width*channel + j*channel + k]);
            }
            if (diff > 150)
            {
                for (int k = 0; k < channel; k++)
                {
                    forecast[i*width*channel + j*channel + k] = foreground[i*width*channel + j*channel + k];
                }
            }
        }
    }
}


int main()
{
    // declare var
    int width, height, channel;
    char path_background[] = "./images/background.png";
    char path_foreground[] = "./images/foreground.png";
    char path_forecast[] = "./images/weather_forecast-resized.jpg";
    char path_save[] = "./images/output.png";

    //read image
    unsigned char *background = stbi_load(path_background, &width, &height, &channel, 0);
    unsigned char *foreground = stbi_load(path_foreground, &width, &height, &channel, 0);
    unsigned char *forecast = stbi_load(path_forecast, &width, &height, &channel, 0);
    if (background == NULL || foreground == NULL || forecast == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }

    printf ("W = %d\nH = %d\nC = %d\n" ,width, height, channel);

    // mask image
    mask_image (background, foreground, forecast, width, height, channel);
    
    // save image
    stbi_write_png (path_save, width, height, channel, forecast, width*channel);
    printf ("New image saved to %s\n", path_save);
}