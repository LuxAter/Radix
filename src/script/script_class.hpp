#ifndef RADIX_SCRIPT_SCRIPT_CLASS_HPP_
#define RADIX_SCRIPT_SCRIPT_CLASS_HPP_

#include <stdarg.h>
#include <lua5.3/lua.hpp>
#include <string>
#include <vector>

#include "../log.hpp"
#include "../sfinae/sfinae.hpp"

namespace radix {
namespace script {
  class Script {
   public:
    explicit Script(const std::string& file_name);

    ~Script();

    template <typename _T>
    typename std::enable_if<sfinae::is_vector<_T>::value, _T>::type get(
        const std::string& var) {
      if (!state_) {
        return _T();
      }
      _T result;
      int level;
      if ((level = lua_get_to_stack(var)) != -1) {
        result = lua_get_vector<typename _T::value_type>(var);
        lua_pop(state_, level + 1);
      } else {
        result = _T();
      }
      return result;
    }

    template <typename _T>
    typename std::enable_if<!sfinae::is_vector<_T>::value, _T>::type get(
        const std::string& var) {
      if (!state_) {
        return _T();
      }
      _T result;
      int level;
      if ((level = lua_get_to_stack(var)) != -1) {
        result = lua_get<_T>(var);
        lua_pop(state_, level + 1);
      } else {
        result = _T();
      }
      return result;
    }

    template <typename _T>
    typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type call(
        const std::string& func_name) {
      lua_getglobal(state_, func_name.c_str());
      lua_call(state_, 0, 1);
      if (!lua_isnumber(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a number type",
            func_name.c_str(), file_name_.c_str());
      }
      return static_cast<_T>(lua_tonumber(state_, -1));
    }
    template <typename _T, typename... _ARGS>
    typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type call(
        const std::string& func_name, const _ARGS&... args) {
      lua_getglobal(state_, func_name.c_str());
      call<0>(args...);
      if (!lua_isnumber(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a number type",
            func_name.c_str(), file_name_.c_str());
      }
      return static_cast<_T>(lua_tonumber(state_, -1));
    }
    template <typename _T>
    typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
    call(const std::string& func_name) {
      lua_getglobal(state_, func_name.c_str());
      lua_call(state_, 0, 1);
      if (!lua_isstring(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a string type",
            func_name.c_str(), file_name_.c_str());
      }
      return _T(lua_tostring(state_, -1));
    }
    template <typename _T, typename... _ARGS>
    typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
    call(const std::string& func_name, const _ARGS&... args) {
      lua_getglobal(state_, func_name.c_str());
      call<0>(args...);
      if (!lua_isstring(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a string type",
            func_name.c_str(), file_name_.c_str());
      }
      return _T(lua_tostring(state_, -1));
    }

   protected:
    int lua_get_to_stack(const std::string& var_name);

    template <typename _T>
    inline typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type
    lua_get(const std::string& var) {
      return static_cast<_T>(lua_tonumber(state_, -1));
    }
    template <typename _T>
    inline typename std::enable_if<std::is_same<_T, bool>::value, _T>::type
    lua_get(const std::string& var) {
      return static_cast<bool>(lua_toboolean(state_, -1));
    }

    template <typename _T>
    std::vector<_T> lua_get_vector(const std::string& var) {
      std::vector<_T> vec;
      lua_getglobal(state_, var.c_str());
      if (lua_isnil(state_, -1)) {
        return vec;
      }
      lua_pushnil(state_);
      while (lua_next(state_, -2)) {
        vec.push_back(lua_get<_T>(var));
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    }

    template <typename _T>
    inline
        typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
        lua_get(const std::string& var) {
      std::string s = "null";
      if (lua_isstring(state_, -1)) {
        s = std::string(lua_tostring(state_, -1));
      }
      return s;
    }

   private:
    template <std::size_t _N, typename _U>
    inline typename std::enable_if<std::is_arithmetic<_U>::value, void>::type
    call(const _U& v) {
      lua_pushnumber(state_, v);
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U>
    inline typename std::enable_if<std::is_same<_U, std::string>::value,
                                   void>::type
    call(const _U& v) {
      lua_pushstring(state_, v);
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U>
    inline typename std::enable_if<std::is_same<_U, bool>::value, void>::type
    call(const _U& v) {
      lua_pushboolean(state_, v);
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<std::is_arithmetic<_U>::value, void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_pushnumber(state_, v);
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<std::is_same<_U, std::string>::value,
                                   void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_pushstring(state_, v);
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<std::is_same<_U, bool>::value, void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_pushboolean(state_, v);
      call<_N + 1>(args...);
    }

    std::string file_name_;
    lua_State* state_ = nullptr;
  };

}  // namespace script
}  // namespace radix

#endif  // RADIX_SCRIPT_SCRIPT_CLASS_HPP_
