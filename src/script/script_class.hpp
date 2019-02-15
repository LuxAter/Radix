#ifndef RADIX_SCRIPT_SCRIPT_CLASS_HPP_
#define RADIX_SCRIPT_SCRIPT_CLASS_HPP_

#include <map>
#include <string>
#include <vector>

#include <lua5.3/lua.hpp>

#include "../log.hpp"
#include "../sfinae/sfinae.hpp"

namespace radix {
namespace script {
  class Script {
   public:
    explicit Script(const std::string& file_name);

    ~Script();

    template <typename _T>
    inline _T get(const std::string& var) {
      if (!state_) return _T();
      _T result;
      int level;
      if ((level = lua_get_to_stack(var)) != -1) {
        result = lua_get<_T>();
        lua_pop(state_, level + 1);
      } else {
        result = _T();
      }
      return result;
    }

    template <typename _T>
    inline _T call(const std::string& func_name) {
      lua_get_to_stack(func_name);
      if (!lua_isfunction(state_, -1)) {
        log::Warning("Function \"%s\" is not found in \"%s\"",
                     func_name.c_str(), file_name_.c_str());
        return _T();
      }
      lua_call(state_, 0, 1);
      return lua_get<_T>();
    }
    template <typename _T, typename... _ARGS>
    inline _T call(const std::string& func_name, const _ARGS&... args) {
      lua_get_to_stack(func_name);
      if (!lua_isfunction(state_, -1)) {
        log::Warning("Function \"%s\" is not found in \"%s\"",
                     func_name.c_str(), file_name_.c_str());
        return _T();
      }
      call<0>(args...);
      return lua_get<_T>();
    }

   protected:
    int lua_get_to_stack(const std::string& var_name);

    template <typename _T>
    inline
        typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
        lua_get(int pos = -1) {
      if (lua_isnil(state_, pos)) {
        return _T();
      } else if (!lua_isstring(state_, pos)) {
        log::Warning("Value at position %i is a %s, not a string", pos,
                     lua_typename(state_, lua_type(state_, pos)));
        return _T();
      }
      return _T(lua_tostring(state_, pos));
    }
    template <typename _T>
    inline typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type
    lua_get(int pos = -1) {
      if (lua_isnil(state_, pos)) {
        return _T();
      } else if (!lua_isnumber(state_, pos)) {
        log::Warning("Value at position %i is a %s, not a number", pos,
                     lua_typename(state_, lua_type(state_, pos)));
        return _T();
      }
      return static_cast<_T>(lua_tonumber(state_, pos));
    }
    template <typename _T>
    inline typename std::enable_if<sfinae::is_vector<_T>::value, _T>::type
    lua_get(int pos = -1) {
      _T vec;
      if (lua_isnil(state_, pos)) {
        return vec;
      } else if (!lua_istable(state_, pos)) {
        log::Warning("Value at position %i is a %s, not a table", pos,
                     lua_typename(state_, lua_type(state_, pos)));
        return vec;
      }
      lua_pushnil(state_);
      while (lua_next(state_, pos - 1)) {
        vec.push_back(lua_get<typename _T::value_type>());
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    }
    template <typename _T>
    inline typename std::enable_if<sfinae::is_array<_T>::value, _T>::type
    lua_get(int pos = -1) {
      _T arr;
      if (lua_isnil(state_, pos)) {
        return arr;
      } else if (!lua_istable(state_, pos)) {
        log::Warning("Value at position %i is a %s, not a table", pos,
                     lua_typename(state_, lua_type(state_, pos)));
        return arr;
      }
      lua_pushnil(state_);
      std::size_t i = 0;
      while (lua_next(state_, pos - 1) && i < arr.max_size()) {
        arr[i] = lua_get<typename _T::value_type>();
        i++;
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return arr;
    }
    template <typename _T>
    inline typename std::enable_if<sfinae::is_map<_T>::value, _T>::type lua_get(
        int pos = -1) {
      _T mapping;
      if (lua_isnil(state_, pos)) {
        return mapping;
      } else if (!lua_istable(state_, pos)) {
        log::Warning("Value at position %i is a %s, not a table", pos,
                     lua_typename(state_, lua_type(state_, pos)));
        return mapping;
      }
      lua_pushnil(state_);
      while (lua_next(state_, pos - 1)) {
        mapping[lua_get<typename _T::key_type>(-2)] =
            lua_get<typename _T::mapped_type>(-1);
        lua_pop(state_, 1);
      }
      return mapping;
    }

    template <typename _T>
    inline typename std::enable_if<std::is_same<_T, std::string>::value,
                                   void>::type
    lua_push(const _T& v) {
      lua_pushstring(state_, v.c_str());
    }
    template <typename _T>
    inline typename std::enable_if<std::is_array<_T>::value, void>::type
    lua_push(const _T& v) {
      lua_pushstring(state_, v);
    }
    template <typename _T>
    inline typename std::enable_if<std::is_arithmetic<_T>::value, void>::type
    lua_push(const _T& v) {
      lua_pushnumber(state_, v);
    }
    template <typename _T>
    inline typename std::enable_if<sfinae::is_vector<_T>::value, void>::type
    lua_push(const _T& v) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_push(i + 1);
        lua_push(v[i]);
        lua_settable(state_, -3);
      }
    }
    template <typename _T>
    inline typename std::enable_if<sfinae::is_array<_T>::value, void>::type
    lua_push(const _T& v) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_push(i + 1);
        lua_push(v[i]);
        lua_settable(state_, -3);
      }
    }
    template <typename _T>
    inline typename std::enable_if<sfinae::is_map<_T>::value, void>::type
    lua_push(const _T& v) {
      lua_newtable(state_);
      for (auto& it : v) {
        lua_push(it.first);
        lua_push(it.second);
        lua_settable(state_, -3);
      }
    }

   private:
    template <std::size_t _N, typename _U>
    inline void call(const _U& v) {
      lua_push(v);
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline void call(const _U& v, const _ARGS&... args) {
      lua_push(v);
      call<_N + 1>(args...);
    }
    std::string file_name_;
    lua_State* state_ = nullptr;
  };

}  // namespace script
}  // namespace radix

#endif  // RADIX_SCRIPT_SCRIPT_CLASS_HPP_
