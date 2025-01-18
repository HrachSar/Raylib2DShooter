//
// Created by hrach on 1/6/25.
//

#ifndef PERLIN_H
#define PERLIN_H
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <random>

#define NOICE_SCALE 0.1f

class PerlinNoise {
private:
    std::vector<int> permutation;

    static float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static float lerp(float t, float a, float b) {
        return a + t * (b - a);
    }

    static float grad(int hash, double x, double y) {
        // 2D gradient computation
        int h = hash & 7; // Only take 3 bits (0-7)
        float u = h < 4 ? x : y;
        float v = h < 4 ? y : x;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

public:
    PerlinNoise(unsigned int seed = 0) {
        // Generate a random permutation based on the seed
        permutation.resize(256);
        std::iota(permutation.begin(), permutation.end(), 0);

        std::default_random_engine engine(seed);
        std::shuffle(permutation.begin(), permutation.end(), engine);

        // Duplicate the permutation vector for overflow
        permutation.insert(permutation.end(), permutation.begin(), permutation.end());
    }

    float noise(float x, float y) {
        // Find the unit grid cell containing the point
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        // Relative position within the cell
        x -= std::floor(x);
        y -= std::floor(y);

        // Compute fade curves for x and y
        float u = fade(x);
        float v = fade(y);

        // Hash coordinates of the four cell corners
        int A = permutation[X] + Y;
        int B = permutation[X + 1] + Y;

        // Interpolate between the gradients at the corners
        float result = lerp(v,
            lerp(u, grad(permutation[A], x, y), grad(permutation[B], x - 1, y)),
            lerp(u, grad(permutation[A + 1], x, y - 1), grad(permutation[B + 1], x - 1, y - 1))
        );

        // Normalize the result to the range [0, 1]
        return (result + 1.0f) / 2.0f;
    }
};

#endif //PERLIN_H
