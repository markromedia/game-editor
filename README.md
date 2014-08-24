## Synopsis

Flight is a sandbox for graphics/systems testing. Cross platform with a custom SDL-based opengl backend. 

## Roadmap

- cmake support
- OSX/*nix support
- Awesomium integration
- Famo.us integration
- Editor
- Live updates
- SSAO 
- Integrated LUA editor


## Installation

For windows the following environment variables must be set for cmake to work
- CPP_REPOSITORY - location of all the dependencies on list
- LUA_DIR - the location of the lua 5.1 installation. If lua is installed, the value of this should be %LUA_DEV%
- BOOST_ROOT - Set or wherever boost is locally installed OR %CPP_REPOSITORY%/boost

