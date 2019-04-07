# MusicBrainz Simple Cover Art

## Background

A very basic example of using the [MusicBrainz](https://musicbrainz.org/) C++ libraries to retrieve thumbnail and full
URLs to cover art for album and artist search combinations:

* [`libmusicbrainz`](https://github.com/metabrainz/libmusicbrainz)
* [`libcoverart`](https://github.com/metabrainz/libcoverart)

## Prerequisites

You'll need the developer installs of the libraries (as well as the normal stuff, including `cmake`).

On Ubuntu:

    sudo apt install libmusicbrainz libcoverart

## Build and Run

    cd musicbrainz-simple-cover-art/
    cmake .
    make
    ./musicbrainz-simple-cover-art "<Artist Name>" "<Album Name>" <Query Limit>

## Example

    $ ./musicbrainz-simple-cover-art "The Primitives" "Lovely" 10
    Artist: The Primitives
    Album: Lovely
    Search String: '"Lovely" artist:"The Primitives"'
    Parsing MusicBrainz Release ID: a5ba15e3-cf7f-4069-9e97-336a243ace3c
    Parsing MusicBrainz Release ID: 4c703590-7386-49ee-854a-a4e54ed00814
    Parsing MusicBrainz Release ID: b18ab80e-6cf1-4d8a-9b1d-cf8aa9595b4f
    Parsing MusicBrainz Release ID: 6ac0e685-66a0-3177-af1d-eb8f85b93ef1
    Parsing MusicBrainz Release ID: 7fa519bb-57e2-4c89-b5aa-c469fb9a6a89
    Parsing MusicBrainz Release ID: eb164a12-edd0-4d30-9783-d74b51d42ee8
    Parsing MusicBrainz Release ID: 2b8da3df-5924-46e5-83bd-542166d2c037
    Parsing MusicBrainz Release ID: 381b4fd0-0456-47c4-8c79-abe3a71402dd
    Parsing MusicBrainz Release ID: 52d60d25-87b6-40cd-890b-21ef8bbabfb4
    Parsing MusicBrainz Release ID: 50ee9e80-3850-4e79-8389-807a12467d93
    Thumbnail: http://coverartarchive.org/release/2b8da3df-5924-46e5-83bd-542166d2c037/16298750844-250.jpg, Full: http://coverartarchive.org/release/2b8da3df-5924-46e5-83bd-542166d2c037/16298750844.jpg
    Thumbnail: http://coverartarchive.org/release/381b4fd0-0456-47c4-8c79-abe3a71402dd/11523050459-250.jpg, Full: http://coverartarchive.org/release/381b4fd0-0456-47c4-8c79-abe3a71402dd/11523050459.jpg
    Thumbnail: http://coverartarchive.org/release/4c703590-7386-49ee-854a-a4e54ed00814/4457399400-250.jpg, Full: http://coverartarchive.org/release/4c703590-7386-49ee-854a-a4e54ed00814/4457399400.jpg
    Thumbnail: http://coverartarchive.org/release/50ee9e80-3850-4e79-8389-807a12467d93/2278048950-250.jpg, Full: http://coverartarchive.org/release/50ee9e80-3850-4e79-8389-807a12467d93/2278048950.jpg
    Thumbnail: http://coverartarchive.org/release/7fa519bb-57e2-4c89-b5aa-c469fb9a6a89/4457418228-250.jpg, Full: http://coverartarchive.org/release/7fa519bb-57e2-4c89-b5aa-c469fb9a6a89/4457418228.jpg
    Thumbnail: http://coverartarchive.org/release/eb164a12-edd0-4d30-9783-d74b51d42ee8/8039434694-250.jpg, Full: http://coverartarchive.org/release/eb164a12-edd0-4d30-9783-d74b51d42ee8/8039434694.jpg
