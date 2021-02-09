//
//  flac_decode.hpp
//  flac
//
//  Created by Uahh on 2021/2/2.
//

#ifndef flac_decode_hpp
#define flac_decode_hpp

#include "bit_stream_helper.hpp"

using namespace std;
class C_Flac;
class C_Flac_Metadata;
class C_Flac_Picture;

class C_Flac
{
private:
    string _str_flac_file_path = "";
    int _int_min_block_size = -1;
    int _int_max_block_size = -1;
    int _int_min_frame_size = -1;
    int _int_max_frame_size = -1;
    int _int_sample_rate = -1;
    int _int_channel = -1;
    int _int_bits_per_sample = -1;
    vector<C_Flac_Picture*> _vt_fp_picture;
//    C_Flac_Metadata* _fm_metadata = new C_Flac_Metadata();
    
public:
    C_Flac() = default;
    C_Flac(string flac_file_path) : _str_flac_file_path(flac_file_path){};
    C_BIT_HELPER* bh_bit_helper;
    C_Flac_Metadata* _fm_metadata;
    void readFlacFile(string flac_file_path);
    void decodeFlacFile();
    void decodeFlacInfo(string hex_stream);
    void decodeVorbisComment(string hex_stream);
    void decodeFlacPicture(string hex_stream);
    
    int getMinBlockSize() const;
    int getMaxBlockSize() const;
    int getMinFrameSize() const;
    int getMaxFrameSize() const;
    int getSampleRate() const;
    int getChannel() const;
    int getBitsPerSample() const;
    
    vector<C_Flac_Picture*> getAllPictures() const;
    C_Flac_Picture* getFrontPicture() const;
};

class C_Flac_Picture
{
private:
    string _str_picture_type = "";
    string _int_picture_block_stream = "";
    int _int_picture_miem = -1;
    int _int_picture_width = -1;
    int _int_picture_height = -1;
    int _int_picture_bits_per_pixel = -1;
    int _int_picture_size = -1;
public:
    C_Flac_Picture() = default;
    C_Flac_Picture(string val) : _int_picture_block_stream(val){};
    int p = 0;
    void setPictureType(string val);
    void setPictureTMiem(int val);
    void setPictureWidth(int val);
    void setPictureHeight(int val);
    void setPictureBitsPerPixel(int val);
    void setPictureSize(int val);
    string getPictureType() const;
    int getPictureMiem() const;
    int getPictureWidth() const;
    int getPictureHeight() const;
    int getPictureBitsPerPixel() const;
    int getPictureSize() const;
    string getPictureBlockStream() const;
    void savePicture(string path) const;
};

class C_Flac_Metadata
{
private:
    string _str_title = "";
    string _str_album = "";
    string _str_album_artist = "";
    string _str_genre = "";
    string _str_genre_number = "";
    string _str_date = "";
    string _str_composer = "";
    string _str_disc_number = "";
    string _str_track_number = "";
    string _str_copyright = "";
    string _str_organization = "";
    string _str_comment = "";
    string _str_performer = "";
    string _str_disctotal = "";
    string _str_dyanmic_range = "";
    string _str_conductor = "";
    string _str_isrc = "";
    string _str_label = "";
public:
    C_Flac_Metadata() = default;
    void seleteSetFunction(string str, string sub);
    void setTitle(string str);
    void setAlbum(string str);
    void setAlbumArtist(string str);
    void setGenre(string str);
    void setGenreNumber(string str);
    void setDate(string str);
    void setComposer(string str);
    void setDiscNumber(string str);
    void setTrackNumber(string str);
    void setCopyright(string str);
    void setOrganization(string str);
    void setComment(string str);
    void setPerformer(string str);
    void setDisctotal(string str);
    void setDyanmicRange(string str);
    void setConductor(string str);
    void setISRC(string str);
    void setLabel(string str);
    string getTitle() const;
    string getAlbum() const;
    string getAlbumArtist() const;
    string getGenre() const;
    string getGenreNumber() const;
    string getDate() const;
    string getComposer() const;
    string getDiscNumber() const;
    string getTrackNumber() const;
    string getCopyright() const;
    string getOrganization() const;
    string getComment() const;
    string getPerformer() const;
    string getDisctotal() const;
    string getDyanmicRange() const;
    string getConductor() const;
    string getISRC() const;
    string getLabel() const;
};

#endif /* flac_decode_hpp */
