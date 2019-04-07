/*
   Simple example of using the MusicBrainz C++ libraries and APIs to return thumbnail and full image URLs
   to cover art for album and artist search combinations.
*/


#include <map>
#include <iostream>
#include <iterator>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/Release.h"
#include "coverart/CoverArt.h"
#include "coverart/Image.h"
#include "coverart/ImageList.h"
#include "coverart/Thumbnails.h"


std::map<std::string, std::string> get_cover_art_urls(const std::string artist, const std::string album, const std::string query_limit)
{
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Album: " << album << std::endl;

    // Format: '"<ALBUM_NAME>" artist:"<ARTIST_NAME>"'
    std::string search_string = "\"" + album + "\"" + " artist:\"" + artist + "\"";
    std::cout << "Search String: \'" << search_string << "\'" << std::endl;

    MusicBrainz5::CQuery Query("cover-art-query");
    MusicBrainz5::CQuery::tParamMap Params;
    Params["query"] = search_string;
    Params["limit"] = query_limit;

    CoverArtArchive::CCoverArt CoverArt("cover-art-query");

    std::map<std::string, std::string> image_urls;

    try
    {
        // First get a list of Releases that match the search criteria
        MusicBrainz5::CMetadata Metadata = Query.Query("release", "", "", Params);
        MusicBrainz5::CReleaseList *ReleaseList = Metadata.ReleaseList();

        std::string image_thumbnail_url;
        std::string image_full_url;

        // Iterate the list of Releases and, for each, pluck out the unique Release ID
        for (int count = 0; count < ReleaseList->NumItems(); count++)
        {
            MusicBrainz5::CRelease *Release = ReleaseList->Item(count);

            std::string ReleaseID = Release->ID();
            std::cout << "Parsing MusicBrainz Release ID: " << ReleaseID << std::endl;

            // We have a Release ID, so query for the appropriate images
            try
            {
                CoverArtArchive::CReleaseInfo ReleaseInfo = CoverArt.ReleaseInfo(ReleaseID);
                CoverArtArchive::CImageList* ImageList = ReleaseInfo.ImageList();

                for (int count = 0; count < ImageList->NumItems(); count++)
                {
                    CoverArtArchive::CImage* Image = ImageList->Item(count);
                    CoverArtArchive::CThumbnails* Thumbnails = Image->Thumbnails();

                    if (!Image->Front() or Thumbnails->Small().empty())
                    {
                        continue;
                    }

                    image_thumbnail_url = Thumbnails->Small();
                    image_full_url = Image->Image();

                    image_urls.insert(std::pair<std::string, std::string>(image_thumbnail_url, image_full_url));
                }
            }
            catch (...)
            {
                // No appropriate images were found for the Release ID, but we continue to check any others
            }
        }
    }
    catch (...)
    {
        // There was an issue with MusicBrainz
    }

    return image_urls;
}


int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cout << argv[0] << " \"<Artist Name>\" \"<Album Name>\" <Query Limit>" << std::endl;
        return 1;
    }

    std::map<std::string, std::string> cover_art_urls = get_cover_art_urls(argv[1], argv[2], argv[3]);
    std::map<std::string, std::string>::iterator iterator;

    for (iterator = cover_art_urls.begin(); iterator != cover_art_urls.end(); iterator++)
    {
        std::cout << "Thumbnail: " << iterator->first << ", Full: " << iterator->second << std::endl;
    }

    return 0;
}
