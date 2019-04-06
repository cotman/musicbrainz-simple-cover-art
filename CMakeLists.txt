cmake_minimum_required(VERSION 2.6)
project(musicbrainz-simple-cover-art)

find_library(LIBMUSICBRAINZ5CC musicbrainz5cc)
find_library(LIBCOVERARTCC coverartcc)

add_executable(musicbrainz-simple-cover-art get_cover_art.cpp)

target_link_libraries(musicbrainz-simple-cover-art ${LIBMUSICBRAINZ5CC} ${LIBCOVERARTCC})

install(TARGETS musicbrainz-simple-cover-art RUNTIME DESTINATION bin)
