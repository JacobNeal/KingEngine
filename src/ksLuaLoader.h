/********************************************************
* Class:            ksLuaLoader
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLuaLoader.h
*
*   Overview:
*       Contains the interface between C++ functionality
*       and Lua scripting for in game content creation.
*       Lua should have access to the following engine
*       types at this point:
*       
*       ksEntityLayer
*       ksControlLayer
*       ksApplication
*
********************************************************/

#ifndef KS_LUALOADER_H
#define KS_LUALOADER_H

#include <lua.hpp>
#include "ksEntityLayer.h"

class ksLuaLoader
{
    public:
        //                  Constructors
        ksLuaLoader(ksEntityLayer * entity_layer);
        
        //                  Methods
        void                insertEntity(int row, int col, int depth, double w, double h, int current_tile);

    private:
        //                  Data members
        ksEntityLayer *     m_entity_layer;
        lua_State *         m_lua_state;
};

#endif
