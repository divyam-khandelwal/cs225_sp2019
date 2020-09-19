/**
 * @file lab_intro.cpp
 * Implementations of image manipulation functions.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using cs225::HSLAPixel;
using cs225::PNG;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image)
{
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++)
  {
    for (unsigned y = 0; y < image.height(); y++)
    {
      HSLAPixel &pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}

/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY)
{

  for (unsigned x = 0; x < image.width(); x++)
  {
    for (unsigned y = 0; y < image.height(); y++)
    {
      HSLAPixel &pixel = image.getPixel(x, y);

      double euclidean_distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));

      double luminance_drop = 0.2;
      if (euclidean_distance < 160.0)
      {
        luminance_drop = 1 - euclidean_distance * .5 / 100;
      }

      pixel.l = pixel.l * luminance_drop;
    }
  }

  return image;
}

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image)
{

  const int orange_hue = 11;
  const int blue_hue = 216;

  for (unsigned x = 0; x < image.width(); x++)
  {
    for (unsigned y = 0; y < image.height(); y++)
    {
      HSLAPixel &pixel = image.getPixel(x, y);

      double orange_hue_diff = std::min(std::abs(pixel.h - orange_hue), std::abs(pixel.h - 360 - orange_hue));
      double blue_hue_diff = std::min(std::abs(pixel.h - blue_hue), std::abs(pixel.h - 360 - blue_hue));

      if (orange_hue_diff < blue_hue_diff) {
        pixel.h = orange_hue;
      } else {
        pixel.h = blue_hue;
      }
    }
  }

  return image;
}

/**
* Returns an image that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage)
{

  cs225::PNG watermark;
  watermark = PNG(secondImage);
  watermark.resize(firstImage.width(), firstImage.height());

  for (unsigned x = 0; x < firstImage.width(); x++)
  {
    for (unsigned y = 0; y < firstImage.height(); y++)
    {

      HSLAPixel &watermarkPixel = watermark.getPixel(x, y);
      if (watermarkPixel.l == 1.0)
      {
        HSLAPixel &imagePixel = firstImage.getPixel(x, y);
        imagePixel.l = std::min(1.0, imagePixel.l + 0.2);
      }
    }
  }
  return firstImage;
}
