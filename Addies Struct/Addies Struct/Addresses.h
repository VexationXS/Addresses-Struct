#pragma once
#include <Windows.h>
#include "RetCheck.h"

extern "C" {
#include "Lua\lua.h"
#include "Lua\lapi.h"
#include "Lua\lualib.h"
#include "Lua\lstate.h"
#include "Lua\lauxlib.h"
#include "Lua\luaconf.h"
#include "Lua\llimits.h"
#include "Lua\lapi.h"
#include "Lua\lfunc.h"
#include "Lua\lobject.h"
}

#define R_LUA_TNONE	(-1)
#define R_LUA_TNIL 0 
#define R_LUA_TLIGHTUSERDATA 1
#define R_LUA_TNUMBER 2
#define R_LUA_TBOOLEAN 3
#define R_LUA_TSTRING 4
#define R_LUA_TTHREAD 5
#define R_LUA_TFUNCTION 6
#define R_LUA_TTABLE 7
#define R_LUA_TUSERDATA 8
#define R_LUA_TPROTO 9
#define R_LUA_TUPVALUE 10

#define r_lua_pop(rL,n)		            r_lua_settop(rL, -(n)-1)
#define r_lua_getglobal(rL,s)	        r_lua_getfield(rL, -10002, (s))
#define r_lua_newtable(rL)              r_lua_createtable(rL, 0, 0)
#define r_lua_tostring(rL,i)	        r_lua_tolstring(rL, (i), NULL)
#define r_lua_pushcfunction(rL, fn)     (r_lua_pushcclosure(rL,fn,0))
#define r_lua_isnil(L,n)	        	(r_lua_type(L, (n)) == R_LUA_TNIL)

#define Unformat(a)(a + 0x400000 - (DWORD)GetModuleHandleA(0))
#define format(x)(x - 0x400000 + (DWORD)GetModuleHandle(NULL))

#if true
#define Declare(address, returnValue, callingConvention, ...) (returnValue(callingConvention*)(__VA_ARGS__))(Retcheck::unprotect(format(address)))
#else
#define Declare(address, returnValue, callingConvention, ...) (returnValue(callingConvention*)(__VA_ARGS__))(address)
#endif 

struct {
/*CC == CALLINGCONVENTION | ADDR == ADDRESS*/

/*Calling Conventions*/

#define CC_GETFIELD         __cdecl
#define CC_SETFIELD         __cdecl
#define CC_TOLSTRING        __cdecl
#define CC_SETTOP           __cdecl
#define CC_TOBOOLEAN        __cdecl
#define CC_PUSHVALUE        __cdecl
#define CC_PUSHNUMBER       __cdecl
#define CC_PUSHSTRING       __cdecl
#define CC_PCALL            __cdecl
#define CC_PUSHNIL          __cdecl
#define CC_NEXT             __cdecl
#define CC_PUSHBOOLEAN      __cdecl
#define CC_TONUMBER         __cdecl
#define CC_PUSHCCLOSURE     __cdecl
#define CC_CREATETABLE      __cdecl
#define CC_INSERT           __cdecl
#define CC_NEWTHREAD        __cdecl
#define CC_NEWUSERDATA      __cdecl
#define CC_PUSHTHREAD       __cdecl
#define CC_RAWGETI          __cdecl
#define CC_RAWSETI          __cdecl
#define CC_SETMETATABLE     __cdecl
#define CC_GETMETATABLE     __cdecl
#define CC_TOUSERDATA       __cdecl
#define CC_TYPE             __cdecl
#define CC_NEWLSTR          __cdecl
#define CC_VGETTABLE        __cdecl
#define CC_VSETTABLE        __cdecl
#define CC_RESUME           __cdecl
#define CC_INDEX2ADR        __cdecl
#define CC_LREF             __cdecl
#define CC_GETTABLE         __cdecl
#define CC_SETTABLE         __cdecl
#define CC_PUSHLIGHTUD      __cdecl
#define CC_GETTOP           __cdecl
#define CC_GETUPVALUES      __cdecl
#define CC_SETUPVALUES      __cdecl
#define CC_PRINT            __cdecl
#define CC_SETREADONLY      __cdecl 

/*Addresses*/

#define ADDR_GETFIELD         0xDEADBEEF
#define ADDR_SETFIELD         0xDEADBEEF
#define ADDR_TOLSTRING        0xDEADBEEF
#define ADDR_SETTOP           0xDEADBEEF
#define ADDR_TOBOOLEAN        0xDEADBEEF
#define ADDR_PUSHVALUE        0xDEADBEEF
#define ADDR_PUSHNUMBER       0xDEADBEEF
#define ADDR_PUSHSTRING       0xDEADBEEF
#define ADDR_PCALL            0xDEADBEEF
#define ADDR_PUSHNIL          0xDEADBEEF
#define ADDR_NEXT             0xDEADBEEF
#define ADDR_PUSHBOOLEAN      0xDEADBEEF
#define ADDR_TONUMBER         0xDEADBEEF
#define ADDR_PUSHCCLOSURE     0xDEADBEEF
#define ADDR_CREATETABLE      0xDEADBEEF
#define ADDR_INSERT           0xDEADBEEF
#define ADDR_NEWTHREAD        0xDEADBEEF
#define ADDR_NEWUSERDATA      0xDEADBEEF
#define ADDR_PUSHTHREAD       0xDEADBEEF
#define ADDR_RAWGETI          0xDEADBEEF
#define ADDR_RAWSETI          0xDEADBEEF
#define ADDR_SETMETATABLE     0xDEADBEEF
#define ADDR_GETMETATABLE     0xDEADBEEF
#define ADDR_TOUSERDATA       0xDEADBEEF
#define ADDR_TYPE             0xDEADBEEF
#define ADDR_NEWLSTR          0xDEADBEEF
#define ADDR_VGETTABLE        0xDEADBEEF
#define ADDR_VSETTABLE        0xDEADBEEF
#define ADDR_RESUME           0xDEADBEEF
#define ADDR_INDEX2ADR        0xDEADBEEF
#define ADDR_LREF             0xDEADBEEF
#define ADDR_GETTABLE         0xDEADBEEF
#define ADDR_SETTABLE         0xDEADBEEF
#define ADDR_PUSHLIGHTUD      0xDEADBEEF
#define ADDR_GETTOP           0xDEADBEEF
#define ADDR_GETUPVALUES      0xDEADBEEF
#define ADDR_SETUPVALUES      0xDEADBEEF
#define ADDR_PRINT            0xDEADBEEF
#define ADDR_SETREADONLY      0xDEADBEEF 
}RBX;

union r_Value
{
	int b;
	double n;
	void* p;
	void* gc;
};

struct r_TValue
{
	r_Value value;
	int tt;
	int value_0;
	int value_1;
	int unk;
};

const auto r_lua_getfield = Declare(ADDR_GETFIELD, void, CC_GETFIELD, int, int, const char);
const auto r_lua_tolstring = Declare(ADDR_TOLSTRING, char*, DWORD, int, size_t *size);
const auto r_lua_toboolean = Declare(ADDR_TOBOOLEAN, int, CC_TOBOOLEAN, int, int);
const auto r_lua_pushvalue = Declare(ADDR_PUSHVALUE, void, CC_PUSHVALUE, int, int);
const auto r_lua_pushnumber = Declare(ADDR_PUSHNUMBER, void, CC_PUSHNUMBER, )(int, double);
const auto r_lua_pcall = Declare(ADDR_PCALL, int, CC_PCALL, int, int, int, int);
const auto r_lua_next = Declare(ADDR_NEXT, int, CC_NEXT, int, int);
const auto r_lua_tonumber = Declare(ADDR_TONUMBER, double, CC_TONUMBER, int, int);
const auto r_lua_pushcclosure = Declare(ADDR_PUSHCCLOSURE, void, CC_PUSHCCLOSURE, int, int, int);
const auto r_lua_createtable = Declare(ADDR_CREATETABLE, void, CC_CREATETABLE, int, int, int);
const auto r_lua_insert = Declare(ADDR_INSERT, void, CC_INSERT, int, int);
const auto r_lua_newthread = Declare(ADDR_NEWTHREAD, int, CC_NEWTHREAD, int);
const auto r_lua_newuserdata = Declare(ADDR_NEWUSERDATA, void*, CC_NEWUSERDATA, int, int);
const auto r_lua_pushthread = Declare(ADDR_PUSHTHREAD, int, CC_PUSHTHREAD, int, int);
const auto r_lua_rawgeti = Declare(ADDR_RAWGETI, void, CC_RAWGETI, int, int, int);
const auto r_lua_rawseti = Declare(ADDR_RAWSETI, void, CC_RAWSETI, int, int, int);
const auto r_lua_setmetatable = Declare(ADDR_SETMETATABLE, void, CC_SETMETATABLE, int, int, int);
const auto r_lua_getmetatable = Declare(ADDR_GETMETATABLE, int, CC_GETMETATABLE, int, int);
const auto r_lua_touserdata = Declare(ADDR_RAWGETI, int, CC_RAWGETI, int, int);
const auto r_lua_type = Declare(ADDR_TYPE, int, CC_TYPE, int, int);
const auto r_lua_newlstr = Declare(ADDR_NEWLSTR, int, CC_NEWLSTR, int, int, int);
const auto r_luaV_gettabe = Declare(ADDR_VGETTABLE, int, CC_VGETTABLE, int, int);
const auto r_luaV_settable = Declare(ADDR_VSETTABLE, int, CC_VSETTABLE, int, int);
const auto r_lua_resume = Declare(ADDR_RESUME, int, CC_RESUME, int, int);
const auto r_lua_index2adr = Declare(ADDR_INDEX2ADR, int, CC_INDEX2ADR, int, int);
const auto r_luaL_ref = Declare(ADDR_LREF, int, CC_LREF, int, int);
const auto r_lua_gettable = Declare(ADDR_GETTABLE, int, CC_GETTABLE, int, int);
const auto r_lua_settable = Declare(ADDR_SETTABLE, int, CC_SETTABLE, int, int);
const auto r_lua_pushlightuserdata = Declare(ADDR_PUSHLIGHTUD, int, CC_PUSHLIGHTUD, int, int);
const auto r_lua_getupvalues = Declare(ADDR_GETUPVALUES, int, CC_GETUPVALUES, int, int);
const auto r_lua_print = Declare(ADDR_PRINT, int, CC_PRINT, int, int);
const auto r_lua_setreadonly = Declare(ADDR_SETREADONLY, int, CC_SETREADONLY, int, int);

int top = 20, base = 24;

typedef DWORD _DWORD;

r_TValue* r_lua_gettop(int r_lua_State) {
	return *(r_TValue**)(r_lua_State + 16);
}

void r_lua_pushnil(DWORD a1) {
	*(_DWORD *)(*(_DWORD *)(a1 + top) + 8) = 0;
	*(_DWORD *)(a1 + top) += 16;
}

void r_lua_pushboolean(DWORD a1, int a2) {
	_DWORD *v2;
	v2 = *(_DWORD **)(a1 + top);
	*v2 = a2 != 0;
	v2[2] = 3;
	*(_DWORD *)(a1 + top) += 16;
}

void r_lua_pushstring(int rState, const char *s) {
	int v3 = *(DWORD *)(rState + top);
	*(DWORD *)v3 = r_lua_newlstr(rState, s, strlen(s));
	*(DWORD *)(v3 + 8) = R_LUA_TSTRING;
	*(DWORD *)(rState + top) += 16;
}

void r_lua_settop(int a1, int a2) {
	int i;
	if (a2 < 0)
	{
		*(_DWORD *)(a1 + top) += 16 * a2 + 16;
	}
	else
	{
		for (i = 16 * a2; *(_DWORD *)(a1 + top) < (unsigned int)(i + *(_DWORD *)(a1 + base)); *(_DWORD *)(a1 + top) += 16)
			*(_DWORD *)(*(_DWORD *)(a1 + top) + 8) = 0;
		*(_DWORD *)(a1 + top) = i + *(_DWORD *)(a1 + base);
	}
}

void r_lua_setfield(DWORD L, int idx, const char *k) {
	r_lua_pushvalue(L, idx);
	if (r_lua_getmetatable(L, -1)) {
		r_lua_getfield(L, -1, "__newindex");
		r_lua_pushvalue(L, -3);
		r_lua_pushstring(L, k);
		r_lua_pushvalue(L, -6);
		r_lua_pcall(L, 3, 1, 0);
		r_lua_pop(L, 3);
	}
	else {
		r_lua_pop(L, 1);
		r_lua_setfield(L, idx, k);
	}
}