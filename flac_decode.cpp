//
//  flac_decode.cpp
//  flac
//
//  Created by Uahh on 2021/2/2.
//

#include "flac_decode.hpp"

void C_FLAC::readFlacFile(string flac_file_path)
{
    this->_str_flac_file_path = flac_file_path;
    return;
}

void C_FLAC::decodeFlacInfo(string hex_stream)
{
    //采样数
    string temp;
    temp = { hex_stream[0], hex_stream[1] };
    int min_block = bh_bit_helper->charArray2Int(temp);
    this->_int_min_block_size = min_block;
    temp = { hex_stream[2], hex_stream[3] };
    int max_block = bh_bit_helper->charArray2Int(temp);
    this->_int_max_block_size = max_block;

    // 最小帧
    temp = { hex_stream[4], hex_stream[5], hex_stream[6] };
    bitset<24> bits1;
    for(int i = 0; i < 8; i++)
    {
        bitset<8> temp_bit = bitset<8>(temp[i]);
        for(int j = 0; j < 8; j++)
        {
            bits1[i*8 + j] = temp_bit[7 - j];
        }
    }
    int min_frame = bh_bit_helper->bitStream2Int(bits1.to_string());
    if(min_frame)
        this->_int_min_frame_size = min_frame;
    else
        this->_int_min_frame_size = -1;

    // 最大帧
    temp = { hex_stream[7], hex_stream[8], hex_stream[9] };
    bitset<24> bits2;
    for(int i = 0; i < 8; i++)
    {
        bitset<8> temp_bit = bitset<8>(temp[i]);
        for(int j = 0; j < 8; j++)
        {
            bits2[i*8 + j] = temp_bit[7 - j];
        }
    }
    int max_frame = bh_bit_helper->bitStream2Int(bits2.to_string());
    if(max_frame)
        this->_int_max_frame_size = max_frame;
    else
        this->_int_max_frame_size = -1;

    // 采样率
    temp = { hex_stream[10], hex_stream[11], hex_stream[12] };
    bitset<20> bits3;
    for(int i = 0; i < 8; i++)
    {
        bitset<8> temp_bit = bitset<8>(temp[i]);
        for(int j = 0; j < 8; j++)
        {
            bits3[i*8 + j] = temp_bit[7 - j];
        }
    }
    int hz = bh_bit_helper->bitStream2Int(bits3.to_string());
    if(hz)
        this->_int_sample_rate = hz;
    else
        this->_int_sample_rate = -1;

    // 声道数
    temp = { hex_stream[12] };
    bitset<8> bits4;
    for(int i = 0; i < 8; i++)
    {
        bitset<8> temp_bit = bitset<8>(temp[i]);
        for(int j = 0; j < 8; j++)
        {
            bits4[i*8 + j] = temp_bit[7 - j];
        }
    }
    bits4 <<= 1;
    bits4 >>= 5;
    bits4 <<= 5;
    int channels = bh_bit_helper->bitStream2Int(bits4.to_string());
    channels += 1;
    if(channels)
        this->_int_channel = channels;
    else
        this->_int_channel = -1;

    // 采样深度
    temp = { hex_stream[12], hex_stream[13]};
    bitset<16> bits5;
    for(int i = 0; i < 8; i++)
    {
        bitset<8> temp_bit = bitset<8>(temp[i]);
        for(int j = 0; j < 8; j++)
        {
            bits5[i*8 + j] = temp_bit[7 - j];
        }
    }
    bits5 >>= 7;
    bits5 <<= 11;
    int bits_per_sample = bh_bit_helper->bitStream2Int(bits5.to_string());
    bits_per_sample += 1;
    if(bits_per_sample)
        this->_int_bits_per_sample = bits_per_sample;
    else
        this->_int_bits_per_sample = -1;
}

void C_FLAC::decodeFlacPicture(string hex_stream)
{
    
    string picture_type[] = { "Other", "32x32 pixels", "Other file icon", "Cover (front)", "Cover (back)", "Leaflet page", "Media (e.g. label side of CD)", "Lead artist/lead performer/soloist", "Artist/performer", "Conductor", "Band/Orchestra", "Composer", "Lyricist/text writer", "Recording Location", "During recording", "During performance", "Movie/video screen capture", "A bright coloured fish", "Illustration", "Band/artist logotype", "Publisher/Studio logotype"};
    /*
        Picture Type:
            0 - Other
            1 - 32x32 pixels 'file icon' (PNG only)
            2 - Other file icon
            3 - Cover (front)
            4 - Cover (back)
            5 - Leaflet page
            6 - Media (e.g. label side of CD)
            7 - Lead artist/lead performer/soloist
            8 - Artist/performer
            9 - Conductor
            10 - Band/Orchestra
            11 - Composer
            12 - Lyricist/text writer
            13 - Recording Location
            14 - During recording
            15 - During performance
            16 - Movie/video screen capture
            17 - A bright coloured fish
            18 - Illustration
            19 - Band/artist logotype
            20 - Publisher/Studio logotype
    */
    
//    int p = 0;
    C_FLAC_PICTURE* picture = new C_FLAC_PICTURE(hex_stream);
    string temp = { hex_stream[0], hex_stream[1], hex_stream[2], hex_stream[3] };
    int type = bh_bit_helper->charArray2Int(temp);
    picture->setPictureType(picture_type[type]);
    picture->p += 3;
    
    temp = { hex_stream[4], hex_stream[5], hex_stream[6], hex_stream[7] };
    int miem_size = bh_bit_helper->charArray2Int(temp);
    picture->p += 4 + miem_size;

    temp = "";
    for(int i = 0; i < miem_size; i++)
    {
        temp += hex_stream[i + 8];
    }
    picture->p += 4;
    
    //picture_width
    temp = { hex_stream[picture->p + 1], hex_stream[picture->p + 2], hex_stream[picture->p + 3], hex_stream[picture->p + 4] };
    int picture_width = bh_bit_helper->charArray2Int(temp);
    picture->setPictureWidth(picture_width);
    picture->p += 4;
    
    //picture_height
    temp = { hex_stream[picture->p + 1], hex_stream[picture->p + 2], hex_stream[picture->p + 3], hex_stream[picture->p + 4] };
    int picture_height = bh_bit_helper->charArray2Int(temp);
    picture->setPictureHeight(picture_height);
    picture->p += 4;

    //bits_per_pixel
    temp = { hex_stream[picture->p + 1], hex_stream[picture->p + 2], hex_stream[picture->p + 3], hex_stream[picture->p + 4] };
    int bits_per_pixel = bh_bit_helper->charArray2Int(temp);
    picture->setPictureBitsPerPixel(bits_per_pixel);
    picture->p += 4;

    temp = { hex_stream[picture->p + 1], hex_stream[picture->p + 2], hex_stream[picture->p + 3], hex_stream[picture->p + 4] };
    picture->p += 4;

    //picture_size
    temp = { hex_stream[picture->p + 1], hex_stream[picture->p + 2], hex_stream[picture->p + 3], hex_stream[picture->p + 4] };
    int picture_size = bh_bit_helper->charArray2Int(temp);
    picture->setPictureSize(picture_size);
    picture->p += 4;

    this->_vt_fp_picture.push_back(picture);
}

void C_FLAC::decodeVorbisComment(string hex_stream)
{
    hex_stream += "~~~";
    cout << hex_stream << endl;

    string metadata[19] = {"TITLE=", "ALBUM=", "ALBUMARTIST=", "GENRE=", "GENRENUMBER=", "DATE=", "COMPOSER=", "DISCNUMBER=", "TRACKNUMBER=", "COPYRIGHT=", "ORGANIZATION=", "COMMENT=", "PERFORMER=", "MOOD=", "DISCTOTAL=", "DYNAMIC RANGE=", "CONDUCTOR=", "ISRC=", "Label=", };
    for(int i = 0; i < 19; i++)
    {
        int step = 5;
        unsigned long tag = hex_stream.find(metadata[i]);
        if(tag == hex_stream.npos)
            continue;
        string sub = "";
        while(sub.find("~~~") == sub.npos)
        {
            sub = hex_stream.substr(tag + metadata[i].size(), step);
            step += 5;
        }
        sub = sub.substr(0, sub.find("~~~"));
        cout << metadata[i].substr(0, metadata[i].size() - 1) << ": " << sub << endl;
    }
}

void C_FLAC::decodeFlacFile()
{
    ifstream music_file(this->_str_flac_file_path, ios::in|ios::binary);
    music_file.seekg(0, ios::beg);
    char file_flag_flac[5] = "fLaC";
    if (!music_file.is_open())
    {
        cerr << "未成功打开文件" << endl;
        return;
    }
    for(int i = 0; i < 4; i++)
    {
        char temp[1];
        music_file.read(temp, 1);
        if(temp[0] == file_flag_flac[i])
            continue;
        else
        {
            cerr << "此文件不是flac文件" << endl;
            return;
        }
    }
    cout << "文件读取成功" << endl;

//    music_file.seekg(20);
//    cout << music_file.tellg() << endl;

    bool break_flag = false;

    while(true)
    {
        if(break_flag)
            break;
        char header_byte[1];

        music_file.read(header_byte, 1);
        bitset<8> header = bitset<8>(header_byte[0]);
//        cout << '\n' << header.to_string() << endl;
        if(header.to_string()[0] == '1')
        {
            break_flag = true;
            header_byte[0] <<= 1;
            header_byte[0] >>= 1;
        }
        if((int)header_byte[0] == 0)
        {
//            cout << "STREAMINFO:" << endl;

            char hex_3[3];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3, 3);
            char metadata_data[num];
            music_file.read(metadata_data, num);

            string input_metadata_data = "";
            for(int i = 0; i < sizeof(metadata_data); i++)
             {
                 input_metadata_data += metadata_data[i];
             }
            this->decodeFlacInfo(input_metadata_data);
        }
        else if((int)header_byte[0] == 1)
        {
//            cout << "PADDING" << endl;

            char hex_3[3];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3, 3);

            char picture_data[num];
            music_file.read(picture_data, num);
            string input_metadata_data = "";
            for(int i = 0; i < sizeof(picture_data); i++)
             {
                 input_metadata_data += picture_data[i];
             }
//            cout << "DataSize: " << input_metadata_data.size() << endl;
//            ResolutionVorbisComment(input_metadata_data);
        }
        else if((int)header_byte[0] == 2)
        {
//            cout << "APPLICATION" << endl;
            char hex_3[3];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3, 3);

            char picture_data[num];
            music_file.read(picture_data, num);
            string input_metadata_data = "";
            for(int i = 0; i < sizeof(picture_data); i++)
             {
                 input_metadata_data += picture_data[i];
             }
//            cout << "DataSize: " << input_metadata_data.size() << endl;
        }
        else if((int)header_byte[0] == 3)
        {
//            cout << "SEEKTABLE" << endl;
            char hex_3[3];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3, 3);

            char picture_data[num];
            music_file.read(picture_data, num);
            string input_metadata_data = "";
            for(int i = 0; i < sizeof(picture_data); i++)
             {
                 input_metadata_data += picture_data[i];
             }
//            cout << "DataSize: " << input_metadata_data.size() << endl;
        }
        else if((int)header_byte[0] == 4)
        {
//            cout << "VORBIS COMMENT" << endl;

            char hex_3[3];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3, 3);
            char picture_data[num];
            music_file.read(picture_data, num);
            string input_metadata_data = "";
            for(int i = 0; i < sizeof(picture_data); i++)
             {
                 if(picture_data[i] != '\0')
                     input_metadata_data += picture_data[i];
                 else
                     input_metadata_data += "~";
             }
//            cout << "DataSize: " << input_metadata_data.size() << endl;
            this->decodeVorbisComment(input_metadata_data);
        }
        else if((int)header_byte[0] == 5)
        {
//            cout << "CUESHEET" << endl;
            char hex_3[3];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3, 3);

            char picture_data[num];
            music_file.read(picture_data, num);
            string input_metadata_data = "";
            for(int i = 0; i < sizeof(picture_data); i++)
             {
                 input_metadata_data += picture_data[i];
             }
//            cout << "DataSize: " << input_metadata_data.size() << endl;
        }
        else if((int)header_byte[0] == 6)
        {
//            cout << "PICTURE" << endl;

            char hex_3[4];
            music_file.read(hex_3, 3);
            int num = bh_bit_helper->charArray2Int(hex_3);
            char picture_data[num];
            music_file.read(picture_data, num);

            string input_metadata_data = "";
            for(int i = 0; i < sizeof(picture_data); i++)
            {
                input_metadata_data += picture_data[i];
            }
            this->decodeFlacPicture(input_metadata_data);
        }
    }
    music_file.close();
}

int C_FLAC::getMinBlockSize() const
{
    return this->_int_min_block_size;
}

int C_FLAC::getMaxBlockSize() const
{
    return this->_int_max_block_size;
}

int C_FLAC::getMinFrameSize() const
{
    return this->_int_min_frame_size;
}

int C_FLAC::getMaxFrameSize() const
{
    return this->_int_max_frame_size;
}

int C_FLAC::getSampleRate() const
{
    return this->_int_sample_rate;
}

int C_FLAC::getChannel() const
{
    return this->_int_channel;
}

int C_FLAC::getBitsPerSample() const
{
    return this->_int_bits_per_sample;
}

vector<C_FLAC_PICTURE*> C_FLAC::getAllPictures() const
{
    return this->_vt_fp_picture;
}

C_FLAC_PICTURE* C_FLAC::getFrontPicture() const
{
    if(_vt_fp_picture.size() > 0)
        return this->_vt_fp_picture[0];
    else
        return nullptr;
}

void C_FLAC_PICTURE::setPictureType(string val)
{
    this->_str_picture_type = val;
}
void C_FLAC_PICTURE::setPictureTMiem(int val)
{
    this->_int_picture_miem = val;
}
void C_FLAC_PICTURE::setPictureWidth(int val)
{
    this->_int_picture_width = val;
}
void C_FLAC_PICTURE::setPictureHeight(int val)
{
    this->_int_picture_height = val;
}
void C_FLAC_PICTURE::setPictureBitsPerPixel(int val)
{
    this->_int_picture_bits_per_pixel = val;
}
void C_FLAC_PICTURE::setPictureSize(int val)
{
    this->_int_picture_size = val;
}
string C_FLAC_PICTURE::getPictureType() const
{
    return this->_str_picture_type;
}
int C_FLAC_PICTURE::getPictureMiem() const
{
    return this->_int_picture_miem;
}
int C_FLAC_PICTURE::getPictureWidth() const
{
    return this->_int_picture_width;
}
int C_FLAC_PICTURE::getPictureHeight() const
{
    return this->_int_picture_height;
}
int C_FLAC_PICTURE::getPictureBitsPerPixel() const
{
    return this->_int_picture_bits_per_pixel;
}
int C_FLAC_PICTURE::getPictureSize() const
{
    return this->_int_picture_size;
}

string C_FLAC_PICTURE::getPictureBlockStream() const
{
    return this->_int_picture_block_stream;
}

void C_FLAC_PICTURE::savePicture(string path) const
{
    ofstream outFile(path, ios::binary | ios::out | ios::trunc);
    string strm = getPictureBlockStream();
    for (int i = this->p + 1; i < strm.size(); i++)
    {
        outFile.put(strm[i]);
    }
}
