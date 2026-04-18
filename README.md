# pixcii
A minimal, lightweight C++ tool to convert images to ASCII art.

## Dependencies

- C++ compiler (e.g., `g++`)
- `make`

*(Note: The project uses the `stb_image.h` header-only library, which is included in the source codebase.)*

## Building

To compile the tool, simply run:

```bash
make
```

## Usage

```bash
./pixcii <image_path> [output_width]
```

- `<image_path>`: Path to the input image file (e.g. `image.png`, `photo.jpg`).
- `[output_width]`: (Optional) Desired width of the ASCII output in characters. Defaults to 100.

**Example:**
```bash
./pixcii sample.jpg 80
```
