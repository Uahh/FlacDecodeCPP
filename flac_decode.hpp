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
class C_FLAC_PICTURE;

class C_FLAC
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
    vector<C_FLAC_PICTURE*> _vt_fp_picture;
    
public:
    C_FLAC(){};
    C_FLAC(string flac_file_path) : _str_flac_file_path(flac_file_path){};
    C_BIT_HELPER* bh_bit_helper;
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
    
    vector<C_FLAC_PICTURE*> getAllPictures() const;
    C_FLAC_PICTURE* getFrontPicture() const;
};

class C_FLAC_PICTURE
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
    C_FLAC_PICTURE(){};
    C_FLAC_PICTURE(string val) : _int_picture_block_stream(val){};
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

#endif /* flac_decode_hpp */
