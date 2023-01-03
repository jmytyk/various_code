#chatgpt output, unknown if this works

import numpy as np

# Measured values of linear light intensity
linear_intensities = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

# Compute the CIE 1931 chromaticity coordinates for each linear intensity
chromaticity_coords = []
for intensity in linear_intensities:
    # Compute the chromaticity coordinates for the current intensity
    # (assume a hypothetical light source with a fixed spectral power distribution)
    x, y = compute_chromaticity_coords(intensity)
    chromaticity_coords.append((x, y))

# Use the chromaticity coordinates to compute the perceived intensity of each light
perceived_intensities = []
for coords in chromaticity_coords:
    # Compute the perceived intensity using the CIE 1931 luminosity function
    perceived_intensity = cie1931_luminosity_function(coords[0], coords[1])
    perceived_intensities.append(perceived_intensity)

# Create a look-up table using the computed perceived intensities
lookup_table = {}
for i in range(len(linear_intensities)):
    lookup_table[linear_intensities[i]] = perceived_intensities[i]

# Use the look-up table to convert a linear intensity value to a perceived intensity value
linear_intensity = 25
perceived_intensity = lookup_table[linear_intensity]



def cie1931_luminosity_function(luminosity):
    # Create a spline interpolation function using measured values of perceived intensity
    luminosity_values = [0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    perceived_intensity_values = [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
    
    # Compute the knots and coefficients of the spline
    num_knots = len(luminosity_values)
    knots = [0.0] * num_knots
    coefs = [0.0] * num_knots
    for i in range(num_knots):
        if i == 0:
            knots[i] = luminosity_values[i]
            coefs[i] = perceived_intensity_values[i]
        elif i == num_knots - 1:
            knots[i] = luminosity_values[i]
            coefs[i] = perceived_intensity_values[i]
        else:
            knots[i] = luminosity_values[i]
            coefs[i] = (perceived_intensity_values[i+1] - perceived_intensity_values[i-1]) / (luminosity_values[i+1] - luminosity_values[i-1])
    
    # Create the look-up table
    lookup_table = [0] * 1024
    for i in range(1024):
        luminosity = i / 1023.0
        index = -1
        for j in range(num_knots):
            if luminosity < knots[j]:
                index = j
                break
        if index == -1:
        # Use the spline interpolation function to map the luminosity value to a perceived intensity value
        if index == 0:
            perceived_intensity = coefs[index] * (luminosity - knots[index]) + perceived_intensity_values[index]
        elif index == num_knots - 1:
            perceived_intensity = coefs[index-1] * (luminosity - knots[index-1]) + perceived_intensity_values[index-1]
        else:
            perceived_intensity = coefs[index-1] * (luminosity - knots[index-1]) + perceived_intensity_values[index-1]
        lookup_table[i] = perceived_intensity
    return lookup_table

# Use the look-up table to convert a luminosity value to a perceived intensity value
luminosity = 0.25
lookup_table = cie1931_luminosity_function(luminosity)
perceived_intensity = lookup_table[int(luminosity * 1023)]
