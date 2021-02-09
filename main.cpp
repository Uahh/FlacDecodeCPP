//
//  main.cpp
//  flac
//
//  Created by Uahh on 2021/1/24.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include "bit_stream_helper.hpp"
#include "flac_decode.hpp"

using namespace std;

int main()
{
    C_Flac* flac = new C_Flac("/Users/uahh/XcodeC++Project/flac/flac/Theme of Violet Evergarden.flac");
    flac->decodeFlacFile();
    
    cout << "最小的采样数/The minimum block size: " << flac->getMinBlockSize() << endl;
    cout << "最大的采样数/The maximum block size: " << flac->getMaxBlockSize() << endl;
    cout << "最小帧/The minimum frame size: " << flac->getMinFrameSize() << " Byte" << endl;
    cout << "最大帧/The maximum frame size: " << flac->getMaxFrameSize() << " Byte" << endl;
    cout << "采样率/Sample rate in Hz: " << flac->getSampleRate() << " Hz" << endl;
    cout << "声道数/number of channels: " << flac->getChannel() << endl;
    cout << "采样深度/bits per sample: " << flac->getBitsPerSample() << " bit" << endl;
    cout << endl;
    
    cout << "图片类型/picture type: " << flac->getFrontPicture()->getPictureType() << endl;
    cout << "图片宽度/The width of the picture: " << flac->getFrontPicture()->getPictureWidth() << endl;
    cout << "图片高度/The height of the picture: " << flac->getFrontPicture()->getPictureHeight() << endl;
    cout << "图片色彩深度/The color depth of the picture: " << flac->getFrontPicture()->getPictureBitsPerPixel() << endl;
    cout << "图片大小/The length of the picture data in bytes: " << flac->getFrontPicture()->getPictureSize() << endl;
    cout << "保存图片到桌面/Save to desktop" << endl;
//    flac->getFrontPicture()->savePicture("/Users/uahh/Desktop/test.jpg");
    cout << endl;
    cout << "标题/TITLE: " << flac->_fm_metadata->getTitle() << endl;
    cout << "专辑/ALBUM: " << flac->_fm_metadata->getAlbum() << endl;
    cout << "专辑艺术家/ALBUMARTIST: " << flac->_fm_metadata->getAlbumArtist() << endl;
    cout << "类型/GENRE: " << flac->_fm_metadata->getGenre() << endl;
    cout << "类型编号/GENRENUMBER: " << flac->_fm_metadata->getGenreNumber() << endl;
    cout << "日期/DATE: " << flac->_fm_metadata->getDate() << endl;
    cout << "作曲家/COMPOSER: " << flac->_fm_metadata->getComposer() << endl;
    cout << "CD编号/DISCNUMBER: " << flac->_fm_metadata->getDiscNumber() << endl;
    cout << "轨道编号/TRACKNUMBER: " << flac->_fm_metadata->getTrackNumber() << endl;
    cout << "版权/COPYRIGHT: " << flac->_fm_metadata->getCopyright() << endl;
    cout << "组织/ORGANIZATION: " << flac->_fm_metadata->getOrganization() << endl;
    cout << "评论/COMMENT: " << flac->_fm_metadata->getComment() << endl;
    cout << "演员/PERFORMER: " << flac->_fm_metadata->getPerformer() << endl;
    cout << "总数/DISCTOTALCD: " << flac->_fm_metadata->getDisctotal() << endl;
    cout << "动态范围/DYNAMIC RANGE: " << flac->_fm_metadata->getDyanmicRange() << endl;
    cout << "指挥/CONDUCTOR: " << flac->_fm_metadata->getConductor() << endl;
    cout << "国际标准音像制品编码/ISRC: " << flac->_fm_metadata->getISRC() << endl;
    cout << "标签/LABEL: " << flac->_fm_metadata->getLabel() << endl;
    return 0;
}
