#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cmath>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile)
{
  // TODO: Part 2

  // Read input file as PNG
  PNG inputImage;
  inputImage.readFromFile(inputFile);

  unsigned int imageHeight = inputImage.height();
  unsigned int imageWidth = inputImage.width();

  unsigned int midHeight = imageHeight / 2;
  unsigned int midWidth = imageWidth / 2;

  // Create output PNG
  PNG outputImage(imageWidth, imageHeight);

  int y_diff, x_diff, y_mapped, x_mapped;
  HSLAPixel inputPixel;

  for (unsigned x = 0; x < imageWidth; x++)
  {
    for (unsigned y = 0; y < imageHeight; y++)
    {

      // Creates a copy of the pixel - this is NOT a reference to the original pixel
      inputPixel = inputImage.getPixel(x, y);

      // 1st quadrant
      if (y < midHeight && x < midWidth)
      {
        y_diff = midHeight - y;
        x_diff = midWidth - x;
        y_mapped = (imageHeight % 2 == 0) ? midHeight + y_diff - 1 : midHeight + y_diff;
        x_mapped = (imageWidth % 2 == 0) ? midWidth + x_diff - 1 : midWidth + x_diff;

        // 2nd quadrant
      }
      else if (y < midHeight && x >= midWidth)
      {
        y_diff = midHeight - y;
        x_diff = x - midWidth;
        y_mapped = (imageHeight % 2 == 0) ? midHeight + y_diff - 1 : midHeight + y_diff;
        x_mapped = (imageWidth % 2 == 0) ? midWidth - x_diff - 1 : midWidth - x_diff;

        // 3rd quadrant
      }
      else if (y >= midHeight && x >= midWidth)
      {
        y_diff = y - midHeight;
        x_diff = x - midWidth;
        y_mapped = (imageHeight % 2 == 0) ? midHeight - y_diff - 1 : midHeight - y_diff;
        x_mapped = (imageWidth % 2 == 0) ? midWidth - x_diff - 1 : midWidth - x_diff;

        // 4th quadrant
      }
      else
      {
        y_diff = y - midHeight;
        x_diff = midWidth - x;
        y_mapped = (imageHeight % 2 == 0) ? midHeight - y_diff - 1 : midHeight - y_diff;
        x_mapped = (imageWidth % 2 == 0) ? midWidth + x_diff - 1 : midWidth + x_diff;
      }

      HSLAPixel &outputPixel = outputImage.getPixel(x_mapped, y_mapped);
      outputPixel = inputPixel;
    }
  }

  outputImage.writeToFile(outputFile);
}

float euclid_dist(float x_o, float y_o, float x_1, float y_1)
{
  return sqrt((x_o - x_1) * (x_o - x_1) + (y_o - y_1) * (y_o - y_1));
}

cs225::PNG myArt(unsigned int width, unsigned int height)
{
  cs225::PNG png(width, height);
  // TODO: Part 3

  float midWidth = width / 2;
  float midHeight = height / 2;

  for (unsigned x = 0; x < width; x++)
  {
    for (unsigned y = 0; y < height; y++)
    {
      HSLAPixel &pixel = png.getPixel(x, y);
      pixel.l = 0.6;
      pixel.a = 1.0;
      pixel.s = 0.8;

      float dist = euclid_dist(x, y, midWidth, midHeight);
      float hue = std::fmod(200 + dist * 20, 360);
      pixel.h = hue;
    }
  }
  return png;
}
