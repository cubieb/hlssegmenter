/*
 * HlsPlaylistGenerator.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef HLSPLAYLISTGENERATOR_H_
#define HLSPLAYLISTGENERATOR_H_

#include "segmenterCommon.h"


class HlsPlaylistGenerator {

	MasterPlaylist *master;
	std::list<VariantPlaylist *> variants;

public:
	HlsPlaylistGenerator();
	virtual ~HlsPlaylistGenerator();

	void generate_header(ConfigParams &config);
	void update_media(IFrameIndex *index);
	void update_iframe(IFrameIndex *index);
};

#endif /* HLSPLAYLISTGENERATOR_H_ */
