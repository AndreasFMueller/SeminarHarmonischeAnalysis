/*
 * wav.cpp
 *
 * (c) 2023 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
 */
#include <cstdlib>
#include <cstdio>
#include <getopt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fcntl.h>
#include "wav.h"

namespace wavreader {

frame::frame(unsigned char *data, int channels) : _channels(channels) {
	for (int i = 0; i < _channels; i++) {
		_data[i] = *(short *)(data + (2 * i));
	}
}

chunk::chunk(int _fd) {
	unsigned char	buffer[8];
	int	bytes = read(_fd, buffer, 8);
	if (bytes != 8) {
		throw std::runtime_error("cannot read junk header");
	}
	_type = std::string((char *)buffer, 4);
	_length = *(unsigned int *)(buffer + 4);
	std::cout << "chunk " << _type << " of length " << _length;
	std::cout << std::endl;
	_data = new unsigned char[_length];
	bytes = read(_fd, _data, _length);
	if (bytes != _length) {
		throw std::runtime_error("cannot read chunk data");
	}
}

chunk::~chunk() {
	delete _data;
}

frame	chunk::getFrame(int offset, int channels) {
	return frame(_data + 2 * channels * offset, channels);
}

wav::wav(const std::string& filename) : _filename(filename) {
	_fd = open(filename.c_str(), O_RDONLY);
	if (_fd < 0) {
		std::cerr << "cannot open file " << filename << ": ";
		std::cerr << strerror(errno);
		throw std::runtime_error("cannot open file");
	}
	std::cout << "file opened" << std::endl;
	// read the RIFF
	{
		unsigned char	buffer[12];
		int	bytes = read(_fd, buffer, 12);
		if (bytes != 12) {
			std::cerr << "could not read RIFF" << std::endl;
			throw std::runtime_error("wrong number bytes in RIFF");
		}
		_size = *(unsigned int *)(buffer + 4);
		std::cout << "file size: " << _size << std::endl;
	}

	// read chunks until 
	chunk_ptr	cp;
	do {
		cp = next();
		std::cout << "chunk type: " << cp->type() << std::endl;
	} while (cp->type() != "fmt ");

	// analyze the current chunk, which is the fmt chunk
	{
		_format = *(unsigned short *)(*cp)[0];
		_channels = *(unsigned short *)(*cp)[2];
		_samplesPerSecond = *(unsigned int *)(*cp)[4];
		_avgBytesPerSecond = *(unsigned int *)(*cp)[8];
		_blockAlign = *(unsigned short *)(*cp)[12];
		_bitsPerSample = *(unsigned short *)(*cp)[14];
		std::cout << "format:             " << _format
			<< std::endl;
		std::cout << "channels:           " << _channels
			<< std::endl;
		std::cout << "samplesPerSecond:   " << _samplesPerSecond
			<< std::endl;
		std::cout << "avgBytesPerSecond:  " << _avgBytesPerSecond
			<< std::endl;
		std::cout << "blockAlign:         " << _blockAlign
			<< std::endl;
		std::cout << "bitsPerSample:      " << _bitsPerSample
			<< std::endl;
	}

	do {
		cp = next();
	} while (cp->type() != "data");

	std::cout << "data chunk of size " << cp->length() << " found" << std::endl;
}

} // namespace wavreader

