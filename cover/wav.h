/*
 * wav.h
 *
 * (c) 2023 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
 */
#ifndef _wav_h
#define _wav_h

#include <cstdlib>
#include <cstdio>
#include <getopt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fcntl.h>

namespace wavreader {

/**
 * \brief Frame class
 */
class frame {
	int	_channels;
	short	_data[2];
public:
	frame(unsigned char *data, int channels);
	short	operator[](int channel) const { return _data[channel]; }
};

/**
 * \brief Class for a wav file chunk
 */
class chunk {
	unsigned char	*_data;
	unsigned int	_length;
	std::string	_type;
public:
	const std::string&	type() const { return _type; }
	int	length() const { return _length; }
	chunk(int _fd);
	unsigned char	*operator[](int offset) const { return _data + offset; }
	chunk(const chunk& other) = delete;
	chunk& operator=(const chunk& other) = delete;
	~chunk();
	frame	getFrame(int offset, int channels);
};

typedef std::shared_ptr<chunk>	chunk_ptr;

/**
 * \brief Class to read WAV files
 */
class wav {
	std::string	_filename;
	unsigned int	_size;
public:
	const std::string& 	filename() const { return _filename; }
private:
	int	_fd;
	chunk_ptr	_current;
public:
	wav(const std::string&);
	chunk_ptr	current() {
		return _current;
	}
	chunk_ptr	next() {
		return _current = chunk_ptr(new chunk(_fd));
	}
private:
	int	_format;
	int	_channels;
	int	_samplesPerSecond;
	int	_avgBytesPerSecond;
	int	_blockAlign;
	int	_bitsPerSample;
public:
	int	format() const { return _format; }
	int	channels() const { return _channels; }
	int	samplesPerSecond() const { return _samplesPerSecond; }
	int	avgBytesPerSecond() const { return _avgBytesPerSecond; }
	int	blockAlign() const { return _blockAlign; }
	int	bitsPerSample() const { return _bitsPerSample; }
};

} // namespace wavreader

#endif /* _wav_h */
