/*
 * PlaylistInterface.h
 *
 *  Created on: Aug 7, 2014
 *      Author: satram
 */

#ifndef PLAYLISTINTERFACE_H_
#define PLAYLISTINTERFACE_H_

#include "segmenterCommon.h"

class PlaylistInterface {
protected:
	std::string playlist_path;
	std::string playlist_name;
	std::string playlist_url;

	Playlist playlist;

public:
	//PlaylistInterface();
	//virtual ~PlaylistInterface();
	void set_url(std::string &path, std::string &filename);
	void publish_playlist();
	virtual void add_header(HlsConfigParams & config)=0;
	virtual void add_header(variant_stream_info &stream_info)=0;
	virtual void update_node(ChunkIndex *index, VariantPlaylist *variant_playlist, bool addition){};
	virtual void update_node(IFrameIndex *index, VariantPlaylist *variant_playlist, bool addition){};
	virtual void add_footer()=0;
	virtual void finalize_playlist()=0;
};


#endif /* PLAYLISTINTERFACE_H_ */
