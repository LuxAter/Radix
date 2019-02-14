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
    typename std::enable_if<sfinae::is_map<_T>::value, _T>::type get(
        const std::string& var) {
      if (!state_) {
        return _T();
      }
      _T result;
      int level;
      if ((level = lua_get_to_stack(var)) != -1) {
        result =
            lua_get_map<typename _T::key_type, typename _T::mapped_type>(var);
        lua_pop(state_, level + 1);
      } else {
        result = _T();
      }
      return result;
    }

    template <typename _T>
    typename std::enable_if<
        !sfinae::is_vector<_T>::value && !sfinae::is_map<_T>::value, _T>::type
    get(const std::string& var) {
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
      lua_get_to_stack(func_name);
      if (!lua_isfunction(state_, -1)) {
        log::Warning("Function \"%s\" is not found in \"%s\"",
                     func_name.c_str(), file_name_.c_str());
        return _T();
      }
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
      lua_get_to_stack(func_name);
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
      lua_get_to_stack(func_name);
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
      lua_get_to_stack(func_name);
      call<0>(args...);
      if (!lua_isstring(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a string type",
            func_name.c_str(), file_name_.c_str());
      }
      return _T(lua_tostring(state_, -1));
    }

    template <typename _T>
    typename std::enable_if<sfinae::is_vector<_T>::value, _T>::type call(
        const std::string& func_name) {
      lua_get_to_stack(func_name);
      if (!lua_isfunction(state_, -1)) {
        log::Warning("Function \"%s\" is not found in \"%s\"",
                     func_name.c_str(), file_name_.c_str());
        return _T();
      }
      lua_call(state_, 0, 1);
      if (!lua_istable(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a table type",
            func_name.c_str(), file_name_.c_str());
      }
      return lua_get_vector<typename _T::value_type>();
    }
    template <typename _T, typename... _ARGS>
    typename std::enable_if<sfinae::is_vector<_T>::value, _T>::type call(
        const std::string& func_name, const _ARGS&... args) {
      lua_get_to_stack(func_name);
      call<0>(args...);
      if (!lua_istable(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a table type",
            func_name.c_str(), file_name_.c_str());
      }
      return lua_get_vector<typename _T::value_type>();
    }

    template <typename _T>
    typename std::enable_if<sfinae::is_map<_T>::value, _T>::type call(
        const std::string& func_name) {
      lua_get_to_stack(func_name);
      if (!lua_isfunction(state_, -1)) {
        log::Warning("Function \"%s\" is not found in \"%s\"",
                     func_name.c_str(), file_name_.c_str());
        return _T();
      }
      lua_call(state_, 0, 1);
      if (!lua_istable(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a table type",
            func_name.c_str(), file_name_.c_str());
      }
      return lua_get_map<typename _T::key_type, typename _T::mapped_type>();
    }
    template <typename _T, typename... _ARGS>
    typename std::enable_if<sfinae::is_map<_T>::value, _T>::type call(
        const std::string& func_name, const _ARGS&... args) {
      lua_get_to_stack(func_name);
      call<0>(args...);
      if (!lua_istable(state_, -1)) {
        log::Warning(
            "Result of Lua function \"%s\" from \"%s\" is not a table type",
            func_name.c_str(), file_name_.c_str());
      }
      return lua_get_map<typename _T::key_type, typename _T::mapped_type>();
    }

   protected:
    int lua_get_to_stack(const std::string& var_name);

    template <typename _T>
    inline typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type
    lua_get(int pos = -1) {
      return static_cast<_T>(lua_tonumber(state_, pos));
    }
    template <typename _T>
    inline
        typename std::enable_if<std::is_same<_T, std::string>::value, _T>::type
        lua_get(int pos = -1) {
      std::string s = "null";
      if (lua_isstring(state_, pos)) {
        s = std::string(lua_tostring(state_, pos));
      }
      return s;
    }

    template <typename _T>
    std::vector<_T> lua_get_vector() {
      std::vector<_T> vec;
      if (lua_isnil(state_, -1)) {
        return vec;
      }
      lua_pushnil(state_);
      while (lua_next(state_, -2)) {
        vec.push_back(lua_get<_T>());
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    }

    template <typename _T, typename _U>
    std::map<_T, _U> lua_get_map() {
      std::map<_T, _U> mapping;
      if (lua_isnil(state_, -1)) {
        return mapping;
      }
      lua_pushnil(state_);
      while (lua_next(state_, -2)) {
        mapping[lua_get<_T>(-2)] = lua_get<_U>(-1);
        lua_pop(state_, 1);
      }
      return mapping;
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
      lua_pushstring(state_, v.c_str());
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }

    template <std::size_t _N, typename _U>
    inline typename std::enable_if<
        sfinae::is_vector<_U>::value &&
            std::is_arithmetic<typename _U::value_type>::value,
        void>::type
    call(const _U& v) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_pushnumber(state_, i + 1);
        lua_pushnumber(state_, v[i]);
        lua_settable(state_, -3);
      }
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U>
    inline typename std::enable_if<
        sfinae::is_vector<_U>::value &&
            std::is_same<typename _U::value_type, std::string>::value,
        void>::type
    call(const _U& v) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_pushnumber(state_, i + 1);
        lua_pushstring(state_, v[i].c_str());
        lua_settable(state_, -3);
      }
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }

    template <std::size_t _N, typename _U>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_arithmetic<typename _U::key_type>::value &&
            std::is_arithmetic<typename _U::mapped_type>::value,
        void>::type
    call(const _U& v) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushnumber(state_, kv.first);
        lua_pushnumber(state_, kv.second);
        lua_settable(state_, -3);
      }
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_arithmetic<typename _U::key_type>::value &&
            std::is_same<typename _U::mapped_type, std::string>::value,
        void>::type
    call(const _U& v) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushnumber(state_, kv.first);
        lua_pushstring(state_, kv.second.c_str());
        lua_settable(state_, -3);
      }
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }

    template <std::size_t _N, typename _U>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_same<typename _U::key_type, std::string>::value &&
            std::is_arithmetic<typename _U::mapped_type>::value,
        void>::type
    call(const _U& v) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushstring(state_, kv.first.c_str());
        lua_pushnumber(state_, kv.second);
        lua_settable(state_, -3);
      }
      luaL_checkstack(state_, 1, "too many arguments");
      lua_call(state_, _N + 1, 1);
    }
    template <std::size_t _N, typename _U>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_same<typename _U::key_type, std::string>::value &&
            std::is_same<typename _U::mapped_type, std::string>::value,
        void>::type
    call(const _U& v) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushstring(state_, kv.first.c_str());
        lua_pushstring(state_, kv.second.c_str());
        lua_settable(state_, -3);
      }
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
      lua_pushstring(state_, v.c_str());
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<
        sfinae::is_vector<_U>::value &&
            std::is_arithmetic<typename _U::value_type>::value,
        void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_pushnumber(state_, i + 1);
        lua_pushnumber(state_, v[i]);
        lua_settable(state_, -3);
      }
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<
        sfinae::is_vector<_U>::value &&
            std::is_same<typename _U::value_type, std::string>::value,
        void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_newtable(state_);
      for (std::size_t i = 0; i < v.size(); ++i) {
        lua_pushnumber(state_, i + 1);
        lua_pushstring(state_, v[i].c_str());
        lua_settable(state_, -3);
      }
      call<_N + 1>(args...);
    }

    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_arithmetic<typename _U::key_type>::value &&
            std::is_arithmetic<typename _U::mapped_type>::value,
        void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushnumber(kv.first);
        lua_pushnumber(kv.second);
        lua_settable(state_, -3);
      }
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_arithmetic<typename _U::key_type>::value &&
            std::is_same<typename _U::mapped_type, std::string>::value,
        void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushnumber(kv.first);
        lua_pushstring(kv.second.c_str());
        lua_settable(state_, -3);
      }
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_same<typename _U::key_type, std::string>::value &&
            std::is_arithmetic<typename _U::mapped_type>::value,
        void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushstring(kv.first.c_str());
        lua_pushnumber(kv.second);
        lua_settable(state_, -3);
      }
      call<_N + 1>(args...);
    }
    template <std::size_t _N, typename _U, typename... _ARGS>
    inline typename std::enable_if<
        sfinae::is_map<_U>::value &&
            std::is_same<typename _U::key_type, std::string>::value &&
            std::is_same<typename _U::mapped_type, std::string>::value,
        void>::type
    call(const _U& v, const _ARGS&... args) {
      lua_newtable(state_);
      for (auto& kv : v) {
        lua_pushstring(kv.first.c_str());
        lua_pushstring(kv.second.c_str());
        lua_settable(state_, -3);
      }
      call<_N + 1>(args...);
    }

    std::string file_name_;
    lua_State* state_ = nullptr;
  };

}  // namespace script
}  // namespace radix

#endif  // RADIX_SCRIPT_SCRIPT_CLASS_HPP_
