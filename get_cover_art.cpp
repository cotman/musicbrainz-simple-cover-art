#include <iostream>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/Release.h"
#include "coverart/CoverArt.h"
#include "coverart/Image.h"
#include "coverart/ImageList.h"

std::vector<std::string> get_cover_art(const std::string artist, const std::string album, const std::string query_limit)
{
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Album: " << album << std::endl;

    std::string search_string = "\"" + album + "\"" + " artist:\"" + artist + "\"";
    std::cout << "Search String: \'" << search_string << "\'" << std::endl;

    MusicBrainz5::CQuery Query("cover-art-query");
    MusicBrainz5::CQuery::tParamMap Params;
    Params["query"] = search_string;
    Params["limit"] = query_limit;

    CoverArtArchive::CCoverArt CoverArt("cover-art-query");

    std::vector <std::string> cover_art;

    try 
    {
        MusicBrainz5::CMetadata Metadata = Query.Query("release", "", "", Params);
        MusicBrainz5::CReleaseList *ReleaseList = Metadata.ReleaseList();

        for (int count = 0; count < ReleaseList->NumItems(); count++)
        {
            MusicBrainz5::CRelease *Release = ReleaseList->Item(count);

            std::string ReleaseID = Release->ID();
            std::cout << "ReleaseID: " << ReleaseID << std::endl;

            try
            {
                CoverArtArchive::CReleaseInfo ReleaseInfo = CoverArt.ReleaseInfo(ReleaseID);
                CoverArtArchive::CImageList *ImageList = ReleaseInfo.ImageList();

                for (int count = 0; count < ImageList->NumItems(); count++)
                {
                    CoverArtArchive::CImage *Image = ImageList->Item(count);
                    if (Image && Image->Front())
                    {
                        cover_art.push_back(Image->Image());
                    }
                }
            }
            catch (...)
            {
                // Might fail, but we don't care
            }
        }
    }
    catch (...)
    {
        // Might fail, but we don't care
    }

    return cover_art;
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cout << argv[0] << " \"<Artist Name>\" \"<Album Name>\" <Query Limit>" << std::endl;
        return 1;
    }

    std::vector <std::string> cover_art = get_cover_art(argv[1], argv[2], argv[3]);

    for (int i = 0; i < cover_art.size(); i++)     
        std::cout << "Cover Art: " << cover_art[i] << std::endl;

    return 0;
}
