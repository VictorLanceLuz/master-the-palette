### Master the Palette

You’ve joined the dev team behind Palette++, a lightweight color-processing engine that drives everything from pixel-art games to LED mood lights. The team’s Color class already stores RGB values and can print or read hex codes, but designers want to combine, tweak, and compare colors with natural C++ syntax. Your mission is to overload the right operators so working with colors feels as intuitive as basic algebra. By the end, users will be able to blend two Color objects with `+`, brighten a shade with `++`, scale intensity with `*`, and much more—all while Palette++ keeps every channel in the valid 0-255 range.

## Index Colors Like an Array

Artists want to look directly into a `Color` object as if it were a three-slot array, so they need a writable `[]` operator.

First, declare the new operator in `Color.hpp`. Then, in `Color.cpp`, define the non-`const` overload for the `[]` operator so that:

- `0` returns the `redChannel`
- `1` returns the `greenChannel`
- `2` returns the `blueChannel`

Any other index should throw `std::out_of_range` with the message “Color index” to indicate where the issue happened.

Read-only contexts also need array-style access, so now add the `const` version of `[]`.

Declare the operator in `Color.hpp`, and then in `Color.cpp`, implement the `const` overload for the `[]` operator with the same switch logic, returning a copy of the channel value.

Open `main.cpp`. Print each of the three channels for the color `emerald` by using the `[]` operator. Confirm the values are `80` for the first channel, `200` for the second channel, and `120` for the third.

## Blend and Adjust Colors

Designers constantly blend colors to discover new hues. Overload `+` so two `Color`s mix like paints on a palette.

To do this, declare the new operator in `Color.hpp`. Then in `Color.cpp`, overload the `+` operator so that it takes in another `Color`, averages each channel of the two colors, and returns the blended color.

Sometimes a designer just wants to tweak a tint. Add a second `+` overload so three offsets can be applied at once, and declare it in `Color.hpp`.

In `Color.cpp`, implement the overload for the `+` operator that takes a three‑element `std::vector<int>` named `adjustments`. The vector’s three elements offset the red, green, and blue channels; if it’s shorter, treat missing values as 0. Compute `r`, `g`, and `b` by adding each adjustment (after a size check) to `redChannel`, `greenChannel`, and `blueChannel`, then return the resulting `Color`.

Make sure each channel in the new `+` operator overload stays within the valid 0–255 range.

There is an existing helper function for this in `ColorUtility.cpp`. It can be used with the `CLIP()` alias. For example, `CLIP(392)` would reduce the value to `255` and warn that the value was too high. Likewise, `CLIP(-92)` would increase the value to `0` and warn as well.

Use this function to clamp the calculated values and return the clamped `Color`.

Back in `main.cpp`, blend the `sunset` and `ocean` colors by adding them and storing the result in a new variable called `dusk`. Then print `dusk` to verify that its value is `#8e6a80`.

Still in `main.cpp`, create a vector of integers named `warmUp` with the values `30`, `-10`, `-10`. Then add this value to `dusk` and print the result to verify it’s `#ac6076`.

## Nudge Brightness Up or Down

Lighting artists asked for an easy way to brighten a color, so `++` should bump every channel up by one.

Declare the operator in `Color.hpp`, and then in `Color.cpp`, define the prefix `++` operator overload to add 1 to every channel. Remember to clamp each result using `CLIP()` and return `*this`.

`--` should dim a shade by a single step whenever a scene needs to be toned down.

Add this new operator to `Color.hpp`. Then, back in `Color.cpp`, define the prefix `--` operator overload to subtract 1 from every channel. Use `CLIP()` and return `*this`.

In `main.cpp`, take `dusk` and increment it with the prefix `++` operator and print the result.

In `main.cpp`, take `sunset` and decrement it with the prefix `--` operator and print the result.

## Scale Intensity and Apply Custom Transforms

Designers fade entire palettes in and out, so multiplying a `Color` must scale every channel in unison.

First, add the new operator to `Color.hpp`. Then, in `Color.cpp`, overload the `*` operator so that each channel is multiplied by an integer `scale`, clamped, and then return the scaled color..

In `Color.hpp`, declare this signature to add a functor to the `Color` class:

```C++
Color operator()(int (*transform)(int)) const;
```

Then implement this overload in `Color.cpp` by applying the provided function to every channel, clamping the results with `CLIP()`, and returning the transformed color.

In `main.cpp`, create a new `Color` named `duskBoost` that scales `dusk` by 2. Then, print `duskBoost`.

Still in `main.cpp`, use your functor to print the inverse of `dusk` using `ColorUtility::invert()`.

## Compare Colors

At last, designers need to know when two colors are truly identical. Overload `==` to compare all three channels exactly.

Declare the new operator in `Color.hpp`. Then in `Color.cpp`, overload the `==` operator so it returns `true` only when all three channels match exactly.

In `main.cpp`, compare `dusk` and `duskBoost` with `==`, and then print the boolean results to confirm that the comparison is `false`.

## Congratulations!

Time to celebrate! Your `Color` class now overloads indexing, arithmetic, increment, scaling, transformation, and comparison operators. Designers can mix and manipulate colors with simple, readable code, and you’ve mastered operator overloading in C++. Great job!

Want to level it up even more? Why not try adding these to your `Color` class:

- Teach your colors to change themselves. Add in-place operators like `+=`, `-=`, and `*=` so you can increment a shade without creating a brand-new object—e.g. `accent *= 0.8;` instantly makes it 20% darker.
- Help colors line up in order. Overload `<`, `<=`, `>`, and `>=` to give each color a sense of “lighter than” or “darker than.” That way you can sort entire palettes, drop colors into ordered maps, or quickly grab the brightest tint in a list.

A few lines of code, and your `Color` class gets even handier!
