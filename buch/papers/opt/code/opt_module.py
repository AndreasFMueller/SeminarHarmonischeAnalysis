import numpy as np
import matplotlib.pyplot as plt
import os


class OptFourier:
    output_path = "output"

    def __init__(self) -> None:
        self.frequency_scale = 10  # 2pi equals to frequency_scale * 2pi
        self.width = 20*int(self.frequency_scale*2*np.pi)
        self.height = self.width
        self.canvas = np.zeros((self.height, self.width), dtype=np.uint8)

    @classmethod
    def show_all(cls):
        plt.show()

    def add_wave(self, frequency, direction="x", dc=0, amplitude=50):
        """
        Add a sin wave to the canvas
        """

        if direction == "x":
            for x in range(self.width):
                intensity = dc + amplitude * \
                    np.sin(frequency * x / self.frequency_scale)
                self.canvas[:, x] = self.canvas[:, x] + intensity

        elif direction == "y":
            for y in range(self.height):
                intensity = dc + amplitude * \
                    np.sin(frequency * y / self.frequency_scale)
                self.canvas[y, :] = self.canvas[y, :] + intensity

        else:
            raise ValueError(
                f"Direction has to be x or y but is {direction}")

    def add_grid(self, a, b):
        """
        Add a grid to the canvas
        a is the material, b is the void
        """

        period = a + b

        for x in range(self.width):
            if (x % period) > b:
                self.canvas[:, x] = 255

        for y in range(self.height):
            if (y % period) > b:
                self.canvas[y, :] = 255

    def add_slit(self, slit_height, slit_width, quantity):
        """Add one or multiple slits to the canvas

        The single slit has a dimension of height*width and is repeated
        """

        start_y = int(self.height/2 - slit_height/2)
        end_y = int(self.height/2 + slit_height/2)

        period = 2*slit_width

        entire_width = slit_width * (2*quantity - 1)
        start_x = int(self.width/2 - entire_width/2)
        end_x = int(self.width/2 + entire_width/2)

        for x in range(start_x, end_x):
            if ((x-start_x) % period) < slit_width:
                self.canvas[start_y:end_y, x] = 255

    def show(self,
             name,
             x_width=100,
             y_width=100,
             vmax=6e7,
             omega=30,
             highpass=True):

        mm = 1/25.4
        plt.figure(name, figsize=(140*mm, 35*mm))
        plt.rcParams.update({'font.size': 10})
        plt.rcParams['font.family'] = 'Times New Roman'

        plt.subplots_adjust(left=0.1,
                            bottom=0.3,
                            right=.9,
                            top=.9,
                            wspace=0.5,
                            hspace=0.4)

        middle_x = self.width/2
        middle_y = self.height/2

        # Grayscale image of aperture
        plt.subplot(141)
        plt.imshow(self.canvas, cmap='gray')
        plt.xlabel("Originalbild")

        # FFT2, with configurable vmax, height and width
        plt.subplot(142)
        fourier = np.fft.fftshift(np.fft.fft2(self.canvas))
        plt.imshow(abs(fourier), cmap='gray', vmax=vmax)
        plt.xlim(int(middle_x - x_width/2), int(middle_x + x_width/2))
        plt.ylim(int(middle_y - y_width/2), int(middle_y + y_width/2))
        plt.xlabel("Spektrum")

        # FFT2 after filter
        plt.subplot(143)
        image_fourier_lowpass = image_filter(fourier, omega, highpass=highpass)
        plt.imshow(abs(image_fourier_lowpass), cmap="gray", vmax=vmax)
        plt.xlim(int(middle_x - x_width/2), int(middle_x + x_width/2))
        plt.ylim(int(middle_y - y_width/2), int(middle_y + y_width/2))

        if (highpass):
            plt.xlabel("Hochpass")
        else:
            plt.xlabel("Tiefpass")

        # Reconstructed image
        plt.subplot(144)
        image_reconstructed_lowpass = np.fft.ifft2(image_fourier_lowpass)
        plt.imshow(abs(image_reconstructed_lowpass), cmap="gray")
        plt.xlabel("Rücktransformation")

        # Create output folder structure if necessary
        if not os.path.isdir(self.output_path):
            os.makedirs(self.output_path)

        save_name = name.replace(" ", "").replace(",", "_").lower() + ".pdf"

        # Final actions
        plt.savefig(os.path.join(self.output_path, save_name),
                    format="pdf", dpi=300)


def image_filter(image, radius, highpass=True):
    image_modified = image.copy()
    size_x, size_y = image_modified.shape
    position_x = size_x / 2 - 0.5
    position_y = size_y / 2 - 0.5

    for x in range(size_x):
        for y in range(size_y):
            distance = np.sqrt((position_x - x)**2 + (position_y - y)**2)
            if ((highpass is False and radius < distance) or
                    (highpass is True and radius >= distance)):
                image_modified[x][y] = 0

    return image_modified
