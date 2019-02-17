#include "script_class.hpp"
#include "../log.hpp"

radix::script::Script::Script(const std::string& file_name) {
  state_ = luaL_newstate();
  luaL_openlibs(state_);
  if (!file_name.compare(0, 4, "%lua")) {
    std::string script = file_name;
    script.erase(0, script.find('\n') + 1);
    if (luaL_loadstring(state_, script.c_str()) || lua_pcall(state_, 0, 0, 0)) {
      log::Error("Failed to read user entered lua script");
      state_ = nullptr;
    }
    file_name_ = "User Script";
  } else {
    if (luaL_loadfile(state_, file_name.c_str()) ||
        lua_pcall(state_, 0, 0, 0)) {
      log::Error("Failed to load Lua file \"%s\"", file_name.c_str());
      state_ = nullptr;
    }
    file_name_ = file_name;
  }
}

radix::script::Script::~Script() {
  if (state_) lua_close(state_);
  state_ = nullptr;
}

int radix::script::Script::lua_get_to_stack(const std::string& var_name) {
  int level = 0;
  std::string var = "";
  for (unsigned i = 0; i < var_name.size(); ++i) {
    if (var_name.at(i) == '.') {
      if (level == 0) {
        lua_getglobal(state_, var.c_str());
      } else {
        lua_getfield(state_, -1, var.c_str());
      }

      if (lua_isnil(state_, -1)) {
        return -1;
      } else {
        var = "";
        level++;
      }
    } else {
      var += var_name.at(i);
    }
  }
  if (level == 0) {
    lua_getglobal(state_, var.c_str());

  } else {
    lua_getfield(state_, -1, var.c_str());
  }
  if (lua_isnil(state_, -1)) {
    return -1;
  }
  return level;
}
