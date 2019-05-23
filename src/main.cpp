#include "radix.hpp"

#include <array>
#include <iostream>
#include <string>

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

std::array<std::string, 255> scrollback;
unsigned max_id = 0;

std::string input() {
  unsigned id = 0;
  std::cout << "\033[36m>>>\033[0m " << std::flush;
  std::string result;
  uint32_t pos = 0;
  while (true) {
    int bytes = 0;
    bool wait = true;
    while (wait) {
      usleep(100);
      ioctl(0, FIONREAD, &bytes);
      wait = !bytes;
    }
    char ch = std::cin.get();
    if (ch == 10) {
      std::cout << '\n';
      break;
    } else if (ch == 127) {
      if (id != 0) {
        result = scrollback[id];
        id = 0;
      }
      if (result.size() > 0) {
        if (pos == 0) {
          result.pop_back();
          std::cout << "\033[D \033[D" << std::flush;
        } else {
          result.erase(result.size() - pos - 1, 1);
          std::cout << "\033[D" << result.substr(result.size() - pos) << ' ';
          for (int i = 0; i < pos + 1; ++i) {
            std::cout << "\033[D";
          }
          std::cout << std::flush;
        }
      }
    } else if (ch == 27) {
      if (bytes == 0) return "exit";
      ch = std::cin.get();
      if (ch == 91 && bytes > 1) {
        ch = std::cin.get();
        if (ch == 65 && id < max_id) {
          id++;
          std::cout << "\033[2K\033[G\033[36m>>>\033[0m " << scrollback[id]
                    << std::flush;
        } else if (ch == 66 && id > 0) {
          id--;
          if (id == 0) {
            std::cout << "\033[2K\033[G\033[36m>>>\033[0m " << result
                      << std::flush;
          } else {
            std::cout << "\033[2K\033[G\033[36m>>>\033[0m " << scrollback[id]
                      << std::flush;
          }
        } else if (ch == 67 && pos > 0) {
          std::cout << "\033[C" << std::flush;
          pos--;
        } else if (ch == 68 && (pos < result.size() ||
                                (id != 0 && pos < scrollback[id].size()))) {
          pos++;
          std::cout << "\033[D" << std::flush;
        }
      }
      return "exit";
    } else {
      if (id != 0) {
        result = scrollback[id];
        id = 0;
      }
      if (pos == 0) {
        result += ch;
        std::cout << ch << std::flush;
      } else {
        result.insert(result.end() - pos, ch);
        std::cout << result.substr(result.size() - pos - 1);
        for (int i = 0; i < pos; ++i) {
          std::cout << "\033[D";
        }
        std::cout << std::flush;
      }
    }
  }
  if (id != 0) {
    result = scrollback[id];
  }
  for (unsigned i = max_id; i > 0; --i) {
    if (i + 1 < 255) scrollback[i + 1] = scrollback[i];
  }
  if (max_id < 254) max_id++;
  scrollback[1] = result;
  return result;
}

int main(int argc, char* argv[]) {
  std::string line;
  struct termios term;
  tcgetattr(0, &term);
  term.c_lflag &= ~ECHO;
  term.c_lflag &= ~ICANON;
  tcsetattr(0, TCSANOW, &term);
  while ((line = input()) != "exit") {
    printf("%.15lf\n", radix::eval(line));
  }
  term.c_lflag |= ECHO;
  term.c_lflag |= ICANON;
  tcsetattr(0, TCSANOW, &term);
  return 0;
}
