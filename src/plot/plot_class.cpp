#include "plot_class.hpp"

#include <limits>
#include <string>
#include <vector>

#include <cstdlib>
#include <cstring>

#include "../log.hpp"

radix::plot::Figure::Figure()
    : title(""),
      xlabel(""),
      ylabel(""),
      xlim({{-std::numeric_limits<double>::infinity(),
             std::numeric_limits<double>::infinity()}}),
      ylim({{-std::numeric_limits<double>::infinity(),
             std::numeric_limits<double>::infinity()}}),
      margins({{0.1, 0.1, 0.1, 0.1}}),
      grid_(false) {}

void radix::plot::Figure::plot(std::vector<double> x_data,
                               std::vector<double> y_data, std::string style) {
  plot_vector_.push_back({x_data, y_data, style});
}

void radix::plot::Figure::scatter(std::vector<double> x_data,
                                  std::vector<double> y_data,
                                  std::string style) {
  if (!style.compare(0, 1, "s")) style = 's' + style;
  plot_vector_.push_back({x_data, y_data, style});
}

bool radix::plot::Figure::bmp(const std::string& file_name,
                              const unsigned img_width,
                              const unsigned img_height) {
  unsigned file_size = 54 + 3 * img_width * img_height;

  uint32_t** buffer = (uint32_t**)std::malloc(img_height * sizeof(uint32_t*));
  for (unsigned i = 0; i < img_height; ++i) {
    buffer[i] = (uint32_t*)std::malloc(img_width * sizeof(uint32_t));
    for (unsigned j = 0; j < img_height; ++j) {
      buffer[i][j] = 0xffffff;
    }
  }

  generate_byte_map(buffer, img_width, img_height);

  uint8_t* byte_data = (uint8_t*)std::malloc(3 * img_width * img_height);
  if (byte_data == NULL) {
    return false;
  }
  std::memset(byte_data, 0, 3 * img_width * img_height);
  for (unsigned x = 0; x < img_width; ++x) {
    for (unsigned y = 0; y < img_height; ++y) {
      unsigned x_ind = x, y_ind = (img_height - 1) - y;
      uint8_t r = ((buffer[y][x] >> 16) & 0XFF);
      uint8_t g = ((buffer[y][x] >> 8) & 0XFF);
      uint8_t b = ((buffer[y][x]) & 0XFF);
      byte_data[(x_ind + y_ind * img_width) * 3 + 0] = b;
      byte_data[(x_ind + y_ind * img_width) * 3 + 1] = g;
      byte_data[(x_ind + y_ind * img_width) * 3 + 2] = r;
    }
  }

  unsigned char file_header[14] = {'B', 'M', 0, 0,  0, 0, 0,
                                   0,   0,   0, 54, 0, 0, 0};
  unsigned char info_header[40] = {40, 0, 0, 0, 0, 0, 0,  0,
                                   0,  0, 0, 0, 1, 0, 24, 0};
  unsigned char pad[3] = {0, 0, 0};

  file_header[2] = (unsigned char)(file_size);
  file_header[3] = (unsigned char)(file_size >> 8);
  file_header[4] = (unsigned char)(file_size >> 14);
  file_header[5] = (unsigned char)(file_size >> 24);

  info_header[4] = (unsigned char)(img_width);
  info_header[5] = (unsigned char)(img_width >> 8);
  info_header[6] = (unsigned char)(img_width >> 16);
  info_header[7] = (unsigned char)(img_width >> 24);
  info_header[8] = (unsigned char)(img_height);
  info_header[9] = (unsigned char)(img_height >> 8);
  info_header[10] = (unsigned char)(img_height >> 16);
  info_header[11] = (unsigned char)(img_height >> 24);

  FILE* out = fopen(file_name.c_str(), "wb");
  if (out == NULL) {
    free(byte_data);
    return false;
  }
  fwrite(file_header, 1, 14, out);
  fwrite(info_header, 1, 40, out);
  for (unsigned i = 0; i < img_height; ++i) {
    fwrite(byte_data + (img_width * (img_height - i - 1) * 3), 3, img_width,
           out);
    fwrite(pad, 1, (4 - (img_width * 3) % 4) % 4, out);
    free(buffer[i]);
  }
  free(byte_data);
  free(buffer);
  fclose(out);
  return true;
}

void radix::plot::Figure::generate_byte_map(uint32_t** bytes,
                                            const unsigned img_width,
                                            const unsigned img_height) {
  // Draw bounding box
  unsigned a = img_height * margins[2], b = img_height * (1.0 - margins[3]);
  for (unsigned x = img_width * margins[0] - 1;
       x <= img_width * (1.0 - margins[1]) + 1; ++x) {
    bytes[a][x] = 0x000000;
    bytes[b][x] = 0x000000;
    bytes[a - 1][x] = 0x000000;
    bytes[b + 1][x] = 0x000000;
  }
  a = img_width * margins[0];
  b = img_width * (1.0 - margins[1]);
  for (unsigned y = img_height * margins[2] - 1;
       y <= img_height * (1.0 - margins[3]) + 1; ++y) {
    bytes[y][a] = 0x000000;
    bytes[y][b] = 0x000000;
    bytes[y][a - 1] = 0x000000;
    bytes[y][b + 1] = 0x000000;
  }

  // Draw grid

  // Draw plot arrays
  for(auto& arr : plot_array_){

  }
  
  // Draw plot vectors
  for(auto& vec : plot_vector_){

  }
}
