# This works on systems that use pkgconfig. If you want to use it on
# systems that don't, such as Windows, you'll have to add to this.

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
