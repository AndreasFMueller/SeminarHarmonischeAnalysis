import math
import os
import numpy
import matplotlib.pyplot as plot
import PIL as pil

# Relative to this file
input_path = "../images/harold_input.jpg"
output_path = "../images/"


def image_filter(image, radius, highpass=True):
    image_modified = image.copy()
    size_x, size_y = image_modified.shape
    position_x = size_x / 2 - 0.5
    position_y = size_y / 2 - 0.5

    for x in range(size_x):
        for y in range(size_y):
            distance = math.sqrt((position_x - x)**2 + (position_y - y)**2)
            if ((highpass is False and radius < distance) or
                    (highpass is True and radius >= distance)):
                image_modified[x][y] = 0

    return image_modified


# Try to read the picture and convert it to grey scale
try:
    image_input = pil.Image.open(input_path)
    image = image_input.convert("L")
    image_rgb = image_input.convert("RGB")
    print(f"Successfully loaded image from {input_path}")
except FileNotFoundError as exception:
    print(exception)
    exit()

# Create output folder structure if necessary
if not os.path.isdir(output_path):
    os.makedirs(output_path)

# Apply two dimensional fft
image_fourier = numpy.fft.fftshift(numpy.fft.fft2(image))

# Filter images
image_fourier_lowpass = image_filter(image_fourier, 30, False)
image_fourier_highpass = image_filter(image_fourier, 30, True)

# Apply inverse fft to all pictures
image_reconstructed_lowpass = numpy.fft.ifft2(image_fourier_lowpass)
image_reconstructed_highpass = numpy.fft.ifft2(image_fourier_highpass)

# Generate output files
plot.rcParams.update({'font.size': 18})
plot.imshow(image, cmap='gray')
plot.savefig(os.path.join(output_path, "harold_gray.png"))

plot.imshow(numpy.log(abs(image_fourier),
            where=abs(image_fourier) > 0), cmap='gray')
plot.savefig(os.path.join(output_path, "harold_fourier.png"))

plot.imshow(numpy.log(abs(image_fourier_lowpass),
            where=abs(image_fourier_lowpass) > 0), cmap='gray')
plot.savefig(os.path.join(output_path, "harold_fourier_lowpass.png"))

plot.imshow(numpy.log(abs(image_fourier_highpass),
            where=abs(image_fourier_highpass) > 0), cmap='gray')
plot.savefig(os.path.join(output_path, "harold_fourier_highpass.png"))

plot.imshow(abs(image_reconstructed_lowpass), cmap='gray')
plot.savefig(os.path.join(output_path, "harold_reconstructed_lowpass.png"))

plot.imshow(abs(image_reconstructed_highpass), cmap='gray')
plot.savefig(os.path.join(output_path, "harold_reconstructed_highpass.png"))

print(f"Saved all outputs to {output_path}")
