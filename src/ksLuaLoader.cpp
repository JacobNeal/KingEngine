/********************************************************
* Class:            ksLuaLoader
* Author:           Beyond Parallel - Jacob Neal
*
* Filename:         ksLuaLoader.cpp
********************************************************/

#include "ksLuaLoader.h"

/********************************************************
*   ksLuaLoader
*
*   Initializes the Lua state and sets the pointer to
*   access the entity layer of the engine.
********************************************************/
ksLuaLoader::ksLuaLoader(ksEntityLayer * entity_layer)
{
    m_entity_layer = entity_layer;

    // Set up Lua
    m_state = luaL_newstate();

    // Loads optional standard library
    luaL_openlibs(m_state);

    lua_pushcfunction(m_state, insertEntity);
    lua_setglobal(m_state, "insertEntity");
}

/********************************************************
*   insertEntity
*
*   Insert an entity from within Lua by passing the
*   position, width, height, and tile of the entity
*   to insert.
********************************************************/
void ksLuaLoader::insertEntity(int row, int col, int depth, double w, double h, int current_tile)
{

}

bool ksLuaLoader::loadScript(std::string filename)
{
    bool error = false;

    if (luaL_loadfile(m_state, filename))
    {
        std::cout << "An error occurred while loading: " << filename << "\n"
                  << lua_tostring(m_state -1) << '\n';
        
        lua_pop(m_state, 1);
        error = true;
    }

    return !error;
}


